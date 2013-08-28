/*
 * PhaseSeparator.cpp
 *
 *  Created on: Aug 28, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "PhaseSeparator.h"

PhaseSeparator::PhaseSeparator() {
}

PhaseSeparator::~PhaseSeparator() {
}

void PhaseSeparator::init(MediumState* port1State, FluidFlow* fluidFlow) {
	this->port1State = port1State;
	this->fluidFlow = fluidFlow;

	this->port2State = MediumState_new(port1State->getMedium());
}

void PhaseSeparator::updateState(double regulatingSignal) {
	if (phaseSelection == overall) {

	} else if (phaseSelection == liquid) {

	} else if (phaseSelection == gas) {

	}
}

