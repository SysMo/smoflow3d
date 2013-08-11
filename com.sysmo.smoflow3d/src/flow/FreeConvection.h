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
	virtual double computeNusseltNumber(double Ra, double Pr, double wallOverheat) = 0;
	virtual ~FreeConvectionModel(){};
};

class FreeConvection  : public Convection {
public:
	FreeConvection(FreeConvectionModel* convectionModel);
	virtual ~FreeConvection();
	void init(MediumState* fluidState, ThermalNode* wallNode);
	void setParametersDirectly(double heatExchangeArea,
			double convectionCoefficient);
	void compute();
	double getGrashofNumber() {return Gr;}
	double getRayleighNumber() {return Ra;}
	double getPrandtlNumber() {return Pr;}
protected:
	double characteristicLength3;

	FreeConvectionModel* convectionModel;

	double Gr;
	double Ra;
};

#else //__cplusplus
DECLARE_C_STRUCT(FreeConvectionModel)
DECLARE_C_STRUCT(FreeConvection)
#endif //__cplusplus

BEGIN_C_LINKAGE
FreeConvection* FreeConvection_new(FreeConvectionModel* convectionModel);
void FreeConvection_setParametersDirectly(FreeConvection* convection,
		double heatExchangeArea, double convectionCoefficient);
void FreeConvection_setHeatExchangeGain(FreeConvection* convection, double gain);
void FreeConvection_init(FreeConvection* convection, MediumState* fluidState,
		ThermalNode* wallNode);
void FreeConvection_compute(FreeConvection* convection);
double FreeConvection_getGrashofNumber(FreeConvection* convection);
double FreeConvection_getRayleighNumber(FreeConvection* convection);
double FreeConvection_getPrandtlNumber(FreeConvection* convection);
double FreeConvection_getNusseltNumber(FreeConvection* convection);
double FreeConvection_getConvectionCoefficient(FreeConvection* convection);
double FreeConvection_getHeatFlowRate(FreeConvection* convection);
void FreeConvection_getFlow_Wall(FreeConvection* convection, HeatFlow* flow);
void FreeConvection_getFlow_Fluid(FreeConvection* convection, FluidFlow* flow);

FreeConvectionModel* FreeConvectionModel_NusseltExpression_new(
		double characteristicLength, double heatExchangeArea, const char* nusseltExpression);
FreeConvectionModel* FreeConvectionModel_VerticalSurface_new(
		double height, double width);
FreeConvectionModel* FreeConvectionModel_HorizontalSurfaceTop_new(
		double length, double width);
FreeConvectionModel* FreeConvectionModel_HorizontalSurfaceBottom_new(
		double length, double width);
FreeConvectionModel* FreeConvectionModel_CylindricalHorizontalSurface_new(
		double length, double diameter);

END_C_LINKAGE

#endif /* FREECONVECTION_H_ */
