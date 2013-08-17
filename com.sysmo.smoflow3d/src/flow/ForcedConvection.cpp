/*
 * ForcedConvection.cpp
 *
 *  Created on: Aug 10, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "ForcedConvection.h"
using namespace smoflow;

ForcedConvection::ForcedConvection() {
	// TODO Auto-generated constructor stub

}

ForcedConvection::~ForcedConvection() {
	// TODO Auto-generated destructor stub
}

void ForcedConvection::init(MediumState* fluidState, ThermalNode* wallNode, FluidFlow* flow) {
	Convection::init(fluidState, wallNode);
	this->flow = flow;
}

void ForcedConvection::compute() {
	// Calculate film state
	double fluidTemperature = fluidState->T();
	double wallTemperature = wallNode->getTemperature();
	double filmTemperature = (fluidTemperature + wallTemperature)/2;
	double wallOverheat = wallTemperature - fluidTemperature;
	filmState->update_Tp(filmTemperature, fluidState->p());


	double v = m::fabs(flow->massFlowRate) / filmState->rho() / flowArea;
	Re = filmState->rho() * v * characteristicLength / filmState->mu();
	Pr = filmState->Pr();
	Nu = computeNusseltNumber(Re, Pr);
	convectionCoefficient = Nu * filmState->lambda() / characteristicLength;
	heatFlowRate = heatExchangeGain * convectionCoefficient
			* heatExchangeArea * wallOverheat;
}

void ForcedConvection_init(ForcedConvection* convection, MediumState* fluidState,
		ThermalNode* wallNode, FluidFlow* flow) {
	convection->init(fluidState, wallNode, flow);
}

void ForcedConvection_compute(ForcedConvection* convection) {
	convection->compute();
}

double ForcedConvection_getReynoldsNumber(ForcedConvection* convection) {
	return convection->getReynoldsNumber();
}
/********************************************************
 *** Forced convection models
 ********************************************************/

class ForcedConvection_GivenConvectionCoefficient : public ForcedConvection {
public:
	ForcedConvection_GivenConvectionCoefficient(double heatExchangeArea) {
		this->heatExchangeArea = heatExchangeArea;
	}
	void compute() {
		double fluidTemperature = fluidState->T();
		double wallTemperature = wallNode->getTemperature();
		double wallOverheat = wallTemperature - fluidTemperature;
		Re = 0;
		Pr = 0;
		Nu = 0;
		heatFlowRate = heatExchangeGain *convectionCoefficient
				* heatExchangeArea * wallOverheat;
	}
protected:
	double computeNusseltNumber(double Re, double Pr) {
		return 0;
	}
};

ForcedConvection* ForcedConvection_GivenConvectionCoefficient_new(
		double heatExchangeArea) {
	return new ForcedConvection_GivenConvectionCoefficient(heatExchangeArea);
}



class ForcedConvection_StraightPipe : public ForcedConvection {
public:
	ForcedConvection_StraightPipe(
			double hydraulicDiameter, double flowArea, double pipeLength) {
		this->characteristicLength = hydraulicDiameter;
		this->flowArea = flowArea;
		double perimeter = 4 * flowArea / hydraulicDiameter;
		this->heatExchangeArea = perimeter * pipeLength;
	}
	double computeNusseltNumber(double Re, double Pr) {
		double Nu;
		const double ReL = 2300;
		const double ReH = 1e4;

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
		return 3.66;
	}
	inline double NuTurbulent(double Re, double Pr) {
		// Friction factor
		double xi = m::pow(1.8 * m::log10(Re) - 1.5, -2);
		double NuNum = (xi / 8) * Re * Pr;
		double NuDenom = 1 + 12.7 * m::sqrt(xi / 8) * (m::pow(Pr, 2./3) - 1);
		return NuNum/NuDenom;
	}
};

ForcedConvection* ForcedConvection_StraightPipe_new(
		double hydraulicDiameter, double flowArea, double pipeLength) {
	return new ForcedConvection_StraightPipe(hydraulicDiameter,
			flowArea, pipeLength);
}

