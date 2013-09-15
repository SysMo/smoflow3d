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

BEGIN_C_LINKAGE
typedef struct {
	MediumState* stateUp;
	MediumState* stateDown;
	double pressureDrop;
	double massFlowRate;
	double enthalpyFlowRate;

	double orificeArea;
	double flowCoefficient;
	int sonicFlow;
} Orifice;

Orifice* Orifice_new();
void Orifice_init(Orifice* orifice, MediumState* stateUp, MediumState* stateDown);
void Orifice_computeMassFlow_CompressibleIdealGas(Orifice* orifice, double regulatingSignal);
void Orifice_computeEnthalpyFlow(Orifice* orifice);
END_C_LINKAGE

#endif /* ORIFICE_H_ */
