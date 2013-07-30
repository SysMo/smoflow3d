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
#include "media/MediumState.h"

#ifdef __cplusplus

class FluidChamber {
public:
	FluidChamber(Medium *fluid);
	virtual ~FluidChamber();

	void selectStates(ThermodynamicVariable state1, ThermodynamicVariable state2);
	inline void setVolume(double volume) {this->volume = volume;}
	inline double getVolume() {return volume;}
	inline double getFluidMass() {return fluidMass;}
	void setStateValues(double stateValue1, double stateValue2);
	void getStateValues(double* stateValue1, double* stateValue2, bool getFromFluid);
	void computeStateDerivatives(double massFlowRate, double enthalpyFlowRate, double heatFlowRate, double volumeChangeRate);
	void getStateDerivatives(double* stateDerivative1, double* stateDerivative2);
	MediumState* getFluidState(){return fluidState;}
protected:
	void computeStateDerivatives_cv(double mDot, double UDot, double VDot);
	void computeStateDerivatives_cp(double mDot, double UDot, double VDot);

	static const int numStateVariables = 2;
	ThermodynamicVariable states[numStateVariables];
	double stateValues[numStateVariables];
	MediumState* fluidState;
	BasicState stateTimeDerivatives;
	double volume;
	double fluidMass;
};

#else
DECLARE_C_STRUCT(FluidChamber)
#endif //__cplusplus

BEGIN_C_LINKAGE
FluidChamber* FluidChamber_new(Medium *fluid);
void FluidChamber_selectStates(FluidChamber* chamber, ThermodynamicVariable state1, ThermodynamicVariable state2);
void FluidChamber_setVolume(FluidChamber* chamber, double volume);
double FluidChamber_getFluidMass(FluidChamber* chamber);
void FluidChamber_setStateValues(FluidChamber* chamber, double stateValue1, double stateValue2);
void FluidChamber_getStateValues(FluidChamber* chamber, double* stateValue1, double* stateValue2, int getFromFluid);
void FluidChamber_computeStateDerivatives(FluidChamber* chamber, double massFlowRate, double enthalpyFlowRate, double heatFlowRate, double volumeChangeRate);
void FluidChamber_getStateDerivatives(FluidChamber* chamber, double* stateDerivative1, double* stateDerivative2);
MediumState* FluidChamber_getFluidState(FluidChamber* chamber);
END_C_LINKAGE

#endif /* FLUIDCHAMBER_H_ */
