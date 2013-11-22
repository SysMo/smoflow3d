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
 * Pipe_R - C
 */
Pipe_R* Pipe_R_new(FrictionFlowPipe* friction) {
	return new Pipe_R(friction);
}

Pipe_R* CylindricalStraightPipe_R_new(
		double length,
		double diameter,
		double surfaceRoughness,
		double pressureDropGain) {
	FrictionFlowPipe* friction = FrictionFlowPipe_CylindricalStraightPipe_new(length, diameter, surfaceRoughness);
	friction->setPressureDropGain(pressureDropGain);

	return Pipe_R_new(friction);
}

Pipe_R* NonCylindricalStraightPipe_R_new(
		double length,
		double hydraulicDiameter,
		double flowArea,
		double surfaceRoughness,
		double pressureDropGain) {
	FrictionFlowPipe* friction = FrictionFlowPipe_NonCylindricalStraightPipe_new(length, hydraulicDiameter, flowArea, surfaceRoughness);
	friction->setPressureDropGain(pressureDropGain);

	return Pipe_R_new(friction);
}

Pipe_R* CylindricalElbowPipe_R_new(
		double diameter,
		double surfaceRoughness,
		double curvatureRadius,
		double bendAngle,
		double pressureDropGain) {
	FrictionFlowPipe* friction = FrictionFlowPipe_CylindricalElbowPipe_new(diameter, surfaceRoughness, curvatureRadius, bendAngle);
	friction->setPressureDropGain(pressureDropGain);

	return Pipe_R_new(friction);
}

Pipe_R* NonCylindricalElbowPipe_R_new(
		double hydraulicDiameter,
		double flowArea,
		double surfaceRoughness,
		double curvatureRadius,
		double bendAngle,
		double pressureDropGain) {
	FrictionFlowPipe* friction = FrictionFlowPipe_NonCylindricalElbowPipe_new(hydraulicDiameter, flowArea, surfaceRoughness, curvatureRadius, bendAngle);
	friction->setPressureDropGain(pressureDropGain);

	return Pipe_R_new(friction);
}

double Pipe_R_getDragCoefficient(Pipe_R* pipe) {
	return pipe->getDragCoefficient();
}

double Pipe_R_getReynoldsNumber(Pipe_R* pipe) {
	return pipe->getReynoldsNumber();
}
