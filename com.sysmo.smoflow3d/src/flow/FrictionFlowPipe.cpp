/*
 * FrictionFlowPipe.cpp
 *
 *  Created on: Aug 22, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "FrictionFlowPipe.h"
#include "math/Interpolators.h"

using namespace smoflow;

/**
 * FrictionFlowPipe - C++
 */
FrictionFlowPipe::FrictionFlowPipe(double flowArea) {
	this->flowArea = flowArea;

	pressureDropGain = 0.0;

	massFlowRate = 0.0;
	absPressureDrop = 0.0;

	state1 = NULL;
	state2 = NULL;

	reynoldsNumber = 0.0;
	dragCoefficient = 0.0;
}

FrictionFlowPipe::~FrictionFlowPipe() {
}

void FrictionFlowPipe::init(MediumState* state1, MediumState* state2) {
	this->state1 = state1;
	this->state2 = state2;
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

/**
 * FrictionFlowPipe_Base - C++
 */
class FrictionFlowPipe_Base : public FrictionFlowPipe {
public:
	FrictionFlowPipe_Base(double hydraulicDiameter, double flowArea) :
		FrictionFlowPipe(flowArea) {
		this->hydraulicDiameter = hydraulicDiameter;
		this->Re_cache = 1e5;

		this->useDragCoeffGain = false;
		this->dragCoeffGainExpression = NULL;
	}

	virtual void setUseDragCoeffGain(bool useDragCoeffGain) {
		this->useDragCoeffGain = useDragCoeffGain;
	}

	virtual void setDragCoeffGainExpression(const char* dragCoeffGainExpression) {
		this->dragCoeffGainExpression = FunctorTwoVariables_Expression_new(dragCoeffGainExpression, "Re", "rho_up");
	}

	virtual double computePressureDrop(double massFlowRate) {//:TRICKY: Used in R components
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
		double dragCoeff = calcDragCoefficient(Re);

		double dragCoeffGain = 1;
		if (useDragCoeffGain) {
			dragCoeffGain = calcDragCoeffGainExpression(Re, upstreamState->rho()); //e.g. 1.15 - (rho/50.)/2 -- FL pipes in G05-Model
		}
		double pressureDrop = pressureDropGain * dragCoeffGain * dragCoeff
				* upstreamState->rho() * vFlow * vFlow / 2;

		absPressureDrop = pressureDrop;
		if (massFlowRate < 0.0) {
			pressureDrop = -pressureDrop;
		}

		reynoldsNumber = Re;
		dragCoefficient = dragCoeff;
		return pressureDrop;
	}

	virtual double computeMassFlowRate(double pressureDrop) {
		static const int maxNumIter = 100; //:SMO_SETTINGS:
		static const double relTolerance = 1e-08; //:SMO_SETTINGS:

		absPressureDrop = m::fabs(pressureDrop);
		if (absPressureDrop < cst::MinPressureDrop) {
			massFlowRate = 0.0;
			reynoldsNumber = 0.0;
			dragCoefficient = 0.0;
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
			// Compute the friction factor, and the upstream flow velocity
			vFlow = m::sqrt(2 * calcPressureDrop / (upstreamState->rho() * calcDragCoefficient(Re)));

			// New guess for the Reynolds number
			Re = upstreamState->rho() * vFlow * hydraulicDiameter / upstreamState->mu();

			// Compute the error
			double dpCalc = calcDragCoefficient(Re) * upstreamState->rho() * vFlow * vFlow / 2;
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

		reynoldsNumber = Re_cache;
		dragCoefficient = calcDragCoefficient(reynoldsNumber);
		return massFlowRate;
	}

protected:
	virtual double calcDragCoefficient(double Re) = 0;

	inline double calcDragCoeffGainExpression(double Re, double rho_up) {
		return  (*dragCoeffGainExpression)(Re, rho_up);
	}

protected:
	double hydraulicDiameter;

	bool useDragCoeffGain;
	FunctorTwoVariables* dragCoeffGainExpression;

private:
	double Re_cache;
};



/*************************************************************
 ***   FrictionFlowPipe implementation classes
 *************************************************************/
/**
 * FrictionFlowPipe_ConstantDragCoefficientPipe - C++
 */
class FrictionFlowPipe_ConstantDragCoefficientPipe : public FrictionFlowPipe {
public:
	FrictionFlowPipe_ConstantDragCoefficientPipe(double flowArea, double dragCoefficient)
		: FrictionFlowPipe(flowArea) {
		this->constDragCoefficient = dragCoefficient;
	}

	virtual double computePressureDrop(double massFlowRate) {
		this->massFlowRate = massFlowRate;

		MediumState* upstreamState;
		if (massFlowRate >= 0) {
			upstreamState = state1;
		} else {
			upstreamState = state2;
		}

		//@see VDI Heat Atlas, L1.2.1 (page 1057), Eq. (1)
		double vFlow = m::fabs(massFlowRate) / (upstreamState->rho() * flowArea);
		double pressureDrop = pressureDropGain * constDragCoefficient
				* upstreamState->rho() * vFlow * vFlow / 2;

		absPressureDrop = pressureDrop;
		if (massFlowRate < 0.0) {
			pressureDrop = -pressureDrop;
		}

		reynoldsNumber = 0.0;
		dragCoefficient = constDragCoefficient;
		return pressureDrop;
	}

	virtual double computeMassFlowRate(double pressureDrop) {
		absPressureDrop = m::fabs(pressureDrop);
		if (absPressureDrop < cst::MinPressureDrop) {
			massFlowRate = 0.0;
			reynoldsNumber = 0.0;
			dragCoefficient = 0.0;
			return 0.0;
		}

		MediumState* upstreamState;
		if (pressureDrop > 0) {
			upstreamState = state1;
		} else {
			upstreamState = state2;
		}

		//@see VDI Heat Atlas, L1.2.1 (page 1057), Eq. (1)
		massFlowRate = flowArea * m::sqrt(2 * upstreamState->rho() * absPressureDrop / (constDragCoefficient * pressureDropGain));
		if (pressureDrop < 0) {
			massFlowRate = -massFlowRate;
		}

		reynoldsNumber = 0.0;
		dragCoefficient = constDragCoefficient;
		return massFlowRate;
	}


protected:
	double constDragCoefficient;
};


/**
 * FrictionFlowPipe_StraightPipe - C++
 */
class FrictionFlowPipe_StraightPipe : public FrictionFlowPipe_Base {
public:
	FrictionFlowPipe_StraightPipe(double length, double hydraulicDiameter, double flowArea, double surfaceRoughness)
		: FrictionFlowPipe_Base(hydraulicDiameter, flowArea) {
		this->length = length;
		this->flowFactor = length/hydraulicDiameter;
		this->surfaceRoughness = surfaceRoughness;
	}

protected:
	virtual double calcDragCoefficient(double Re) {
		//double frictionFactor = frictionFactor_EQ_JainAndSwamee_1976(Re);
		double frictionFactor = calcFrictionFactor_EQ_Churchill_1977(Re);
		return frictionFactor * flowFactor;
	}

private:
	double calcFrictionFactor_EQ_Churchill_1977(double Re) {
		// "Churchill'1977" equation for friction factor in the laminar, transition and turbulent flow
		// see: http://en.wikipedia.org/wiki/Darcy_friction_factor_formulae#Table_of_Approximations)
		// see: AMESim help for 'tpf_pipe_fr' function
		double theta1 = m::pow(2.457 * m::log(m::pow(7./Re, 0.9) + 0.27*surfaceRoughness/hydraulicDiameter), 16.);
		double theta2 = m::pow(37530./Re, 16.);
		double zeta = 8 * m::pow(m::pow(8./Re, 12) + 1 / m::pow(theta1 + theta2, 1.5), 1./12);
		return zeta;
	}

	double calcFrictionFactor_EQ_JainAndSwamee_1976(double Re) {
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
	double length;
	double surfaceRoughness;
	double flowFactor;
};

/**
 * FrictionFlowPipe_ConstantDragCoefficientStraigntPipe - C++
 */
class FrictionFlowPipe_ConstantDragCoefficientStraightPipe : public FrictionFlowPipe_StraightPipe {
public:
	FrictionFlowPipe_ConstantDragCoefficientStraightPipe(double lenght, double hydraulicDiameter, double flowArea, double surfaceRoughness, double dragCoefficient) :
		FrictionFlowPipe_StraightPipe(lenght, hydraulicDiameter, flowArea, surfaceRoughness) {
		this->constDragCoefficient = dragCoefficient;
	}

protected:
	virtual double calcDragCoefficient(double Re) {
		double regularDragCoeff = FrictionFlowPipe_StraightPipe::calcDragCoefficient(Re);
		return regularDragCoeff + constDragCoefficient;
	}

protected:
	double constDragCoefficient;
};

/**
 * FrictionFlowPipe_ElbowPipe - C++
 */
class FrictionFlowPipe_ElbowPipe : public FrictionFlowPipe_StraightPipe {
public:
	FrictionFlowPipe_ElbowPipe(double hydraulicDiameter, double flowArea, double surfaceRoughness, double curvatureRadius, double bendAngle) :
		FrictionFlowPipe_StraightPipe((curvatureRadius * bendAngle * m::pi) / 180., hydraulicDiameter, flowArea, surfaceRoughness) {
		this->curvatureRadius = curvatureRadius;
		this->bendAngle = bendAngle;

		this->A1 = calc_A1(bendAngle);
		this->B1 = calc_B1(hydraulicDiameter, curvatureRadius);
		this->kDelta = calc_kDelta(surfaceRoughness, hydraulicDiameter);
	}

protected:
	virtual double calcDragCoefficient(double Re) {
		double regularDragCoeff = FrictionFlowPipe_StraightPipe::calcDragCoefficient(Re);
		double localDragCoeff = calcLocalDragCoefficient_EQ_Idelchik_1966(Re);
		return regularDragCoeff + localDragCoeff;
	}

private:
	double calcLocalDragCoefficient_EQ_Idelchik_1966(double Re) {
		//Idelchik, I. E., Handbook of Hydraulic Resistance (Israel Program for Scientific Translations Ltd., 1966).
		double kRe = calc_kRe_Formula(Re);
		return A1 * B1 * kDelta * kRe;
	}

	double calc_A1(double bendAngle) {
		static FunctorOneVariable* A1Function = NULL;
		if (A1Function == NULL) {
			ArrayXd inputValues(11);
			inputValues << 0, 20, 30, 45, 60, 75, 90, 110, 130, 150, 180; //bendAngle [degree]
			ArrayXd outputValues(11);
			outputValues << 0, 0.31, 0.45, 0.60, 0.78, 0.90, 1.00, 1.13, 1.20, 1.28, 1.40;

			A1Function = new Interpolator1D(&inputValues, &outputValues);
		}

		FunctorCache* cache = A1Function->createCache();
		return (*A1Function)(bendAngle, cache);
	}

	double calc_B1(double hydraulicDiameter, double curvatureRadius) {
		static FunctorOneVariable* B1Function = NULL;
		if (B1Function == NULL) {
			ArrayXd inputValues(17);
			inputValues << 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.25, 1.50, 2.0, 4.0, 6.0, 8.0, 10.0, 20.0, 30.0, 40.0, 1000.0;
			ArrayXd outputValues(17);
			outputValues << 1.18, 0.77, 0.51, 0.37, 0.28, 0.21, 0.19, 0.17, 0.15, 0.11, 0.09, 0.07, 0.07, 0.05, 0.04, 0.03, 0.03;

			B1Function = new Interpolator1D(&inputValues, &outputValues);
		}

		FunctorCache* cache = B1Function->createCache();
		return (*B1Function)(curvatureRadius / hydraulicDiameter, cache);
	}

	double calc_kRe_Table(double Re) {
		static FunctorOneVariable* kReFunction = NULL;
		if (kReFunction == NULL) {
			ArrayXd inputValues(12);
			inputValues << 0.1, 0.14, 0.2, 0.3, 0.4, 0.6, 0.8, 1.0, 1.4, 2.0, 3.0, 4.0;
			ArrayXd outputValues(12);
			outputValues << 2.00, 1.89, 1.77, 1.64, 1.56, 1.46, 1.38, 1.30, 1.15, 1.02, 1.00, 1.00;

			kReFunction = new Interpolator1D(&inputValues, &outputValues);
			kRe_cache = kReFunction->createCache();
		}

		return (*kReFunction)(Re * 1e-5, kRe_cache);
	}

	double calc_kRe_Formula(double Re) {
		double kRe = 1.3 - 0.29 * m::log(Re * 1.e-5);
		return m::max(1.0, kRe);
	}

	double calc_kDelta(double surfaceRoughness, double hydraulicDiameter) {
		double relRougness = surfaceRoughness / hydraulicDiameter;
		if (relRougness >= 1e-3) {
			return 2;
		} else if (0 <= relRougness && relRougness < 1e3) {
			return 1 + 1e3 * relRougness;
		} else {
			Assert(relRougness < 0);
			return 0.0;
		}
	}

protected:
	double curvatureRadius;
	double bendAngle; //[degree]

	double A1;
	double B1;
	double kDelta;
	FunctorCache* kRe_cache;
};

/**
 * FrictionFlowPipe - C
 */
FrictionFlowPipe* FrictionFlowPipe_StraightPipe_new(double length, double hydraulicDiameter, double flowArea, double surfaceRoughness) {
	return new FrictionFlowPipe_StraightPipe(length, hydraulicDiameter, flowArea, surfaceRoughness);
}

FrictionFlowPipe* FrictionFlowPipe_ElbowPipe_new(double hydraulicDiameter, double flowArea, double surfaceRoughness, double curvatureRadius, double bendAngle) {
	return new FrictionFlowPipe_ElbowPipe(hydraulicDiameter, flowArea, surfaceRoughness, curvatureRadius, bendAngle);
}

FrictionFlowPipe* FrictionFlowPipe_ConstantDragCoefficientPipe_new(double flowArea, double dragCoefficient) {
	return new FrictionFlowPipe_ConstantDragCoefficientPipe(flowArea, dragCoefficient);
}

FrictionFlowPipe* FrictionFlowPipe_ConstantDragCoefficientStraightPipe_new(double length, double hydraulicDiameter, double flowArea, double surfaceRoughness, double dragCoefficient) {
	return new FrictionFlowPipe_ConstantDragCoefficientStraightPipe(length, hydraulicDiameter, flowArea, surfaceRoughness, dragCoefficient);
}

void FrictionFlowPipe_setPressureDropGain(FrictionFlowPipe* component, double gain) {
	component->setPressureDropGain(gain);
}


double FrictionFlowPipe_getAbsolutePressureDrop(FrictionFlowPipe* component) {
	return component->getAbsolutePressureDrop();
}

double FrictionFlowPipe_getMassFlowRate(FrictionFlowPipe* component) {
	return component->getMassFlowRate();
}
