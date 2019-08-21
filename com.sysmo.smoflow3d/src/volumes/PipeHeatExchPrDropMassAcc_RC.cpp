/*
 * PipeHeatExchPrDropMassAcc_RC.cpp
 *
 *  Created on: Aug 23, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "PipeHeatExchPrDropMassAcc_RC.h"

using namespace smoflow;

/**
 * PipeHeatExchPrDrop_RC - C++
 */
PipeHeatExchPrDropMassAcc_RC::PipeHeatExchPrDropMassAcc_RC(
		int allowBidirectionalFlow,
		double internalVolume,
		FrictionFlowPipe* friction,
		ForcedConvection* convection) {
	this->allowBidirectionalFlow = allowBidirectionalFlow;
	this->volume = internalVolume;
	this->friction = friction;
	this->convection = convection;
	SMOCOMPONENT_SET_PARENT(this->convection, this);

	accFluid = NULL;
	internalFlow = NULL;

	port1State = NULL;
	port1Flow = NULL;

	port2State = NULL;
	port2Flow = NULL;

	wallNode = NULL;
	wallHeatFlow = NULL;
}

PipeHeatExchPrDropMassAcc_RC::~PipeHeatExchPrDropMassAcc_RC() {
}

void PipeHeatExchPrDropMassAcc_RC::init(FluidFlow* port2Flow) {
	this->port2Flow = port2Flow;

	this->port1Flow = FluidFlow_new();
	FluidFlow_register(this->port1Flow);

	this->wallHeatFlow = HeatFlow_new();
	HeatFlow_register(this->wallHeatFlow);

	friction->init(port1State, port2State);
	convection->init(port2State, port2State, wallNode); //:TRICKY: the both states of the convection are the internal pipe state
	convection->setLimitOutput(false);

	internalFlow = FluidFlow_new();
	FluidFlow_register(internalFlow);
}

void PipeHeatExchPrDropMassAcc_RC::initOuterStates(MediumState* port1State, ThermalNode* wallNode) {
	this->port1State = port1State;
	this->wallNode = wallNode;
}

void PipeHeatExchPrDropMassAcc_RC::initInternalState(Medium* fluid, int stateVariableSelection, StateVariableSet& internalStateInitialValues) {
	accFluid = FluidChamber_new(fluid);
	SMOCOMPONENT_SET_PARENT(accFluid, this);

	accFluid->setVolume(volume);
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

	port2State = accFluid->getFluidState();
	port2State->init(internalStateInitialValues);
}

void PipeHeatExchPrDropMassAcc_RC::getStateValues(double* value1, double* value2) {
	accFluid->getStateValues(value1, value2, true);
}

void PipeHeatExchPrDropMassAcc_RC::setStateValues(double value1, double value2) {
	accFluid->setStateValues(value1, value2);
}

void PipeHeatExchPrDropMassAcc_RC::getStateDerivatives(double* value1, double* value2) {
	accFluid->getStateDerivatives(value1, value2);
}

void PipeHeatExchPrDropMassAcc_RC::compute() {
	double pressureDrop = port1State->p() - port2State->p();
	if (allowBidirectionalFlow == 0 && pressureDrop > 0) { //only one direction
		compute(cst::zeroPressureDrop);  //:TRICKY: block flow in the opposite direction (i.e. compute zero mass flow rate)
	} else {
		compute(pressureDrop);
	}
}

void PipeHeatExchPrDropMassAcc_RC::compute_deactivedFluidFlow() {
	compute(cst::zeroPressureDrop);  //:TRICKY: to compute zero mass flow rate
}

void PipeHeatExchPrDropMassAcc_RC::compute(double pressureDrop) {
	double massFlowRate = friction->computeMassFlowRate(pressureDrop);
	friction->updateFluidFlows(port1Flow, internalFlow, massFlowRate);

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
PipeHeatExchPrDropMassAcc_RC* PipeHeatExchPrDropMassAcc_RC_new(int allowBidirectionalFlow, double internalVolume,
		FrictionFlowPipe* friction, ForcedConvection* convection) {
	return new PipeHeatExchPrDropMassAcc_RC(allowBidirectionalFlow, internalVolume, friction, convection);
}

void PipeHeatExchPrDropMassAcc_RC_init(PipeHeatExchPrDropMassAcc_RC* pipe, FluidFlow* port2Flow) {
	pipe->init(port2Flow);
}

void PipeHeatExchPrDropMassAcc_RC_initOuterStates(PipeHeatExchPrDropMassAcc_RC* pipe, MediumState* port1State, ThermalNode* wallNode) {
	pipe->initOuterStates(port1State, wallNode);
}

void PipeHeatExchPrDropMassAcc_RC_initInternalState(PipeHeatExchPrDropMassAcc_RC* pipe,
		Medium* fluid, int stateVariableSelection, StateVariableSet innerStateInitializer) {
	pipe->initInternalState(fluid, stateVariableSelection, innerStateInitializer);
}

void PipeHeatExchPrDropMassAcc_RC_compute(PipeHeatExchPrDropMassAcc_RC* pipe) {
	pipe->compute();
}

void PipeHeatExchPrDropMassAcc_RC_compute_deactivedFluidFlow(PipeHeatExchPrDropMassAcc_RC* pipe) {
	pipe->compute_deactivedFluidFlow();
}

void PipeHeatExchPrDropMassAcc_RC_setStateValues(PipeHeatExchPrDropMassAcc_RC* pipe, double value1, double value2) {
	pipe->setStateValues(value1, value2);
}
void PipeHeatExchPrDropMassAcc_RC_getStateValues(PipeHeatExchPrDropMassAcc_RC* pipe, double* value1, double* value2) {
	pipe->getStateValues(value1, value2);
}
void PipeHeatExchPrDropMassAcc_RC_getStateDerivatives(PipeHeatExchPrDropMassAcc_RC* pipe, double* value1, double* value2) {
	pipe->getStateDerivatives(value1, value2);
}

MediumState* PipeHeatExchPrDropMassAcc_RC_getPort2State(PipeHeatExchPrDropMassAcc_RC* pipe) {
	return pipe->getPort2State();
}

FluidFlow* PipeHeatExchPrDropMassAcc_RC_getPort1Flow(PipeHeatExchPrDropMassAcc_RC* pipe) {
	return pipe->getPort1Flow();
}

HeatFlow* PipeHeatExchPrDropMassAcc_RC_getWallHeatFlow(PipeHeatExchPrDropMassAcc_RC* pipe) {
	return pipe->getWallHeatFlow();
}

double PipeHeatExchPrDropMassAcc_RC_getVolume(PipeHeatExchPrDropMassAcc_RC* component) {
	return component->getVolume();
}

double PipeHeatExchPrDropMassAcc_RC_getFluidMass(PipeHeatExchPrDropMassAcc_RC* component) {
	return component->getFluidMass();
}
