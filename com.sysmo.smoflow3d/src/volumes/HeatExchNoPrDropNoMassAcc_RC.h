/*
 * HeatExchNoPrDropNoMassAcc_RC.h
 *
 *  Created on: Aug 13, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#ifndef HEATEXCHNOPRDROPNOMASSACC_H_
#define HEATEXCHNOPRDROPNOMASSACC_H_

#include "media/MediumState.h"
#include "flow/FlowBase.h"
#include "volumes/ThermalNode.h"
#include "volumes/FluidChamber.h"
#include "flow/ForcedConvection.h"

#ifdef __cplusplus

class HeatExchNoPrDropNoMassAcc_RC : public SmoComponent {
public:
	HeatExchNoPrDropNoMassAcc_RC(double stateTimeConstant);
	virtual ~HeatExchNoPrDropNoMassAcc_RC();

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
DECLARE_C_STRUCT(HeatExchNoPrDropNoMassAcc_RC)
#endif //__cplusplus

BEGIN_C_LINKAGE
HeatExchNoPrDropNoMassAcc_RC* HeatExchNoPrDropNoMassAcc_RC_Efficiency_new(double heatExchEfficiency, double stateTimeConstant);
HeatExchNoPrDropNoMassAcc_RC* HeatExchNoPrDropNoMassAcc_RC_Convection_new(ForcedConvection* convection, double stateTimeConstant);

void HeatExchNoPrDropNoMassAcc_RC_init(HeatExchNoPrDropNoMassAcc_RC* heatExch, FluidFlow* port2Flow);
void HeatExchNoPrDropNoMassAcc_RC_initStates(HeatExchNoPrDropNoMassAcc_RC* heatExch, MediumState* port1State, ThermalNode* wallNode);
void HeatExchNoPrDropNoMassAcc_RC_compute(HeatExchNoPrDropNoMassAcc_RC* heatExch);

void HeatExchNoPrDropNoMassAcc_RC_setStateValue(HeatExchNoPrDropNoMassAcc_RC* heatExch,  double stateValue);
double HeatExchNoPrDropNoMassAcc_RC_getStateValue(HeatExchNoPrDropNoMassAcc_RC* heatExch);
double HeatExchNoPrDropNoMassAcc_RC_getStateDerivative(HeatExchNoPrDropNoMassAcc_RC* heatExch);

MediumState* HeatExchNoPrDropNoMassAcc_RC_getPort2State(HeatExchNoPrDropNoMassAcc_RC* heatExch);
FluidFlow* HeatExchNoPrDropNoMassAcc_RC_getPort1Flow(HeatExchNoPrDropNoMassAcc_RC* heatExch);
HeatFlow* HeatExchNoPrDropNoMassAcc_RC_getWallHeatFlow(HeatExchNoPrDropNoMassAcc_RC* heatExch);
END_C_LINKAGE

#endif /* HEATEXCHNOPRDROPNOMASSACC_H_ */
