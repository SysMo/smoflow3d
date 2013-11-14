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
Pipe_R::Pipe_R(FrictionFlowPipe* friction, ForcedConvection* convection) {
	this->friction = friction;
	this->convection = convection;
	if (this->convection != NULL) {
		SMOCOMPONENT_SET_PARENT(this->convection, this);
	}

	this->wallNode = NULL;
}

Pipe_R::~Pipe_R() {
}

void Pipe_R::init(MediumState* state1Input) {
	FlowComponent_R::init(state1Input);
	friction->init(state1, state2);

	if (hasHeatExhcanger()) {
		convection->init(state1, state2, wallNode);
	}
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

	// Compute heat flow rate
	if (hasHeatExhcanger()) {
		convection->compute(massFlowRate);
	}

	// Compute downstream enthalpy
	double downstreamEnthalpy = upstreamState->h();
	if (hasHeatExhcanger()) {
		downstreamEnthalpy += convection->getHeatFlowRate() / m::fabs(massFlowRate);
	}

	// Set downstream state
	MediumState* downstreamState = getDownstreamState(massFlowRate);
	downstreamState->update_ph(downstreamPressure, downstreamEnthalpy);
	return true;
}

bool Pipe_R::hasHeatExhcanger() {
	if (convection == NULL or wallNode == NULL) {
		return false;
	}

	return true;
}


/**
 * Pipe_R - C
 */
Pipe_R* Pipe_R_new(FrictionFlowPipe* friction) {
	return new Pipe_R(friction);
}

Pipe_R* PipeHeatExhcanger_R_new(FrictionFlowPipe* friction, ForcedConvection* convection) {
	return new Pipe_R(friction, convection);
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

Pipe_R* CylindricalStraightPipeHeatExchanger_R_new(
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

Pipe_R* NonCylindricalStraightPipeHeatExchanger_R_new(
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
