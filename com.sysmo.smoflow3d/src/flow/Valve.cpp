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
	double pressureDrop12 = state1->p() - state2->p();
	friction->computeMassFlowRate(pressureDrop12);
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

