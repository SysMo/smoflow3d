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
	FrictionFlowPipe(double length,	double hydraulicDiameter, double flowArea);
	virtual ~FrictionFlowPipe();

	void init(MediumState* state1, MediumState* state2);
	void setPressureDropGain(double gain){pressureDropGain = gain;}

	double computePressureDrop(double massFlowRate);
	double computeMassFlowRate(double pressureDrop);

	void updateFluidFlows(FluidFlow* flow1, FluidFlow* flow2);

	double getAbsolutePressureDrop() {return absPressureDrop;}
	double getMassFlowRate() {return massFlowRate;}

protected:
	virtual double dragCoefficient(double Re) = 0;
	MediumState* getUpstreamState(double massFlowRate);

protected:
	double length;
	double hydraulicDiameter;
	double flowArea;

private:
	double pressureDropGain;

	double massFlowRate;
	double absPressureDrop;

	MediumState* state1;
	MediumState* state2;

	double Re_cache;
};

#else //__cplusplus
DECLARE_C_STRUCT(FrictionFlowPipe)
#endif //__cplusplus

BEGIN_C_LINKAGE
FrictionFlowPipe* FrictionFlowPipe_CylindricalStraightPipe_new(double length, double diameter, double surfaceRoughness);
FrictionFlowPipe* FrictionFlowPipe_NonCylindricalStraightPipe_new(double length, double hydraulicDiameter, double flowArea, double surfaceRoughness);

void FrictionFlowPipe_init(FrictionFlowPipe* component, MediumState* state1, MediumState* state2);
void FrictionFlowPipe_setPressureDropGain(FrictionFlowPipe* component, double gain);

double FrictionFlowPipe_computePressureDrop(FrictionFlowPipe* component, double massFlowRate);
double FrictionFlowPipe_computeMassFlowRate(FrictionFlowPipe* component, double pressureDifference);

double FrictionFlowPipe_getAbsolutePressureDrop(FrictionFlowPipe* component);
double FrictionFlowPipe_getMassFlowRate(FrictionFlowPipe* component);
END_C_LINKAGE

#endif /* FRICTIONFLOWPIPE_H_ */
