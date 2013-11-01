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
	FrictionFlowPipe(double hydraulicDiameter, double flowArea, double flowFactor);
	virtual ~FrictionFlowPipe();

	void init(MediumState* state1, MediumState* state2);
	void setPressureDropGain(double gain){pressureDropGain = gain;}

	double computePressureDrop(double massFlowRate);
	double computeMassFlowRate(double pressureDrop);

	double getAbsolutePressureDrop() {return absPressureDrop;}
	double getMassFlowRate() {return massFlowRate;}

	void updateFluidFlows(FluidFlow* flow1, FluidFlow* flow2);

protected:
	virtual double frictionFactor(double Re) = 0;

protected:
	double flowArea;
	double hydraulicDiameter;
	double flowFactor;

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
FrictionFlowPipe* FrictionFlowPipe_StraightPipe_new(double diameter, double length, double surfaceRoughness);

void FrictionFlowPipe_init(FrictionFlowPipe* component, MediumState* state1, MediumState* state2);
void FrictionFlowPipe_setPressureDropGain(FrictionFlowPipe* component, double gain);

double FrictionFlowPipe_computePressureDrop(FrictionFlowPipe* component, double massFlowRate);
double FrictionFlowPipe_computeMassFlowRate(FrictionFlowPipe* component, double pressureDifference);

double FrictionFlowPipe_getAbsolutePressureDrop(FrictionFlowPipe* component);
double FrictionFlowPipe_getMassFlowRate(FrictionFlowPipe* component);
END_C_LINKAGE

#endif /* FRICTIONFLOWPIPE_H_ */
