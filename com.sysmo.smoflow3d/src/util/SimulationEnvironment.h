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
	void (*message)(const char* message);
	void (*warning)(const char* message);
	void (*error)(const char* message);
	void (*exit)();
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
void SimulationEnvironment_message(const char* message);
void SimulationEnvironment_warning(const char* message);
void SimulationEnvironment_error(const char* message);
void SimulationEnvironment_exit();
const char* SimulationEnvironment_getComponentId(SmoComponent* component);
//std::stringstream SimulationEnvironment_StreamEvent(SmoComponent* component, const char* file,
//		const char* function, const char* line);
END_C_LINKAGE
#endif /* SIMULATIONENVIRONMENT_H_ */
