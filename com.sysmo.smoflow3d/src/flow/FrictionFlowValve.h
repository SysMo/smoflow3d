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

typedef enum {
	sFlowType_Undefine = -1,
	sFlowType_Subsonic = 0,
	sFlowType_Sonic = 1
} FlowType;

class FrictionFlowValve {
public:
	FrictionFlowValve(int allowBidirectionalFlow, int limitRegulatingSignal = 0);
	virtual ~FrictionFlowValve();

	void init(MediumState* state1, MediumState* state2);
	void setRegulatingSignal(double regulatingSignal) {this->regulatingSignal = regulatingSignal;}
	double getRegulatingSignal() {return regulatingSignal;}

	virtual double computePressureDrop(double massFlowRate) = 0;
	virtual double computeMassFlowRate(double pressureDrop) = 0;
	double computeMassFlowRate_NoFluidFlow(double pressureDrop);

	void updateFluidFlows(FluidFlow* flow1, FluidFlow* flow2);

	double getAbsolutePressureDrop() {return absPressureDrop;}
	double getMassFlowRate() {return massFlowRate;}
	FlowType getFlowType() {return flowType;}

	bool isBidirectionalFlowAllowed() {return allowBidirectionalFlow == 1;}
	bool isRegulatingSignalLimited() {return limitRegulatingSignal == 1;}

protected:
	MediumState* getUpstreamState(double massFlowRate);
	MediumState* getUpstreamState(int flowDirection);
	MediumState* getDownstreamState(int flowDirection);

protected:
	double regulatingSignal;

	double massFlowRate;
	double absPressureDrop;

	FlowType flowType;

private:
	int allowBidirectionalFlow; //0 - no; 1 - yes
	int limitRegulatingSignal; //0 - no; 1 - yes

	MediumState* state1;
	MediumState* state2;
};

#else //__cplusplus
DECLARE_C_STRUCT(FrictionFlowValve)
#endif //__cplusplus

BEGIN_C_LINKAGE
FrictionFlowValve* FrictionFlowValve_InputPressureLoss_new(
		int allowBidirectionalFlow);

FrictionFlowValve* FrictionFlowValve_InputMassFlowRate_new(
		int allowBidirectionalFlow, int useAsPump);

FrictionFlowValve* FrictionFlowValve_Kv_new(
		int allowBidirectionalFlow,
		double Kv,
		int transitionChoice,
		double transitionMassFlowRate,
		double transitionPressureDifference,
		double maximumMassFlowRate,
		int limitRegulatingSignal);

FrictionFlowValve* FrictionFlowValve_OrificeCompressibleIdealGas_new(
		int allowBidirectionalFlow,
		double orificeArea,
		double flowCoefficient);

FrictionFlowValve* FrictionFlowValve_OrificeCompressibleRealGas_new(
		int allowBidirectionalFlow,
		double orificeArea,
		double flowCoefficient);

END_C_LINKAGE

#endif /* FRICTIONFLOWVALVE_H_ */
