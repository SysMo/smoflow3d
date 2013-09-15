/*
 * NaturalConvection.cpp
 *
 *  Created on: Aug 10, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "FreeConvection.h"
#include "math/Functors.h"

using namespace smoflow;

/**
 * FreeConvection - C++
 */
FreeConvection::FreeConvection() {
	Gr = 0;
	Pr = 0;
	Ra = 0;
	Nu = 0;
	convectionCoefficient = 0;
}

FreeConvection::~FreeConvection() {
}

void FreeConvection::init(MediumState* fluidState, ThermalNode* wallNode) {
	Convection::init(fluidState, wallNode);
}

void FreeConvection::compute() {
	double fluidTemperature = fluidState->T();
	double wallTemperature = wallNode->getTemperature();
	double wallOverheat = wallTemperature - fluidTemperature;

	const double g = 9.81; // m/s**2
	// Calculate film state
	double filmTemperature = (fluidTemperature + wallTemperature)/2;
	filmState->update_Tp(filmTemperature, fluidState->p());
	// Calculate Rayleigh & Prandtl number
	double eta = filmState->mu() / filmState->rho();
	Gr = filmState->beta() * g * m::pow(characteristicLength, 3) * m::fabs(wallOverheat) / (eta * eta );
	Pr = filmState->Pr();
	Ra = Gr * Pr;
	Nu = computeNusseltNumber(Ra, Pr, wallOverheat);
	convectionCoefficient = Nu * filmState->lambda() / characteristicLength;
	heatFlowRate = heatExchangeGain * convectionCoefficient * heatExchangeArea * wallOverheat;
}

/**
 * FreeConvection - C
 */
void FreeConvection_init(FreeConvection* convection, MediumState* fluidState,
		ThermalNode* wallNode) {
	convection->init(fluidState, wallNode);
}

void FreeConvection_compute(FreeConvection* convection) {
	convection->compute();
}

double FreeConvection_getGrashofNumber(FreeConvection* convection) {
	return convection->getGrashofNumber();
}

double FreeConvection_getRayleighNumber(FreeConvection* convection) {
	return convection->getRayleighNumber();
}

/*************************************************************
 ***  Free convection models
 *************************************************************/
class FreeConvection_GivenConvectionCoefficient : public FreeConvection {
public:
	FreeConvection_GivenConvectionCoefficient(
			double convectionCoefficient, double heatExchangeArea) {
		this->convectionCoefficient = convectionCoefficient;
		this->heatExchangeArea = heatExchangeArea;
	}

	virtual void compute() {
		double fluidTemperature = fluidState->T();
		double wallTemperature = wallNode->getTemperature();
		double wallOverheat = wallTemperature - fluidTemperature;
		heatFlowRate = heatExchangeGain * convectionCoefficient * heatExchangeArea * wallOverheat;
	}

	virtual double computeNusseltNumber(double Re, double Pr, double wallOverheat) {
		return 0;
	}
};

class FreeConvection_NusseltExpression : public FreeConvection {
public:
	FreeConvection_NusseltExpression(double characteristicLength,
			double heatExchangeArea, const char* nusseltExpression) {
		this->characteristicLength = characteristicLength;
		this->heatExchangeArea = heatExchangeArea;
		this->nusseltExpression = FunctorTwoVariables_Expression_new(nusseltExpression, "Ra", "Pr");
	}

	virtual double computeNusseltNumber(double Ra, double Pr, double wallOverheat) {
		return (*nusseltExpression)(Ra, Pr);
	}

protected:
	FunctorTwoVariables* nusseltExpression;
};

class FreeConvection_VerticalSurface : public FreeConvection {
public:
	FreeConvection_VerticalSurface(double height, double width) {
		this->heatExchangeArea = height * width;
		this->characteristicLength = height;
	}

	virtual double computeNusseltNumber(double Ra, double Pr, double wallOverheat) {
		// Correlation from VDI Heat Atlas F2.1
		// Valid for 0.001 < Pr < inf
		double f1 = m::pow(1 + m::pow(0.492 / Pr, 9./16), -16./9);
		// Valid for 0.1 < Ra < 1e12
		double Nu0 = 0.825 + 0.387 * m::pow(Ra * f1, 1./6);
		double Nu = Nu0 * Nu0;
		return Nu;
	}
};

class FreeConvection_InclinedSurface : public FreeConvection {
public:
	FreeConvection_InclinedSurface(double length, double width, double angleOfInclination) {
		// Positive angle means HE surface on top
		this->length = length;
		this->width = width;
		this->angleOfInclination = angleOfInclination;
		this->RaCritical = m::pow(10, 8.9 - 0.00178 * m::pow(m::fabs(angleOfInclination), 1.82));
		this->heatExchangeArea = length * width;
		this->characteristicLength = length;
	}

	virtual double computeNusseltNumber(double Ra, double Pr, double wallOverheat) {
		double Nu = 0;
		// Correlation from VDI Heat Atlas F2.3
		if (
				((this->angleOfInclination > 0 && wallOverheat > 0) || (this->angleOfInclination < 0 && wallOverheat < 0))
				&& (Ra > RaCritical) ) {
			// Flow separation occurs
			Nu = 0.56 * m::pow(RaCritical * m::cos(this->angleOfInclination), 0.25)
			+ 0.13 * (m::pow(Ra, 1./3) - m::pow(RaCritical, 1./3));
		} else {
			// No flow separation, use the modified form of vertical wall correlation
			double f1 = m::pow(1 + m::pow(0.492 / Pr, 9./16), -16./9);
			double Nu0 = 0.825 + 0.387 * m::pow(Ra * m::cos(this->angleOfInclination) * f1, 1./6);
			Nu = Nu0 * Nu0;
		}
		return Nu;
	}

protected:
	double length;
	double width;
	double angleOfInclination;
	double RaCritical;
};

class FreeConvection_HorizontalSurface : public FreeConvection {
public:
	FreeConvection_HorizontalSurface(double length, double width, bool topSide) {
		this->heatExchangeArea = length * width;
		this->characteristicLength = length * width / 2 / (length + width);
		this->topSide = topSide;
	}

	virtual double computeNusseltNumber(double Ra, double Pr, double wallOverheat) {
		// Correlation from VDI Heat Atlas F2.3
		// Valid for 0.001 < Pr < inf
		double f2 = m::pow(1 + m::pow(0.322 / Pr, 11./20), -20./11);
		double Nu = 0;
		if ((topSide && (wallOverheat > 0) ) || (!topSide && (wallOverheat < 0))) {
			if (Ra * f2 < 7e4) {
				// Laminar flow
				Nu = 0.766 * m::pow(Ra * f2, 1./5);
			} else {
				// Turbulent flow
				Nu = 0.15 * m::pow(Ra * f2, 1./3);
			}
		} else {
			// Always laminar flow
			double f1 = m::pow(1 + m::pow(0.492 / Pr, 9./16), -16./9);
			Nu = 0.6 * m::pow(Ra * f1, 1./5);
		}
		return Nu;
	}

protected:
	bool topSide;
};

class FreeConvection_CylindricalHorizontalSurface : public FreeConvection {
public:
	FreeConvection_CylindricalHorizontalSurface(double length, double diameter) {
		this->heatExchangeArea = length * m::pi * diameter;
		this->characteristicLength = diameter;
	}

	virtual double computeNusseltNumber(double Ra, double Pr, double wallOverheat) {
		// Correlation from VDI Heat Atlas F2.4.1
		// Valid for 0 < Pr < inf
		double f3 = m::pow(1 + m::pow(0.559 / Pr, 9./16), -16./9);
		// Valid for 0.1 < Ra < 1e12
		double Nu0 = 0.6 + 0.387 * m::pow(Ra * f3, 1./6);
		double Nu = Nu0 * Nu0;
		return Nu;
	}
};

class FreeConvection_CylindricalVerticalSurface : public FreeConvection {
public:
	FreeConvection_CylindricalVerticalSurface(double height, double diameter) {
		this->height = height;
		this->diameter = diameter;
		this->heatExchangeArea = height * m::pi * diameter;
		this->characteristicLength = height;
	}

	virtual double computeNusseltNumber(double Ra, double Pr, double wallOverheat) {
		// Correlation from VDI Heat Atlas F2.1
		// Valid for 0.001 < Pr < inf
		double f1 = m::pow(1 + m::pow(0.492 / Pr, 9./16), -16./9);
		// Valid for 0.1 < Ra < 1e12
		double Nu0 = 0.825 + 0.387 * m::pow(Ra * f1, 1./6);
		double Nu = Nu0 * Nu0 + 0.97 * height / diameter;
		return Nu;
	}

protected:
	double height;
	double diameter;
};

class FreeConvection_SphericalSurface : public FreeConvection {
public:
	FreeConvection_SphericalSurface(double diameter) {
		this->diameter = diameter;
		this->heatExchangeArea = m::pi * diameter * diameter;
		this->characteristicLength = diameter;
	}

	virtual double computeNusseltNumber(double Ra, double Pr, double wallOverheat) {
		// Correlation from VDI Heat Atlas F2.4.2
		Nu = 0.56 * m::pow(Pr / (0.846 + Pr) * Ra, 0.25) + 2;
		return Nu;
	}

protected:
	double diameter;
};

class FreeConvection_FinnedPipe : public FreeConvection {
public:
	FreeConvection_FinnedPipe(double pipeDiameter, double pipeLength,
			double finSpacing, double finThickness, double finHeight) {
		this->pipeDiameter = pipeDiameter;
		this->pipeLength = pipeLength;
		this->finSpacing = finSpacing;
		this->finThickness = finThickness;
		this->finHeight = finHeight;
		double finsPerLength = 1./(finThickness + finSpacing);
		this->heatExchangeArea = m::pi * pipeDiameter * (1 - finThickness * finsPerLength);
		this->heatExchangeArea += finsPerLength * m::pi * finHeight * 2 * (pipeDiameter + finHeight);
		this->heatExchangeArea += finsPerLength * m::pi * finThickness * (pipeDiameter + 2 * finHeight);
		this->heatExchangeArea *= pipeLength;
		// halfway between full rib and bare pipe
		this->characteristicLength = pipeDiameter + finHeight;
	}

	virtual double computeNusseltNumber(double Ra, double Pr, double wallOverheat) {
		// Correlation from VDI Heat Atlas F2.4.4
		Nu = 0.24 * m::pow(Ra * finSpacing / pipeDiameter, 1./3);
		return Nu;
	}

protected:
	double pipeDiameter;
	double pipeLength;
	double finSpacing;
	double finThickness;
	double finHeight;
};


/**
 *  FreeConvection - C
 */
FreeConvection* FreeConvection_GivenConvectionCoefficient_new(
		double convectionCoefficient, double heatExchangeArea) {
	return new FreeConvection_GivenConvectionCoefficient(
			convectionCoefficient, heatExchangeArea);
}

FreeConvection* FreeConvection_NusseltExpression_new(
		double characteristicLength, double heatExchangeArea, const char* nusseltExpression) {
	return new FreeConvection_NusseltExpression(
			characteristicLength, heatExchangeArea, nusseltExpression);
}

FreeConvection* FreeConvection_VerticalSurface_new(
		double height, double width) {
	return new FreeConvection_VerticalSurface(height, width);
}

FreeConvection* FreeConvection_InclinedSurface_new(
		double length, double width, double angleOfInclination) {
	return new FreeConvection_InclinedSurface(length, width, angleOfInclination);
}

FreeConvection* FreeConvection_HorizontalSurfaceTop_new(
		double length, double width) {
	return new FreeConvection_HorizontalSurface(
			length, width, true);
}

FreeConvection* FreeConvection_HorizontalSurfaceBottom_new(
		double length, double width) {
	return new FreeConvection_HorizontalSurface(
			length, width, false);
}

FreeConvection* FreeConvection_CylindricalHorizontalSurface_new(
		double length, double diameter) {
	return new FreeConvection_CylindricalHorizontalSurface(
			length, diameter);
}

FreeConvection* FreeConvection_CylindricalVerticalSurface_new(double height, double diameter) {
	return new FreeConvection_CylindricalVerticalSurface(height, diameter);
}

FreeConvection* FreeConvection_SphericalSurface_new(double diameter) {
	return new FreeConvection_SphericalSurface(diameter);
}

FreeConvection* FreeConvection_FinnedPipe_new(double pipeDiameter, double pipeLength,
			double finSpacing, double finThickness, double finHeight) {
	return new FreeConvection_FinnedPipe(pipeDiameter, pipeLength,
			finSpacing, finThickness, finHeight);
}
