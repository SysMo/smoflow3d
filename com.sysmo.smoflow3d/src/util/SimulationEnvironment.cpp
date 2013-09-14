/*
 * SimulationEnvironment.cpp
 *
 *  Created on: Aug 25, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "SimulationEnvironment.h"
#include <cstdlib>

SimulationEnvironment SimEnv;

/******* Default functions **********/

static void message_default(const char* text) {
	std::cout << text;
}

static void warning_default(const char* text) {
	std::cerr << text;
}

static void error_default(const char* text) {
	std::cerr << text;
	std::exit(1);
}

static void exit_default() {
	std::exit(0);
}

static void updateEventIndicator_default(int indicator) {
	RaiseError("Function 'updateEventIndicator': " << "The simulation environment does not support event mode, or no function assigned")
}

static int isEventMode_default() {
	RaiseError("Function 'isEventMode': " << "The simulation environment does not support event mode, or no function assigned")
}

static int isFirstTimeStep_default() {
	RaiseError("Function 'isFirstTimeStep': " << "Not implemented")
}

static void registerTimeEvent_default(double t) {
	RaiseError("Function 'registerTimeEvent': " << "The simulation environment does not support event mode, or no function assigned")
}
/******* End default functions **********/

SimulationEnvironment::SimulationEnvironment() {
	present = false;
	//currentComponent = NULL;
	t = -1;
	this->_message = message_default;
	this->_warning = warning_default;
	this->_error = error_default;
	this->_exit = exit_default;
	this->_updateEventIndicator = updateEventIndicator_default;
	this->_isEventMode = isEventMode_default;
	this->_isFirstTimeStep = isFirstTimeStep_default;
	this->_registerTimeEvent = registerTimeEvent_default;
}

SimulationEnvironment::~SimulationEnvironment() {
}

void SimulationEnvironment::message(const char* text) {
	_message(text);
}

void SimulationEnvironment::message(const String text) {
	_message(text.c_str());
}

void SimulationEnvironment::warning(const char* text) {
	_warning(text);
}

void SimulationEnvironment::warning(const String text) {
	_warning(text.c_str());
}

void SimulationEnvironment::error(const char* text) {
	_error(text);
}

void SimulationEnvironment::error(const String text) {
	_error(text.c_str());
}

void SimulationEnvironment::exit() {
	_exit();
}

void SimulationEnvironment::updateEventIndicator(bool indicator) {
	if (indicator) {
		_updateEventIndicator(1);
	} else {
		_updateEventIndicator(0);
	}
}

bool SimulationEnvironment::isEventMode() {
	int res = _isEventMode();
	if (res == 0) {
		return false;
	} else {
		return true;
	}
}

bool SimulationEnvironment::isFirstTimeStep() {
	int res = _isFirstTimeStep();
	if (res == 0) {
		return false;
	} else {
		return true;
	}
}

void SimulationEnvironment::registerTimeEvent(double t) {
	_registerTimeEvent(t);
}

void SimulationEnvironment_registerSimEnvComponent() {
	if (SimEnv.present) {
		RaiseError("No more than one \"Simulation Environment\" component can be present in a model")
	}
	SimEnv.present = true;
}

void SimulationEnvironment_setTime(double t) {
	SimEnv.t = t;
}

double SimulationEnvironment_getTime() {
	return SimEnv.t;
}

void SimulationEnvironment_message(const char* text) {
	SimEnv.message(text);
}

void SimulationEnvironment_warning(const char* text) {
	SimEnv.warning(text);
}

void SimulationEnvironment_error(const char* text) {
	SimEnv.error(text);
}

void SimulationEnvironment_exit() {
	SimEnv.exit();
}

const char* SimulationEnvironment_getComponentId(SmoComponent* component) {
	std::stringstream resStream;
	resStream << component->getComponentName()
	<< " instance " << component->instanceIndex;
	String componentId(resStream.str());
	return componentId.c_str();
}

void SimulationEnvironment_setMessageFunc(SimEnv_MessageFunc func) {
	SimEnv._message = func;
}

void SimulationEnvironment_setWarningFunc(SimEnv_WarningFunc func) {
	SimEnv._warning = func;
}

void SimulationEnvironment_setErrorFunc(SimEnv_ErrorFunc func) {
	SimEnv._error = func;
}

void SimulationEnvironment_setExitFunc(SimEnv_ExitFunc func) {
	SimEnv._exit = func;
}

void SimulationEnvironment_setUpdateEventIndicatorFunc(SimEnv_UpdateEventIndicatorFunc func) {
	SimEnv._updateEventIndicator = func;
}

void SimulationEnvironment_setIsEventModeFunc(SimEnv_IsEventModeFunc func) {
	SimEnv._isEventMode = func;
}
void SimulationEnvironment_setIsFirstTimeStepFunc(SimEnv_IsFirstTimeStep func) {
	SimEnv._isFirstTimeStep = func;
}
void SimulationEnvironment_setRegisterTimeEventFunc(SimEnv_RegisterTimeEventFunc func) {
	SimEnv._registerTimeEvent = func;
}
