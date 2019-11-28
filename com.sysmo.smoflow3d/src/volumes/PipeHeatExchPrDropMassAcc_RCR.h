/*
 * PipeHeatExchPrDropMassAcc_RCRR.h
 *
 *  Created on: Nov 28, 2019
 *      Author: Milen Borisov, Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#ifndef PIPEHEATEXCHPRDROPMASSACC_RCR_H_
#define PIPEHEATEXCHPRDROPMASSACC_RCR_H_

#include "volumes/FluidChamber.h"
#include "flow/ForcedConvection.h"
#include "flow/FrictionFlowPipe.h"

#ifdef __cplusplus

class PipeHeatExchPrDropMassAcc_RCR : public SmoComponent {
public:
	PipeHeatExchPrDropMassAcc_RCR(
			int allowBidirectionalFlow,
			double internalVolume,
			FrictionFlowPipe* friction1,
			FrictionFlowPipe* friction2,
			ForcedConvection* convection);
	virtual ~PipeHeatExchPrDropMassAcc_RCR();

	void init();
	void initOuterStates(MediumState* port1State, MediumState* port2State, ThermalNode* wallNode);
	void initInternalState(Medium* fluid, int stateVariableSelection, StateVariableSet& internalStateInitialValues);

	void compute();
	void compute_deactivedFluidFlow();

	void setStateValues(double value1, double value2);
	void getStateValues(double* value1, double* value2);
	void getStateDerivatives(double* value1, double* value2);

	double getVolume() {return accFluid->getVolume();}
	double getFluidMass() {return accFluid->getFluidMass();}

	FluidFlow* getPort1Flow() {return port1Flow;}
	FluidFlow* getPort2Flow() {return port2Flow;}
	MediumState* getInternalFluidState() {return internalState;}
	HeatFlow* getWallHeatFlow() {return wallHeatFlow;}

protected:
	void compute(double pressureDrop1, double pressureDrop2);

protected:
	// Port 1 (fluid)
	MediumState* port1State; 	// input
	FluidFlow* port1Flow;		// output

	// Port 2 (fluid)
	MediumState* port2State; 	// input
	FluidFlow* port2Flow;		// output

	// Port 3 (thermal)
	ThermalNode* wallNode;		// input
	HeatFlow* wallHeatFlow;		// output


	// Parameters
	int allowBidirectionalFlow; //0-no, 1-yes
	double volume;
	ForcedConvection* convection;
	FrictionFlowPipe* friction1;
	FrictionFlowPipe* friction2;

	// Internals
	FluidChamber* accFluid;
	FluidFlow* internalFlow1;
	FluidFlow* internalFlow2;
	MediumState* internalState;
};

#else //__cplusplus
DECLARE_C_STRUCT(PipeHeatExchPrDropMassAcc_RCR)
#endif //__cplusplus

BEGIN_C_LINKAGE
PipeHeatExchPrDropMassAcc_RCR* PipeHeatExchPrDropMassAcc_RCR_new(
		int allowBidirectionalFlow,
		double internalVolume,
		FrictionFlowPipe* friction1,
		FrictionFlowPipe* friction2,
		ForcedConvection* convection);

void PipeHeatExchPrDropMassAcc_RCR_init(PipeHeatExchPrDropMassAcc_RCR* pipe);
void PipeHeatExchPrDropMassAcc_RCR_initOuterStates(PipeHeatExchPrDropMassAcc_RCR* pipe,
		MediumState* port1State, MediumState* port2State, ThermalNode* wallNode);
void PipeHeatExchPrDropMassAcc_RCR_initInternalState(PipeHeatExchPrDropMassAcc_RCR* pipe,
		Medium* fluid, int stateVariableSelection, StateVariableSet innerStateInitializer);

void PipeHeatExchPrDropMassAcc_RCR_compute(PipeHeatExchPrDropMassAcc_RCR* pipe);
void PipeHeatExchPrDropMassAcc_RCR_compute_deactivedFluidFlow(PipeHeatExchPrDropMassAcc_RCR* pipe);

void PipeHeatExchPrDropMassAcc_RCR_setStateValues(PipeHeatExchPrDropMassAcc_RCR* pipe, double value1, double value2);
void PipeHeatExchPrDropMassAcc_RCR_getStateValues(PipeHeatExchPrDropMassAcc_RCR* pipe, double* value1, double* value2);
void PipeHeatExchPrDropMassAcc_RCR_getStateDerivatives(PipeHeatExchPrDropMassAcc_RCR* pipe, double* value1, double* value2);

FluidFlow* PipeHeatExchPrDropMassAcc_RCR_getPort1Flow(PipeHeatExchPrDropMassAcc_RCR* pipe);
FluidFlow* PipeHeatExchPrDropMassAcc_RCR_getPort2Flow(PipeHeatExchPrDropMassAcc_RCR* pipe);
MediumState* PipeHeatExchPrDropMassAcc_RCR_getInternalFluidState(PipeHeatExchPrDropMassAcc_RCR* pipe);

HeatFlow* PipeHeatExchPrDropMassAcc_RCR_getWallHeatFlow(PipeHeatExchPrDropMassAcc_RCR* pipe);

double PipeHeatExchPrDropMassAcc_RCR_getVolume(PipeHeatExchPrDropMassAcc_RCR* component);
double PipeHeatExchPrDropMassAcc_RCR_getFluidMass(PipeHeatExchPrDropMassAcc_RCR* component);
END_C_LINKAGE

#endif /* PIPEHEATEXCHPRDROPMASSACC_RCR_H_ */
