/* Submodel SMO_PIPE_STRAIGHT_HEAT_EXCHANGER_C skeleton created by AME Submodel editing utility
   Thu Feb 9 10:56:42 2017 */



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

#define _SUBMODELNAME_ "SMO_PIPE_STRAIGHT_HEAT_EXCHANGER_C"

/* >>>>>>>>>>>>Insert Private Code Here. */
#include "SmoFlowAme.h"
#include "volumes/PipeHeatExchNoPrDropMassAcc_C.h"
 
#define _wallHeatFlow ps[0]
#define _wallHeatFlowIndex ic[0]
 
#define _pipeState ps[1]
#define _pipeStateIndex ic[1]
 
#define _convection ps[2]
#define _component ps[3]
/* <<<<<<<<<<<<End of Private Code. */


/* There are 11 real parameters:

   hydraulicDiameter      hydraulic diameter                                      [mm -> m]
   pipeLength             pipe length                                             [m]
   flowArea               flow (cross sectional) area                             [mm**2 -> m**2]
   heatExchangeGain       heat exchange gain                                      [null]
   initialPressure        initial pressure                                        [barA -> PaA]
   initialTemperature     initial temperature (K)                                 [K]
   initialTemperatureC    initial temperature (°C)                                [degC]
   initialGasMassFraction initial gas mass fraction                               [null]
   initialSuperheat       initial superheat                                       [K]
   ReL                    laminar to turbulent transition:  lower Reynolds number [null]
   ReH                    laminar to turbulent transition:  upper Reynolds number [null]
*/


/* There are 6 integer parameters:

   fluidIndex                   fluid index                       
   convCalcMethod               convection calculation method     
   geometryType                 geometry type                     
   forcedConvectionUseFilmState use film state (forced convection)
   initConditionsChoice         type of initialization            
   stateVariableSelection       states variables                  
*/


/* There are 2 text parameters:

   nusseltExpressionLaminarFlow   nusselt correlation expression Nu=f(Re, Pr) in laminar flow  
   nusseltExpressionTurbulentFlow nusselt correlation expression Nu=f(Re, Pr) in turbulent flow
*/

void smo_pipe_straight_heat_exchanger_cin_(int *n, double rp[11]
      , int ip[6], char *tp[2], int ic[2], void *ps[4]
      , double stateValues[2])

{
   int loop, error;
/* >>>>>>>>>>>>Extra Initialization Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Initialization declarations. */
   int fluidIndex, convCalcMethod, geometryType, 
      forcedConvectionUseFilmState, initConditionsChoice, 
      stateVariableSelection;
   double hydraulicDiameter, pipeLength, flowArea, heatExchangeGain, 
      initialPressure, initialTemperature, initialTemperatureC, 
      initialGasMassFraction, initialSuperheat, ReL, ReH;
   char *nusseltExpressionLaminarFlow, *nusseltExpressionTurbulentFlow;

   fluidIndex = ip[0];
   convCalcMethod = ip[1];
   geometryType = ip[2];
   forcedConvectionUseFilmState = ip[3];
   initConditionsChoice = ip[4];
   stateVariableSelection = ip[5];

   hydraulicDiameter = rp[0];
   pipeLength = rp[1];
   flowArea   = rp[2];
   heatExchangeGain = rp[3];
   initialPressure = rp[4];
   initialTemperature = rp[5];
   initialTemperatureC = rp[6];
   initialGasMassFraction = rp[7];
   initialSuperheat = rp[8];
   ReL        = rp[9];
   ReH        = rp[10];

   nusseltExpressionLaminarFlow = tp[0];
   nusseltExpressionTurbulentFlow = tp[1];
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

   if (fluidIndex < 1 || fluidIndex > 99)
   {
      amefprintf(stderr, "\nfluid index must be in range [1..99].\n");
      error = 2;
   }
   if (convCalcMethod < 1 || convCalcMethod > 2)
   {
      amefprintf(stderr, "\nconvection calculation method must be in range [1..2].\n");
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
   rp[4]    *= 1.00000000000000e+005;
   initialPressure = rp[4];


/* >>>>>>>>>>>>Initialization Function Executable Statements. */
   double flowAreaValue;
   if (geometryType == 1) { //cylindrical pipe
	   flowAreaValue = M_PI * hydraulicDiameter * hydraulicDiameter / 4.;
   } else { //non-cylindrical pipe
	   flowAreaValue = flowArea;
   }
 
   if (convCalcMethod == 1) { //default expression for Nuselt number
	   _convection = ForcedConvection_StraightPipe_new(pipeLength, hydraulicDiameter, flowAreaValue);
   } else { //user expression for Nuselt number
		_convection = ForcedConvection_StraightPipe_NusseltExpression_new(pipeLength, hydraulicDiameter, flowAreaValue,
				nusseltExpressionLaminarFlow, nusseltExpressionTurbulentFlow, ReL, ReH);
   }
 
   Convection_setHeatExchangeGain(_convection, heatExchangeGain);
   Convection_setUseFilmState(_convection, forcedConvectionUseFilmState - 1); //:TRICKY: (0-no, 1-yes)
 
   double internalVolume = flowAreaValue * pipeLength;
   Medium* fluid = Medium_get(fluidIndex);
   _component = PipeHeatExchNoPrDropMassAcc_C_new(fluid, internalVolume, _convection, stateVariableSelection);
   SMOCOMPONENT_SET_PROPS(_component)
 
   _pipeState = PipeHeatExchNoPrDropMassAcc_C_getFluidState(_component);
   _pipeStateIndex = SmoObject_getInstanceIndex(_pipeState);
 
 
   if (initConditionsChoice == 1) {
 	   MediumState_update_Tp(_pipeState, initialTemperature, initialPressure);
    } else if (initConditionsChoice == 2) {
 	   MediumState_update_Tp(_pipeState, initialTemperatureC + 273.15, initialPressure);
    } else if (initConditionsChoice == 3) {
    	   MediumState_update_pq(_pipeState, initialPressure, initialGasMassFraction);
    } else {
 	   AME_RAISE_ERROR("Unsupported type of initialization.")
    }
 
   PipeHeatExchNoPrDropMassAcc_C_getStateValues(_component, &stateValues[0], &stateValues[1]);
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

/*  There are 3 ports.

   Port 1 has 3 variables:

      1 port1FluidStateIndex           fluid state index outlet             [smoTDS]  multi line macro 'smo_pipe_straight_heat_exchanger_c_macro0_'  UNPLOTTABLE
      2 port1FluidFlowIndex            fluid flow index at port 1           [smoFFL]  basic variable input  UNPLOTTABLE
      3 fluidFlowActivationSignal1     fluid flow activation signal (port1) [smoFFAS] basic variable input  UNPLOTTABLE

   Port 2 has 2 variables:

      1 heatFlowIndex        heat flow index    [smoHFL] basic variable output  UNPLOTTABLE
      2 thermalNodeIndex     thermal node index [smoTHN] basic variable input  UNPLOTTABLE

   Port 3 has 3 variables:

      1 port3FluidStateIndexDupl       duplicate of port1FluidStateIndex   
      2 port3FluidFlowIndex            fluid flow index at port 3           [smoFFL]  basic variable input  UNPLOTTABLE
      3 fluidFlowActivationSignal3     fluid flow activation signal (port3) [smoFFAS] basic variable input  UNPLOTTABLE
*/

/*  There are 11 internal variables.

      1 pressure                  pressure               [bar -> Pa]     basic variable
      2 temperature               temperature            [K]             basic variable
      3 density                   density                [kg/m**3]       basic variable
      4 specificEnthalpy          specific enthalpy      [kJ/kg -> J/kg] basic variable
      5 gasMassFraction           gas mass fraction      [null]          basic variable
      6 superHeat                 subcooling / superheat [degC]          basic variable
      7 internalVolume            volume                 [L -> m**3]     basic variable
      8 stateValues[2]            state values           [null]          explicit state (derivative `stateValuesDot')
      9 reynoldsNumber            Reynolds number        [null]          basic variable
     10 convectionCoefficient     convection coefficient [W/m**2/K]      basic variable
     11 heatFlowRateFromWall      heat flow rate         [W]             basic variable
*/

void smo_pipe_straight_heat_exchanger_c_(int *n
      , double *port1FluidStateIndex, double *port1FluidFlowIndex
      , double *fluidFlowActivationSignal1, double *heatFlowIndex
      , double *thermalNodeIndex, double *port3FluidFlowIndex
      , double *fluidFlowActivationSignal3, double *pressure
      , double *temperature, double *density, double *specificEnthalpy
      , double *gasMassFraction, double *superHeat
      , double *internalVolume, double stateValues[2]
      , double stateValuesDot[2], double *reynoldsNumber
      , double *convectionCoefficient, double *heatFlowRateFromWall
      , double rp[11], int ip[6], char *tp[2], int ic[2], void *ps[4]
      , int *flag)

{
   int loop, logi;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   int fluidIndex, convCalcMethod, geometryType, 
      forcedConvectionUseFilmState, initConditionsChoice, 
      stateVariableSelection;
   double hydraulicDiameter, pipeLength, flowArea, heatExchangeGain, 
      initialPressure, initialTemperature, initialTemperatureC, 
      initialGasMassFraction, initialSuperheat, ReL, ReH;
   char *nusseltExpressionLaminarFlow, *nusseltExpressionTurbulentFlow;

   fluidIndex = ip[0];
   convCalcMethod = ip[1];
   geometryType = ip[2];
   forcedConvectionUseFilmState = ip[3];
   initConditionsChoice = ip[4];
   stateVariableSelection = ip[5];

   hydraulicDiameter = rp[0];
   pipeLength = rp[1];
   flowArea   = rp[2];
   heatExchangeGain = rp[3];
   initialPressure = rp[4];
   initialTemperature = rp[5];
   initialTemperatureC = rp[6];
   initialGasMassFraction = rp[7];
   initialSuperheat = rp[8];
   ReL        = rp[9];
   ReH        = rp[10];

   nusseltExpressionLaminarFlow = tp[0];
   nusseltExpressionTurbulentFlow = tp[1];
   logi = 0;
   loop = 0;

/* Common -> SI units conversions. */

/*   *port1FluidStateIndex *= ??; CONVERSION UNKNOWN [smoTDS] */
/*   *port1FluidFlowIndex *= ??; CONVERSION UNKNOWN [smoFFL] */
/*   *fluidFlowActivationSignal1 *= ??; CONVERSION UNKNOWN [smoFFAS] */
/*   *thermalNodeIndex *= ??; CONVERSION UNKNOWN [smoTHN] */
/*   *port3FluidFlowIndex *= ??; CONVERSION UNKNOWN [smoFFL] */
/*   *fluidFlowActivationSignal3 *= ??; CONVERSION UNKNOWN [smoFFAS] */

/*
   Set all submodel outputs below:

   *heatFlowIndex = ??;
   *pressure   = ??;
   *temperature = ??;
   *density    = ??;
   *specificEnthalpy = ??;
   *gasMassFraction = ??;
   *superHeat  = ??;
   *internalVolume = ??;
   stateValuesDot[0..1] = ??;
   *reynoldsNumber = ??;
   *convectionCoefficient = ??;
   *heatFlowRateFromWall = ??;
*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
   SMOCOMPONENT_PRINT_MAIN_CALC
   if (firstc_()) {
	   FluidFlow* port1Flow = FluidFlow_get(*port1FluidFlowIndex);
	   FluidFlow* port3Flow = FluidFlow_get(*port3FluidFlowIndex);
	   PipeHeatExchNoPrDropMassAcc_C_init(_component, port1Flow, port3Flow);
 
	   _wallHeatFlow = PipeHeatExchNoPrDropMassAcc_C_getWallHeatFlow(_component);
	   _wallHeatFlowIndex = SmoObject_getInstanceIndex(_wallHeatFlow);
   }
 
   PipeHeatExchNoPrDropMassAcc_C_compute(_component);
   PipeHeatExchNoPrDropMassAcc_C_getStateDerivatives(_component, &stateValuesDot[0], &stateValuesDot[1]);
 
   *heatFlowIndex = _wallHeatFlowIndex;
   *reynoldsNumber = ForcedConvection_getReynoldsNumber(_convection);
   *convectionCoefficient = Convection_getConvectionCoefficient(_convection);
   *heatFlowRateFromWall = -HeatFlow_getEnthalpyFlowRate(_wallHeatFlow);
 
   *pressure = MediumState_p(_pipeState);
   *temperature = MediumState_T(_pipeState);
   *density = MediumState_rho(_pipeState);
   *specificEnthalpy = MediumState_h(_pipeState);
   *gasMassFraction = MediumState_q(_pipeState);
   *superHeat  = MediumState_deltaTSat(_pipeState);
   *internalVolume = PipeHeatExchNoPrDropMassAcc_C_getVolume(_component);
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *port1FluidStateIndex /= ??; CONVERSION UNKNOWN [smoTDS] */
/*   *port1FluidFlowIndex /= ??; CONVERSION UNKNOWN [smoFFL] */
/*   *fluidFlowActivationSignal1 /= ??; CONVERSION UNKNOWN [smoFFAS] */
/*   *heatFlowIndex /= ??; CONVERSION UNKNOWN [smoHFL] */
/*   *thermalNodeIndex /= ??; CONVERSION UNKNOWN [smoTHN] */
/*   *port3FluidFlowIndex /= ??; CONVERSION UNKNOWN [smoFFL] */
/*   *fluidFlowActivationSignal3 /= ??; CONVERSION UNKNOWN [smoFFAS] */
   *pressure /= 1.00000000000000e+005;
   *specificEnthalpy /= 1.00000000000000e+003;
   *internalVolume /= 1.00000000000000e-003;
}

extern double smo_pipe_straight_heat_exchanger_c_macro0_(int *n
      , double *thermalNodeIndex, double stateValues[2], double rp[11]
      , int ip[6], char *tp[2], int ic[2], void *ps[4], int *flag)

{
   double port1FluidStateIndex;
   int loop, logi;
/* >>>>>>>>>>>>Extra Macro Function macro0 Declarations Here. */
/* <<<<<<<<<<<<End of Extra Macro macro0 declarations. */
   int fluidIndex, convCalcMethod, geometryType, 
      forcedConvectionUseFilmState, initConditionsChoice, 
      stateVariableSelection;
   double hydraulicDiameter, pipeLength, flowArea, heatExchangeGain, 
      initialPressure, initialTemperature, initialTemperatureC, 
      initialGasMassFraction, initialSuperheat, ReL, ReH;
   char *nusseltExpressionLaminarFlow, *nusseltExpressionTurbulentFlow;

   fluidIndex = ip[0];
   convCalcMethod = ip[1];
   geometryType = ip[2];
   forcedConvectionUseFilmState = ip[3];
   initConditionsChoice = ip[4];
   stateVariableSelection = ip[5];

   hydraulicDiameter = rp[0];
   pipeLength = rp[1];
   flowArea   = rp[2];
   heatExchangeGain = rp[3];
   initialPressure = rp[4];
   initialTemperature = rp[5];
   initialTemperatureC = rp[6];
   initialGasMassFraction = rp[7];
   initialSuperheat = rp[8];
   ReL        = rp[9];
   ReH        = rp[10];

   nusseltExpressionLaminarFlow = tp[0];
   nusseltExpressionTurbulentFlow = tp[1];
   logi = 0;
   loop = 0;

/* Common -> SI units conversions. */

/*   *thermalNodeIndex *= ??; CONVERSION UNKNOWN [smoTHN] */

/*
   Define and return the following macro variable:

   port1FluidStateIndex = ??;
*/


/* >>>>>>>>>>>>Macro Function macro0 Executable Statements. */
   SMOCOMPONENt_PRINT_MACRO
   if (firstc_()) {
	   ThermalNode* wallNode = ThermalNode_get(*thermalNodeIndex);
	   PipeHeatExchNoPrDropMassAcc_C_setWallNode(_component, wallNode);
   }
 
   PipeHeatExchNoPrDropMassAcc_C_setStateValues(_component, stateValues[0], stateValues[1]);
   port1FluidStateIndex = _pipeStateIndex;
/* <<<<<<<<<<<<End of Macro macro0 Executable Statements. */

/* SI -> Common units conversions. */

/*   *thermalNodeIndex /= ??; CONVERSION UNKNOWN [smoTHN] */

/*   *port1FluidStateIndex /= ??; CONVERSION UNKNOWN [smoTDS] */

   return port1FluidStateIndex;
}

