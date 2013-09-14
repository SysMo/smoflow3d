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

typedef void (*SimEnv_MessageFunc)(const char* text);
typedef void (*SimEnv_WarningFunc)(const char* text);
typedef void (*SimEnv_ErrorFunc)(const char* text);
typedef void (*SimEnv_ExitFunc)();
typedef void (*SimEnv_UpdateEventIndicatorFunc)(int indicator);
typedef int (*SimEnv_IsEventModeFunc)();
typedef int (*SimEnv_IsFirstTimeStep)();
typedef void (*SimEnv_RegisterTimeEventFunc)(double t);

#ifdef __cplusplus

class SimulationEnvironment {
public:
	SimulationEnvironment();
	virtual ~SimulationEnvironment();
	bool present;
	double t;
	//SmoComponent* currentComponent;

	void message(const char* text);
	void message(const String text);
	void warning(const char* text);
	void warning(const String text);
	void error(const char* text);
	void error(const String text);
	void exit();

	void updateEventIndicator(bool indicator);
	bool isEventMode();
	bool isFirstTimeStep();
	void registerTimeEvent(double t);

	SimEnv_MessageFunc _message;
	SimEnv_WarningFunc _warning;
	SimEnv_ErrorFunc _error;
	SimEnv_ExitFunc _exit;
	SimEnv_UpdateEventIndicatorFunc _updateEventIndicator;
	SimEnv_IsEventModeFunc _isEventMode;
	SimEnv_RegisterTimeEventFunc _registerTimeEvent;
	SimEnv_IsFirstTimeStep _isFirstTimeStep;
};

extern SimulationEnvironment SimEnv;

#else // __cplusplus
DECLARE_C_STRUCT(SimulationEnvironment)
#endif //__cplusplus

BEGIN_C_LINKAGE
void SimulationEnvironment_registerSimEnvComponent();
void SimulationEnvironment_setTime(double t);
double SimulationEnvironment_getTime();
void SimulationEnvironment_message(const char* message);
void SimulationEnvironment_warning(const char* message);
void SimulationEnvironment_error(const char* message);
void SimulationEnvironment_exit();
const char* SimulationEnvironment_getComponentId(SmoComponent* component);

void SimulationEnvironment_setMessageFunc(SimEnv_MessageFunc func);
void SimulationEnvironment_setWarningFunc(SimEnv_WarningFunc func);
void SimulationEnvironment_setErrorFunc(SimEnv_ErrorFunc func);
void SimulationEnvironment_setExitFunc(SimEnv_ExitFunc func);
void SimulationEnvironment_setUpdateEventIndicatorFunc(SimEnv_UpdateEventIndicatorFunc func);
void SimulationEnvironment_setIsEventModeFunc(SimEnv_IsEventModeFunc func);
void SimulationEnvironment_setIsFirstTimeStepFunc(SimEnv_IsFirstTimeStep func);
void SimulationEnvironment_setRegisterTimeEventFunc(SimEnv_RegisterTimeEventFunc func);

END_C_LINKAGE
#endif /* SIMULATIONENVIRONMENT_H_ */
