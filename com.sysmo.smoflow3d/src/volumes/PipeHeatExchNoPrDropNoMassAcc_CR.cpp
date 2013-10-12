/*
 * PipeHeatExchNoPrDropNoMassAccCR.cpp
 *
 *  Created on: Aug 23, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "PipeHeatExchNoPrDropNoMassAcc_CR.h"
using namespace smoflow;

/**
 * PipeHeatExchNoPrDropNoMassAcc_CR - C++
 */
PipeHeatExchNoPrDropNoMassAcc_CR::PipeHeatExchNoPrDropNoMassAcc_CR(double heatExhcangeEfficienccy) {
	this->heatExhcangeEfficienccy = heatExhcangeEfficienccy;

	wallNode = NULL;
	fluidStateOutlet = NULL;
	fluidFlowInlet = NULL;

	inletTemperature = 0.0;
	outletTemperature = 0.0;
	wallTemperature = 0.0;
	wallHeatFlowRate = 0.0;
	massFlowRateInlet = 0.0;

	fluidStateOutletInternal = NULL;
	fluidStateInletInternal = NULL;
	fluidFlowOutlet = NULL;
	fluidFlowOutletIndex = -1;
	wallHeatFlow = NULL;
	wallHeatFlowIndex = -1;
}

PipeHeatExchNoPrDropNoMassAcc_CR::~PipeHeatExchNoPrDropNoMassAcc_CR() {
}

void PipeHeatExchNoPrDropNoMassAcc_CR::init(
		ThermalNode* wallNode,
		MediumState* fluidStateOutlet,
		FluidFlow* fluidFlowInlet) {
	this->wallNode = wallNode;
	this->fluidStateOutlet = fluidStateOutlet;
	this->fluidFlowInlet = fluidFlowInlet;

	int mediumIndexOutlet = Medium_index(fluidStateOutlet->getMedium());
	Medium* fluid = Medium_get(mediumIndexOutlet);

	fluidStateOutletInternal = MediumState_new(fluid);
	MediumState_register(fluidStateOutletInternal);

	fluidStateInletInternal = MediumState_new(fluid);
	MediumState_register(fluidStateInletInternal);

	fluidFlowOutlet = FluidFlow_new();
	fluidFlowOutletIndex = FluidFlow_register(fluidFlowOutlet);

	wallHeatFlow = HeatFlow_new();
	wallHeatFlowIndex = HeatFlow_register(wallHeatFlow);
}

void PipeHeatExchNoPrDropNoMassAcc_CR::compute() {
	if (fluidFlowInlet->massFlowRate < 0.0) {
		RaiseComponentError(this, "Reverse flow encouuntered. Restrict the flow direction, e.g. by adding check valve.");
	}

	wallTemperature =  wallNode->getTemperature();
	if (fluidFlowInlet->massFlowRate > 1e-8) {
		double inletSpecificEnthalpy = fluidFlowInlet->enthalpyFlowRate / fluidFlowInlet->massFlowRate;
		fluidStateInletInternal->update_ph(fluidStateOutlet->p(), inletSpecificEnthalpy);

		inletTemperature = fluidStateInletInternal->T();
		outletTemperature = inletTemperature + (wallTemperature - inletTemperature) * heatExhcangeEfficienccy;

		fluidStateOutletInternal->update_Tp(outletTemperature, fluidStateOutlet->p());

		fluidFlowOutlet->massFlowRate = fluidFlowInlet->massFlowRate;
		fluidFlowOutlet->enthalpyFlowRate = fluidStateOutletInternal->h() * fluidFlowInlet->massFlowRate;

		wallHeatFlow->enthalpyFlowRate = fluidFlowInlet->enthalpyFlowRate - fluidFlowOutlet->enthalpyFlowRate;
	} else {
		outletTemperature = 0.0;
		inletTemperature = 0.0;

		fluidFlowOutlet->massFlowRate = 0.0;
		fluidFlowOutlet->enthalpyFlowRate = 0.0;

		wallHeatFlow->enthalpyFlowRate = 0.0;
	}

	wallHeatFlowRate = wallHeatFlow->enthalpyFlowRate;
	massFlowRateInlet = fluidFlowInlet->massFlowRate;
}

/**
 * PipeHeatExchNoPrDropNoMassAcc_CR - C
 */
PipeHeatExchNoPrDropNoMassAcc_CR* PipeHeatExchNoPrDropNoMassAcc_CR_new(double heatExhcangeEfficienccy) {
	return new PipeHeatExchNoPrDropNoMassAcc_CR(heatExhcangeEfficienccy);
}

void PipeHeatExchNoPrDropNoMassAcc_CR_init(PipeHeatExchNoPrDropNoMassAcc_CR* pipe,
		ThermalNode* wallNode, MediumState* fluidStateOutlet, FluidFlow* fluidFlowInlet) {
	pipe->init(wallNode, fluidStateOutlet, fluidFlowInlet);
}

void PipeHeatExchNoPrDropNoMassAcc_CR_compute(PipeHeatExchNoPrDropNoMassAcc_CR* pipe) {
	pipe->compute();
}

int PipeHeatExchNoPrDropNoMassAcc_CR_getFluidFlowOutletIndex(PipeHeatExchNoPrDropNoMassAcc_CR* pipe) {
	return pipe->getFluidFlowOutletIndex();
}

int PipeHeatExchNoPrDropNoMassAcc_CR_getWallHeatFlowIndex(PipeHeatExchNoPrDropNoMassAcc_CR* pipe) {
	return pipe->getWallHeatFlowIndex();
}

double PipeHeatExchNoPrDropNoMassAcc_CR_getInletTemperature(PipeHeatExchNoPrDropNoMassAcc_CR* pipe) {
	return pipe->getInletTemperature();
}

double PipeHeatExchNoPrDropNoMassAcc_CR_getOutletTemperature(PipeHeatExchNoPrDropNoMassAcc_CR* pipe) {
	return pipe->getOutletTemperature();
}

double PipeHeatExchNoPrDropNoMassAcc_CR_getWallTemperature(PipeHeatExchNoPrDropNoMassAcc_CR* pipe) {
	return pipe->getWallTemperature();
}

double PipeHeatExchNoPrDropNoMassAcc_CR_getWallHeatFlowRate(PipeHeatExchNoPrDropNoMassAcc_CR* pipe) {
	return pipe->getWallHeatFlowRate();
}

double PipeHeatExchNoPrDropNoMassAcc_CR_getMassFlowRateInlet(PipeHeatExchNoPrDropNoMassAcc_CR* pipe) {
	return pipe->getMassFlowRateInlet();
}
