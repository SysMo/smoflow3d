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
	ForcedConvection();
	virtual ~ForcedConvection();
	void init(MediumState* fluidState,
			ThermalNode* wallNode, FluidFlow* flow);
	virtual void compute();
	double getReynoldsNumber() {return Re;}
protected:
	virtual double computeNusseltNumber(double Re, double Pr) = 0;
	double flowArea;

	FluidFlow* flow;

	double Re;
};

#else // __cplusplus
DECLARE_C_STRUCT(ForcedConvectionModel)
DECLARE_C_STRUCT(ForcedConvection)
#endif //__cplusplus

BEGIN_C_LINKAGE
void ForcedConvection_init(ForcedConvection* convection, MediumState* fluidState,
		ThermalNode* wallNode, FluidFlow* flow);
void ForcedConvection_setHeatExchangeGain(ForcedConvection* convection, double gain);

void ForcedConvection_compute(ForcedConvection* convection);
double ForcedConvection_getReynoldsNumber(ForcedConvection* convection);

ForcedConvection* ForcedConvection_GivenConvectionCoefficient_new(
		double heatExchangeArea);
ForcedConvection* ForcedConvection_StraightPipe_new(
		double hydraulicDiameter, double flowArea, double pipeLength);
END_C_LINKAGE
#endif /* FORCEDCONVECTION_H_ */
