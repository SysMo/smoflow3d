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
#include "flow/ForcedConvection.h"
#include "volumes/ThermalNode.h"
#include "volumes/Component_RC.h"

#ifdef __cplusplus

class PipeHeatExchNoPrDropNoMassAcc_RC : public Component_RC {
public:
	PipeHeatExchNoPrDropNoMassAcc_RC(double stateTimeConstant);
	virtual ~PipeHeatExchNoPrDropNoMassAcc_RC();

	virtual void init(FluidFlow* port2Flow);
	virtual void initStates(MediumState* port1State,
			ThermalNode* wallNode, StateVariableSet& innerStateInitializer);

	virtual void compute() = 0;

	void setOutletStateValue(double outletStateValue);
	double getOutletStateValue() {return port2StateValue;}
	double getOutletStateDerivative();

protected:
	virtual void _init() {}

protected:
	enum {
		sTemperature,
		sEnthalpy
	} stateVariable;

	// Parameters
	double pipeLength;
	double stateTimeConstant;

	// internals
	MediumState* port2LimitState;

	double port2StateValue;
	double port2StateSetpoint;
};

#else //__cplusplus
DECLARE_C_STRUCT(PipeHeatExchNoPrDropNoMassAcc_RC)
#endif //__cplusplus

BEGIN_C_LINKAGE
PipeHeatExchNoPrDropNoMassAcc_RC* PipeHeatExchNoPrDropNoMassAcc_RC_Efficiency_new(double heatExchEfficiency, double stateTimeConstant);
PipeHeatExchNoPrDropNoMassAcc_RC* PipeHeatExchNoPrDropNoMassAcc_RC_Convection_new(ForcedConvection* convection, double stateTimeConstant);

void PipeHeatExchNoPrDropNoMassAcc_RC_compute(PipeHeatExchNoPrDropNoMassAcc_RC* pipe);

void PipeHeatExchNoPrDropNoMassAcc_RC_setOutletStateValue(PipeHeatExchNoPrDropNoMassAcc_RC* pipe,  double outletStateValue);
double PipeHeatExchNoPrDropNoMassAcc_RC_getOutletStateValue(PipeHeatExchNoPrDropNoMassAcc_RC* pipe);
double PipeHeatExchNoPrDropNoMassAcc_RC_getOutletStateDerivative(PipeHeatExchNoPrDropNoMassAcc_RC* pipe);
END_C_LINKAGE

#endif /* PIPEHEATEXCHNOPRDROPNOMASSACC_H_ */
