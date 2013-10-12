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

	virtual void getStateValues(double* value1, double* value2);
	virtual void setStateValues(double value1, double value2);
	virtual void getStateDerivatives(double* value1, double* value2);
	virtual void compute();

protected:
	virtual void _init();
	virtual void _initStates();

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
END_C_LINKAGE

#endif /* PIPEHEATEXCHPRDROPRC_H_ */
