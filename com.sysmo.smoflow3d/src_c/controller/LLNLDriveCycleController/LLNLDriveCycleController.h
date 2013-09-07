/*
 * LLNLDriveCycleController.h
 *
 *  Created on: July, 31 2014
 *      Author: Milen Borisov
 */

#include "controller/StateMachineController.h"

#define CONTROLLER_NAME LLNLDriveCycleController
#define NUM_INPUTS 3
#define NUM_OUTPUTS 3
#define NUM_REAL_PARAMETERS 6
#define NUM_INTEGER_PARAMETERS 1

#define LOAD_COMPONENT_VARIABLES \
	Parameters *parameters = (Parameters*) self->parameters; \
	Inputs *inputs = (Inputs *) self->inputs; \
	Outputs *outputs = (Outputs *) self->outputs; \
	Locals* locals = (Locals*) self->locals;

typedef enum {
	UNDEFINED = -1,
	COLD_REFUELING,
	WARM_REFUELING,
	DRIVING,
	VENTING,
	WAITING,
	NUMBER_OF_STATES
} ControllerStateEnum;

typedef struct {
	/** Real parameters */
	/** Extraction final pressure [bar]*/
	double tankFinalPressureExtraction;
	/** Refuelling final pressure (cold) [bar]*/
	double tankFinalPressureColdRefueling;
	/** Refuelling final pressure (warm) [bar]*/
	double tankFinalPressureWarmRefueling;
	/** Number cold refueling*/
	double numberColdRefueling;
	/** Number warm refueling (after the cold refuelings)*/
	double numberWarmRefueling;
	/** Venting final temperature [K] */
	double tankFinalVentingTemperature;

	/** Integer parameters */
	/** Venting after the last cold refueling (0 - No, 1 - Yes) */
	int hasVenting;
} Parameters;

typedef struct {
	/** Tank pressure*/
	double tankPressure;
	/** Tank temperature*/
	double tankTemperature;
	/** Tank density*/
	double tankDensity;
} Inputs;

typedef struct {
	/** Cold refueling valve signal (0 - off, 1 - on)*/
	double valveSignalColdRefueling;
	/** Warm refueling valve signal (0 - off, 1 - on)*/
	double valveSignalWarmRefueling;
	/** Extraction valve signal (0 - off, 1 - on)*/
	double valveSignalExtraction;
} Outputs;

typedef struct {
	ControllerStateEnum currentState;
	ControllerStateEnum nextState;
	int numStartedColdRefuelings;
	int numStartedWarmRefuelings;
} Locals;

void new(StateMachineController* self);
void setParameters(StateMachineController* self, double *realParameterValues, int *integerParameterValues);
void init(StateMachineController* self, int initialState);
void setInputs(StateMachineController* self, double* inputValues);
void getOutputs(StateMachineController* self, double* outputValues);
int checkForTransition(StateMachineController* self);
void switchState(StateMachineController* self);
