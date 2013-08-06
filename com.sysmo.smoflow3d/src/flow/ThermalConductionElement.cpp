/*
 * ThermalConductionElement.cpp
 *
 *  Created on: Aug 5, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "ThermalConductionElement.h"

ThermalConductionElement::ThermalConductionElement(Medium_Solid* medium, int numNodes)
: nodes(numNodes), heatFlows(numNodes) {
	internalState = MediumStateSolid_new(medium);
	MediumState_register(internalState);
}

ThermalConductionElement::~ThermalConductionElement() {
}

void ThermalConductionElement::assignNode(size_t nodeIndex, ThermalNode* node) {
	if (nodeIndex >= nodes.size()) {
		RaiseError("Illegal node index " << nodeIndex
				<< ", it must be in the interval [0 .. " << (nodes.size() - 1) << "]")
	}
	nodes[nodeIndex] = node;
}

double ThermalConductionElement::getHeatFlow(size_t nodeIndex) {
	return heatFlows.at(nodeIndex);
}

void ThermalConductionElement::getFlow(size_t nodeIndex, FluidFlow* flow) {
	flow->enthalpyFlowRate = getHeatFlow(nodeIndex);
}

#include "Eigen/Core"

class ThermalConductionElement_Eigen : public ThermalConductionElement {
public:

	ThermalConductionElement_Eigen(Medium_Solid* medium, int numNodes)
	: ThermalConductionElement(medium, numNodes),
	  interactionCoefficients(numNodes, numNodes) {

	}

	virtual void setInteractionCoefficient(size_t row, size_t column, double value) {
		if (row >= nodes.size()) {
			RaiseError("Illegal row index " << row
					<< ", it must be in the interval [0 .. " << (nodes.size() - 1) << "]")
		}
		if (column >= nodes.size()) {
			RaiseError("Illegal column index " << column
					<< ", it must be in the interval [0 .. " << (nodes.size() - 1) << "]")
		}
		interactionCoefficients(row, column) = value;
	}

	virtual void computeExplicit() {
		double meanTemperature = 0;
		for (size_t i = 0; i < nodes.size(); i++) {
			meanTemperature += nodes[i]->getThermalState()->T();
		}
		meanTemperature /= nodes.size();
		internalState->update_Tp(meanTemperature, cst::StandardPressure);
		double lambda = internalState->lambda();
		for (size_t rowIndex = 0; rowIndex < nodes.size(); rowIndex++) {
			heatFlows[rowIndex] = 0;
			for (size_t colIndex = 0; colIndex < nodes.size(); colIndex++) {
				if (colIndex != rowIndex) {
					heatFlows[rowIndex] += lambda * interactionCoefficients(rowIndex, colIndex)
					* (nodes[colIndex]->getThermalState()->T() - nodes[rowIndex]->getThermalState()->T());
				}
			}
		}
	}
protected:
	Eigen::MatrixXd interactionCoefficients;
};

ThermalConductionElement* ThermalConductionElement_new(
		Medium_Solid* medium, int numNodes) {
	return new ThermalConductionElement_Eigen(medium, numNodes);
}

ThermalConductionElement* ThermalConductionElement_newLine(
		Medium_Solid* medium, double area, double length) {
	ThermalConductionElement* element = ThermalConductionElement_new(medium, 2);
	double coeff = area/length;
	element->setInteractionCoefficient(0, 0, -coeff);
	element->setInteractionCoefficient(0, 1, coeff);
	element->setInteractionCoefficient(1, 0, coeff);
	element->setInteractionCoefficient(1, 1, -coeff);
	return element;
}

void ThermalConductionElement_assignNode(
		ThermalConductionElement* element, size_t nodeIndex, ThermalNode* node) {
	element->assignNode(nodeIndex, node);
}

void ThermalConductionElement_setInteractionCoefficient(
		ThermalConductionElement* element, size_t row, size_t column, double value) {
	element->setInteractionCoefficient(row, column, value);
}

void ThermalConductionElement_computeExplicit(
		ThermalConductionElement* element) {
	element->computeExplicit();
}

double ThermalConductionElement_getHeatFlow(
		ThermalConductionElement* element, size_t nodeIndex) {
	return element->getHeatFlow(nodeIndex);
}

void ThermalConductionElement_getFlow(
		ThermalConductionElement* element, size_t nodeIndex, FluidFlow* flow) {
	element->getFlow(nodeIndex, flow);
}
