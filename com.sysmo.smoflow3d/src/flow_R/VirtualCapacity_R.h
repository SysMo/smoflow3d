/*
 * VirtualCapacity_R.h
 *
 *  Created on: Jul 31, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#ifndef VIRTUALCAPACITY_R_H
#define VIRTUALCAPACITY_R_H

#include "util/CommonDefinitions.h"
#include "media/MediumState.h"
#include "flow/FlowBase.h"
#include "flow_R/Component_R.h"

#ifdef __cplusplus

class VirtualCapacity_R : public SmoComponent {
public:
	VirtualCapacity_R(Medium* fluid);
	virtual ~VirtualCapacity_R();

	MediumState* getState() {return state;}
	int getStateIndex() {return stateIndex;}

	void addComponent(Component_R* component_R);
	Component_R* getOtherComponent(Component_R* component_R);

private:
	MediumState* state;
	int stateIndex;

	Component_R* component1;
	Component_R* component2;
};

#else //_cplusplus
DECLARE_C_STRUCT(VirtualCapacity_R)
#endif //_cplusplus

BEGIN_C_LINKAGE
VirtualCapacity_R* VirtualCapacity_R_new(Medium* fluid);

MediumState* VirtualCapacity_R_getState(VirtualCapacity_R* virtualCapacity);
int VirtualCapacity_R_getStateIndex(VirtualCapacity_R* virtualCapacity);
END_C_LINKAGE

#endif /* VIRTUALCAPACITY_R_H */
