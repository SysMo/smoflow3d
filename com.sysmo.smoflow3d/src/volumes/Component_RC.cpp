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

void Component_RC::initState(MediumState* port1State,
		ThermalNode* wallNode) {
	this->port1State = port1State;
	this->wallNode = wallNode;
	_createState();
	convectionLimitState = MediumState_new(port1State->getMedium());
	MediumState_register(convectionLimitState);
}



MediumState* getPort1State(Component_RC* component) {
	return component->getPort1State();
}

FluidFlow* getPort1Flow(Component_RC* component) {
	return component->getPort1Flow();
}

MediumState* getPort2State(Component_RC* component) {
	return component->getPort2State();
}

FluidFlow* getPort2Flow(Component_RC* component) {
	return component->getPort2Flow();
}

ThermalNode* getWallNode(Component_RC* component) {
	return component->getWallNode();
}

HeatFlow* getWallHeatFlow(Component_RC* component) {
	return component->getWallHeatFlow();
}
