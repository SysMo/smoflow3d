/*
 * ThermalConduction2Node.cpp
 *
 *  Created on: Dec 13, 2018
 *      Author: Milen Borisov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "ThermalConduction2Node.h"

using namespace smoflow;

/**
 * ThermalConduction2Node - C++
 */
ThermalConduction2Node::ThermalConduction2Node() {
	node1 = NULL;
	node2 = NULL;
	heatFlowRate1 = 0;
	heatFlowRate2 = 0;
}

ThermalConduction2Node::~ThermalConduction2Node() {
}

void ThermalConduction2Node::init(ThermalNode* node1, ThermalNode* node2) {
	this->node1 = node1;
	this->node2 = node2;
}

double ThermalConduction2Node::getHeatFlowRate1() {
	return heatFlowRate1;
}

double ThermalConduction2Node::getHeatFlowRate2() {
	return heatFlowRate2;
}

void ThermalConduction2Node::updateHeatFlow1(HeatFlow* flow) {
	flow->enthalpyFlowRate = getHeatFlowRate1();
}

void ThermalConduction2Node::updateHeatFlow2(HeatFlow* flow) {
	flow->enthalpyFlowRate = getHeatFlowRate2();
}

/*************************************************************
 ***  Conduction models
 *************************************************************/
class ThermalConduction2Node_Linear : public ThermalConduction2Node {
public:
	ThermalConduction2Node_Linear(
			Medium_Solid* medium, double area, double length) {
		internalState = MediumState_new(medium);
		MediumState_register(internalState);
		this->area = area;
		this->length = length;
	}

	virtual void compute() {
		double T1 = node1->getTemperature();
		double T2 = node2->getTemperature();
		double meanTemperature = (T1+T2)/2;
		internalState->update_Tp(meanTemperature, cst::StandardPressure);

		heatFlowRate1 = internalState->lambda() * area * (T2-T1) / length;
		heatFlowRate2 = -heatFlowRate1;
	}

protected:
	MediumState* internalState;
	double area;
	double length;
};

class ThermalConduction2Node_2Material : public ThermalConduction2Node {
public:
	ThermalConduction2Node_2Material(
			Medium_Solid* medium1, Medium_Solid* medium2,
			double area, double length1, double length2,
			double contactResistance) {
		internalState1 = MediumState_new(medium1);
		MediumState_register(internalState1);
		internalState2 = MediumState_new(medium2);
		MediumState_register(internalState2);
		this->area = area;
		this->length1 = length1;
		this->length2 = length2;
		this->contactResistance = contactResistance;
	}

	virtual void compute() {
		double T1 = node1->getTemperature();
		internalState1->update_Tp(T1, cst::StandardPressure);
		double T2 = node2->getTemperature();
		internalState2->update_Tp(T2, cst::StandardPressure);

		heatFlowRate1 = (T2-T1)/ (
				length1/(internalState1->lambda() * area) +
				length2/(internalState2->lambda() * area) +
				contactResistance/area);
		heatFlowRate2 = -heatFlowRate1;
	}

protected:
	MediumState* internalState1;
	MediumState* internalState2;
	double area;
	double length1;
	double length2;
	double contactResistance;
};

/**
 * ThermalConduction2Node - C
 */

ThermalConduction2Node* ThermalConduction2Node_Linear_new(
		Medium_Solid* medium, double area, double length) {
	return new ThermalConduction2Node_Linear(
			medium, area, length);
}

ThermalConduction2Node* ThermalConduction2Node_2Material_new(
		Medium_Solid* medium1, Medium_Solid* medium2,
		double area, double length1, double length2,
		double contactResistance) {
	return new ThermalConduction2Node_2Material(
			medium1, medium2, area, length1, length2, contactResistance);
}

void ThermalConduction2Node_init(
		ThermalConduction2Node* conduction, ThermalNode* node1, ThermalNode* node2) {
	conduction->init(node1, node2);
}

void ThermalConduction2Node_compute(
		ThermalConduction2Node* conduction) {
	conduction->compute();
}

double ThermalConduction2Node_getHeatFlowRate1(
		ThermalConduction2Node* conduction) {
	return conduction->getHeatFlowRate1();
}

double ThermalConduction2Node_getHeatFlowRate2(
		ThermalConduction2Node* conduction) {
	return conduction->getHeatFlowRate2();
}

void ThermalConduction2Node_updateHeatFlow1(
		ThermalConduction2Node* conduction, HeatFlow* flow) {
	conduction->updateHeatFlow1(flow);
}

void ThermalConduction2Node_updateHeatFlow2(
		ThermalConduction2Node* conduction, HeatFlow* flow) {
	conduction->updateHeatFlow2(flow);
}
