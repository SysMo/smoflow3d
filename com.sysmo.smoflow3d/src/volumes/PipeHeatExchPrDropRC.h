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
	PipeHeatExchPrDrop_RC(
			double hydraulicDiameter, double flowArea,
			double length, double surfaceRoughness);
	virtual ~PipeHeatExchPrDrop_RC();
	virtual void compute();
protected:
	virtual void _init();
	virtual void _createState();
	double hydraulicDiameter;
	double flowArea;
	double length;
	double surfaceRoughness;
	double volume;
	FluidChamber* accFluid;

	ForcedConvection* convection;
	FrictionFlowPipe* friction;
};

#else //__cplusplus
DECLARE_C_STRUCT(PipeHeatExchPrDrop_RC)
#endif //__cplusplus

BEGIN_C_LINKAGE

END_C_LINKAGE

#endif /* PIPEHEATEXCHPRDROPRC_H_ */
