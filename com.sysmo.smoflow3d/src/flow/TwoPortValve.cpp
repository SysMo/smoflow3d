/*
 * TwoPortValve.cpp
 *
 *  Created on: Jul 28, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "TwoPortValve.h"
using namespace smoflow;

/**
 * TwoPortValve - C++
 */
TwoPortValve::TwoPortValve() {
	/* Parameters */
	transitionChoice = 0;
	allowBidirectionalFlow = 0;

	Kv = 0.0;
	transitionMassFlowRate = 0.0;
	transitionPressureDifference = 0.0;
	maximumMassFlowRate = 0.0;

	/* Inputs */
	regulatingSignal = 0.0;

	/* Results */
	massFlowRate = 0.0;
	enthalpyFlowRate = 0.0;
	pressureLoss = 0.0;
}

TwoPortValve::~TwoPortValve() {
}

void TwoPortValve::compute_Kv() {
	massFlowRate = 0.0;
	enthalpyFlowRate = 0.0;

	// Compute pressure loss
	pressureLoss = MediumState_p(state1) - MediumState_p(state2);

	// Compute mass flow rate
	const double N1 = 8.784e-07; //2.403e-5;
	const double referenceLiquidDensity = 1000;

	m::limitVariable(regulatingSignal, 0.0, 1.0);

	int flowDirection = 0;
	MediumState* inletState;
	MediumState* outletState;
	if (regulatingSignal <= 0) {
		flowDirection = 0;
	} else if (pressureLoss > 0) {
		inletState = state1;
		outletState = state2;
		flowDirection = 1;
	} else if (pressureLoss < 0 && (allowBidirectionalFlow == 1)) {
		inletState = state2;
		outletState = state1;
		flowDirection = -1;
	} else {
		flowDirection = 0;
	}

	if (flowDirection == 0) {
		// No flow
		return;
	}

	double rho_inlet = MediumState_rho(inletState);
	double relativeDensity = rho_inlet / referenceLiquidDensity;

	// Calculate transition pressure if necessary
	if (transitionChoice == 1) { //1 - Minimum mass flow
		transitionPressureDifference = m::pow((transitionMassFlowRate / rho_inlet)
				/ (N1 * Kv), 2.0) * relativeDensity;
	} else { //2 - Minimum pressure difference
		//:TRICKY: the user have been set the transitionPressureDifference yet
	}

	double volumetricFlowRateMagnitude;
	if (m::fabs(pressureLoss) < transitionPressureDifference) {
		volumetricFlowRateMagnitude = regulatingSignal * N1 * Kv
				* m::pow(transitionPressureDifference / relativeDensity, 0.5)
				* (m::fabs(pressureLoss) / transitionPressureDifference);
	} else {
		volumetricFlowRateMagnitude = regulatingSignal * N1 * Kv
				* m::pow(m::fabs(pressureLoss) / relativeDensity, 0.5);
	}

	massFlowRate = volumetricFlowRateMagnitude * flowDirection * rho_inlet;
	if (m::fabs(massFlowRate) > maximumMassFlowRate) {
		massFlowRate = maximumMassFlowRate * flowDirection;
	}

	// Compute enthalpy flow rate
	if (flowDirection == 1) {
		double h1 = MediumState_h(state1);
		enthalpyFlowRate = massFlowRate * h1;
	} else if (flowDirection == -1) {
		double h2 = MediumState_h(state2);
		enthalpyFlowRate = massFlowRate * h2;
	} else {
		enthalpyFlowRate = 0;
	}
}

void TwoPortValve::getFlowRates(FluidFlow* flow1, FluidFlow* flow2) {
	flow1->massFlowRate = -massFlowRate;
	flow1->enthalpyFlowRate = -enthalpyFlowRate;

	flow2->massFlowRate = massFlowRate;
	flow2->enthalpyFlowRate = enthalpyFlowRate;
}

/**
 * TwoPortValve - C
 */
TwoPortValve* TwoPortValve_new() {
	return new TwoPortValve();
}

void TwoPortValve_init(TwoPortValve* valve, MediumState* state1, MediumState* state2) {
	valve->init(state1, state2);
}

void TwoPortValve_compute_Kv(TwoPortValve* valve) {
	valve->compute_Kv();
}

void TwoPortValve_setTransitionChoice(TwoPortValve* valve, int transitionChoice) {
	valve->setTransitionChoice(transitionChoice);
}

void TwoPortValve_setAllowBidirectionalFlow(TwoPortValve* valve, int allowBidirectionalFlow) {
	valve->setAllowBidirectionalFlow(allowBidirectionalFlow);
}

void TwoPortValve_setKv(TwoPortValve* valve, double Kv) {
	valve->setKv(Kv);
}

void TwoPortValve_setTransitionMassFlowRate(TwoPortValve* valve, double transitionMassFlowRate) {
	valve->setTransitionMassFlowRate(transitionMassFlowRate);
}

void TwoPortValve_setTransitionPressureDifference(TwoPortValve* valve, double transitionPressureDifference) {
	valve->setTransitionPressureDifference(transitionPressureDifference);
}

void TwoPortValve_setMaximumMassFlowRate(TwoPortValve* valve, double maximumMassFlowRate) {
	valve->setMaximumMassFlowRate(maximumMassFlowRate);
}

void TwoPortValve_setRegulatingSignal(TwoPortValve* valve, double regulatingSignal) {
	valve->setRegulatingSignal(regulatingSignal);
}

double TwoPortValve_getMassFlowRate(TwoPortValve* valve) {
	return valve->getMassFlowRate();
}

double TwoPortValve_getEnthalpyFlowRate(TwoPortValve* valve) {
	return valve->getEnthalpyFlowRate();
}

double TwoPortValve_getPressureLoss(TwoPortValve* valve) {
	return valve->getPressureLoss();
}

void TwoPortValve_getFlowRates(TwoPortValve* valve, FluidFlow* flow1, FluidFlow* flow2) {
	valve->getFlowRates(flow1, flow2);
}
