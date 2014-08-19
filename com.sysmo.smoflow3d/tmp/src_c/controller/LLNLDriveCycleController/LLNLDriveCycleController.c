/*
 * LLNLDriveCycleController.c
 *
 *  Created on: July, 31 2014
 *      Author: Milen Borisov
 */

#include "LLNLDriveCycleController.h"

static const char *stateNames[NUMBER_OF_STATES] = {
	"Cold refueling",
	"Warm refueling",
	"Extraction",
	"Venting",
	"Waiting"
};

void new(StateMachineController* self) {
	self->numInputs = NUM_INPUTS;
	self->numOutputs = NUM_OUTPUTS;
	self->numRealParameters = NUM_REAL_PARAMETERS;
	self->numIntegerParameters = NUM_INTEGER_PARAMETERS;

	self->parameters = malloc(sizeof(Parameters));
	self->inputs = malloc(sizeof(Inputs));
	self->outputs = malloc(sizeof(Outputs));
	self->locals = malloc(sizeof(Locals));
}

void setParameters(StateMachineController* self,
		double *realParameterValues, int *integerParameterValues) {
	LOAD_COMPONENT_VARIABLES
	parameters->hasVenting = integerParameterValues[0];

	parameters->tankFinalPressureExtraction = realParameterValues[0];
	parameters->tankFinalPressureColdRefueling = realParameterValues[1];
	parameters->tankFinalPressureWarmRefueling = realParameterValues[2];
	parameters->numberColdRefueling = realParameterValues[3];
	parameters->numberWarmRefueling = realParameterValues[4];
	parameters->tankFinalVentingTemperature = realParameterValues[5];
}

void init(StateMachineController* self, int initialState) {
	LOAD_COMPONENT_VARIABLES
	locals->currentState = UNDEFINED;
	locals->nextState = initialState;
	locals->numStartedColdRefuelings = 0;
	locals->numStartedWarmRefuelings = 0;
	switchState(self);
}

void setInputs(StateMachineController* self, double* inputValues) {
	LOAD_COMPONENT_VARIABLES
	inputs->tankPressure = inputValues[0];
	inputs->tankTemperature = inputValues[1];
	inputs->tankDensity = inputValues[2];
}

void getOutputs(StateMachineController* self, double* outputValues) {
	LOAD_COMPONENT_VARIABLES
	outputValues[0] = outputs->valveSignalColdRefueling;
	outputValues[1] = outputs->valveSignalWarmRefueling;
	outputValues[2] = outputs->valveSignalExtraction;
}

int checkForTransition(StateMachineController* self) {
	LOAD_COMPONENT_VARIABLES
	locals->nextState = UNDEFINED;
	switch (locals->currentState) {
	case COLD_REFUELING:
		if (inputs->tankPressure > parameters->tankFinalPressureColdRefueling) {
			locals->nextState = DRIVING;

			if (parameters->hasVenting) {
				if (locals->numStartedColdRefuelings == parameters->numberColdRefueling) {
					locals->nextState = VENTING;
				}
			}
		}
		break;
	case WARM_REFUELING:
		if (inputs->tankPressure > parameters->tankFinalPressureWarmRefueling) {
			locals->nextState = DRIVING;
		}
		break;
	case DRIVING:
		if (inputs->tankPressure < parameters->tankFinalPressureExtraction) {
			if (locals->numStartedColdRefuelings < parameters->numberColdRefueling) {
				locals->nextState = COLD_REFUELING;
			} else if (locals->numStartedWarmRefuelings < parameters->numberWarmRefueling) {
				locals->nextState = WARM_REFUELING;
			} else {
				locals->nextState = WAITING;
			}
		}
		break;
	case VENTING:
		if (inputs->tankTemperature > parameters->tankFinalVentingTemperature) {
			locals->nextState = DRIVING;
		}
		break;
	case WAITING:
		break;
	default:
		self->platform->printError("Non existing state #%d", locals->currentState);
		self->platform->exit(1);
	}
	return locals->nextState;
}


void switchState(StateMachineController* self) {
	LOAD_COMPONENT_VARIABLES

	if (locals->currentState == UNDEFINED) {
		self->platform->printMessage(
				"Time: %e: Controller '%s' setting initial state '(%d)%s'\n",
				self->time, self->name->chars,
				locals->nextState, stateNames[locals->nextState]);
	} else {
		self->platform->printMessage(
				"Time: %e: Controller '%s' switching from state '(%d)%s' to state '(%d)%s'\n",
				self->time, self->name->chars,
				locals->currentState, stateNames[locals->currentState],
				locals->nextState, stateNames[locals->nextState]);

		//Actions to be performed on state exit
		switch (locals->currentState) {
		default:
			break;
		}
	}
	locals->currentState = locals->nextState;
	locals->nextState = UNDEFINED;

	// Default output values
	outputs->valveSignalColdRefueling = 0.0;
	outputs->valveSignalWarmRefueling = 0.0;
	outputs->valveSignalExtraction = 0.0;

	//Actions to be performed on state enter and set the values of the discrete output variables
	switch (locals->currentState) {
	case COLD_REFUELING:
		locals->numStartedColdRefuelings++;
		outputs->valveSignalColdRefueling = 1.0;
		break;
	case WARM_REFUELING:
		locals->numStartedWarmRefuelings++;
		outputs->valveSignalWarmRefueling = 1.0;
		break;
	case DRIVING:
		outputs->valveSignalExtraction = 1.0;
		break;
	case VENTING:
		break;
	case WAITING:
		break;
	default:
		self->platform->printError("Non existing state #%d", locals->currentState);
		self->platform->exit(1);
	}
}
