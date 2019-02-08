/*
 * Valve.h
 *
 *  Created on: Jul 28, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#ifndef VALVE_H_
#define VALVE_H_

#include "media/MediumState.h"
#include "flow/FlowBase.h"
#include "flow/FrictionFlowValve.h"


#ifdef __cplusplus

class Valve : public SmoComponent {
public:
	Valve(FrictionFlowValve* friction);
	virtual ~Valve();

	void init(MediumState* state1, MediumState* state2);
	void compute();

	void setRegulatingSignal(double regulatingSignal) {friction->setRegulatingSignal(regulatingSignal);}

	void updateFluidFlows(FluidFlow* flow1, FluidFlow* flow2) {friction->updateFluidFlows(flow1, flow2);}
	double getAbsolutePressureDrop() {return friction->getAbsolutePressureDrop();}
	FlowType getFlowType() {return friction->getFlowType();}

	bool isFlowClosed();

	void setPressureDifferenceParameters(bool useOpeningClosePressDiff, double openingPressDiff, double closingPressDiff);
	void handleEvent_OpeningClosingPressureDifferenceIsCrossed();

protected:
	FrictionFlowValve* friction;

	MediumState* state1;
	MediumState* state2;

private:
	// Opening/closing pressure difference
	bool useOpeningClosePressDiff;
	double openingPressDiff;
	double closingPressDiff;

	bool isFlowClosed_byPressDiff;

	bool isClosingPressDiffCrossed;
	bool discFlag_isClosingPressDiffCrossed;
	bool discFlag_isClosingPressDiffCrossed_isInit;

	bool isOpeningPressDiffCrossed;
	bool discFlag_isOpeningPressDiffCrossed;
	bool discFlag_isOpeningPressDiffCrossed_isInit;
};

#else //_cplusplus
DECLARE_C_STRUCT(Valve)
#endif //_cplusplus


BEGIN_C_LINKAGE
Valve* Valve_InputMassFlowRate_new(
		int allowBidirectionalFlow,
		int useAsPump);

Valve* Valve_Kv_new(
		int allowBidirectionalFlow,
		double Kv,
		int transitionChoice,
		double transitionMassFlowRate,
		double transitionPressureDifference,
		double maximumMassFlowRate,
		int limitRegulatingSignal);

Valve* Valve_OrificeCompressibleIdealGas_new(
		int allowBidirectionalFlow,
		double orificeArea,
		double flowCoefficient);

Valve* Valve_OrificeCompressibleRealGas_new(
		int allowBidirectionalFlow,
		double orificeArea,
		double flowCoefficient);

void Valve_init(Valve* valve, MediumState* state1, MediumState* state2);
void Valve_compute(Valve* valve);

void Valve_setRegulatingSignal(Valve* valve, double regulatingSignal);

void Valve_updateFluidFlows(Valve* valve, FluidFlow* flow1, FluidFlow* flow2);

double Valve_getAbsolutePressureDrop(Valve* valve);
int Valve_getFlowType(Valve* valve);
int Valve_getIsFlowClosed(Valve* valve);

void Valve_setPressureDifferenceParameters(Valve* valve, int useOpeningClosePressDiff, double openingPressDiff, double closingPressDiff);
END_C_LINKAGE


#endif /* VALVE_H_ */
