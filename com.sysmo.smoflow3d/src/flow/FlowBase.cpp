/*
 * FlowBase.cpp
 *
 *  Created on: Aug 8, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "FlowBase.h"

/* ==============================================
 * Heat flow
 * ==============================================*/
static std::vector<HeatFlow*> HeatFlowRegistry;

HeatFlow* HeatFlow_new() {
	return new HeatFlow();
}

int HeatFlow_register(HeatFlow* flow) {
	HeatFlowRegistry.push_back(flow);
	return HeatFlowRegistry.size();
}

HeatFlow* HeatFlow_get(int flowIndex) {
	return HeatFlowRegistry.at(flowIndex - 1);
}

void HeatFlow_setEnthalpyFlowRate(HeatFlow* flow, double enthalpyFlowRate) {
	flow->enthalpyFlowRate = enthalpyFlowRate;
}

double HeatFlow_getEnthalpyFlowRate(HeatFlow* flow) {
	return flow->enthalpyFlowRate;
}

/* ==============================================
 * Fluid flow
 * ==============================================*/
static std::vector<FluidFlow*> FluidFlowRegistry;

FluidFlow* FluidFlow_new(){
	return new FluidFlow();
}

int FluidFlow_register(FluidFlow* flow){
	FluidFlowRegistry.push_back(flow);
	return FluidFlowRegistry.size();
}

FluidFlow* FluidFlow_get(int flowIndex) {
	return FluidFlowRegistry.at(flowIndex - 1);
}

void FluidFlow_setMassFlowRate(FluidFlow* flow, double massFlowRate) {
	flow->massFlowRate = massFlowRate;
}

double FluidFlow_getMassFlowRate(FluidFlow* flow) {
	return flow->massFlowRate;
}

void FluidFlow_setEnthalpyFlowRate(FluidFlow* flow, double enthalpyFlowRate) {
	flow->enthalpyFlowRate = enthalpyFlowRate;
}

double FluidFlow_getEnthalpyFlowRate(FluidFlow* flow) {
	return flow->enthalpyFlowRate;
}

