/*
 * StateMachineController.h
 *
 *  Created on: Aug 8, 2014
 *      Author: nasko
 */

#ifndef STATEMACHINECONTROLLER_H_
#define STATEMACHINECONTROLLER_H_

#include "util/CommonDefinitions.h"

#ifdef __cplusplus

class StateMachineController : public SmoComponent {
public:
	StateMachineController();
	virtual ~StateMachineController();

	void loadController(const char* controllerPath);
	void init(int numRealParameters, int numIntegerParameters,
			int numInputs, int numOutputs);

	void setParameters(double realParameterValues[],
		int integerParameterValues[]);
	void setInputs(double inputValues[]);
	void getOutputs(double outputValues[]);

	void enter();
	void step();
protected:
	typedef void* (*CreateControllerFunc)(SimulationEnvironment* simEnv);
	typedef void (*GetSizesFunc)(void* controller,
				int* numRealParameters, int* numIntegerParameters,
				int* numInputs, int* numOutputs);
	typedef void (*InitFunc)(void* controller);

	typedef void (*SetParametersFunc)(void* controller,
			double realParameterValues[],
			int integerParameterValues[]);
	typedef void (*SetInputsFunc)(void* controller, double inputValues[]);
	typedef void (*GetOutputsFunc)(void* controller, double outputValues[]);

	typedef void (*EnterFunc)(void* controller);
	typedef bool (*ActionRequestedFunc)(void* controller);
	typedef void (*ReactFunc)(void* controller);
protected:
	void* controller;

	GetSizesFunc _getSizes;

	SetParametersFunc _setParameters;
	SetInputsFunc _setInputs;
	GetOutputsFunc _getOutputs;

	InitFunc _init;
	EnterFunc _enter;
	ActionRequestedFunc _isActionRequested;
	ReactFunc _react;
};

#else // __cplusplus
DECLARE_C_STRUCT(StateMachineController)
#endif //__cplusplus

BEGIN_C_LINKAGE

StateMachineController* StateMachineController_new();

void StateMachineController_loadController(StateMachineController* component, const char* controllerPath);
void StateMachineController_init(StateMachineController* component,
		int numRealParameters, int numIntegerParameters,
		int numInputs, int numOutputs);

void StateMachineController_setParameters(StateMachineController* component,
		double realParameterValues[],
		int integerParameterValues[]);
void StateMachineController_setInputs(StateMachineController* component, double inputValues[]);
void StateMachineController_getOutputs(StateMachineController* component, double outputValues[]);

void StateMachineController_enter(StateMachineController* component);
void StateMachineController_step(StateMachineController* component);

END_C_LINKAGE

#endif /* STATEMACHINECONTROLLER_H_ */
