/*
 * RadiationWallFluid.h
 *
 *  Created on: Oct 26, 2016
 *      Author: Atanas Pavlov, Milen Borisov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#ifndef RADIATION_WALL_FLUID_H_
#define RADIATION_WALL_FLUID_H_

#include "Radiation.h"

#ifdef __cplusplus

class RadiationWallFluid : public Radiation {
public:
	RadiationWallFluid(double emissivity, double heatExchangeArea);
	virtual ~RadiationWallFluid();

	void init(MediumState* fluidState, ThermalNode* wallNode);

	virtual void compute();

	void updateHeatFlow(HeatFlow* flow); //heat flow to the wall
	void updateFluidFlow(FluidFlow* flow); //fluid flow to the fluid

	double getEmissivity() {return emissivity;}

protected:
	double heatExchangeArea;
	double emissivity;

	MediumState* fluidState;
	ThermalNode* wallNode;
};

class RadiationWallFluid_VariableEmissivity : public RadiationWallFluid{
public:
	RadiationWallFluid_VariableEmissivity(const char* emissivityVar, double heatExchangeArea);
	virtual ~RadiationWallFluid_VariableEmissivity();

	virtual void compute();

protected:
	FunctorOneVariable* emissivityFunction;
	FunctorCache* emissivityCache;
};

#else //__cplusplus
DECLARE_C_STRUCT(RadiationWallFluid)
#endif //__cplusplus

BEGIN_C_LINKAGE
RadiationWallFluid* RadiationWallFluid_new(double emissivity, double heatExchangeArea);
RadiationWallFluid* RadiationWallFluid_VariableEmissivity_new(const char* emissivityVar, double heatExchangeArea);

void RadiationWallFluid_init(RadiationWallFluid* radiation, MediumState* fluidState, ThermalNode* wallNode);
void RadiationWallFluid_compute(RadiationWallFluid* radiation);

void RadiationWallFluid_updateHeatFlow(RadiationWallFluid* radiation, HeatFlow* flow);
void RadiationWallFluid_updateFluidFlow(RadiationWallFluid* radiation, FluidFlow* flow);

double RadiationWallFluid_getEmissivity(RadiationWallFluid* radiation);

END_C_LINKAGE

#endif /* RADIATION_WALL_FLUID_H_ */
