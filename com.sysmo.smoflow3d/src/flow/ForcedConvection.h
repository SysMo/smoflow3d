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

class ForcedConvectionModel : public ConvectionModel {
public:
	virtual double getFlowArea() = 0;
	virtual double computeNusseltNumber(double Re, double Pr) = 0;
	virtual ~ForcedConvectionModel(){};
};

class ForcedConvection : public Convection {
public:
	ForcedConvection();
	virtual ~ForcedConvection();
	void init(MediumState* fluidState, ThermalNode* wallNode,
			ForcedConvectionModel* convectionModel, FluidFlow* flow);
	void compute();
protected:
	double flowArea;

	ForcedConvectionModel* convectionModel;
	FluidFlow* flow;

	double Re;
};

#else // __cplusplus
DECLARE_C_STRUCT(ForcedConvectionModel)
DECLARE_C_STRUCT(ForcedConvection)
#endif //__cplusplus

BEGIN_C_LINKAGE
ForcedConvection* ForcedConvection_new();
void ForcedConvection_init(ForcedConvection* convection, MediumState* fluidState,
		ThermalNode* wallNode, ForcedConvectionModel* convectionModel, FluidFlow* flow);
void ForcedConvection_compute(ForcedConvection* convection);
END_C_LINKAGE

#endif /* FORCEDCONVECTION_H_ */
