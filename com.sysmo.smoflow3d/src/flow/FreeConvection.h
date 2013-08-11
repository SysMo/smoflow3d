/*
 * FreeConvection.h
 *
 *  Created on: Aug 10, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#ifndef FREECONVECTION_H_
#define FREECONVECTION_H_

#include "Convection.h"

#ifdef __cplusplus

class FreeConvectionModel : public ConvectionModel {
public:
	virtual double computeNusseltNumber(double Ra, double Pr) = 0;
	virtual ~FreeConvectionModel(){};
};

class FreeConvection  : public Convection {
public:
	FreeConvection();
	virtual ~FreeConvection();
	void init(MediumState* fluidState, ThermalNode* wallNode,
			FreeConvectionModel* convectionModel);
	void compute();
	double getGrashofNumber() {return Gr;}
	double getRayleighNumber() {return Ra;}
	double getPrandtlNumber() {return Pr;}
protected:
	double lengthScale3;

	FreeConvectionModel* convectionModel;

	double Gr;
	double Ra;
};

#else //__cplusplus
DECLARE_C_STRUCT(FreeConvection)
#endif //__cplusplus

BEGIN_C_LINKAGE
FreeConvection* FreeConvection_new();
void FreeConvection_init(FreeConvection* convection, MediumState* fluidState,
		ThermalNode* wallNode, FreeConvectionModel* convectionModel);
void FreeConvection_compute(FreeConvection* convection);
double FreeConvection_getGrashofNumber(FreeConvection* convection);
double FreeConvection_getRayleighNumber(FreeConvection* convection);
double FreeConvection_getPrandtlNumber(FreeConvection* convection);
double FreeConvection_getNusseltNumber(FreeConvection* convection);
double FreeConvection_getConvectionCoefficient(FreeConvection* convection);
double FreeConvection_getHeatFlowRate(FreeConvection* convection);
void FreeConvection_getFlow_Wall(FreeConvection* convection, HeatFlow* flow);
void FreeConvection_getFlow_Fluid(FreeConvection* convection, FluidFlow* flow);
END_C_LINKAGE

#endif /* FREECONVECTION_H_ */
