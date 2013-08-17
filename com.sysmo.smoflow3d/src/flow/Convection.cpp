/*
 * Convection.cpp
 *
 *  Created on: Aug 10, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "Convection.h"

/*
ConvectionModel::ConvectionModel() {
		characteristicLength = 0;
		heatExchangeArea = 0;
}
*/

Convection::Convection() {
	heatExchangeGain = 1.0;
}

Convection::~Convection() {
}

void Convection::init(MediumState* fluidState, ThermalNode* wallNode) {
	this->fluidState = fluidState;
	this->wallNode = wallNode;
	this->filmState = MediumState_new(fluidState->getMedium());
	MediumState_register(this->filmState);
}

void Convection::getFlow_Wall(HeatFlow* flow) {
	flow->enthalpyFlowRate = - heatFlowRate;
}

void Convection::getFlow_Fluid(FluidFlow* flow) {
	flow->enthalpyFlowRate = heatFlowRate;
	flow->massFlowRate = 0;
}

void Convection_setHeatExchangeGain(Convection* convection, double gain) {
	convection->setHeatExchangeGain(gain);
}

double Convection_getPrandtlNumber(Convection* convection) {
	return convection->getPrandtlNumber();
}

double Convection_getNusseltNumber(Convection* convection) {
	return convection->getNusseltNumber();
}

void Convection_setConvectionCoefficient(Convection* convection,
		double convectionCoefficient) {
	convection->setConvectionCoefficient(convectionCoefficient);
}

double Convection_getConvectionCoefficient(Convection* convection) {
	return convection->getConvectionCoefficient();
}

double Convection_getHeatFlowRate(Convection* convection) {
	return convection->getHeatFlowRate();
}
void Convection_getFlow_Wall(Convection* convection, HeatFlow* flow) {
	convection->getFlow_Wall(flow);
}

void Convection_getFlow_Fluid(Convection* convection, FluidFlow* flow) {
	convection->getFlow_Fluid(flow);
}

