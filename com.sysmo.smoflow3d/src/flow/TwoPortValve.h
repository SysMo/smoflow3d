/*
 * TwoPortValve.h
 *
 *  Created on: Jul 28, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#ifndef TWOPORTVALVE_H_
#define TWOPORTVALVE_H_

#include "media/MediumState.h"


BEGIN_C_LINKAGE
typedef struct {
	MediumState* state1;
	MediumState* state2;
	double pressureDrop;
	double massFlowRate;
	double enthalpyFlowRate;
	int allowBidirectionalFlow;

	double maximumMassFlowRate;
	double transitionPressureDifference;
	double transitionMassFlowRate;
	double Kv;
	int transitionChoice;
	int flowDirection;
} TwoPortValve; //TODO (Milen) Rename: TwoPortValve to BidirectionalValve


TwoPortValve* TwoPortValve_new();
void TwoPortValve_init(TwoPortValve* valve, MediumState* state1, MediumState* state2);
void TwoPortValve_computeMassFlow_Kv(TwoPortValve* valve, double regulatingSignal);
void TwoPortValve_computeEnthalpyFlow(TwoPortValve* valve);
END_C_LINKAGE


#endif /* TWOPORTVALVE_H_ */
