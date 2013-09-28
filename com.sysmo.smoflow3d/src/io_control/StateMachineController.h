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

// TOOD: getSizes, setTime, getState

class StateMachineController : public SmoComponent {
public:
	StateMachineController();
	virtual ~StateMachineController();

	void loadController(const char* controllerPath);
	void init();

	void checkSizes(int numRealParameters, int numIntegerParameters,
			int numInputs, int numOutputs, int maxNumOrthogonalStates);

	void setParameters(double realParameterValues[],
		int integerParameterValues[]);
	void setInputs(double inputValues[]);
	void setTime(double t);
	void getOutputs(double outputValues[]);
	void getState(int stateVector[]);
	void getState(double stateVector[]);

	void enter();
	void step();

	int getNumRealParameters() {
		return numRealParameters;
	}
	int getNumIntegerParameters() {
		return numIntegerParameters;
	}
	int getNumInputs() {
		return numInputs;
	}
	int getNumOutputs() {
		return numOutputs;
	}
	int getMaxNumOrthogonalStates() {
		return maxNumOrthogonalStates;
	}
protected:
	double t;
	double timeLastEvent;

	int numRealParameters;
	int numIntegerParameters;
	int numInputs;
	int numOutputs;
	int maxNumOrthogonalStates;


	typedef void* (*CreateControllerFunc)(SimEnv_MessageFunc messageFunc, SimEnv_ErrorFunc errorFunc);
	typedef void (*GetSizesFunc)(void* controller,
				int* numRealParameters, int* numIntegerParameters,
				int* numInputs, int* numOutputs, int* maxNumOrthogonalStates);
	typedef void (*InitFunc)(void* controller);

	typedef void (*SetParametersFunc)(void* controller,
			double realParameterValues[],
			int integerParameterValues[]);
	typedef void (*SetInputsFunc)(void* controller, double inputValues[]);
	typedef void (*SetTimeFunc)(void* controller, double setTime);
	typedef void (*GetOutputsFunc)(void* controller, double outputValues[]);
	typedef void (*GetStateFunc)(void* controller, int stateVector[]);

	typedef void (*EnterFunc)(void* controller);
	typedef bool (*ActionRequestedFunc)(void* controller);
	typedef void (*ReactFunc)(void* controller);
protected:
	void* controller;

	GetSizesFunc _getSizes;

	SetParametersFunc _setParameters;
	SetInputsFunc _setInputs;
	SetTimeFunc _setTime;
	GetOutputsFunc _getOutputs;
	GetStateFunc _getState;

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
void StateMachineController_init(StateMachineController* component);
void StateMachineController_checkSizes(StateMachineController* component,
		int numRealParameters, int numIntegerParameters,
		int numInputs, int numOutputs, int maxNumOrthogonalStates);

void StateMachineController_setParameters(StateMachineController* component,
		double realParameterValues[],
		int integerParameterValues[]);
void StateMachineController_setInputs(StateMachineController* component, double inputValues[]);
void StateMachineController_setTime(StateMachineController* component, double t);
void StateMachineController_getOutputs(StateMachineController* component, double outputValues[]);
void StateMachineController_getState(StateMachineController* component, int stateVector[]);
void StateMachineController_getState_ToDouble(StateMachineController* component, double stateVector[]);

void StateMachineController_enter(StateMachineController* component);
void StateMachineController_step(StateMachineController* component);

END_C_LINKAGE

#endif /* STATEMACHINECONTROLLER_H_ */
