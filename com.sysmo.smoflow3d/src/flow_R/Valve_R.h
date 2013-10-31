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
#include "flow/FrictionFlowPipe.h"
#include "Component_R.h"


#ifdef __cplusplus

class Valve_R : public Component_R {
public:
	Valve_R();
	virtual ~Valve_R();

	virtual bool compute(double massFlowRate, double minDownstreamPressure);
	virtual double computePressureDrop(double massFlowRat) = 0;

	double getAbsolutePressureDrop() {return absPressureDrop;}
	void setRegulationgSignal(double regulatingSignal);

protected:
	double regulatingSignal;
	double absPressureDrop;
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
