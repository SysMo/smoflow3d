/*
 * Component_R.cpp
 *
 *  Created on: Jul 31, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "Component_R.h"

using namespace smoflow;

/**
 * Component_R - C++
 */
Component_R::Component_R() {
	component1 = NULL;
	component2 = NULL;

	state1Index = -1;
	state2Index = -1;
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
}

Component_R::~Component_R() {
}

void Component_R::init(MediumState* state1) {
	this->state1 = state1;
	state1Index = state1->instanceIndex;

	Medium* fluid = state1->getMedium();
	state2 = MediumState_new(fluid);
	state2Index = MediumState_register(state2);
	SMOOBJECT_SET_PARENT_COMPONENT(state2, this);
	state2->update_Tp(cst::StandardTemperature, cst::StandardPressure);
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

bool Component_R::isFlowClosed(double massFlowRate) {
	if (flagIsFlowOpen == false) {
		return true;
	}

	if (massFlowRate < 0.0 && !isBidirectionalFlowAllowed()) {
		return true;
	}

	return false;
}

double Component_R::getAbsolutePressureDrop() {
	return m::fabs(state1->p() - state2->p());
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

int Component_R_getState2Index(Component_R* component) {
	return component->getState2Index();
}

double Component_R_getAbsolutePressureDrop(Component_R* component) {
	return component->getAbsolutePressureDrop();
}
