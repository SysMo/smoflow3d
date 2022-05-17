/*
 * FlowBase.cpp
 *
 *  Created on: Aug 8, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "FlowBase.h"
#include "util/CommonDefinitions.h"

using namespace smoflow;

/**
 * Heat flow - C
 */
static std::vector<HeatFlow*> HeatFlowRegistry;

HeatFlow* HeatFlow_new() {
	return new HeatFlow();
}

int HeatFlow_register(HeatFlow* flow) {
	HeatFlowRegistry.push_back(flow);
	size_t instanceIndex = HeatFlowRegistry.size();
	flow->instanceIndex = instanceIndex;
	return instanceIndex;
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

/**
 * Fluid flow - C
 */
static std::vector<FluidFlow*> FluidFlowRegistry;

FluidFlow* FluidFlow_new(){
	return new FluidFlow();
}

int FluidFlow_register(FluidFlow* flow){
	FluidFlowRegistry.push_back(flow);
	size_t instanceIndex = FluidFlowRegistry.size();
	flow->instanceIndex = instanceIndex;
	return instanceIndex;
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

void FluidFlow_setVolume(FluidFlow* flow, double volume) {
	flow->volume = volume;
}

double FluidFlow_getVolume(FluidFlow* flow) {
	return flow->volume;
}

void FluidFlow_setVolumeDot(FluidFlow* flow, double volumeDot) {
	flow->volumeDot = volumeDot;
}

double FluidFlow_getVolumeDot(FluidFlow* flow) {
	return flow->volumeDot;
}

void FluidFlow_copy(FluidFlow* flowSource, FluidFlow* flowTarget) {
	flowTarget->enthalpyFlowRate = flowSource->enthalpyFlowRate;
	flowTarget->massFlowRate = flowSource->massFlowRate;
	flowTarget->volume = flowSource->volume;
	flowTarget->volumeDot = flowSource->volumeDot;
}

void FluidFlow_zero(FluidFlow* flow) {
	flow->enthalpyFlowRate = cst::zeroSpecEnthalpy;
	flow->massFlowRate = cst::zeroMassFlowRate;
	flow->volume = 0.0;
	flow->volumeDot = 0.0;
}
