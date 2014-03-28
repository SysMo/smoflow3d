/*
 * CryopumpHeatExch.cpp
 *
 *  Created on: Jul 31, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "CryopumpHeatExch.h"
using namespace smoflow;

/**
 * CryopumpHeatExch - C++
 */
CryopumpHeatExch::CryopumpHeatExch() {
	/* Inputs */
	rotationalSpeed = 0.0;

	/* Inputs (parameters) */
	computationMethod = 1; //1 - outlet temperature (constant); 2 - outlet temperature (compute)
	displacementVolume = 0.0;
	volumetricEfficiencyFunction = NULL;
	isentropicEfficiencyFunction = NULL;
	mechanicalEfficiencyFunction = NULL;
	outletTemperatureFunction = NULL;
	heatFlowRateToPumpReservoirParam = 0.0;
	fractionOfExtraHeatToFluid = 0.0;

	/* Results */
	massFlowRate = 0.0;
	pressureRatio = 0.0;
	isentropicEfficiency = 0.0;
	mechanicalEfficiency = 0.0;
	volumetricEfficiency = 0.0;
	pumpWork = 0.0;
	torque = 0.0;
	outletTemperature = 0.0;
	heatFlowRateToPumpReservoir = 0.0;

	/* Intermediate variables */
	outletFlowStateIdeal = NULL;
	outletFlowStateReal = NULL;
	outletEnthalpyReal = 0.0;

	/* States */
	inletState = NULL;
	outletState = NULL;
}

CryopumpHeatExch::~CryopumpHeatExch() {
	// At the moment states are meant to be deleted centrally
	// delete outletFlowStateIdeal;
	if (volumetricEfficiencyFunction != NULL) {
		delete volumetricEfficiencyFunction;
	}
	if (isentropicEfficiencyFunction != NULL) {
		delete isentropicEfficiencyFunction;
	}
	if (mechanicalEfficiencyFunction != NULL) {
		delete mechanicalEfficiencyFunction;
	}
	if (outletTemperatureFunction != NULL) {
		delete outletTemperatureFunction;
	}
}

void CryopumpHeatExch::init(MediumState* inletState, MediumState* outletState) {
	// Check parameters
	if (isentropicEfficiencyFunction == NULL && !computeUsingOutletTemperature()) {
		RaiseComponentError(this, "Function for evaluating isentropic efficiency not set");
	}
	if (mechanicalEfficiencyFunction == NULL) {
		RaiseComponentError(this, "Function for evaluating mechanical efficiency not set");
	}
	if (volumetricEfficiencyFunction == NULL) {
		RaiseComponentError(this, "Function for evaluating volumetric efficiency not set");
	}
	if (outletTemperatureFunction == NULL && computeUsingOutletTemperature()) {
		RaiseComponentError(this, "Function for evaluating outlet temperature not set");
	}

	if (inletState->getMedium() != outletState->getMedium()) {
		RaiseComponentError(this, "Different media connected to the pump!");
	}
	this->inletState = inletState;
	this->outletState = outletState;

	outletFlowStateIdeal = MediumState_new(inletState->getMedium());
	MediumState_register(outletFlowStateIdeal);

	outletFlowStateReal = MediumState_new(inletState->getMedium());
	MediumState_register(outletFlowStateReal);
}

void CryopumpHeatExch::compute() {
	// Check
	if (rotationalSpeed < 0) {
		RaiseComponentError(this, "pump is not allowed to operate in reverse" );
	}

	// Compute pressure ratio
	pressureRatio = outletState->p() / inletState->p();


	// Compute mass flow rate
	double rotationalSpeedRPM = rotationalSpeed / (2 * M_PI) * 60; // [rad/s] -> [rev/min]
	double outletPressureBar = outletState->p() / 1.e+005;

	volumetricEfficiency = (*volumetricEfficiencyFunction)(rotationalSpeedRPM, outletPressureBar);
	m::limitVariable(volumetricEfficiency, 0, 1);

	double volumetricFlowRate = volumetricEfficiency * rotationalSpeed / (2 * M_PI) * displacementVolume;
	massFlowRate = volumetricFlowRate * inletState->rho();


	// Compute real outlet enthalpy, outlet temperature,
	double workReal = 0.0;
	if (computeUsingOutletTemperature()) { //compute using outlet temperature
		heatFlowRateToPumpReservoir = heatFlowRateToPumpReservoirParam;
		outletTemperature = (*outletTemperatureFunction)(rotationalSpeedRPM, outletPressureBar);

		outletFlowStateReal->update_Tp(outletTemperature, outletState->p());
		outletEnthalpyReal = outletFlowStateReal->h();

		workReal = outletFlowStateReal->h() - inletState->h();

	} else { //compute using isentropic efficiency
		if (pressureRatio > 1) { //:TRICKY: Pin > Pout
			// Compute ideal work
			double sIn = inletState->s();
			outletFlowStateIdeal->update_ps(outletState->p(), sIn);
			double workIdeal = outletFlowStateIdeal->h() - inletState->h();

			// Compute real work
			isentropicEfficiency = (*isentropicEfficiencyFunction)(rotationalSpeedRPM, outletPressureBar);
			m::limitVariable(isentropicEfficiency, 0, 1);
			workReal = workIdeal / isentropicEfficiency;

			// Compute additional work
			double workAdditional = workReal - workIdeal;

			// Compute real outlet enthalpy
			outletEnthalpyReal = inletState->h() + workIdeal + workAdditional * fractionOfExtraHeatToFluid;

			// Compute heat flow rate to pump reservoir
			heatFlowRateToPumpReservoir = massFlowRate * (1 - fractionOfExtraHeatToFluid) * workAdditional;
		} else {
			outletEnthalpyReal = inletState->h();
			heatFlowRateToPumpReservoir = 0.0;
		}

		outletFlowStateReal->update_ph(outletState->p(), outletEnthalpyReal);
		outletTemperature = outletFlowStateReal->T();
	}

	// Compute the rest results
	mechanicalEfficiency = (*mechanicalEfficiencyFunction)(rotationalSpeedRPM, outletPressureBar);
	m::limitVariable(mechanicalEfficiency, 0, 1);

	pumpWork = massFlowRate * workReal / mechanicalEfficiency;
	torque = pumpWork / rotationalSpeed;
}

void CryopumpHeatExch::updateFluidFlows(FluidFlow* inletFlow, FluidFlow* outletFlow) {
	inletFlow->massFlowRate = -massFlowRate;
	inletFlow->enthalpyFlowRate = -massFlowRate * inletState->h();

	outletFlow->massFlowRate = massFlowRate;
	outletFlow->enthalpyFlowRate = massFlowRate * outletEnthalpyReal;
}

/**
 * CryopumpHeatExch - C
 */
CryopumpHeatExch* CryopumpHeatExch_new() {
	return new CryopumpHeatExch;
}

void CryopumpHeatExch_init(CryopumpHeatExch* pump, MediumState* inletState, MediumState* outletState) {
	pump->init(inletState, outletState);
}

void CryopumpHeatExch_setRotationalSpeed(CryopumpHeatExch* pump, double rotationalSpeed) {
	pump->setRotationalSpeed(rotationalSpeed);
}

void CryopumpHeatExch_setComputationMethod(CryopumpHeatExch* pump, int computationMethod) {
	pump->setComputationMethod(computationMethod);
}

void CryopumpHeatExch_setDisplacementVolume(CryopumpHeatExch* pump, double displacementVolume) {
	pump->setDisplacementVolume(displacementVolume);
}

void CryopumpHeatExch_setVolumetricEfficiencyFunction(CryopumpHeatExch* pump, FunctorTwoVariables* volumetricEfficiencyFunction) {
	pump->setVolumetricEfficiencyFunction(volumetricEfficiencyFunction);
}

void CryopumpHeatExch_setIsentropicEfficiencyFunction(CryopumpHeatExch* pump, FunctorTwoVariables* isentropicEfficiencyFunction) {
	pump->setIsentropicEfficiencyFunction(isentropicEfficiencyFunction);
}

void CryopumpHeatExch_setMechanicalEfficiencyFunction(CryopumpHeatExch* pump, FunctorTwoVariables* mechanicalEfficiencyFunction) {
	pump->setMechanicalEfficiencyFunction(mechanicalEfficiencyFunction);
}

void CryopumpHeatExch_setOutletTemperatureFunction(CryopumpHeatExch* pump, FunctorTwoVariables* outletTemperatureFunction) {
	pump->setOutletTemperatureFunction(outletTemperatureFunction);
}

void CryopumpHeatExch_setHeatFlowRateToPumpReservoir(CryopumpHeatExch* pump, double heatFlowRateToPumpReservoir) {
	pump->setHeatFlowRateToPumpReservoir(heatFlowRateToPumpReservoir);
}

void CryopumpHeatExch_setFractionOfExtraHeatToFluid(CryopumpHeatExch* pump, double fractionOfExtraHeatToFluid) {
	pump->setFractionOfExtraHeatToFluid(fractionOfExtraHeatToFluid);
}

void CryopumpHeatExch_compute(CryopumpHeatExch* pump) {
	pump->compute();
}

void CryopumpHeatExch_updateFluidFlows(CryopumpHeatExch* pump, FluidFlow* inletFlow, FluidFlow* outletFlow) {
	pump->updateFluidFlows(inletFlow, outletFlow);
}

double CryopumpHeatExch_getPressureRatio(CryopumpHeatExch* pump) {
	return pump->getPressureRatio();
}

double CryopumpHeatExch_getIsentropicEfficiency(CryopumpHeatExch* pump){
	return pump->getIsentropicEfficiency();
}

double CryopumpHeatExch_getMechanicalEfficiency(CryopumpHeatExch* pump){
	return pump->getMechanicalEfficiency();
}

double CryopumpHeatExch_getVolumetricEfficiency(CryopumpHeatExch* pump){
	return pump->getVolumetricEfficiency();
}

double CryopumpHeatExch_getPumpWork(CryopumpHeatExch* pump) {
	return pump->getPumpWork();
}

double CryopumpHeatExch_getTorque(CryopumpHeatExch* pump) {
	return pump->getTorque();
}

double CryopumpHeatExch_getOutletTemperature(CryopumpHeatExch* pump) {
	return pump->getOutletTemperature();
}

double CryopumpHeatExch_getHeatFlowRateToPumpReservoir(CryopumpHeatExch* pump) {
	return pump->getHeatFlowRateToPumpReservoir();
}
