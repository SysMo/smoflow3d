/*
 * ThermalNode.cpp
 *
 *  Created on: Aug 5, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "ThermalNode.h"
#include "util/CommonDefinitions.h"

using namespace smoflow;

/**
 * ThermalNode, ThermalSourceNode, ThermalMaterialNode - C++
 */
std::vector<ThermalNode*> ThermalNodeRegistry;

ThermalNode::ThermalNode(ThermalNodeType nodeType) :
	nodeType(nodeType) {
	temperature = 0.0;
}

void ThermalNode::setTemperature(double temperature) {
	this->temperature = temperature;
}

ThermalSourceNode::ThermalSourceNode() :
	ThermalNode(sThermalNode_Source) {

}

ThermalMaterialNode::ThermalMaterialNode() :
	ThermalNode(sThermalNode_Material) {
	totalHeatCapacity = 0.0;
	temperatureDerivative = 0.0;
}

void ThermalMaterialNode::addMaterialMass(Medium_Solid* medium, double mass) {
	size_t i = 0;
	// Check if a state with such a medium is already present
	for (i = 0; i < subnodeStates.size(); i++) {
		if (subnodeStates[i]->getMedium() == medium)
			subnodeMasses[i] += mass;
			break;
	}
	// If not, create a new state with this medium
	if (i == subnodeStates.size()) {
		MediumState_Solid* state = MediumStateSolid_new(medium);
		MediumState_register(state);
		SMOOBJECT_SET_PARENT(state, this);

		subnodeStates.push_back(state);
		subnodeMasses.push_back(mass);
	}
}

void ThermalMaterialNode::setTemperature(double temperature) {
	ThermalNode::setTemperature(temperature);
	for (size_t i = 0; i < subnodeStates.size(); i++) {
		subnodeStates[i]->update_Tp(temperature, cst::StandardPressure);
	}
}

void ThermalMaterialNode::compute(double heatFlow) {
	totalHeatCapacity = 0;
	for (size_t i = 0; i < subnodeStates.size(); i++) {
		totalHeatCapacity += subnodeMasses[i] * subnodeStates[i]->cp();
	}
	temperatureDerivative = heatFlow / totalHeatCapacity;
}

/**
 * ThermalNode, ThermalSourceNode, ThermalMaterialNode - C
 */
ThermalNode* ThermalNode_new(ThermalNodeType nodeType) {
	if (nodeType == sThermalNode_Source) {
		return new ThermalSourceNode();
	} else {
		return new ThermalMaterialNode();
	}
}

int ThermalNode_register(ThermalNode* node) {
	ThermalNodeRegistry.push_back(node);
	size_t instanceIndex = ThermalNodeRegistry.size();
	node->instanceIndex = instanceIndex;
	return instanceIndex;
}

ThermalNode* ThermalNode_get(int nodeIndex) {
	return ThermalNodeRegistry.at(nodeIndex - 1);
}

void ThermalNode_setTemperature(ThermalNode* node, double temperature) {
	node->setTemperature(temperature);
}

double ThermalNode_getTemperature(ThermalNode* node) {
	return node->getTemperature();
}

void ThermalMaterialNode_addMaterialMass(ThermalMaterialNode* node,
		Medium_Solid* medium, double mass) {
	node->addMaterialMass(medium, mass);
}
void ThermalMaterialNode_compute(ThermalMaterialNode* node, double heatFlow) {
	node->compute(heatFlow);
}

double ThermalMaterialNode_getTemperatureDerivative(ThermalMaterialNode* node) {
	return node->getTemperatureDerivative();
}

double ThermalMaterialNode_getTotalHeatCapacity(ThermalMaterialNode* node) {
	return node->getTotalHeatCapacity();
}

ThermalMaterialNode* ThermalMaterialNode_getFromState(MediumState* state) {
	ThermalMaterialNode* node = dynamic_cast<ThermalMaterialNode*>(state->parent);
	if (node == NULL) {
		RaiseError("The parent of the MediumState is not a thermal node");
	}
	return node;
}

MediumState* ThermalMaterialNode_getThermalState(ThermalMaterialNode* node, int subnodeIndex) {
	return node->getThermalState(subnodeIndex);
}
