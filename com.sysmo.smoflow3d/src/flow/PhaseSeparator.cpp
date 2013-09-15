/*
 * PhaseSeparator.cpp
 *
 *  Created on: Aug 28, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "PhaseSeparator.h"
using namespace smoflow;

/**
 * PhaseSeparator - C++
 */
PhaseSeparator::PhaseSeparator(PhaseSelection phaseSelection) {
	this->phaseSelection = phaseSelection;
	port1State = NULL;
	port2State = NULL;
}

PhaseSeparator::~PhaseSeparator() {
}

void PhaseSeparator::init(MediumState* port1State) {
	this->port1State = port1State;
	this->port2State = MediumState_new(port1State->getMedium());
	MediumState_register(this->port2State);
}

void PhaseSeparator::updateState(double regulatingSignal) {
	if (!port1State->isTwoPhase() || phaseSelection == PhaseSelection_Overall) {
		// If port1 is in single phase state, just copy its state
		port2State->update_Trho(port1State->T(), port1State->rho());
	} else {
		// We are in two phase and we need to separate
		if (phaseSelection == PhaseSelection_Liquid) {
			port2State->update_Tq(port1State->T(), 0);
		} else if (phaseSelection == PhaseSelection_Gas) {
			port2State->update_Tq(port1State->T(), 1);
		} else if (phaseSelection == PhaseSelection_varDiscrete) {
			if (regulatingSignal < 0) {
				port2State->update_Trho(port1State->T(), port1State->rho());
			} else if (regulatingSignal < 0.5) {
				port2State->update_Tq(port1State->T(), 0);
			} else {
				port2State->update_Tq(port1State->T(), 1);
			}
		} else if (phaseSelection == PhaseSelection_varContinuous) {
			if (regulatingSignal < 0) {
				port2State->update_Trho(port1State->T(), port1State->rho());
			} else {
				m::limitVariable(regulatingSignal, 0, 1);
				port2State->update_Tq(port1State->T(), regulatingSignal);
			}
		}
	}
}

/**
 * PhaseSeparator - C
 */
PhaseSeparator* PhaseSeparator_new(PhaseSelection phaseSelection) {
	return new PhaseSeparator(phaseSelection);
}

void PhaseSeparator_init(PhaseSeparator* component, MediumState* port1State) {
	component->init(port1State);
}

MediumState* PhaseSeparator_getPort2State(PhaseSeparator* component) {
	return component->getPort2State();
}

void PhaseSeparator_updateState(PhaseSeparator* component, double regulatingSignal) {
	component->updateState(regulatingSignal);
}
