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
	PipeHeatExch_C(double internalVolume, ForcedConvection* convection);
	virtual ~PipeHeatExch_C();

	void init(FluidFlow* port1Flow, FluidFlow* port2Flow);
	void createState(Medium* fluid, ThermalNode* wallNode);

	void getStateValues(double* value1, double* value2);
	void setStateValues(double value1, double value2);
	void getStateDerivatives(double* value1, double* value2);

	void compute();

private:
	double volume;
	FluidChamber* accFluid;
	MediumState* accFluidState;
	ForcedConvection* convection;

	// Port 1 (fluid)
	//MediumState* port1State; // output
	FluidFlow* port1Flow; 	 // input

	// Port 2 (fluid)
	//MediumState* port2State; // output
	FluidFlow* port2Flow;	 // input

	// Port 3 (thermal)
	ThermalNode* wallNode;	 // input
	HeatFlow* wallHeatFlow;	 // output
};

#else //__cplusplus
DECLARE_C_STRUCT(PipeHeatExch_C)
#endif //__cplusplus

BEGIN_C_LINKAGE
PipeHeatExch_C* PipeHeatExch_C_new(double internalVolume, ForcedConvection* convection);
END_C_LINKAGE

#endif /* PIPEHEATEXCHC_H_ */
