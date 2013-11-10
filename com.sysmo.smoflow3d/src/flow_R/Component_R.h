/*
 * Component_R.h
 *
 *  Created on: Jul 31, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#ifndef COMPONENT_R_H_
#define COMPONENT_R_H_

#include "util/CommonDefinitions.h"
#include "media/MediumState.h"
#include "flow/FlowBase.h"

#ifdef __cplusplus

class VirtualCapacity_R;

class Component_R : public SmoComponent {
public:
	Component_R();
	virtual ~Component_R();

	virtual void init(MediumState* state1, MediumState* state2);
	virtual bool compute(double massFlowRate, double minDownstreamPressure) = 0;
	void updateFlows(double massFlow);

	int getFlow1Index() {return flow1Index;}
	int getFlow2Index() {return flow2Index;}

	MediumState* getUpstreamState(double massFlowRate);
	MediumState* getDownstreamState(double massFlowRate);

	void addVirtualCapacity1(VirtualCapacity_R* virtualCapacity);
	void addVirtualCapacity2(VirtualCapacity_R* virtualCapacity);
	VirtualCapacity_R* getVirtualCapacity2() {return virtualCapacity2;}

	bool isFlowClosed(double massFlowRate);
	void closeFlow() {flagIsFlowOpen = false;}
	void openFlow() {flagIsFlowOpen = true;}

	bool isBidirectionalFlowAllowed() {return flagIsBidirectionalFlowAllowed;}
	void setIsBidirectionalFlowAllowed(bool isBidirectionalFlowAllowed) {this->flagIsBidirectionalFlowAllowed = isBidirectionalFlowAllowed;}

	double getAbsolutePressureDrop();

private:
	int flow1Index;
	int flow2Index;

	FluidFlow* flow1;
	FluidFlow* flow2;

	MediumState* state1;
	MediumState* state2;

	VirtualCapacity_R* virtualCapacity1;
	VirtualCapacity_R* virtualCapacity2;

	bool flagIsFlowOpen;
	bool flagIsBidirectionalFlowAllowed;
};

#else //_cplusplus
DECLARE_C_STRUCT(Component_R)
#endif //_cplusplus

BEGIN_C_LINKAGE
int Component_R_getFlow1Index(Component_R* component);
int Component_R_getFlow2Index(Component_R* component);

double Component_R_getAbsolutePressureDrop(Component_R* component);
END_C_LINKAGE

#endif /* COMPONENT_R_H_ */
