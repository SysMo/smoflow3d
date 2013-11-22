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

	double getReynoldsNumber() {return friction->getReynoldsNumber();}
	double getDragCoefficient() {return friction->getDragCoefficient();}

protected:
	FrictionFlowPipe* friction;
};

#else //_cplusplus
DECLARE_C_STRUCT(Pipe_R)
#endif //_cplusplus

BEGIN_C_LINKAGE
Pipe_R* Pipe_R_new(FrictionFlowPipe* friction);

Pipe_R* CylindricalStraightPipe_R_new(
		double length,
		double diameter,
		double surfaceRoughness,
		double pressureDropGain);

Pipe_R* NonCylindricalStraightPipe_R_new(
		double length,
		double hydraulicDiameter,
		double flowArea,
		double surfaceRoughness,
		double pressureDropGain);

Pipe_R* CylindricalElbowPipe_R_new(
		double diameter,
		double surfaceRoughness,
		double curvatureRadius,
		double bendAngle,
		double pressureDropGain);

Pipe_R* NonCylindricalElbowPipe_R_new(
		double hydraulicDiameter,
		double flowArea,
		double surfaceRoughness,
		 double curvatureRadius,
		 double bendAngle,
		double pressureDropGain);

double Pipe_R_getReynoldsNumber(Pipe_R* pipe);
double Pipe_R_getDragCoefficient(Pipe_R* pipe);


END_C_LINKAGE

#endif /* PIPE_R_H_ */
