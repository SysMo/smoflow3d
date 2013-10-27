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

void Pipe_R::init(MediumState* state1, MediumState* state2) {
	Component_R::init(state1, state2);
	friction->init(state1, state2);
}

bool Pipe_R::compute(double massFlowRate, double minDownstreamPressure) {
	// Compute absolute pressure drop
	friction->computePressureDrop(massFlowRate);
	double absPressureDrop = friction->getAbsolutePressureDrop();

	// Compute downstream enthalpy
	MediumState* upstreamState = getUpstreamState(massFlowRate);
	double downstreamEnthalpy = upstreamState->h();

	// Try to compute downstream pressure
	double downstreamPressure = upstreamState->p() - absPressureDrop;
	if (downstreamPressure < minDownstreamPressure or downstreamPressure <= 0.0) {
		return false;
	}

	// Set downstream state
	MediumState* downstreamState = getDownstreamState(massFlowRate);
	downstreamState->update_ph(downstreamPressure, downstreamEnthalpy);
	return true;
}

/**
 * TwoPortValve - C
 */
Pipe_R* Pipe_R_new(FrictionFlowPipe* friction) {
	return new Pipe_R(friction);
}
