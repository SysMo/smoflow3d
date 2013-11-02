/*
 * PipeHeatExchPrDropRC.h
 *
 *  Created on: Aug 23, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#ifndef PIPEHEATEXCHNOPRDROPNOMASSACC_CR_H_
#define PIPEHEATEXCHNOPRDROPNOMASSACC_CR_H_

#include "media/MediumState.h"
#include "flow/FlowBase.h"
#include "volumes/ThermalNode.h"

#ifdef __cplusplus

class PipeHeatExchNoPrDropNoMassAcc_CR : public SmoComponent {
public:
	PipeHeatExchNoPrDropNoMassAcc_CR(double heatExhcangeEfficienccy);
	virtual ~PipeHeatExchNoPrDropNoMassAcc_CR();

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
DECLARE_C_STRUCT(PipeHeatExchNoPrDropNoMassAcc_CR)
#endif //__cplusplus

BEGIN_C_LINKAGE
PipeHeatExchNoPrDropNoMassAcc_CR* PipeHeatExchNoPrDropNoMassAcc_CR_new(double heatExhcangeEfficienccy);

void PipeHeatExchNoPrDropNoMassAcc_CR_init(PipeHeatExchNoPrDropNoMassAcc_CR* pipe,
		ThermalNode* wallNode, MediumState* fluidStateOutlet, FluidFlow* fluidFlowInlet);
void PipeHeatExchNoPrDropNoMassAcc_CR_compute(PipeHeatExchNoPrDropNoMassAcc_CR* pipe);

int PipeHeatExchNoPrDropNoMassAcc_CR_getFluidFlowOutletIndex(PipeHeatExchNoPrDropNoMassAcc_CR* pipe);
int PipeHeatExchNoPrDropNoMassAcc_CR_getWallHeatFlowIndex(PipeHeatExchNoPrDropNoMassAcc_CR* pipe);
double PipeHeatExchNoPrDropNoMassAcc_CR_getInletTemperature(PipeHeatExchNoPrDropNoMassAcc_CR* pipe);
double PipeHeatExchNoPrDropNoMassAcc_CR_getOutletTemperature(PipeHeatExchNoPrDropNoMassAcc_CR* pipe);
double PipeHeatExchNoPrDropNoMassAcc_CR_getWallTemperature(PipeHeatExchNoPrDropNoMassAcc_CR* pipe);
double PipeHeatExchNoPrDropNoMassAcc_CR_getWallHeatFlowRate(PipeHeatExchNoPrDropNoMassAcc_CR* pipe);
double PipeHeatExchNoPrDropNoMassAcc_CR_getMassFlowRateInlet(PipeHeatExchNoPrDropNoMassAcc_CR* pipe);
END_C_LINKAGE

#endif /* PIPEHEATEXCHNOPRDROPNOMASSACC_CR_H_ */
