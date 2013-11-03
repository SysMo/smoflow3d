/*
 * Valve_R.cpp
 *
 *  Created on: Sep 19, 2014
 *      Author: Milen Borisov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "Valve_R.h"
using namespace smoflow;

/**
 * Valve_R - C++
 */
Valve_R::Valve_R(FrictionFlowValve* friction) {
	this->friction = friction;
}

Valve_R::~Valve_R() {
}

void Valve_R::init(MediumState* state1, MediumState* state2) {
	Component_R::init(state1, state2);
	friction->init(state1, state2);
}

bool Valve_R::compute(double massFlowRate, double minDownstreamPressure) {
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

void Valve_R::setRegulatingSignal(double regulatingSignal) {
	friction->setRegulatingSignal(regulatingSignal);
	if (regulatingSignal > 0) {
		openFlow();
	} else {
		closeFlow();
	}
}

bool Valve_R::isFlowClosed(double massFlowRate) {
	if (Component_R::isFlowClosed(massFlowRate)) {
		return true;
	}

	if (massFlowRate < 0 && !friction->isBidirectionalFlowAllowed()) {
		return true;
	}

	return false;
}

/**
 * Valve_R - C
 */
Valve_R* ValveKv_R_new(
		int allowBidirectionalFlow,
		double Kv,
		int transitionChoice,
		double transitionMassFlowRate,
		double transitionPressureDifference) {
	FrictionFlowValve* friction = FrictionFlowValve_Kv_new(
			allowBidirectionalFlow,
			Kv,
			transitionChoice,
			transitionMassFlowRate,
			transitionPressureDifference,
			1.0e4 //maximumMassFlowRate
	);

	return new Valve_R(friction);
}

void Valve_R_setRegulatingSignal(Valve_R* valve, double regulatingSignal) {
	valve->setRegulatingSignal(regulatingSignal);
}
