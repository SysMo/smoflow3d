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
