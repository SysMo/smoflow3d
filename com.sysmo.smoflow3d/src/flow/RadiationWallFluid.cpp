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
 * RadiationWallFluid - C
 */
RadiationWallFluid* RadiationWallFluid_new(double emissivity, double heatExchangeArea) {
	return new RadiationWallFluid(emissivity, heatExchangeArea);
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
