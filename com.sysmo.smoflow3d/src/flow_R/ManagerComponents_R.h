/*
 * ManagerRComponents.h
 *
 *  Created on: Jul 31, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#ifndef MANAGERCOMPONENTS_R_H_
#define MANAGERCOMPONENTS_R_H_

#include "flow_R/Component_R.h"
#include "flow_R/VirtualCapacity_R.h"

#ifdef __cplusplus

class ManagerComponents_R {
public:
	ManagerComponents_R();
	virtual ~ManagerComponents_R();

	void add(Component_R* component_R, int state1Index, int state2Index);
	void compute(Component_R* component_R);

private:
	double computeMassFlowRate();
	void updateFlows(double massFlowRate);
	bool areAllComponentsComputed();
	void setAllComponentsNoComputed();

	void connectVirtualCapacityAndComponent(VirtualCapacity_R* virtualCapacity, Component_R* component_R);
	void addMainState(MediumState* state, Component_R* component_R);
	void constructComponentsChain();

	inline int getNumComponents() {return (int) components.size();}

	bool hasVirtualCapacityParent(MediumState* state);
	VirtualCapacity_R* getVirtualCapacityParent(MediumState* state);

private:
	std::vector<Component_R*> components;
	MediumState* mainState1;
	MediumState* mainState2;

	Component_R* componentMainState1;
	Component_R* componentMainState2;
	bool isComponentsChainContructed;

	double cache_massFlowRate;
};

#else //_cplusplus
DECLARE_C_STRUCT(ManagerComponents_R)
#endif //_cplusplus

BEGIN_C_LINKAGE
void ManagerComponents_R_add(Component_R* component_R, int state1Index, int state2Index);
void ManagerComponents_R_compute(Component_R* component_R);
END_C_LINKAGE

#endif /* MANAGERCOMPONENTS_R_H_ */
