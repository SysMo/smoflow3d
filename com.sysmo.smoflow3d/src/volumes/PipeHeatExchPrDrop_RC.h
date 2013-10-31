/*
 * PipeHeatExchPrDropRC.h
 *
 *  Created on: Aug 23, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#ifndef PIPEHEATEXCHPRDROPRC_H_
#define PIPEHEATEXCHPRDROPRC_H_

#include "Component_RC.h"

#ifdef __cplusplus

class PipeHeatExchPrDrop_RC : public Component_RC {
public:
	PipeHeatExchPrDrop_RC(double internalVolume, FrictionFlowPipe* friction, ForcedConvection* convection);
	virtual ~PipeHeatExchPrDrop_RC();

	virtual void init(FluidFlow* port2Flow);
	virtual void initStates(MediumState* port1State,
			ThermalNode* wallNode, StateVariableSet& innerStateInitializer);

	virtual void compute();

	void setStateValues(double value1, double value2);
	void getStateValues(double* value1, double* value2);
	void getStateDerivatives(double* value1, double* value2);

protected:
	// Parameters
	double volume;
	ForcedConvection* convection;
	FrictionFlowPipe* friction;

	// Internals
	FluidChamber* accFluid;
	FluidFlow* internalFlow;
};

#else //__cplusplus
DECLARE_C_STRUCT(PipeHeatExchPrDrop_RC)
#endif //__cplusplus

BEGIN_C_LINKAGE
PipeHeatExchPrDrop_RC* PipeHeatExchPrDrop_RC_new(double internalVolume, FrictionFlowPipe* friction, ForcedConvection* convection);

void PipeHeatExchPrDrop_RC_setStateValues(PipeHeatExchPrDrop_RC* pipe, double value1, double value2);
void PipeHeatExchPrDrop_RC_getStateValues(PipeHeatExchPrDrop_RC* pipe, double* value1, double* value2);
void PipeHeatExchPrDrop_RC_getStateDerivatives(PipeHeatExchPrDrop_RC* pipe, double* value1, double* value2);

END_C_LINKAGE

#endif /* PIPEHEATEXCHPRDROPRC_H_ */
