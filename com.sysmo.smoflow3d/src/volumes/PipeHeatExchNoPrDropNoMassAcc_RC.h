/*
 * PipeHeatExchNoPrDropNoMassAccRC.h
 *
 *  Created on: Aug 13, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#ifndef PIPEHEATEXCHNOPRDROPNOMASSACC_H_
#define PIPEHEATEXCHNOPRDROPNOMASSACC_H_

#include "media/MediumState.h"
#include "flow/FlowBase.h"
#include "volumes/ThermalNode.h"
#include "flow/ForcedConvection.h"

#ifdef __cplusplus

class PipeHeatExchNoPrDropNoMassAcc_RC : public SmoComponent {
public:
	PipeHeatExchNoPrDropNoMassAcc_RC(double stateTimeConstant);
	virtual ~PipeHeatExchNoPrDropNoMassAcc_RC();

	void init(FluidFlow* outletFlow);
	void initStates(MediumState* inletState, ThermalNode* wallNode);

	virtual void compute() = 0;
	void setOutletStateValue(double outletStateValue);

	MediumState* getOutletState() {return outletState;}
	double getOutletStateValue() {return outletStateValue;}
	double getOutletStateDerivative();
	HeatFlow* getWallHeatFlow() {return wallHeatFlow;}
	FluidFlow* getInletFlow() {return inletFlow;}

protected:
	enum {
		sTemperature,
		sEnthalpy
	} stateVariable;

	// Parameters
	double pipeLength;
	double stateTimeConstant;

	// Port 1 (fluid)
	MediumState* inletState; // input
	FluidFlow* inletFlow; // output

	// Port 2 (fluid)
	MediumState* outletState; // output
	FluidFlow* outletFlow; // input

	// Port 3 (thermal)
	ThermalNode* wallNode; // input
	HeatFlow* wallHeatFlow;	// output

	// internals
	MediumState* outletLimitState;

	double outletStateValue;
	double outletStateSetpoint;
};

#else //__cplusplus
DECLARE_C_STRUCT(PipeHeatExchNoPrDropNoMassAcc_RC)
#endif //__cplusplus

BEGIN_C_LINKAGE
PipeHeatExchNoPrDropNoMassAcc_RC* PipeHeatExchNoPrDropNoMassAcc_RC_Efficiency_new(double heatExchEfficiency, double stateTimeConstant);
PipeHeatExchNoPrDropNoMassAcc_RC* PipeHeatExchNoPrDropNoMassAcc_RC_Convection_new(ForcedConvection* convection, double stateTimeConstant);

void PipeHeatExchNoPrDropNoMassAcc_RC_init(PipeHeatExchNoPrDropNoMassAcc_RC* pipe, FluidFlow* outletFlow);
void PipeHeatExchNoPrDropNoMassAcc_RC_initStates(PipeHeatExchNoPrDropNoMassAcc_RC* pipe, MediumState* inletState, ThermalNode* wallNode);

void PipeHeatExchNoPrDropNoMassAcc_RC_compute(PipeHeatExchNoPrDropNoMassAcc_RC* pipe);
void PipeHeatExchNoPrDropNoMassAcc_RC_setOutletStateValue(PipeHeatExchNoPrDropNoMassAcc_RC* pipe,  double outletStateValue);

MediumState* PipeHeatExchNoPrDropNoMassAcc_RC_getOutletState(PipeHeatExchNoPrDropNoMassAcc_RC* pipe);
double PipeHeatExchNoPrDropNoMassAcc_RC_getOutletStateValue(PipeHeatExchNoPrDropNoMassAcc_RC* pipe);
double PipeHeatExchNoPrDropNoMassAcc_RC_getOutletStateDerivative(PipeHeatExchNoPrDropNoMassAcc_RC* pipe);

HeatFlow* PipeHeatExchNoPrDropNoMassAcc_RC_getWallHeatFlow(PipeHeatExchNoPrDropNoMassAcc_RC* pipe);
FluidFlow* PipeHeatExchNoPrDropNoMassAcc_RC_getInletFlow(PipeHeatExchNoPrDropNoMassAcc_RC* pipe);
END_C_LINKAGE

#endif /* PIPEHEATEXCHNOPRDROPNOMASSACC_H_ */
