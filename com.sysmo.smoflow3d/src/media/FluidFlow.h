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

typedef struct {
	double massFlowRate;
	double volumetricFlowRate;
	double enthalpyFlowRate;
} FluidFlow;

BEGIN_C_LINKAGE
FluidFlow* FluidFlow_new();
int FluidFlow_register(FluidFlow* flow);
FluidFlow* FluidFlow_get(int flowIndex);
END_C_LINKAGE

#endif /* FLUIDFLOW_H_ */
