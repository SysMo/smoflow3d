/*
 * ForcedConvection.cpp
 *
 *  Created on: Aug 10, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "ForcedConvection.h"

ForcedConvection::ForcedConvection() {
	// TODO Auto-generated constructor stub

}

ForcedConvection::~ForcedConvection() {
	// TODO Auto-generated destructor stub
}

void ForcedConvection::init(MediumState* fluidState, ThermalNode* wallNode,
		ForcedConvectionModel* convectionModel, FluidFlow* flow) {
	Convection::init(fluidState, wallNode);
	this->convectionModel = convectionModel;
	this->flow = flow;
	characteristicLength = convectionModel->getCharacteristicLength();
	heatExchangeArea = convectionModel->getHeatExchangeArea();
	flowArea = convectionModel->getFlowArea();
}

void ForcedConvection::compute() {
	// Calculate film state
	double fluidTemperature = fluidState->T();
	double wallTemperature = wallNode->getTemperature();
	double filmTemperature = (fluidTemperature + wallTemperature)/2;
	double wallOverheat = wallTemperature - fluidTemperature;
	filmState->update_Tp(filmTemperature, fluidState->p());


	double v = flow->massFlowRate / filmState->rho() / flowArea;
	Re = filmState->rho() * v * characteristicLength;
	Pr = filmState->Pr();
	Nu = convectionModel->computeNusseltNumber(Re, Pr);
	convectionCoefficient = Nu * filmState->lambda() / characteristicLength;
	heatFlowRate = convectionCoefficient * heatExchangeArea * wallOverheat;
}

ForcedConvection* ForcedConvection_new() {
	return new ForcedConvection();
}

void ForcedConvection_init(ForcedConvection* convection, MediumState* fluidState,
		ThermalNode* wallNode, ForcedConvectionModel* convectionModel, FluidFlow* flow) {
	convection->init(fluidState, wallNode, convectionModel, flow);
}

void ForcedConvection_compute(ForcedConvection* convection) {
	convection->compute();
}
