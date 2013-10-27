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
	/* Inputs */
	regulatingSignal = 0.0;

	/* Results */
	massFlowRate = 0.0;
	enthalpyFlowRate = 0.0;
	pressureLoss = 0.0;
}

TwoPortValve::~TwoPortValve() {
}

void TwoPortValve::getFlowRates(FluidFlow* flow1, FluidFlow* flow2) {
	flow1->massFlowRate = -massFlowRate;
	flow1->enthalpyFlowRate = -enthalpyFlowRate;

	flow2->massFlowRate = massFlowRate;
	flow2->enthalpyFlowRate = enthalpyFlowRate;
}

/*************************************************************
 *** TwoPortValve implementation classes
 *************************************************************/
/**
 * TwoPortValve_Kv - C++
 */
class TwoPortValve_InputMassFlowRate : public TwoPortValve {
public:
	TwoPortValve_InputMassFlowRate(int allowBidirectionalFlow) {
		this->allowBidirectionalFlow = allowBidirectionalFlow;
	}

	virtual void compute() {
		massFlowRate = 0.0;
		enthalpyFlowRate = 0.0;

		// Compute pressure drop between state1 and state2
		double pressureDrop12 = MediumState_p(state1) - MediumState_p(state2);

		// Find the outlet and inlet state
		int flowDirection = 0;
		MediumState* inletState;
		MediumState* outletState;
		if (regulatingSignal <= 0) {
			flowDirection = 0;
		} else if (pressureDrop12 >= 0) {
			inletState = state1;
			outletState = state2;
			flowDirection = 1;
		} else if (pressureDrop12 < 0 && (allowBidirectionalFlow == 1)) { //allowBidirectionalFlow == 1 - yes
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

		// Compute mass flow rate
		massFlowRate = regulatingSignal * flowDirection;

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

		// Compute pressure loss
		pressureLoss = m::fabs(pressureDrop12);
	}

protected:
	int allowBidirectionalFlow; // 0 - no; 1 - yes
};


/**
 * TwoPortValve_Kv - C++
 */
class TwoPortValve_Kv : public TwoPortValve {
public:
	TwoPortValve_Kv(
			int transitionChoice,
			int allowBidirectionalFlow,
			double Kv,
			double transitionMassFlowRate,
			double transitionPressureDifference,
			double maximumMassFlowRate) {
		this->transitionChoice = transitionChoice;
		this->allowBidirectionalFlow = allowBidirectionalFlow;
		this->Kv = Kv;
		this->transitionMassFlowRate = transitionMassFlowRate;
		this->transitionPressureDifference = transitionPressureDifference;
		this->maximumMassFlowRate = maximumMassFlowRate;
	}

	virtual void compute() {
		massFlowRate = 0.0;
		enthalpyFlowRate = 0.0;

		// Compute pressure drop between state1 and state2
		double pressureDrop12 = MediumState_p(state1) - MediumState_p(state2);

		// Compute mass flow rate
		const double N1 = 8.784e-07; //2.403e-5;
		const double referenceLiquidDensity = 1000;

		m::limitVariable(regulatingSignal, 0.0, 1.0);

		int flowDirection = 0;
		MediumState* inletState;
		MediumState* outletState;
		if (regulatingSignal <= 0) {
			flowDirection = 0;
		} else if (pressureDrop12 > 0) {
			inletState = state1;
			outletState = state2;
			flowDirection = 1;
		} else if (pressureDrop12 < 0 && (allowBidirectionalFlow == 1)) { //allowBidirectionalFlow == 1 - yes
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
		}

		double volumetricFlowRateMagnitude;
		if (m::fabs(pressureDrop12) < transitionPressureDifference) {
			volumetricFlowRateMagnitude = regulatingSignal * N1 * Kv
					* m::pow(transitionPressureDifference / relativeDensity, 0.5)
					* (m::fabs(pressureDrop12) / transitionPressureDifference);
		} else {
			volumetricFlowRateMagnitude = regulatingSignal * N1 * Kv
					* m::pow(m::fabs(pressureDrop12) / relativeDensity, 0.5);
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

		// Compute pressure loss
		pressureLoss = m::fabs(pressureDrop12);
	}

protected:
	/* Parameters */
	int transitionChoice; //choice of transition to linear region: 1 - Minimum mass flow; 2 - Minimum pressure difference
	int allowBidirectionalFlow; // 0 - no; 1 - yes

	double Kv;
	double transitionMassFlowRate;
	double transitionPressureDifference;
	double maximumMassFlowRate;
};

/**
 * TwoPortValve - C
 */
TwoPortValve* TwoPortValve_InputMassFlowRate_new(int allowBidirectionalFlow) {
	return new TwoPortValve_InputMassFlowRate(allowBidirectionalFlow);
}

TwoPortValve* TwoPortValve_Kv_new(
		int transitionChoice,
		int allowBidirectionalFlow,
		double Kv,
		double transitionMassFlowRate,
		double transitionPressureDifference,
		double maximumMassFlowRate) {
	return new TwoPortValve_Kv(
			transitionChoice,
			allowBidirectionalFlow,
			Kv,
			transitionMassFlowRate,
			transitionPressureDifference,
			maximumMassFlowRate);
}

void TwoPortValve_init(TwoPortValve* valve, MediumState* state1, MediumState* state2) {
	valve->init(state1, state2);
}

void TwoPortValve_compute(TwoPortValve* valve) {
	valve->compute();
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
