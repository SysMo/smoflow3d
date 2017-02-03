/* Submodel SMO_PIPE_STRAIGHT_HEAT_EXCHANGER_RC skeleton created by AME Submodel editing utility
   Thu Feb 2 14:19:54 2017 */



#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "ameutils.h"
/* *******************************************************************************
TITLE :
 
------------------------------------------------------------------------------
DESCRIPTION :
 
------------------------------------------------------------------------------
USAGE :
 
------------------------------------------------------------------------------
PARAMETER SETTINGS :
 
------------------------------------------------------------------------------
REVISIONS :
 
******************************************************************************* */

#define _SUBMODELNAME_ "SMO_PIPE_STRAIGHT_HEAT_EXCHANGER_RC"

/* >>>>>>>>>>>>Insert Private Code Here. */
#include "SmoFlowAme.h"
#include "volumes/PipeHeatExchPrDropMassAcc_RC.h"
 
#define _port1FluidFlow ps[0]
#define _port1FluidFlowIndex ic[0]
 
#define _port3FluidState ps[1]
#define _port3FluidStateIndex ic[1]
 
#define _wallHeatFlow ps[2]
#define _wallHeatFlowIndex ic[2]
 
#define _port1FluidState ps[3]
#define _friction ps[4]
#define _convection ps[5]
#define _component ps[6]
/* <<<<<<<<<<<<End of Private Code. */


/* There are 11 real parameters:

   hydraulicDiameter      hydraulic diameter          [mm -> m]
   pipeLength             pipe length                 [m]
   flowArea               flow (cross sectional) area [mm**2 -> m**2]
   absoluteRoughness      absolute roughness          [mm -> m]
   pressureDropGain       pressure drop gain          [null]
   heatExchangeGain       heat exchange gain          [null]
   initialPressure        initial pressure            [barA -> PaA]
   initialTemperature     initial temperature (K)     [K]
   initialTemperatureC    initial temperature (°C)    [degC]
   initialGasMassFraction initial gas mass fraction   [null]
   initialSuperheat       initial superheat           [K]
*/


/* There are 5 integer parameters:

   allowBidirectionalFlow       allow bi-directional flow         
   geometryType                 geometry type                     
   forcedConvectionUseFilmState use film state (forced convection)
   initConditionsChoice         type of initialization            
   stateVariableSelection       states variables                  
*/

void smo_pipe_straight_heat_exchanger_rcin_(int *n, double rp[11]
      , int ip[5], int ic[6], void *ps[7], double stateValues[2])

{
   int loop, error;
/* >>>>>>>>>>>>Extra Initialization Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Initialization declarations. */
   int allowBidirectionalFlow, geometryType, 
      forcedConvectionUseFilmState, initConditionsChoice, 
      stateVariableSelection;
   double hydraulicDiameter, pipeLength, flowArea, absoluteRoughness, 
      pressureDropGain, heatExchangeGain, initialPressure, 
      initialTemperature, initialTemperatureC, initialGasMassFraction
      , initialSuperheat;

   allowBidirectionalFlow = ip[0];
   geometryType = ip[1];
   forcedConvectionUseFilmState = ip[2];
   initConditionsChoice = ip[3];
   stateVariableSelection = ip[4];

   hydraulicDiameter = rp[0];
   pipeLength = rp[1];
   flowArea   = rp[2];
   absoluteRoughness = rp[3];
   pressureDropGain = rp[4];
   heatExchangeGain = rp[5];
   initialPressure = rp[6];
   initialTemperature = rp[7];
   initialTemperatureC = rp[8];
   initialGasMassFraction = rp[9];
   initialSuperheat = rp[10];
   loop = 0;
   error = 0;

/*
   If necessary, check values of the following:

   rp[0..10]
   stateValues[0..1]
*/


/* >>>>>>>>>>>>Initialization Function Check Statements. */
/* <<<<<<<<<<<<End of Initialization Check Statements. */

/*   Integer parameter checking:   */

   if (allowBidirectionalFlow < 1 || allowBidirectionalFlow > 2)
   {
      amefprintf(stderr, "\nallow bi-directional flow must be in range [1..2].\n");
      error = 2;
   }
   if (geometryType < 1 || geometryType > 2)
   {
      amefprintf(stderr, "\ngeometry type must be in range [1..2].\n");
      error = 2;
   }
   if (forcedConvectionUseFilmState < 1 || forcedConvectionUseFilmState > 2)
   {
      amefprintf(stderr, "\nuse film state (forced convection) must be in range [1..2].\n");
      error = 2;
   }
   if (initConditionsChoice < 1 || initConditionsChoice > 4)
   {
      amefprintf(stderr, "\ntype of initialization must be in range [1..4].\n");
      error = 2;
   }
   if (stateVariableSelection < 1 || stateVariableSelection > 4)
   {
      amefprintf(stderr, "\nstates variables must be in range [1..4].\n");
      error = 2;
   }

   if(error == 1)
   {
      amefprintf(stderr, "\nWarning in %s instance %d.\n", _SUBMODELNAME_, *n);
   }
   else if(error == 2)
   {
      amefprintf(stderr, "\nFatal error in %s instance %d.\n", _SUBMODELNAME_, *n);
      amefprintf(stderr, "Terminating the program.\n");
      AmeExit(1);
   }

/* Common -> SI units conversions. */

   rp[0]    *= 1.00000000000000e-003;
   hydraulicDiameter = rp[0];
   rp[2]    *= 1.00000000000000e-006;
   flowArea   = rp[2];
   rp[3]    *= 1.00000000000000e-003;
   absoluteRoughness = rp[3];
   rp[6]    *= 1.00000000000000e+005;
   initialPressure = rp[6];


/* >>>>>>>>>>>>Initialization Function Executable Statements. */
   double flowAreaValue;
   if (geometryType == 1) { //cylindrical pipe
	   flowAreaValue = M_PI / 4 * hydraulicDiameter * hydraulicDiameter;
   } else { //non-cylindrical pipe
	   flowAreaValue = flowArea;
   }
   _friction = FrictionFlowPipe_StraightPipe_new(pipeLength, hydraulicDiameter, flowAreaValue, absoluteRoughness);
   _convection = ForcedConvection_StraightPipe_new(pipeLength, hydraulicDiameter, flowAreaValue);
 
   Convection_setHeatExchangeGain(_convection, heatExchangeGain);
   Convection_setUseFilmState(_convection, forcedConvectionUseFilmState - 1); //:TRICKY: (0-no, 1-yes)
   ForcedConvection_setLimitOutput(_convection, 1); //:TRICKY: (0-no, 1-yes)
   FrictionFlowPipe_setPressureDropGain(_friction, pressureDropGain);
 
   double internalVolume = flowAreaValue * pipeLength;
   _component = PipeHeatExchPrDropMassAcc_RC_new(
		   allowBidirectionalFlow - 1, //:TRICKY: allowBidirectionalFlow =  '{1-no, 2-yes} - 1'  =  '{0-no, 1-yes}'
		   internalVolume,
		   _friction,
		   _convection);
   SMOCOMPONENT_SET_PROPS(_component)
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

/*  There are 3 ports.

   Port 1 has 3 variables:

      1 port1FluidFlowIndex              fluid flow index at port 1   [smoFFL] basic variable output  UNPLOTTABLE
      2 fluidFlowActivationSignalDup     duplicate of fluidFlowActivationSignal
      3 port1FluidStateIndex             fluid state index at port 1  [smoTDS] basic variable input  UNPLOTTABLE

   Port 2 has 2 variables:

      1 heatFlowIndex        heat flow index    [smoHFL] basic variable output  UNPLOTTABLE
      2 thermalNodeIndex     thermal node index [smoTHN] basic variable input  UNPLOTTABLE

   Port 3 has 3 variables:

      1 port3FluidStateIndex          fluid state index outlet     [smoTDS]  multi line macro 'smo_pipe_straight_heat_exchanger_rc_macro0_'  UNPLOTTABLE
      2 port3FluidFlowIndex           fluid flow index at port 3   [smoFFL]  basic variable input  UNPLOTTABLE
      3 fluidFlowActivationSignal     fluid flow activation signal [smoFFAS] basic variable input
*/

/*  There are 7 internal variables.

      1 port1Temperature          port 1 temperature     [K]         basic variable
      2 port3Temperature          port 3 temperature     [K]         basic variable
      3 stateValues[2]            state values           [null]      explicit state (derivative `stateValuesDot')
      4 reynoldsNumber            Reynolds number        [null]      basic variable
      5 convectionCoefficient     convection coefficient [W/m**2/K]  basic variable
      6 heatFlowRateFromWall      heat flow rate         [W]         basic variable
      7 totalPressureLoss         total pressure loss    [bar -> Pa] basic variable
*/

void smo_pipe_straight_heat_exchanger_rc_(int *n
      , double *port1FluidFlowIndex, double *port1FluidStateIndex
      , double *heatFlowIndex, double *thermalNodeIndex
      , double *port3FluidStateIndex, double *port3FluidFlowIndex
      , double *fluidFlowActivationSignal, double *port1Temperature
      , double *port3Temperature, double stateValues[2]
      , double stateValuesDot[2], double *reynoldsNumber
      , double *convectionCoefficient, double *heatFlowRateFromWall
      , double *totalPressureLoss, double rp[11], int ip[5], int ic[6]
      , void *ps[7], int *flag)

{
   int loop, logi;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   int allowBidirectionalFlow, geometryType, 
      forcedConvectionUseFilmState, initConditionsChoice, 
      stateVariableSelection;
   double hydraulicDiameter, pipeLength, flowArea, absoluteRoughness, 
      pressureDropGain, heatExchangeGain, initialPressure, 
      initialTemperature, initialTemperatureC, initialGasMassFraction
      , initialSuperheat;

   allowBidirectionalFlow = ip[0];
   geometryType = ip[1];
   forcedConvectionUseFilmState = ip[2];
   initConditionsChoice = ip[3];
   stateVariableSelection = ip[4];

   hydraulicDiameter = rp[0];
   pipeLength = rp[1];
   flowArea   = rp[2];
   absoluteRoughness = rp[3];
   pressureDropGain = rp[4];
   heatExchangeGain = rp[5];
   initialPressure = rp[6];
   initialTemperature = rp[7];
   initialTemperatureC = rp[8];
   initialGasMassFraction = rp[9];
   initialSuperheat = rp[10];
   logi = 0;
   loop = 0;

/* Common -> SI units conversions. */

/*   *port1FluidStateIndex *= ??; CONVERSION UNKNOWN [smoTDS] */
/*   *thermalNodeIndex *= ??; CONVERSION UNKNOWN [smoTHN] */
/*   *port3FluidStateIndex *= ??; CONVERSION UNKNOWN [smoTDS] */
/*   *port3FluidFlowIndex *= ??; CONVERSION UNKNOWN [smoFFL] */
/*   *fluidFlowActivationSignal *= ??; CONVERSION UNKNOWN [smoFFAS] */

/*
   Set all submodel outputs below:

   *port1FluidFlowIndex = ??;
   *heatFlowIndex = ??;
   *port1Temperature = ??;
   *port3Temperature = ??;
   stateValuesDot[0..1] = ??;
   *reynoldsNumber = ??;
   *convectionCoefficient = ??;
   *heatFlowRateFromWall = ??;
   *totalPressureLoss = ??;
*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
   SMOCOMPONENT_PRINT_MAIN_CALC
   if (firstc_()) {
	   FluidFlow* port3Flow = FluidFlow_get(*port3FluidFlowIndex);
	   PipeHeatExchPrDropMassAcc_RC_init(_component, port3Flow);
 
	   _port1FluidFlow = PipeHeatExchPrDropMassAcc_RC_getPort1Flow(_component);
	   _port1FluidFlowIndex = SmoObject_getInstanceIndex(_port1FluidFlow);
 
	   _wallHeatFlow = PipeHeatExchPrDropMassAcc_RC_getWallHeatFlow(_component);
	   _wallHeatFlowIndex = SmoObject_getInstanceIndex(_wallHeatFlow);
   }
   if (*fluidFlowActivationSignal == 0) {
	   PipeHeatExchPrDropMassAcc_RC_compute_deactivedFluidFlow(_component);
   } else {
	   PipeHeatExchPrDropMassAcc_RC_compute(_component);
   }
 
   *port1FluidFlowIndex = _port1FluidFlowIndex;
   *heatFlowIndex = _wallHeatFlowIndex;
   *port1Temperature = MediumState_T(_port1FluidState);
   *port3Temperature = MediumState_T(_port3FluidState);
   PipeHeatExchPrDropMassAcc_RC_getStateDerivatives(_component, &stateValuesDot[0], &stateValuesDot[1]);
   *reynoldsNumber = ForcedConvection_getReynoldsNumber(_convection);
   *convectionCoefficient = Convection_getConvectionCoefficient(_convection);
   *heatFlowRateFromWall = -HeatFlow_getEnthalpyFlowRate(_wallHeatFlow);
   *totalPressureLoss = FrictionFlowPipe_getAbsolutePressureDrop(_friction);
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *port1FluidFlowIndex /= ??; CONVERSION UNKNOWN [smoFFL] */
/*   *port1FluidStateIndex /= ??; CONVERSION UNKNOWN [smoTDS] */
/*   *heatFlowIndex /= ??; CONVERSION UNKNOWN [smoHFL] */
/*   *thermalNodeIndex /= ??; CONVERSION UNKNOWN [smoTHN] */
/*   *port3FluidStateIndex /= ??; CONVERSION UNKNOWN [smoTDS] */
/*   *port3FluidFlowIndex /= ??; CONVERSION UNKNOWN [smoFFL] */
/*   *fluidFlowActivationSignal /= ??; CONVERSION UNKNOWN [smoFFAS] */
   *totalPressureLoss /= 1.00000000000000e+005;
}

extern double smo_pipe_straight_heat_exchanger_rc_macro0_(int *n
      , double *port1FluidStateIndex, double *thermalNodeIndex
      , double stateValues[2], double rp[11], int ip[5], int ic[6]
      , void *ps[7], int *flag)

{
   double port3FluidStateIndex;
   int loop, logi;
/* >>>>>>>>>>>>Extra Macro Function macro0 Declarations Here. */
/* <<<<<<<<<<<<End of Extra Macro macro0 declarations. */
   int allowBidirectionalFlow, geometryType, 
      forcedConvectionUseFilmState, initConditionsChoice, 
      stateVariableSelection;
   double hydraulicDiameter, pipeLength, flowArea, absoluteRoughness, 
      pressureDropGain, heatExchangeGain, initialPressure, 
      initialTemperature, initialTemperatureC, initialGasMassFraction
      , initialSuperheat;

   allowBidirectionalFlow = ip[0];
   geometryType = ip[1];
   forcedConvectionUseFilmState = ip[2];
   initConditionsChoice = ip[3];
   stateVariableSelection = ip[4];

   hydraulicDiameter = rp[0];
   pipeLength = rp[1];
   flowArea   = rp[2];
   absoluteRoughness = rp[3];
   pressureDropGain = rp[4];
   heatExchangeGain = rp[5];
   initialPressure = rp[6];
   initialTemperature = rp[7];
   initialTemperatureC = rp[8];
   initialGasMassFraction = rp[9];
   initialSuperheat = rp[10];
   logi = 0;
   loop = 0;

/* Common -> SI units conversions. */

/*   *port1FluidStateIndex *= ??; CONVERSION UNKNOWN [smoTDS] */
/*   *thermalNodeIndex *= ??; CONVERSION UNKNOWN [smoTHN] */

/*
   Define and return the following macro variable:

   port3FluidStateIndex = ??;
*/


/* >>>>>>>>>>>>Macro Function macro0 Executable Statements. */
   SMOCOMPONENt_PRINT_MACRO
   if (firstc_()) {
	   // Get the inlet state and wall node
	   _port1FluidState = MediumState_get(*port1FluidStateIndex);
	   ThermalNode* wallNode = ThermalNode_get(*thermalNodeIndex);
 
	   // Initialize outlet state
	   StateVariableSet internalStateInitialValues;
	   if (initConditionsChoice == 1) {
		   internalStateInitialValues = (StateVariableSet) {iT, initialTemperature, iP, initialPressure};
	   } else if (initConditionsChoice == 2) {
		   internalStateInitialValues = (StateVariableSet) {iT, initialTemperatureC + 273.15, iP, initialPressure};
	   } else if (initConditionsChoice == 3) {
		   internalStateInitialValues = (StateVariableSet) {iP, initialPressure, iQ, initialGasMassFraction};
	   } else {
		   AME_RAISE_ERROR("Unsupported type of initialization.")
	   }
 
	   PipeHeatExchPrDropMassAcc_RC_initStates(_component, _port1FluidState, wallNode, stateVariableSelection, internalStateInitialValues);
 
	   _port3FluidState = PipeHeatExchPrDropMassAcc_RC_getPort2State(_component);
	   _port3FluidStateIndex = SmoObject_getInstanceIndex(_port3FluidState);
 
 
	   PipeHeatExchPrDropMassAcc_RC_getStateValues(_component, &stateValues[0], &stateValues[1]);
   } else {
	   PipeHeatExchPrDropMassAcc_RC_setStateValues(_component, stateValues[0], stateValues[1]);
   }
 
   port3FluidStateIndex = _port3FluidStateIndex;
/* <<<<<<<<<<<<End of Macro macro0 Executable Statements. */

/* SI -> Common units conversions. */

/*   *port1FluidStateIndex /= ??; CONVERSION UNKNOWN [smoTDS] */
/*   *thermalNodeIndex /= ??; CONVERSION UNKNOWN [smoTHN] */

/*   *port3FluidStateIndex /= ??; CONVERSION UNKNOWN [smoTDS] */

   return port3FluidStateIndex;
}

