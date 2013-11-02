/*
 * PipeHeatExchPrDropRC.h
 *
 *  Created on: Aug 23, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#ifndef PIPEHEATEXCHPRDROPRC_H_
#define PIPEHEATEXCHPRDROPRC_H_

#include "volumes/FluidChamber.h"
#include "flow/ForcedConvection.h"
#include "flow/FrictionFlowPipe.h"

#ifdef __cplusplus

class PipeHeatExchPrDrop_RC : public SmoComponent {
public:
	PipeHeatExchPrDrop_RC(double internalVolume, FrictionFlowPipe* friction, ForcedConvection* convection);
	virtual ~PipeHeatExchPrDrop_RC();

	void init(FluidFlow* port2Flow);
	void initStates(MediumState* port1State, ThermalNode* wallNode, StateVariableSet& innerStateInitializer);
	void compute();

	void setStateValues(double value1, double value2);
	void getStateValues(double* value1, double* value2);
	void getStateDerivatives(double* value1, double* value2);

	FluidFlow* getPort1Flow() {return port1Flow;}
	MediumState* getPort2State() {return port2State;}
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


	// Parameters
	double volume;
	ForcedConvection* convection;
	FrictionFlowPipe* friction;

	// Internals
	FluidChamber* accFluid;
	FluidFlow* internalFlow;
};

#else //__cplusplus
DECLARE_C_STRUCT(PipeHeatExchPrDrop_RC)
#endif //__cplusplus

BEGIN_C_LINKAGE
PipeHeatExchPrDrop_RC* PipeHeatExchPrDrop_RC_new(double internalVolume, FrictionFlowPipe* friction, ForcedConvection* convection);

void PipeHeatExchPrDrop_RC_init(PipeHeatExchPrDrop_RC* pipe, FluidFlow* port2Flow);
void PipeHeatExchPrDrop_RC_initStates(PipeHeatExchPrDrop_RC* pipe, MediumState* port1State, ThermalNode* wallNode, StateVariableSet innerStateInitializer);
void PipeHeatExchPrDrop_RC_compute(PipeHeatExchPrDrop_RC* pipe);

void PipeHeatExchPrDrop_RC_setStateValues(PipeHeatExchPrDrop_RC* pipe, double value1, double value2);
void PipeHeatExchPrDrop_RC_getStateValues(PipeHeatExchPrDrop_RC* pipe, double* value1, double* value2);
void PipeHeatExchPrDrop_RC_getStateDerivatives(PipeHeatExchPrDrop_RC* pipe, double* value1, double* value2);

MediumState* PipeHeatExchPrDrop_RC_getPort2State(PipeHeatExchPrDrop_RC* pipe);
FluidFlow* PipeHeatExchPrDrop_RC_getPort1Flow(PipeHeatExchPrDrop_RC* pipe);
HeatFlow* PipeHeatExchPrDrop_RC_getWallHeatFlow(PipeHeatExchPrDrop_RC* pipe);
END_C_LINKAGE

#endif /* PIPEHEATEXCHPRDROPRC_H_ */
