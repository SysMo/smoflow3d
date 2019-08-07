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
	this->flagCloseFlowAtNegativeRegulatingSignal = true;
}

Valve_R::~Valve_R() {
}

void Valve_R::init(MediumState* state1Input) {
	FlowComponent_R::init(state1Input);
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
	} else if (regulatingSignal == 0){
		closeFlow();
	} else { //regulatingSignal < 0
		if (flagCloseFlowAtNegativeRegulatingSignal == true) {
			closeFlow();
		} else {
			openFlow(); //:TRICKY: the flow is open and dp = 0 bar; i.e. no pressure loss in the valve
		}
	}
}

void Valve_R::setCloseFlowAtNegativeRegulatingSignal(bool flagCloseFlowAtNegativeRegulatingSignal) {
	this->flagCloseFlowAtNegativeRegulatingSignal = flagCloseFlowAtNegativeRegulatingSignal;
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
			1.0e4, //maximumMassFlowRate
			0 //limitRegulatingSignal 0 - no, 1 - yes
	);

	Valve_R* valve = new Valve_R(friction);
	if (allowBidirectionalFlow == 0) { //0 - no
		valve->setIsBidirectionalFlowAllowed(false);
	}

	return valve;
}

Valve_R* Valve_OrificeCompressibleIdealGas_R_new(
		int allowBidirectionalFlow,
		double orificeArea,
		double flowCoefficient) {
	FrictionFlowValve* friction = FrictionFlowValve_OrificeCompressibleIdealGas_new(
			allowBidirectionalFlow,
			orificeArea,
			flowCoefficient
	);

	Valve_R* valve = new Valve_R(friction);
	if (allowBidirectionalFlow == 0) { //0 - no
		valve->setIsBidirectionalFlowAllowed(false);
	}

	return valve;
}

void Valve_R_setRegulatingSignal(Valve_R* valve, double regulatingSignal) {
	valve->setRegulatingSignal(regulatingSignal);
}

void Valve_R_setCloseFlowAtNegativeRegulatingSignal(Valve_R* valve, int flagCloseFlowAtNegativeRegulatingSignal) {
	if (flagCloseFlowAtNegativeRegulatingSignal == 1) {
		valve->setCloseFlowAtNegativeRegulatingSignal(true);
	} else {
		valve->setCloseFlowAtNegativeRegulatingSignal(false);
	}
}

int Valve_R_getFlowType(Valve_R* valve) {
	return (int) valve->getFlowType();
}


