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

	void addMainState1(BeginAdaptor_R* beginAdaptor, int state1Index);
	void addMainState2(EndAdaptor_R* endAdaptor, int state2Index);
	void addComponent(FlowComponent_R* component, int prevComponentID);
	void setComponentMainState2(EndAdaptor_R* endAdaptor, int componentMainState2ID);

	int getFlow1Index() {return componentMainState1->getFlow1Index();}
	int getFlow2Index() {return componentMainState2->getFlow2Index();}

	void compute();
	void clearIsComputed() {isComputed = false;}

private:
	double computeMassFlowRate();
	void updateFlows(double massFlowRate);

	void constructComponentsChain();
	inline int getNumComponents() {return (int) components.size();}

private:
	std::vector<FlowComponent_R*> components;
	MediumState* mainState1;
	MediumState* mainState2;

	FlowComponent_R* componentMainState1;
	FlowComponent_R* componentMainState2;

	BeginAdaptor_R* beginAdaptor;
	EndAdaptor_R* endAdaptor;

	bool isComponentsChainContructed;
	bool isComputed;

	double cache_massFlowRate;
};

#else //_cplusplus
DECLARE_C_STRUCT(ManagerComponents_R)
#endif //_cplusplus

BEGIN_C_LINKAGE
ManagerComponents_R* ManagerComponents_R_new();
int ManagerComponents_R_register(ManagerComponents_R* manager);
ManagerComponents_R* ManagerComponents_R_get(int managerIndex);

void ManagerComponents_R_addMainState1(ManagerComponents_R* manager, BeginAdaptor_R* beginAdaptor, int state1Index);
void ManagerComponents_R_addMainState2(ManagerComponents_R* manager, EndAdaptor_R* endAdaptor, int state2Index);
void ManagerComponents_R_addComponent(ManagerComponents_R* manager, FlowComponent_R* component, int prevComponentID);
void ManagerComponents_R_setComponentMainState2(ManagerComponents_R* manager, EndAdaptor_R* endAdaptor, int state1Index);

int ManagerComponents_R_getFlow1Index(ManagerComponents_R* manager);
int ManagerComponents_R_getFlow2Index(ManagerComponents_R* manager);

void ManagerComponents_R_compute(ManagerComponents_R* manager);
void ManagerComponents_R_clearIsComputed(ManagerComponents_R* manager);
END_C_LINKAGE

#endif /* MANAGERCOMPONENTS_R_H_ */
