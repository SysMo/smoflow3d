/*
 * StateMachineController.h
 *
 *  Created on: Oct 24, 2013
 *      Author: Atanas Pavlov
 */

#ifndef STATEMACHINECONTROLLER_H_
#define STATEMACHINECONTROLLER_H_

#include "util/Common.h"
#include "util/Arrays.h"
#include "util/String.h"
#include "util/DynamicLoader.h"

typedef struct StateMachineControllerStruct StateMachineControllerStruct;

typedef void (*StateMachineController_dllNew)(StateMachineControllerStruct* self);
typedef void (*StateMachineController_libInit)(StateMachineControllerStruct* self, int initialControllerState);
typedef int (*StateMachineController_checkForTransition)(StateMachineControllerStruct* self);
typedef void (*StateMachineController_switchState)(StateMachineControllerStruct* self);
typedef void (*StateMachineController_setParameters)(StateMachineControllerStruct* self, double* realParameters, int* integerParameters);
typedef void (*StateMachineController_setInputs)(StateMachineControllerStruct* self, double* inputs);
typedef void (*StateMachineController_getOutputs)(StateMachineControllerStruct* self, double* outputs);

typedef struct StateMachineControllerStruct {
	SmoObject base;
	String* name;
	double time;
	PlatformFunctions* platform;

	int numInputs;
	int numOutputs;
	int numRealParameters;
	int numIntegerParameters;
	void *parameters;
	void *inputs;
	void *outputs;
	void *locals;

	DynamicLoader *loader;

	StateMachineController_dllNew new;
	StateMachineController_libInit init;
	StateMachineController_checkForTransition checkForTransition;
	StateMachineController_switchState switchState;
	StateMachineController_setParameters setParameters;
	StateMachineController_setInputs setInputs;
	StateMachineController_getOutputs getOutputs;

} StateMachineController;

StateMachineController* StateMachineController_new(
		const char* controllerName,
		const char* controllerPath,
		int numRealParameters,
		int numIntegerParameters,
		int numInputs,
		int numOutputs);
//void StateMachineController_init(StateMachineController* self, int initialControllerState);
void StateMachineController_free(StateMachineController** pSelf);

#endif /* STATEMACHINECONTROLLER_H_ */
