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

class FluidChamber : public SmoComponent {
public:
	FluidChamber(Medium *fluid);
	virtual ~FluidChamber();

	void selectStates(ThermodynamicVariable state1, ThermodynamicVariable state2);

	void setVolume(double volume) {this->volume = volume;}
	double getVolume() {return volume;}
	double getTotalVolume() {return totalVolume;}
	double getFluidMass() {return fluidState->rho() * volume;}
	double getTotalFluidMass() {return fluidState->rho() * getTotalVolume();}
	MediumState* getFluidState(){return fluidState;}

	void setStateValues(double stateValue1, double stateValue2);
	void getStateValues(double* stateValue1, double* stateValue2, bool getFromFluid);

	void compute(double massFlowRate, double enthalpyFlowRate, double heatFlowRate, double volume, double volumeDot);
	void getStateDerivatives(double* stateDerivative1, double* stateDerivative2);

protected:
	void computeStateDerivatives_cv(double mDot, double UDot, double VDot);
	void computeStateDerivatives_cp(double mDot, double UDot, double VDot);

	void handleEvent_FluidPhaseTransition();

protected:
	double volume;
	double totalVolume;

	static const int numStateVariables = 2;
	ThermodynamicVariable states[numStateVariables];
	double stateValues[numStateVariables];

	MediumState* fluidState;
	BasicState stateTimeDerivatives;

	bool flagInTwoPhase;
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

void FluidChamber_compute(FluidChamber* chamber, double massFlowRate, double enthalpyFlowRate, double heatFlowRate, double volume, double volumeDot);
void FluidChamber_getStateDerivatives(FluidChamber* chamber, double* stateDerivative1, double* stateDerivative2);

MediumState* FluidChamber_getFluidState(FluidChamber* chamber);
double FluidChamber_getVolume(FluidChamber* chamber);
double FluidChamber_getTotalVolume(FluidChamber* chamber);
double FluidChamber_getTotalFluidMass(FluidChamber* chamber);
END_C_LINKAGE

#endif /* FLUIDCHAMBER_H_ */
