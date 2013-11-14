/*
 * FlowComponent_R.cpp
 *
 *  Created on: Jul 31, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "FlowComponent_R.h"

using namespace smoflow;

/**
 * Component_R - C++
 */
FlowComponent_R::FlowComponent_R() {
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

FlowComponent_R::~FlowComponent_R() {
}

void FlowComponent_R::init(MediumState* state1) {
	this->state1 = state1;
	state1Index = state1->instanceIndex;

	Medium* fluid = state1->getMedium();
	state2 = MediumState_new(fluid);
	state2Index = MediumState_register(state2);
	SMOOBJECT_SET_PARENT_COMPONENT(state2, this);
	state2->update_Tp(cst::StandardTemperature, cst::StandardPressure);
}

void FlowComponent_R::updateFlows(double massFlowRate) {
	flow1->massFlowRate = -massFlowRate;
	flow1->enthalpyFlowRate = flow1->massFlowRate * state1->h();

	flow2->massFlowRate = massFlowRate;
	flow2->enthalpyFlowRate = flow2->massFlowRate * state2->h();
}

MediumState* FlowComponent_R::getUpstreamState(double massFlowRate) {
	if (massFlowRate >= 0) {
		return state1;
	} else {
		return state2;
	}
}

MediumState* FlowComponent_R::getDownstreamState(double massFlowRate) {
	if (massFlowRate >= 0) {
		return state2;
	} else {
		return state1;
	}
}

bool FlowComponent_R::isFlowClosed(double massFlowRate) {
	if (flagIsFlowOpen == false) {
		return true;
	}

	if (massFlowRate < 0.0 && !isBidirectionalFlowAllowed()) {
		return true;
	}

	return false;
}

double FlowComponent_R::getAbsolutePressureDrop() {
	return m::fabs(state1->p() - state2->p());
}

/**
 * Component_R - C
 */
int Component_R_isFlowComponent(Component_R* component) {
	if (dynamic_cast<FlowComponent_R*>(component) != NULL) {
		return 1;
	} else {
		return 0;
	}
}

int FlowComponent_R_getFlow1Index(FlowComponent_R* component) {
	return component->getFlow1Index();
}

int FlowComponent_R_getFlow2Index(FlowComponent_R* component) {
	return component->getFlow2Index();
}

int FlowComponent_R_getState2Index(FlowComponent_R* component) {
	return component->getState2Index();
}

double FlowComponent_R_getAbsolutePressureDrop(FlowComponent_R* component) {
	return component->getAbsolutePressureDrop();
}
