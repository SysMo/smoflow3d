/* Submodel SMO_FLUID_CHAMBER_4PORT skeleton created by AME Submodel editing utility
   Sun Aug 4 16:50:13 2013 */



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

#define _SUBMODELNAME_ "SMO_FLUID_CHAMBER_4PORT"

/* >>>>>>>>>>>>Insert Private Code Here. */
#include "volumes/FluidChamber.h"
#include "flow/FluidFlow.h"

#define fluidChamberStateIndex ic[0]
#define fluidChamber ps[0]
#define fluidState ps[1]
#define flow1 ps[2]
#define flow2 ps[3]
#define flow3 ps[4]
#define flow4 ps[5]
/* <<<<<<<<<<<<End of Private Code. */


/* There are 6 real parameters:

   initialPressure        initial pressure          [barA -> PaA]
   initialTemperature     initial temperature (K)   [K]
   initialTemperatureC    initial temperature (�C)  [degC]
   initialGasMassFraction initial gas mass fraction [null]
   initialSuperheat       initial superheat         [K]
   volume                 volume                    [L -> m**3]
*/


/* There are 3 integer parameters:

   fluidIndex             fluid index           
   initConditionsChoice   type of initialization
   stateVariableSelection states variables      
*/

void smo_fluid_chamber_4portin_(int *n, double rp[6], int ip[3]
      , int ic[1], void *ps[6], double *state1, double *state2)

{
   int loop, error;
/* >>>>>>>>>>>>Extra Initialization Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Initialization declarations. */
   int fluidIndex, initConditionsChoice, stateVariableSelection;
   double initialPressure, initialTemperature, initialTemperatureC, 
      initialGasMassFraction, initialSuperheat, volume;

   fluidIndex = ip[0];
   initConditionsChoice = ip[1];
   stateVariableSelection = ip[2];

   initialPressure = rp[0];
   initialTemperature = rp[1];
   initialTemperatureC = rp[2];
   initialGasMassFraction = rp[3];
   initialSuperheat = rp[4];
   volume     = rp[5];
   loop = 0;
   error = 0;

/*
   If necessary, check values of the following:

   rp[0..5]
   *state1
   *state2
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


/* >>>>>>>>>>>>Initialization Function Executable Statements. */
Medium* fluid = Medium_get(fluidIndex);
fluidChamber = FluidChamber_new(fluid);
FluidChamber_setVolume(fluidChamber, volume);

fluidState = FluidChamber_getFluidState(fluidChamber);
fluidChamberStateIndex = MediumState_index(fluidState);

if (stateVariableSelection == 1) {
	FluidChamber_selectStates(fluidChamber, iT, iD);
} else if (stateVariableSelection == 2) {
	FluidChamber_selectStates(fluidChamber, iP, iT);
} else if (stateVariableSelection == 3) {
	FluidChamber_selectStates(fluidChamber, iP, iD);
} else if (stateVariableSelection == 4) {
	FluidChamber_selectStates(fluidChamber, iP, iH);
} else {
    amefprintf(stderr, "\nFatal error in %s instance %d.\n", _SUBMODELNAME_, *n);
    amefprintf(stderr, "Terminating the program.\n");
    AmeExit(1);
}

if (initConditionsChoice == 1) {
	MediumState_update_Tp(fluidState, initialTemperature, initialPressure);
} else if (initConditionsChoice == 2) {
	MediumState_update_Tp(fluidState, initialTemperatureC + 273.15, initialPressure);
} else {
    amefprintf(stderr, "\nFatal error in %s instance %d.\n", _SUBMODELNAME_, *n);
    amefprintf(stderr, "Terminating the program.\n");
    AmeExit(1);
}

FluidChamber_getStateValues(fluidChamber, state1, state2, 1);
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

/*  There are 4 ports.

   Port 1 has 2 variables:

      1 stateIndex     state index  [smoTDS] multi line macro 'smo_fluid_chamber_4port_macro0_'  UNPLOTTABLE
      2 flowIndex1     flow index 1 [smoFFL] basic variable input  UNPLOTTABLE

   Port 2 has 2 variables:

      1 stateIndexDup2     duplicate of stateIndex
      2 flowIndex2         flow index 2 [smoFFL] basic variable input  UNPLOTTABLE

   Port 3 has 2 variables:

      1 stateIndexDup3     duplicate of stateIndex
      2 flowIndex3         flow index 3 [smoFFL] basic variable input  UNPLOTTABLE

   Port 4 has 2 variables:

      1 stateIndexDup4     duplicate of stateIndex
      2 flowIndex4         flow index 4 [smoFFL] basic variable input  UNPLOTTABLE
*/

/*  There are 9 internal variables.

      1 pressure             pressure               [bar -> Pa]     basic variable
      2 temperature          temperature            [K]             basic variable
      3 density              density                [kg/m**3]       basic variable
      4 specificEnthalpy     specific enthalpy      [kJ/kg -> J/kg] basic variable
      5 gasMassFraction      gas mass fraction      [null]          basic variable
      6 superHeat            subcooling / superheat [degC]          basic variable
      7 totalMass            mass in chamber        [kg]            basic variable
      8 state1               state variable 1       [null]          explicit state (derivative `state1Dot')
      9 state2               state variable 2       [null]          explicit state (derivative `state2Dot')
*/

void smo_fluid_chamber_4port_(int *n, double *stateIndex
      , double *flowIndex1, double *flowIndex2, double *flowIndex3
      , double *flowIndex4, double *pressure, double *temperature
      , double *density, double *specificEnthalpy
      , double *gasMassFraction, double *superHeat, double *totalMass
      , double *state1, double *state1Dot, double *state2
      , double *state2Dot, double rp[6], int ip[3], int ic[1]
      , void *ps[6])

{
   int loop;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   int fluidIndex, initConditionsChoice, stateVariableSelection;
   double initialPressure, initialTemperature, initialTemperatureC, 
      initialGasMassFraction, initialSuperheat, volume;

   fluidIndex = ip[0];
   initConditionsChoice = ip[1];
   stateVariableSelection = ip[2];

   initialPressure = rp[0];
   initialTemperature = rp[1];
   initialTemperatureC = rp[2];
   initialGasMassFraction = rp[3];
   initialSuperheat = rp[4];
   volume     = rp[5];
   loop = 0;

/* Common -> SI units conversions. */

/*   *stateIndex *= ??; CONVERSION UNKNOWN */
/*   *flowIndex1 *= ??; CONVERSION UNKNOWN */
/*   *flowIndex2 *= ??; CONVERSION UNKNOWN */
/*   *flowIndex3 *= ??; CONVERSION UNKNOWN */
/*   *flowIndex4 *= ??; CONVERSION UNKNOWN */

/*
   Set all submodel outputs below:

   *pressure   = ??;
   *temperature = ??;
   *density    = ??;
   *specificEnthalpy = ??;
   *gasMassFraction = ??;
   *superHeat  = ??;
   *totalMass  = ??;
   *state1Dot  = ??;
   *state2Dot  = ??;
*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
   if (firstc_()) {
	   flow1 = FluidFlow_get(*flowIndex1);
	   flow2 = FluidFlow_get(*flowIndex2);
	   flow3 = FluidFlow_get(*flowIndex3);
	   flow4 = FluidFlow_get(*flowIndex4);
   }
   double massFlowRate = FluidFlow_getMassFlowRate(flow1) + FluidFlow_getMassFlowRate(flow2)
		   +  FluidFlow_getMassFlowRate(flow3) + FluidFlow_getMassFlowRate(flow4);
   double enthalpyFlowRate = FluidFlow_getEnthalpyFlowRate(flow1) + FluidFlow_getEnthalpyFlowRate(flow2)
		   + FluidFlow_getEnthalpyFlowRate(flow3) + FluidFlow_getEnthalpyFlowRate(flow4);
   FluidChamber_computeStateDerivatives(fluidChamber, massFlowRate, enthalpyFlowRate, 0, 0);
   FluidChamber_getStateDerivatives(fluidChamber, state1Dot, state2Dot);

   *pressure = MediumState_p(fluidState);
   *temperature = MediumState_T(fluidState);
   *density = MediumState_rho(fluidState);
   *specificEnthalpy = MediumState_h(fluidState);
   //*gasMassFraction = ??;
   //*superHeat  = ??;
   *totalMass  = FluidChamber_getFluidMass(fluidChamber);

/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *stateIndex /= ??; CONVERSION UNKNOWN */
/*   *flowIndex1 /= ??; CONVERSION UNKNOWN */
/*   *flowIndex2 /= ??; CONVERSION UNKNOWN */
/*   *flowIndex3 /= ??; CONVERSION UNKNOWN */
/*   *flowIndex4 /= ??; CONVERSION UNKNOWN */
   *pressure /= 1.00000000000000e+005;
   *specificEnthalpy /= 1.00000000000000e+003;
}

extern double smo_fluid_chamber_4port_macro0_(int *n, double *state1
      , double *state2, double rp[6], int ip[3], int ic[1]
      , void *ps[6])

{
   double stateIndex;
   int loop;
/* >>>>>>>>>>>>Extra Macro Function macro0 Declarations Here. */
/* <<<<<<<<<<<<End of Extra Macro macro0 declarations. */
   int fluidIndex, initConditionsChoice, stateVariableSelection;
   double initialPressure, initialTemperature, initialTemperatureC, 
      initialGasMassFraction, initialSuperheat, volume;

   fluidIndex = ip[0];
   initConditionsChoice = ip[1];
   stateVariableSelection = ip[2];

   initialPressure = rp[0];
   initialTemperature = rp[1];
   initialTemperatureC = rp[2];
   initialGasMassFraction = rp[3];
   initialSuperheat = rp[4];
   volume     = rp[5];
   loop = 0;

/*
   Define and return the following macro variable:

   stateIndex = ??;
*/


/* >>>>>>>>>>>>Macro Function macro0 Executable Statements. */
   FluidChamber_setStateValues(fluidChamber, *state1, *state2);
   stateIndex = fluidChamberStateIndex;
/* <<<<<<<<<<<<End of Macro macro0 Executable Statements. */

/*   *stateIndex /= ??; CONVERSION UNKNOWN */

   return stateIndex;
}

