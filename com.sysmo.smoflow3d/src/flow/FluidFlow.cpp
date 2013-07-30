/*
 * FluidFlow.cpp
 *
 *  Created on: Jul 24, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "FluidFlow.h"
#include <vector>

static std::vector<FluidFlow*> FluidFlowRegistry;

BEGIN_C_LINKAGE
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

END_C_LINKAGE
