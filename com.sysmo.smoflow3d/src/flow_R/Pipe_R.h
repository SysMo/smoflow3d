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
#include "flow/ForcedConvection.h"
#include "volumes/ThermalNode.h"
#include "flow_R/FlowComponent_R.h"


#ifdef __cplusplus

class Pipe_R : public FlowComponent_R {
public:
	Pipe_R(FrictionFlowPipe* friction, ForcedConvection* convection = NULL);
	virtual ~Pipe_R();

	virtual void init(MediumState* state1);
	virtual bool compute(double massFlowRate, double minDownstreamPressure);

	bool hasHeatExhcanger();
	void setHeatExchangerThermalNode(ThermalNode* wallNode) {this->wallNode = wallNode;}

protected:
	FrictionFlowPipe* friction;
	ForcedConvection* convection;
	ThermalNode* wallNode;
};

#else //_cplusplus
DECLARE_C_STRUCT(Pipe_R)
#endif //_cplusplus


BEGIN_C_LINKAGE
Pipe_R* Pipe_R_new(FrictionFlowPipe* friction);
Pipe_R* PipeHeatExhcanger_R_new(FrictionFlowPipe* friction, ForcedConvection* convection);

Pipe_R* CylindricalStraightPipe_R_new(
		double diameter,
		double length,
		double surfaceRoughness,
		double pressureDropGain);

Pipe_R* CylindricalStraightPipeHeatExchanger_R_new(
		double diameter,
		double length,
		double surfaceRoughness,
		double pressureDropGain,
		double heatExchangeGain,
		int heatExchangerLimitOutput);

Pipe_R* NonCylindricalStraightPipeHeatExchanger_R_new(
		double hydraulicDiameter,
		double length,
		double flowArea,
		double surfaceRoughness,
		double pressureDropGain,
		double heatExchangeGain,
		int heatExchangerLimitOutput);
END_C_LINKAGE


#endif /* PIPE_R_H_ */
