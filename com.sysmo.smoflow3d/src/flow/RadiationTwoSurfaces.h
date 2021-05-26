/*
 * RadiationTwoSurfaces.h
 *
 *  Created on: Feb 13, 2020
 *      Author: Atanas Pavlov, Milen Borisov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#ifndef RADIATION_TWO_SURFACES_H_
#define RADIATION_TWO_SURFACES_H_

#include "Radiation.h"

#ifdef __cplusplus

class RadiationTwoSurfaces  : public Radiation {
public:
	RadiationTwoSurfaces(
			double emissivity1, double emissivity2,
			double heatExchangeArea1, double heatExchangeArea2,
			double shapeFactor12);
	virtual ~RadiationTwoSurfaces();

	void init(ThermalNode* wallNode1, ThermalNode* wallNode2);

	virtual void compute();

	void updateHeatFlow1(HeatFlow* flow1);
	void updateHeatFlow2(HeatFlow* flow2);

	double getEmissivity1() {return emissivity1;}
	double getEmissivity2() {return emissivity2;}

protected:
	double emissivity1;
    double emissivity2;
    double heatExchangeArea1;
    double heatExchangeArea2;
    double shapeFactor12;

	ThermalNode* wallNode1;
	ThermalNode* wallNode2;
};

class RadiationTwoSurfaces_VariableEmissivity  : public RadiationTwoSurfaces {
public:
	RadiationTwoSurfaces_VariableEmissivity(
			const char* emissivity1Var, const char* emissivity2Var,
			double heatExchangeArea1, double heatExchangeArea2,
			double shapeFactor12);

	virtual ~RadiationTwoSurfaces_VariableEmissivity();
	virtual void compute();

protected:
	FunctorOneVariable* emissivity1Function;
	FunctorCache* emissivity1Cache;

	FunctorOneVariable* emissivity2Function;
	FunctorCache* emissivity2Cache;
};

#else //__cplusplus
DECLARE_C_STRUCT(RadiationTwoSurfaces)
#endif //__cplusplus

BEGIN_C_LINKAGE
RadiationTwoSurfaces* RadiationTwoSurfaces_new(
		double emissivity1, double emissivity2,
		double heatExchangeArea1, double heatExchangeArea2,
		double shapeFactor12);

RadiationTwoSurfaces* RadiationTwoSurfaces_VariableEmissivity_new(
		const char* emissivity1Var, const char* emissivity2Var,
		double heatExchangeArea1, double heatExchangeArea2,
		double shapeFactor12);

void RadiationTwoSurfaces_init(RadiationTwoSurfaces* radiation, ThermalNode* wallNode1, ThermalNode* wallNode2);
void RadiationTwoSurfaces_compute(RadiationTwoSurfaces* radiation);

void RadiationTwoSurfaces_updateHeatFlow1(RadiationTwoSurfaces* radiation, HeatFlow* flow1);
void RadiationTwoSurfaces_updateHeatFlow2(RadiationTwoSurfaces* radiation, HeatFlow* flow2);

double RadiationTwoSurfaces_getEmissivity1(RadiationTwoSurfaces* radiation);
double RadiationTwoSurfaces_getEmissivity2(RadiationTwoSurfaces* radiation);

END_C_LINKAGE

#endif /* RADIATION_TWO_SURFACES_H_ */
