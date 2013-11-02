/*
 * PipeHeatExchNoPrDropNoMassAcc.cpp
 *
 *  Created on: Aug 13, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "PipeHeatExchNoPrDropNoMassAcc_RC.h"
using namespace smoflow;

/**
 * Pipe_HeatExch_NoPrDr_NoMassAcc
 */
PipeHeatExchNoPrDropNoMassAcc_RC::PipeHeatExchNoPrDropNoMassAcc_RC(double stateTimeConstant) {
	this->stateTimeConstant = stateTimeConstant;
	stateVariableType = sTemperature;

	// internals
	port2LimitState = NULL;

	port2StateValue = 0.0;
	port2StateSetpoint = 0.0;

	// ports
	port1State = NULL;
	port1Flow = NULL;
	port2State = NULL;
	port2Flow = NULL;
	wallNode = NULL;
	wallHeatFlow = NULL;
}

PipeHeatExchNoPrDropNoMassAcc_RC::~PipeHeatExchNoPrDropNoMassAcc_RC() {
}

void PipeHeatExchNoPrDropNoMassAcc_RC::init(FluidFlow* port2Flow) {
	this->port2Flow = port2Flow;

	this->port1Flow = FluidFlow_new();
	FluidFlow_register(this->port1Flow);

	this->wallHeatFlow = HeatFlow_new();
	HeatFlow_register(this->wallHeatFlow);

	_init();
}

void PipeHeatExchNoPrDropNoMassAcc_RC::initStates(MediumState* port1State,
		ThermalNode* wallNode, StateVariableSet& innerStateInitializer) {
	this->port1State = port1State;
	this->wallNode = wallNode;

	this->port2State = MediumState_new(port1State->getMedium());
	MediumState_register(port2State);

	this->port2LimitState = MediumState_new(port1State->getMedium());
	MediumState_register(port2LimitState);

	port2State->init(iT, wallNode->getTemperature(), iP, port1State->p());
	if (stateVariableType == sTemperature) {
		this->port2StateValue = port2State->T();
	} else {
		this->port2StateValue = port2State->h();
	}
}

void PipeHeatExchNoPrDropNoMassAcc_RC::setOutletStateValue(double outletStateValue) {
	this->port2StateValue = outletStateValue;
	if (stateVariableType == sTemperature) {
		this->port2State->update_Tp(outletStateValue, port1State->p());
	} else {
		this->port2State->update_ph(port1State->p(), outletStateValue);
	}
}

double PipeHeatExchNoPrDropNoMassAcc_RC::getOutletStateDerivative() {
	double outletStateDerivative;
	if (stateVariableType == sTemperature) {
		outletStateDerivative = (port2StateSetpoint - port2State->T()) / stateTimeConstant;
	} else {
		outletStateDerivative = (port2StateSetpoint - port2State->h()) / stateTimeConstant;
	}
	return outletStateDerivative;
}

/*************************************************************
 ***   Pipe_HeatExch_NoPrDr_NoMassAcc implementation classes
 *************************************************************/
class PipeHeatExchNoPrDropNoMassAcc_RC_HEEfficiency : public PipeHeatExchNoPrDropNoMassAcc_RC {
public:
	PipeHeatExchNoPrDropNoMassAcc_RC_HEEfficiency(
			double heatExchEfficiency,
			double stateTimeConstant) :
			PipeHeatExchNoPrDropNoMassAcc_RC(stateTimeConstant) {
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
		port2StateSetpoint = inletTemperature + (wallTemperature - inletTemperature) * heatExchEfficiency;

	}

protected:
	double heatExchEfficiency;
};

class PipeHeatExchNoPrDropNoMassAcc_RC_Convection : public PipeHeatExchNoPrDropNoMassAcc_RC {
public:
	PipeHeatExchNoPrDropNoMassAcc_RC_Convection(
			ForcedConvection* convection,
			double stateTimeConstant) :
			PipeHeatExchNoPrDropNoMassAcc_RC(stateTimeConstant) {
		this->convection = convection;
		SMOCOMPONENT_SET_PARENT(this->convection, this);

		stateVariableType = sEnthalpy;
	}

	virtual void compute() {
		// Compute flows
		double massFlowRate = -port2Flow->massFlowRate;
		if (massFlowRate < -m::eps) {
			RaiseComponentError(this, "Reverse flow encountered");
		}
		port1Flow->massFlowRate = port2Flow->massFlowRate;
		port1Flow->enthalpyFlowRate = port1Flow->massFlowRate * port1State->h();
		wallHeatFlow->enthalpyFlowRate = massFlowRate * (port1State->h() - port2State->h());

		// Compute outlet setpoint
		const double minMassFlowRate = 1e-12;
		double wallTemperature = wallNode->getTemperature();
		double inletTemperature = port1State->T();
		port2LimitState->update_Tp(wallTemperature, port1State->p());
		if (massFlowRate > minMassFlowRate) {
			convection->compute(massFlowRate);
			port2StateSetpoint = port1State->h() + convection->getHeatFlowRate() / massFlowRate;
			if (wallTemperature > inletTemperature) {
				// Ensure the outlet temperature is not above wall temperature
				if (port2StateSetpoint > port2LimitState->h()) {
					port2StateSetpoint = port2LimitState->h();
				}
			} else {
				// Ensure the outlet temperature is not below wall temperature
				if (port2StateSetpoint < port2LimitState->h()) {
					port2StateSetpoint = port2LimitState->h();
				}
			}

		} else {
			port2StateSetpoint = port2LimitState->h();
		}
	}

protected:
	virtual void _init() {
		convection->init(port1State, port2State, wallNode);
	}

protected:
	ForcedConvection* convection;
};

/**
 * Pipe_HeatExch_NoPrDr_NoMassAc - C
 */
PipeHeatExchNoPrDropNoMassAcc_RC* PipeHeatExchNoPrDropNoMassAcc_RC_Efficiency_new(double heatExchEfficiency, double stateTimeConstant) {
	return new PipeHeatExchNoPrDropNoMassAcc_RC_HEEfficiency(heatExchEfficiency, stateTimeConstant);
}

PipeHeatExchNoPrDropNoMassAcc_RC* PipeHeatExchNoPrDropNoMassAcc_RC_Convection_new(ForcedConvection* convection, double stateTimeConstant) {
	return new PipeHeatExchNoPrDropNoMassAcc_RC_Convection(convection, stateTimeConstant);
}

void PipeHeatExchNoPrDropNoMassAcc_RC_init(PipeHeatExchNoPrDropNoMassAcc_RC* pipe, FluidFlow* port2Flow) {
	pipe->init(port2Flow);
}

void PipeHeatExchNoPrDropNoMassAcc_RC_initStates(PipeHeatExchNoPrDropNoMassAcc_RC* pipe, MediumState* port1State, ThermalNode* wallNode, StateVariableSet innerStateInitializer) {
	pipe->initStates(port1State, wallNode, innerStateInitializer);
}

void PipeHeatExchNoPrDropNoMassAcc_RC_compute(PipeHeatExchNoPrDropNoMassAcc_RC* pipe) {
	pipe->compute();
}

void PipeHeatExchNoPrDropNoMassAcc_RC_setOutletStateValue(PipeHeatExchNoPrDropNoMassAcc_RC* pipe,  double outletStateValue) {
	pipe->setOutletStateValue(outletStateValue);
}

double PipeHeatExchNoPrDropNoMassAcc_RC_getOutletStateValue(PipeHeatExchNoPrDropNoMassAcc_RC* pipe) {
	return pipe->getOutletStateValue();
}

double PipeHeatExchNoPrDropNoMassAcc_RC_getOutletStateDerivative(PipeHeatExchNoPrDropNoMassAcc_RC* pipe) {
	return pipe->getOutletStateDerivative();
}

MediumState* PipeHeatExchNoPrDropNoMassAcc_RC_getPort2State(PipeHeatExchNoPrDropNoMassAcc_RC* pipe) {
	return pipe->getPort2State();
}

FluidFlow* PipeHeatExchNoPrDropNoMassAcc_RC_getPort1Flow(PipeHeatExchNoPrDropNoMassAcc_RC* pipe) {
	return pipe->getPort1Flow();
}

HeatFlow* PipeHeatExchNoPrDropNoMassAcc_RC_getWallHeatFlow(PipeHeatExchNoPrDropNoMassAcc_RC* pipe) {
	return pipe->getWallHeatFlow();
}
