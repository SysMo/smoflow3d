/*
 * Component_R.cpp
 *
 *  Created on: Jul 31, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "Component_R.h"
#include "flow_R/VirtualCapacity_R.h"

/**
 * Component_R - C++
 */
Component_R::Component_R() {
	state1 = NULL;
	state2 = NULL;

	flow1 = FluidFlow_new();
	flow1Index = FluidFlow_register(flow1);
	SMOOBJECT_SET_PARENT_COMPONENT(flow1, this);

	flow2 = FluidFlow_new();
	flow2Index = FluidFlow_register(flow2);
	SMOOBJECT_SET_PARENT_COMPONENT(flow2, this);

	flagIsFlowOpen = true;

	isComputed = false;

	virtualCapacity1 = NULL;
	virtualCapacity2 = NULL;
}

Component_R::~Component_R() {
}

void Component_R::init(MediumState* state1, MediumState* state2) {
	if (state1->getMedium() != state2->getMedium()) {
		RaiseComponentError(this, "Different media connected to the flow component!");
	}
	this->state1 = state1;
	this->state2 = state2;
}

void Component_R::updateFlows(double massFlowRate) {
	MediumState* upstreamState = getUpstreamState(massFlowRate);
	FluidFlow* upstreamFlow = getUpstreamFlow(massFlowRate);
	upstreamFlow->massFlowRate = -massFlowRate;
	upstreamFlow->enthalpyFlowRate = upstreamFlow->massFlowRate * upstreamState->h();

	MediumState* downstreamState = getDownstreamState(massFlowRate);
	FluidFlow* downstreamFlow = getDownstreamFlow(massFlowRate);
	downstreamFlow->massFlowRate = massFlowRate;
	downstreamFlow->enthalpyFlowRate = downstreamFlow->massFlowRate * downstreamState->h();
}

MediumState* Component_R::getUpstreamState(double massFlowRate) {
	if (massFlowRate >= 0) {
		return state1;
	} else {
		return state2;
	}
}

MediumState* Component_R::getDownstreamState(double massFlowRate) {
	if (massFlowRate >= 0) {
		return state2;
	} else {
		return state1;
	}
}

FluidFlow* Component_R::getUpstreamFlow(double massFlowRate) {
	if (massFlowRate >= 0) {
		return flow1;
	} else {
		return flow2;
	}
}

FluidFlow* Component_R::getDownstreamFlow(double massFlowRate) {
	if (massFlowRate >= 0) {
		return flow2;
	} else {
		return flow1;
	}
}

void Component_R::addVirtualCapacity(VirtualCapacity_R* virtualCapacity) {
	if (virtualCapacity1 == NULL) {
		virtualCapacity1 = virtualCapacity;
		return;
	}

	if (virtualCapacity2 == NULL) {
		virtualCapacity2 = virtualCapacity;
		return;
	}

	RaiseComponentError(this, "Try to connect 'Virtual Capacity'-component to 'R-Component' which already has two 'Virtual Capacity'-components connected to it!");
}

VirtualCapacity_R* Component_R::getOtherVirtualCapacity(VirtualCapacity_R* virtualCapacity) {
	if (virtualCapacity1 == virtualCapacity) {
		return virtualCapacity2;
	}

	if (virtualCapacity2 == virtualCapacity) {
			return virtualCapacity1;
	}

	return NULL;
}

/**
 * Component_R - C
 */
int Component_R_getFlow1Index(Component_R* component) {
	return component->getFlow1Index();
}

int Component_R_getFlow2Index(Component_R* component) {
	return component->getFlow2Index();
}
