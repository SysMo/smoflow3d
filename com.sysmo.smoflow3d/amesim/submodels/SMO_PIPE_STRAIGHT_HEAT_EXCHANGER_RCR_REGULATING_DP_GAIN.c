/* Submodel SMO_PIPE_STRAIGHT_HEAT_EXCHANGER_RCR_REGULATING_DP_GAIN skeleton created by AME Submodel editing utility
   ?? ??? 14 10:09:02 2022 */



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

#define _SUBMODELNAME_ "SMO_PIPE_STRAIGHT_HEAT_EXCHANGER_RCR_REGULATING_DP_GAIN"

/* >>>>>>>>>>>>Insert Private Code Here. */
#include "SmoFlowAme.h"
#include "volumes/PipeHeatExchPrDropMassAcc_RCR.h"

#define _port1FluidFlow ps[0]
#define _port1FluidFlowIndex ic[0]

#define _port3FluidFlow ps[1]
#define _port3FluidFlowIndex ic[1]

#define _wallHeatFlow ps[2]
#define _wallHeatFlowIndex ic[2]

#define _port1FluidStateIndex

#define _internalFluidState ps[3]
#define _friction1 ps[4]
#define _friction3 ps[5]
#define _convection ps[6]
#define _component ps[7]
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


/* There are 7 integer parameters:

   fluidIndex                   fluid index                       
   allowBidirectionalFlow       allow bi-directional flow         
   geometryType                 geometry type                     
   forcedConvectionUseFilmState use film state (forced convection)
   useFluidFlowActivationSignal use fluid flow activation signal  
   initConditionsChoice         type of initialization            
   stateVariableSelection       states variables                  
*/

void smo_pipe_straight_heat_exchanger_rcr_regulating_dp_gainin_(int *n
      , double rp[12], int ip[7], int ic[3], void *ps[8]
      , double stateValues[2])

{
   int loop, error;
/* >>>>>>>>>>>>Extra Initialization Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Initialization declarations. */
   int fluidIndex, allowBidirectionalFlow, geometryType, 
      forcedConvectionUseFilmState, useFluidFlowActivationSignal, 
      initConditionsChoice, stateVariableSelection;
   double hydraulicDiameter, pipeLength, flowArea, absoluteRoughness, 
      pressureDropGainConst, heatExchangeGain, 
      heatExchangeGainDeactivedFlow, initialPressure, 
      initialTemperature, initialTemperatureC, initialGasMassFraction
      , initialSuperheat;

   fluidIndex = ip[0];
   allowBidirectionalFlow = ip[1];
   geometryType = ip[2];
   forcedConvectionUseFilmState = ip[3];
   useFluidFlowActivationSignal = ip[4];
   initConditionsChoice = ip[5];
   stateVariableSelection = ip[6];

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
   if (useFluidFlowActivationSignal < 1 || useFluidFlowActivationSignal > 2)
   {
      amefprintf(stderr, "\nuse fluid flow activation signal must be in range [1..2].\n");
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
   _friction1 = FrictionFlowPipe_StraightPipe_new(pipeLength/2., hydraulicDiameter, flowAreaValue, absoluteRoughness);
   _friction3 = FrictionFlowPipe_StraightPipe_new(pipeLength/2., hydraulicDiameter, flowAreaValue, absoluteRoughness);
   _convection = ForcedConvection_StraightPipe_new(pipeLength, hydraulicDiameter, flowAreaValue);

   Convection_setHeatExchangeGain(_convection, heatExchangeGain);
   Convection_setUseFilmState(_convection, forcedConvectionUseFilmState - 1); //:TRICKY: (0-no, 1-yes)
   ForcedConvection_setLimitOutput(_convection, 1); //:TRICKY: (0-no, 1-yes)

   double internalVolume = flowAreaValue * pipeLength;
   _component = PipeHeatExchPrDropMassAcc_RCR_new(
		   allowBidirectionalFlow - 1, //:TRICKY: allowBidirectionalFlow =  '{1-no, 2-yes} - 1'  =  '{0-no, 1-yes}'
		   internalVolume,
		   _friction1, _friction3,
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
   PipeHeatExchPrDropMassAcc_RCR_initInternalState(_component, fluid, stateVariableSelection, internalStateInitialValues);

   _internalFluidState = PipeHeatExchPrDropMassAcc_RCR_getInternalFluidState(_component);
   PipeHeatExchPrDropMassAcc_RCR_getStateValues(_component, &stateValues[0], &stateValues[1]);
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

/*  There are 4 ports.

   Port 1 has 3 variables:

      1 port1FluidFlowIndex            fluid flow index at port1             [smoFFL]  basic variable output  UNPLOTTABLE
      2 fluidFlowActivationSignal1     fluid flow activation signal at port1 [smoFFAS] basic variable output
      3 port1FluidStateIndex           fluid state index at port1            [smoTDS]  basic variable input  UNPLOTTABLE

   Port 2 has 2 variables:

      1 heatFlowIndex        heat flow index    [smoHFL] basic variable output  UNPLOTTABLE
      2 thermalNodeIndex     thermal node index [smoTHN] basic variable input  UNPLOTTABLE

   Port 3 has 3 variables:

      1 port3FluidFlowIndex            fluid flow index at port3             [smoFFL]  basic variable output  UNPLOTTABLE
      2 fluidFlowActivationSignal3     fluid flow activation signal at port3 [smoFFAS] basic variable output
      3 port3FluidStateIndex           fluid state index at port3            [smoTDS]  basic variable input  UNPLOTTABLE

   Port 4 has 1 variable:

      1 pressureDropGainRegSignal     pressure drop gain (regulated signal) [null] basic variable input
*/

/*  There are 22 internal variables.

      1 pressureLossTotal         total pressure loss                       [bar -> Pa]   basic variable
      2 stateValues[2]            state values                              [null]        explicit state (derivative `stateValuesDot')
      3 internalPressure          fluid pressure                            [barA -> PaA] basic variable
      4 internalTemperatrue       fluid temperature                         [K]           basic variable
      5 internalDensity           fluid density                             [[kg/m**3]]   basic variable
      6 internalVolume            fluid volume                              [L -> m**3]   basic variable
      7 mass                      fluid mass in the pipe                    [kg]          basic variable
      8 massFlowRate1             mass flow rate at port1                   [kg/s]        basic variable
      9 massFlowRate3             mass flow rate at port3                   [kg/s]        basic variable
     10 enthalpyFlowRate1         enthalpy flow rate at port1               [W]           basic variable
     11 enthalpyFlowRate3         enthalpy flow rate at port3               [W]           basic variable
     12 pressureLoss1             pressure loss at port1                    [bar -> Pa]   basic variable
     13 pressureLoss3             pressure loss at port3                    [bar -> Pa]   basic variable
     14 dynamicPressureUp1        dynamic pressure (upstream flow) at port1 [barA -> PaA] basic variable
     15 dynamicPressureUp3        dynamic pressure (upstream flow) at port3 [barA -> PaA] basic variable
     16 vFlowUp1                  velocity (upstream flow) at port1         [m/s]         basic variable
     17 vFlowUp3                  velocity (upstream flow) at port3         [m/s]         basic variable
     18 machNumberUp1             Mach number (upstream flow) at port1      [null]        basic variable
     19 machNumberUp3             Mach number (upstream flow) at port3      [null]        basic variable
     20 reynoldsNumber            Reynolds number                           [null]        basic variable
     21 convectionCoefficient     convection coefficient                    [W/m**2/K]    basic variable
     22 heatFlowRateFromWall      heat flow rate                            [W]           basic variable
*/

void smo_pipe_straight_heat_exchanger_rcr_regulating_dp_gain_(int *n
      , double *port1FluidFlowIndex
      , double *fluidFlowActivationSignal1
      , double *port1FluidStateIndex, double *heatFlowIndex
      , double *thermalNodeIndex, double *port3FluidFlowIndex
      , double *fluidFlowActivationSignal3
      , double *port3FluidStateIndex
      , double *pressureDropGainRegSignal, double *pressureLossTotal
      , double stateValues[2], double stateValuesDot[2]
      , double *internalPressure, double *internalTemperatrue
      , double *internalDensity, double *internalVolume, double *mass
      , double *massFlowRate1, double *massFlowRate3
      , double *enthalpyFlowRate1, double *enthalpyFlowRate3
      , double *pressureLoss1, double *pressureLoss3
      , double *dynamicPressureUp1, double *dynamicPressureUp3
      , double *vFlowUp1, double *vFlowUp3, double *machNumberUp1
      , double *machNumberUp3, double *reynoldsNumber
      , double *convectionCoefficient, double *heatFlowRateFromWall
      , double rp[12], int ip[7], int ic[3], void *ps[8], int *flag)

{
   int loop, logi;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   int fluidIndex, allowBidirectionalFlow, geometryType, 
      forcedConvectionUseFilmState, useFluidFlowActivationSignal, 
      initConditionsChoice, stateVariableSelection;
   double hydraulicDiameter, pipeLength, flowArea, absoluteRoughness, 
      pressureDropGainConst, heatExchangeGain, 
      heatExchangeGainDeactivedFlow, initialPressure, 
      initialTemperature, initialTemperatureC, initialGasMassFraction
      , initialSuperheat;

   fluidIndex = ip[0];
   allowBidirectionalFlow = ip[1];
   geometryType = ip[2];
   forcedConvectionUseFilmState = ip[3];
   useFluidFlowActivationSignal = ip[4];
   initConditionsChoice = ip[5];
   stateVariableSelection = ip[6];

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

/*
   Set all submodel outputs below:

   *port1FluidFlowIndex = ??;
   *fluidFlowActivationSignal1 = ??;
   *heatFlowIndex = ??;
   *port3FluidFlowIndex = ??;
   *fluidFlowActivationSignal3 = ??;
   *pressureLossTotal = ??;
   stateValuesDot[0..1] = ??;
   *internalPressure = ??;
   *internalTemperatrue = ??;
   *internalDensity = ??;
   *internalVolume = ??;
   *mass       = ??;
   *massFlowRate1 = ??;
   *massFlowRate3 = ??;
   *enthalpyFlowRate1 = ??;
   *enthalpyFlowRate3 = ??;
   *pressureLoss1 = ??;
   *pressureLoss3 = ??;
   *dynamicPressureUp1 = ??;
   *dynamicPressureUp3 = ??;
   *vFlowUp1   = ??;
   *vFlowUp3   = ??;
   *machNumberUp1 = ??;
   *machNumberUp3 = ??;
   *reynoldsNumber = ??;
   *convectionCoefficient = ??;
   *heatFlowRateFromWall = ??;
*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
   SMOCOMPONENT_PRINT_MAIN_CALC
   if (firstc_()) {
	   MediumState* port1FluidState = MediumState_get(*port1FluidStateIndex);
	   MediumState* port3FluidState = MediumState_get(*port3FluidStateIndex);
	   ThermalNode* wallNode = ThermalNode_get(*thermalNodeIndex);

	   PipeHeatExchPrDropMassAcc_RCR_initOuterStates(_component, port1FluidState, port3FluidState, wallNode);
	   PipeHeatExchPrDropMassAcc_RCR_init(_component);

	   _port1FluidFlow = PipeHeatExchPrDropMassAcc_RCR_getPort1Flow(_component);
	   _port1FluidFlowIndex = SmoObject_getInstanceIndex(_port1FluidFlow);

	   _port3FluidFlow = PipeHeatExchPrDropMassAcc_RCR_getPort2Flow(_component);
	   _port3FluidFlowIndex = SmoObject_getInstanceIndex(_port3FluidFlow);

	   _wallHeatFlow = PipeHeatExchPrDropMassAcc_RCR_getWallHeatFlow(_component);
	   _wallHeatFlowIndex = SmoObject_getInstanceIndex(_wallHeatFlow);
   }

   PipeHeatExchPrDropMassAcc_RCR_setStateValues(_component, stateValues[0], stateValues[1]);

   double pressureDropGainTotal = (*pressureDropGainRegSignal) * pressureDropGainConst;
   FrictionFlowPipe_setPressureDropGain(_friction1, pressureDropGainTotal);
   FrictionFlowPipe_setPressureDropGain(_friction3, pressureDropGainTotal);
   if (*pressureDropGainRegSignal <= 0) { //no flow
	   Convection_setHeatExchangeGain(_convection, heatExchangeGainDeactivedFlow);
	   PipeHeatExchPrDropMassAcc_RCR_compute_deactivedFluidFlow(_component);
   } else {
	   Convection_setHeatExchangeGain(_convection, heatExchangeGain);
	   PipeHeatExchPrDropMassAcc_RCR_compute(_component);
   }

   *port1FluidFlowIndex = _port1FluidFlowIndex;
   *port3FluidFlowIndex = _port3FluidFlowIndex;
   *heatFlowIndex = _wallHeatFlowIndex;

   PipeHeatExchPrDropMassAcc_RCR_getStateDerivatives(_component, &stateValuesDot[0], &stateValuesDot[1]);

   *internalPressure = MediumState_p(_internalFluidState);
   *internalTemperatrue = MediumState_T(_internalFluidState);
   *internalDensity = MediumState_rho(_internalFluidState);
   *internalVolume = PipeHeatExchPrDropMassAcc_RCR_getVolume(_component);
   *mass = PipeHeatExchPrDropMassAcc_RCR_getFluidMass(_component);

   *reynoldsNumber = ForcedConvection_getReynoldsNumber(_convection);
   *convectionCoefficient = Convection_getConvectionCoefficient(_convection);
   *heatFlowRateFromWall = -HeatFlow_getEnthalpyFlowRate(_wallHeatFlow);

   *massFlowRate1 = FluidFlow_getMassFlowRate(_port1FluidFlow);
   *enthalpyFlowRate1 = FluidFlow_getEnthalpyFlowRate(_port1FluidFlow);
   *vFlowUp1 = FrictionFlowPipe_getUpstreamVelocity(_friction1, *massFlowRate1);
   *dynamicPressureUp1 = FrictionFlowPipe_getUpstreamDynamicPressure(_friction1, *massFlowRate1);
   *machNumberUp1 = FrictionFlowPipe_getUpstreamMachNumber(_friction1, *massFlowRate1);

   *massFlowRate3 = FluidFlow_getMassFlowRate(_port3FluidFlow);
   *enthalpyFlowRate3 = FluidFlow_getEnthalpyFlowRate(_port3FluidFlow);
   *vFlowUp3 = FrictionFlowPipe_getUpstreamVelocity(_friction3, *massFlowRate3);
   *dynamicPressureUp3 = FrictionFlowPipe_getUpstreamDynamicPressure(_friction3, *massFlowRate3);
   *machNumberUp3 = FrictionFlowPipe_getUpstreamMachNumber(_friction3, *massFlowRate3);

   *pressureLoss1 = FrictionFlowPipe_getAbsolutePressureDrop(_friction1);
   *pressureLoss3 = FrictionFlowPipe_getAbsolutePressureDrop(_friction3);
   *pressureLossTotal = *pressureLoss1 + *pressureLoss3;

   if (useFluidFlowActivationSignal == 1) { //no
	   *fluidFlowActivationSignal1 = -1; //not used
	   *fluidFlowActivationSignal3 = -1; //not used
   } else { // yes
	   if (*massFlowRate1 == 0) {
		   *fluidFlowActivationSignal1 = 0; //deactivate flow
	   } else {
		   *fluidFlowActivationSignal1 = 1; //activate flow
	   }

	   if (*massFlowRate3 == 0) {
		   *fluidFlowActivationSignal3 = 0; //deactivate flow
	   } else {
	   	   *fluidFlowActivationSignal3 = 1; //activate flow
	   }
   }
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *port1FluidFlowIndex /= ??; CONVERSION UNKNOWN [smoFFL] */
/*   *fluidFlowActivationSignal1 /= ??; CONVERSION UNKNOWN [smoFFAS] */
/*   *port1FluidStateIndex /= ??; CONVERSION UNKNOWN [smoTDS] */
/*   *heatFlowIndex /= ??; CONVERSION UNKNOWN [smoHFL] */
/*   *thermalNodeIndex /= ??; CONVERSION UNKNOWN [smoTHN] */
/*   *port3FluidFlowIndex /= ??; CONVERSION UNKNOWN [smoFFL] */
/*   *fluidFlowActivationSignal3 /= ??; CONVERSION UNKNOWN [smoFFAS] */
/*   *port3FluidStateIndex /= ??; CONVERSION UNKNOWN [smoTDS] */
   *pressureLossTotal /= 1.00000000000000e+05;
   *internalPressure /= 1.00000000000000e+05;
/*   *internalDensity /= ??; CONVERSION UNKNOWN [[kg/m**3]] */
   *internalVolume /= 1.00000000000000e-03;
   *pressureLoss1 /= 1.00000000000000e+05;
   *pressureLoss3 /= 1.00000000000000e+05;
   *dynamicPressureUp1 /= 1.00000000000000e+05;
   *dynamicPressureUp3 /= 1.00000000000000e+05;
}

