/*
 * PipeHeatExchPrDropRC.cpp
 *
 *  Created on: Aug 23, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "PipeHeatExchPrDropRC.h"

using namespace smoflow;

/**
 * PipeHeatExchPrDrop_RC - C++
 */
PipeHeatExchPrDrop_RC::PipeHeatExchPrDrop_RC(
		double internalVolume, FrictionFlowPipe* friction,
		ForcedConvection* convection) {
	this->volume = internalVolume;
	this->friction = friction;
	this->convection = convection;

	accFluid = NULL;
	internalFlow = NULL;
}

PipeHeatExchPrDrop_RC::~PipeHeatExchPrDrop_RC() {
}

void PipeHeatExchPrDrop_RC::_init() {
	friction->init(port1State, port2State);
	convection->init(port2State, port2State, wallNode);
	convection->setLimitOutput(false);
	internalFlow = FluidFlow_new();
	FluidFlow_register(internalFlow);
}

void PipeHeatExchPrDrop_RC::_createState() {
	accFluid = FluidChamber_new(port1State->getMedium());
	accFluid->setVolume(volume);
	accFluid->selectStates(iT, iD);
	// TODO fix the user initialization
	port2State = accFluid->getFluidState();
	port2State->update_Tp(wallNode->getTemperature(), port1State->p());
}

void PipeHeatExchPrDrop_RC::getStateValues(double* value1, double* value2) {
	accFluid->getStateValues(value1, value2, true);
}

void PipeHeatExchPrDrop_RC::setStateValues(double value1, double value2) {
	accFluid->setStateValues(value1, value2);
}

void PipeHeatExchPrDrop_RC::getStateDerivatives(double* value1, double* value2) {
	accFluid->getStateDerivatives(value1, value2);
}

void PipeHeatExchPrDrop_RC::compute() {
	double dp = port1State->p() - port2State->p();
	double massFlowRate = friction->computeMassFlowRate(dp);
	friction->getFluidFlow1(port1Flow);
	friction->getFluidFlow2(internalFlow);

	convection->compute(massFlowRate);
	convection->getFlow_Wall(wallHeatFlow);

	double netHeatFlowRate = convection->getHeatFlowRate();
	double netEnthalpyFlow = internalFlow->enthalpyFlowRate + port2Flow->enthalpyFlowRate;
	double netMassFlowRate = internalFlow->massFlowRate + port2Flow->massFlowRate;

	accFluid->computeStateDerivatives(netMassFlowRate, netEnthalpyFlow,
			netHeatFlowRate, 0);
}

/**
 * PipeHeatExchPrDrop_RC - C
 */
PipeHeatExchPrDrop_RC* PipeHeatExchPrDrop_RC_new(double internalVolume,
		FrictionFlowPipe* friction, ForcedConvection* convection) {
	return new PipeHeatExchPrDrop_RC(internalVolume, friction, convection);
}

void PipeHeatExchPrDrop_RC_compute(PipeHeatExchPrDrop_RC* component) {
	component->compute();
}
