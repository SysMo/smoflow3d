/*
 * HeatExchNoPrDropNoMassAcc_CR.cpp
 *
 *  Created on: Aug 23, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "HeatExchNoPrDropNoMassAcc_CR.h"
using namespace smoflow;

/**
 * PipeHeatExchNoPrDropNoMassAcc_CR - C++
 */
HeatExchNoPrDropNoMassAcc_CR::HeatExchNoPrDropNoMassAcc_CR(double heatExhcangeEfficienccy) {
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

HeatExchNoPrDropNoMassAcc_CR::~HeatExchNoPrDropNoMassAcc_CR() {
}

void HeatExchNoPrDropNoMassAcc_CR::init(
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

void HeatExchNoPrDropNoMassAcc_CR::compute() {
	if (fluidFlowInlet->massFlowRate < 0.0) {
		RaiseComponentError(this, "Reverse flow encouuntered. Restrict the flow direction, e.g. by adding check valve.");
	}

	wallTemperature =  wallNode->getTemperature();
	if (fluidFlowInlet->massFlowRate > cst::MinMassFlowRate) {
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
HeatExchNoPrDropNoMassAcc_CR* HeatExchNoPrDropNoMassAcc_CR_new(double heatExhcangeEfficienccy) {
	return new HeatExchNoPrDropNoMassAcc_CR(heatExhcangeEfficienccy);
}

void HeatExchNoPrDropNoMassAcc_CR_init(HeatExchNoPrDropNoMassAcc_CR* heatExch,
		ThermalNode* wallNode, MediumState* fluidStateOutlet, FluidFlow* fluidFlowInlet) {
	heatExch->init(wallNode, fluidStateOutlet, fluidFlowInlet);
}

void HeatExchNoPrDropNoMassAcc_CR_compute(HeatExchNoPrDropNoMassAcc_CR* heatExch) {
	heatExch->compute();
}

int HeatExchNoPrDropNoMassAcc_CR_getFluidFlowOutletIndex(HeatExchNoPrDropNoMassAcc_CR* heatExch) {
	return heatExch->getFluidFlowOutletIndex();
}

int HeatExchNoPrDropNoMassAcc_CR_getWallHeatFlowIndex(HeatExchNoPrDropNoMassAcc_CR* heatExch) {
	return heatExch->getWallHeatFlowIndex();
}

double HeatExchNoPrDropNoMassAcc_CR_getInletTemperature(HeatExchNoPrDropNoMassAcc_CR* heatExch) {
	return heatExch->getInletTemperature();
}

double HeatExchNoPrDropNoMassAcc_CR_getOutletTemperature(HeatExchNoPrDropNoMassAcc_CR* heatExch) {
	return heatExch->getOutletTemperature();
}

double HeatExchNoPrDropNoMassAcc_CR_getWallTemperature(HeatExchNoPrDropNoMassAcc_CR* heatExch) {
	return heatExch->getWallTemperature();
}

double HeatExchNoPrDropNoMassAcc_CR_getWallHeatFlowRate(HeatExchNoPrDropNoMassAcc_CR* heatExch) {
	return heatExch->getWallHeatFlowRate();
}

double HeatExchNoPrDropNoMassAcc_CR_getMassFlowRateInlet(HeatExchNoPrDropNoMassAcc_CR* heatExch) {
	return heatExch->getMassFlowRateInlet();
}
