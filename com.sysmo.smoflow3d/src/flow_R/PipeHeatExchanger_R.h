/*
 * PipeHeatExchanger_R.h
 *
 *  Created on: Sep 19, 2014
 *      Author: Milen Borisov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#ifndef PIPEHEATEXCHANGER_R_H_
#define PIPEHEATEXCHANGER_R_H_

#include "media/MediumState.h"
#include "flow/ForcedConvection.h"
#include "volumes/ThermalNode.h"
#include "flow_R/Pipe_R.h"

#ifdef __cplusplus

class PipeHeatExchanger_R : public Pipe_R {
public:
	PipeHeatExchanger_R(FrictionFlowPipe* friction, ForcedConvection* convection = NULL);
	virtual ~PipeHeatExchanger_R();

	virtual void init(MediumState* state1);
	virtual bool compute(double massFlowRate, double minDownstreamPressure);
	virtual void compute_NoMassFlowRate();

	void setHeatExchangerThermalNode(ThermalNode* wallNode) {this->wallNode = wallNode;}

	HeatFlow* getWallHeatFlow() {return wallHeatFlow;}
	ForcedConvection* getConvection() {return convection;}

protected:
	ForcedConvection* convection;
	MediumState* limitStateT;

	ThermalNode* wallNode;
	HeatFlow* wallHeatFlow;
};

#else //_cplusplus
DECLARE_C_STRUCT(PipeHeatExchanger_R)
#endif //_cplusplus


BEGIN_C_LINKAGE
PipeHeatExchanger_R* PipeHeatExhcanger_R_new(
		FrictionFlowPipe* friction,
		ForcedConvection* convection);

PipeHeatExchanger_R* StraightPipeHeatExchanger_R_new(
		double length,
		double hydraulicDiameter,
		double flowArea,
		double surfaceRoughness,
		double pressureDropGain,
		double heatExchangeGain,
		int forcedConvectionLimitOutput,
		int forcedConvectionUseFilmState,
		int useDragCoeffGain,
		const char* dragCoeffGainExpression);

HeatFlow* PipeHeatExchanger_R_getWallHeatFlow(PipeHeatExchanger_R* pipe);
ForcedConvection* PipeHeatExchanger_R_getConvection(PipeHeatExchanger_R* pipe);
void PipeHeatExchanger_R_setHeatExchangerThermalNode(PipeHeatExchanger_R* pipe, ThermalNode* wallNode);
END_C_LINKAGE

#endif /* PIPEHEATEXCHANGER_R_H_ */
