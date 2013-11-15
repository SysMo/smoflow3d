/*
 * ManagerRComponents.h
 *
 *  Created on: Jul 31, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#ifndef MANAGERCOMPONENTS_R_H_
#define MANAGERCOMPONENTS_R_H_

#include "flow_R/Adaptor_R.h"
#include "flow_R/FlowComponent_R.h"

#ifdef __cplusplus

class ManagerComponents_R : public SmoObject {
public:
	ManagerComponents_R();
	virtual ~ManagerComponents_R();

	void addOuterState1(BeginAdaptor_R* beginAdaptor, int state1Index);
	void addOuterState2(EndAdaptor_R* endAdaptor, int state2Index);
	void addComponent(FlowComponent_R* component, int prevComponentID);
	void checkComponentOuterState2(EndAdaptor_R* endAdaptor, int componentMainState2ID);

	int getFlow1Index() {return componentOuterState1->getFlow1Index();}
	int getFlow2Index() {return componentOuterState2->getFlow2Index();}

	void compute();
	void clearIsComputed() {isComputed = false;}

	bool isFlowOpen() {return !isFlowClosed;}

private:
	double computeMassFlowRate();
	void updateFlows(double massFlowRate);

	void constructComponentsChain();
	inline int getNumComponents() {return (int) components.size();}

	double getAbsoluteOuterPressureDrop();
	bool checkIsFlowClosed(double massFlowRate);

private:
	std::vector<FlowComponent_R*> components;
	MediumState* outerState1;
	MediumState* outerState2;

	FlowComponent_R* componentOuterState1;
	FlowComponent_R* componentOuterState2;

	BeginAdaptor_R* beginAdaptor;
	EndAdaptor_R* endAdaptor;

	bool isComponentsChainContructed;
	bool isComputed;

	bool isFlowClosed;
	bool discFlag_isFlowClosed;

	double cache_massFlowRate;
	double cache_pressureDrop;
};

#else //_cplusplus
DECLARE_C_STRUCT(ManagerComponents_R)
#endif //_cplusplus

BEGIN_C_LINKAGE
ManagerComponents_R* ManagerComponents_R_new();
int ManagerComponents_R_register(ManagerComponents_R* manager);
ManagerComponents_R* ManagerComponents_R_get(int managerIndex);

void ManagerComponents_R_addOuterState1(ManagerComponents_R* manager, BeginAdaptor_R* beginAdaptor, int state1Index);
void ManagerComponents_R_addOuterState2(ManagerComponents_R* manager, int componentIndex);
void ManagerComponents_R_addComponent(ManagerComponents_R* manager, FlowComponent_R* component, int prevComponentID);
void ManagerComponents_R_checkComponentOuterState2(ManagerComponents_R* manager, EndAdaptor_R* endAdaptor, int componentOuterState2Index);

int ManagerComponents_R_getFlow1Index(ManagerComponents_R* manager);
int ManagerComponents_R_getFlow2Index(ManagerComponents_R* manager);

void ManagerComponents_R_compute(ManagerComponents_R* manager);
void ManagerComponents_R_clearIsComputed(ManagerComponents_R* manager);

int ManagerComponents_R_getIsFlowOpen(ManagerComponents_R* manager);
END_C_LINKAGE

#endif /* MANAGERCOMPONENTS_R_H_ */
