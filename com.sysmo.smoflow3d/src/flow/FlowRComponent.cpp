/*
 * FlowRComponent.cpp
 *
 *  Created on: Jul 31, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "FlowRComponent.h"

FlowRComponent::FlowRComponent() {
	// TODO Auto-generated constructor stub

}

FlowRComponent::~FlowRComponent() {
	// TODO Auto-generated destructor stub
}

void FlowRComponent::init(MediumState* state1, MediumState* state2) {
	if (state1->getMedium() != state2->getMedium()) {
		RaiseError("Different media connected to the flow component!");
	}
	this->state1 = state1;
	this->state2 = state2;
}
