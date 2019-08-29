/*
 * TPipeJunction.cpp
 *
 *  Created on: Aug 30, 2019
 *      Author: Milen Borisov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "TPipeJunction.h"

/**
 * TPipeJunction - C++
 */
TPipeJunction::TPipeJunction(Medium *fluid, double internalVolume, int stateVariableSelection) {
	accFluid = FluidChamber_new(fluid);
	SMOCOMPONENT_SET_PARENT(accFluid, this);
	accFluid->setVolume(internalVolume);

	if (stateVariableSelection == 1) {
		accFluid->selectStates(iT, iD);
	} else if (stateVariableSelection == 2) {
		accFluid->selectStates(iP, iT);
	} else if (stateVariableSelection == 3) {
		accFluid->selectStates(iP, iD);
	} else if (stateVariableSelection == 4) {
		accFluid->selectStates(iP, iH);
	} else {
		RaiseComponentError(this, "Unsupported type of state variables.");
	}

	port1Flow = NULL;
	port2Flow = NULL;
	port3Flow = NULL;
}

TPipeJunction::~TPipeJunction() {
}

void TPipeJunction::initFlows(FluidFlow* port1Flow, FluidFlow* port2Flow, FluidFlow* port3Flow) {
	this->port1Flow = port1Flow;
	this->port2Flow = port2Flow;
	this->port3Flow = port3Flow;
}

void TPipeJunction::getStateValues(double* value1, double* value2) {
	accFluid->getStateValues(value1, value2, true);
}

void TPipeJunction::setStateValues(double value1, double value2) {
	accFluid->setStateValues(value1, value2);
}

void TPipeJunction::getStateDerivatives(double* value1, double* value2) {
	accFluid->getStateDerivatives(value1, value2);
}

MediumState* TPipeJunction::getFluidState1() {
	return accFluid->getFluidState();
}

double TPipeJunction::getFluidMass() {
	return accFluid->getFluidMass();
}

void TPipeJunction::compute() {
	double netMassFlowRate = port1Flow->massFlowRate + port2Flow->massFlowRate + port3Flow->massFlowRate;
	double netEnthalpyFlow = port1Flow->enthalpyFlowRate + port2Flow->enthalpyFlowRate + port3Flow->enthalpyFlowRate;

	accFluid->compute(netMassFlowRate, netEnthalpyFlow, 0, 0); // netHeatFlowRate = netVolumeChangeRate = 0
}


/**
 * TPipeJunction - C
 */
TPipeJunction* TPipeJunction_new(Medium *fluid, double internalVolume, int stateVariableSelection) {
	return new TPipeJunction(fluid, internalVolume, stateVariableSelection);
}

void TPipeJunction_initFlows(TPipeJunction* component, FluidFlow* port1Flow, FluidFlow* port2Flow, FluidFlow* port3Flow) {
	component->initFlows(port1Flow, port2Flow, port3Flow);
}

void TPipeJunction_setStateValues(TPipeJunction* component, double value1, double value2) {
	component->setStateValues(value1, value2);
}

void TPipeJunction_getStateValues(TPipeJunction* component, double* value1, double* value2) {
	component->getStateValues(value1, value2);
}

void TPipeJunction_getStateDerivatives(TPipeJunction* component, double* value1, double* value2) {
	component->getStateDerivatives(value1, value2);
}

MediumState* TPipeJunction_getFluidState1(TPipeJunction* component) {
	return component->getFluidState1();
}

double TPipeJunction_getFluidMass(TPipeJunction* component) {
	return component->getFluidMass();
}

void TPipeJunction_compute(TPipeJunction* component) {
	component->compute();
}
