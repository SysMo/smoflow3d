/*
 * MechanicalCompressor.cpp
 *
 *  Created on: Jul 31, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "MechanicalCompressor.h"
using namespace smoflow;

/**
 * MechanicalCompressor - C++
 */
MechanicalCompressor::MechanicalCompressor() {
	/* Inputs */
	displacementVolume = 0.0;
	rotationalSpeed = 0.0;
	volumetricEfficiencyFunction = NULL;
	volumetricFlowRateFunction = NULL;
	isentropicEfficiencyFunction = NULL;
	mechanicalEfficiencyFunction = NULL;

	/* Results */
	massFlowRate = 0.0;
	pressureRatio = 0.0;
	isentropicEfficiency = 0.0;
	mechanicalEfficiency = 0.0;
	volumetricEfficiency = 0.0;
	compressorWork = 0.0;
	torque = 0.0;

	/* Intermediate variables */
	outletFlowStateIdeal = NULL;
	outletEnthalpyReal = 0.0;

	/* States */
	inletState = NULL;
	outletState = NULL;
}

MechanicalCompressor::~MechanicalCompressor() {
	// At the moment states are meant to be deleted centrally
	// delete outletFlowStateIdeal;
	if (volumetricEfficiencyFunction != NULL) {
		delete volumetricEfficiencyFunction;
	}
	if (volumetricFlowRateFunction != NULL) {
		delete volumetricFlowRateFunction;
	}
	if (isentropicEfficiencyFunction != NULL) {
		delete isentropicEfficiencyFunction;
	}
	if (mechanicalEfficiencyFunction != NULL) {
		delete mechanicalEfficiencyFunction;
	}
}

void MechanicalCompressor::init(MediumState* inletState, MediumState* outletState) {
	// Check parameters
	if (isentropicEfficiencyFunction == NULL) {
		RaiseComponentError(this, "Function for evaluating isentropic efficiency not set");
	}
	if (mechanicalEfficiencyFunction == NULL) {
		RaiseComponentError(this, "Function for evaluating mechanical efficiency not set");
	}
	if (volumetricFlowRateFunction == NULL && volumetricEfficiencyFunction == NULL) {
		RaiseComponentError(this, "Neither 'volumetric flow rate' nor 'volumetric efficiency' functions set");
	}

	if (inletState->getMedium() != outletState->getMedium()) {
		RaiseComponentError(this, "Different media connected to the compressor!");
	}
	this->inletState = inletState;
	this->outletState = outletState;

	outletFlowStateIdeal = MediumState_new(inletState->getMedium());
	MediumState_register(outletFlowStateIdeal);
}

void MechanicalCompressor::compute() {
	pressureRatio = outletState->p() / inletState->p();
	double rotationalSpeedRPM = rotationalSpeed / (2 * M_PI) * 60;

	if (rotationalSpeed < 0) {
		RaiseComponentError(this, "Compressor is not allowed to operate in reverse" );
	}

	double enthalpyChangeReal = 0.0;
	double volumetricFlowRate = 0;
	if (volumetricFlowRateFunction != NULL) {
		volumetricFlowRate = (*volumetricFlowRateFunction)(rotationalSpeedRPM, pressureRatio);
	} else {
		volumetricEfficiency = (*volumetricEfficiencyFunction)(rotationalSpeedRPM, pressureRatio);
		m::limitVariable(volumetricEfficiency, 0, 1);
		volumetricFlowRate = volumetricEfficiency * rotationalSpeed / (2 * M_PI) * displacementVolume;
	}
	massFlowRate = volumetricFlowRate * inletState->rho();

	mechanicalEfficiency = (*mechanicalEfficiencyFunction)(rotationalSpeedRPM, pressureRatio);
	m::limitVariable(mechanicalEfficiency, 0, 1);
	isentropicEfficiency = (*isentropicEfficiencyFunction)(rotationalSpeedRPM, pressureRatio);
	m::limitVariable(isentropicEfficiency, 0, 1);

	if (pressureRatio > 1) { //:TRICKY: Pin > Pout
		double sIn = inletState->s();
		outletFlowStateIdeal->update_ps(outletState->p(), sIn);
		double enthalpyChangeIdeal = outletFlowStateIdeal->h() - inletState->h();
		enthalpyChangeReal = enthalpyChangeIdeal / isentropicEfficiency;
	}
	outletEnthalpyReal = inletState->h() + enthalpyChangeReal;

	compressorWork = massFlowRate * enthalpyChangeReal / mechanicalEfficiency;
	torque = compressorWork / rotationalSpeed;

}

void MechanicalCompressor::updateFluidFlows(FluidFlow* inletFlow, FluidFlow* outletFlow) {
	inletFlow->massFlowRate = -massFlowRate;
	inletFlow->enthalpyFlowRate = -massFlowRate * inletState->h();

	outletFlow->massFlowRate = massFlowRate;
	outletFlow->enthalpyFlowRate = massFlowRate * outletEnthalpyReal;
}

/**
 * MechanicalCompressor - C
 */
MechanicalCompressor* MechanicalCompressor_new() {
	return new MechanicalCompressor;
}

void MechanicalCompressor_init(MechanicalCompressor* compressor, MediumState* inletState, MediumState* outletState) {
	compressor->init(inletState, outletState);
}

void MechanicalCompressor_setDisplacementVolume(MechanicalCompressor* compressor, double displacementVolume) {
	compressor->setDisplacementVolume(displacementVolume);
}

void MechanicalCompressor_setRotationalSpeed(MechanicalCompressor* compressor, double rotationalSpeed) {
	compressor->setRotationalSpeed(rotationalSpeed);
}

void MechanicalCompressor_setVolumetricEfficiencyFunction(MechanicalCompressor* compressor,
		FunctorTwoVariables* volumetricEfficiencyFunction) {
	compressor->setVolumetricEfficiencyFunction(volumetricEfficiencyFunction);
}

void MechanicalCompressor_setVolumetricFlowRateFunction(MechanicalCompressor* compressor,
		FunctorTwoVariables* volumetricFlowRateFunction) {
	compressor->setVolumetricFlowRateFunction(volumetricFlowRateFunction);
}

void MechanicalCompressor_setIsentropicEfficiencyFunction(MechanicalCompressor* compressor,
		FunctorTwoVariables* isentropicEfficiencyFunction) {
	compressor->setIsentropicEfficiencyFunction(isentropicEfficiencyFunction);
}

void MechanicalCompressor_setMechanicalEfficiencyFunction(MechanicalCompressor* compressor,
		FunctorTwoVariables* mechanicalEfficiencyFunction) {
	compressor->setMechanicalEfficiencyFunction(mechanicalEfficiencyFunction);
}


void MechanicalCompressor_compute(MechanicalCompressor* compressor) {
	compressor->compute();
}

void MechanicalCompressor_updateFluidFlows(MechanicalCompressor* compressor, FluidFlow* inletFlow, FluidFlow* outletFlow) {
	compressor->updateFluidFlows(inletFlow, outletFlow);
}

double MechanicalCompressor_getPressureRatio(MechanicalCompressor* compressor) {
	return compressor->getPressureRatio();
}

double MechanicalCompressor_getIsentropicEfficiency(MechanicalCompressor* compressor){
	return compressor->getIsentropicEfficiency();
}

double MechanicalCompressor_getMechanicalEfficiency(MechanicalCompressor* compressor){
	return compressor->getMechanicalEfficiency();
}

double MechanicalCompressor_getVolumetricEfficiency(MechanicalCompressor* compressor){
	return compressor->getVolumetricEfficiency();
}

double MechanicalCompressor_getCompressorWork(MechanicalCompressor* compressor) {
	return compressor->getCompressorWork();
}

double MechanicalCompressor_getTorque(MechanicalCompressor* compressor) {
	return compressor->getTorque();
}
