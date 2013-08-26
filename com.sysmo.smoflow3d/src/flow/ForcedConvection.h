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
	void init(MediumState* fluidState1, MediumState* fluidState2,
			ThermalNode* wallNode);
	void setLimitOutput(bool limitOutput);
	virtual void compute(double massFlowRate);
	double getReynoldsNumber() {return Re;}
protected:
	virtual double computeNusseltNumber(double Re, double Pr) = 0;
	double flowArea;

	MediumState* fluidState2;
	bool limitOutput;
	MediumState* limitState;

	double Re;
};

#else // __cplusplus
DECLARE_C_STRUCT(ForcedConvection)
#endif //__cplusplus

BEGIN_C_LINKAGE
void ForcedConvection_init(ForcedConvection* convection,
		MediumState* fluidState1, MediumState* fluidState2,
		ThermalNode* wallNode);
void ForcedConvection_setLimitOutput(ForcedConvection* convection, int limitOutput);
void ForcedConvection_compute(ForcedConvection* convection, double massFlowRate);
double ForcedConvection_getReynoldsNumber(ForcedConvection* convection);

ForcedConvection* ForcedConvection_GivenConvectionCoefficient_new(
		double heatExchangeArea);
ForcedConvection* ForcedConvection_StraightPipe_new(
		double hydraulicDiameter, double flowArea, double pipeLength);
END_C_LINKAGE
#endif /* FORCEDCONVECTION_H_ */