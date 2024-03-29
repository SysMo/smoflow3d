/*
 * Convection.cpp
 *
 *  Created on: Aug 10, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "Convection.h"

/**
 * Convection - C++
 */
Convection::Convection() {
	characteristicLength = 0.0;
	heatExchangeArea = 0.0;
	heatExchangeGain = 1.0;

	fluidState = NULL;
	wallNode = NULL;
	filmState = NULL;
	useFilmState = true;

	Pr = 0.0;
	Nu = 0.0;
	convectionCoefficient = 0.0;
	heatFlowRate = 0.0;
}

Convection::~Convection() {
}

void Convection::init(MediumState* fluidState, ThermalNode* wallNode) {
	this->fluidState = fluidState;
	this->wallNode = wallNode;

	this->filmState = MediumState_new(fluidState->getMedium());
	MediumState_register(this->filmState);
}

void Convection::updateHeatFlow(HeatFlow* flow) {
	flow->enthalpyFlowRate = -heatFlowRate;
}

void Convection::updateFluidFlow(FluidFlow* flow) {
	flow->enthalpyFlowRate = heatFlowRate;
	flow->massFlowRate = 0;
}

/**
 * Convection - C
 */
void Convection_setHeatExchangeGain(Convection* convection, double gain) {
	convection->setHeatExchangeGain(gain);
}

double Convection_getPrandtlNumber(Convection* convection) {
	return convection->getPrandtlNumber();
}

double Convection_getNusseltNumber(Convection* convection) {
	return convection->getNusseltNumber();
}

void Convection_setConvectionCoefficient(Convection* convection,
		double convectionCoefficient) {
	convection->setConvectionCoefficient(convectionCoefficient);
}

double Convection_getConvectionCoefficient(Convection* convection) {
	return convection->getConvectionCoefficient();
}

double Convection_getHeatFlowRate(Convection* convection) {
	return convection->getHeatFlowRate();
}
void Convection_updateHeatFlow(Convection* convection, HeatFlow* flow) {
	convection->updateHeatFlow(flow);
}

void Convection_updateFluidFlow(Convection* convection, FluidFlow* flow) {
	convection->updateFluidFlow(flow);
}

void Convection_setUseFilmState(Convection* convection, int useFilmState) {
	convection->setUseFilmState(useFilmState);
}

