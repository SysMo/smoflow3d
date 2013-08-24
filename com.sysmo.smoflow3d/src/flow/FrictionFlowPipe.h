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
	FrictionFlowPipe(double hydraulicDiameter,
			double flowArea, double flowFactor);
	virtual ~FrictionFlowPipe();
	void setPressureDropGain(double gain){
		this->pressureDropGain = gain;
	}
	void init(MediumState* state1, MediumState* state2);
	double computePressureDrop(double massFlowRate);
	double computeMassFlowRate(double pressureDifference);
	virtual double frictionFactor(double Re) = 0;
	double getAbsolutePressureDrop() {
		return absolutePressureDrop;
	}
	double getMassFlowRate() {
		return massFlowRate;
	}
protected:
	double flowArea;
	double hydraulicDiameter;
	double flowFactor;
	double pressureDropGain;
	double massFlowRate;
	double absolutePressureDrop;
	MediumState* state1;
	MediumState* state2;
};

#else //__cplusplus
DECLARE_C_STRUCT(FrictionFlowPipe)
#endif //__cplusplus

BEGIN_C_LINKAGE
FrictionFlowPipe* FrictionFlowPipe_StraightPipe_new(
		double diameter, double length, double surfaceRoughness);
void FrictionFlowPipe_setPressureDropGain(FrictionFlowPipe* component, double gain);
void FrictionFlowPipe_init(FrictionFlowPipe* component, MediumState* state1, MediumState* state2);
double FrictionFlowPipe_computePressureDrop(FrictionFlowPipe* component, double massFlowRate);
double FrictionFlowPipe_computeMassFlowRate(FrictionFlowPipe* component, double pressureDifference);
double FrictionFlowPipe_getAbsolutePressureDrop(FrictionFlowPipe* component);
double FrictionFlowPipe_getMassFlowRate(FrictionFlowPipe* component);

END_C_LINKAGE

#endif /* FRICTIONFLOWPIPE_H_ */
