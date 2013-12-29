/*
 * Valve.cpp
 *
 *  Created on: Jul 28, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "Valve.h"
using namespace smoflow;

/**
 * TwoPortValve - C++
 */
Valve::Valve(FrictionFlowValve* friction) {
	this->friction = friction;

	state1 = NULL;
	state2 = NULL;

	useOpeningClosePressDiff = false;
	openingPressDiff = 0.0;
	closingPressDiff = 0.0;

	isFlowClosed_byPressDiff = false;

	isClosingPressDiffCrossed = false;
	discFlag_isClosingPressDiffCrossed = false;
	discFlag_isClosingPressDiffCrossed_isInit = false;

	isOpeningPressDiffCrossed = false;
	discFlag_isOpeningPressDiffCrossed = false;
	discFlag_isOpeningPressDiffCrossed_isInit = false;
}

Valve::~Valve() {
}

void Valve::init(MediumState* state1, MediumState* state2) {
	if (state1->getMedium() != state2->getMedium()) {
		RaiseComponentError(this, "Different media connected to the valve component!");
	}

	this->state1 = state1;
	this->state2 = state2;
	friction->init(state1, state2);
}

void Valve::compute() {
	// Get pressure drop
	double pressureDrop12 = state1->p() - state2->p();

	// Use opening/closing pressure difference
	if (useOpeningClosePressDiff) {
		double absOuterPressDrop = m::fabs(pressureDrop12);
		isClosingPressDiffCrossed = absOuterPressDrop < closingPressDiff;
		isOpeningPressDiffCrossed = absOuterPressDrop > openingPressDiff;

		if (SimEnv.isEventMode()) { //in a discontinuity
			if (absOuterPressDrop <= closingPressDiff) {
				isFlowClosed_byPressDiff = true;
			}

			if (absOuterPressDrop >= openingPressDiff) {
				isFlowClosed_byPressDiff = false;
			}
		}
	}

	// Compute
	if (isFlowClosed_byPressDiff) {
		friction->computeMassFlowRate_NoFluidFlow(pressureDrop12);
	} else {
		friction->computeMassFlowRate(pressureDrop12);
	}

	// Check for discontinuities
	handleEvent_OpeningClosingPressureDifferenceIsCrossed();
}

void Valve::setPressureDifferenceParameters(bool useOpeningClosePressDiff, double openingPressDiff, double closingPressDiff) {
	this->useOpeningClosePressDiff = useOpeningClosePressDiff;
	this->openingPressDiff = openingPressDiff;
	this->closingPressDiff = closingPressDiff;
}

void Valve::handleEvent_OpeningClosingPressureDifferenceIsCrossed() {
	if (!useOpeningClosePressDiff) {
		return;
	}

	// Handle - Closing pressure difference
	if (isFlowClosed_byPressDiff == false) {
		if (discFlag_isClosingPressDiffCrossed_isInit == false) {
			discFlag_isClosingPressDiffCrossed = isClosingPressDiffCrossed;
			discFlag_isClosingPressDiffCrossed_isInit = true;
		}

		if (SimEnv.isEventMode()) { //in a discontinuity
			discFlag_isClosingPressDiffCrossed = isClosingPressDiffCrossed;
		}

		bool eventIndicator = false;
		if (isClosingPressDiffCrossed != discFlag_isClosingPressDiffCrossed) {
			eventIndicator = true;
		}

		if (eventIndicator) { //trigger a discontinuity
			SimEnv.updateEventIndicator(eventIndicator);
		}
	}

	// Handle - Opening pressure difference
	if (isFlowClosed_byPressDiff == true) {
		if (discFlag_isOpeningPressDiffCrossed_isInit == false) {
			discFlag_isOpeningPressDiffCrossed = isOpeningPressDiffCrossed;
			discFlag_isOpeningPressDiffCrossed_isInit = true;
		}

		if (SimEnv.isEventMode()) { //in a discontinuity
			discFlag_isOpeningPressDiffCrossed = isOpeningPressDiffCrossed;
		}

		bool eventIndicator = false;
		if (isOpeningPressDiffCrossed != discFlag_isOpeningPressDiffCrossed) {
			eventIndicator = true;
		}

		if (eventIndicator) { //trigger a discontinuity
			SimEnv.updateEventIndicator(eventIndicator);
		}
	}
}

/**
 * TwoPortValve - C
 */
Valve* Valve_InputMassFlowRate_new(int allowBidirectionalFlow) {
	FrictionFlowValve* friction = FrictionFlowValve_InputMassFlowRate_new(allowBidirectionalFlow);
	return new Valve(friction);
}

Valve* Valve_Kv_new(
		int allowBidirectionalFlow,
		double Kv,
		int transitionChoice,
		double transitionMassFlowRate,
		double transitionPressureDifference,
		double maximumMassFlowRate) {
	FrictionFlowValve* friction = FrictionFlowValve_Kv_new(
				allowBidirectionalFlow,
				Kv,
				transitionChoice,
				transitionMassFlowRate,
				transitionPressureDifference,
				maximumMassFlowRate);

	return new Valve(friction);
}

Valve* Valve_OrificeCompressibleIdealGas_new(
		int allowBidirectionalFlow,
		double orificeArea,
		double flowCoefficient) {
	FrictionFlowValve* friction = FrictionFlowValve_OrificeCompressibleIdealGas_new(
			allowBidirectionalFlow,
			orificeArea,
			flowCoefficient);

	return new Valve(friction);
}

void Valve_init(Valve* valve, MediumState* state1, MediumState* state2) {
	valve->init(state1, state2);
}

void Valve_compute(Valve* valve) {
	valve->compute();
}

void Valve_setRegulatingSignal(Valve* valve, double regulatingSignal) {
	valve->setRegulatingSignal(regulatingSignal);
}

void Valve_updateFluidFlows(Valve* valve, FluidFlow* flow1, FluidFlow* flow2) {
	valve->updateFluidFlows(flow1, flow2);
}

double Valve_getAbsolutePressureDrop(Valve* valve) {
	return valve->getAbsolutePressureDrop();
}

int Valve_getFlowType(Valve* valve) {
	return (int) valve->getFlowType();
}

int Valve_getIsFlowClosed(Valve* valve) {
	if (valve->isFlowClosed()) {
		return 1;
	} else {
		return 0;
	}
}

void Valve_setPressureDifferenceParameters(Valve* valve, int useOpeningClosePressDiff, double openingPressDiff, double closingPressDiff) {
	bool flagUseOpeningClosingPressDiff = false;
	if (useOpeningClosePressDiff == 1) {
		flagUseOpeningClosingPressDiff = true;
	}

	valve->setPressureDifferenceParameters(flagUseOpeningClosingPressDiff, openingPressDiff, closingPressDiff);
}
