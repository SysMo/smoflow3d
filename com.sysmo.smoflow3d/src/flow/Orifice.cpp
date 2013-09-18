/*
 * Orifice.cpp
 *
 *  Created on: Aug 3, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "Orifice.h"
using namespace smoflow;

/**
 * Orifice - C++
 */
Orifice::Orifice() {
	/* Parameters */
	orificeArea = 0.0;
	flowCoefficient = 0.0;

	/* Inputs */
	regulatingSignal = 0.0;

	/* Results */
	massFlowRate = 0.0;
	enthalpyFlowRate = 0.0;
	pressureDrop = 0.0;

	/* Intermediate variables */
	sonicFlow = 0;
}

Orifice::~Orifice() {
}

void Orifice::compute_CompressibleIdealGas() {
	// Compute pressure drop
	pressureDrop = MediumState_p(state1) - MediumState_p(state2);

	// Compute mass flow rate - Using AMESim 'pn2rcqfix' function documentation
	double pDn = MediumState_p(state2);
	double pUp = MediumState_p(state1);
	double tUp = MediumState_T(state1);
	double r = MediumState_R(state1);
	double g = MediumState_gamma(state1);

	if (pUp < pDn) {
		massFlowRate = 0.0;
		return;
	}

	double pCr = m::pow(2/(g+1) , g/(g-1)); // critical pressure

	double flowParam = 0.0; //flow parameter
	if (pDn/pUp > pCr) {//(subsonic)
		flowParam = m::sqrt(2*g/(r*(g-1)))
		* m::sqrt(m::pow(pDn/pUp, 2/g) - m::pow(pDn/pUp,(g+1)/g));
		sonicFlow = 0;
	} else { //pDn/pUp <= pCr (sonic)
		flowParam = m::sqrt(2*g/(r*(g+1)))
		* m::pow((2/(g+1)), 1/(g-1));
		sonicFlow = 1;
	}

	m::limitVariable(regulatingSignal, 0.0, 1.0);
	massFlowRate = regulatingSignal * orificeArea * flowCoefficient
			* flowParam * pUp / m::sqrt(tUp);

	// Compute enthalpy flow rate
	enthalpyFlowRate = massFlowRate * MediumState_h(state1);
}

void Orifice::getInletFlowRates(FluidFlow* inletFlow) {
	inletFlow->massFlowRate = -massFlowRate;
	inletFlow->enthalpyFlowRate = -enthalpyFlowRate;
}

void Orifice::getOutletFlowRates(FluidFlow* outletFlow) {
	outletFlow->massFlowRate = massFlowRate;
	outletFlow->enthalpyFlowRate = enthalpyFlowRate;
}

/**
 * Orifice - C
 */
Orifice* Orifice_new() {
	return new Orifice();
}

void Orifice_init(Orifice* orifice, MediumState* state1, MediumState* state2) {
	orifice->init(state1, state2);
}

void Orifice_compute_CompressibleIdealGas(Orifice* orifice) {
	orifice->compute_CompressibleIdealGas();
}

void Orifice_setOrificeArea(Orifice* orifice, double orificeArea) {
	orifice->setOrificeArea(orificeArea);
}

void Orifice_setFlowCoefficient(Orifice* orifice, double flowCoefficient) {
	orifice->setFlowCoefficient(flowCoefficient);
}

void Orifice_setRegulatingSignal(Orifice* orifice, double regulatingSignal) {
	orifice->setRegulatingSignal(regulatingSignal);
}

double Orifice_getMassFlowRate(Orifice* orifice) {
	return orifice->getMassFlowRate();
}

double Orifice_getEnthalpyFlowRate(Orifice* orifice) {
	return orifice->getEnthalpyFlowRate();
}

double Orifice_getPressureDrop(Orifice* orifice) {
	return orifice->getPressureDrop();
}

int Orifice_getSonicFlow(Orifice* orifice) {
	return orifice->getSonicFlow();
}

void Orifice_getInletFlowRates(Orifice* orifice, FluidFlow* inletFlow) {
	orifice->getInletFlowRates(inletFlow);
}

void Orifice_getOutletFlowRates(Orifice* orifice, FluidFlow* outletFlow) {
	orifice->getOutletFlowRates(outletFlow);
}
