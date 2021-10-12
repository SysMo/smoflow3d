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
#include "flow/ForcedConvection.h"

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

	MediumState* getFluidState1() {return fluidState1;}
	MediumState* getFluidState2() {return fluidState2;}
	MediumState* getFluidState3() {return fluidState3;}

	double getPressureLoss2() {return pressureLoss2;}
	double getPressureLoss3() {return pressureLoss3;}

	double getFluidMass();

	double getDragCoeff2() {return dragCoeff2;}
	double getDragCoeff3() {return dragCoeff3;}

	virtual void compute();
	virtual void updateFluidStates23(double mDotRatio21) = 0;
	virtual HeatFlow* getWallHeatFlow();
	virtual void setWallNode(ThermalNode* wallNode);
	virtual void initWallHeatFlow();

protected:

	void updateFluidStates23AtZeroMassFlow();

	// Ports
	FluidFlow* port1Flow; // input
	FluidFlow* port2Flow; // input
	FluidFlow* port3Flow; // input

	// Internals
	FluidChamber* accFluid;
	MediumState* fluidState1;
	MediumState* fluidState2;
	MediumState* fluidState3;

	double pressureLoss2;
	double pressureLoss3;

	double dragCoeff2;
	double dragCoeff3;

	// Parameters
	double flowArea;

};



#else //__cplusplus
DECLARE_C_STRUCT(TPipeJunction)
#endif //__cplusplus

BEGIN_C_LINKAGE

TPipeJunction* TPipeJunction_ConstantDragCoefficients_HeatExchanger_new(
			Medium *fluid,
			double internalVolume,
			double flowArea,
			double dragCoeff2,
			double dragCoeff3,
			ForcedConvection* convection,
			int stateVariableSelection);

TPipeJunction* TPipeJunction_ConstantDragCoefficients_new(
		Medium* fluid,
		double internalVolume,
		double flowArea,
		double dragCoeff2,
		double dragCoeff3,
		int stateVariableSelection);

TPipeJunction* TPipeJunction_RegulatingMassFlowRatio_new(
		Medium* fluid,
		double internalVolume,
		double flowArea,
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

double TPipeJunction_getDragCoeff2(TPipeJunction* component);
double TPipeJunction_getDragCoeff3(TPipeJunction* component);

void TPipeJunction_compute(TPipeJunction* component);
void TPipeJunction_updateFluidStates23(TPipeJunction* component, double mDotRatio21);

void TPipeJunction_HeatExchanger_setWallNode(TPipeJunction* component, ThermalNode* wallNode);
void TPipeJunction_HeatExchanger_initWallHeatFlow(TPipeJunction* component);
HeatFlow* TPipeJunction_HeatExchanger_getWallHeatFlow(TPipeJunction* component);

END_C_LINKAGE

#endif /* TPIPEJUNCTION_H_ */
