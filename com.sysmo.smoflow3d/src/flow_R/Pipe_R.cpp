/*
 * Pipe_R.cpp
 *
 *  Created on: Sep 19, 2014
 *      Author: Milen Borisov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "Pipe_R.h"
using namespace smoflow;

/**
 * Pipe_R - C++
 */
Pipe_R::Pipe_R(FrictionFlowPipe* friction) {
	this->friction = friction;
}

Pipe_R::~Pipe_R() {
}

void Pipe_R::init(MediumState* state1Input) {
	FlowComponent_R::init(state1Input);
	friction->init(state1, state2);
}

bool Pipe_R::compute(double massFlowRate, double minDownstreamPressure) {
	// Compute pressure drop
	friction->computePressureDrop(massFlowRate);

	// Try to compute downstream pressure
	MediumState* upstreamState = getUpstreamState(massFlowRate);
	double downstreamPressure = upstreamState->p() - friction->getAbsolutePressureDrop();
	if (downstreamPressure < minDownstreamPressure or downstreamPressure <= 0.0) {
		return false;
	}

	// Compute downstream enthalpy
	double downstreamEnthalpy = upstreamState->h();

	// Set downstream state
	MediumState* downstreamState = getDownstreamState(massFlowRate);
	downstreamState->update_ph(downstreamPressure, downstreamEnthalpy);
	return true;
}

/**
 * PipeHeatExchanger_R - C++
 */
PipeHeatExchanger_R::PipeHeatExchanger_R(FrictionFlowPipe* friction, ForcedConvection* convection) :
		Pipe_R(friction) {
	this->convection = convection;
	SMOCOMPONENT_SET_PARENT(this->convection, this);

	wallHeatFlow = HeatFlow_new();
	HeatFlow_register(wallHeatFlow);

	wallNode = NULL;
}

PipeHeatExchanger_R::~PipeHeatExchanger_R() {
}

void PipeHeatExchanger_R::init(MediumState* state1Input) {
	Pipe_R::init(state1Input);
	convection->init(state1, state2, wallNode);
}

bool PipeHeatExchanger_R::compute(double massFlowRate, double minDownstreamPressure) {
	// Compute pressure drop
	friction->computePressureDrop(massFlowRate);

	// Try to compute downstream pressure
	MediumState* upstreamState = getUpstreamState(massFlowRate);
	double downstreamPressure = upstreamState->p() - friction->getAbsolutePressureDrop();
	if (downstreamPressure < minDownstreamPressure or downstreamPressure <= 0.0) {
		return false;
	}

	// Compute heat flow rate
	convection->compute(massFlowRate);
	convection->updateHeatFlow(wallHeatFlow);

	// Compute downstream enthalpy
	double downstreamEnthalpy = upstreamState->h() + convection->getHeatFlowRate() / m::fabs(massFlowRate);

	// Set downstream state
	MediumState* downstreamState = getDownstreamState(massFlowRate);
	downstreamState->update_ph(downstreamPressure, downstreamEnthalpy);
	return true;
}

/**
 * Pipe_R - C
 */
Pipe_R* Pipe_R_new(FrictionFlowPipe* friction) {
	return new Pipe_R(friction);
}

Pipe_R* CylindricalStraightPipe_R_new(
		double diameter,
		double length,
		double surfaceRoughness,
		double pressureDropGain) {
	FrictionFlowPipe* friction = FrictionFlowPipe_StraightPipe_new(diameter, length, surfaceRoughness);
	friction->setPressureDropGain(pressureDropGain);

	return Pipe_R_new(friction);
}

/**
 * PipeHeatExchanger_R - C
 */
PipeHeatExchanger_R* PipeHeatExhcanger_R_new(FrictionFlowPipe* friction, ForcedConvection* convection) {
	return new PipeHeatExchanger_R(friction, convection);
}

PipeHeatExchanger_R* CylindricalStraightPipeHeatExchanger_R_new(
		double diameter,
		double length,
		double surfaceRoughness,
		double pressureDropGain,
		double heatExchangeGain,
		int heatExchangerLimitOutput) {
	FrictionFlowPipe* friction = FrictionFlowPipe_StraightPipe_new(diameter, length, surfaceRoughness);
	friction->setPressureDropGain(pressureDropGain);

	double flowArea = M_PI / 4 * diameter * diameter;
	ForcedConvection* convection = ForcedConvection_StraightPipe_new(diameter, flowArea, length);
	convection->setHeatExchangeGain(heatExchangeGain);
	if (heatExchangerLimitOutput == 1) {
		convection->setLimitOutput(true);
	} else {
		convection->setLimitOutput(false);
	}

	return PipeHeatExhcanger_R_new(friction, convection);
}

PipeHeatExchanger_R* NonCylindricalStraightPipeHeatExchanger_R_new(
		double hydraulicDiameter,
		double length,
		double flowArea,
		double surfaceRoughness,
		double pressureDropGain,
		double heatExchangeGain,
		int heatExchangerLimitOutput) {
	FrictionFlowPipe* friction = FrictionFlowPipe_StraightPipe_new(hydraulicDiameter, length, surfaceRoughness);
	friction->setPressureDropGain(pressureDropGain);

	ForcedConvection* convection = ForcedConvection_StraightPipe_new(hydraulicDiameter, flowArea, length);
	convection->setHeatExchangeGain(heatExchangeGain);
	if (heatExchangerLimitOutput == 1) {
		convection->setLimitOutput(true);
	} else {
		convection->setLimitOutput(false);
	}


	return PipeHeatExhcanger_R_new(friction, convection);
}

HeatFlow* PipeHeatExchanger_R_getWallHeatFlow(PipeHeatExchanger_R* pipe) {
	return pipe->getWallHeatFlow();
}

ForcedConvection* PipeHeatExchanger_R_getConvection(PipeHeatExchanger_R* pipe) {
	return pipe->getConvection();
}

void PipeHeatExchanger_R_setHeatExchangerThermalNode(PipeHeatExchanger_R* pipe, ThermalNode* wallNode) {
	pipe->setHeatExchangerThermalNode(wallNode);
}
