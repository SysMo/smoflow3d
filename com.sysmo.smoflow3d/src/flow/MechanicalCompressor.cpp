/*
 * MechanicalCompressor.cpp
 *
 *  Created on: Jul 31, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "MechanicalCompressor.h"

MechanicalCompressor::MechanicalCompressor() {
	outletFlowStateIdeal = NULL;
	isentropicEfficiencyFunction = NULL;
	mechanicalEfficiencyFunction = NULL;
	volumetricEfficiencyFunction = NULL;
	volumetricFlowRateFunction = NULL;
}

MechanicalCompressor::~MechanicalCompressor() {
	// TODO Auto-generated destructor stub
}

void MechanicalCompressor::init(MediumState* state1, MediumState* state2) {
	// Check parameters
	if (isentropicEfficiencyFunction == NULL)
		RaiseError("Function for evaluating isentropic efficiency not set");
	if (mechanicalEfficiencyFunction == NULL)
		RaiseError("Function for evaluating mechanical efficiency not set");
	if (volumetricFlowRateFunction == NULL && volumetricEfficiencyFunction == NULL)
		RaiseError("Neither 'volumetric flow rate' nor 'volumetric efficiency' functions set");

	FlowRComponent::init(state1, state2);
	outletFlowStateIdeal = MediumState_new(state1->getMedium());
	MediumState_register(outletFlowStateIdeal);
}

void MechanicalCompressor::compute() {
	pressureRatio = state2->p() / state1->p();

	mechanicalEfficiency = (*mechanicalEfficiencyFunction)(rotationalSpeed, pressureRatio);
	isentropicEfficiency = (*isentropicEfficiencyFunction)(rotationalSpeed, pressureRatio);

	double volumetricFlowRate = 0;
	if (volumetricFlowRateFunction != NULL) {
		volumetricFlowRate = (*volumetricFlowRateFunction)(rotationalSpeed, pressureRatio);
	} else {
		volumetricEfficiency = (*volumetricEfficiencyFunction)(rotationalSpeed, pressureRatio);
		volumetricFlowRate = volumetricEfficiency * rotationalSpeed * displacementVolume;
	}
	massFlowRate = volumetricFlowRate * state1->rho();

	double sIn = state1->s();
	outletFlowStateIdeal->update_ps(state2->p(), sIn);
	double enthalpyChangeIdeal = outletFlowStateIdeal->h() - state1->h();
	double enthalpyChangeReal = enthalpyChangeIdeal / isentropicEfficiency;
	outletEnthalpyReal = state1->h() + enthalpyChangeReal;

	compressorWork = massFlowRate * enthalpyChangeReal / mechanicalEfficiency;
	torque = compressorWork / (2 * 3.14 * rotationalSpeed);

}

void MechanicalCompressor::getInletFlowRates(FluidFlow* inletFlow) {
	inletFlow->massFlowRate = -massFlowRate;
	inletFlow->enthalpyFlowRate = -massFlowRate * state1->h();
}

void MechanicalCompressor::getOutletFlowRates(FluidFlow* outletFlow) {
	outletFlow->massFlowRate = massFlowRate;
	outletFlow->enthalpyFlowRate = massFlowRate * outletEnthalpyReal;
}

MechanicalCompressor* MechanicalCompressor_new() {
	return new MechanicalCompressor;
}

void MechanicalCompressor_init(MechanicalCompressor* compressor, MediumState* state1, MediumState* state2) {
	compressor->init(state1, state2);
}

void MechanicalCompressor_setDisplacementVolume(MechanicalCompressor* compressor, double displacementVolume) {
	compressor->setDisplacementVolume(displacementVolume);
}

void MechanicalCompressor_setRotationalSpeed(MechanicalCompressor* compressor, double rotationalSpeed) {
	compressor->setRotationalSpeed(rotationalSpeed);
}

void MechanicalCompressor_setIsentropicEfficiencyFunction(MechanicalCompressor* compressor,
		FunctorTwoVariables* isentropicEfficiencyFunction) {
	compressor->setIsentropicEfficiencyFunction(isentropicEfficiencyFunction);
}

void MechanicalCompressor_setMechanicalEfficiencyFunction(MechanicalCompressor* compressor,
		FunctorTwoVariables* mechanicalEfficiencyFunction) {
	compressor->setMechanicalEfficiencyFunction(mechanicalEfficiencyFunction);
}

void MechanicalCompressor_setVolumetricEfficiencyFunction(MechanicalCompressor* compressor,
		FunctorTwoVariables* volumetricEfficiencyFunction) {
	compressor->setVolumetricEfficiencyFunction(volumetricEfficiencyFunction);
}

void MechanicalCompressor_compute(MechanicalCompressor* compressor) {
	compressor->compute();
}

void MechanicalCompressor_getInletFlowRates(MechanicalCompressor* compressor, FluidFlow* inletFlow) {
	compressor->getInletFlowRates(inletFlow);
}

void MechanicalCompressor_getOutletFlowRates(MechanicalCompressor* compressor, FluidFlow* outletFlow) {
	compressor->getOutletFlowRates(outletFlow);
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
