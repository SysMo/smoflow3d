/*
 * PipeHeatExchanger_R.cpp
 *
 *  Created on: Sep 19, 2014
 *      Author: Milen Borisov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "PipeHeatExchanger_R.h"
using namespace smoflow;

/**
 * PipeHeatExchanger_R - C++
 */
PipeHeatExchanger_R::PipeHeatExchanger_R(FrictionFlowPipe* friction, ForcedConvection* convection) :
		Pipe_R(friction) {
	this->convection = convection;
	SMOCOMPONENT_SET_PARENT(this->convection, this);

	wallHeatFlow = HeatFlow_new();
	HeatFlow_register(wallHeatFlow);

	wallNode = NULL;
	limitStateT = NULL;
}

PipeHeatExchanger_R::~PipeHeatExchanger_R() {
}

void PipeHeatExchanger_R::init(MediumState* state1Input) {
	limitStateT = MediumState_new(state1Input->getMedium());
	MediumState_register(limitStateT);

	Pipe_R::init(state1Input);
	convection->init(state1, state2, wallNode);
}

bool PipeHeatExchanger_R::compute(double massFlowRate, double minDownstreamPressure) {
	// Compute pressure drop
	friction->computePressureDrop(massFlowRate);

	// Try to compute downstream pressure
	MediumState* upstreamState = getUpstreamState(massFlowRate);
	double downstreamPressure = upstreamState->p() - friction->getAbsolutePressureDrop();
	if (downstreamPressure < minDownstreamPressure or downstreamPressure <= 0.0) {
		return false;
	}

	// Compute heat flow rate
	convection->compute(massFlowRate);
	convection->updateHeatFlow(wallHeatFlow);

	// Compute downstream enthalpy
	double downstreamEnthalpy = upstreamState->h() + convection->getHeatFlowRate() / m::fabs(massFlowRate);

	double wallTemperature = wallNode->getTemperature();
	limitStateT->update_Tp(wallNode->getTemperature(), upstreamState->p());
	if (wallTemperature >  upstreamState->T()) {// Ensure the outlet temperature is not above wall temperature
		if (downstreamEnthalpy > limitStateT->h()) {
			downstreamEnthalpy = limitStateT->h();
		}
	} else { // Ensure the outlet temperature is not below wall temperature
		if (downstreamEnthalpy < limitStateT->h()) {
			downstreamEnthalpy = limitStateT->h();
		}
	}

	// Set downstream state
	MediumState* downstreamState = getDownstreamState(massFlowRate);
	downstreamState->update_ph(downstreamPressure, downstreamEnthalpy);
	return true;
}

void  PipeHeatExchanger_R::compute_NoMassFlowRate() {
	convection->compute_NoHeatFlow();
	convection->updateHeatFlow(wallHeatFlow);
}

/**
 * PipeHeatExchanger_R - C
 */
PipeHeatExchanger_R* PipeHeatExhcanger_R_new(FrictionFlowPipe* friction, ForcedConvection* convection) {
	return new PipeHeatExchanger_R(friction, convection);
}

PipeHeatExchanger_R* StraightPipeHeatExchanger_R_new(
		double length,
		double hydraulicDiameter,
		double flowArea,
		double surfaceRoughness,
		double pressureDropGain,
		double heatExchangeGain,
		int forcedConvectionLimitOutput,
		int forcedConvectionUseFilmState) {
	FrictionFlowPipe* friction = FrictionFlowPipe_StraightPipe_new(length, hydraulicDiameter, flowArea, surfaceRoughness);
	friction->setPressureDropGain(pressureDropGain);

	ForcedConvection* convection = ForcedConvection_StraightPipe_new(length, hydraulicDiameter, flowArea);
	convection->setHeatExchangeGain(heatExchangeGain);
	if (forcedConvectionLimitOutput == 1) {
		convection->setLimitOutput(true);
	} else {
		convection->setLimitOutput(false);
	}

	if (forcedConvectionUseFilmState == 1) {
		convection->setUseFilmState(true);
	} else {
		convection->setUseFilmState(false);
	}


	return PipeHeatExhcanger_R_new(friction, convection);
}

HeatFlow* PipeHeatExchanger_R_getWallHeatFlow(PipeHeatExchanger_R* pipe) {
	return pipe->getWallHeatFlow();
}

ForcedConvection* PipeHeatExchanger_R_getConvection(PipeHeatExchanger_R* pipe) {
	return pipe->getConvection();
}

void PipeHeatExchanger_R_setHeatExchangerThermalNode(PipeHeatExchanger_R* pipe, ThermalNode* wallNode) {
	pipe->setHeatExchangerThermalNode(wallNode);
}
