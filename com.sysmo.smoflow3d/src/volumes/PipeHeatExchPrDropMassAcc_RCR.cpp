/*
 * PipeHeatExchPrDropMassAcc_RCR.cpp
 *
 *  Created on: Nov 28, 2019
 *      Author: Milen Borisov, Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "PipeHeatExchPrDropMassAcc_RCR.h"

using namespace smoflow;

/**
 * PipeHeatExchPrDrop_RC - C++
 */
PipeHeatExchPrDropMassAcc_RCR::PipeHeatExchPrDropMassAcc_RCR(
		int allowBidirectionalFlow,
		double internalVolume,
		FrictionFlowPipe* friction1,
		FrictionFlowPipe* friction2,
		ForcedConvection* convection) {
	this->allowBidirectionalFlow = allowBidirectionalFlow;
	this->volume = internalVolume;
	this->friction1 = friction1;
	this->friction2 = friction2;
	this->convection = convection;
	SMOCOMPONENT_SET_PARENT(this->convection, this);

	accFluid = NULL;
	internalFlow1 = NULL;
	internalFlow2 = NULL;
	internalState = NULL;

	port1State = NULL;
	port1Flow = NULL;

	port2State = NULL;
	port2Flow = NULL;

	wallNode = NULL;
	wallHeatFlow = NULL;
}

PipeHeatExchPrDropMassAcc_RCR::~PipeHeatExchPrDropMassAcc_RCR() {
}

void PipeHeatExchPrDropMassAcc_RCR::init() {
	this->port1Flow = FluidFlow_new();
	FluidFlow_register(this->port1Flow);

	this->port2Flow = FluidFlow_new();
	FluidFlow_register(this->port2Flow);

	this->wallHeatFlow = HeatFlow_new();
	HeatFlow_register(this->wallHeatFlow);

	internalFlow1 = FluidFlow_new();
	FluidFlow_register(internalFlow1);

	internalFlow2 = FluidFlow_new();
	FluidFlow_register(internalFlow2);

	friction1->init(port1State, internalState);
	friction2->init(internalState, port2State);
	convection->init(internalState, internalState, wallNode); //:TRICKY: the both states of the convection are the internal pipe state
	convection->setLimitOutput(false);
}

void PipeHeatExchPrDropMassAcc_RCR::initOuterStates(
		MediumState* port1State, MediumState* port2State, ThermalNode* wallNode) {
	this->port1State = port1State;
	this->port2State = port2State;
	this->wallNode = wallNode;
}

void PipeHeatExchPrDropMassAcc_RCR::initInternalState(
		Medium* fluid,
		int stateVariableSelection,
		StateVariableSet& internalStateInitialValues) {
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

	internalState = accFluid->getFluidState();
	internalState->init(internalStateInitialValues);
}

void PipeHeatExchPrDropMassAcc_RCR::getStateValues(double* value1, double* value2) {
	accFluid->getStateValues(value1, value2, true);
}

void PipeHeatExchPrDropMassAcc_RCR::setStateValues(double value1, double value2) {
	accFluid->setStateValues(value1, value2);
}

void PipeHeatExchPrDropMassAcc_RCR::getStateDerivatives(double* value1, double* value2) {
	accFluid->getStateDerivatives(value1, value2);
}

void PipeHeatExchPrDropMassAcc_RCR::compute() {
	double pressureDrop1 = port1State->p() - internalState->p();
	double pressureDrop2 = internalState->p() - port2State->p();
	if (allowBidirectionalFlow == 0 && pressureDrop1 > 0 && pressureDrop2 > 0) { //allow only one direction
		compute_deactivedFluidFlow();  //:TRICKY: the flow is in the opposite direction (i.e. compute zero mass flow rate)
	} else {
		compute(pressureDrop1, pressureDrop2);
	}
}

void PipeHeatExchPrDropMassAcc_RCR::compute_deactivedFluidFlow() {
	compute(cst::zeroPressureDrop, cst::zeroPressureDrop);
}

void PipeHeatExchPrDropMassAcc_RCR::compute(double pressureDrop1, double pressureDrop2) {
	double massFlowRate1 = friction1->computeMassFlowRate(pressureDrop1);
	friction1->updateFluidFlows(port1Flow, internalFlow1, massFlowRate1);

	double massFlowRate2 = friction2->computeMassFlowRate(pressureDrop2);
	friction2->updateFluidFlows(internalFlow2, port2Flow, massFlowRate2);

	convection->compute(m::quadratic_mean(massFlowRate1, massFlowRate2)); //:TRICKY:
	convection->updateHeatFlow(wallHeatFlow);

	double netHeatFlowRate = convection->getHeatFlowRate();
	double netEnthalpyFlow = internalFlow1->enthalpyFlowRate + internalFlow2->enthalpyFlowRate;
	double netMassFlowRate = internalFlow1->massFlowRate + internalFlow2->massFlowRate;

	accFluid->compute(netMassFlowRate, netEnthalpyFlow, netHeatFlowRate, 0, 0); //volume = volumeDot = 0
}


/**
 * PipeHeatExchPrDrop_RC - C
 */
PipeHeatExchPrDropMassAcc_RCR* PipeHeatExchPrDropMassAcc_RCR_new(
		int allowBidirectionalFlow, double internalVolume,
		FrictionFlowPipe* friction1, FrictionFlowPipe* friction2,
		ForcedConvection* convection) {
	return new PipeHeatExchPrDropMassAcc_RCR(
			allowBidirectionalFlow, internalVolume,
			friction1, friction2,
			convection);
}

void PipeHeatExchPrDropMassAcc_RCR_init(PipeHeatExchPrDropMassAcc_RCR* pipe) {
	pipe->init();
}

void PipeHeatExchPrDropMassAcc_RCR_initOuterStates(
		PipeHeatExchPrDropMassAcc_RCR* pipe,
		MediumState* port1State,
		MediumState* port2State,
		ThermalNode* wallNode) {
	pipe->initOuterStates(port1State, port2State, wallNode);
}

void PipeHeatExchPrDropMassAcc_RCR_initInternalState(PipeHeatExchPrDropMassAcc_RCR* pipe,
		Medium* fluid, int stateVariableSelection, StateVariableSet innerStateInitializer) {
	pipe->initInternalState(fluid, stateVariableSelection, innerStateInitializer);
}

void PipeHeatExchPrDropMassAcc_RCR_compute(PipeHeatExchPrDropMassAcc_RCR* pipe) {
	pipe->compute();
}

void PipeHeatExchPrDropMassAcc_RCR_compute_deactivedFluidFlow(PipeHeatExchPrDropMassAcc_RCR* pipe) {
	pipe->compute_deactivedFluidFlow();
}

void PipeHeatExchPrDropMassAcc_RCR_setStateValues(PipeHeatExchPrDropMassAcc_RCR* pipe, double value1, double value2) {
	pipe->setStateValues(value1, value2);
}
void PipeHeatExchPrDropMassAcc_RCR_getStateValues(PipeHeatExchPrDropMassAcc_RCR* pipe, double* value1, double* value2) {
	pipe->getStateValues(value1, value2);
}
void PipeHeatExchPrDropMassAcc_RCR_getStateDerivatives(PipeHeatExchPrDropMassAcc_RCR* pipe, double* value1, double* value2) {
	pipe->getStateDerivatives(value1, value2);
}

FluidFlow* PipeHeatExchPrDropMassAcc_RCR_getPort1Flow(PipeHeatExchPrDropMassAcc_RCR* pipe) {
	return pipe->getPort1Flow();
}

FluidFlow* PipeHeatExchPrDropMassAcc_RCR_getPort2Flow(PipeHeatExchPrDropMassAcc_RCR* pipe) {
	return pipe->getPort2Flow();
}

MediumState* PipeHeatExchPrDropMassAcc_RCR_getInternalFluidState(PipeHeatExchPrDropMassAcc_RCR* pipe) {
	return pipe->getInternalFluidState();
}

HeatFlow* PipeHeatExchPrDropMassAcc_RCR_getWallHeatFlow(PipeHeatExchPrDropMassAcc_RCR* pipe) {
	return pipe->getWallHeatFlow();
}

double PipeHeatExchPrDropMassAcc_RCR_getVolume(PipeHeatExchPrDropMassAcc_RCR* component) {
	return component->getVolume();
}

double PipeHeatExchPrDropMassAcc_RCR_getFluidMass(PipeHeatExchPrDropMassAcc_RCR* component) {
	return component->getFluidMass();
}
