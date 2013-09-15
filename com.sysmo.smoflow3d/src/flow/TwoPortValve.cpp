/*
 * TwoPortValve.cpp
 *
 *  Created on: Jul 28, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "TwoPortValve.h"
using namespace smoflow;


BEGIN_C_LINKAGE

TwoPortValve* TwoPortValve_new() {
	return new TwoPortValve();
}

void TwoPortValve_init(TwoPortValve* valve, MediumState* state1, MediumState* state2) {
	valve->state1 = state1;
	valve->state2 = state2;
}

void TwoPortValve_computeMassFlow_Kv(TwoPortValve* valve, double regulatingSignal) {
	const double N1 = 8.784e-07; //2.403e-5;
	const double referenceLiquidDensity = 1000;
	double regulatingSignalLimited = regulatingSignal;

	if (regulatingSignal < 0) {
		regulatingSignalLimited = 0;
	} else if (regulatingSignal > 1) {
		regulatingSignalLimited = 1;
	}

	valve->massFlowRate = 0;
	double p1 = MediumState_p(valve->state1);
	double p2 = MediumState_p(valve->state2);
	valve->pressureDrop = p1 - p2;

	MediumState* inletState;
	MediumState* outletState;

	if (regulatingSignalLimited <= 0) {
		valve->flowDirection = 0;
	} else if (valve->pressureDrop > 0) {
		inletState = valve->state1;
		outletState = valve->state2;
		valve->flowDirection = 1;
	} else if (valve->pressureDrop < 0 && (valve->allowBidirectionalFlow == 1)) {
		inletState = valve->state2;
		outletState = valve->state1;
		valve->flowDirection = -1;
	} else {
		valve->flowDirection = 0;
	}

	if (valve->flowDirection == 0) {
		// No flow
		return;
	}

	double rho_inlet = MediumState_rho(inletState);
	double relativeDensity = rho_inlet / referenceLiquidDensity;

	// Calculate transition pressure if necessary
	if (valve->transitionChoice == 1) {
		valve->transitionPressureDifference = m::pow((valve->transitionMassFlowRate / rho_inlet)
				/ (N1 * valve->Kv), 2.0) * relativeDensity;
	}
	double volumetricFlowRateMagnitude;
	if (m::fabs(valve->pressureDrop) < valve->transitionPressureDifference) {
		volumetricFlowRateMagnitude = regulatingSignalLimited * N1 * valve->Kv *
			m::pow(valve->transitionPressureDifference / relativeDensity, 0.5)
			* (m::fabs(valve->pressureDrop) / valve->transitionPressureDifference);
	} else {
		volumetricFlowRateMagnitude = regulatingSignalLimited * N1 * valve->Kv *
			m::pow(m::fabs(valve->pressureDrop) / relativeDensity, 0.5);
	}
	valve->massFlowRate = volumetricFlowRateMagnitude * valve->flowDirection * rho_inlet;
	if (m::fabs(valve->massFlowRate) > valve->maximumMassFlowRate) {
		valve->massFlowRate = valve->maximumMassFlowRate * valve->flowDirection;
	}
}

void TwoPortValve_computeEnthalpyFlow(TwoPortValve* valve) {
	if (valve->flowDirection == 1) {
		double h1 = MediumState_h(valve->state1);
		valve->enthalpyFlowRate = valve->massFlowRate * h1;
	} else if (valve->flowDirection == -1) {
		double h2 = MediumState_h(valve->state2);
		valve->enthalpyFlowRate = valve->massFlowRate * h2;
	} else {
		valve->enthalpyFlowRate = 0;
	}
}

END_C_LINKAGE
