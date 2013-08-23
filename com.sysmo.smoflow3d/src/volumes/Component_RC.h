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

class Component_RC {
public:
	Component_RC();
	virtual ~Component_RC();
	void init(FluidFlow* port2Flow);
	void initState(MediumState* port1State,
			ThermalNode* wallNode);
	virtual void compute() = 0;

	MediumState* getPort1State() {return port1State;}
	FluidFlow* getPort1Flow() {return port1Flow;}
	MediumState* getPort2State() {return port2State;}
	FluidFlow* getPort2Flow() {return port2Flow;}
	ThermalNode* getWallNode() {return wallNode;}
	HeatFlow* getWallHeatFlow() {return wallHeatFlow;}

protected:
	virtual void _init() = 0;
	virtual void _createState() = 0;
	// Port 1 (fluid)
	MediumState* port1State; 	// input
	FluidFlow* port1Flow;		// output
	// Port 2 (fluid)
	MediumState* port2State; 	// output
	FluidFlow* port2Flow;		// input
	// Port 3 (thermal)
	ThermalNode* wallNode;		// input
	HeatFlow* wallHeatFlow;		// output

	// internals
	MediumState* convectionLimitState;

};

#else //__cplusplus
DECLARE_C_STRUCT(Component_RC)
#endif //__cplusplus

BEGIN_C_LINKAGE
MediumState* getPort1State(Component_RC* component);
FluidFlow* getPort1Flow(Component_RC* component);
MediumState* getPort2State(Component_RC* component);
FluidFlow* getPort2Flow(Component_RC* component);
ThermalNode* getWallNode(Component_RC* component);
HeatFlow* getWallHeatFlow(Component_RC* component);
END_C_LINKAGE

#endif /* COMPONENT_RC_H_ */
