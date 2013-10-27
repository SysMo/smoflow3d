/*
 * Component_R.cpp
 *
 *  Created on: Jul 31, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "Component_R.h"

/**
 * Component_R - C++
 */
Component_R::Component_R() {
	state1 = NULL;
	state2 = NULL;
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
