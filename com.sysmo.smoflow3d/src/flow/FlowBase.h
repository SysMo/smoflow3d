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
struct FlowBase : public  SmoComponent {
};

struct HeatFlow : public FlowBase {
	// the heat flow rate
	double enthalpyFlowRate;
};

struct FluidFlow : public FlowBase {
	double massFlowRate;
	double enthalpyFlowRate;
	//double volumetricFlowRate; //:NOT_USED:
};
#else //__cplusplus
DECLARE_C_STRUCT(HeatFlow)
DECLARE_C_STRUCT(FluidFlow)
#endif // __cplusplus

BEGIN_C_LINKAGE
/* ==============================================
 * Heat flow
 * ==============================================*/
HeatFlow* HeatFlow_new();
int HeatFlow_register(HeatFlow* flow);
HeatFlow* HeatFlow_get(int flowIndex);
void HeatFlow_setEnthalpyFlowRate(HeatFlow* flow, double enthalpyFlowRate);
double HeatFlow_getEnthalpyFlowRate(HeatFlow* flow);

/* ==============================================
 * Fluid flow
 * ==============================================*/
FluidFlow* FluidFlow_new();
int FluidFlow_register(FluidFlow* flow);
FluidFlow* FluidFlow_get(int flowIndex);
void FluidFlow_setMassFlowRate(FluidFlow* flow, double massFlowRate);
double FluidFlow_getMassFlowRate(FluidFlow* flow);
void FluidFlow_setEnthalpyFlowRate(FluidFlow* flow, double enthalpyFlowRate);
double FluidFlow_getEnthalpyFlowRate(FluidFlow* flow);

END_C_LINKAGE

#endif /* FLOWBASE_H_ */
