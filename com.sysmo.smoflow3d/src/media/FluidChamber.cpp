/*
 * FluidChamber.cpp
 *
 *  Created on: Jul 26, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "FluidChamber.h"

FluidChamber::FluidChamber(Medium *fluid) {
	fluidState = MediumState_new(fluid);
	MediumState_register(fluidState);
	volume = 0;
}

FluidChamber::~FluidChamber() {
	// TODO Auto-generated destructor stub
}

void FluidChamber::seletcStates(params state1, params state2) {
	this->states[0] = state1;
	this->states[1] = state2;
	if ((state1 == iD && state2 == iT) || (state1 == iT && state2 == iD)) {

	} else {
		RaiseError("Incorrect combination of states used: "
				<< state1 << " and " << state2);
	}
}

void FluidChamber::setStateValues(double stateValue1, double stateValue2) {
	stateValues[0] = stateValue1;
	stateValues[1] = stateValue2;
	if (states[0] == iD && states[1] == iT) {
		fluidState->update_Trho(stateValue2, stateValue1);
	} else if (states[0] == iT && states[1] == iD) {
		fluidState->update_Trho(stateValue1, stateValue2);
	} else if (states[0] == iP && states[1] == iT) {
		fluidState->update_Tp(stateValue2, stateValue1);
	} else if (states[0] == iT && states[1] == iP) {
		fluidState->update_Tp(stateValue1, stateValue2);
	} else {
		RaiseError("Cannot set state using state variables: "
				<< states[0] << " and " << states[1]);
	}
}
void FluidChamber::getStateValues(double* stateValue1, double* stateValue2) {
	*stateValue1 = stateValues[0];
	*stateValue2 = stateValues[1];
}
void FluidChamber::getStateDerivatives(double* stateDerivative1, double* stateDerivative2) {
	double stateDerivatives[2];
	for (int i = 0; i < numStateVariables; i++) {
		switch (states[i]) {
		case iP:
			stateDerivatives[i] = stateTimeDerivatives.p;
			break;
		case iT:
			stateDerivatives[i] = stateTimeDerivatives.T;
			break;
		case iD:
			stateDerivatives[i] = stateTimeDerivatives.rho;
			break;
		default:
			RaiseError("Calculation of time derivative of state (enum) " << states[i]
			   <<	"not implemented");
		}
	}

	*stateDerivative1 = stateDerivatives[0];
	*stateDerivative2 = stateDerivatives[1];
}

void FluidChamber::computeStateDerivatives(double mDot, double UDot, double VDot) {
	Real m = fluidState->rho() * volume;
	Real c1 = mDot/m - VDot/volume;
	stateTimeDerivatives.rho = fluidState->rho() * c1;
	//stateTimeDerivatives.specificVolume = - specificVolume * c1;

	double dvdt_p = fluidState->dvdt_p();
	double dvdp_T = 1./fluidState->dpdv_t();

	Real alpha_m = mDot /fluidState->rho();
	Real alpha_T = m * dvdt_p;
	Real alpha_p = m * dvdp_T;
	Real beta_m = mDot * fluidState->u();
	Real beta_T = m * (fluidState->cp() - fluidState->p() * dvdt_p);
	Real beta_p = - m * (fluidState->p() * dvdp_T + fluidState->T() * dvdt_p);

	stateTimeDerivatives.T = (beta_p * (VDot - alpha_m) - alpha_p * (UDot - beta_m)) /
			(alpha_T * beta_p - alpha_p * beta_T);
	stateTimeDerivatives.p = ( - beta_T * (VDot - alpha_m) + alpha_T * (UDot - beta_m)) /
			(alpha_T * beta_p - alpha_p * beta_T);

}
