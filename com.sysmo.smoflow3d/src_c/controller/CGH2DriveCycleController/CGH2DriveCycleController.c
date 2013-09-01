/*
 * CGH2DriveCycleController.c
 *
 *  Created on: July, 25 2014
 *      Author: Milen Borisov
 */

#include "CGH2DriveCycleController.h"

static const char *stateNames[NUMBER_OF_STATES] = {
	"Refueling",
	"Driving",
	"Finish",
	"Minimal pressure reached during driving",
	"Maximal temperature reached during refueling",
	"Minimal temperature reached during driving",
	"Tank overflow"
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
	parameters->tankMinDensity = realParameterValues[0];
	parameters->tankMaxDensity = realParameterValues[1];
	parameters->tankMinTemperature = realParameterValues[2];
	parameters->tankMaxTemperature = realParameterValues[3];
	parameters->tankMinPressure = realParameterValues[4];

	parameters->numRefuelings = integerParameterValues[0];
	parameters->stopAfterRefueling = integerParameterValues[1];
}

void init(StateMachineController* self, int initialState) {
	LOAD_COMPONENT_VARIABLES
	locals->currentState = UNDEFINED;
	locals->nextState = initialState;
	locals->finalRefuelingPressure = 0.0;
	locals->numStartedRefuelings = 0;
	switchState(self);
}

void setInputs(StateMachineController* self, double* inputValues) {
	LOAD_COMPONENT_VARIABLES
	inputs->simTime = inputValues[0];
	inputs->tankPressure = inputValues[1];
	inputs->tankTemperature = inputValues[2];
	inputs->tankDensity = inputValues[3];
	inputs->pressureRampRate = inputValues[4];
	inputs->finalRefuelingPressure = inputValues[5];
	inputs->ifRefuel = inputValues[6];
}

void getOutputs(StateMachineController* self, double* outputValues) {
	LOAD_COMPONENT_VARIABLES
	outputValues[0] = outputs->startingRefuelingPressure;
	outputValues[1] = outputs->pressureRampRate;
	outputValues[2] = outputs->extractionValveSignal;
}

int checkForTransition(StateMachineController* self) {
	LOAD_COMPONENT_VARIABLES
	locals->nextState = UNDEFINED;
	switch (locals->currentState) {
	case REFUELING:
		if (inputs->tankDensity > parameters->tankMaxDensity) {
			locals->nextState = TANK_OVERFLOW;
		} else if (inputs->tankPressure >= locals->finalRefuelingPressure) {
			if (locals->numStartedRefuelings == parameters->numRefuelings) {
				if (parameters->stopAfterRefueling == 1) {
					locals->nextState = FINISH;
				} else {
					locals->nextState = DRIVING;
				}
			} else {
				locals->nextState = DRIVING;
			}
		} else if (inputs->tankTemperature > parameters->tankMaxTemperature) {
			locals->nextState = MAX_TEMPERATURE_REACHED_DURING_REFUELING;
		}
		break;
	case DRIVING:
		if (inputs->tankDensity < parameters->tankMinDensity) {
			if (locals->numStartedRefuelings == parameters->numRefuelings) {
				locals->nextState = FINISH;
			} else {
				locals->nextState = REFUELING;
			}
		} else if (inputs->tankTemperature < parameters->tankMinTemperature) {
			locals->nextState = MIN_TEMPERATURE_REACHED_DURING_DRIVING;
		} else if (inputs->tankPressure < parameters->tankMinPressure) {
			locals->nextState = MIN_PRESSURE_REACHED_DURING_DRIVING;
		}
		break;
	case FINISH:
		break;
	case MIN_PRESSURE_REACHED_DURING_DRIVING:
		break;
	case MAX_TEMPERATURE_REACHED_DURING_REFUELING:
		break;
	case MIN_TEMPERATURE_REACHED_DURING_DRIVING:
		break;
	case TANK_OVERFLOW:
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
	outputs->startingRefuelingPressure = 0.0;
	outputs->pressureRampRate = 0.0;
	outputs->extractionValveSignal = 0.0;

	//Actions to be performed on state enter and set the values of the discrete output variables
	switch (locals->currentState) {
	case REFUELING:
		locals->finalRefuelingPressure = inputs->finalRefuelingPressure;
		locals->numStartedRefuelings++;

		outputs->startingRefuelingPressure = inputs->tankPressure;
		outputs->pressureRampRate = inputs->pressureRampRate;
		break;
	case DRIVING:
		outputs->extractionValveSignal = 1.0;
		break;
	case FINISH:
		break;
	case MIN_PRESSURE_REACHED_DURING_DRIVING:
		break;
	case MAX_TEMPERATURE_REACHED_DURING_REFUELING:
		break;
	case MIN_TEMPERATURE_REACHED_DURING_DRIVING:
		break;
	case TANK_OVERFLOW:
		break;
	default:
		self->platform->printError("Non existing state #%d", locals->currentState);
		self->platform->exit(1);
	}
}
