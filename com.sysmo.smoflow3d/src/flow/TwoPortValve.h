/*
 * TwoPortValve.h
 *
 *  Created on: Jul 28, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#ifndef TWOPORTVALVE_H_
#define TWOPORTVALVE_H_

#include "media/MediumState.h"
#include "FlowBase.h"
#include "FlowComponent_R_2Port.h"


#ifdef __cplusplus

class TwoPortValve : public FlowComponent_R_2Port {
public:
	TwoPortValve();
	virtual ~TwoPortValve();

	void setRegulatingSignal(double regulatingSignal) {this->regulatingSignal = regulatingSignal;}

	double getMassFlowRate() {return massFlowRate;}
	double getEnthalpyFlowRate() {return enthalpyFlowRate;}
	double getPressureLoss() {return pressureLoss;}

	void getFlowRates(FluidFlow* flow1, FluidFlow* flow2);

protected:
	/* Inputs */
	double regulatingSignal;

	/* Results */
	double massFlowRate;
	double enthalpyFlowRate;
	double pressureLoss;
};

#else //_cplusplus
DECLARE_C_STRUCT(TwoPortValve)
#endif //_cplusplus


BEGIN_C_LINKAGE
TwoPortValve* TwoPortValve_InputMassFlowRate_new(int allowBidirectionalFlow);

TwoPortValve* TwoPortValve_Kv_new(
		int transitionChoice,
		int allowBidirectionalFlow,
		double Kv,
		double transitionMassFlowRate,
		double transitionPressureDifference,
		double maximumMassFlowRate);

void TwoPortValve_init(TwoPortValve* valve, MediumState* state1, MediumState* state2);
void TwoPortValve_compute(TwoPortValve* valve);

void TwoPortValve_setRegulatingSignal(TwoPortValve* valve, double regulatingSignal);

double TwoPortValve_getMassFlowRate(TwoPortValve* valve);
double TwoPortValve_getEnthalpyFlowRate(TwoPortValve* valve);
double TwoPortValve_getPressureLoss(TwoPortValve* valve);

void TwoPortValve_getFlowRates(TwoPortValve* valve, FluidFlow* flow1, FluidFlow* flow2);
END_C_LINKAGE


#endif /* TWOPORTVALVE_H_ */
