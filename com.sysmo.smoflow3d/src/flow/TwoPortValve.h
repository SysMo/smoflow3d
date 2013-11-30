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
#include "flow/FlowBase.h"
#include "flow/FrictionFlowValve.h"


#ifdef __cplusplus

class TwoPortValve : public SmoComponent {
public:
	TwoPortValve(FrictionFlowValve* friction);
	virtual ~TwoPortValve();

	void init(MediumState* state1, MediumState* state2);
	void compute();

	void setRegulatingSignal(double regulatingSignal) {friction->setRegulatingSignal(regulatingSignal);}

	void updateFluidFlows(FluidFlow* flow1, FluidFlow* flow2) {friction->updateFluidFlows(flow1, flow2);}
	double getAbsolutePressureDrop() {return friction->getAbsolutePressureDrop();}
	FlowType getFlowType() {return friction->getFlowType();}

	bool isFlowClosed() {return friction->getRegulatingSignal() <= 0;}

protected:
	FrictionFlowValve* friction;

	MediumState* state1;
	MediumState* state2;
};

#else //_cplusplus
DECLARE_C_STRUCT(TwoPortValve)
#endif //_cplusplus


BEGIN_C_LINKAGE
TwoPortValve* TwoPortValve_InputMassFlowRate_new(
		int allowBidirectionalFlow);

TwoPortValve* TwoPortValve_Kv_new(
		int allowBidirectionalFlow,
		double Kv,
		int transitionChoice,
		double transitionMassFlowRate,
		double transitionPressureDifference,
		double maximumMassFlowRate);

TwoPortValve* TwoPortValve_OrificeCompressibleIdealGas_new(
		int allowBidirectionalFlow,
		double orificeArea,
		double flowCoefficient);

void TwoPortValve_init(TwoPortValve* valve, MediumState* state1, MediumState* state2);
void TwoPortValve_compute(TwoPortValve* valve);

void TwoPortValve_setRegulatingSignal(TwoPortValve* valve, double regulatingSignal);

void TwoPortValve_updateFluidFlows(TwoPortValve* valve, FluidFlow* flow1, FluidFlow* flow2);
double TwoPortValve_getAbsolutePressureDrop(TwoPortValve* valve);
int TwoPortValve_getFlowType(TwoPortValve* valve);
int TwoPortValve_getIsFlowClosed(TwoPortValve* valve);
END_C_LINKAGE


#endif /* TWOPORTVALVE_H_ */
