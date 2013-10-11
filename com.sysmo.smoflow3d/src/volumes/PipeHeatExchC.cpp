/*
 * PipeHeatExchC.cpp
 *
 *  Created on: Oct 10, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "PipeHeatExchC.h"

using namespace smoflow;

/**
 * PipeHeatExch_C - C++
 */
PipeHeatExch_C::PipeHeatExch_C(Medium* fluid, double internalVolume, ForcedConvection* convection) {
	this->convection = convection;

	accFluid = FluidChamber_new(fluid);
	SMOCOMPONENT_SET_PARENT(accFluid, this);
	accFluid->setVolume(internalVolume);
	accFluid->selectStates(iT, iD);
	accFluidState = accFluid->getFluidState();

	this->port1Flow = NULL;
	this->port2Flow = NULL;

	this->wallHeatFlow = NULL;
	this->wallNode = NULL;
}

PipeHeatExch_C::~PipeHeatExch_C() {

}

void PipeHeatExch_C::init(FluidFlow* port1Flow, FluidFlow* port2Flow) {
	this->port1Flow = port1Flow;
	this->port2Flow = port2Flow;

	wallHeatFlow = HeatFlow_new();
	HeatFlow_register(this->wallHeatFlow);

	convection->init(accFluidState, accFluidState, wallNode); //:TRICKY: the both states of the convection are the internal pipe state
	convection->setLimitOutput(false);
}

void PipeHeatExch_C::getStateValues(double* value1, double* value2) {
	accFluid->getStateValues(value1, value2, true);
}

void PipeHeatExch_C::setStateValues(double value1, double value2) {
	accFluid->setStateValues(value1, value2);
}

void PipeHeatExch_C::getStateDerivatives(double* value1, double* value2) {
	accFluid->getStateDerivatives(value1, value2);
}

void PipeHeatExch_C::compute() {
	double massFlowRate = m::quadratic_mean(port1Flow->massFlowRate, port2Flow->massFlowRate);
	convection->compute(massFlowRate);
	convection->getFlow_Wall(wallHeatFlow);

	double netHeatFlowRate = convection->getHeatFlowRate();
	double netEnthalpyFlow = port1Flow->enthalpyFlowRate + port2Flow->enthalpyFlowRate;
	double netMassFlowRate = port1Flow->massFlowRate + port2Flow->massFlowRate;

	accFluid->compute(netMassFlowRate, netEnthalpyFlow, netHeatFlowRate, 0);
}

/**
 * PipeHeatExch_C - C
 */
PipeHeatExch_C* PipeHeatExch_C_new(Medium* fluid, double internalVolume, ForcedConvection* convection) {
	return new PipeHeatExch_C(fluid, internalVolume, convection);
}

void PipeHeatExch_C_init(PipeHeatExch_C* component, FluidFlow* port1Flow, FluidFlow* port2Flow) {
	component->init(port1Flow, port2Flow);
}

void PipeHeatExch_C_compute(PipeHeatExch_C* component) {
	component->compute();
}

void PipeHeatExch_C_setWallNode(PipeHeatExch_C* component, ThermalNode* wallNode) {
	component->setWallNode(wallNode);
}


void PipeHeatExch_C_setStateValues(PipeHeatExch_C* component, double value1, double value2) {
	component->setStateValues(value1, value2);
}

void PipeHeatExch_C_getStateValues(PipeHeatExch_C* component, double* value1, double* value2) {
	component->getStateValues(value1, value2);
}

void PipeHeatExch_C_getStateDerivatives(PipeHeatExch_C* component, double* value1, double* value2) {
	component->getStateDerivatives(value1, value2);
}

HeatFlow* PipeHeatExch_C_getWallHeatFlow(PipeHeatExch_C* component) {
	return component->getWallHeatFlow();
}

MediumState* PipeHeatExch_C_getFluidState(PipeHeatExch_C* component) {
	return component->getFluidState();
}

double PipeHeatExch_C_getVolume(PipeHeatExch_C* component) {
	return component->getVolume();
}
