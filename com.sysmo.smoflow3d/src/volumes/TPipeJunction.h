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
	TPipeJunction(Medium *fluid, double internalVolume, int stateVariableSelection);
	virtual ~TPipeJunction();

	void initFlows(FluidFlow* port1Flow, FluidFlow* port2Flow, FluidFlow* port3Flow);

	void getStateValues(double* value1, double* value2);
	void setStateValues(double value1, double value2);
	void getStateDerivatives(double* value1, double* value2);

	MediumState* getFluidState1();

	double getFluidMass();

	void compute();

protected:
	//void compute(double pressureDrop);

protected:
	// Ports
	FluidFlow* port1Flow; // input
	FluidFlow* port2Flow; // input
	FluidFlow* port3Flow; // input

	// Internals
	FluidChamber* accFluid;
};

#else //__cplusplus
DECLARE_C_STRUCT(TPipeJunction)
#endif //__cplusplus

BEGIN_C_LINKAGE

TPipeJunction* TPipeJunction_new(Medium* fluid, double internalVolume, int stateVariableSelection);
void TPipeJunction_initFlows(TPipeJunction* component, FluidFlow* port1Flow, FluidFlow* port2Flow, FluidFlow* port3Flow);

void TPipeJunction_setStateValues(TPipeJunction* component, double value1, double value2);
void TPipeJunction_getStateValues(TPipeJunction* component, double* value1, double* value2);
void TPipeJunction_getStateDerivatives(TPipeJunction* component, double* value1, double* value2);
MediumState* TPipeJunction_getFluidState1(TPipeJunction* component);

double TPipeJunction_getFluidMass(TPipeJunction* component);

void TPipeJunction_compute(TPipeJunction* component);

END_C_LINKAGE

#endif /* TPIPEJUNCTION_H_ */
