/*
 * PhaseSeparator.h
 *
 *  Created on: Aug 28, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#ifndef PHASESEPARATOR_H_
#define PHASESEPARATOR_H_

#include "media/MediumState.h"
#include "flow/FlowBase.h"

class PhaseSeparator {
public:
	enum PhaseSelection {
		overall,
		liquid,
		gas,
		signalSelect_Discrete,
		signalSelect_Continuous
	};
public:
	PhaseSeparator();
	virtual ~PhaseSeparator();
	void init(MediumState* port1State, FluidFlow* fluidFlow);
	MediumState* getPort2State() {return port2State;}
	void updateState(double regulatingSignal);
protected:
	PhaseSelection phaseSelection;
	PhaseSelection currentPhase;
	MediumState* port1State;
	MediumState* port2State;
	FluidFlow* fluidFlow;


};

#endif /* PHASESEPARATOR_H_ */
