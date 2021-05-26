/*
 * RadiationWallFluid.cpp
 *
 *  Created on: Oct 26, 2016
 *      Author: Atanas Pavlov, Milen Borisov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "util/String.h"
#include "math/Interpolators.h"
#include "util/CommonDefinitions.h"
#include "RadiationWallFluid.h"

using namespace smoflow;

/**
 * RadiationWallFluid - C++
 */
RadiationWallFluid::RadiationWallFluid(double emissivity, double heatExchangeArea) {
	this->emissivity = emissivity;
	this->heatExchangeArea = heatExchangeArea;

	this->fluidState = NULL;
	this->wallNode = NULL;
}

RadiationWallFluid::~RadiationWallFluid() {
}

void RadiationWallFluid::init(MediumState* fluidState, ThermalNode* wallNode) {
	this->fluidState = fluidState;
	this->wallNode = wallNode;
}

void RadiationWallFluid::compute() {
	double fluidTemperature = fluidState->T();
	double wallTemperature = wallNode->getTemperature();

	// Calculate the heat flow rate (from wall to the fluid)
	heatFlowRate = heatExchangeGain * emissivity * cst::StefanBoltzmannConstant * heatExchangeArea *
			(m::pow(wallTemperature, 4) - m::pow(fluidTemperature, 4)) ;
}

void RadiationWallFluid::updateHeatFlow(HeatFlow* flow) {
	flow->enthalpyFlowRate = -heatFlowRate;
}

void RadiationWallFluid::updateFluidFlow(FluidFlow* flow) {
	flow->enthalpyFlowRate = heatFlowRate;
	flow->massFlowRate = 0;
}


/**
 * RadiationWallFluid_VariableEmissivity - C++
 */
RadiationWallFluid_VariableEmissivity::RadiationWallFluid_VariableEmissivity(
		const char* emissivityVar, double heatExchangeArea) :
		RadiationWallFluid(0, heatExchangeArea) {//:TRICKY: emissivity is not used during the initialization
	double emissivityConst;
	if (smoflow::String::toDouble(emissivityVar, &emissivityConst)) {
		emissivityFunction = FunctorOneVariable_Constant_new(emissivityConst);
	} else {
		Interpolator1D::createFromCsvFile(emissivityVar, &emissivityFunction);
	}
	emissivityCache = emissivityFunction->createCache();
}

RadiationWallFluid_VariableEmissivity::~RadiationWallFluid_VariableEmissivity() {
}

void RadiationWallFluid_VariableEmissivity::compute() {
	emissivity = (*emissivityFunction)(wallNode->getTemperature(), emissivityCache);

	RadiationWallFluid::compute();
}


/**
 * RadiationWallFluid - C
 */
RadiationWallFluid* RadiationWallFluid_new(double emissivity, double heatExchangeArea) {
	return new RadiationWallFluid(emissivity, heatExchangeArea);
}

RadiationWallFluid* RadiationWallFluid_VariableEmissivity_new(
		const char* emissivityVar, double heatExchangeArea) {
	return new RadiationWallFluid_VariableEmissivity(emissivityVar, heatExchangeArea);
}

void RadiationWallFluid_init(RadiationWallFluid* radiation, MediumState* fluidState, ThermalNode* wallNode) {
	radiation->init(fluidState, wallNode);
}

void RadiationWallFluid_compute(RadiationWallFluid* radiation) {
	radiation->compute();
}

void RadiationWallFluid_updateHeatFlow(RadiationWallFluid* radiation, HeatFlow* flow) {
	radiation->updateHeatFlow(flow);
}

void RadiationWallFluid_updateFluidFlow(RadiationWallFluid* radiation, FluidFlow* flow) {
	radiation->updateFluidFlow(flow);
}

double RadiationWallFluid_getEmissivity(RadiationWallFluid* radiation) {
	return radiation->getEmissivity();
}
