/*
 * ThermalConductionElement.cpp
 *
 *  Created on: Aug 5, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "ThermalConductionElement.h"

ThermalConductionElement::ThermalConductionElement(Medium* medium, int numNodes)
: nodes(numNodes), heatFlows(numNodes), interactionCoefficients(numNodes, numNodes) {
	internalState = MediumState_new(medium);
	MediumState_register(internalState);
}

ThermalConductionElement::~ThermalConductionElement() {
}

void ThermalConductionElement::assignNode(size_t nodeIndex, ThermalNode* node) {
	if (nodeIndex > nodes.size()) {
		RaiseError("Illegal node index " << nodeIndex
				<< ", it must be in the interval [1 .. "
				<< nodes.size() << "]")
	}
	nodes[nodeIndex - 1] = node;
}

void ThermalConductionElement::setInteractionCoefficient(size_t row, size_t column, double value) {
	if (row > nodes.size()) {
		RaiseError("Illegal row index " << row
				<< ", it must be in the interval [1 .. " << nodes.size() << "]")
	}
	if (column > nodes.size()) {
		RaiseError("Illegal column index " << column
				<< ", it must be in the interval [1 .. " << nodes.size() << "]")
	}
	interactionCoefficients(row - 1, column - 1) = value;
}

void ThermalConductionElement::computeExplicit() {
	double meanTemperature = 0;
	for (size_t i = 0; i < nodes.size(); i++) {
		meanTemperature += nodes[i]->getTemperature();
	}
	meanTemperature /= nodes.size();
	internalState->update_Tp(meanTemperature, cst::StandardPressure);
	double lambda = internalState->lambda();
	for (size_t rowIndex = 0; rowIndex < nodes.size(); rowIndex++) {
		heatFlows[rowIndex] = 0;
		for (size_t colIndex = 0; colIndex < nodes.size(); colIndex++) {
			if (colIndex != rowIndex) {
				heatFlows[rowIndex] += lambda
						* interactionCoefficients(rowIndex, colIndex)
						* (nodes[colIndex]->getTemperature()
								- nodes[rowIndex]->getTemperature());
			}
		}
	}
}

double ThermalConductionElement::getHeatFlow(size_t nodeIndex) {
	return heatFlows.at(nodeIndex - 1);
}

void ThermalConductionElement::getFlow(size_t nodeIndex, HeatFlow* flow) {
	flow->enthalpyFlowRate = getHeatFlow(nodeIndex);
}

ThermalConductionElement* ThermalConductionElement_new(
		Medium* medium, int numNodes) {
	return new ThermalConductionElement(medium, numNodes);
}

ThermalConductionElement* ThermalConductionElement_Line_new(
		Medium_Solid* medium, double area, double length) {
	ThermalConductionElement* element = ThermalConductionElement_new(medium, 2);
	double coeff = area/length;
	element->setInteractionCoefficient(1, 1, -coeff);
	element->setInteractionCoefficient(1, 2, coeff);
	element->setInteractionCoefficient(2, 1, coeff);
	element->setInteractionCoefficient(2, 2, -coeff);
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
