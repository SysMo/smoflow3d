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

	MediumState* getState1() {return state1;}
	MediumState* getState2() {return state1;}

	MediumState* getUpstreamState(double massFlowRate);
	MediumState* getDownstreamState(double massFlowRate);

	FluidFlow* getUpstreamFlow(double massFlowRate);
	FluidFlow* getDownstreamFlow(double massFlowRate);

	int getFlow1Index() {return flow1Index;}
	int getFlow2Index() {return flow2Index;}

	virtual bool isFlowClosed(double massFlowRate) {return !flagIsFlowOpen;}
	void closeFlow() {flagIsFlowOpen = false;}
	void openFlow() {flagIsFlowOpen = true;}

	void addVirtualCapacity(VirtualCapacity_R* virtualCapacity);
	VirtualCapacity_R* getOtherVirtualCapacity(VirtualCapacity_R* virtualCapacity);

public: //computational properties
	bool isComputed;

private:
	FluidFlow* flow1;
	int flow1Index;
	FluidFlow* flow2;
	int flow2Index;

	MediumState* state1;
	MediumState* state2;

	bool flagIsFlowOpen;

	VirtualCapacity_R* virtualCapacity1;
	VirtualCapacity_R* virtualCapacity2;
};

#else //_cplusplus
DECLARE_C_STRUCT(Component_R)
#endif //_cplusplus

BEGIN_C_LINKAGE
int Component_R_getFlow1Index(Component_R* component);
int Component_R_getFlow2Index(Component_R* component);
END_C_LINKAGE

#endif /* COMPONENT_R_H_ */
