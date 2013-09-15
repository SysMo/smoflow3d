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

#ifdef __cplusplus

class PhaseSeparator {
public:
	PhaseSeparator(PhaseSelection phaseSelection);
	virtual ~PhaseSeparator();

	void init(MediumState* port1State);

	MediumState* getPort2State() {return port2State;}
	void updateState(double regulatingSignal);

protected:
	PhaseSelection phaseSelection;
	MediumState* port1State;
	MediumState* port2State;
};

#else // __cplusplus
DECLARE_C_STRUCT(PhaseSeparator)
#endif //__cplusplus

BEGIN_C_LINKAGE
PhaseSeparator* PhaseSeparator_new(PhaseSelection phaseSelection);
void PhaseSeparator_init(PhaseSeparator* component,	MediumState* port1State);
MediumState* PhaseSeparator_getPort2State(PhaseSeparator* component);
void PhaseSeparator_updateState(PhaseSeparator* component, double regulatingSignal);
END_C_LINKAGE

#endif /* PHASESEPARATOR_H_ */
