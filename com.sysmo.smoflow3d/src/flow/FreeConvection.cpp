/*
 * NaturalConvection.cpp
 *
 *  Created on: Aug 10, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "FreeConvection.h"

using namespace smoflow;

FreeConvection::FreeConvection() {
}

FreeConvection::~FreeConvection() {
}

void FreeConvection::init(MediumState* fluidState, ThermalNode* wallNode,
		FreeConvectionModel* convectionModel) {
	Convection::init(fluidState, wallNode);
	this->convectionModel = convectionModel;
	lengthScale = convectionModel->getLengthScale();
	lengthScale3 = lengthScale * lengthScale * lengthScale;
	heatExchangeArea = convectionModel->getHeatExchangeArea();
}

void FreeConvection::compute() {
	const double g = 9.81; // m/s**2
	// Calculate film state
	double fluidTemperature = fluidState->T();
	double wallTemperature = wallNode->getTemperature();
	double filmTemperature = (fluidTemperature + wallTemperature)/2;
	double wallOverheat = wallTemperature - fluidTemperature;
	filmState->update_Tp(filmTemperature, fluidState->p());
	// Calculate Rayleigh & Prandtl number
	double eta = filmState->mu() / filmState->rho();
	Gr = filmState->beta() * g * lengthScale3 * m::fabs(wallOverheat) / (eta * eta );
	Pr = filmState->Pr();
	Ra = Gr * Pr;
	Nu = convectionModel->computeNusseltNumber(Ra, Pr);
	convectionCoefficient = Nu * filmState->lambda() / lengthScale;
	heatFlowRate = convectionCoefficient * heatExchangeArea * wallOverheat;
}

FreeConvection* FreeConvection_new() {
	return new FreeConvection();
}

void FreeConvection_init(FreeConvection* convection, MediumState* fluidState,
		ThermalNode* wallNode, FreeConvectionModel* convectionModel) {
	convection->init(fluidState, wallNode, convectionModel);
}
void FreeConvection_compute(FreeConvection* convection) {
	convection->compute();
}

double FreeConvection_getGrashofNumber(FreeConvection* convection) {
	return convection->getGrashofNumber();
}

double FreeConvection_getRayleighNumber(FreeConvection* convection) {
	return convection->getRayleighNumber();
}

double FreeConvection_getPrandtlNumber(FreeConvection* convection) {
	return convection->getPrandtlNumber();
}

double FreeConvection_getNusseltNumber(FreeConvection* convection) {
	return convection->getNusseltNumber();
}

double FreeConvection_getConvectionCoefficient(FreeConvection* convection) {
	return convection->getConvectionCoefficient();
}

double FreeConvection_getHeatFlowRate(FreeConvection* convection) {
	return convection->getHeatFlowRate();
}
void FreeConvection_getFlow_Wall(FreeConvection* convection, HeatFlow* flow) {
	convection->getFlow_Wall(flow);
}

void FreeConvection_getFlow_Fluid(FreeConvection* convection, FluidFlow* flow) {
	convection->getFlow_Fluid(flow);
}
