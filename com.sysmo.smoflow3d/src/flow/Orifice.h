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
	double getPressureDrop() {return pressureDrop;}
	int getSonicFlow() {return sonicFlow;}

	void compute_CompressibleIdealGas();

	void getInletFlowRates(FluidFlow* inletFlow);
	void getOutletFlowRates(FluidFlow* outletFlow);

protected:
	/* Parameters */
	double orificeArea;
	double flowCoefficient;

	/* Inputs */
	double regulatingSignal;

	/* Results */
	double massFlowRate;
	double enthalpyFlowRate;
	double pressureDrop;

	/* Intermediate variables */
	int sonicFlow;
};

#else //_cplusplus
DECLARE_C_STRUCT(Orifice)
#endif //_cplusplus


BEGIN_C_LINKAGE
Orifice* Orifice_new();
void Orifice_init(Orifice* orifice, MediumState* state1, MediumState* state2);
void Orifice_compute_CompressibleIdealGas(Orifice* orifice);

void Orifice_setOrificeArea(Orifice* orifice, double orificeArea);
void Orifice_setFlowCoefficient(Orifice* orifice, double flowCoefficient);
void Orifice_setRegulatingSignal(Orifice* orifice, double regulatingSignal);
double Orifice_getMassFlowRate(Orifice* orifice);
double Orifice_getEnthalpyFlowRate(Orifice* orifice);
double Orifice_getPressureDrop(Orifice* orifice);
int Orifice_getSonicFlow(Orifice* orifice);
void Orifice_getInletFlowRates(Orifice* orifice, FluidFlow* inletFlow);
void Orifice_getOutletFlowRates(Orifice* orifice, FluidFlow* outletFlow);
END_C_LINKAGE

#endif /* ORIFICE_H_ */
