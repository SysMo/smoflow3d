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

void VirtualCapacity_R::addComponent1(Component_R* component_R) {
	if (component1 == NULL) {
		component1 = component_R;
		return;
	}

	RaiseComponentError(this, "Try to connect 'R-Component' to port1 of the 'Virtual Capacity'-component which already has other 'R-components' on this port!");
}

void VirtualCapacity_R::addComponent2(Component_R* component_R) {
	if (component2 == NULL) {
		component2 = component_R;
		return;
	}

	RaiseComponentError(this, "Try to connect 'R-Component' to port2 of the 'Virtual Capacity'-component which already has other 'R-components' on this port!");
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
