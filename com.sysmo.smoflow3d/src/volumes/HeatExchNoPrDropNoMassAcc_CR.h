/*
 * HeatExchNoPrDropNoMassAcc_CR.h
 *
 *  Created on: Aug 23, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#ifndef HEATEXCHNOPRDROPNOMASSACC_CR_H_
#define HEATEXCHNOPRDROPNOMASSACC_CR_H_

#include "media/MediumState.h"
#include "flow/FlowBase.h"
#include "volumes/ThermalNode.h"

#ifdef __cplusplus

class HeatExchNoPrDropNoMassAcc_CR : public SmoComponent {
public:
	HeatExchNoPrDropNoMassAcc_CR(double heatExhcangeEfficienccy);
	virtual ~HeatExchNoPrDropNoMassAcc_CR();

	void init(ThermalNode* wallNode, MediumState* fluidStateOutlet, FluidFlow* fluidFlowInlet);
	void compute();

	int getFluidFlowOutletIndex() {return fluidFlowOutletIndex;}
	int getWallHeatFlowIndex() {return wallHeatFlowIndex;}
	double getInletTemperature() {return inletTemperature;}
	double getOutletTemperature() {return outletTemperature;}
	double getWallTemperature() {return wallTemperature;}
	double getWallHeatFlowRate() {return wallHeatFlowRate;}
	double getMassFlowRateInlet() {return massFlowRateInlet;}

protected:
	// Internal variables
	MediumState* fluidStateOutletInternal;
	MediumState* fluidStateInletInternal;
	FluidFlow* fluidFlowOutlet;
	int fluidFlowOutletIndex;
	HeatFlow* wallHeatFlow;
	int wallHeatFlowIndex;

	double inletTemperature;
	double outletTemperature;
	double wallTemperature;
	double wallHeatFlowRate;
	double massFlowRateInlet;

	// Parameters
	double heatExhcangeEfficienccy;

	// Inputs
	ThermalNode* wallNode;
	MediumState* fluidStateOutlet;
	FluidFlow* fluidFlowInlet;
};

#else //__cplusplus
DECLARE_C_STRUCT(HeatExchNoPrDropNoMassAcc_CR)
#endif //__cplusplus

BEGIN_C_LINKAGE
HeatExchNoPrDropNoMassAcc_CR* HeatExchNoPrDropNoMassAcc_CR_new(double heatExhcangeEfficienccy);

void HeatExchNoPrDropNoMassAcc_CR_init(HeatExchNoPrDropNoMassAcc_CR* heatExch,
		ThermalNode* wallNode, MediumState* fluidStateOutlet, FluidFlow* fluidFlowInlet);
void HeatExchNoPrDropNoMassAcc_CR_compute(HeatExchNoPrDropNoMassAcc_CR* heatExch);

int HeatExchNoPrDropNoMassAcc_CR_getFluidFlowOutletIndex(HeatExchNoPrDropNoMassAcc_CR* heatExch);
int HeatExchNoPrDropNoMassAcc_CR_getWallHeatFlowIndex(HeatExchNoPrDropNoMassAcc_CR* heatExch);
double HeatExchNoPrDropNoMassAcc_CR_getInletTemperature(HeatExchNoPrDropNoMassAcc_CR* heatExch);
double HeatExchNoPrDropNoMassAcc_CR_getOutletTemperature(HeatExchNoPrDropNoMassAcc_CR* heatExch);
double HeatExchNoPrDropNoMassAcc_CR_getWallTemperature(HeatExchNoPrDropNoMassAcc_CR* heatExch);
double HeatExchNoPrDropNoMassAcc_CR_getWallHeatFlowRate(HeatExchNoPrDropNoMassAcc_CR* heatExch);
double HeatExchNoPrDropNoMassAcc_CR_getMassFlowRateInlet(HeatExchNoPrDropNoMassAcc_CR* heatExch);
END_C_LINKAGE

#endif /* HEATEXCHNOPRDROPNOMASSACC_CR_H_ */
