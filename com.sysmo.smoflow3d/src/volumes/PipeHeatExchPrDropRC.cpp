/*
 * PipeHeatExchPrDropRC.cpp
 *
 *  Created on: Aug 23, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "PipeHeatExchPrDropRC.h"

PipeHeatExchPrDrop_RC::PipeHeatExchPrDrop_RC(
		double hydraulicDiameter, double flowArea,
		double length, double surfaceRoughness) {
	this->hydraulicDiameter = hydraulicDiameter;
	this->flowArea = flowArea;
	this->length = length;
	this->surfaceRoughness = surfaceRoughness;
	this->volume = flowArea * length;
}

PipeHeatExchPrDrop_RC::~PipeHeatExchPrDrop_RC() {
}

void PipeHeatExchPrDrop_RC::_init() {
	// TODO provide for different pressure drop and convection geometries
	friction = FrictionFlowPipe_StraightPipe_new(
			hydraulicDiameter, length, surfaceRoughness);
	friction->init(port1State, port1State);
	convection = ForcedConvection_StraightPipe_new(
			hydraulicDiameter, flowArea, length);
	convection->init(port2State, port2State, wallNode);
	convection->setLimitOutput(false);
}

void PipeHeatExchPrDrop_RC::_createState() {
	accFluid = FluidChamber_new(port1State->getMedium());
	accFluid->setVolume(volume);
	accFluid->selectStates(iT, iD);
	// TODO maybe user initialization should be included here
	accFluid->setStateValues(wallNode->getTemperature(), port1State->p());
	port2State = accFluid->getFluidState();
}

void PipeHeatExchPrDrop_RC::compute() {
	double dp = port1State->p() - port2State->p();
	double massFlowRate = friction->computeMassFlowRate(dp);
	convection->compute(massFlowRate);
	double netHeatFlowRate = convection->getHeatFlowRate();
	double netEnthalpyFlow = 0;
	if (massFlowRate > 0) {
		netEnthalpyFlow += massFlowRate * port1State->h();
		netEnthalpyFlow += port2Flow->massFlowRate * port2State->h();
	} else {
		netEnthalpyFlow += massFlowRate * port2State->h();
		netEnthalpyFlow += port2Flow->enthalpyFlowRate;
	}
	double netMassFlowRate = massFlowRate + port2Flow->massFlowRate;
	accFluid->computeStateDerivatives(netMassFlowRate, netEnthalpyFlow,
			netHeatFlowRate, 0);
}
