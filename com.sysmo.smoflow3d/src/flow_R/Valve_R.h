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

protected:
	FrictionFlowValve* friction;
};

#else //_cplusplus
DECLARE_C_STRUCT(Valve_R)
#endif //_cplusplus


BEGIN_C_LINKAGE
Valve_R* ValveKv_R_new(
		int allowBidirectionalFlow,
		double Kv,
		int transitionChoice,
		double transitionMassFlowRate,
		double transitionPressureDifference);

void Valve_R_setRegulatingSignal(Valve_R* valve, double regulatingSignal);
END_C_LINKAGE


#endif /* VALVE_R_H_ */
