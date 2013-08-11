/*
 * Convection.h
 *
 *  Created on: Aug 10, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#ifndef CONVECTION_H_
#define CONVECTION_H_

#include "util/CommonDefinitions.h"
#include "media/MediumState.h"
#include "volumes/ThermalNode.h"
#include "FlowBase.h"

#ifdef __cplusplus

class ConvectionModel {
public:
	virtual double getLengthScale() = 0;
	virtual double getHeatExchangeArea() = 0;
	virtual ~ConvectionModel();
};

class Convection {
public:
	Convection();
	virtual ~Convection();
	void init(MediumState* fluidState, ThermalNode* wallNode);
	double getPrandtlNumber() {return Pr;}
	double getNusseltNumber() {return Nu;}
	double getConvectionCoefficient() {return convectionCoefficient;}
	double getHeatFlowRate() {return heatFlowRate;}
	void getFlow_Wall(HeatFlow* flow);
	void getFlow_Fluid(FluidFlow* flow);
protected:
	// Parameters
	double lengthScale;
	double heatExchangeArea;

	MediumState* fluidState;
	ThermalNode* wallNode;
	MediumState* filmState;

	double Pr;
	double Nu;
	double convectionCoefficient;
	double heatFlowRate;
};

#else //__cplusplus
DECLARE_C_STRUCT(Convection)
#endif //__cplusplus


#endif /* CONVECTION_H_ */
