/*
 * PipeHeatExchPrDropMassAcc_RC.h
 *
 *  Created on: Aug 23, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#ifndef PIPEHEATEXCHPRDROPMASSACC_RC_H_
#define PIPEHEATEXCHPRDROPMASSACC_RC_H_

#include "volumes/FluidChamber.h"
#include "flow/ForcedConvection.h"
#include "flow/FrictionFlowPipe.h"

#ifdef __cplusplus

class PipeHeatExchPrDropMassAcc_RC : public SmoComponent {
public:
	PipeHeatExchPrDropMassAcc_RC(int allowBidirectionalFlow, double internalVolume, FrictionFlowPipe* friction, ForcedConvection* convection);
	virtual ~PipeHeatExchPrDropMassAcc_RC();

	void init(FluidFlow* port2Flow);
	void initOuterStates(MediumState* port1State, ThermalNode* wallNode);
	void initInternalState(Medium* fluid, int stateVariableSelection, StateVariableSet& internalStateInitialValues);
	void compute();
	void compute_deactivedFluidFlow();

	void setStateValues(double value1, double value2);
	void getStateValues(double* value1, double* value2);
	void getStateDerivatives(double* value1, double* value2);

	double getVolume() {return accFluid->getVolume();}
	double getFluidMass() {return accFluid->getFluidMass();}

	FluidFlow* getPort1Flow() {return port1Flow;}
	MediumState* getPort2State() {return port2State;}
	HeatFlow* getWallHeatFlow() {return wallHeatFlow;}

protected:
	void compute(double pressureDrop);

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
	int allowBidirectionalFlow; //0-no, 1-yes
	double volume;
	ForcedConvection* convection;
	FrictionFlowPipe* friction;

	// Internals
	FluidChamber* accFluid;
	FluidFlow* internalFlow;
};

#else //__cplusplus
DECLARE_C_STRUCT(PipeHeatExchPrDropMassAcc_RC)
#endif //__cplusplus

BEGIN_C_LINKAGE
PipeHeatExchPrDropMassAcc_RC* PipeHeatExchPrDropMassAcc_RC_new(int allowBidirectionalFlow, double internalVolume, FrictionFlowPipe* friction, ForcedConvection* convection);

void PipeHeatExchPrDropMassAcc_RC_init(PipeHeatExchPrDropMassAcc_RC* pipe, FluidFlow* port2Flow);
void PipeHeatExchPrDropMassAcc_RC_initOuterStates(PipeHeatExchPrDropMassAcc_RC* pipe, MediumState* port1State, ThermalNode* wallNode);
void PipeHeatExchPrDropMassAcc_RC_initInternalState(PipeHeatExchPrDropMassAcc_RC* pipe, Medium* fluid, int stateVariableSelection, StateVariableSet innerStateInitializer);
void PipeHeatExchPrDropMassAcc_RC_compute(PipeHeatExchPrDropMassAcc_RC* pipe);
void PipeHeatExchPrDropMassAcc_RC_compute_deactivedFluidFlow(PipeHeatExchPrDropMassAcc_RC* pipe);

void PipeHeatExchPrDropMassAcc_RC_setStateValues(PipeHeatExchPrDropMassAcc_RC* pipe, double value1, double value2);
void PipeHeatExchPrDropMassAcc_RC_getStateValues(PipeHeatExchPrDropMassAcc_RC* pipe, double* value1, double* value2);
void PipeHeatExchPrDropMassAcc_RC_getStateDerivatives(PipeHeatExchPrDropMassAcc_RC* pipe, double* value1, double* value2);

MediumState* PipeHeatExchPrDropMassAcc_RC_getPort2State(PipeHeatExchPrDropMassAcc_RC* pipe);
FluidFlow* PipeHeatExchPrDropMassAcc_RC_getPort1Flow(PipeHeatExchPrDropMassAcc_RC* pipe);
HeatFlow* PipeHeatExchPrDropMassAcc_RC_getWallHeatFlow(PipeHeatExchPrDropMassAcc_RC* pipe);
double PipeHeatExchPrDropMassAcc_RC_getVolume(PipeHeatExchPrDropMassAcc_RC* component);
double PipeHeatExchPrDropMassAcc_RC_getFluidMass(PipeHeatExchPrDropMassAcc_RC* component);
END_C_LINKAGE

#endif /* PIPEHEATEXCHPRDROPMASSACC_RC_H_ */
