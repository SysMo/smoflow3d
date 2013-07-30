/*
 * DriveCycleController.c
 *
 *  Created on: Oct 24, 2013
 *      Author: Atanas Pavlov
 */

#include "DriveCycleController.h"

static const char *stateNames[NUMBER_OF_STATES] = {
		"Cold refueling",
		"Warm refueling",
		"Driving without heat exchanger",
		"Driving with heat exchanger",
		"Stop"
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
	parameters->refuelingPumpSpeed = realParameterValues[0];
	parameters->rhoTankMin = realParameterValues[1];
	parameters->pTankMin = realParameterValues[2];
	parameters->pTankMaxCold = realParameterValues[3];
	parameters->pTankMaxWarm = realParameterValues[4];
	parameters->pTankStartHE = realParameterValues[5];
	parameters->pTankStopHE = realParameterValues[6];
	parameters->rhoTankTurnOnHEPermanently = realParameterValues[7];
	parameters->refuelingType = integerParameterValues[0];
	parameters->stopOnMinPressure = integerParameterValues[1];
}

void init(StateMachineController* self, int initialState) {
	LOAD_COMPONENT_VARIABLES
	locals->currentState = UNDEFINED;
	locals->nextState = initialState;
	switchState(self);
}

void setInputs(StateMachineController* self, double* inputValues) {
	LOAD_COMPONENT_VARIABLES
	inputs->pTank = inputValues[0];
	inputs->TTank = inputValues[1];
	inputs->rhoTank = inputValues[2];
}

void getOutputs(StateMachineController* self, double* outputValues) {
	LOAD_COMPONENT_VARIABLES
	outputValues[0] = outputs->refuelingPumpSpeed;
	outputValues[1] = outputs->stationValveCGH2;
	outputValues[2] = outputs->extractionValve;
	outputValues[3] = outputs->extractionValveHE;

}

void eventRefueling(StateMachineController* self) {
	LOAD_COMPONENT_VARIABLES
	if (parameters->refuelingType == 0) {
		locals->nextState = COLD_REFUELING;
	} else {
		locals->nextState = WARM_REFUELING;
	}
}

Boolean guardTankEmpty(StateMachineController* self) {
	LOAD_COMPONENT_VARIABLES
	Boolean guard1 = (inputs->pTank < parameters->pTankMin);
	if  (guard1) {
		if (parameters->stopOnMinPressure) {
			locals->nextState = STOP;
		} else {
			eventRefueling(self);
		}
		return 1;
	}
	Boolean guard2 = (inputs->rhoTank < parameters->rhoTankMin);
	if (guard2) {
		eventRefueling(self);
		return 1;
	}
	return 0;
}

Boolean guardTankFull(StateMachineController* self, double maxPressure) {
	LOAD_COMPONENT_VARIABLES
	Boolean guard = (inputs->pTank >= maxPressure);
	if (guard) {
		locals->nextState = DRIVING_WITHOUT_HEAT_EXCHANGER;
	}
	return guard;
}

Boolean guardTurnHeatExchangerOn(StateMachineController* self) {
	LOAD_COMPONENT_VARIABLES
	Boolean guard = (inputs->pTank < parameters->pTankStartHE ||
			inputs->rhoTank < parameters->rhoTankTurnOnHEPermanently);
	if (guard) {
		locals->nextState = DRIVING_WITH_HEAT_EXCHANGER;
	}
	return guard;
}
Boolean guardTurnHeatExchangerOff(StateMachineController* self) {
	LOAD_COMPONENT_VARIABLES
	Boolean guard = (inputs->pTank > parameters->pTankStopHE &&
			inputs->rhoTank > parameters->rhoTankTurnOnHEPermanently);
	if (guard) {
		locals->nextState = DRIVING_WITHOUT_HEAT_EXCHANGER;
	}
	return guard;
}

int checkForTransition(StateMachineController* self) {
	LOAD_COMPONENT_VARIABLES
	locals->nextState = UNDEFINED;
	switch (locals->currentState) {
	case COLD_REFUELING:
		if (guardTankFull(self, parameters->pTankMaxCold)){}
		break;
	case WARM_REFUELING:
		if (guardTankFull(self, parameters->pTankMaxWarm)){}
		break;
	case DRIVING_WITHOUT_HEAT_EXCHANGER:
		if (guardTurnHeatExchangerOn(self)) {}
		else if (guardTankEmpty(self)) {}
		break;
	case DRIVING_WITH_HEAT_EXCHANGER:
		if (guardTurnHeatExchangerOff(self)) {}
		else if (guardTankEmpty(self)) {}
		break;
	case STOP:
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
		self->platform->printMessage("Time: %e: Controller '%s' setting initial state '(%d)%s'\n",
				self->time, self->name->chars,
				locals->nextState, stateNames[locals->nextState]);

	} else {
		self->platform->printMessage("Time: %e: Controller '%s' switching from state '(%d)%s' to state '(%d)%s'\n",
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
	outputs->refuelingPumpSpeed = 0;
	outputs->stationValveCGH2 = 0;
	outputs->extractionValve = 0;
	outputs->extractionValveHE = 0;

	switch (locals->currentState) {
	case COLD_REFUELING:
		outputs->refuelingPumpSpeed = parameters->refuelingPumpSpeed;
		break;
	case WARM_REFUELING:
		outputs->stationValveCGH2 = 1;
		break;
	case DRIVING_WITHOUT_HEAT_EXCHANGER:
		outputs->extractionValve = 1;
		break;
	case DRIVING_WITH_HEAT_EXCHANGER:
		outputs->extractionValveHE = 1;
		break;
	case STOP:
		break;
	default:
		self->platform->printError("Non existing state #%d", locals->currentState);
		self->platform->exit(1);
	}
}
