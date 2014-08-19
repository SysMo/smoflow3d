/*
 * StateMachineController.cpp
 *
 *  Created on: Aug 8, 2014
 *      Author: nasko
 */

#include "StateMachineController.h"
#include "util/DynamicLoader.h"

StateMachineController::StateMachineController() {
}

StateMachineController::~StateMachineController() {
}

void StateMachineController::loadController(const char* controllerPath) {
	DynamicLoader* loader = new DynamicLoader();
	loader->load(controllerPath);
	CreateControllerFunc createController = (CreateControllerFunc) loader->getMethodAddress("createController");
	controller = createController(&SimEnv);

	if (controller != NULL) {
		ShowMessage("Succesfully created controller instance from " << controllerPath);
	} else {
		RaiseComponentError(this, "Couldn't create controller instance from " << controllerPath);
	}
	_getSizes = (GetSizesFunc) loader->getMethodAddress("getSizes");

	_setParameters = (SetParametersFunc) loader->getMethodAddress("setParameters");
	_setInputs = (SetInputsFunc) loader->getMethodAddress("setInputs");
	_getOutputs = (GetOutputsFunc) loader->getMethodAddress("getOutputs");

	_init = (InitFunc) loader->getMethodAddress("init");
	_enter = (EnterFunc) loader->getMethodAddress("enter");
	_isActionRequested= (ActionRequestedFunc) loader->getMethodAddress("isActionRequested");
	_react  = (ReactFunc) loader->getMethodAddress("react");

	delete loader;
}

void StateMachineController::init(int numRealParameters, int numIntegerParameters,
		int numInputs, int numOutputs) {
	int dll_numRealParameters;
	int dll_numIntegerParameters;
	int dll_numInputs;
	int dll_numOutputs;

	_getSizes(controller, &dll_numRealParameters, &dll_numIntegerParameters,
			&dll_numInputs, &dll_numOutputs);

	if (numRealParameters != dll_numRealParameters) {
		RaiseComponentError(this, "Controller loaded from dll expects " << dll_numRealParameters
				<< " real parameters, simulation component has " << numRealParameters)
	}

	if (numIntegerParameters != dll_numIntegerParameters) {
		RaiseComponentError(this, "Controller loaded from dll expects " << dll_numIntegerParameters
				<< " integer parameters, simulation component has " << numIntegerParameters)
	}

	if (numInputs != dll_numInputs) {
		RaiseComponentError(this, "Controller loaded from dll expects " << dll_numInputs
				<< " inputs, simulation component has " << numInputs)
	}

	if (numOutputs != dll_numOutputs) {
		RaiseComponentError(this, "Controller loaded from dll expects " << dll_numOutputs
				<< " outputs, simulation component has " << numOutputs)
	}


	_init(controller);
}

void StateMachineController::setParameters(double realParameterValues[],
	int integerParameterValues[]) {
	_setParameters(controller, realParameterValues, integerParameterValues);
}

void StateMachineController::setInputs(double inputValues[]) {
	_setInputs(controller, inputValues);
}

void StateMachineController::getOutputs(double outputValues[]) {
	_getOutputs(controller, outputValues);
}

void StateMachineController::enter() {
	_enter(controller);
}

/* Function called on each integrator step */
void StateMachineController::step() {
	if (SimEnv.isEventMode()) {
		while (_isActionRequested(controller)) {
			_react(controller);
		}
	} else {
		bool actionRequested = _isActionRequested(controller);
		if (actionRequested) {
			SimEnv.updateEventIndicator(actionRequested);
		}
	}
}

StateMachineController* StateMachineController_new() {
	return new StateMachineController();
}

void StateMachineController_loadController(StateMachineController* component, const char* controllerPath) {
	component->loadController(controllerPath);
}

void StateMachineController_init(StateMachineController* component,
		int numRealParameters, int numIntegerParameters,
		int numInputs, int numOutputs) {
	component->init(numRealParameters, numIntegerParameters, numInputs, numOutputs);
}

void StateMachineController_setParameters(StateMachineController* component,
		double realParameterValues[],
		int integerParameterValues[]) {
	component->setParameters(realParameterValues, integerParameterValues);
}

void StateMachineController_setInputs(StateMachineController* component, double inputValues[]) {
	component->setInputs(inputValues);
}

void StateMachineController_getOutputs(StateMachineController* component, double outputValues[]) {
	component->getOutputs(outputValues);
}

void StateMachineController_enter(StateMachineController* component) {
	component->enter();
}

void StateMachineController_step(StateMachineController* component) {
	component->step();
}
