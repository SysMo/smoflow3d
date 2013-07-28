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
END_C_LINKAGE
