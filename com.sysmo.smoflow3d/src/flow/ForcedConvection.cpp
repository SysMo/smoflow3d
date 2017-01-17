/*
 * ForcedConvection.cpp
 *
 *  Created on: Aug 10, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "ForcedConvection.h"
using namespace smoflow;

/**
 * ForcedConvection - C++
 */

ForcedConvection::ForcedConvection() {
	flowArea = 0.0;

	fluidState2 = NULL;
	limitOutput = true;
	limitState = NULL;

	Re = 0.0;
}

void ForcedConvection::init(MediumState* fluidState1, MediumState* fluidState2, ThermalNode* wallNode) {
	Convection::init(fluidState1, wallNode);
	this->fluidState2 = fluidState2;

	limitState = MediumState_new(fluidState->getMedium());
	MediumState_register(limitState);
}

void ForcedConvection::setLimitOutput(bool limitOutput) {
	this->limitOutput = limitOutput;
}

void ForcedConvection::compute(double massFlowRate) {
	MediumState* upstreamFluidState;
	if (massFlowRate >= 0) {
		upstreamFluidState = fluidState;
	} else {
		upstreamFluidState = fluidState2;
	}
	double absMassFlowRate = m::fabs(massFlowRate);


	double fluidTemperature = upstreamFluidState->T();
	double wallTemperature = wallNode->getTemperature();

	double wallOverheat = wallTemperature - fluidTemperature;
	if (absMassFlowRate < cst::MinMassFlowRate) {
		Re = 0;
		Pr = 0;
		Nu = 3.66;
		convectionCoefficient = Nu * fluidState->lambda() / characteristicLength;
		heatFlowRate = heatExchangeGain * convectionCoefficient
				* heatExchangeArea * wallOverheat;
		return;
	}

	// Calculate film state
	MediumState* workState = upstreamFluidState;
	if (useFilmState) {
		double filmTemperature = (fluidTemperature + wallTemperature)/2;
		filmState->update_Tp(filmTemperature, upstreamFluidState->p());

		workState = filmState;
	}

	// Calculate
	double vFlow =  absMassFlowRate / workState->rho() / flowArea;
	Re = workState->rho() * vFlow * characteristicLength / workState->mu();
	Pr = workState->Pr();
	Nu = computeNusseltNumber(Re, Pr);
	convectionCoefficient = Nu * workState->lambda() / characteristicLength;

	heatFlowRate = heatExchangeGain * convectionCoefficient * heatExchangeArea * wallOverheat;

	if (limitOutput) {
		limitState->update_Tp(wallTemperature, upstreamFluidState->p());

		double limitHeatFlowRate = absMassFlowRate * (limitState->h() - upstreamFluidState->h());
		if (heatFlowRate > 0) {
			heatFlowRate = m::min(heatFlowRate, limitHeatFlowRate);
		} else {
			heatFlowRate = m::max(heatFlowRate, limitHeatFlowRate);
		}
	}
}

void ForcedConvection::compute_NoHeatFlow() {
	Re = 0;
	Pr = 0;
	Nu = 0.0;
	convectionCoefficient = 0.0;
	heatFlowRate = 0.0;
}

/*************************************************************
 ***  Forced convection models
 *************************************************************/
/**
 * ForcedConvection 'GivenConvectionCoefficient' model - C++
 */
class ForcedConvection_GivenConvectionCoefficient : public ForcedConvection {
public:
	ForcedConvection_GivenConvectionCoefficient(double heatExchangeArea) {
		this->heatExchangeArea = heatExchangeArea;
	}

	virtual void compute(double massFlowRate) {
		double fluidTemperature = fluidState->T();
		double wallTemperature = wallNode->getTemperature();
		double wallOverheat = wallTemperature - fluidTemperature;
		Re = 0.0;
		Pr = 0.0;
		Nu = 0.0;
		heatFlowRate = heatExchangeGain * convectionCoefficient
				* heatExchangeArea * wallOverheat;
	}

protected:
	double computeNusseltNumber(double Re, double Pr) {
		return 0;
	}
};

/**
 * ForcedConvection 'StraightPipe' model - C++
 */
class ForcedConvection_StraightPipe : public ForcedConvection {
public:
	ForcedConvection_StraightPipe(double length, double hydraulicDiameter, double flowArea) {
		this->characteristicLength = hydraulicDiameter;
		this->flowArea = flowArea;
		double perimeter = 4 * flowArea / hydraulicDiameter;
		this->heatExchangeArea = perimeter * length;
	}

	double computeNusseltNumber(double Re, double Pr) {
		static const double ReL = 2300; //@see VDI Heat Atlas, page 696, Sect. 4.2
		static const double ReH = 1e4;

		double Nu;
		if (Re < ReL) {
			Nu = NuLaminar(Re, Pr);
		} else if (Re > ReH) {
			Nu = NuTurbulent(Re, Pr);
		} else {
			// Interpolation coefficient
			double gamma = (Re - ReL) / (ReH - ReL);
			//gamma = -2*m::pow(gamma, 3.0) + 3*m::pow(gamma, 2.0); //:TRICKY: - this polynomial smooth the interpolation
			//:TRICKY: ReH = 4000 in SmoFlow
			Nu = (1 - gamma) * NuLaminar(ReL, Pr) + gamma * NuTurbulent(ReH, Pr);
		}
		return Nu;
	}

protected:
	inline double NuLaminar(double Re, double Pr) {
		return 3.66; //@see VDI Heat Atlas, page 693, Eq. (1)
	}

	inline double NuTurbulent(double Re, double Pr) {
		// Friction factor - @see VDI Heat Atlas, page 696, Eq. (26) and (27)
		// Range of validity: 1e4 < Re < 1e6, 0.1 < Pr < 1000

		// Limit the Prandtl number, to prevent crashing around the critical point
		//m::limitVariable(Pr, 0, 100);

		double xi = m::pow(1.8 * m::log10(Re) - 1.5, -2);
		double NuNum = (xi / 8) * Re * Pr;
		double NuDenom = 1 + 12.7 * m::sqrt(xi / 8) * (m::pow(Pr, 2./3) - 1);
		return NuNum/NuDenom;
	}
};


/**
 * ForcedConvection 'Straight Pipe with Nusselt Expression' model - C++
 */
class ForcedConvection_StraightPipe_NusseltExpression : public ForcedConvection {
public:
	ForcedConvection_StraightPipe_NusseltExpression(
			double length, double hydraulicDiameter, double flowArea,
			const char* nusseltExpressionLaminarFlow, const char* nusseltExpressionTurbulentFlow,
			double criticalReynoldsNumber_EndLaminarFlow, double criticalReynoldsNumber_StartTurbulentFlow) {
		this->characteristicLength = hydraulicDiameter;
		this->flowArea = flowArea;
		double perimeter = 4 * flowArea / hydraulicDiameter;
		this->heatExchangeArea = perimeter * length;

		this->nusseltExpressionLaminarFlow = FunctorTwoVariables_Expression_new(nusseltExpressionLaminarFlow, "Re", "Pr");
		this->nusseltExpressionTurbulentFlow = FunctorTwoVariables_Expression_new(nusseltExpressionTurbulentFlow, "Re", "Pr");
		this->ReL = criticalReynoldsNumber_EndLaminarFlow;
		this->ReH = criticalReynoldsNumber_StartTurbulentFlow;
	}

	double computeNusseltNumber(double Re, double Pr) {
		double ReL = this->ReL;
		double ReH = this->ReH;

		double Nu;
		if (Re < ReL) {
			Nu = NuLaminar(Re, Pr);
		} else if (Re > ReH) {
			Nu = NuTurbulent(Re, Pr);
		} else {
			// Interpolation coefficient
			double gamma = (Re - ReL) / (ReH - ReL);
			Nu = (1 - gamma) * NuLaminar(ReL, Pr) + gamma * NuTurbulent(ReH, Pr);
		}
		return Nu;
	}

protected:
	inline double NuLaminar(double Re, double Pr) {
		return  (*nusseltExpressionLaminarFlow)(Re, Pr);
	}

	inline double NuTurbulent(double Re, double Pr) {
		return  (*nusseltExpressionTurbulentFlow)(Re, Pr);
	}

protected:
	FunctorTwoVariables* nusseltExpressionLaminarFlow;
	FunctorTwoVariables* nusseltExpressionTurbulentFlow;
	double ReL;
	double ReH;
};


/**
 * ForcedConvection_XXX - C
 */
ForcedConvection* ForcedConvection_GivenConvectionCoefficient_new(double heatExchangeArea) {
	return new ForcedConvection_GivenConvectionCoefficient(heatExchangeArea);
}

ForcedConvection* ForcedConvection_StraightPipe_new(double length, double hydraulicDiameter, double flowArea) {
	return new ForcedConvection_StraightPipe(length, hydraulicDiameter, flowArea);
}

ForcedConvection* ForcedConvection_StraightPipe_NusseltExpression_new(
		double length, double hydraulicDiameter, double flowArea,
		const char* nusseltExpressionLaminarFlow, const char* nusseltExpressionTurbulentFlow,
		double criticalReynoldsNumber_EndLaminarFlow, double criticalReynoldsNumber_StartTurbulentFlow) {
	return new ForcedConvection_StraightPipe_NusseltExpression(length,
			hydraulicDiameter, flowArea,
			nusseltExpressionLaminarFlow, nusseltExpressionTurbulentFlow,
			criticalReynoldsNumber_EndLaminarFlow, criticalReynoldsNumber_StartTurbulentFlow);
}

/**
 * ForcedConvection - C
 */
void ForcedConvection_init(ForcedConvection* convection,
		MediumState* fluidState1, MediumState* fluidState2,
		ThermalNode* wallNode) {
	convection->init(fluidState1, fluidState2, wallNode);
}

void ForcedConvection_setLimitOutput(ForcedConvection* convection, int limitOutput) {
	convection->setLimitOutput(limitOutput);
}

void ForcedConvection_compute(ForcedConvection* convection, double massFlowRate) {
	convection->compute(massFlowRate);
}

double ForcedConvection_getReynoldsNumber(ForcedConvection* convection) {
	return convection->getReynoldsNumber();
}

