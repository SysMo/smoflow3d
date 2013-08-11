/*
 * NaturalConvection.cpp
 *
 *  Created on: Aug 10, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "FreeConvection.h"

using namespace smoflow;

FreeConvection::FreeConvection(FreeConvectionModel* convectionModel) {
	this->convectionModel = convectionModel;
	convectionCoefficient = 0;
}

FreeConvection::~FreeConvection() {
}

void FreeConvection::init(MediumState* fluidState, ThermalNode* wallNode,
		FreeConvectionModel* convectionModel) {
	Convection::init(fluidState, wallNode);
	characteristicLength = convectionModel->getCharacteristicLength();
	characteristicLength3 = characteristicLength * characteristicLength * characteristicLength;
	heatExchangeArea = convectionModel->getHeatExchangeArea();
}

void FreeConvection::setConvectionCoefficient(double convectionCoefficient) {
	if (convectionModel != 0) {
		RaiseError("Convection coefficient for free convection can be only set if there is no convection model")
	}
	this->convectionCoefficient = convectionCoefficient;
}

void FreeConvection::compute() {
	double fluidTemperature = fluidState->T();
	double wallTemperature = wallNode->getTemperature();
	double wallOverheat = wallTemperature - fluidTemperature;
	if (convectionModel != 0) {
		const double g = 9.81; // m/s**2
		// Calculate film state
		double filmTemperature = (fluidTemperature + wallTemperature)/2;
		filmState->update_Tp(filmTemperature, fluidState->p());
		// Calculate Rayleigh & Prandtl number
		double eta = filmState->mu() / filmState->rho();
		Gr = filmState->beta() * g * characteristicLength3 * m::fabs(wallOverheat) / (eta * eta );
		Pr = filmState->Pr();
		Ra = Gr * Pr;
		Nu = convectionModel->computeNusseltNumber(Ra, Pr, wallOverheat);
		convectionCoefficient = Nu * filmState->lambda() / characteristicLength;
		heatFlowRate = convectionCoefficient * heatExchangeArea * wallOverheat;
	} else {
		heatFlowRate = convectionCoefficient * heatExchangeArea * wallOverheat;
	}
}

FreeConvection* FreeConvection_new(FreeConvectionModel* convectionModel) {
	return new FreeConvection(convectionModel);
}
void FreeConvection_setConvectionCoefficient(FreeConvection* convection,
		double convectionCoefficient) {
	convection->setConvectionCoefficient(convectionCoefficient);
}
void FreeConvection_init(FreeConvection* convection, MediumState* fluidState,
		ThermalNode* wallNode, FreeConvectionModel* convectionModel) {
	convection->init(fluidState, wallNode, convectionModel);
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

double FreeConvection_getPrandtlNumber(FreeConvection* convection) {
	return convection->getPrandtlNumber();
}

double FreeConvection_getNusseltNumber(FreeConvection* convection) {
	return convection->getNusseltNumber();
}

double FreeConvection_getConvectionCoefficient(FreeConvection* convection) {
	return convection->getConvectionCoefficient();
}

double FreeConvection_getHeatFlowRate(FreeConvection* convection) {
	return convection->getHeatFlowRate();
}
void FreeConvection_getFlow_Wall(FreeConvection* convection, HeatFlow* flow) {
	convection->getFlow_Wall(flow);
}

void FreeConvection_getFlow_Fluid(FreeConvection* convection, FluidFlow* flow) {
	convection->getFlow_Fluid(flow);
}

/*************************************************************
 ***  Free convection models
 *************************************************************/
#include "math/Functors.h"

class FreeConvectionModel_NusseltExpression : public FreeConvectionModel {
public:
	FreeConvectionModel_NusseltExpression(double characteristicLength,
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

class FreeConvection_VerticalSurface : public FreeConvectionModel {
public:
	FreeConvection_VerticalSurface(double height, double width, double wallOverheat) {
		this->heatExchangeArea = height * width;
		this->characteristicLength = height;
	}
	virtual double computeNusseltNumber(double Ra, double Pr, double wallOverheat) {
		// Valid for 0.001 < Pr < inf
		double f1 = m::pow(1 + m::pow(0.492 / Pr, 9./16), -16./9);
		// Valid for 0.1 < Ra < 1e12
		double Nu0 = 0.825 + 0.387 * m::pow(Ra * f1, 1./6);
		double Nu = Nu0 * Nu0;
		return Nu;
	}
};

#include <math.h>

class FreeConvection_HorizontalSurface : public FreeConvectionModel {
public:
	FreeConvection_HorizontalSurface(double length, double width, bool topSide) {
		this->heatExchangeArea = length * width;
		this->characteristicLength = length * width / 2 / (length + width);
		this->topSide = topSide;
	}
	virtual double computeNusseltNumber(double Ra, double Pr, double wallOverheat) {
		// Valid for 0.001 < Pr < inf
		double f2 = m::pow(1 + m::pow(0.0322 / Pr, 11./20), -20./11);
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

class FreeConvection_CylindricalHorizontalSurface : public FreeConvectionModel {
public:
	FreeConvection_CylindricalHorizontalSurface(double length, double diameter) {
		this->heatExchangeArea = length * m::pi * diameter;
		this->characteristicLength = diameter;
	}
	virtual double computeNusseltNumber(double Ra, double Pr, double wallOverheat) {
		// Valid for 0 < Pr < inf
		double f3 = m::pow(1 + m::pow(0.559 / Pr, 9./16), -16./9);
		// Valid for 0.1 < Ra < 1e12
		double Nu0 = 0.6 + 0.387 * m::pow(Ra * f3, 1./6);
		double Nu = Nu0 * Nu0;
		return Nu;
	}
};

FreeConvectionModel* FreeConvectionModel_NusseltExpression_new(
		double characteristicLength, double heatExchangeArea, const char* nusseltExpression) {
	return new FreeConvectionModel_NusseltExpression(
			characteristicLength, heatExchangeArea, nusseltExpression);
}

FreeConvectionModel* FreeConvectionModel_VerticalSurface_new(
		double height, double width) {
	return FreeConvectionModel_VerticalSurface_new(height, width);
}

FreeConvectionModel* FreeConvectionModel_HorizontalSurfaceTop_new(
		double length, double width) {
	return new FreeConvection_HorizontalSurface(
			length, width, true);
}

FreeConvectionModel* FreeConvectionModel_HorizontalSurfaceBottom_new(
		double length, double width) {
	return new FreeConvection_HorizontalSurface(
			length, width, false);
}

FreeConvectionModel* FreeConvectionModel_CylindricalHorizontalSurface_new(
		double length, double diameter) {
	return new FreeConvection_CylindricalHorizontalSurface(
			length, diameter);
}
