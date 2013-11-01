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
Valve_R::Valve_R() {
	regulatingSignal = 0.0;
	absPressureDrop = 0.0;
}

Valve_R::~Valve_R() {
}

bool Valve_R::compute(double massFlowRate, double minDownstreamPressure) {
	computePressureDrop(massFlowRate);

	// Try to compute downstream pressure
	MediumState* upstreamState = getUpstreamState(massFlowRate);
	double downstreamPressure = upstreamState->p() - getAbsolutePressureDrop();
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

void Valve_R::setRegulationgSignal(double regulatingSignal) {
	this->regulatingSignal = regulatingSignal;
	if (regulatingSignal > 0) {
		openFlow();
	} else {
		closeFlow();
	}
}

/*************************************************************
 *** Valve_R implementation classes
 *************************************************************/

/**
 * ValveKv_R - C++
 */
class ValveKv_R : public Valve_R {
public:
	ValveKv_R(
			double Kv,
			int transitionChoice,
			double transitionMassFlowRate,
			double transitionPressureDifference) {
		this->transitionChoice = transitionChoice;
		this->Kv = Kv;
		this->transitionMassFlowRate = transitionMassFlowRate;
		this->transitionPressureDifference = transitionPressureDifference;
	}

	double computePressureDrop(double massFlowRate) {
		// Set some constants
		const double N1 = 8.784e-07; //2.403e-5;
		const double referenceLiquidDensity = 1000;

		m::limitVariable(regulatingSignal, 0.0, 1.0);
		double absMassFlowRate = m::fabs(massFlowRate);

		// Get upstream state
		MediumState* upstreamState = getUpstreamState(massFlowRate);
		double upstreamDensity = upstreamState->rho();
		double relativeDensity = upstreamDensity / referenceLiquidDensity;

		// Calculate transition mass flow rate if necessary
		if (transitionChoice == 1) { //1 - Minimum mass flow
			//:TRICKY: transitionMassFlowRate is set from the user
			transitionPressureDifference = m::pow((transitionMassFlowRate / upstreamDensity)
					/ (N1 * Kv), 2.0) * relativeDensity;
		} else { //2 - Minimum pressure difference
			//:TRICKY: transitionPressureDifference is set from the user
			transitionMassFlowRate = m::sqrt((transitionPressureDifference/relativeDensity))
					* upstreamDensity * N1 * Kv;
		}

		// Calculate pressure drop
		double vFlow = absMassFlowRate / upstreamDensity;
		double pressureDrop = 0.0;
		if (absMassFlowRate < transitionMassFlowRate) {
			pressureDrop = transitionPressureDifference * vFlow
					/ (regulatingSignal * N1 * Kv * m::pow(transitionPressureDifference / relativeDensity, 0.5));
		} else {
			pressureDrop = relativeDensity * m::pow(vFlow/(regulatingSignal * N1 * Kv), 2);
		}

		absPressureDrop = pressureDrop;
		if (massFlowRate < 0) {
			pressureDrop = -pressureDrop;
		}
		return pressureDrop;
	}

protected:
	double Kv;
	int transitionChoice;
	double transitionMassFlowRate;
	double transitionPressureDifference;
};


/**
 * Valve_R - C
 */
Valve_R* ValveKv_R_new(
		double Kv,
		int transitionChoice,
		double transitionMassFlowRate,
		double transitionPressureDifference) {
	return new ValveKv_R(Kv, transitionChoice, transitionMassFlowRate, transitionPressureDifference);
}
