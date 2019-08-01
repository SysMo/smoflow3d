/* Submodel SMO_FLUID_CHAMBER_4PORT skeleton created by AME Submodel editing utility
   ???? ??? 1 13:01:38 2019 */



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
#include "SmoFlowAme.h"
#include "volumes/FluidChamber.h"
#include "flow/FlowBase.h"

#define _component ps[0]

#define _fluidStateIndex ic[0]
#define _fluidState ps[1]

#define _fluidFlow1 ps[2]
#define _fluidFlow2 ps[3]
#define _fluidFlow3 ps[4]
#define _fluidFlow4 ps[5]
/* <<<<<<<<<<<<End of Private Code. */


/* There are 6 real parameters:

   initialPressure        initial pressure          [barA -> PaA]
   initialTemperature     initial temperature       [K]
   initialTemperatureC    initial temperature (°C)  [degC]
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
   _component = FluidChamber_new(fluid);
   SMOCOMPONENT_SET_PROPS(_component)

   FluidChamber_setVolume(_component, volume);
   _fluidState = FluidChamber_getFluidState(_component);
   _fluidStateIndex = MediumState_index(_fluidState);

   if (stateVariableSelection == 1) {
	   FluidChamber_selectStates(_component, iT, iD);
   } else if (stateVariableSelection == 2) {
	   FluidChamber_selectStates(_component, iP, iT);
   } else if (stateVariableSelection == 3) {
	   FluidChamber_selectStates(_component, iP, iD);
   } else if (stateVariableSelection == 4) {
	   FluidChamber_selectStates(_component, iP, iH);
   } else {
	   AME_RAISE_ERROR("Unsupported type of state variables.")
   }

   if (initConditionsChoice == 1) {
	   MediumState_update_Tp(_fluidState, initialTemperature, initialPressure);
   } else if (initConditionsChoice == 2) {
	   MediumState_update_Tp(_fluidState, initialTemperatureC + 273.15, initialPressure);
   } else if (initConditionsChoice == 3) {
	   MediumState_update_pq(_fluidState, initialPressure, initialGasMassFraction);
   } else {
	   AME_RAISE_ERROR("Unsupported type of initialization.")
   }

   FluidChamber_getStateValues(_component, state1, state2, 1);
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

/*  There are 4 ports.

   Port 1 has 3 variables:

      1 fluidStateIndex                fluid state index                    [smoTDS]  multi line macro 'smo_fluid_chamber_4port_macro0_'  UNPLOTTABLE
      2 fluidFlow1Index                fluid flow index 1                   [smoFFL]  basic variable input  UNPLOTTABLE
      3 fluidFlowActivationSignal1     fluid flow activation signal (port1) [smoFFAS] basic variable input  UNPLOTTABLE

   Port 2 has 3 variables:

      1 fluidStateIndexDup2            duplicate of fluidStateIndex        
      2 fluidFlow2Index                fluid flow index 2                   [smoFFL]  basic variable input  UNPLOTTABLE
      3 fluidFlowActivationSignal2     fluid flow activation signal (port2) [smoFFAS] basic variable input  UNPLOTTABLE

   Port 3 has 3 variables:

      1 fluidStateIndexDup3            duplicate of fluidStateIndex        
      2 fluidFlow3Index                fluid flow index 3                   [smoFFL]  basic variable input  UNPLOTTABLE
      3 fluidFlowActivationSignal3     fluid flow activation signal (port3) [smoFFAS] basic variable input  UNPLOTTABLE

   Port 4 has 3 variables:

      1 fluidStateIndexDup4            duplicate of fluidStateIndex        
      2 fluidFlow4Index                flow index 4                         [smoFFL]  basic variable input  UNPLOTTABLE
      3 fluidFlowActivationSignal4     fluid flow activation signal (port4) [smoFFAS] basic variable input  UNPLOTTABLE
*/

/*  There are 9 internal variables.

      1 pressure             pressure               [barA -> PaA]   basic variable
      2 temperature          temperature            [K]             basic variable
      3 density              density                [kg/m**3]       basic variable
      4 specificEnthalpy     specific enthalpy      [kJ/kg -> J/kg] basic variable
      5 gasMassFraction      gas mass fraction      [null]          basic variable
      6 superHeat            subcooling / superheat [degC]          basic variable
      7 totalMass            mass in chamber        [kg]            basic variable
      8 state1               state variable 1       [null]          explicit state (derivative `state1Dot')
      9 state2               state variable 2       [null]          explicit state (derivative `state2Dot')
*/

void smo_fluid_chamber_4port_(int *n, double *fluidStateIndex
      , double *fluidFlow1Index, double *fluidFlowActivationSignal1
      , double *fluidFlow2Index, double *fluidFlowActivationSignal2
      , double *fluidFlow3Index, double *fluidFlowActivationSignal3
      , double *fluidFlow4Index, double *fluidFlowActivationSignal4
      , double *pressure, double *temperature, double *density
      , double *specificEnthalpy, double *gasMassFraction
      , double *superHeat, double *totalMass, double *state1
      , double *state1Dot, double *state2, double *state2Dot
      , double rp[6], int ip[3], int ic[1], void *ps[6])

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

/*   *fluidStateIndex *= ??; CONVERSION UNKNOWN [smoTDS] */
/*   *fluidFlow1Index *= ??; CONVERSION UNKNOWN [smoFFL] */
/*   *fluidFlowActivationSignal1 *= ??; CONVERSION UNKNOWN [smoFFAS] */
/*   *fluidFlow2Index *= ??; CONVERSION UNKNOWN [smoFFL] */
/*   *fluidFlowActivationSignal2 *= ??; CONVERSION UNKNOWN [smoFFAS] */
/*   *fluidFlow3Index *= ??; CONVERSION UNKNOWN [smoFFL] */
/*   *fluidFlowActivationSignal3 *= ??; CONVERSION UNKNOWN [smoFFAS] */
/*   *fluidFlow4Index *= ??; CONVERSION UNKNOWN [smoFFL] */
/*   *fluidFlowActivationSignal4 *= ??; CONVERSION UNKNOWN [smoFFAS] */

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
   SMOCOMPONENT_PRINT_MAIN_CALC
   if (firstc_()) {
	   _fluidFlow1 = FluidFlow_get(*fluidFlow1Index);
	   _fluidFlow2 = FluidFlow_get(*fluidFlow2Index);
	   _fluidFlow3 = FluidFlow_get(*fluidFlow3Index);
	   _fluidFlow4 = FluidFlow_get(*fluidFlow4Index);
   }

   double massFlowRate = FluidFlow_getMassFlowRate(_fluidFlow1) + FluidFlow_getMassFlowRate(_fluidFlow2)
		   +  FluidFlow_getMassFlowRate(_fluidFlow3) + FluidFlow_getMassFlowRate(_fluidFlow4);
   double enthalpyFlowRate = FluidFlow_getEnthalpyFlowRate(_fluidFlow1) + FluidFlow_getEnthalpyFlowRate(_fluidFlow2)
		   + FluidFlow_getEnthalpyFlowRate(_fluidFlow3) + FluidFlow_getEnthalpyFlowRate(_fluidFlow4);
   FluidChamber_compute(_component, massFlowRate, enthalpyFlowRate, 0, 0);
   FluidChamber_getStateDerivatives(_component, state1Dot, state2Dot);

   *pressure = MediumState_p(_fluidState);
   *temperature = MediumState_T(_fluidState);
   *density = MediumState_rho(_fluidState);
   *specificEnthalpy = MediumState_h(_fluidState);
   *gasMassFraction = MediumState_q(_fluidState);
   *superHeat  = MediumState_deltaTSat(_fluidState);
   *totalMass  = FluidChamber_getFluidMass(_component);
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *fluidStateIndex /= ??; CONVERSION UNKNOWN [smoTDS] */
/*   *fluidFlow1Index /= ??; CONVERSION UNKNOWN [smoFFL] */
/*   *fluidFlowActivationSignal1 /= ??; CONVERSION UNKNOWN [smoFFAS] */
/*   *fluidFlow2Index /= ??; CONVERSION UNKNOWN [smoFFL] */
/*   *fluidFlowActivationSignal2 /= ??; CONVERSION UNKNOWN [smoFFAS] */
/*   *fluidFlow3Index /= ??; CONVERSION UNKNOWN [smoFFL] */
/*   *fluidFlowActivationSignal3 /= ??; CONVERSION UNKNOWN [smoFFAS] */
/*   *fluidFlow4Index /= ??; CONVERSION UNKNOWN [smoFFL] */
/*   *fluidFlowActivationSignal4 /= ??; CONVERSION UNKNOWN [smoFFAS] */
   *pressure /= 1.00000000000000e+005;
   *specificEnthalpy /= 1.00000000000000e+003;
}

extern double smo_fluid_chamber_4port_macro0_(int *n, double *state1
      , double *state2, double rp[6], int ip[3], int ic[1]
      , void *ps[6])

{
   double fluidStateIndex;
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

   fluidStateIndex = ??;
*/


/* >>>>>>>>>>>>Macro Function macro0 Executable Statements. */
   SMOCOMPONENt_PRINT_MACRO
   FluidChamber_setStateValues(_component, *state1, *state2);
   fluidStateIndex = _fluidStateIndex;
/* <<<<<<<<<<<<End of Macro macro0 Executable Statements. */

/*   *fluidStateIndex /= ??; CONVERSION UNKNOWN [smoTDS] */

   return fluidStateIndex;
}

