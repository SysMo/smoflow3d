/*
 * PipeHeatExchNoPrDrNoMassAcc.cpp
 *
 *  Created on: Aug 13, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "PipeHeatExchNoPrDrNoMassAcc.h"

using namespace smoflow;

Pipe_HeatExch_NoPrDr_NoMassAcc::Pipe_HeatExch_NoPrDr_NoMassAcc(double stateTimeConstant) {
	this->stateTimeConstant = stateTimeConstant;
}

Pipe_HeatExch_NoPrDr_NoMassAcc::~Pipe_HeatExch_NoPrDr_NoMassAcc() {
}

void Pipe_HeatExch_NoPrDr_NoMassAcc::init(FluidFlow* outletFlow) {
	this->outletFlow = outletFlow;
	this->inletFlow = FluidFlow_new();
	FluidFlow_register(this->inletFlow);
	this->wallHeatFlow = HeatFlow_new();
	HeatFlow_register(this->wallHeatFlow);
	_init();
}

void Pipe_HeatExch_NoPrDr_NoMassAcc::initOutletState(
		MediumState* inletState, ThermalNode* wallNode) {
	this->inletState = inletState;
	this->wallNode = wallNode;
	this->outletState = MediumState_new(inletState->getMedium());
	MediumState_register(outletState);
	this->outletLimitState = MediumState_new(inletState->getMedium());
	MediumState_register(outletLimitState);

	outletState->update_Tp(wallNode->getTemperature(), inletState->p());
	if (stateVariable == sTemperature) {
		this->outletStateValue = outletState->T();
	} else {
		this->outletStateValue = outletState->h();
	}

}


void Pipe_HeatExch_NoPrDr_NoMassAcc::updateOutletState(double outletStateValue) {
	this->outletStateValue = outletStateValue;
	if (stateVariable == sTemperature) {
		this->outletState->update_Tp(outletStateValue, inletState->p());
	} else {
		this->outletState->update_ph(inletState->p(), outletStateValue);
	}
}

double Pipe_HeatExch_NoPrDr_NoMassAcc::getOutletStateDerivative() {
	double outletStateDerivative;
	if (stateVariable == sTemperature) {
		outletStateDerivative = (outletStateSetpoint - outletState->T()) / stateTimeConstant;
	} else {
		outletStateDerivative = (outletStateSetpoint - outletState->h()) / stateTimeConstant;
	}
	return outletStateDerivative;
}

class Pipe_HeatExch_NoPrDr_NoMassAcc_HEEfficiency
		: public Pipe_HeatExch_NoPrDr_NoMassAcc {
public:
	Pipe_HeatExch_NoPrDr_NoMassAcc_HEEfficiency(double heatExchEfficiency,
			double stateTimeConstant) : Pipe_HeatExch_NoPrDr_NoMassAcc(stateTimeConstant) {
		stateVariable = sTemperature;
		this->heatExchEfficiency = heatExchEfficiency;
	}
	virtual void compute() {
		double massFlowRate = - outletFlow->massFlowRate;
		inletFlow->massFlowRate = outletFlow->massFlowRate;
		inletFlow->enthalpyFlowRate = inletFlow->massFlowRate * inletState->h();
		wallHeatFlow->enthalpyFlowRate = massFlowRate * (inletState->h() - outletState->h());

		double inletTemperature = inletState->T();
		double wallTemperature = wallNode->getTemperature();
		outletStateSetpoint = inletTemperature +
				(wallTemperature - inletTemperature) * heatExchEfficiency;

	}
protected:
	double heatExchEfficiency;
};

class Pipe_HeatExch_NoPrDr_NoMassAcc_Convection
		: public Pipe_HeatExch_NoPrDr_NoMassAcc {
public:
	Pipe_HeatExch_NoPrDr_NoMassAcc_Convection(ForcedConvection* convection,
			double stateTimeConstant)  : Pipe_HeatExch_NoPrDr_NoMassAcc(stateTimeConstant){
		stateVariable = sEnthalpy;
		this->convection = convection;
		this->heatExchangeArea = convection->getHeatExchangeArea();
	}
	virtual void compute() {
		// Compute flows
		double massFlowRate = - outletFlow->massFlowRate;
		if (massFlowRate < - m::eps()) {
			RaiseError("Reverse flow encountered");
		}
		inletFlow->massFlowRate = outletFlow->massFlowRate;
		inletFlow->enthalpyFlowRate = inletFlow->massFlowRate * inletState->h();
		wallHeatFlow->enthalpyFlowRate = massFlowRate * (inletState->h() - outletState->h());
		// Compute outlet setpoint
		const double minMassFlowRate = 1e-12;
		double wallTemperature = wallNode->getTemperature();
		double inletTemperature = inletState->T();
		outletLimitState->update_Tp(wallTemperature, inletState->p());
		if (massFlowRate > minMassFlowRate) {
			convection->compute(massFlowRate);
			outletStateSetpoint = inletState->h() + convection->getHeatFlowRate() / massFlowRate;
			if (wallTemperature > inletTemperature) {
				// Ensure the outlet temperature is not above wall temperature
				if (outletStateSetpoint > outletLimitState->h()) {
					outletStateSetpoint = outletLimitState->h();
				}
			} else {
				// Ensure the outlet temperature is not below wall temperature
				if (outletStateSetpoint < outletLimitState->h()) {
					outletStateSetpoint = outletLimitState->h();
				}
			}

		} else {
			outletStateSetpoint = outletLimitState->h();
		}
	}
protected:
	virtual void _init() {
		convection->init(inletState, outletState, wallNode);
	}
	ForcedConvection* convection;
	double heatExchangeArea;
};

Pipe_HeatExch_NoPrDr_NoMassAcc* Pipe_HeatExch_NoPrDr_NoMassAcc_Efficiency_new(
		double heatExchEfficiency, double stateTimeConstant) {
	return new Pipe_HeatExch_NoPrDr_NoMassAcc_HEEfficiency(
			heatExchEfficiency, stateTimeConstant);
}

Pipe_HeatExch_NoPrDr_NoMassAcc* Pipe_HeatExch_NoPrDr_NoMassAcc_Convection_new(
		ForcedConvection* convection, double stateTimeConstant) {
	return new Pipe_HeatExch_NoPrDr_NoMassAcc_Convection(
			convection, stateTimeConstant);
}

#define KOMPONENT Pipe_HeatExch_NoPrDr_NoMassAcc

KOMPONENT_FUNC(void, init, FluidFlow* outletFlow) {
	component->init(outletFlow);
}

KOMPONENT_FUNC(void, initOutletState, MediumState* inletState, ThermalNode* wallNode) {
	component->initOutletState(inletState, wallNode);
}

KOMPONENT_FUNC(void, updateOutletState, double outletStateValue) {
	component->updateOutletState(outletStateValue);
}

KOMPONENT_FUNC_V(void, compute) {
	component->compute();
}

KOMPONENT_FUNC_V(MediumState*, getOutletState) {
	return component->getOutletState();
}

KOMPONENT_FUNC_V(double, getOutletStateValue) {
	return component->getOutletStateValue();
}

KOMPONENT_FUNC_V(double, getOutletStateDerivative) {
	return component->getOutletStateDerivative();
}

KOMPONENT_FUNC_V(HeatFlow*, getWallHeatFlow) {
	return component->getWallHeatFlow();
}

KOMPONENT_FUNC_V(FluidFlow*, getInletFlow) {
	return component->getInletFlow();
}

#undef KOMPONENT
