/*
 * TPipeJunction.h
 *
 *  Created on: Aug 30, 2019
 *      Author: Milen Borisov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#ifndef TPIPEJUNCTION_H_
#define TPIPEJUNCTION_H_

#include "flow/FlowBase.h"
#include "volumes/FluidChamber.h"

#ifdef __cplusplus

class TPipeJunction : public SmoComponent {
public:
	TPipeJunction(Medium *fluid, double internalVolume, double flowArea, int stateVariableSelection);
	virtual ~TPipeJunction();

	void initFluidStates(int initConditionsChoice, double initialPressure,
				double initialTemperature, double initialTemperatureC, double initialGasMassFraction);

	void setFluidFlow1(FluidFlow* port1Flow);
	void setFluidFlow2(FluidFlow* port2Flow);
	void setFluidFlow3(FluidFlow* port3Flow);

	void getStateValues(double* value1, double* value2);
	void setStateValues(double value1, double value2);
	void getStateDerivatives(double* value1, double* value2);

	MediumState* getFluidState1();
	MediumState* getFluidState2();
	MediumState* getFluidState3();

	double getPressureLoss2() {return dp2;}
	double getPressureLoss3() {return dp3;}

	double getFluidMass();

	void compute();
	virtual void updateFluidStates23() = 0;

protected:
	// Ports
	FluidFlow* port1Flow; // input
	FluidFlow* port2Flow; // input
	FluidFlow* port3Flow; // input

	// Internals
	FluidChamber* accFluid;
	MediumState* fluidState1;
	MediumState* fluidState2;
	MediumState* fluidState3;

	double dp2;
	double dp3;

	// Parameters
	double flowArea;

};



#else //__cplusplus
DECLARE_C_STRUCT(TPipeJunction)
#endif //__cplusplus

BEGIN_C_LINKAGE

TPipeJunction* TPipeJunction_ConstantDragCoefficients_new(
		Medium* fluid,
		double internalVolume,
		double flowArea,
		double dragCoeff2,
		double dragCoeff3,
		int stateVariableSelection);

void TPipeJunction_initFluidStates(
		TPipeJunction* component,
		int initConditionsChoice,
		double initialPressure,
		double initialTemperature,
		double initialTemperatureC,
		double initialGasMassFraction);

void TPipeJunction_setStateValues(TPipeJunction* component, double value1, double value2);
void TPipeJunction_getStateValues(TPipeJunction* component, double* value1, double* value2);
void TPipeJunction_getStateDerivatives(TPipeJunction* component, double* value1, double* value2);

void TPipeJunction_setFluidFlow1(TPipeJunction* component, FluidFlow* port1Flow);
void TPipeJunction_setFluidFlow2(TPipeJunction* component, FluidFlow* port2Flow);
void TPipeJunction_setFluidFlow3(TPipeJunction* component, FluidFlow* port3Flow);

MediumState* TPipeJunction_getFluidState1(TPipeJunction* component);
MediumState* TPipeJunction_getFluidState2(TPipeJunction* component);
MediumState* TPipeJunction_getFluidState3(TPipeJunction* component);

double TPipeJunction_getPressureLoss2(TPipeJunction* component);
double TPipeJunction_getPressureLoss3(TPipeJunction* component);

double TPipeJunction_getFluidMass(TPipeJunction* component);

void TPipeJunction_compute(TPipeJunction* component);
void TPipeJunction_updateFluidStates23(TPipeJunction* component);


END_C_LINKAGE

#endif /* TPIPEJUNCTION_H_ */
