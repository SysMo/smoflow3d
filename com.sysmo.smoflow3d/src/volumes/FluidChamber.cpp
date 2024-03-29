/*
 * FluidChamber.cpp
 *
 *  Created on: Jul 26, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "FluidChamber.h"

/**
 * FluidChamber - C++
 */
FluidChamber::FluidChamber(Medium *fluid) {
	fluidState = MediumState_new(fluid);
	MediumState_register(fluidState);
	setVolume(0.0);
	totalVolume = 0.0;
	flagInTwoPhase = false;
}

FluidChamber::~FluidChamber() {
}

void FluidChamber::selectStates(ThermodynamicVariable state1, ThermodynamicVariable state2) {
	this->states[0] = state1;
	this->states[1] = state2;
	// :SMO_TODO: (Nasko) if P & T are state variables it has to be ensured that the 2-phase region is not entered
	if (
			((state1 == iD && state2 == iT) || (state1 == iT && state2 == iD)) ||
			((state1 == iP && state2 == iT) || (state1 == iT && state2 == iP)) ||
			((state1 == iP && state2 == iD) || (state1 == iD && state2 == iP)) ||
			((state1 == iP && state2 == iH) || (state1 == iH && state2 == iP))
		) {
	} else {
		RaiseComponentError(this,
				"Incorrect combination of states selected (enum): "
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
	} else if (states[0] == iP && states[1] == iD) {
		fluidState->update_prho(stateValue1, stateValue2);
	} else if (states[0] == iD && states[1] == iP) {
		fluidState->update_prho(stateValue2, stateValue1);
	} else if (states[0] == iP && states[1] == iH) {
		fluidState->update_ph(stateValue1, stateValue2);
	} else if (states[0] == iH && states[1] == iP) {
		fluidState->update_ph(stateValue2, stateValue1);
	} else {
		RaiseComponentError(this,
				"Cannot set state using state variables (enum): "
				<< states[0] << " and " << states[1]);
	}
}

void FluidChamber::getStateValues(double* stateValue1, double* stateValue2, bool getFromFluid) {
	if (getFromFluid) {
		for (int i = 0; i < numStateVariables; i++) {
			switch (states[i]) {
			case iP:
				stateValues[i] = fluidState->p();
				break;
			case iT:
				stateValues[i] = fluidState->T();
				break;
			case iD:
				stateValues[i] = fluidState->rho();
				break;
			case iH:
				stateValues[i] = fluidState->h();
				break;
			default:
				RaiseComponentError(this, "Incorrect state variable (enum) " << states[i]);
			}
		}
	}
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
		case iH:
			stateDerivatives[i] = stateTimeDerivatives.h;
			break;
		default:
			RaiseComponentError(this,
					"Calculation of time derivative of state (enum) "
					<< states[i] << "not implemented");
		}
	}

	*stateDerivative1 = stateDerivatives[0];
	*stateDerivative2 = stateDerivatives[1];
}

void FluidChamber::compute(
		double massFlowRate,
		double enthalpyFlowRate,
		double heatFlowRate,
		double volume,
		double volumeDot) {
	double deadVolume = getVolume();
	totalVolume = deadVolume + volume;
	if (totalVolume < 0.01*deadVolume) {
		//The total volume of the chamber is limited to 1% of its dead volume
		totalVolume = 0.01*deadVolume;
	}

	double c1 = massFlowRate/getTotalFluidMass() - volumeDot/totalVolume;
	double UDot = enthalpyFlowRate + heatFlowRate - fluidState->p() * volumeDot;
	stateTimeDerivatives.rho = fluidState->rho() * c1;
	computeStateDerivatives_cv(massFlowRate, UDot, volumeDot);

	handleEvent_FluidPhaseTransition();
}

void FluidChamber::computeStateDerivatives_cv(double mDot, double UDot, double VDot) {
	double vDot = - stateTimeDerivatives.rho / (fluidState->rho() * fluidState->rho());
	double uDot = (UDot - mDot * fluidState->u())/getTotalFluidMass();
	double k2 = (fluidState->T() * fluidState->dpdt_v() - fluidState->p()) * vDot;
	stateTimeDerivatives.T = (uDot - k2) / fluidState->cv();
	stateTimeDerivatives.p = fluidState->dpdt_v() * stateTimeDerivatives.T + fluidState->dpdrho_t() * stateTimeDerivatives.rho;
	stateTimeDerivatives.h = uDot + fluidState->p() * vDot + stateTimeDerivatives.p / fluidState->rho();
}

void FluidChamber::computeStateDerivatives_cp(double mDot, double UDot, double VDot) {
	//:NOTE: This function is not used, because it is not suitable for the two phase region and
	//also it doesn't work for state variables = (p,h)
	double totalFluidMass = getTotalFluidMass();

	double dvdt_p = fluidState->dvdt_p();
	double dvdp_T = 1./fluidState->dpdv_t();

	double alpha_m = mDot /fluidState->rho();
	double alpha_T = totalFluidMass * dvdt_p;
	double alpha_p = totalFluidMass * dvdp_T;
	double beta_m = mDot * fluidState->u();
	double beta_T = totalFluidMass * (fluidState->cp() - fluidState->p() * dvdt_p);
	double beta_p = - totalFluidMass * (fluidState->p() * dvdp_T + fluidState->T() * dvdt_p);

	stateTimeDerivatives.T = (beta_p * (VDot - alpha_m) - alpha_p * (UDot - beta_m)) /
			(alpha_T * beta_p - alpha_p * beta_T);
	stateTimeDerivatives.p = ( - beta_T * (VDot - alpha_m) + alpha_T * (UDot - beta_m)) /
			(alpha_T * beta_p - alpha_p * beta_T);

}

void FluidChamber::handleEvent_FluidPhaseTransition() {
	if (SimEnv.isEventMode()) { //in a discontinuity
		flagInTwoPhase = fluidState->isTwoPhase();
	}

	bool eventIndicator = false;
	if (fluidState->isTwoPhase() != flagInTwoPhase) {
		eventIndicator = true;
	}

	if (eventIndicator) {
		//trigger a discontinuity when the fluid in the chamber changes its phase (from single to two phase and vice versa)
		SimEnv.updateEventIndicator(eventIndicator);
	}
}

/**
 * FluidChamber - C
 */
FluidChamber* FluidChamber_new(Medium *fluid) {
	return new FluidChamber(fluid);
}

void FluidChamber_selectStates(FluidChamber* chamber, ThermodynamicVariable state1, ThermodynamicVariable state2) {
	chamber->selectStates(state1, state2);
}

void FluidChamber_setVolume(FluidChamber* chamber, double volume) {
	chamber->setVolume(volume);
}

double FluidChamber_getFluidMass(FluidChamber* chamber) {
	return chamber->getFluidMass();
}

void FluidChamber_setStateValues(FluidChamber* chamber, double stateValue1, double stateValue2) {
	chamber->setStateValues(stateValue1, stateValue2);
}

void FluidChamber_getStateValues(FluidChamber* chamber, double* stateValue1, double* stateValue2, int getFromFluid) {
	chamber->getStateValues(stateValue1, stateValue2, getFromFluid);
}

void FluidChamber_compute(FluidChamber* chamber, double massFlowRate, double enthalpyFlowRate, double heatFlowRate, double volume, double volumeDot) {
	chamber->compute(massFlowRate, enthalpyFlowRate, heatFlowRate, volume, volumeDot);
}

void FluidChamber_getStateDerivatives(FluidChamber* chamber, double* stateDerivative1, double* stateDerivative2) {
	chamber->getStateDerivatives(stateDerivative1, stateDerivative2);
}

MediumState* FluidChamber_getFluidState(FluidChamber* chamber) {
	return chamber->getFluidState();
}

double FluidChamber_getVolume(FluidChamber* chamber) {
	return chamber->getVolume();
}

double FluidChamber_getTotalVolume(FluidChamber* chamber) {
	return chamber->getTotalVolume();
}

double FluidChamber_getTotalFluidMass(FluidChamber* chamber) {
	return chamber->getTotalFluidMass();
}
