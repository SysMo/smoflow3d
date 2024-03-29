/*
 * Pipe_R.h
 *
 *  Created on: Sep 19, 2014
 *      Author: Milen Borisov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#ifndef PIPE_R_H_
#define PIPE_R_H_

#include "media/MediumState.h"
#include "flow/FrictionFlowPipe.h"
#include "flow_R/FlowComponent_R.h"

#ifdef __cplusplus

class Pipe_R : public FlowComponent_R {
public:
	Pipe_R(FrictionFlowPipe* friction);
	virtual ~Pipe_R();

	virtual void init(MediumState* state1);
	virtual bool compute(double massFlowRate, double minDownstreamPressure);

	FrictionFlowPipe* getFrictionFlowPipe() {return friction;}

protected:
	FrictionFlowPipe* friction;
};

#else //_cplusplus
DECLARE_C_STRUCT(Pipe_R)
#endif //_cplusplus

BEGIN_C_LINKAGE
Pipe_R* Pipe_R_new(FrictionFlowPipe* friction);

Pipe_R* StraightPipe_R_new(
		double length,
		double hydraulicDiameter,
		double flowArea,
		double surfaceRoughness,
		double pressureDropGain);

Pipe_R* ElbowPipe_R_new(
		double hydraulicDiameter,
		double flowArea,
		double surfaceRoughness,
		double curvatureRadius,
		double bendAngle,
		double pressureDropGain);

Pipe_R* ConstantDragCoefficientPipe_new(
		double flowArea,
		double dragCoefficient,
		double pressureDropGain);

Pipe_R* ConstantDragCoefficientStraightPipe_new(
		double length,
		double hydraulicDiameter,
		double flowArea,
		double surfaceRoughness,
		double dragCoefficient,
		double pressureDropGain);

FrictionFlowPipe* Pipe_R_getFrictionFlowPipe(Pipe_R* pipe);

END_C_LINKAGE

#endif /* PIPE_R_H_ */
