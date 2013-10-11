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
PipeHeatExch_C::PipeHeatExch_C(double internalVolume, ForcedConvection* convection) {
	this->volume = internalVolume;
	this->convection = convection;

	this->accFluidState = NULL;
	this->accFluid = NULL;

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

	this->wallHeatFlow = HeatFlow_new();
	HeatFlow_register(this->wallHeatFlow);

	convection->init(accFluidState, accFluidState, wallNode); //:TRICKY: the both states of the convection are the internal pipe state
	convection->setLimitOutput(false);
}

void PipeHeatExch_C::createState(Medium* fluid, ThermalNode* wallNode) {
	this->wallNode = wallNode;

	accFluid = FluidChamber_new(fluid);
	accFluid->setVolume(volume);
	accFluid->selectStates(iT, iD);

	accFluidState = accFluid->getFluidState();
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
	double massFlowRate = m::fabs((port1Flow->massFlowRate - port2Flow->massFlowRate) / 2.0); //:TODO: (???) (MILEN) massFlowRate = ?
	convection->compute(massFlowRate);
	convection->getFlow_Wall(wallHeatFlow);

	double netHeatFlowRate = convection->getHeatFlowRate();
	double netEnthalpyFlow = port1Flow->enthalpyFlowRate + port2Flow->enthalpyFlowRate;
	double netMassFlowRate = port1Flow->massFlowRate + port2Flow->massFlowRate;

	accFluid->computeStateDerivatives(netMassFlowRate, netEnthalpyFlow, netHeatFlowRate, 0);
}

/**
 * PipeHeatExch_C - C
 */
PipeHeatExch_C* PipeHeatExch_C_new(double internalVolume, ForcedConvection* convection) {
	return new PipeHeatExch_C(internalVolume, convection);
}
