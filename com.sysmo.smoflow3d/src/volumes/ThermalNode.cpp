/*
 * ThermalNode.cpp
 *
 *  Created on: Aug 5, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "ThermalNode.h"

std::vector<ThermalNode*> ThermalNodeRegistry;

ThermalNode::ThermalNode() {
}

ThermalNode::~ThermalNode() {
}

void ThermalNode::addMaterialMass(Medium_Solid* medium, double mass) {
	size_t i = 0;
	// Check if a state with such a medium is already present
	for (i = 0; i < subnodeStates.size(); i++) {
		if (subnodeStates[i]->getMedium() == medium)
			subnodeMasses[i] += mass;
			break;
	}
	// If not, create a new state with this medium
	if (i == subnodeStates.size()) {
		MediumStateSolid* state = MediumStateSolid_new(medium);
		MediumState_register(state);
		state->parent = this;
		subnodeStates.push_back(state);
		subnodeMasses.push_back(mass);
	}
}

void ThermalNode::setTemperature(double temperature) {
	for (size_t i = 0; i < subnodeStates.size(); i++) {
		subnodeStates[i]->update_Tp(temperature, cst::StandardPressure);
	}
}

void ThermalNode::compute(double heatFlow) {
	totalHeatCapacity = 0;
	for (size_t i = 0; i < subnodeStates.size(); i++) {
		totalHeatCapacity += subnodeMasses[i] * subnodeStates[i]->cp();
	}
	temperatureDerivative = heatFlow / totalHeatCapacity;
}

ThermalNode* ThermalNode_new() {
	ThermalNode* node = new ThermalNode();
	ThermalNodeRegistry.push_back(node);
	return node;
}

ThermalNode* ThermalNode_getFromState(MediumStateSolid* state) {
	ThermalNode* node = dynamic_cast<ThermalNode*>(state->parent);
	if (node == NULL) {
		RaiseError("The parent of the MediumStateSolid is not a thermal node");
	}
	return node;
}

void ThermalNode_addMaterialMass(ThermalNode* node, Medium_Solid* medium, double mass) {
	node->addMaterialMass(medium, mass);
}

void ThermalNode_setTemperature(ThermalNode* node, double temperature) {
	node->setTemperature(temperature);
}

void ThermalNode_compute(ThermalNode* node, double heatFlow) {
	node->compute(heatFlow);
}

double ThermalNode_getTemperatureDerivative(ThermalNode* node) {
	return node->getTemperatureDerivative();
}

double ThermalNode_getTotalHeatCapacity(ThermalNode* node) {
	return node->getTotalHeatCapacity();
}

MediumState* getThermalState(ThermalNode* node, int subnodeIndex) {
	return node->getThermalState(subnodeIndex);
}
