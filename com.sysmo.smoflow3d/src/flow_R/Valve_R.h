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
#include "Component_R.h"


#ifdef __cplusplus

class Valve_R : public Component_R {
public:
	Valve_R(FrictionFlowValve* friction);
	virtual ~Valve_R();

	virtual void init(MediumState* state1, MediumState* state2);
	virtual bool compute(double massFlowRate, double minDownstreamPressure);

	void setRegulationgSignal(double regulatingSignal);

protected:
	FrictionFlowValve* friction;
};

#else //_cplusplus
DECLARE_C_STRUCT(Valve_R)
#endif //_cplusplus


BEGIN_C_LINKAGE
Valve_R* ValveKv_R_new(
		double Kv,
		int transitionChoice,
		double transitionMassFlowRate,
		double transitionPressureDifference);
END_C_LINKAGE


#endif /* VALVE_R_H_ */
