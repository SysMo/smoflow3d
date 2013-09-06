/*
 * SimulationEnvironment.cpp
 *
 *  Created on: Aug 25, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "SimulationEnvironment.h"
#include <cstdlib>

static SimulationEnvironment SimEnv;

/******* Default functions **********/

static void message_default(const char* message) {
	std::cout << message;
}

static void warning_default(const char* message) {
	std::cerr << message;
}

static void error_default(const char* message) {
	std::cerr << message;
	std::exit(1);
}

static void exit_default() {
	std::exit(0);
}

/******* End default functions **********/

SimulationEnvironment::SimulationEnvironment() {
	present = false;
	currentComponent = NULL;
	t = -1;
	this->message = message_default;
	this->warning = warning_default;
	this->error = error_default;
	this->exit = exit_default;
}

SimulationEnvironment::~SimulationEnvironment() {
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

void SimulationEnvironment_setCurrentComponent(SmoComponent* component) {
	SimEnv.currentComponent = component;
}

SmoComponent* SimulationEnvironment_getCurrentComponent() {
	return SimEnv.currentComponent;
}

void SimulationEnvironment_message(const char* message) {
	SimEnv.message(message);
}

void SimulationEnvironment_warning(const char* message) {
	SimEnv.warning(message);
}

void SimulationEnvironment_error(const char* message) {
	SimEnv.error(message);
}

void SimulationEnvironment_exit() {
	SimEnv.exit();
}

//Fatal error in TPFCH000 instance 1.
const char* SimulationEnvironment_getComponentId(SmoComponent* component) {
	std::stringstream resStream;
	resStream << component->getComponentName()
	<< " instance " << component->instanceIndex;
	String componentId(resStream.str());
	return componentId.c_str();
}

/*
std::stringstream SimulationEnvironment_StreamEvent(SmoComponent* component, const char* file,
		const char* function, const char* line) {
	std::stringstream messageStream;
	messageStream << "\n" <<
	"--------------------------------------------------\n" <<
	"--------------------------------------------------\n" <<
	"Component: " << SimulationEnvironment_getComponentId(component) << "\n" <<
	"File: " << file << "\n" <<
	"Function: " << function << "\n" <<
	"Line: " << line << "\n";
	return messageStream;
}
*/
