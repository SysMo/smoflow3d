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
#include "flow/FlowBase.h"

#ifdef __cplusplus

class Convection : public SmoComponent {
public:
	Convection();
	virtual ~Convection();

	void init(MediumState* fluidState, ThermalNode* wallNode);

	void setHeatExchangeGain(double gain) {this->heatExchangeGain = gain;}

	double getCharacteristicLength(){return characteristicLength;}
	double getHeatExchangeArea(){return heatExchangeArea;}
	double getPrandtlNumber() {return Pr;}
	double getNusseltNumber() {return Nu;}

	void setConvectionCoefficient(double convectionCoeff) {convectionCoefficient = convectionCoeff;}
	double getConvectionCoefficient() {return convectionCoefficient;}

	double getHeatFlowRate() {return heatFlowRate;} //:TRICKY: heat flow rate from the wall to the fluid

	void updateHeatFlow(HeatFlow* flow); //heat flow to the wall
	void updateFluidFlow(FluidFlow* flow); //fluid flow to the fluid

	void setUseFilmState(bool useFilmState) {this->useFilmState = useFilmState;}

protected:
	double characteristicLength;
	double heatExchangeArea;
	double heatExchangeGain;

	MediumState* fluidState;
	ThermalNode* wallNode;
	MediumState* filmState;
	bool useFilmState;

	double Pr;
	double Nu;
	double convectionCoefficient;
	double heatFlowRate;
};

#else //__cplusplus
DECLARE_C_STRUCT(Convection)
#endif //__cplusplus

BEGIN_C_LINKAGE
void Convection_setHeatExchangeGain(Convection* convection, double gain);

double Convection_getPrandtlNumber(Convection* convection);
double Convection_getNusseltNumber(Convection* convection);

void Convection_setConvectionCoefficient(Convection* convection, double convectionCoefficient);
double Convection_getConvectionCoefficient(Convection* convection);

double Convection_getHeatFlowRate(Convection* convection);

void Convection_updateHeatFlow(Convection* convection, HeatFlow* flow);
void Convection_updateFluidFlow(Convection* convection, FluidFlow* flow);

void Convection_setUseFilmState(Convection* convection, int useFilmState);
END_C_LINKAGE

#endif /* CONVECTION_H_ */
