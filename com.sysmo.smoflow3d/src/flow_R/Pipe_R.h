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
	Pipe_R(FrictionFlowPipe* friction);
	virtual ~Pipe_R();

	virtual void init(MediumState* state1);
	virtual bool compute(double massFlowRate, double minDownstreamPressure);

protected:
	FrictionFlowPipe* friction;
};

class PipeHeatExchanger_R : public Pipe_R {
public:
	PipeHeatExchanger_R(FrictionFlowPipe* friction, ForcedConvection* convection = NULL);
	virtual ~PipeHeatExchanger_R();

	virtual void init(MediumState* state1);
	virtual bool compute(double massFlowRate, double minDownstreamPressure);

	void setHeatExchangerThermalNode(ThermalNode* wallNode) {this->wallNode = wallNode;}

	HeatFlow* getWallHeatFlow() {return wallHeatFlow;}
	ForcedConvection* getConvection() {return convection;}

protected:
	ForcedConvection* convection;
	ThermalNode* wallNode;
	HeatFlow* wallHeatFlow;
};

#else //_cplusplus
DECLARE_C_STRUCT(Pipe_R)
DECLARE_C_STRUCT(PipeHeatExchanger_R)
#endif //_cplusplus


BEGIN_C_LINKAGE
Pipe_R* Pipe_R_new(FrictionFlowPipe* friction);

Pipe_R* CylindricalStraightPipe_R_new(
		double diameter,
		double length,
		double surfaceRoughness,
		double pressureDropGain);


PipeHeatExchanger_R* PipeHeatExhcanger_R_new(
		FrictionFlowPipe* friction,
		ForcedConvection* convection);

PipeHeatExchanger_R* CylindricalStraightPipeHeatExchanger_R_new(
		double diameter,
		double length,
		double surfaceRoughness,
		double pressureDropGain,
		double heatExchangeGain,
		int heatExchangerLimitOutput);

PipeHeatExchanger_R* NonCylindricalStraightPipeHeatExchanger_R_new(
		double hydraulicDiameter,
		double length,
		double flowArea,
		double surfaceRoughness,
		double pressureDropGain,
		double heatExchangeGain,
		int heatExchangerLimitOutput);

HeatFlow* PipeHeatExchanger_R_getWallHeatFlow(PipeHeatExchanger_R* pipe);
ForcedConvection* PipeHeatExchanger_R_getConvection(PipeHeatExchanger_R* pipe);
void PipeHeatExchanger_R_setHeatExchangerThermalNode(PipeHeatExchanger_R* pipe, ThermalNode* wallNode);
END_C_LINKAGE

#endif /* PIPE_R_H_ */
