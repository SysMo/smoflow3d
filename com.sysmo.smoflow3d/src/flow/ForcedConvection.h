/*
 * ForcedConvection.h
 *
 *  Created on: Aug 10, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#ifndef FORCEDCONVECTION_H_
#define FORCEDCONVECTION_H_

#include "Convection.h"

#ifdef __cplusplus

class ForcedConvection : public Convection {
public:
	void init(MediumState* fluidState1, MediumState* fluidState2, ThermalNode* wallNode);

	virtual void compute(double massFlowRate);
	virtual void compute_NoHeatFlow();
	void setLimitOutput(bool limitOutput);
	double getReynoldsNumber() {return Re;}

protected:
	virtual double computeNusseltNumber(double Re, double Pr) = 0;
	ForcedConvection();

protected:
	double flowArea;

	MediumState* fluidState2;
	MediumState* limitState;
	bool limitOutput;

	double Re;

	double hydraulicDiameterInjector;
};

#else // __cplusplus
DECLARE_C_STRUCT(ForcedConvection)
#endif //__cplusplus

BEGIN_C_LINKAGE
ForcedConvection* ForcedConvection_GivenConvectionCoefficient_new(double convectionCoefficient, double heatExchangeArea);
ForcedConvection* ForcedConvection_StraightPipe_new(double length, double hydraulicDiameter, double flowArea);
ForcedConvection* ForcedConvection_StraightPipe_NusseltExpression_new(
		double length,
		double hydraulicDiameter,
		double flowArea,
		const char* nusseltExpressionLaminarFlow,
		const char* nusseltExpressionTurbulentFlow,
		double criticalReynoldsNumber_EndLaminarFlow,
		double criticalReynoldsNumber_StartTurbulentFlow,
		double hydraulicDiameterInjector);

ForcedConvection* ForcedConvection_NusseltExpression_new(
		double characteristicLength,
		double flowArea,
		double heatExchangeArea,
		const char* nusseltExpressionLaminarFlow,
		const char* nusseltExpressionTurbulentFlow,
		double criticalReynoldsNumber_EndLaminarFlow,
		double criticalReynoldsNumber_StartTurbulentFlow);

ForcedConvection* ForcedConvection_NusseltExpression_WithInjector_new(
		double characteristicLength,
		double heatExchangeArea,
		const char* nusseltExpressionLaminarFlow,
		const char* nusseltExpressionTurbulentFlow,
		double criticalReynoldsNumber_EndLaminarFlow,
		double criticalReynoldsNumber_StartTurbulentFlow,
		double hydraulicDiameterInjector);

void ForcedConvection_init(ForcedConvection* convection, MediumState* fluidState1, MediumState* fluidState2, ThermalNode* wallNode);
void ForcedConvection_setLimitOutput(ForcedConvection* convection, int limitOutput);
void ForcedConvection_compute(ForcedConvection* convection, double massFlowRate);
double ForcedConvection_getReynoldsNumber(ForcedConvection* convection);
END_C_LINKAGE
#endif /* FORCEDCONVECTION_H_ */
