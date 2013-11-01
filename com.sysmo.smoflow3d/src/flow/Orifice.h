/*
 * Orifice.h
 *
 *  Created on: Aug 3, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#ifndef ORIFICE_H_
#define ORIFICE_H_

#include "media/MediumState.h"
#include "FlowBase.h"
#include "FlowComponent_R_2Port.h"

typedef enum {
	sFlowType_Undefine = -1,
	sFlowType_Subsonic = 0,
	sFlowType_Sonic = 1
} FlowType;


#ifdef __cplusplus

class Orifice : public FlowComponent_R_2Port {
public:
	Orifice();
	virtual ~Orifice();

	void setOrificeArea(double orificeArea) {this->orificeArea = orificeArea;}
	void setFlowCoefficient(double flowCoefficient) {this->flowCoefficient = flowCoefficient;}

	void setRegulatingSignal(double regulatingSignal) {this->regulatingSignal = regulatingSignal;}

	double getMassFlowRate() {return massFlowRate;}
	double getEnthalpyFlowRate() {return enthalpyFlowRate;}
	double getPressureLoss() {return pressureLoss;}
	FlowType getFlowType() {return flowType;}

	void updateFluidFlows(FluidFlow* flow1, FluidFlow* flow2);

protected:
	/* Parameters */
	double orificeArea;
	double flowCoefficient;

	/* Inputs */
	double regulatingSignal;

	/* Results */
	double massFlowRate;
	double enthalpyFlowRate;
	double pressureLoss;
	FlowType flowType;
};

#else //_cplusplus
DECLARE_C_STRUCT(Orifice)
#endif //_cplusplus


BEGIN_C_LINKAGE
Orifice* Orifice_CompressibleIdealGas_new();

void Orifice_init(Orifice* orifice, MediumState* state1, MediumState* state2);
void Orifice_compute(Orifice* orifice);

void Orifice_setOrificeArea(Orifice* orifice, double orificeArea);
void Orifice_setFlowCoefficient(Orifice* orifice, double flowCoefficient);

void Orifice_setRegulatingSignal(Orifice* orifice, double regulatingSignal);

double Orifice_getMassFlowRate(Orifice* orifice);
double Orifice_getEnthalpyFlowRate(Orifice* orifice);
double Orifice_getPressureLoss(Orifice* orifice);
int Orifice_getFlowType(Orifice* orifice);

void Orifice_updateFluidFlows(Orifice* orifice, FluidFlow* flow1, FluidFlow* flow2);
END_C_LINKAGE

#endif /* ORIFICE_H_ */
