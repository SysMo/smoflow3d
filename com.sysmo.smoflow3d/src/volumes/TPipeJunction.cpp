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

	fluidState1 = NULL;
	fluidState2 = NULL;
	fluidState3 = NULL;
}

TPipeJunction::~TPipeJunction() {
}

void TPipeJunction::initFluidStates(
		int initConditionsChoice, double initialPressure,
		double initialTemperature, double initialTemperatureC, double initialGasMassFraction) {
	fluidState1 = accFluid->getFluidState();
	Medium* fluid = fluidState1->getMedium();

	fluidState2 = MediumState_new(fluid);
	MediumState_register(fluidState2);

	fluidState3 = MediumState_new(fluid);
	MediumState_register(fluidState3);

	if (initConditionsChoice == 1) {
		fluidState1->update_Tp(initialTemperature, initialPressure);
		fluidState2->update_Tp(initialTemperature, initialPressure);
		fluidState3->update_Tp(initialTemperature, initialPressure);
	} else if (initConditionsChoice == 2) {
		fluidState1->update_Tp(initialTemperatureC + 273.15, initialPressure);
		fluidState2->update_Tp(initialTemperatureC + 273.15, initialPressure);
		fluidState3->update_Tp(initialTemperatureC + 273.15, initialPressure);
	} else if (initConditionsChoice == 3) {
		fluidState1->update_pq(initialPressure, initialGasMassFraction);
		fluidState2->update_pq(initialPressure, initialGasMassFraction);
		fluidState3->update_pq(initialPressure, initialGasMassFraction);
	} else {
		RaiseComponentError(this, "Unsupported type of initialization.");
	}
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
	return fluidState1;
}

MediumState* TPipeJunction::getFluidState2() {
	return fluidState2;
}

MediumState* TPipeJunction::getFluidState3() {
	return fluidState3;
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

void TPipeJunction_initFluidStates(TPipeJunction* component, int initConditionsChoice,
		double initialPressure, double initialTemperature, double initialTemperatureC,
		double initialGasMassFraction) {
	component->initFluidStates(initConditionsChoice, initialPressure,
			initialTemperature, initialTemperatureC, initialGasMassFraction);
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

MediumState* TPipeJunction_getFluidState2(TPipeJunction* component) {
	return component->getFluidState2();
}

MediumState* TPipeJunction_getFluidState3(TPipeJunction* component) {
	return component->getFluidState3();
}

double TPipeJunction_getFluidMass(TPipeJunction* component) {
	return component->getFluidMass();
}

void TPipeJunction_compute(TPipeJunction* component) {
	component->compute();
}
