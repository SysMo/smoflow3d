/* Submodel SMO_TANK skeleton created by AME Submodel editing utility
   Tue Feb 7 16:05:20 2017 */



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

#define _SUBMODELNAME_ "SMO_TANK"

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


/* There are 12 real parameters:

   initialPressure           initial pressure                                [barA -> PaA]
   initialTemperature        initial temperature (K)                         [K]
   initialTemperatureC       initial temperature (�C)                        [degC]
   initialGasMassFraction    initial gas mass fraction                       [null]
   initialSuperheat          initial superheat                               [K]
   volume                    volume                                          [L -> m**3]
   hydraulicDiameter         hydraulic diameter                              [mm -> m]
   pipeLength                pipe length                                     [m]
   heatExchangeGain          heat exchange gain                              [null]
   ReL                       critical Reynolds number (end laminar flow)     [null]
   ReH                       critical Reynolds number (start turbulent flow) [null]
   hydraulicDiameterInjector hydraulic diameter of the injector              [mm -> m]
*/


/* There are 4 integer parameters:

   fluidIndex                   fluid index                                                          
   initConditionsChoice         type of initialization                                               
   stateVariableSelection       states variables                                                     
   forcedConvectionUseFilmState use film state for the forced convection; T_film = (T_wall+T_fluid)/2
*/


/* There are 2 text parameters:

   nusseltExpressionLaminarFlow   nusselt correlation expression Nu=f(Re, Pr) - laminar flow  
   nusseltExpressionTurbulentFlow nusselt correlation expression Nu=f(Re, Pr) - turbulent flow
*/

void smo_tankin_(int *n, double rp[12], int ip[4], char *tp[2]
      , int ic[2], void *ps[6], double stateValues[2])

{
   int loop, error;
/* >>>>>>>>>>>>Extra Initialization Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Initialization declarations. */
   int fluidIndex, initConditionsChoice, stateVariableSelection, 
      forcedConvectionUseFilmState;
   double initialPressure, initialTemperature, initialTemperatureC, 
      initialGasMassFraction, initialSuperheat, volume, 
      hydraulicDiameter, pipeLength, heatExchangeGain, ReL, ReH, 
      hydraulicDiameterInjector;
   char *nusseltExpressionLaminarFlow, *nusseltExpressionTurbulentFlow;

   fluidIndex = ip[0];
   initConditionsChoice = ip[1];
   stateVariableSelection = ip[2];
   forcedConvectionUseFilmState = ip[3];

   initialPressure = rp[0];
   initialTemperature = rp[1];
   initialTemperatureC = rp[2];
   initialGasMassFraction = rp[3];
   initialSuperheat = rp[4];
   volume     = rp[5];
   hydraulicDiameter = rp[6];
   pipeLength = rp[7];
   heatExchangeGain = rp[8];
   ReL        = rp[9];
   ReH        = rp[10];
   hydraulicDiameterInjector = rp[11];

   nusseltExpressionLaminarFlow = tp[0];
   nusseltExpressionTurbulentFlow = tp[1];
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
   if (forcedConvectionUseFilmState < 1 || forcedConvectionUseFilmState > 2)
   {
      amefprintf(stderr, "\nuse film state for the forced convection; T_film = (T_wall+T_fluid)/2 must be in range [1..2].\n");
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

   rp[0]    *= 1.00000000000000e+005;
   initialPressure = rp[0];
   rp[5]    *= 1.00000000000000e-003;
   volume     = rp[5];
   rp[6]    *= 1.00000000000000e-003;
   hydraulicDiameter = rp[6];
   rp[11]   *= 1.00000000000000e-003;
   hydraulicDiameterInjector = rp[11];


/* >>>>>>>>>>>>Initialization Function Executable Statements. */
   double flowAreaValue;
   flowAreaValue = M_PI / 4 * hydraulicDiameter * hydraulicDiameter;

   _convection = ForcedConvection_StraightPipe_NusseltExpression_new(pipeLength,
		   hydraulicDiameter, flowAreaValue,
		   nusseltExpressionLaminarFlow, nusseltExpressionTurbulentFlow, ReL, ReH);

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

/*  There are 4 ports.

   Port 1 has 3 variables:

      1 fluidStateIndex                fluid state index                                                 [smoTDS]  multi line macro 'smo_tank_macro0_'  UNPLOTTABLE
      2 fluidFlow1Index                fluid flow index (port1); (connection with the fueling subsystem) [smoFFL]  basic variable input  UNPLOTTABLE
      3 fluidFlowActivationSignal1     fluid flow activation signal (port1)                              [smoFFAS] basic variable input  UNPLOTTABLE

   Port 2 has 2 variables:

      1 heatFlowIndex        heat flow index (port2)                                       [smoHFL] basic variable output  UNPLOTTABLE
      2 thermalNodeIndex     thermal node index (port2); (connection with the tank's wall) [smoTHN] basic variable input  UNPLOTTABLE

   Port 3 has 3 variables:

      1 fluidStateIndexDup3            duplicate of fluidStateIndex                                      
      2 fluidFlow3Index                outlet fluid flow (port3); (connect with the extraction subsystem) [smoFFL]  basic variable input  UNPLOTTABLE
      3 fluidFlowActivationSignal3     fluid flow activation signal (port3)                               [smoFFAS] basic variable input  UNPLOTTABLE

   Port 4 has 3 variables:

      1 fluidStateIndexDup4            duplicate of fluidStateIndex                                           
      2 fluidFlow4Index                fluid flow index (port4); (use it for a additional heat/fluid exchange) [smoFFL]  basic variable input  UNPLOTTABLE
      3 fluidFlowActivationSignal4     fluid flow activation signal (port4)                                    [smoFFAS] basic variable input  UNPLOTTABLE
*/

/*  There are 11 internal variables.

      1 pressure                  pressure                    [bar -> Pa]     basic variable
      2 temperature               temperature                 [K]             basic variable
      3 density                   density                     [kg/m**3]       basic variable
      4 specificEnthalpy          specific enthalpy           [kJ/kg -> J/kg] basic variable
      5 gasMassFraction           gas mass fraction           [null]          basic variable
      6 superHeat                 subcooling / superheat      [degC]          basic variable
      7 totalMass                 mass in chamber             [kg]            basic variable
      8 stateValues[2]            state values                [null]          explicit state (derivative `stateValuesDot')
      9 reynoldsNumber            Reynolds number             [null]          basic variable
     10 convectionCoefficient     convection coefficient      [W/m**2/K]      basic variable
     11 heatFlowRateFromWall      heat flow rate fom the wall [W]             basic variable
*/

void smo_tank_(int *n, double *fluidStateIndex
      , double *fluidFlow1Index, double *fluidFlowActivationSignal1
      , double *heatFlowIndex, double *thermalNodeIndex
      , double *fluidFlow3Index, double *fluidFlowActivationSignal3
      , double *fluidFlow4Index, double *fluidFlowActivationSignal4
      , double *pressure, double *temperature, double *density
      , double *specificEnthalpy, double *gasMassFraction
      , double *superHeat, double *totalMass, double stateValues[2]
      , double stateValuesDot[2], double *reynoldsNumber
      , double *convectionCoefficient, double *heatFlowRateFromWall
      , double rp[12], int ip[4], char *tp[2], int ic[2], void *ps[6])

{
   int loop;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   int fluidIndex, initConditionsChoice, stateVariableSelection, 
      forcedConvectionUseFilmState;
   double initialPressure, initialTemperature, initialTemperatureC, 
      initialGasMassFraction, initialSuperheat, volume, 
      hydraulicDiameter, pipeLength, heatExchangeGain, ReL, ReH, 
      hydraulicDiameterInjector;
   char *nusseltExpressionLaminarFlow, *nusseltExpressionTurbulentFlow;

   fluidIndex = ip[0];
   initConditionsChoice = ip[1];
   stateVariableSelection = ip[2];
   forcedConvectionUseFilmState = ip[3];

   initialPressure = rp[0];
   initialTemperature = rp[1];
   initialTemperatureC = rp[2];
   initialGasMassFraction = rp[3];
   initialSuperheat = rp[4];
   volume     = rp[5];
   hydraulicDiameter = rp[6];
   pipeLength = rp[7];
   heatExchangeGain = rp[8];
   ReL        = rp[9];
   ReH        = rp[10];
   hydraulicDiameterInjector = rp[11];

   nusseltExpressionLaminarFlow = tp[0];
   nusseltExpressionTurbulentFlow = tp[1];
   loop = 0;

/* Common -> SI units conversions. */

/*   *fluidStateIndex *= ??; CONVERSION UNKNOWN [smoTDS] */
/*   *fluidFlow1Index *= ??; CONVERSION UNKNOWN [smoFFL] */
/*   *fluidFlowActivationSignal1 *= ??; CONVERSION UNKNOWN [smoFFAS] */
/*   *thermalNodeIndex *= ??; CONVERSION UNKNOWN [smoTHN] */
/*   *fluidFlow3Index *= ??; CONVERSION UNKNOWN [smoFFL] */
/*   *fluidFlowActivationSignal3 *= ??; CONVERSION UNKNOWN [smoFFAS] */
/*   *fluidFlow4Index *= ??; CONVERSION UNKNOWN [smoFFL] */
/*   *fluidFlowActivationSignal4 *= ??; CONVERSION UNKNOWN [smoFFAS] */

/*
   Set all submodel outputs below:

   *heatFlowIndex = ??;
   *pressure   = ??;
   *temperature = ??;
   *density    = ??;
   *specificEnthalpy = ??;
   *gasMassFraction = ??;
   *superHeat  = ??;
   *totalMass  = ??;
   stateValuesDot[0..1] = ??;
   *reynoldsNumber = ??;
   *convectionCoefficient = ??;
   *heatFlowRateFromWall = ??;
*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
   SMOCOMPONENT_PRINT_MAIN_CALC
     if (firstc_()) {
  	   FluidFlow* port1Flow = FluidFlow_get(*fluidFlow1Index);
  	   FluidFlow* port3Flow = FluidFlow_get(*fluidFlow3Index);
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
     //*internalVolume = PipeHeatExchNoPrDropMassAcc_C_getVolume(_component);
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *fluidStateIndex /= ??; CONVERSION UNKNOWN [smoTDS] */
/*   *fluidFlow1Index /= ??; CONVERSION UNKNOWN [smoFFL] */
/*   *fluidFlowActivationSignal1 /= ??; CONVERSION UNKNOWN [smoFFAS] */
/*   *heatFlowIndex /= ??; CONVERSION UNKNOWN [smoHFL] */
/*   *thermalNodeIndex /= ??; CONVERSION UNKNOWN [smoTHN] */
/*   *fluidFlow3Index /= ??; CONVERSION UNKNOWN [smoFFL] */
/*   *fluidFlowActivationSignal3 /= ??; CONVERSION UNKNOWN [smoFFAS] */
/*   *fluidFlow4Index /= ??; CONVERSION UNKNOWN [smoFFL] */
/*   *fluidFlowActivationSignal4 /= ??; CONVERSION UNKNOWN [smoFFAS] */
   *pressure /= 1.00000000000000e+005;
   *specificEnthalpy /= 1.00000000000000e+003;
}

extern double smo_tank_macro0_(int *n, double *thermalNodeIndex
      , double stateValues[2], double rp[12], int ip[4], char *tp[2]
      , int ic[2], void *ps[6])

{
   double fluidStateIndex;
   int loop;
/* >>>>>>>>>>>>Extra Macro Function macro0 Declarations Here. */
/* <<<<<<<<<<<<End of Extra Macro macro0 declarations. */
   int fluidIndex, initConditionsChoice, stateVariableSelection, 
      forcedConvectionUseFilmState;
   double initialPressure, initialTemperature, initialTemperatureC, 
      initialGasMassFraction, initialSuperheat, volume, 
      hydraulicDiameter, pipeLength, heatExchangeGain, ReL, ReH, 
      hydraulicDiameterInjector;
   char *nusseltExpressionLaminarFlow, *nusseltExpressionTurbulentFlow;

   fluidIndex = ip[0];
   initConditionsChoice = ip[1];
   stateVariableSelection = ip[2];
   forcedConvectionUseFilmState = ip[3];

   initialPressure = rp[0];
   initialTemperature = rp[1];
   initialTemperatureC = rp[2];
   initialGasMassFraction = rp[3];
   initialSuperheat = rp[4];
   volume     = rp[5];
   hydraulicDiameter = rp[6];
   pipeLength = rp[7];
   heatExchangeGain = rp[8];
   ReL        = rp[9];
   ReH        = rp[10];
   hydraulicDiameterInjector = rp[11];

   nusseltExpressionLaminarFlow = tp[0];
   nusseltExpressionTurbulentFlow = tp[1];
   loop = 0;

/* Common -> SI units conversions. */

/*   *thermalNodeIndex *= ??; CONVERSION UNKNOWN [smoTHN] */

/*
   Define and return the following macro variable:

   fluidStateIndex = ??;
*/


/* >>>>>>>>>>>>Macro Function macro0 Executable Statements. */
   SMOCOMPONENt_PRINT_MACRO
   if (firstc_()) {
	   ThermalNode* wallNode = ThermalNode_get(*thermalNodeIndex);
	   PipeHeatExchNoPrDropMassAcc_C_setWallNode(_component, wallNode);
   }

   PipeHeatExchNoPrDropMassAcc_C_setStateValues(_component, stateValues[0], stateValues[1]);
   fluidStateIndex = _pipeStateIndex;
/* <<<<<<<<<<<<End of Macro macro0 Executable Statements. */

/* SI -> Common units conversions. */

/*   *thermalNodeIndex /= ??; CONVERSION UNKNOWN [smoTHN] */

/*   *fluidStateIndex /= ??; CONVERSION UNKNOWN [smoTDS] */

   return fluidStateIndex;
}

