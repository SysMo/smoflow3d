/*
 * FluidChamber.h
 *
 *  Created on: Jul 26, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#ifndef FLUIDCHAMBER_H_
#define FLUIDCHAMBER_H_

#include "util/CommonDefinitions.h"
#include "MediumState.h"

#ifdef __cplusplus

#include "CoolProp.h"

class FluidChamber {
public:
	FluidChamber(Medium *fluid);
	virtual ~FluidChamber();

	void seletcStates(params state1, params state2);
	inline void setVolume() {this->volume = volume;}
	void setStateValues(double stateValue1, double stateValue2);
	void getStateValues(double* stateValue1, double* stateValue2);
	void getStateDerivatives(double* stateDerivative1, double* stateDerivative2);
	MediumState* getFluidState();

	void computeStateDerivatives(double mDot, double UDot, double VDot);
protected:
	static const int numStateVariables = 2;
	params states[numStateVariables];
	double stateValues[numStateVariables];
	MediumState* fluidState;
	BasicState stateTimeDerivatives;
	double volume;
};

#else
DECLARE_C_STRUCT(FluidChamber)
#endif //__cplusplus

BEGIN_C_LINKAGE
FluidChamber* FluidChamber_new();
void FluidChamber_setVolume(double volume);
void FluidChamber_setStateValues(double stateValue1, double stateValue2);
void FluidChamber_computeStateDerivatives(double mDot, double UDot, double VDot);
void FluidChamber_getStateValues(double* stateValues);
void FluidChamber_getStateDerivatives(double* stateDerivatives);
END_C_LINKAGE

#endif /* FLUIDCHAMBER_H_ */
