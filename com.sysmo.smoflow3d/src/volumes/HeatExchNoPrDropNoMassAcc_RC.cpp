/*
 * HeatExchNoPrDropNoMassAcc_RC.cpp
 *
 *  Created on: Aug 13, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "HeatExchNoPrDropNoMassAcc_RC.h"

using namespace smoflow;

/**
 * Pipe_HeatExch_NoPrDr_NoMassAcc
 */
HeatExchNoPrDropNoMassAcc_RC::HeatExchNoPrDropNoMassAcc_RC(double stateTimeConstant) {
	this->stateTimeConstant = stateTimeConstant;
	stateVariableType = sTemperature;

	// internals
	stateValue = 0.0;
	stateSetpoint = 0.0;

	// ports
	port1State = NULL;
	port1Flow = NULL;
	port2State = NULL;
	port2Flow = NULL;
	wallNode = NULL;
	wallHeatFlow = NULL;
}

HeatExchNoPrDropNoMassAcc_RC::~HeatExchNoPrDropNoMassAcc_RC() {
}

void HeatExchNoPrDropNoMassAcc_RC::init(FluidFlow* port2Flow) {
	this->port2Flow = port2Flow;

	this->port1Flow = FluidFlow_new();
	FluidFlow_register(this->port1Flow);

	this->wallHeatFlow = HeatFlow_new();
	HeatFlow_register(this->wallHeatFlow);
}

void HeatExchNoPrDropNoMassAcc_RC::initStates(MediumState* port1State, ThermalNode* wallNode) {
	this->port1State = port1State;
	this->wallNode = wallNode;

	this->port2State = MediumState_new(port1State->getMedium());
	MediumState_register(port2State);

	port2State->init(iT, wallNode->getTemperature(), iP, port1State->p());
	if (stateVariableType == sTemperature) {
		this->stateValue = port2State->T();
	} else {
		this->stateValue = port2State->h();
	}
}

void HeatExchNoPrDropNoMassAcc_RC::setStateValue(double stateValue) {
	this->stateValue = stateValue;
	if (stateVariableType == sTemperature) {
		this->port2State->update_Tp(stateValue, port1State->p());
	} else {
		this->port2State->update_ph(port1State->p(), stateValue);
	}
}

double HeatExchNoPrDropNoMassAcc_RC::getStateDerivative() {
	double stateDerivative;
	if (stateVariableType == sTemperature) {
		stateDerivative = (stateSetpoint - port2State->T()) / stateTimeConstant;
	} else {
		stateDerivative = (stateSetpoint - port2State->h()) / stateTimeConstant;
	}
	return stateDerivative;
}

/*************************************************************
 ***   Pipe_HeatExch_NoPrDr_NoMassAcc implementation classes
 *************************************************************/
class PipeHeatExchNoPrDropNoMassAcc_RC_HEEfficiency : public HeatExchNoPrDropNoMassAcc_RC {
public:
	PipeHeatExchNoPrDropNoMassAcc_RC_HEEfficiency(
			double heatExchEfficiency,
			double stateTimeConstant) :
			HeatExchNoPrDropNoMassAcc_RC(stateTimeConstant) {
		this->heatExchEfficiency = heatExchEfficiency;

		stateVariableType = sTemperature;
	}

	virtual void compute() {
		double massFlowRate = -port2Flow->massFlowRate;
		port1Flow->massFlowRate = port2Flow->massFlowRate;
		port1Flow->enthalpyFlowRate = port1Flow->massFlowRate * port1State->h();
		wallHeatFlow->enthalpyFlowRate = massFlowRate * (port1State->h() - port2State->h());

		double inletTemperature = port1State->T();
		double wallTemperature = wallNode->getTemperature();
		stateSetpoint = inletTemperature + (wallTemperature - inletTemperature) * heatExchEfficiency;
	}

protected:
	double heatExchEfficiency;
};

class PipeHeatExchNoPrDropNoMassAcc_RC_Convection : public HeatExchNoPrDropNoMassAcc_RC {
public:
	PipeHeatExchNoPrDropNoMassAcc_RC_Convection(
			ForcedConvection* convection,
			double stateTimeConstant) :
			HeatExchNoPrDropNoMassAcc_RC(stateTimeConstant) {
		this->convection = convection;
		SMOCOMPONENT_SET_PARENT(this->convection, this);
		port2LimitState = NULL;

		stateVariableType = sEnthalpy;
	}

	virtual void initStates(MediumState* port1State, ThermalNode* wallNode) {
		HeatExchNoPrDropNoMassAcc_RC::initStates(port1State, wallNode);
		convection->init(port1State, port2State, wallNode);

		port2LimitState = MediumState_new(port1State->getMedium());
		MediumState_register(port2LimitState);
	}

	virtual void compute() {
		// Compute flows
		double massFlowRate = -port2Flow->massFlowRate;
		if (massFlowRate < 0.0) {
			RaiseComponentError(this, "Reverse flow encouuntered. Restrict the flow direction, e.g. by adding check valve.");
		}
		port1Flow->massFlowRate = port2Flow->massFlowRate;
		port1Flow->enthalpyFlowRate = port1Flow->massFlowRate * port1State->h();
		wallHeatFlow->enthalpyFlowRate = massFlowRate * (port1State->h() - port2State->h());

		// Compute outlet setpoint
		double wallTemperature = wallNode->getTemperature();
		double inletTemperature = port1State->T();
		port2LimitState->update_Tp(wallTemperature, port1State->p());
		if (massFlowRate > cst::MinMassFlowRate) {
			convection->compute(massFlowRate);
			stateSetpoint = port1State->h() + convection->getHeatFlowRate() / massFlowRate;
			if (wallTemperature > inletTemperature) {
				// Ensure the outlet temperature is not above wall temperature
				if (stateSetpoint > port2LimitState->h()) {
					stateSetpoint = port2LimitState->h();
				}
			} else {
				// Ensure the outlet temperature is not below wall temperature
				if (stateSetpoint < port2LimitState->h()) {
					stateSetpoint = port2LimitState->h();
				}
			}

		} else {
			stateSetpoint = port2LimitState->h();
		}
	}

protected:
	ForcedConvection* convection;
	MediumState* port2LimitState;
};

/**
 * Pipe_HeatExch_NoPrDr_NoMassAc - C
 */
HeatExchNoPrDropNoMassAcc_RC* HeatExchNoPrDropNoMassAcc_RC_Efficiency_new(double heatExchEfficiency, double stateTimeConstant) {
	return new PipeHeatExchNoPrDropNoMassAcc_RC_HEEfficiency(heatExchEfficiency, stateTimeConstant);
}

HeatExchNoPrDropNoMassAcc_RC* HeatExchNoPrDropNoMassAcc_RC_Convection_new(ForcedConvection* convection, double stateTimeConstant) {
	return new PipeHeatExchNoPrDropNoMassAcc_RC_Convection(convection, stateTimeConstant);
}

void HeatExchNoPrDropNoMassAcc_RC_init(HeatExchNoPrDropNoMassAcc_RC* heatExch, FluidFlow* port2Flow) {
	heatExch->init(port2Flow);
}

void HeatExchNoPrDropNoMassAcc_RC_initStates(HeatExchNoPrDropNoMassAcc_RC* heatExch, MediumState* port1State, ThermalNode* wallNode) {
	heatExch->initStates(port1State, wallNode);
}

void HeatExchNoPrDropNoMassAcc_RC_compute(HeatExchNoPrDropNoMassAcc_RC* heatExch) {
	heatExch->compute();
}

void HeatExchNoPrDropNoMassAcc_RC_setStateValue(HeatExchNoPrDropNoMassAcc_RC* heatExch,  double stateValue) {
	heatExch->setStateValue(stateValue);
}

double HeatExchNoPrDropNoMassAcc_RC_getStateValue(HeatExchNoPrDropNoMassAcc_RC* heatExch) {
	return heatExch->getStateValue();
}

double HeatExchNoPrDropNoMassAcc_RC_getStateDerivative(HeatExchNoPrDropNoMassAcc_RC* heatExch) {
	return heatExch->getStateDerivative();
}

MediumState* HeatExchNoPrDropNoMassAcc_RC_getPort2State(HeatExchNoPrDropNoMassAcc_RC* heatExch) {
	return heatExch->getPort2State();
}

FluidFlow* HeatExchNoPrDropNoMassAcc_RC_getPort1Flow(HeatExchNoPrDropNoMassAcc_RC* heatExch) {
	return heatExch->getPort1Flow();
}

HeatFlow* HeatExchNoPrDropNoMassAcc_RC_getWallHeatFlow(HeatExchNoPrDropNoMassAcc_RC* heatExch) {
	return heatExch->getWallHeatFlow();
}
