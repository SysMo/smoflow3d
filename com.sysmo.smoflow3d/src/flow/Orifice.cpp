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
	pressureLoss = 0.0;
	flowType = sFlowType_Undefine;
}

Orifice::~Orifice() {
}

void Orifice::compute_CompressibleIdealGas() {
	massFlowRate = 0.0;
	enthalpyFlowRate = 0.0;

	// Compute pressure drop
	pressureLoss = m::fabs(MediumState_p(state1) - MediumState_p(state2));

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
		flowType = sFlowType_Subsonic;
	} else { //pDn/pUp <= pCr (sonic)
		flowParam = m::sqrt(2*g/(r*(g+1)))
		* m::pow((2/(g+1)), 1/(g-1));
		flowType = sFlowType_Sonic;
	}

	m::limitVariable(regulatingSignal, 0.0, 1.0);
	massFlowRate = regulatingSignal * orificeArea * flowCoefficient
			* flowParam * pUp / m::sqrt(tUp);

	// Compute enthalpy flow rate
	enthalpyFlowRate = massFlowRate * MediumState_h(state1);
}

void Orifice::getFlowRates(FluidFlow* flow1, FluidFlow* flow2) {
	flow1->massFlowRate = -massFlowRate;
	flow1->enthalpyFlowRate = -enthalpyFlowRate;

	flow2->massFlowRate = massFlowRate;
	flow2->enthalpyFlowRate = enthalpyFlowRate;
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

double Orifice_getPressureLoss(Orifice* orifice) {
	return orifice->getPressureLoss();
}

int Orifice_getFlowType(Orifice* orifice) {
	return orifice->getFlowType();
}

void Orifice_getFlowRates(Orifice* orifice, FluidFlow* flow1, FluidFlow* flow2) {
	orifice->getFlowRates(flow1, flow2);
}

