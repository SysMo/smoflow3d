/*
 * PipeHeatExchC.h
 *
 *  Created on: Oct 10, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#ifndef PIPEHEATEXCHC_H_
#define PIPEHEATEXCHC_H_

#include "volumes/FluidChamber.h"
#include "flow/ForcedConvection.h"

#ifdef __cplusplus

class PipeHeatExch_C : public SmoComponent {
public:
	PipeHeatExch_C(Medium* fluid, double internalVolume, ForcedConvection* convection);
	virtual ~PipeHeatExch_C();

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
DECLARE_C_STRUCT(PipeHeatExch_C)
#endif //__cplusplus

BEGIN_C_LINKAGE
PipeHeatExch_C* PipeHeatExch_C_new(Medium* fluid, double internalVolume, ForcedConvection* convection);

void PipeHeatExch_C_init(PipeHeatExch_C* component, FluidFlow* port1Flow, FluidFlow* port2Flow);
void PipeHeatExch_C_compute(PipeHeatExch_C* component);

void PipeHeatExch_C_setWallNode(PipeHeatExch_C* component, ThermalNode* wallNode);
void PipeHeatExch_C_setStateValues(PipeHeatExch_C* component, double value1, double value2);
void PipeHeatExch_C_getStateValues(PipeHeatExch_C* component, double* value1, double* value2);
void PipeHeatExch_C_getStateDerivatives(PipeHeatExch_C* component, double* value1, double* value2);

HeatFlow* PipeHeatExch_C_getWallHeatFlow(PipeHeatExch_C* component);
MediumState* PipeHeatExch_C_getFluidState(PipeHeatExch_C* component);
double PipeHeatExch_C_getVolume(PipeHeatExch_C* component);
END_C_LINKAGE

#endif /* PIPEHEATEXCHC_H_ */
