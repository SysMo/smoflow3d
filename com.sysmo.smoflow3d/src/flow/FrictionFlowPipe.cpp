/*
 * FrictionFlowPipe.cpp
 *
 *  Created on: Aug 22, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "FrictionFlowPipe.h"

using namespace smoflow;

/**
 * FrictionFlowPipe - C++
 */
FrictionFlowPipe::FrictionFlowPipe(
		double hydraulicDiameter,
		double flowArea,
		double flowFactor) {
	this->hydraulicDiameter = hydraulicDiameter;
	this->flowArea = flowArea;
	this->flowFactor = flowFactor;

	pressureDropGain = 0.0;
	massFlowRate = 0.0;
	absPressureDrop = 0.0;
	state1 = NULL;
	state2 = NULL;

	Re_cache = 1e5;
}

FrictionFlowPipe::~FrictionFlowPipe() {
}

void FrictionFlowPipe::init(MediumState* state1, MediumState* state2) {
	this->state1 = state1;
	this->state2 = state2;
}

double FrictionFlowPipe::computePressureDrop(double massFlowRate) {
	this->massFlowRate = massFlowRate;

	MediumState* upstreamState;
	if (massFlowRate >= 0) {
		upstreamState = state1;
	} else {
		upstreamState = state2;
	}

	double vFlow = m::fabs(massFlowRate) / (upstreamState->rho() * flowArea);
	//@see VDI Heat Atlas, L1.2.1 (page 1057), Eq. (2)
	double Re = upstreamState->rho() * vFlow * hydraulicDiameter / upstreamState->mu();

	//@see VDI Heat Atlas, L1.2.1 (page 1057), Eq. (1)
	double pressureDrop = pressureDropGain * frictionFactor(Re)
		* flowFactor * upstreamState->rho() * vFlow * vFlow / 2;

	absPressureDrop = pressureDrop;
	if (massFlowRate < 0.0) {
		pressureDrop = -pressureDrop;
	}
	return pressureDrop;
}

double FrictionFlowPipe::computeMassFlowRate(double pressureDrop) {
	static const int maxNumIter = 100;
	static const double relTolerance = 1e-08;

	absPressureDrop = m::fabs(pressureDrop);
	if (absPressureDrop < cst::MinPressureDrop) {
		massFlowRate = 0.0;
		return 0.0;
	}

	MediumState* upstreamState;
	if (pressureDrop > 0) {
		upstreamState = state1;
	} else {
		upstreamState = state2;
	}

	double calcPressureDrop = this->absPressureDrop / this->pressureDropGain;

	// Calculate vFlow (i.e. mass flow rate) by pressure drop using iterations
	int numIter = 0;
	double relError = 1.0;
	double vFlow;

	double Re = Re_cache;
	while ((m::fabs(relError) > relTolerance) && (numIter < maxNumIter)) {
		// Compute the friction factor, and the flow velocity
		vFlow = m::sqrt(2 * calcPressureDrop / (upstreamState->rho() * frictionFactor(Re) * flowFactor));

		// New guess for the Reynolds number
		Re = upstreamState->rho() * vFlow * hydraulicDiameter / upstreamState->mu();

		// Compute the error
		double dpCalc = frictionFactor(Re) * flowFactor * upstreamState->rho() * vFlow * vFlow / 2;
		relError = (dpCalc - calcPressureDrop) / calcPressureDrop;
		numIter++;
	}
	Re_cache = upstreamState->rho() * vFlow * hydraulicDiameter / upstreamState->mu();
	//m::limitVariable(Re_cache, 10, 1e8); //:TRICKY:

	// Compute mass flow rate, accounting for the flow direction
	massFlowRate = upstreamState->rho() * vFlow * flowArea;
	if (pressureDrop < 0) {
		massFlowRate = -massFlowRate;
	}

	return massFlowRate;
}

void FrictionFlowPipe::updateFluidFlows(FluidFlow* flow1, FluidFlow* flow2) {
	MediumState* upstreamState = getUpstreamState(massFlowRate);

	flow1->massFlowRate = -massFlowRate;
	flow1->enthalpyFlowRate = -massFlowRate * upstreamState->h();

	flow2->massFlowRate = massFlowRate;
	flow2->enthalpyFlowRate = massFlowRate * upstreamState->h();
}

MediumState* FrictionFlowPipe::getUpstreamState(double massFlowRate) {
	MediumState* upstreamState;
	if (massFlowRate >= 0) {
		upstreamState = state1;
	} else {
		upstreamState = state2;
	}

	return upstreamState;
}

/*************************************************************
 ***   FrictionFlowPipe implementation classes
 *************************************************************/
/**
 * FrictionFlowPipe_StraightPipe - C++
 */
class FrictionFlowPipe_StraightPipe : public FrictionFlowPipe {
public:
	FrictionFlowPipe_StraightPipe(double diameter, double length, double surfaceRoughness)
		: FrictionFlowPipe(diameter, (m::pi / 4) * diameter * diameter, length / diameter) {
		this->surfaceRoughness = surfaceRoughness;
	}

protected:
	virtual double frictionFactor(double Re) {
		//return frictionFactor_EQ_JainAndSwamee_1976(Re);
		return frictionFactor_EQ_Churchill_1977(Re);
	}

	double frictionFactor_EQ_Churchill_1977(double Re) {
		// "Churchill'1977" equation for friction factor in the laminar, transition and turbulent flow
		// see: http://en.wikipedia.org/wiki/Darcy_friction_factor_formulae#Table_of_Approximations)
		// see: AMESim help for 'tpf_pipe_fr' function
		double theta1 = m::pow(2.457 * m::log(m::pow(7./Re, 0.9) + 0.27*surfaceRoughness/hydraulicDiameter), 16.);
		double theta2 = m::pow(37530./Re, 16.);
		double zeta = 8 * m::pow(m::pow(8./Re, 12) + 1 / m::pow(theta1 + theta2, 1.5), 1./12);
		return zeta;
	}

	double frictionFactor_EQ_JainAndSwamee_1976(double Re) {
		// "Jain and Swamee'1976" equation for friction factor in the turbulent flow (see http://en.wikipedia.org/wiki/Darcy_friction_factor_formulae#Table_of_Approximations)
		double zetaTurbulent = 1.325 / m::pow(m::log(surfaceRoughness / (3.7 * hydraulicDiameter) + 5.74 * m::pow(Re, -0.9)), 2);

		double zeta;
		if (Re < 2320) { //laminar flow
			//@see VDI Heat Atlas, L1.2.1 (page 1057), Eq. (4)
			double zetaLaminar = 64 / Re;
			zeta = m::max(zetaLaminar, zetaTurbulent);
		} else { //turbulent flow
			zeta = zetaTurbulent;
		}

		return zeta;
	}


protected:
	double surfaceRoughness;
};

/**
 * FrictionFlowPipe - C
 */
FrictionFlowPipe* FrictionFlowPipe_StraightPipe_new(double diameter, double length, double surfaceRoughness) {
	return new FrictionFlowPipe_StraightPipe(diameter, length, surfaceRoughness);
}

void FrictionFlowPipe_init(FrictionFlowPipe* component, MediumState* state1, MediumState* state2) {
	component->init(state1, state2);
}

void FrictionFlowPipe_setPressureDropGain(FrictionFlowPipe* component, double gain) {
	component->setPressureDropGain(gain);
}

double FrictionFlowPipe_computePressureDrop(FrictionFlowPipe* component, double massFlowRate) {
	return component->computePressureDrop(massFlowRate);
}

double FrictionFlowPipe_computeMassFlowRate(FrictionFlowPipe* component, double pressureDifference) {
	return component->computeMassFlowRate(pressureDifference);
}

double FrictionFlowPipe_getAbsolutePressureDrop(FrictionFlowPipe* component) {
	return component->getAbsolutePressureDrop();
}

double FrictionFlowPipe_getMassFlowRate(FrictionFlowPipe* component) {
	return component->getMassFlowRate();
}
