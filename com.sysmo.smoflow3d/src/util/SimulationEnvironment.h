/*
 * SimulationEnvironment.h
 *
 *  Created on: Aug 25, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#ifndef SIMULATIONENVIRONMENT_H_
#define SIMULATIONENVIRONMENT_H_

#include "CommonDefinitions.h"

#ifdef __cplusplus

class SimulationEnvironment {
public:
	SimulationEnvironment();
	virtual ~SimulationEnvironment();
	bool present;
	double t;
	SmoComponent* currentComponent;
};

#else // __cplusplus
DECLARE_C_STRUCT(SimulationEnvironment)
#endif //__cplusplus

BEGIN_C_LINKAGE
void SimulationEnvironment_registerSimEnvComponent();
void SimulationEnvironment_setTime(double t);
double SimulationEnvironment_getTime();
void SimulationEnvironment_setCurrentComponent(SmoComponent* component);
SmoComponent* SimulationEnvironment_getCurrentComponent();
END_C_LINKAGE
#endif /* SIMULATIONENVIRONMENT_H_ */
