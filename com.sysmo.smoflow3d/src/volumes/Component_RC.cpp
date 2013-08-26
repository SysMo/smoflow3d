/*
 * RCComponent.cpp
 *
 *  Created on: Aug 23, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "Component_RC.h"

Component_RC::Component_RC() {

}

Component_RC::~Component_RC() {
}

void Component_RC::init(FluidFlow* port2Flow) {
	this->port2Flow = port2Flow;
	this->port1Flow = FluidFlow_new();
	FluidFlow_register(this->port1Flow);
	this->wallHeatFlow = HeatFlow_new();
	HeatFlow_register(this->wallHeatFlow);
	_init();
}

void Component_RC::createState(MediumState* port1State,
		ThermalNode* wallNode) {
	this->port1State = port1State;
	this->wallNode = wallNode;
	_createState();
}

MediumState* Component_RC_getPort1State(Component_RC* component) {
	return component->getPort1State();
}

FluidFlow* Component_RC_getPort1Flow(Component_RC* component) {
	return component->getPort1Flow();
}

MediumState* Component_RC_getPort2State(Component_RC* component) {
	return component->getPort2State();
}

FluidFlow* Component_RC_getPort2Flow(Component_RC* component) {
	return component->getPort2Flow();
}

ThermalNode* Component_RC_getWallNode(Component_RC* component) {
	return component->getWallNode();
}

HeatFlow* Component_RC_getWallHeatFlow(Component_RC* component) {
	return component->getWallHeatFlow();
}

void Component_RC_init(Component_RC* component, FluidFlow* port2Flow) {
	component->init(port2Flow);
}
void Component_RC_initState(Component_RC* component,
		MediumState* port1State, ThermalNode* wallNode) {
	component->createState(port1State, wallNode);
}

void Component_RC_setStateValues(Component_RC* component,
		double value1, double value2) {
	component->setStateValues(value1, value2);
}

void Component_RC_getStateValues(Component_RC* component,
		double* value1, double* value2) {
	component->getStateValues(value1, value2);
}

void Component_RC_getStateDerivatives(Component_RC* component,
		double* value1, double* value2) {
	component->getStateDerivatives(value1, value2);
}

void Component_RC_compute(Component_RC* component) {
	component->compute();
}