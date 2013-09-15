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

class FreeConvection  : public Convection {
public:
	FreeConvection();
	virtual ~FreeConvection();

	void init(MediumState* fluidState, ThermalNode* wallNode);

	virtual void compute();
	virtual double computeNusseltNumber(double Ra, double Pr, double wallOverheat) = 0;
	double getGrashofNumber() {return Gr;}
	double getRayleighNumber() {return Ra;}

protected:
	double Gr;
	double Ra;
};

#else //__cplusplus
DECLARE_C_STRUCT(FreeConvection)
#endif //__cplusplus

BEGIN_C_LINKAGE
void FreeConvection_init(FreeConvection* convection, MediumState* fluidState, ThermalNode* wallNode);
void FreeConvection_compute(FreeConvection* convection);
double FreeConvection_getGrashofNumber(FreeConvection* convection);
double FreeConvection_getRayleighNumber(FreeConvection* convection);

FreeConvection* FreeConvection_GivenConvectionCoefficient_new(
		double convectionCoefficient, double heatExchangeArea);
FreeConvection* FreeConvection_NusseltExpression_new(
		double characteristicLength, double heatExchangeArea, const char* nusseltExpression);
FreeConvection* FreeConvection_VerticalSurface_new(
		double height, double width);
FreeConvection* FreeConvection_InclinedSurface_new(
		double length, double width, double angleOfInclination);
FreeConvection* FreeConvection_HorizontalSurfaceTop_new(
		double length, double width);
FreeConvection* FreeConvection_HorizontalSurfaceBottom_new(
		double length, double width);
FreeConvection* FreeConvection_CylindricalHorizontalSurface_new(
		double length, double diameter);
FreeConvection* FreeConvection_CylindricalVerticalSurface_new(
		double height, double diameter);
FreeConvection* FreeConvection_SphericalSurface_new(
		double diameter);
FreeConvection* FreeConvection_FinnedPipe_new(double pipeDiameter, double pipeLength,
		double finSpacing, double finThickness, double finHeight);
END_C_LINKAGE

#endif /* FREECONVECTION_H_ */
