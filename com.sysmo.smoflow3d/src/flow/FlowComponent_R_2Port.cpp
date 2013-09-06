/*
 * FlowComponent_R_2Port.cpp
 *
 *  Created on: Jul 31, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "FlowComponent_R_2Port.h"

FlowComponent_R_2Port::FlowComponent_R_2Port() {
}

FlowComponent_R_2Port::~FlowComponent_R_2Port() {
}

void FlowComponent_R_2Port::init(MediumState* state1, MediumState* state2) {
	if (state1->getMedium() != state2->getMedium()) {
		RaiseError("Different media connected to the flow component!");
	}
	this->state1 = state1;
	this->state2 = state2;
}
