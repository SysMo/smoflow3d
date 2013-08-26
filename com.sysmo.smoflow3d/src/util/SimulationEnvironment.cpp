/*
 * SimulationEnvironment.cpp
 *
 *  Created on: Aug 25, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "SimulationEnvironment.h"

static SimulationEnvironment SimEnv;

SimulationEnvironment::SimulationEnvironment() {
	present = false;
}

SimulationEnvironment::~SimulationEnvironment() {
	// TODO Auto-generated destructor stub
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
