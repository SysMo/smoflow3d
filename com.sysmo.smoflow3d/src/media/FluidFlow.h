/*
 * FluidFlow.h
 *
 *  Created on: Jul 24, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#ifndef FLUIDFLOW_H_
#define FLUIDFLOW_H_

#include "util/CommonDefinitions.h"

BEGIN_C_LINKAGE
typedef struct {
	double massFlowRate;
	double enthalpyFlowRate;
	//double volumetricFlowRate; //:NOT_USED:
} FluidFlow;

FluidFlow* FluidFlow_new();
int FluidFlow_register(FluidFlow* flow);
FluidFlow* FluidFlow_get(int flowIndex);
END_C_LINKAGE

#endif /* FLUIDFLOW_H_ */
