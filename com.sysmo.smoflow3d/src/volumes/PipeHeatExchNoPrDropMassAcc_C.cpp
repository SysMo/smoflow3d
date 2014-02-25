/*
 * PipeHeatExchNoPrDropMassAcc_C.cpp
 *
 *  Created on: Oct 10, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "PipeHeatExchNoPrDropMassAcc_C.h"

using namespace smoflow;

/**
 * PipeHeatExch_C - C++
 */
PipeHeatExchNoPrDropMassAcc_C::PipeHeatExchNoPrDropMassAcc_C(Medium* fluid, double internalVolume, ForcedConvection* convection, int stateVariableSelection) {
	this->convection = convection;
	SMOCOMPONENT_SET_PARENT(this->convection, this);

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


	accFluidState = accFluid->getFluidState();

	this->port1Flow = NULL;
	this->port2Flow = NULL;

	this->wallHeatFlow = NULL;
	this->wallNode = NULL;
}

PipeHeatExchNoPrDropMassAcc_C::~PipeHeatExchNoPrDropMassAcc_C() {

}

void PipeHeatExchNoPrDropMassAcc_C::init(FluidFlow* port1Flow, FluidFlow* port2Flow) {
	this->port1Flow = port1Flow;
	this->port2Flow = port2Flow;

	wallHeatFlow = HeatFlow_new();
	HeatFlow_register(this->wallHeatFlow);

	convection->init(accFluidState, accFluidState, wallNode); //:TRICKY: the both states of the convection are the internal pipe state
	convection->setLimitOutput(false);
}

void PipeHeatExchNoPrDropMassAcc_C::getStateValues(double* value1, double* value2) {
	accFluid->getStateValues(value1, value2, true);
}

void PipeHeatExchNoPrDropMassAcc_C::setStateValues(double value1, double value2) {
	accFluid->setStateValues(value1, value2);
}

void PipeHeatExchNoPrDropMassAcc_C::getStateDerivatives(double* value1, double* value2) {
	accFluid->getStateDerivatives(value1, value2);
}

void PipeHeatExchNoPrDropMassAcc_C::compute() {
	double massFlowRate = m::quadratic_mean(port1Flow->massFlowRate, port2Flow->massFlowRate);
	convection->compute(massFlowRate);
	convection->updateHeatFlow(wallHeatFlow);

	double netHeatFlowRate = convection->getHeatFlowRate();
	double netEnthalpyFlow = port1Flow->enthalpyFlowRate + port2Flow->enthalpyFlowRate;
	double netMassFlowRate = port1Flow->massFlowRate + port2Flow->massFlowRate;

	accFluid->compute(netMassFlowRate, netEnthalpyFlow, netHeatFlowRate, 0);
}

/**
 * PipeHeatExch_C - C
 */
PipeHeatExchNoPrDropMassAcc_C* PipeHeatExchNoPrDropMassAcc_C_new(Medium* fluid, double internalVolume, ForcedConvection* convection, int stateVariableSelection) {
	return new PipeHeatExchNoPrDropMassAcc_C(fluid, internalVolume, convection, stateVariableSelection);
}

void PipeHeatExchNoPrDropMassAcc_C_init(PipeHeatExchNoPrDropMassAcc_C* component, FluidFlow* port1Flow, FluidFlow* port2Flow) {
	component->init(port1Flow, port2Flow);
}

void PipeHeatExchNoPrDropMassAcc_C_compute(PipeHeatExchNoPrDropMassAcc_C* component) {
	component->compute();
}

void PipeHeatExchNoPrDropMassAcc_C_setWallNode(PipeHeatExchNoPrDropMassAcc_C* component, ThermalNode* wallNode) {
	component->setWallNode(wallNode);
}


void PipeHeatExchNoPrDropMassAcc_C_setStateValues(PipeHeatExchNoPrDropMassAcc_C* component, double value1, double value2) {
	component->setStateValues(value1, value2);
}

void PipeHeatExchNoPrDropMassAcc_C_getStateValues(PipeHeatExchNoPrDropMassAcc_C* component, double* value1, double* value2) {
	component->getStateValues(value1, value2);
}

void PipeHeatExchNoPrDropMassAcc_C_getStateDerivatives(PipeHeatExchNoPrDropMassAcc_C* component, double* value1, double* value2) {
	component->getStateDerivatives(value1, value2);
}

HeatFlow* PipeHeatExchNoPrDropMassAcc_C_getWallHeatFlow(PipeHeatExchNoPrDropMassAcc_C* component) {
	return component->getWallHeatFlow();
}

MediumState* PipeHeatExchNoPrDropMassAcc_C_getFluidState(PipeHeatExchNoPrDropMassAcc_C* component) {
	return component->getFluidState();
}

double PipeHeatExchNoPrDropMassAcc_C_getVolume(PipeHeatExchNoPrDropMassAcc_C* component) {
	return component->getVolume();
}
