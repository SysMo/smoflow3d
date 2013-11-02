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
#include "volumes/FluidChamber.h"
#include "flow/ForcedConvection.h"

#ifdef __cplusplus

class PipeHeatExchNoPrDropNoMassAcc_RC : public SmoComponent {
public:
	PipeHeatExchNoPrDropNoMassAcc_RC(double stateTimeConstant);
	virtual ~PipeHeatExchNoPrDropNoMassAcc_RC();

	virtual void init(FluidFlow* port2Flow);
	virtual void initStates(MediumState* port1State, ThermalNode* wallNode);
	virtual void compute() = 0;

	void setStateValue(double stateValue);
	double getStateValue() {return stateValue;}
	double getStateDerivative();

	FluidFlow* getPort1Flow() {return port1Flow;}
	MediumState* getPort2State() {return port2State;}
	HeatFlow* getWallHeatFlow() {return wallHeatFlow;}

protected:
	typedef enum {
		sTemperature,
		sEnthalpy
	} StateVariableType;
	StateVariableType stateVariableType;

	// Parameters
	double stateTimeConstant;

	// internals
	double stateValue;
	double stateSetpoint;

	// Port 1 (fluid)
	MediumState* port1State; 	// input
	FluidFlow* port1Flow;		// output

	// Port 2 (fluid)
	MediumState* port2State; 	// output
	FluidFlow* port2Flow;		// input

	// Port 3 (thermal)
	ThermalNode* wallNode;		// input
	HeatFlow* wallHeatFlow;		// output
};

#else //__cplusplus
DECLARE_C_STRUCT(PipeHeatExchNoPrDropNoMassAcc_RC)
#endif //__cplusplus

BEGIN_C_LINKAGE
PipeHeatExchNoPrDropNoMassAcc_RC* PipeHeatExchNoPrDropNoMassAcc_RC_Efficiency_new(double heatExchEfficiency, double stateTimeConstant);
PipeHeatExchNoPrDropNoMassAcc_RC* PipeHeatExchNoPrDropNoMassAcc_RC_Convection_new(ForcedConvection* convection, double stateTimeConstant);

void PipeHeatExchNoPrDropNoMassAcc_RC_init(PipeHeatExchNoPrDropNoMassAcc_RC* pipe, FluidFlow* port2Flow);
void PipeHeatExchNoPrDropNoMassAcc_RC_initStates(PipeHeatExchNoPrDropNoMassAcc_RC* pipe, MediumState* port1State, ThermalNode* wallNode);
void PipeHeatExchNoPrDropNoMassAcc_RC_compute(PipeHeatExchNoPrDropNoMassAcc_RC* pipe);

void PipeHeatExchNoPrDropNoMassAcc_RC_setStateValue(PipeHeatExchNoPrDropNoMassAcc_RC* pipe,  double stateValue);
double PipeHeatExchNoPrDropNoMassAcc_RC_getStateValue(PipeHeatExchNoPrDropNoMassAcc_RC* pipe);
double PipeHeatExchNoPrDropNoMassAcc_RC_getStateDerivative(PipeHeatExchNoPrDropNoMassAcc_RC* pipe);

MediumState* PipeHeatExchNoPrDropNoMassAcc_RC_getPort2State(PipeHeatExchNoPrDropNoMassAcc_RC* pipe);
FluidFlow* PipeHeatExchNoPrDropNoMassAcc_RC_getPort1Flow(PipeHeatExchNoPrDropNoMassAcc_RC* pipe);
HeatFlow* PipeHeatExchNoPrDropNoMassAcc_RC_getWallHeatFlow(PipeHeatExchNoPrDropNoMassAcc_RC* pipe);
END_C_LINKAGE

#endif /* PIPEHEATEXCHNOPRDROPNOMASSACC_H_ */
