/*
 * Radiation.cpp
 *
 *  Created on: Oct 26, 2016
 *      Author: Atanas Pavlov, Milen Borisov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "Radiation.h"

/**
 * Radiation - C++
 */
Radiation::Radiation() {
	heatExchangeGain = 1.0;

	fluidState = NULL;
	wallNode = NULL;

	heatFlowRate = 0.0;
}

Radiation::~Radiation() {
}

void Radiation::init(MediumState* fluidState, ThermalNode* wallNode) {
	this->fluidState = fluidState;
	this->wallNode = wallNode;
}

void Radiation::updateHeatFlow(HeatFlow* flow) {
	flow->enthalpyFlowRate = -heatFlowRate;
}

void Radiation::updateFluidFlow(FluidFlow* flow) {
	flow->enthalpyFlowRate = heatFlowRate;
	flow->massFlowRate = 0;
}

/**
 * Radiation - C
 */
void Radiation_setHeatExchangeGain(Radiation* radiation, double gain) {
	radiation->setHeatExchangeGain(gain);
}

double Radiation_getHeatFlowRate(Radiation* radiation) {
	return radiation->getHeatFlowRate();
}
void Radiation_updateHeatFlow(Radiation* radiation, HeatFlow* flow) {
	radiation->updateHeatFlow(flow);
}

void Radiation_updateFluidFlow(Radiation* radiation, FluidFlow* flow) {
	radiation->updateFluidFlow(flow);
}
