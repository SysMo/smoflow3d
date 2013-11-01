/*
 * FrictionFlowVale.h
 *
 *  Created on: Aug 22, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#ifndef FRICTIONFLOWVALVE_H_
#define FRICTIONFLOWVALVE_H_

#include "media/MediumState.h"
#include "flow/FlowBase.h"

#ifdef __cplusplus

class FrictionFlowValve {
public:
	FrictionFlowValve(int allowBidirectionalFlow);
	virtual ~FrictionFlowValve();

	void init(MediumState* state1, MediumState* state2);
	void setRegulationSignal(double regulatingSignal) {this->regulatingSignal = regulatingSignal;}

	virtual double computePressureDrop(double massFlowRate) = 0;
	virtual double computeMassFlowRate(double pressureDrop) = 0;

	void updateFluidFlows(FluidFlow* flow1, FluidFlow* flow2);

	double getAbsolutePressureDrop() {return absPressureDrop;}
	double getMassFlowRate() {return massFlowRate;}

protected:
	bool isBidirectionalFlowAllowed() {return allowBidirectionalFlow == 1;}
	MediumState* getUpstreamState(double massFlowRate);
	MediumState* getUpstreamState(int flowDirection);

protected:
	double regulatingSignal;

	double massFlowRate;
	double absPressureDrop;

private:
	int allowBidirectionalFlow; //0 - no; 1 - yes

	MediumState* state1;
	MediumState* state2;
};

#else //__cplusplus
DECLARE_C_STRUCT(FrictionFlowValve)
#endif //__cplusplus

BEGIN_C_LINKAGE
FrictionFlowValve* FrictionFlowValve_InputMassFlowRate_new(int allowBidirectionalFlow);

FrictionFlowValve* FrictionFlowValve_Kv_new(
		int allowBidirectionalFlow,
		double Kv,
		int transitionChoice,
		double transitionMassFlowRate,
		double transitionPressureDifference,
		double maximumMassFlowRate);
END_C_LINKAGE

#endif /* FRICTIONFLOWVALVE_H_ */
