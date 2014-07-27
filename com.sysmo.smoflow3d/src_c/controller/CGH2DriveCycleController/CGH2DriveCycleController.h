/*
 * CGH2DriveCycleController.h
 *
 *  Created on: July, 25 2014
 *      Author: Milen Borisov
 */

#include "controller/StateMachineController.h"

#define CONTROLLER_NAME CGH2DriveCycleController
#define NUM_INPUTS 7
#define NUM_OUTPUTS 3
#define NUM_REAL_PARAMETERS 5
#define NUM_INTEGER_PARAMETERS 2

#define LOAD_COMPONENT_VARIABLES \
	Parameters *parameters = (Parameters*) self->parameters; \
	Inputs *inputs = (Inputs *) self->inputs; \
	Outputs *outputs = (Outputs *) self->outputs; \
	Locals* locals = (Locals*) self->locals;

typedef enum {
	UNDEFINED = -1,
	REFUELING,
	DRIVING,
	FINISH,
	MIN_PRESSURE_REACHED_DURING_DRIVING,
	MAX_TEMPERATURE_REACHED_DURING_REFUELING,
	MIN_TEMPERATURE_REACHED_DURING_DRIVING,
	TANK_OVERFLOW,
	NUMBER_OF_STATES
} ControllerStateEnum;

typedef struct {
	/** Real parameters */
	/** Density for refueling*/
	double tankMinDensity;
	/** Maximum allowed density for refueling in the tank*/
	double tankMaxDensity;
	/** Minimal allowed temperature in the tank*/
	double tankMinTemperature;
	/** Maximal allowed temperature in the tank*/
	double tankMaxTemperature;
	/** Minimal allowed pressure in the tank*/
	double tankMinPressure;

	/** Integer parameters */
	/** Number refueling*/
	int numRefuelings;
	/** Stop after refueling (0 - no, 1 - yes=stop)*/
	int stopAfterRefueling;
} Parameters;

typedef struct {
	/** Simulation time */
	double simTime;
	/** Tank pressure*/
	double tankPressure;
	/** Tank temperature*/
	double tankTemperature;
	/** Tank density*/
	double tankDensity;
	/** Pressure ramp rate according to the table*/
	double pressureRampRate;
	/** Final refueling pressure according to the table*/
	double finalRefuelingPressure;
	/** Whether refueling is allowed (0 - no, 1 - yes=allowed) according to the table*/
	double ifRefuel;
} Inputs;

typedef struct {
	/** Refueling pressure at the beginning of refueling*/
	double startingRefuelingPressure;
	/** Desired pressure ramp rate for the station*/
	double pressureRampRate;
	/** Extraction valve signal (0 - off, 1 - on)*/
	double extractionValveSignal;
} Outputs;

typedef struct {
	ControllerStateEnum currentState;
	ControllerStateEnum nextState;
	double finalRefuelingPressure;
	int numStartedRefuelings;
} Locals;

void new(StateMachineController* self);
void setParameters(StateMachineController* self, double *realParameterValues, int *integerParameterValues);
void init(StateMachineController* self, int initialState);
void setInputs(StateMachineController* self, double* inputValues);
void getOutputs(StateMachineController* self, double* outputValues);
int checkForTransition(StateMachineController* self);
void switchState(StateMachineController* self);
