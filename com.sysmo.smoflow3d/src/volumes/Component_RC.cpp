/*
 * RCComponent.cpp
 *
 *  Created on: Aug 23, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "Component_RC.h"

/**
 * Component_RC - C++
 */
Component_RC::Component_RC() {
	port1State = NULL;
	port1Flow = NULL;
	port2State = NULL;
	port2Flow = NULL;
	wallNode = NULL;
	wallHeatFlow = NULL;
}

Component_RC::~Component_RC() {
}

void Component_RC::init(FluidFlow* port2Flow) {
	this->port2Flow = port2Flow;

	this->port1Flow = FluidFlow_new();
	FluidFlow_register(this->port1Flow);

	this->wallHeatFlow = HeatFlow_new();
	HeatFlow_register(this->wallHeatFlow);
}

void Component_RC::initStates(MediumState* port1State, ThermalNode* wallNode,
		StateVariableSet& innerStateInitializer) {
	this->port1State = port1State;
	this->wallNode = wallNode;
}

/**
 * Component_RC - C
 */
void Component_RC_init(Component_RC* component, FluidFlow* port2Flow) {
	component->init(port2Flow);
}

void Component_RC_initStates(Component_RC* component, MediumState* port1State,
		ThermalNode* wallNode, StateVariableSet innerStateInitializer) {
	component->initStates(port1State, wallNode, innerStateInitializer);
}

void Component_RC_compute(Component_RC* component) {
	component->compute();
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
