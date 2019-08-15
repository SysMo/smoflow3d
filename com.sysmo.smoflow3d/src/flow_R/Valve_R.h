/*
 * Valve_R.h
 *
 *  Created on: Sep 19, 2014
 *      Author: Milen Borisov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#ifndef VALVE_R_H_
#define VALVE_R_H_

#include "media/MediumState.h"
#include "flow/FrictionFlowValve.h"
#include "flow_R/FlowComponent_R.h"


#ifdef __cplusplus

class Valve_R : public FlowComponent_R {
public:
	Valve_R(FrictionFlowValve* friction);
	virtual ~Valve_R();

	virtual void init(MediumState* state1);
	virtual bool compute(double massFlowRate, double minDownstreamPressure);

	void setRegulatingSignal(double regulatingSignal);
	void setCloseFlowAtNegativeRegulatingSignal(bool flagCloseFlowAtNegativeRegulatingSignal);

	FlowType getFlowType() {return friction->getFlowType();}

protected:
	FrictionFlowValve* friction;
	bool flagCloseFlowAtNegativeRegulatingSignal;
};

#else //_cplusplus
DECLARE_C_STRUCT(Valve_R)
#endif //_cplusplus


BEGIN_C_LINKAGE
Valve_R* Valve_InputPressureLoss_R_new(
		int allowBidirectionalFlow);

Valve_R* ValveKv_R_new(
		int allowBidirectionalFlow,
		double Kv,
		int transitionChoice,
		double transitionMassFlowRate,
		double transitionPressureDifference);

Valve_R* Valve_OrificeCompressibleIdealGas_R_new(
		int allowBidirectionalFlow,
		double orificeArea,
		double flowCoefficient);

void Valve_R_setRegulatingSignal(Valve_R* valve, double regulatingSignal);
void Valve_R_setCloseFlowAtNegativeRegulatingSignal(Valve_R* valve, int flagCloseFlowAtNegativeRegulatingSignal);

int Valve_R_getFlowType(Valve_R* valve);


END_C_LINKAGE


#endif /* VALVE_R_H_ */
