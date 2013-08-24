/*
 * FrictionFlowPipe.cpp
 *
 *  Created on: Aug 22, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "FrictionFlowPipe.h"

using namespace smoflow;

FrictionFlowPipe::FrictionFlowPipe(double hydraulicDiameter,
		double flowArea, double flowFactor) {
	this->hydraulicDiameter = hydraulicDiameter;
	this->flowArea = flowArea;
	this->flowFactor = flowFactor;
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
	if (massFlowRate > 0) {
		upstreamState = state1;
	} else {
		upstreamState = state2;
	}
	//@see VDI Heat Atlas, L1.2.1 (page 1057), Eq. (2)
	double vFlow = m::fabs(massFlowRate)
		/ (upstreamState->rho() * flowArea);
	double Re = upstreamState->rho() * vFlow
		* hydraulicDiameter / upstreamState->mu();
	//@see VDI Heat Atlas, L1.2.1 (page 1057), Eq. (1)
	double pressureDrop = pressureDropGain * frictionFactor(Re)
		* flowFactor * upstreamState->rho() * vFlow * vFlow / 2;
	this->absolutePressureDrop = pressureDrop;
	if (massFlowRate < 0) {
		pressureDrop = -pressureDrop;
	}
	return pressureDrop;
}

double FrictionFlowPipe::computeMassFlowRate(double pressureDifference) {
	static const int maxNumIter = 20;
	static const double relTolerance = 1e-10;
	static const double minPressureDifference = 1e-12;

	// TODO check if caching the Reynolds number can help speed up convergence
	this->absolutePressureDrop = m::fabs(pressureDifference);

	if (this->absolutePressureDrop < minPressureDifference) {
		return 0;
	}

	MediumState* upstreamState;
	if (pressureDifference > 0) {
		upstreamState = state1;
	} else {
		upstreamState = state2;
	}

	double calcPressureDifference = this->absolutePressureDrop / this->pressureDropGain;
	double relError = 1;
	int numIter = 0;
	double vFlow;

	// Initial guess for the Reynolds number
	double Re = 1e6;

	while (m::fabs(relError) > relTolerance && numIter < maxNumIter) {
		// Compute the friction factor, and the flow velocity
		double zeta = frictionFactor(Re);
		vFlow = m::sqrt(2 * calcPressureDifference / (upstreamState->rho() * zeta * flowFactor));
		// Compute the error
		double dpCalc = frictionFactor(Re) * flowFactor
				* upstreamState->rho() * vFlow * vFlow / 2;
		relError = (dpCalc - calcPressureDifference) / calcPressureDifference;
		numIter++;
		// New guess for the Reynolds number
		Re = upstreamState->rho() * vFlow * hydraulicDiameter / upstreamState->mu();
	}
	// compute mass flow rate, accounting for the flow direction
	double mDot = upstreamState->rho() * vFlow * flowArea;
	if (pressureDifference < 0) {
		mDot *= -mDot;
	}
	this->massFlowRate = mDot;
	return mDot;
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

/**********************************************************************
 *********************  Implementation classes ************************
 **********************************************************************/

class FrictionFlowPipe_StraightPipe : public FrictionFlowPipe {
public:
	FrictionFlowPipe_StraightPipe(double diameter, double length, double surfaceRoughness)
	: FrictionFlowPipe(diameter, m::pi / 4 * diameter * diameter,
			length / diameter) {
		this->surfaceRoughness = surfaceRoughness;
	}

	virtual double frictionFactor(double Re) {
		// TODO The transition from laminar to turbulent is not handled properly
		// TRICKY @ the transition the friction factor falls and then rises again
		double zeta = 1.325 / m::pow(m::log(surfaceRoughness / (3.7 * hydraulicDiameter) + 5.74 * m::pow(Re, -0.9)), 2);
		double zetaLaminar;
		if (Re < 2320) {
			zetaLaminar = 64 / Re;
			zeta = m::max(zeta, zetaLaminar);
		}
		return zeta;
	}
protected:
	double surfaceRoughness;
};

FrictionFlowPipe* FrictionFlowPipe_StraightPipe_new(
		double diameter, double length, double surfaceRoughness) {
	return new FrictionFlowPipe_StraightPipe(diameter, length, surfaceRoughness);
}
