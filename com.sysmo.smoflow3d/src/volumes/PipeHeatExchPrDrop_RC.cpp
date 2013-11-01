/*
 * PipeHeatExchPrDropRC.cpp
 *
 *  Created on: Aug 23, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "PipeHeatExchPrDrop_RC.h"


/**
 * PipeHeatExchPrDrop_RC - C++
 */
PipeHeatExchPrDrop_RC::PipeHeatExchPrDrop_RC(
		double internalVolume,
		FrictionFlowPipe* friction,
		ForcedConvection* convection) {
	this->volume = internalVolume;
	this->friction = friction;
	this->convection = convection;
	SMOCOMPONENT_SET_PARENT(this->convection, this);

	accFluid = NULL;
	internalFlow = NULL;
}

PipeHeatExchPrDrop_RC::~PipeHeatExchPrDrop_RC() {
}

void PipeHeatExchPrDrop_RC::init(FluidFlow* port2Flow) {
	Component_RC::init(port2Flow);

	friction->init(port1State, port2State);
	convection->init(port2State, port2State, wallNode); //:TRICKY: the both states of the convection are the internal pipe state
	convection->setLimitOutput(false);

	internalFlow = FluidFlow_new();
	FluidFlow_register(internalFlow);
}

void PipeHeatExchPrDrop_RC::initStates(MediumState* port1State,
		ThermalNode* wallNode, StateVariableSet& innerStateInitializer) {
	Component_RC::initStates(port1State, wallNode, innerStateInitializer);

	accFluid = FluidChamber_new(port1State->getMedium());
	SMOCOMPONENT_SET_PARENT(accFluid, this);

	accFluid->setVolume(volume);
	accFluid->selectStates(iP, iD);

	port2State = accFluid->getFluidState();
	//port2State->update_Tp(wallNode->getTemperature(), port1State->p());
	port2State->init(innerStateInitializer);
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
	double pressureDrop = port1State->p() - port2State->p();
	double massFlowRate = friction->computeMassFlowRate(pressureDrop);
	friction->updateFluidFlows(port1Flow, internalFlow);

	convection->compute(massFlowRate);
	convection->updateHeatFlow(wallHeatFlow);

	double netHeatFlowRate = convection->getHeatFlowRate();
	double netEnthalpyFlow = internalFlow->enthalpyFlowRate + port2Flow->enthalpyFlowRate;
	double netMassFlowRate = internalFlow->massFlowRate + port2Flow->massFlowRate;

	accFluid->compute(netMassFlowRate, netEnthalpyFlow, netHeatFlowRate, 0);
}

/**
 * PipeHeatExchPrDrop_RC - C
 */
PipeHeatExchPrDrop_RC* PipeHeatExchPrDrop_RC_new(double internalVolume, FrictionFlowPipe* friction, ForcedConvection* convection) {
	return new PipeHeatExchPrDrop_RC(internalVolume, friction, convection);
}

void PipeHeatExchPrDrop_RC_setStateValues(PipeHeatExchPrDrop_RC* pipe, double value1, double value2) {
	pipe->setStateValues(value1, value2);
}
void PipeHeatExchPrDrop_RC_getStateValues(PipeHeatExchPrDrop_RC* pipe, double* value1, double* value2) {
	pipe->getStateValues(value1, value2);
}
void PipeHeatExchPrDrop_RC_getStateDerivatives(PipeHeatExchPrDrop_RC* pipe, double* value1, double* value2) {
	pipe->getStateDerivatives(value1, value2);
}
