/*
 * FrictionFlowPipe.h
 *
 *  Created on: Aug 22, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#ifndef FRICTIONFLOWPIPE_H_
#define FRICTIONFLOWPIPE_H_

#include "media/MediumState.h"
#include "flow/FlowBase.h"

#ifdef __cplusplus

class FrictionFlowPipe {
public:
	FrictionFlowPipe(double flowArea);
	virtual ~FrictionFlowPipe();

	void init(MediumState* state1, MediumState* state2);
	void setPressureDropGain(double gain) {pressureDropGain = gain;}

	virtual double computePressureDrop(double massFlowRate) = 0;
	virtual double computeMassFlowRate(double pressureDrop) = 0;

	void updateFluidFlows(FluidFlow* flow1, FluidFlow* flow2);

	double getAbsolutePressureDrop() {return absPressureDrop;}
	double getMassFlowRate() {return massFlowRate;}

	double getReynoldsNumber() {return reynoldsNumber;}
	double getDragCoefficient() {return dragCoefficient;}

protected:
	MediumState* getUpstreamState(double massFlowRate);

protected:
	double flowArea;
	double pressureDropGain;

	MediumState* state1;
	MediumState* state2;

	double massFlowRate;
	double absPressureDrop;

	double reynoldsNumber;
	double dragCoefficient;
};

#else //__cplusplus
DECLARE_C_STRUCT(FrictionFlowPipe)
#endif //__cplusplus

BEGIN_C_LINKAGE
FrictionFlowPipe* FrictionFlowPipe_StraightPipe_new(double length, double hydraulicDiameter, double flowArea, double surfaceRoughness);
FrictionFlowPipe* FrictionFlowPipe_ElbowPipe_new(double hydraulicDiameter, double flowArea, double surfaceRoughness, double curvatureRadius, double bendAngle);
FrictionFlowPipe* FrictionFlowPipe_ConstantDragCoefficientPipe_new(double flowArea, double dragCoefficient);
FrictionFlowPipe* FrictionFlowPipe_ConstantDragCoefficientStraightPipe_new(double length, double hydraulicDiameter, double flowArea, double surfaceRoughness, double dragCoefficient);

void FrictionFlowPipe_setPressureDropGain(FrictionFlowPipe* component, double gain);

double FrictionFlowPipe_getAbsolutePressureDrop(FrictionFlowPipe* component);
double FrictionFlowPipe_getMassFlowRate(FrictionFlowPipe* component);
END_C_LINKAGE

#endif /* FRICTIONFLOWPIPE_H_ */
