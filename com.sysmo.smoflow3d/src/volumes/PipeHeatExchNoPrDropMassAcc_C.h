/*
 * PipeHeatExchNoPrDropMassAcc_C.h
 *
 *  Created on: Oct 10, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#ifndef PIPEHEATEXCHCNOPRESSDROPMASSACC_H_
#define PIPEHEATEXCHCNOPRESSDROPMASSACC_H_

#include "volumes/FluidChamber.h"
#include "flow/ForcedConvection.h"

#ifdef __cplusplus

class PipeHeatExchNoPrDropMassAcc_C : public SmoComponent {
public:
	PipeHeatExchNoPrDropMassAcc_C(Medium* fluid, double internalVolume, ForcedConvection* convection);
	virtual ~PipeHeatExchNoPrDropMassAcc_C();

	void init(FluidFlow* port1Flow, FluidFlow* port2Flow);
	void compute();

	void getStateValues(double* value1, double* value2);
	void setStateValues(double value1, double value2);
	void getStateDerivatives(double* value1, double* value2);

	HeatFlow* getWallHeatFlow() {return wallHeatFlow;}
	MediumState* getFluidState() {return accFluidState;}
	double getVolume() {return accFluid->getVolume();}

	void setWallNode(ThermalNode* wallNode) {this->wallNode = wallNode;}

private:
	FluidChamber* accFluid;
	MediumState* accFluidState;
	ForcedConvection* convection;

	// Port 1 (fluid)
	//MediumState* port1State; // output (Note: port1State = accFluidState)
	FluidFlow* port1Flow; // input

	// Port 2 (fluid)
	//MediumState* port2State; // output (Note: port2State = accFluidState)
	FluidFlow* port2Flow; // input

	// Port 3 (thermal)
	ThermalNode* wallNode; // input
	HeatFlow* wallHeatFlow;	// output
};

#else //__cplusplus
DECLARE_C_STRUCT(PipeHeatExchNoPrDropMassAcc_C)
#endif //__cplusplus

BEGIN_C_LINKAGE
PipeHeatExchNoPrDropMassAcc_C* PipeHeatExchNoPrDropMassAcc_C_new(Medium* fluid, double internalVolume, ForcedConvection* convection);

void PipeHeatExchNoPrDropMassAcc_C_init(PipeHeatExchNoPrDropMassAcc_C* component, FluidFlow* port1Flow, FluidFlow* port2Flow);
void PipeHeatExchNoPrDropMassAcc_C_compute(PipeHeatExchNoPrDropMassAcc_C* component);

void PipeHeatExchNoPrDropMassAcc_C_setWallNode(PipeHeatExchNoPrDropMassAcc_C* component, ThermalNode* wallNode);
void PipeHeatExchNoPrDropMassAcc_C_setStateValues(PipeHeatExchNoPrDropMassAcc_C* component, double value1, double value2);
void PipeHeatExchNoPrDropMassAcc_C_getStateValues(PipeHeatExchNoPrDropMassAcc_C* component, double* value1, double* value2);
void PipeHeatExchNoPrDropMassAcc_C_getStateDerivatives(PipeHeatExchNoPrDropMassAcc_C* component, double* value1, double* value2);

HeatFlow* PipeHeatExchNoPrDropMassAcc_C_getWallHeatFlow(PipeHeatExchNoPrDropMassAcc_C* component);
MediumState* PipeHeatExchNoPrDropMassAcc_C_getFluidState(PipeHeatExchNoPrDropMassAcc_C* component);
double PipeHeatExchNoPrDropMassAcc_C_getVolume(PipeHeatExchNoPrDropMassAcc_C* component);
END_C_LINKAGE

#endif /* PIPEHEATEXCHCNOPRESSDROPMASSACC_H_ */
