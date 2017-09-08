/*
 * FrictionFlowValve.cpp
 *
 *  Created on: Aug 22, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "FrictionFlowValve.h"

using namespace smoflow;

/**
 * FrictionFlowValve - C++
 */
FrictionFlowValve::FrictionFlowValve(int allowBidirectionalFlow) {
	flowType = sFlowType_Undefine;
	this->allowBidirectionalFlow = allowBidirectionalFlow;
	regulatingSignal = 0.0;

	massFlowRate = 0.0;
	absPressureDrop = 0.0;

	state1 = NULL;
	state2 = NULL;
}

FrictionFlowValve::~FrictionFlowValve() {
}

void FrictionFlowValve::init(MediumState* state1, MediumState* state2) {
	this->state1 = state1;
	this->state2 = state2;
}

double FrictionFlowValve::computeMassFlowRate_NoFluidFlow(double pressureDrop) {
	absPressureDrop = m::fabs(pressureDrop);
	massFlowRate = cst::zeroMassFlowRate;
	return massFlowRate;
}

void FrictionFlowValve::updateFluidFlows(FluidFlow* flow1, FluidFlow* flow2) {
	MediumState* upstreamState = getUpstreamState(massFlowRate);

	flow1->massFlowRate = -massFlowRate;
	flow1->enthalpyFlowRate = -massFlowRate * upstreamState->h();

	flow2->massFlowRate = massFlowRate;
	flow2->enthalpyFlowRate = massFlowRate * upstreamState->h();
}

MediumState* FrictionFlowValve::getUpstreamState(double massFlowRate) {
	MediumState* upstreamState;
	if (massFlowRate >= 0) {
		upstreamState = state1;
	} else {
		upstreamState = state2;
	}

	return upstreamState;
}

MediumState* FrictionFlowValve::getUpstreamState(int flowDirection) {
	MediumState* upstreamState;
	if (flowDirection == 1) {
		upstreamState = state1;
	} else {
		upstreamState = state2;
	}

	return upstreamState;
}

MediumState* FrictionFlowValve::getDownstreamState(int flowDirection) {
	MediumState* downstreamState;
	if (flowDirection == 1) {
		downstreamState = state2;
	} else {
		downstreamState = state1;
	}

	return downstreamState;
}

/*************************************************************
 ***   FrictionFlowValve implementation classes
 *************************************************************/
/**
 * FrictionFlowValve_InputMassFlowRate - C++
 */
class FrictionFlowValve_InputMassFlowRate : public FrictionFlowValve {
public:
	FrictionFlowValve_InputMassFlowRate(int allowBidirectionalFlow) :
			FrictionFlowValve(allowBidirectionalFlow) {
	}

	virtual double computePressureDrop(double massFlowRate) {
		RaiseError_UnimplementedFunction();
		return 0.0;
	}

	virtual double computeMassFlowRate(double pressureDrop) {
		// Set absolute pressure drop
		absPressureDrop = m::fabs(pressureDrop);
		if (absPressureDrop < cst::MinPressureDrop) { //No flow
			massFlowRate = 0.0;
			return massFlowRate;
		}

		// Find the flow direction (1 - from state1 to state2;  0 - no flow;  -1 - from state2 to state2
		int flowDirection = 0;
		if (regulatingSignal <= 0) {
			flowDirection = 0;
		} else if (pressureDrop >= 0) {
			flowDirection = 1;
		} else if (pressureDrop < 0 && isBidirectionalFlowAllowed()) { //allowBidirectionalFlow == 1 - yes
			flowDirection = -1;
		} else {
			flowDirection = 0;
		}

		if (flowDirection == 0) { //No flow
			massFlowRate = 0.0;
			return massFlowRate;
		}

		// Compute mass flow rate
		massFlowRate = regulatingSignal * flowDirection;
		return massFlowRate;
	}
};

/**
 * FrictionFlowValve_Kv - C++
 */
class FrictionFlowValve_Kv : public FrictionFlowValve {
public:
	FrictionFlowValve_Kv(
			int allowBidirectionalFlow,
			double Kv,
			int transitionChoice,
			double transitionMassFlowRate,
			double transitionPressureDifference,
			double maximumMassFlowRate) :
			FrictionFlowValve(allowBidirectionalFlow) {
		this->Kv = Kv;
		this->transitionChoice = transitionChoice; //1 - Minimum mass flow;  2 - Minimum pressure difference
		this->transitionMassFlowRate = transitionMassFlowRate;
		this->transitionPressureDifference = transitionPressureDifference;
		this->maximumMassFlowRate = maximumMassFlowRate;
	}

	virtual double computePressureDrop(double massFlowRate) { //:TRICKY: Used in R components
		// Set mass flow rate
		this->massFlowRate = massFlowRate;
		if (massFlowRate < 0.0 && !isBidirectionalFlowAllowed()) {
			absPressureDrop = 0.0;
			return 0.0;
		}

		// Check regulating signal
		m::limitVariable(regulatingSignal, 0.0, 1.0);
		if (regulatingSignal <= 0) {
			absPressureDrop = 0.0;
			return 0.0;
		}

		// Get upstream state
		MediumState* upstreamState = getUpstreamState(massFlowRate);
		double upstreamDensity = upstreamState->rho();
		double relativeDensity = upstreamDensity / referenceLiquidDensity;

		// Calculate transition mass flow rate if necessary
		if (transitionChoice == 1) { //1 - Minimum mass flow
			//:TRICKY: transitionMassFlowRate is set from the user
			transitionPressureDifference =
					m::pow((transitionMassFlowRate / upstreamDensity)
					/ (N1 * Kv), 2.0) * relativeDensity;
		} else { //2 - Minimum pressure difference
			//:TRICKY: transitionPressureDifference is set from the user
			transitionMassFlowRate =
					m::sqrt((transitionPressureDifference/relativeDensity))
					* upstreamDensity * N1 * Kv;
		}

		// Calculate pressure drop
		double vFlow = m::fabs(massFlowRate) / upstreamDensity;
		//:TRICKY: use 'pressureDrop < transitionPressureDifference'. Using 'absMassFlowRate < transitionMassFlowRate' is wrong
		double pressureDrop = relativeDensity * m::pow(vFlow / (regulatingSignal * N1 * Kv), 2);
		if (pressureDrop < transitionPressureDifference) {
			pressureDrop =
					transitionPressureDifference * vFlow
					/ (regulatingSignal * N1 * Kv * m::pow(transitionPressureDifference / relativeDensity, 0.5));
		}

		absPressureDrop = pressureDrop;
		if (massFlowRate < 0.0) {
			pressureDrop = -pressureDrop;
		}
		return pressureDrop;
	}

	virtual double computeMassFlowRate(double pressureDrop) {
		// Set absolute pressure drop
		absPressureDrop = m::fabs(pressureDrop);
		if (absPressureDrop < cst::MinPressureDrop) { //No flow
			massFlowRate = 0.0;
			return massFlowRate;
		}

		// Compute mass flow rate
		m::limitVariable(regulatingSignal, 0.0, 1.0);

		int flowDirection = 0;
		if (regulatingSignal <= 0) {
			flowDirection = 0;
		} else if (pressureDrop > 0) {
			flowDirection = 1;
		} else if (pressureDrop < 0 && isBidirectionalFlowAllowed()) {
			flowDirection = -1;
		} else {
			flowDirection = 0;
		}

		if (flowDirection == 0) {//No flow
			massFlowRate = 0.0;
			return massFlowRate;
		}

		MediumState* upstreamState = getUpstreamState(flowDirection);
		double upstreamDensity = upstreamState->rho();
		double relativeDensity = upstreamDensity / referenceLiquidDensity;

		// Calculate transition pressure if necessary
		if (transitionChoice == 1) { //1 - Minimum mass flow
			transitionPressureDifference =
					m::pow((transitionMassFlowRate / upstreamDensity)
					/ (N1 * Kv), 2.0) * relativeDensity;
		} else { //2 - Minimum pressure difference
		}

		double vFlow; //volumetric flow rate magnitude
		if (absPressureDrop < transitionPressureDifference) {
			vFlow = regulatingSignal * N1 * Kv
					* m::pow(transitionPressureDifference / relativeDensity, 0.5)
					* (absPressureDrop / transitionPressureDifference);
		} else {
			vFlow = regulatingSignal * N1 * Kv
					* m::pow(absPressureDrop / relativeDensity, 0.5);
		}

		massFlowRate = vFlow * flowDirection * upstreamDensity;
		if (m::fabs(massFlowRate) > maximumMassFlowRate) {
			massFlowRate = maximumMassFlowRate * flowDirection;
		}

		return massFlowRate;
	}

private:
	int transitionChoice;
	double transitionMassFlowRate;
	double transitionPressureDifference;
	double Kv;
	double maximumMassFlowRate;

	static const double N1 = 8.784e-07; //2.403e-5; //:SMO_SETTINGS:
	static const double referenceLiquidDensity = 1000; //:SMO_SETTINGS:
};

/**
 * FrictionFlowValve_OrificeCompressibleIdealGas - C++
 */
class FrictionFlowValve_OrificeCompressibleIdealGas : public FrictionFlowValve {
public:
	FrictionFlowValve_OrificeCompressibleIdealGas(
			int allowBidirectionalFlow,
			double orificeArea,
			double flowCoefficient) :
			FrictionFlowValve(allowBidirectionalFlow) {
		this->orificeArea = orificeArea;
		this->flowCoefficient = flowCoefficient;
	}

	virtual double computePressureDrop(double massFlowRate) {
		RaiseError_UnimplementedFunction();
		return 0.0;
	}

	virtual double computeMassFlowRate(double pressureDrop) {
		// Set absolute pressure drop
		absPressureDrop = m::fabs(pressureDrop);
		if (absPressureDrop < cst::MinPressureDrop) { //No flow
			massFlowRate = 0.0;
			return massFlowRate;
		}

		// Compute mass flow rate
		m::limitVariable(regulatingSignal, 0.0, 1.0);

		int flowDirection = 0;
		if (regulatingSignal <= 0) {
			flowDirection = 0;
		} else if (pressureDrop > 0) {
			flowDirection = 1;
		} else if (pressureDrop < 0 && isBidirectionalFlowAllowed()) {
			flowDirection = -1;
		} else {
			flowDirection = 0;
		}

		if (flowDirection == 0) {//No flow
			massFlowRate = 0.0;
			return massFlowRate;
		}

		MediumState* upstreamState = getUpstreamState(flowDirection);
		MediumState* downstreamState = getDownstreamState(flowDirection);


		// Compute mass flow rate - Using AMESim 'pn2rcqfix' function documentation
		double pDn = downstreamState->p();
		double pUp = upstreamState->p();
		double tUp = upstreamState->T();
		double r = upstreamState->R();
		double g = upstreamState->gamma();

		double pCr = m::pow(2/(g+1) , g/(g-1)); // critical pressure

		double Cm = 0.0; //flow parameter
		if (pDn/pUp > pCr) {//(subsonic)
			Cm = m::sqrt(2*g/(r*(g-1)))
				* m::sqrt(m::pow(pDn/pUp, 2/g) - m::pow(pDn/pUp,(g+1)/g));
			flowType = sFlowType_Subsonic;
		} else { //pDn/pUp <= pCr (sonic)
			Cm = m::sqrt(2*g/(r*(g+1)))
				* m::pow((2/(g+1)), 1/(g-1));
			flowType = sFlowType_Sonic;
		}

		massFlowRate = flowDirection
				* regulatingSignal * orificeArea * flowCoefficient
				* Cm * pUp / m::sqrt(tUp);

		return massFlowRate;
	}

protected:
	double orificeArea;
	double flowCoefficient;
};

/**
 * FrictionFlowValve_OrificeCompressibleRealGas - C++
 */
class FrictionFlowValve_OrificeCompressibleRealGas : public FrictionFlowValve {
public:
	FrictionFlowValve_OrificeCompressibleRealGas(
			int allowBidirectionalFlow,
			double orificeArea,
			double flowCoefficient) :
			FrictionFlowValve(allowBidirectionalFlow) {
		this->orificeArea = orificeArea;
		this->flowCoefficient = flowCoefficient;
	}

	virtual double computePressureDrop(double massFlowRate) {
		RaiseError_UnimplementedFunction();
		return 0.0;
	}

	virtual double computeMassFlowRate(double pressureDrop) {
		// Set absolute pressure drop
		absPressureDrop = m::fabs(pressureDrop);
		if (absPressureDrop < cst::MinPressureDrop) { //No flow
			massFlowRate = 0.0;
			return massFlowRate;
		}

		// Compute mass flow rate
		m::limitVariable(regulatingSignal, 0.0, 1.0);

		int flowDirection = 0;
		if (regulatingSignal <= 0) {
			flowDirection = 0;
		} else if (pressureDrop > 0) {
			flowDirection = 1;
		} else if (pressureDrop < 0 && isBidirectionalFlowAllowed()) {
			flowDirection = -1;
		} else {
			flowDirection = 0;
		}

		if (flowDirection == 0) {//No flow
			massFlowRate = 0.0;
			return massFlowRate;
		}

		MediumState* upstreamState = getUpstreamState(flowDirection);
		MediumState* downstreamState = getDownstreamState(flowDirection);


		// Compute mass flow rate - Using AMESim 'pn2rcqfix' function documentation
		double pDn = downstreamState->p();
		double pUp = upstreamState->p();
		double tUp = upstreamState->T();
		double rhoUp = upstreamState->rho();
		//double r = upstreamState->R();
		double cUp = upstreamState->speed_sound();
		double drhodp_s_Up = 1/(cUp*cUp);
		double gs = (pUp/rhoUp) * drhodp_s_Up;

		double pCr = m::pow(2*gs/(gs+1), 1/(1-gs)); // critical pressure

		double Cm = 0.0; //flow parameter
		if (pDn/pUp > pCr) {//(subsonic)
			Cm = m::sqrt( (2/(1-gs))*(rhoUp*tUp/pUp) )
				* m::sqrt( m::pow(pDn/pUp, 2*gs) - m::pow(pDn/pUp, 1+gs) );
			flowType = sFlowType_Subsonic;
		} else { //pDn/pUp <= pCr (sonic)
			Cm = m::sqrt( (2/(1+gs))*(rhoUp*tUp/pUp) )
				* m::pow(2*gs/(gs+1), gs/(1-gs));
			flowType = sFlowType_Sonic;
		}

		massFlowRate = flowDirection
				* regulatingSignal * orificeArea * flowCoefficient
				* Cm * pUp / m::sqrt(tUp);

		return massFlowRate;
	}

protected:
	double orificeArea;
	double flowCoefficient;
};

/**
 * FrictionFlowValve - C
 */
FrictionFlowValve* FrictionFlowValve_InputMassFlowRate_new(int allowBidirectionalFlow) {
	return new FrictionFlowValve_InputMassFlowRate(allowBidirectionalFlow);
}

FrictionFlowValve* FrictionFlowValve_Kv_new(
		int allowBidirectionalFlow,
		double Kv,
		int transitionChoice,
		double transitionMassFlowRate,
		double transitionPressureDifference,
		double maximumMassFlowRate) {
	return new FrictionFlowValve_Kv(
			allowBidirectionalFlow,
			Kv,
			transitionChoice,
			transitionMassFlowRate,
			transitionPressureDifference,
			maximumMassFlowRate);
}

FrictionFlowValve* FrictionFlowValve_OrificeCompressibleIdealGas_new(
		int allowBidirectionalFlow,
		double orificeArea,
		double flowCoefficient) {
	return new FrictionFlowValve_OrificeCompressibleIdealGas(
			allowBidirectionalFlow,
			orificeArea,
			flowCoefficient);
}

FrictionFlowValve* FrictionFlowValve_OrificeCompressibleRealGas_new(
		int allowBidirectionalFlow,
		double orificeArea,
		double flowCoefficient) {
	return new FrictionFlowValve_OrificeCompressibleRealGas(
			allowBidirectionalFlow,
			orificeArea,
			flowCoefficient);
}

