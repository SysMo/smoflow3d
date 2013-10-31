/*
 * Component_RC.h
 *
 *  Created on: Aug 23, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#ifndef COMPONENT_RC_H_
#define COMPONENT_RC_H_

#include "volumes/FluidChamber.h"
#include "flow/ForcedConvection.h"
#include "flow/FrictionFlowPipe.h"

#ifdef __cplusplus

class Component_RC : public SmoComponent {
public:
	Component_RC();
	virtual ~Component_RC();

	virtual void init(FluidFlow* port2Flow);
	virtual void initStates(MediumState* port1State, ThermalNode* wallNode,
			StateVariableSet& innerStateInitializer);

	virtual void compute() = 0;

	MediumState* getPort1State() {return port1State;}
	FluidFlow* getPort1Flow() {return port1Flow;}
	MediumState* getPort2State() {return port2State;}
	FluidFlow* getPort2Flow() {return port2Flow;}
	ThermalNode* getWallNode() {return wallNode;}
	HeatFlow* getWallHeatFlow() {return wallHeatFlow;}

protected:
	// Port 1 (fluid)
	MediumState* port1State; 	// input
	FluidFlow* port1Flow;		// output

	// Port 2 (fluid)
	MediumState* port2State; 	// output
	FluidFlow* port2Flow;		// input

	// Port 3 (thermal)
	ThermalNode* wallNode;		// input
	HeatFlow* wallHeatFlow;		// output
};

#else //__cplusplus
DECLARE_C_STRUCT(Component_RC)
#endif //__cplusplus

BEGIN_C_LINKAGE
void Component_RC_init(Component_RC* component, FluidFlow* port2Flow);
void Component_RC_initStates(Component_RC* component, MediumState* port1State,
		ThermalNode* wallNode, StateVariableSet innerStateInitializer);

void Component_RC_compute(Component_RC* component);

MediumState* Component_RC_getPort1State(Component_RC* component);
FluidFlow* Component_RC_getPort1Flow(Component_RC* component);
MediumState* Component_RC_getPort2State(Component_RC* component);
FluidFlow* Component_RC_getPort2Flow(Component_RC* component);
ThermalNode* Component_RC_getWallNode(Component_RC* component);
HeatFlow* Component_RC_getWallHeatFlow(Component_RC* component);
END_C_LINKAGE

#endif /* COMPONENT_RC_H_ */
