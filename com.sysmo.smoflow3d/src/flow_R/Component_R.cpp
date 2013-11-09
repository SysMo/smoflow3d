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
	flagIsBidirectionalFlowAllowed = true;

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
	flow1->massFlowRate = -massFlowRate;
	flow1->enthalpyFlowRate = flow1->massFlowRate * state1->h();

	flow2->massFlowRate = massFlowRate;
	flow2->enthalpyFlowRate = flow2->massFlowRate * state2->h();
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

void Component_R::addVirtualCapacity1(VirtualCapacity_R* virtualCapacity) {
	if (virtualCapacity1 == NULL) {
		virtualCapacity1 = virtualCapacity;
		return;
	}

	RaiseComponentError(this, "Try to connect 'Virtual Capacity'-component to port1 of the 'R-Component' which already has other 'Virtual Capacity'-components on this port!");
}

void Component_R::addVirtualCapacity2(VirtualCapacity_R* virtualCapacity) {
	if (virtualCapacity2 == NULL) {
		virtualCapacity2 = virtualCapacity;
		return;
	}

	RaiseComponentError(this, "Try to connect 'Virtual Capacity'-component to port2 of the 'R-Component' which already has other 'Virtual Capacity'-components on this port!");
}

bool Component_R::isFlowClosed(double massFlowRate) {
	if (flagIsFlowOpen == false) {
		return true;
	}

	if (massFlowRate < 0.0 && !isBidirectionalFlowAllowed()) {
		return true;
	}

	return false;
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
