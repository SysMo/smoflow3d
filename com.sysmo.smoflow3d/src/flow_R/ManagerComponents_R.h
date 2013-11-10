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
#include "flow_R/Component_R.h"
#include "flow_R/VirtualCapacity_R.h"
#include "flow_R/Adaptor_R.h"

#ifdef __cplusplus

class ManagerComponents_R : public SmoObject {
public:
	ManagerComponents_R();
	virtual ~ManagerComponents_R();

	void addMainState1(BeginAdaptor_R* beginAdaptor, int state1Index);
	void addMainState2(EndAdaptor_R* endAdaptor, int state2Index);
	void addComponent(Component_R* component_R, int state1Index);
	void addVirtualCapacity(VirtualCapacity_R* virtualCapacity, int flow1Index);
	void addComponentMainState2(EndAdaptor_R* endAdaptor, int flow1Index);

	void compute();

private:
	double computeMassFlowRate();
	void updateFlows(double massFlowRate);

	void constructComponentsChain();

	VirtualCapacity_R* getParent_VirtualCapacity(MediumState* state);
	Component_R* getParent_Component(FluidFlow* flow);

	inline int getNumComponents() {return (int) components.size();}

private:
	std::vector<Component_R*> components;
	MediumState* mainState1;
	MediumState* mainState2;

	Component_R* componentMainState1;
	Component_R* componentMainState2;

	BeginAdaptor_R* beginAdaptor;
	EndAdaptor_R* endAdaptor;

	bool isComponentsChainContructed;

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
void ManagerComponents_R_addComponent(ManagerComponents_R* manager, Component_R* component_R, int state1Index);
void ManagerComponents_R_addVirtualCapacity(ManagerComponents_R* manager, VirtualCapacity_R* virtualCapacity, int flow1Index);
void ManagerComponents_R_addComponentMainState2(ManagerComponents_R* manager, EndAdaptor_R* endAdaptor, int flow1Index);

void ManagerComponents_R_compute(ManagerComponents_R* manager, EndAdaptor_R* endAdaptor);
END_C_LINKAGE

#endif /* MANAGERCOMPONENTS_R_H_ */
