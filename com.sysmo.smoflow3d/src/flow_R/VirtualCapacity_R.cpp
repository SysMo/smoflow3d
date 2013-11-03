/*
 * VirtualCapacity_C.cpp
 *
 *  Created on: Jul 31, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "VirtualCapacity_R.h"

using namespace smoflow;

/**
 * VirtualCapacity_C - C++
 */
VirtualCapacity_R::VirtualCapacity_R(Medium* fluid) {
	state = MediumState_new(fluid);
	stateIndex = MediumState_register(state);
	SMOOBJECT_SET_PARENT_COMPONENT(state, this);

	state->update_Tp(cst::StandardTemperature, cst::StandardPressure);

	component1 = NULL;
	component2 = NULL;
}

VirtualCapacity_R::~VirtualCapacity_R() {
}

void VirtualCapacity_R::addComponent(Component_R* component_R) {
	if (component1 == NULL) {
		component1 = component_R;
		return;
	}

	if (component2 == NULL) {
		component2 = component_R;
		return;
	}

	RaiseComponentError(this, "Try to connect 'R-Component' to 'Virtual Capacity'-component which already has two 'R-components' connected to it!");
}

Component_R* VirtualCapacity_R::getOtherComponent(Component_R* component_R) {
	if (component1 == component_R) {
		return component2;
	}

	if (component2 == component_R) {
			return component1;
	}

	return NULL;
}



/**
 * VirtualCapacity_C - C
 */
VirtualCapacity_R* VirtualCapacity_R_new(Medium* fluid) {
	return new VirtualCapacity_R(fluid);
}

MediumState* VirtualCapacity_R_getState(VirtualCapacity_R* virtualCapacity) {
	return virtualCapacity->getState();
}

int VirtualCapacity_R_getStateIndex(VirtualCapacity_R* virtualCapacity) {
	return virtualCapacity->getStateIndex();
}
