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

	ShowMessage("Loading controller instance from " << controllerPath << std::endl);
	loader->load(controllerPath);
	CreateControllerFunc createController = (CreateControllerFunc) loader->getMethodAddress("createController");
	controller = createController(SimulationEnvironment_message, SimulationEnvironment_error);

	if (controller != NULL) {
		ShowMessage("Succesfully created controller instance\n");
	} else {
		RaiseComponentError(this, "Couldn't create controller instance from " << controllerPath);
	}
	_getSizes = (GetSizesFunc) loader->getMethodAddress("getSizes");

	_setParameters = (SetParametersFunc) loader->getMethodAddress("setParameters");
	_setInputs = (SetInputsFunc) loader->getMethodAddress("setInputs");
	_setTime = (SetTimeFunc) loader->getMethodAddress("setTime");
	_getOutputs = (GetOutputsFunc) loader->getMethodAddress("getOutputs");
	_getState = (GetStateFunc) loader->getMethodAddress("getState");

	_init = (InitFunc) loader->getMethodAddress("init");
	_enter = (EnterFunc) loader->getMethodAddress("enter");
	_isActionRequested= (ActionRequestedFunc) loader->getMethodAddress("isActionRequested");
	_react  = (ReactFunc) loader->getMethodAddress("react");

	delete loader;
}

void StateMachineController::init() {

	_getSizes(controller, &this->numRealParameters, &this->numIntegerParameters,
			&this->numInputs, &this->numOutputs, &this->maxNumOrthogonalStates);
	_init(controller);
}

void StateMachineController::checkSizes(int numRealParameters, int numIntegerParameters,
		int numInputs, int numOutputs, int maxNumOrthogonalStates) {

	if (numRealParameters != this->numRealParameters) {
		RaiseComponentError(this, "Controller loaded from dll expects " << this->numRealParameters
				<< " real parameters, simulation component has " << numRealParameters)
	}

	if (numIntegerParameters != this->numIntegerParameters) {
		RaiseComponentError(this, "Controller loaded from dll expects " << this->numIntegerParameters
				<< " integer parameters, simulation component has " << numIntegerParameters)
	}

	if (numInputs != this->numInputs) {
		RaiseComponentError(this, "Controller loaded from dll expects " << this->numInputs
				<< " inputs, simulation component has " << numInputs)
	}

	if (numOutputs != this->numOutputs) {
		RaiseComponentError(this, "Controller loaded from dll expects " << this->numOutputs
				<< " outputs, simulation component has " << numOutputs)
	}

	if (maxNumOrthogonalStates != this->maxNumOrthogonalStates) {
		RaiseComponentError(this, "Controller loaded from dll has " << this->maxNumOrthogonalStates
				<< " max. number of orthogonal states, simulation component has " << maxNumOrthogonalStates)
	}
}


void StateMachineController::setParameters(double realParameterValues[],
	int integerParameterValues[]) {
	_setParameters(controller, realParameterValues, integerParameterValues);
}

void StateMachineController::setInputs(double inputValues[]) {
	_setInputs(controller, inputValues);
}

void StateMachineController::setTime(double t) {
	this->t = t;
	_setTime(controller, t);
}

void StateMachineController::getOutputs(double outputValues[]) {
	_getOutputs(controller, outputValues);
}

void StateMachineController::getState(int stateVector[]) {
	_getState(controller, stateVector);
}

void StateMachineController::getState(double stateVector[]) {
	int* stateVectorInt = new int[maxNumOrthogonalStates];
	_getState(controller, stateVectorInt);
	for (int i = 0; i < maxNumOrthogonalStates; i++) {
		stateVector[i] = (double) stateVectorInt[i];
	}
	delete[] stateVectorInt;
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
		timeLastEvent = t;
	} else {
		bool actionRequested = _isActionRequested(controller);
		if (actionRequested && (t - timeLastEvent > 1)) {
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

void StateMachineController_init(StateMachineController* component) {
	component->init();
}

void StateMachineController_checkSizes(StateMachineController* component,
		int numRealParameters, int numIntegerParameters,
		int numInputs, int numOutputs, int maxNumOrthogonalStates) {
	component->checkSizes(numRealParameters, numIntegerParameters,
			numInputs, numOutputs, maxNumOrthogonalStates);
}

void StateMachineController_setParameters(StateMachineController* component,
		double realParameterValues[],
		int integerParameterValues[]) {
	component->setParameters(realParameterValues, integerParameterValues);
}

void StateMachineController_setInputs(StateMachineController* component, double inputValues[]) {
	component->setInputs(inputValues);
}

void StateMachineController_setTime(StateMachineController* component, double t) {
	component->setTime(t);
}

void StateMachineController_getOutputs(StateMachineController* component, double outputValues[]) {
	component->getOutputs(outputValues);
}

void StateMachineController_getState(StateMachineController* component, int stateVector[]) {
	component->getState(stateVector);
}

void StateMachineController_getState_ToDouble(StateMachineController* component, double stateVector[]) {
	component->getState(stateVector);
}

void StateMachineController_enter(StateMachineController* component) {
	component->enter();
}

void StateMachineController_step(StateMachineController* component) {
	component->step();
}
