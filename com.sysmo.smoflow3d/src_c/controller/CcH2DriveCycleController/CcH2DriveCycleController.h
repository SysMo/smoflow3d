/*
 * CcH2DriveCycleController.h
 *
 *  Created on: Oct 24, 2013
 *      Author: Atanas Pavlov
 */

#include "controller/StateMachineController.h"

#define CONTROLLER_NAME CcH2DriveCycleController
#define NUM_INPUTS 3
#define NUM_OUTPUTS 4
#define NUM_REAL_PARAMETERS 8
#define NUM_INTEGER_PARAMETERS 2

#define LOAD_COMPONENT_VARIABLES \
	Parameters *parameters = (Parameters*) self->parameters; \
	Inputs *inputs = (Inputs *) self->inputs; \
	Outputs *outputs = (Outputs *) self->outputs; \
	Locals* locals = (Locals*) self->locals;

typedef enum {
	UNDEFINED = -1,
	COLD_REFUELING,
	WARM_REFUELING,
	DRIVING_WITHOUT_HEAT_EXCHANGER,
	DRIVING_WITH_HEAT_EXCHANGER,
	STOP,
	NUMBER_OF_STATES
} ControllerStateEnum;

typedef struct {
	/** Real parameters */
	/** Refueling pump speed*/
	double refuelingPumpSpeed;
	/** Minimum density in the tank*/
	double rhoTankMin;
	/** Minimum pressure in the tank*/
	double pTankMin;
	/** Refuelling final pressure (cold)*/
	double pTankMaxCold;
	/** Refuelling final pressure (warm)*/
	double pTankMaxWarm;
	/** Pressure to turn on permanently the heat exchanger*/
	double pTankStartHE;
	/** Pressure to turn off the heat exchanger*/
	double pTankStopHE;
	/** Density to turn on the heat exchanger permanently */
	double rhoTankTurnOnHEPermanently;

	/** Integer parameters */
	/** Refueling type (0 - cold, 1 - warm)*/
	int refuelingType;
	/** refuel on min pressure (0) or stop on min pressure (1)*/
	int stopOnMinPressure;

} Parameters;

typedef struct {
	/** Tank pressure*/
	double pTank;
	/** Tank temperature*/
	double TTank;
	/** Tank density*/
	double rhoTank;
} Inputs;

typedef struct {
	/** Refueling pump speed*/
	double refuelingPumpSpeed;
	/** CGH2 valve at the refueling station*/
	double stationValveCGH2;
	/** Valve for hydrogen extraction without HE*/
	double extractionValve;
	/** Valve for hydrogen extraction with HE*/
	double extractionValveHE;
} Outputs;

typedef struct {
	ControllerStateEnum currentState;
	ControllerStateEnum nextState;
} Locals;

void new(StateMachineController* self);
void setParameters(StateMachineController* self,
		double *realParameterValues, int *integerParameterValues);
void init(StateMachineController* self, int initialState);
void setInputs(StateMachineController* self, double* inputValues);
void getOutputs(StateMachineController* self, double* outputValues);
void eventRefueling(StateMachineController* self);
Boolean guardTankEmpty(StateMachineController* self);
Boolean guardTankFull(StateMachineController* self, double maxPressure);
Boolean guardTurnHeatExchangerOn(StateMachineController* self);
Boolean guardTurnHeatExchangerOff(StateMachineController* self);
int checkForTransition(StateMachineController* self);
void switchState(StateMachineController* self);
