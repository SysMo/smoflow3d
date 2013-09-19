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

	void setTransitionChoice(int transitionChoice) {this->transitionChoice = transitionChoice;}
	void setAllowBidirectionalFlow(int allowBidirectionalFlow) {this->allowBidirectionalFlow = allowBidirectionalFlow;}
	void setKv(double Kv) {this->Kv = Kv;}
	void setTransitionMassFlowRate(double transitionMassFlowRate) {this->transitionMassFlowRate = transitionMassFlowRate;}
	void setTransitionPressureDifference(double transitionPressureDifference) {this->transitionPressureDifference = transitionPressureDifference;}
	void setMaximumMassFlowRate(double maximumMassFlowRate) {this->maximumMassFlowRate = maximumMassFlowRate;}

	void setRegulatingSignal(double regulatingSignal) {this->regulatingSignal = regulatingSignal;}

	double getMassFlowRate() {return massFlowRate;}
	double getEnthalpyFlowRate() {return enthalpyFlowRate;}
	double getPressureLoss() {return pressureLoss;}

	void compute_Kv();

	void getFlowRates(FluidFlow* flow1, FluidFlow* flow2);

protected:
	/* Parameters */
	int transitionChoice; //choice of transition to linear region: 1 - Minimum mass flow; 2 - Minimum pressure difference
	int allowBidirectionalFlow; // 0 - no; 1 - yes

	double Kv;
	double transitionMassFlowRate;
	double transitionPressureDifference;
	double maximumMassFlowRate;

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
TwoPortValve* TwoPortValve_new();
void TwoPortValve_init(TwoPortValve* valve, MediumState* state1, MediumState* state2);
void TwoPortValve_compute_Kv(TwoPortValve* valve);

void TwoPortValve_setTransitionChoice(TwoPortValve* valve, int transitionChoice);
void TwoPortValve_setAllowBidirectionalFlow(TwoPortValve* valve, int allowBidirectionalFlow);
void TwoPortValve_setKv(TwoPortValve* valve, double Kv);
void TwoPortValve_setTransitionMassFlowRate(TwoPortValve* valve, double transitionMassFlowRate);
void TwoPortValve_setTransitionPressureDifference(TwoPortValve* valve, double transitionPressureDifference);
void TwoPortValve_setMaximumMassFlowRate(TwoPortValve* valve, double maximumMassFlowRate);

void TwoPortValve_setRegulatingSignal(TwoPortValve* valve, double regulatingSignal);

double TwoPortValve_getMassFlowRate(TwoPortValve* valve);
double TwoPortValve_getEnthalpyFlowRate(TwoPortValve* valve);
double TwoPortValve_getPressureLoss(TwoPortValve* valve);

void TwoPortValve_getFlowRates(TwoPortValve* valve, FluidFlow* flow1, FluidFlow* flow2);
END_C_LINKAGE


#endif /* TWOPORTVALVE_H_ */
