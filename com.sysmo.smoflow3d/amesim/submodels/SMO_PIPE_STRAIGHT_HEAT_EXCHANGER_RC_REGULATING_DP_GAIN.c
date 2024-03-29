/* Submodel SMO_PIPE_STRAIGHT_HEAT_EXCHANGER_RC_REGULATING_DP_GAIN skeleton created by AME Submodel editing utility
   ?? ??? 14 10:08:50 2022 */



#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
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

#define _SUBMODELNAME_ "SMO_PIPE_STRAIGHT_HEAT_EXCHANGER_RC_REGULATING_DP_GAIN"

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


/* There are 12 real parameters:

   hydraulicDiameter             hydraulic diameter                        [mm -> m]
   pipeLength                    pipe length                               [m]
   flowArea                      flow (cross sectional) area               [mm**2 -> m**2]
   absoluteRoughness             absolute roughness                        [mm -> m]
   pressureDropGainConst         pressure drop gain                        [null]
   heatExchangeGain              heat exchange gain                        [null]
   heatExchangeGainDeactivedFlow heat exchange gain (deactived fluid flow) [null]
   initialPressure               initial pressure                          [barA -> PaA]
   initialTemperature            initial temperature (K)                   [K]
   initialTemperatureC           initial temperature (°C)                 [degC]
   initialGasMassFraction        initial gas mass fraction                 [null]
   initialSuperheat              initial superheat                         [K]
*/


/* There are 6 integer parameters:

   fluidIndex                   fluid index                       
   allowBidirectionalFlow       allow bi-directional flow         
   geometryType                 geometry type                     
   forcedConvectionUseFilmState use film state (forced convection)
   initConditionsChoice         type of initialization            
   stateVariableSelection       states variables                  
*/

void smo_pipe_straight_heat_exchanger_rc_regulating_dp_gainin_(int *n
      , double rp[12], int ip[6], int ic[6], void *ps[7]
      , double stateValues[2])

{
   int loop, error;
/* >>>>>>>>>>>>Extra Initialization Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Initialization declarations. */
   int fluidIndex, allowBidirectionalFlow, geometryType, 
      forcedConvectionUseFilmState, initConditionsChoice, 
      stateVariableSelection;
   double hydraulicDiameter, pipeLength, flowArea, absoluteRoughness, 
      pressureDropGainConst, heatExchangeGain, 
      heatExchangeGainDeactivedFlow, initialPressure, 
      initialTemperature, initialTemperatureC, initialGasMassFraction
      , initialSuperheat;

   fluidIndex = ip[0];
   allowBidirectionalFlow = ip[1];
   geometryType = ip[2];
   forcedConvectionUseFilmState = ip[3];
   initConditionsChoice = ip[4];
   stateVariableSelection = ip[5];

   hydraulicDiameter = rp[0];
   pipeLength = rp[1];
   flowArea   = rp[2];
   absoluteRoughness = rp[3];
   pressureDropGainConst = rp[4];
   heatExchangeGain = rp[5];
   heatExchangeGainDeactivedFlow = rp[6];
   initialPressure = rp[7];
   initialTemperature = rp[8];
   initialTemperatureC = rp[9];
   initialGasMassFraction = rp[10];
   initialSuperheat = rp[11];
   loop = 0;
   error = 0;

/*
   If necessary, check values of the following:

   rp[0..11]
   stateValues[0..1]
*/


/* >>>>>>>>>>>>Initialization Function Check Statements. */
/* <<<<<<<<<<<<End of Initialization Check Statements. */

/*   Integer parameter checking:   */

   if (fluidIndex < 1 || fluidIndex > 99)
   {
      amefprintf(stderr, "\nfluid index must be in range [1..99].\n");
      error = 2;
   }
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

   if (ameHandleSubmodelError(_SUBMODELNAME_, *n, error))
   {
      return;
   }

/* Common -> SI units conversions. */

   rp[0]    *= 1.00000000000000e-03;
   hydraulicDiameter = rp[0];
   rp[2]    *= 1.00000000000000e-06;
   flowArea   = rp[2];
   rp[3]    *= 1.00000000000000e-03;
   absoluteRoughness = rp[3];
   rp[7]    *= 1.00000000000000e+05;
   initialPressure = rp[7];


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

   double internalVolume = flowAreaValue * pipeLength;
   _component = PipeHeatExchPrDropMassAcc_RC_new(
		   allowBidirectionalFlow - 1, //:TRICKY: allowBidirectionalFlow =  '{1-no, 2-yes} - 1'  =  '{0-no, 1-yes}'
		   internalVolume,
		   _friction,
		   _convection);
   SMOCOMPONENT_SET_PROPS(_component)

   // Initialize the internal state
   StateVariableSet internalStateInitialValues;
   if (initConditionsChoice == 1) {
	   internalStateInitialValues = (StateVariableSet) {iT, initialTemperature, iP, initialPressure};
   } else if (initConditionsChoice == 2) {
	   internalStateInitialValues = (StateVariableSet) {iT, initialTemperatureC + 273.15, iP, initialPressure};
   } else if (initConditionsChoice == 3) {
	   internalStateInitialValues = (StateVariableSet) {iP, initialPressure, iQ, initialGasMassFraction};
   } else {
	   AME_RAISE_ERROR("Unsupported type of initialization.");
	   internalStateInitialValues = (StateVariableSet) {iT, initialTemperature, iP, initialPressure};
   }

   Medium* fluid = Medium_get(fluidIndex);
   PipeHeatExchPrDropMassAcc_RC_initInternalState(_component, fluid, stateVariableSelection, internalStateInitialValues);

   _port3FluidState = PipeHeatExchPrDropMassAcc_RC_getPort2State(_component);
   _port3FluidStateIndex = SmoObject_getInstanceIndex(_port3FluidState);

   PipeHeatExchPrDropMassAcc_RC_getStateValues(_component, &stateValues[0], &stateValues[1]);
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

/*  There are 4 ports.

   Port 1 has 3 variables:

      1 port1FluidFlowIndex              fluid flow index at port 1   [smoFFL] basic variable output  UNPLOTTABLE
      2 fluidFlowActivationSignalDup     duplicate of fluidFlowActivationSignal
      3 port1FluidStateIndex             fluid state index at port 1  [smoTDS] basic variable input  UNPLOTTABLE

   Port 2 has 2 variables:

      1 heatFlowIndex        heat flow index    [smoHFL] basic variable output  UNPLOTTABLE
      2 thermalNodeIndex     thermal node index [smoTHN] basic variable input  UNPLOTTABLE

   Port 3 has 3 variables:

      1 port3FluidStateIndex          fluid state index outlet     [smoTDS]  multi line macro 'smo_pipe_straight_heat_exchanger_rc_regulating_dp_gain_macro0_'  UNPLOTTABLE
      2 port3FluidFlowIndex           fluid flow index at port 3   [smoFFL]  basic variable input  UNPLOTTABLE
      3 fluidFlowActivationSignal     fluid flow activation signal [smoFFAS] basic variable input

   Port 4 has 1 variable:

      1 pressureDropGainRegSignal     pressure drop gain (regulated signal) [null] basic variable input
*/

/*  There are 14 internal variables.

      1 stateValues[2]            state values                        [null]        explicit state (derivative `stateValuesDot')
      2 port1Temperature          port 1 temperature                  [K]           basic variable
      3 port3Temperature          port 3 temperature                  [K]           basic variable
      4 internalVolume            volume                              [L -> m**3]   basic variable
      5 mass                      fluid mass in the pipe              [kg]          basic variable
      6 massFlowRate              mass flow rate (port3 -> port1)     [kg/s]        basic variable
      7 enthalpyFlowRate          enthalpy flow rate (port3 -> port1) [W]           basic variable
      8 totalPressureLoss         total pressure loss                 [bar -> Pa]   basic variable
      9 reynoldsNumber            Reynolds number                     [null]        basic variable
     10 convectionCoefficient     convection coefficient              [W/m**2/K]    basic variable
     11 heatFlowRateFromWall      heat flow rate                      [W]           basic variable
     12 vFlowUp                   velocity (upstream flow)            [m/s]         basic variable
     13 dynamicPressureUp         dynamic pressure (upstream flow)    [barA -> PaA] basic variable
     14 machNumberUp              Mach number (upstream flow)         [null]        basic variable
*/

void smo_pipe_straight_heat_exchanger_rc_regulating_dp_gain_(int *n
      , double *port1FluidFlowIndex, double *port1FluidStateIndex
      , double *heatFlowIndex, double *thermalNodeIndex
      , double *port3FluidStateIndex, double *port3FluidFlowIndex
      , double *fluidFlowActivationSignal
      , double *pressureDropGainRegSignal, double stateValues[2]
      , double stateValuesDot[2], double *port1Temperature
      , double *port3Temperature, double *internalVolume, double *mass
      , double *massFlowRate, double *enthalpyFlowRate
      , double *totalPressureLoss, double *reynoldsNumber
      , double *convectionCoefficient, double *heatFlowRateFromWall
      , double *vFlowUp, double *dynamicPressureUp
      , double *machNumberUp, double rp[12], int ip[6], int ic[6]
      , void *ps[7], int *flag)

{
   int loop, logi;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   int fluidIndex, allowBidirectionalFlow, geometryType, 
      forcedConvectionUseFilmState, initConditionsChoice, 
      stateVariableSelection;
   double hydraulicDiameter, pipeLength, flowArea, absoluteRoughness, 
      pressureDropGainConst, heatExchangeGain, 
      heatExchangeGainDeactivedFlow, initialPressure, 
      initialTemperature, initialTemperatureC, initialGasMassFraction
      , initialSuperheat;

   fluidIndex = ip[0];
   allowBidirectionalFlow = ip[1];
   geometryType = ip[2];
   forcedConvectionUseFilmState = ip[3];
   initConditionsChoice = ip[4];
   stateVariableSelection = ip[5];

   hydraulicDiameter = rp[0];
   pipeLength = rp[1];
   flowArea   = rp[2];
   absoluteRoughness = rp[3];
   pressureDropGainConst = rp[4];
   heatExchangeGain = rp[5];
   heatExchangeGainDeactivedFlow = rp[6];
   initialPressure = rp[7];
   initialTemperature = rp[8];
   initialTemperatureC = rp[9];
   initialGasMassFraction = rp[10];
   initialSuperheat = rp[11];
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
   stateValuesDot[0..1] = ??;
   *port1Temperature = ??;
   *port3Temperature = ??;
   *internalVolume = ??;
   *mass       = ??;
   *massFlowRate = ??;
   *enthalpyFlowRate = ??;
   *totalPressureLoss = ??;
   *reynoldsNumber = ??;
   *convectionCoefficient = ??;
   *heatFlowRateFromWall = ??;
   *vFlowUp    = ??;
   *dynamicPressureUp = ??;
   *machNumberUp = ??;
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

   double pressureDropGainTotal = (*pressureDropGainRegSignal) * pressureDropGainConst;
   FrictionFlowPipe_setPressureDropGain(_friction, pressureDropGainTotal);
   if (*fluidFlowActivationSignal == 0 || *pressureDropGainRegSignal <= 0) {
	   Convection_setHeatExchangeGain(_convection, heatExchangeGainDeactivedFlow);
	   PipeHeatExchPrDropMassAcc_RC_compute_deactivedFluidFlow(_component);
   } else {
	   Convection_setHeatExchangeGain(_convection, heatExchangeGain);
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
   *internalVolume = PipeHeatExchPrDropMassAcc_RC_getVolume(_component);
   *mass = PipeHeatExchPrDropMassAcc_RC_getFluidMass(_component);

   *massFlowRate = FluidFlow_getMassFlowRate(_port1FluidFlow);
   *enthalpyFlowRate = FluidFlow_getEnthalpyFlowRate(_port1FluidFlow);
   *vFlowUp = FrictionFlowPipe_getUpstreamVelocity(_friction, *massFlowRate);
   *dynamicPressureUp = FrictionFlowPipe_getUpstreamDynamicPressure(_friction, *massFlowRate);
   *machNumberUp = FrictionFlowPipe_getUpstreamMachNumber(_friction, *massFlowRate);
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *port1FluidFlowIndex /= ??; CONVERSION UNKNOWN [smoFFL] */
/*   *port1FluidStateIndex /= ??; CONVERSION UNKNOWN [smoTDS] */
/*   *heatFlowIndex /= ??; CONVERSION UNKNOWN [smoHFL] */
/*   *thermalNodeIndex /= ??; CONVERSION UNKNOWN [smoTHN] */
/*   *port3FluidStateIndex /= ??; CONVERSION UNKNOWN [smoTDS] */
/*   *port3FluidFlowIndex /= ??; CONVERSION UNKNOWN [smoFFL] */
/*   *fluidFlowActivationSignal /= ??; CONVERSION UNKNOWN [smoFFAS] */
   *internalVolume /= 1.00000000000000e-03;
   *totalPressureLoss /= 1.00000000000000e+05;
   *dynamicPressureUp /= 1.00000000000000e+05;
}

extern double smo_pipe_straight_heat_exchanger_rc_regulating_dp_gain_macro0_(
      int *n, double *port1FluidStateIndex, double *thermalNodeIndex
      , double stateValues[2], double rp[12], int ip[6], int ic[6]
      , void *ps[7], int *flag)

{
   double port3FluidStateIndex;
   int loop, logi;
/* >>>>>>>>>>>>Extra Macro Function macro0 Declarations Here. */
/* <<<<<<<<<<<<End of Extra Macro macro0 declarations. */
   int fluidIndex, allowBidirectionalFlow, geometryType, 
      forcedConvectionUseFilmState, initConditionsChoice, 
      stateVariableSelection;
   double hydraulicDiameter, pipeLength, flowArea, absoluteRoughness, 
      pressureDropGainConst, heatExchangeGain, 
      heatExchangeGainDeactivedFlow, initialPressure, 
      initialTemperature, initialTemperatureC, initialGasMassFraction
      , initialSuperheat;

   fluidIndex = ip[0];
   allowBidirectionalFlow = ip[1];
   geometryType = ip[2];
   forcedConvectionUseFilmState = ip[3];
   initConditionsChoice = ip[4];
   stateVariableSelection = ip[5];

   hydraulicDiameter = rp[0];
   pipeLength = rp[1];
   flowArea   = rp[2];
   absoluteRoughness = rp[3];
   pressureDropGainConst = rp[4];
   heatExchangeGain = rp[5];
   heatExchangeGainDeactivedFlow = rp[6];
   initialPressure = rp[7];
   initialTemperature = rp[8];
   initialTemperatureC = rp[9];
   initialGasMassFraction = rp[10];
   initialSuperheat = rp[11];
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
	   _port1FluidState = MediumState_get(*port1FluidStateIndex);
	   ThermalNode* wallNode = ThermalNode_get(*thermalNodeIndex);

	   PipeHeatExchPrDropMassAcc_RC_initOuterStates(_component, _port1FluidState, wallNode);
   }

   PipeHeatExchPrDropMassAcc_RC_setStateValues(_component, stateValues[0], stateValues[1]);


   port3FluidStateIndex = _port3FluidStateIndex;
/* <<<<<<<<<<<<End of Macro macro0 Executable Statements. */

/* SI -> Common units conversions. */

/*   *port1FluidStateIndex /= ??; CONVERSION UNKNOWN [smoTDS] */
/*   *thermalNodeIndex /= ??; CONVERSION UNKNOWN [smoTHN] */

/*   *port3FluidStateIndex /= ??; CONVERSION UNKNOWN [smoTDS] */

   return port3FluidStateIndex;
}

