/*
 * Orifice.cpp
 *
 *  Created on: Aug 3, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "Orifice.h"


using namespace smoflow;


BEGIN_C_LINKAGE
Orifice* Orifice_new() {
	return new Orifice();
}

void Orifice_init(Orifice* orifice, MediumState* stateUp, MediumState* stateDown) {
	orifice->stateUp = stateUp;
	orifice->stateDown = stateDown;
}

void Orifice_computeMassFlow_CompressibleIdealGas(Orifice* orifice, double regulatingSignal) {
	// Using AMESim 'pn2rcqfix' function documentation
	double pDn = MediumState_p(orifice->stateDown);
	double pUp = MediumState_p(orifice->stateUp);
	double tUp = MediumState_T(orifice->stateUp);
	double r = MediumState_R(orifice->stateUp);
	double g = MediumState_gamma(orifice->stateUp);

	if (pUp < pDn) {
		orifice->massFlowRate = 0.0;
		return;
	}

	double pCr = m::pow(2/(g+1) , g/(g-1)); // critical pressure

	double flowParam = 0.0; //flow parameter
	if (pDn/pUp > pCr) {//(subsonic)
		flowParam = m::sqrt(2*g/(r*(g-1)))
			* m::sqrt(m::pow(pDn/pUp, 2/g) - m::pow(pDn/pUp,(g+1)/g));
	} else { //pDn/pUp <= pCr (sonic)
		flowParam = m::sqrt(2*g/(r*(g+1)))
			* m::pow((2/(g+1)), 1/(g-1));
	}

	m::limitVariable(regulatingSignal, 0.0, 1.0);
	orifice->massFlowRate = regulatingSignal * orifice->orificeArea * orifice->flowCoefficient
		* flowParam * pUp / m::sqrt(tUp);
}

void Orifice_computeEnthalpyFlow(Orifice* orifice) {
	orifice->enthalpyFlowRate = orifice->massFlowRate * MediumState_h(orifice->stateUp);
}

END_C_LINKAGE
