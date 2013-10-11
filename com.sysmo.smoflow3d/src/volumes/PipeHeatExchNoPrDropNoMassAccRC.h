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

	void initOutletState(MediumState* inletState, ThermalNode* wallNode);
	void updateOutletState(double outletStateValue);

	virtual void compute() = 0;

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
#define KOMPONENT PipeHeatExchNoPrDropNoMassAcc_RC
KOMPONENT* PipeHeatExchNoPrDropNoMassAcc_RC_Efficiency_new(double heatExchEfficiency, double stateTimeConstant);
KOMPONENT* PipeHeatExchNoPrDropNoMassAcc_RC_Convection_new(ForcedConvection* convection, double stateTimeConstant);

KOMPONENT_FUNC(void, init, FluidFlow* outletFlow);

KOMPONENT_FUNC(void, initOutletState, MediumState* inletState, ThermalNode* wallNode);
KOMPONENT_FUNC(void, updateOutletState, double outletStateValue);

KOMPONENT_FUNC_V(void, compute);

KOMPONENT_FUNC_V(MediumState*, getOutletState);
KOMPONENT_FUNC_V(double, getOutletStateValue);
KOMPONENT_FUNC_V(double, getOutletStateDerivative);
KOMPONENT_FUNC_V(HeatFlow*, getWallHeatFlow);
KOMPONENT_FUNC_V(FluidFlow*, getInletFlow);
#undef KOMPONENT
END_C_LINKAGE

#endif /* PIPEHEATEXCHNOPRDROPNOMASSACC_H_ */
