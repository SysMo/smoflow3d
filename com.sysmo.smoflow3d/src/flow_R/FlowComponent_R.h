/*
 * FlowComponent_R.h
 *
 *  Created on: Jul 31, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#ifndef FLOWCOMPONENT_R_H_
#define FLOWCOMPONENT_R_H_

#include "flow_R/Component_R.h"
#include "media/MediumState.h"
#include "flow/FlowBase.h"

#ifdef __cplusplus

class FlowComponent_R : public Component_R {
public:
	FlowComponent_R();
	virtual ~FlowComponent_R();

	virtual void init(MediumState* state1);
	virtual bool compute(double massFlowRate, double minDownstreamPressure) = 0;
	void updateFlows(double massFlow);

	int getFlow1Index() {return flow1Index;}
	int getFlow2Index() {return flow2Index;}

	int getState1Index() {return state1Index;}
	int getState2Index() {return state2Index;}

	MediumState* getState2() {return state2;}
	MediumState* getState1() {return state1;}

	MediumState* getUpstreamState(double massFlowRate);
	MediumState* getDownstreamState(double massFlowRate);

	FlowComponent_R* getComponent1() {return component1;}
	FlowComponent_R* getComponent2() {return component2;}

	void setComponent1(FlowComponent_R* component) {component1 = component;}
	void setComponent2(FlowComponent_R* component) {component2 = component;}

	bool isFlowClosed(double massFlowRate);
	void closeFlow() {flagIsFlowOpen = false;}
	void openFlow() {flagIsFlowOpen = true;}

	bool isBidirectionalFlowAllowed() {return flagIsBidirectionalFlowAllowed;}
	void setIsBidirectionalFlowAllowed(bool isBidirectionalFlowAllowed) {this->flagIsBidirectionalFlowAllowed = isBidirectionalFlowAllowed;}

	double getAbsolutePressureDrop();

protected:
	int flow1Index;
	int flow2Index;
	FluidFlow* flow1;
	FluidFlow* flow2;

	int state1Index;
	int state2Index;
	MediumState* state1;
	MediumState* state2;

	FlowComponent_R* component1;
	FlowComponent_R* component2;

	bool flagIsFlowOpen;
	bool flagIsBidirectionalFlowAllowed;
};

#else //_cplusplus
DECLARE_C_STRUCT(FlowComponent_R)
#endif //_cplusplus

BEGIN_C_LINKAGE
int Component_R_isFlowComponent(Component_R* component);

int FlowComponent_R_getFlow2Index(FlowComponent_R* component);
int FlowComponent_R_getState2Index(FlowComponent_R* component);

double FlowComponent_R_getAbsolutePressureDrop(FlowComponent_R* component);
END_C_LINKAGE

#endif /* FLOWCOMPONENT_R_H_ */
