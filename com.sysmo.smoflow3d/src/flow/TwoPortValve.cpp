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
TwoPortValve::TwoPortValve(FrictionFlowValve* friction) {
	this->friction = friction;
}

TwoPortValve::~TwoPortValve() {
}

void TwoPortValve::init(MediumState* state1, MediumState* state2) {
	FlowComponent_R_2Port::init(state1, state2);
	friction->init(state1, state2);
}

void TwoPortValve::compute() {
	double pressureDrop12 = state1->p() - state2->p();
	friction->computeMassFlowRate(pressureDrop12);
}

/**
 * TwoPortValve - C
 */
TwoPortValve* TwoPortValve_InputMassFlowRate_new(int allowBidirectionalFlow) {
	FrictionFlowValve* friction = FrictionFlowValve_InputMassFlowRate_new(allowBidirectionalFlow);
	return new TwoPortValve(friction);
}

TwoPortValve* TwoPortValve_Kv_new(
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

	return new TwoPortValve(friction);
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

void TwoPortValve_updateFluidFlows(TwoPortValve* valve, FluidFlow* flow1, FluidFlow* flow2) {
	valve->updateFluidFlows(flow1, flow2);
}

double TwoPortValve_getAbsolutePressureDrop(TwoPortValve* valve) {
	return valve->getAbsolutePressureDrop();
}

