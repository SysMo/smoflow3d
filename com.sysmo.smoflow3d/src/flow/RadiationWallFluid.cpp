/*
 * RadiationWallFluid.cpp
 *
 *  Created on: Oct 26, 2016
 *      Author: Atanas Pavlov, Milen Borisov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "RadiationWallFluid.h"
#include "math/Functors.h"
#include "util/CommonDefinitions.h"

using namespace smoflow;

/**
 * RadiationWallFluid - C++
 */
RadiationWallFluid::RadiationWallFluid(double emissivity, double heatExchangeArea) {
	this->emissivity = emissivity;
	this->heatExchangeArea = heatExchangeArea;
}

RadiationWallFluid::~RadiationWallFluid() {
}

void RadiationWallFluid::init(MediumState* fluidState, ThermalNode* wallNode) {
	Radiation::init(fluidState, wallNode);
}

void RadiationWallFluid::compute() {
	double fluidTemperature = fluidState->T();
	double wallTemperature = wallNode->getTemperature();

	// Calculate the heat flow rate (from wall to the fluid)
	heatFlowRate = heatExchangeGain * emissivity * cst::StefanBoltzmannConstant * heatExchangeArea *
			(m::pow(wallTemperature, 4) - m::pow(fluidTemperature, 4)) ;
}

/**
 * RadiationWallFluid - C
 */
void RadiationWallFluid_init(RadiationWallFluid* radiation, MediumState* fluidState, ThermalNode* wallNode) {
	radiation->init(fluidState, wallNode);
}

void RadiationWallFluid_compute(RadiationWallFluid* radiation) {
	radiation->compute();
}

RadiationWallFluid* RadiationWallFluid_new(double emissivity, double heatExchangeArea) {
	return new RadiationWallFluid(emissivity, heatExchangeArea);
}
