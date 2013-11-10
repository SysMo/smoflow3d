/*
 * FlowBase.h
 *
 *  Created on: Aug 8, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#ifndef FLOWBASE_H_
#define FLOWBASE_H_

#include "util/CommonDefinitions.h"

#ifdef __cplusplus

#include "util/SmoComponent.h"

struct FlowBase : public SmoObject {
};

struct HeatFlow : public FlowBase {
	HeatFlow () : enthalpyFlowRate(0.0) {}

	double enthalpyFlowRate; // equals of the heat flow rate
};

struct FluidFlow : public FlowBase {
	FluidFlow () : massFlowRate(0.0), enthalpyFlowRate(0.0) {}

	double massFlowRate;
	double enthalpyFlowRate;
	//double volumetricFlowRate; //:NOT_USED:
};

#else //__cplusplus
DECLARE_C_STRUCT(HeatFlow)
DECLARE_C_STRUCT(FluidFlow)
#endif // __cplusplus

BEGIN_C_LINKAGE
/**
 * Heat flow
 */
HeatFlow* HeatFlow_new();
int HeatFlow_register(HeatFlow* flow);
HeatFlow* HeatFlow_get(int flowIndex);
void HeatFlow_setEnthalpyFlowRate(HeatFlow* flow, double enthalpyFlowRate);
double HeatFlow_getEnthalpyFlowRate(HeatFlow* flow);

/**
 * Fluid fow
 */
FluidFlow* FluidFlow_new();
int FluidFlow_register(FluidFlow* flow);
FluidFlow* FluidFlow_get(int flowIndex);
void FluidFlow_setMassFlowRate(FluidFlow* flow, double massFlowRate);
double FluidFlow_getMassFlowRate(FluidFlow* flow);
void FluidFlow_setEnthalpyFlowRate(FluidFlow* flow, double enthalpyFlowRate);
double FluidFlow_getEnthalpyFlowRate(FluidFlow* flow);
END_C_LINKAGE

#endif /* FLOWBASE_H_ */
