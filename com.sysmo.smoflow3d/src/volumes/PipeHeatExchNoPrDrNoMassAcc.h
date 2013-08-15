/*
 * PipeHeatExchNoPrDrNoMassAcc.h
 *
 *  Created on: Aug 13, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#ifndef PIPEHEATEXCHNOPRDRNOMASSACC_H_
#define PIPEHEATEXCHNOPRDRNOMASSACC_H_

#include "media/MediumState.h"
#include "flow/FlowBase.h"
#include "volumes/ThermalNode.h"
#include "flow/ForcedConvection.h"

#ifdef __cplusplus

class Pipe_HeatExch_NoPrDr_NoMassAcc {
public:
	Pipe_HeatExch_NoPrDr_NoMassAcc(double stateTimeConstant);
	virtual ~Pipe_HeatExch_NoPrDr_NoMassAcc();
	void init(MediumState* inletState, ThermalNode* wallNode,
			FluidFlow* outletFlow, // inputs
			int& inletFlowIndex, int& outletStateIndex,
			int& wallHeatFlowIndex); // outputs
	void updateOutletState(double outletStateValue);
	virtual void compute() = 0;
	MediumState* getOutletState() {return outletState;}
	HeatFlow* getWallHeatFlow() {return wallHeatFlow;}
	double getOutletStateDerivative();
protected:
	virtual void _init(){}
	enum {
		sTemperature,
		sEnthalpy
	} stateVariable;
	double pipeLength;
	double stateTimeConstant;

	// inputs
	MediumState* inletState;
	ThermalNode* wallNode;
	FluidFlow* outletFlow;
 	// outputs
	FluidFlow* inletFlow;
	MediumState* outletState;
	HeatFlow* wallHeatFlow;
	// internals
	MediumState* outletLimitState;

	double outletStateValue;
	double outletStateSetpoint;
};

#else //__cplusplus
DECLARE_C_STRUCT(Pipe_HeatExch_NoPrDr_NoMassAcc)
#endif //__cplusplus

BEGIN_C_LINKAGE
#define KOMPONENT Pipe_HeatExch_NoPrDr_NoMassAcc
KOMPONENT* Pipe_HeatExch_NoPrDr_NoMassAcc_HeEfficiency_new(
		double heatExchEfficiency, double stateTimeConstant);
KOMPONENT* Pipe_HeatExch_NoPrDr_NoMassAcc_Convection_new(
		ForcedConvection* convection, double stateTimeConstant);
KOMPONENT_FUNC(void, init, MediumState* inletState, ThermalNode* wallNode,
		FluidFlow* outletFlow, int* inletFlowIndex, int* outletStateIndex,
		int* wallHeatFlowIndex);
#undef KOMPONENT
END_C_LINKAGE

#endif /* PIPEHEATEXCHNOPRDRNOMASSACC_H_ */
