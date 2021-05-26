/*
 * RadiationTwoSurfaces.cpp
 *
 *  Created on: Feb 13, 2020
 *      Author: Atanas Pavlov, Milen Borisov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "util/String.h"
#include "math/Interpolators.h"
#include "util/CommonDefinitions.h"
#include "RadiationTwoSurfaces.h"

using namespace smoflow;

/**
 * RadiationTwoSurfaces - C++
 */
RadiationTwoSurfaces::RadiationTwoSurfaces(
		double emissivity1, double emissivity2,
		double heatExchangeArea1, double heatExchangeArea2,
		double shapeFactor12) {
	this->emissivity1 = emissivity1;
	this->emissivity2 = emissivity2;
	this->heatExchangeArea1 = heatExchangeArea1;
	this->heatExchangeArea2 = heatExchangeArea2;
	this->shapeFactor12 = shapeFactor12;

	this->wallNode1 = NULL;
	this->wallNode2 = NULL;
}

RadiationTwoSurfaces::~RadiationTwoSurfaces() {
}

void RadiationTwoSurfaces::init(ThermalNode* wallNode1, ThermalNode* wallNode2) {
	this->wallNode1 = wallNode1;
	this->wallNode2 = wallNode2;
}

void RadiationTwoSurfaces::compute() {
	double wallTemperature1 = wallNode1->getTemperature();
	double wallTemperature2 = wallNode2->getTemperature();

	// Calculate the heat flow rate (from wall to the fluid)
	heatFlowRate = heatExchangeGain * cst::StefanBoltzmannConstant *
			(m::pow(wallTemperature1, 4) - m::pow(wallTemperature2, 4)) /
			(
					(1 - emissivity1)/(heatExchangeArea1*emissivity1) +
					(1/(heatExchangeArea1*shapeFactor12)) +
					(1 - emissivity2)/(heatExchangeArea2*emissivity2)
			);
}

void RadiationTwoSurfaces::updateHeatFlow1(HeatFlow* flow1) {
	flow1->enthalpyFlowRate = -heatFlowRate;
}

void RadiationTwoSurfaces::updateHeatFlow2(HeatFlow* flow2) {
	flow2->enthalpyFlowRate = heatFlowRate;
}


/**
 * RadiationTwoSurfaces_VariableEmissivity - C++
 */
RadiationTwoSurfaces_VariableEmissivity::RadiationTwoSurfaces_VariableEmissivity(
		const char* emissivity1Var, const char* emissivity2Var,
		double heatExchangeArea1, double heatExchangeArea2,
		double shapeFactor12) :
				RadiationTwoSurfaces(
						0, 0, //:TRICKY: not used in the initialization
						heatExchangeArea1, heatExchangeArea2,
						shapeFactor12) {

	double emissivity1Const;
	if (smoflow::String::toDouble(emissivity1Var, &emissivity1Const)) {
		emissivity1Function = FunctorOneVariable_Constant_new(emissivity1Const);
	} else {
		Interpolator1D::createFromCsvFile(emissivity1Var, &emissivity1Function);
	}
	emissivity1Cache = emissivity1Function->createCache();

	double emissivity2Const;
	if (smoflow::String::toDouble(emissivity2Var, &emissivity2Const)) {
		emissivity2Function = FunctorOneVariable_Constant_new(emissivity2Const);
	} else {
		Interpolator1D::createFromCsvFile(emissivity2Var, &emissivity2Function);
	}
	emissivity2Cache = emissivity2Function->createCache();
}

RadiationTwoSurfaces_VariableEmissivity::~RadiationTwoSurfaces_VariableEmissivity() {
}


void RadiationTwoSurfaces_VariableEmissivity::compute() {
	emissivity1 = (*emissivity1Function)(wallNode1->getTemperature(), emissivity1Cache);
	emissivity2 = (*emissivity2Function)(wallNode2->getTemperature(), emissivity2Cache);

	RadiationTwoSurfaces::compute();
}

/**
 * RadiationTwoSurfaces - C
 */
RadiationTwoSurfaces* RadiationTwoSurfaces_new(
		double emissivity1, double emissivity2,
		double heatExchangeArea1, double heatExchangeArea2,
		double shapeFactor12) {
	return new RadiationTwoSurfaces(
			emissivity1, emissivity2,
			heatExchangeArea1, heatExchangeArea2,
			shapeFactor12);
}

RadiationTwoSurfaces* RadiationTwoSurfaces_VariableEmissivity_new(
		const char* emissivity1Var, const char* emissivity2Var,
		double heatExchangeArea1, double heatExchangeArea2,
		double shapeFactor12) {
	return new RadiationTwoSurfaces_VariableEmissivity(
			emissivity1Var, emissivity2Var,
			heatExchangeArea1, heatExchangeArea2,
			shapeFactor12);
}

void RadiationTwoSurfaces_init(RadiationTwoSurfaces* radiation, ThermalNode* wallNode1, ThermalNode* wallNode2) {
	radiation->init(wallNode1, wallNode2);
}

void RadiationTwoSurfaces_compute(RadiationTwoSurfaces* radiation) {
	radiation->compute();
}

void RadiationTwoSurfaces_updateHeatFlow1(RadiationTwoSurfaces* radiation, HeatFlow* flow1) {
	radiation->updateHeatFlow1(flow1);
}

void RadiationTwoSurfaces_updateHeatFlow2(RadiationTwoSurfaces* radiation, HeatFlow* flow2) {
	radiation->updateHeatFlow2(flow2);
}

double RadiationTwoSurfaces_getEmissivity1(RadiationTwoSurfaces* radiation) {
	return radiation->getEmissivity1();
}

double RadiationTwoSurfaces_getEmissivity2(RadiationTwoSurfaces* radiation) {
	return radiation->getEmissivity2();
}
