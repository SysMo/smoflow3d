/* Submodel SMO_TPIPE_JUNCTION skeleton created by AME Submodel editing utility
   ??? ??? 30 15:34:05 2019 */



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

#define _SUBMODELNAME_ "SMO_TPIPE_JUNCTION"

/* >>>>>>>>>>>>Insert Private Code Here. */
#include "SmoFlowAme.h"
#include "volumes/TPipeJunction.h"
#include "flow/FlowBase.h"

#define _component ps[0]

#define _fluidStateIndex1 ic[0]
#define _fluidState1 ps[1]

#define _fluidStateIndex2 ic[1]
#define _fluidState2 ps[2]

#define _fluidStateIndex3 ic[2]
#define _fluidState3 ps[3]

#define _fluidFlow1 ps[4]
#define _fluidFlow2 ps[5]
#define _fluidFlow3 ps[6]
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

void smo_tpipe_junctionin_(int *n, double rp[6], int ip[3], int ic[3]
      , void *ps[7], double *state1, double *state2)

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
	_component = TPipeJunction_new(fluid, volume, stateVariableSelection);
	SMOCOMPONENT_SET_PROPS(_component)

	TPipeJunction_initFluidStates(_component,
			initConditionsChoice, initialPressure, initialTemperature,
			initialTemperatureC, initialGasMassFraction);

	_fluidState1 = TPipeJunction_getFluidState1(_component);
	_fluidStateIndex1 = MediumState_index(_fluidState1);

	_fluidState2 = TPipeJunction_getFluidState2(_component);
	_fluidStateIndex2 = MediumState_index(_fluidState2);

	_fluidState3 = TPipeJunction_getFluidState3(_component);
	_fluidStateIndex3 = MediumState_index(_fluidState3);

	TPipeJunction_getStateValues(_component, state1, state2);
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

/*  There are 3 ports.

   Port 1 has 3 variables:

      1 fluidStateIndex1               fluid state index (port1)            [smoTDS]  multi line macro 'smo_tpipe_junction_macro0_'  UNPLOTTABLE
      2 fluidFlowIndex1                fluid flow index (port1)             [smoFFL]  basic variable input  UNPLOTTABLE
      3 fluidFlowActivationSignal1     fluid flow activation signal (port1) [smoFFAS] basic variable input  UNPLOTTABLE

   Port 2 has 3 variables:

      1 stateIndexDup2                 duplicate of fluidStateIndex1       
      2 fluidFlowIndex2                fluid flow index (port2)             [smoFFL]  basic variable input  UNPLOTTABLE
      3 fluidFlowActivationSignal2     fluid flow activation signal (port2) [smoFFAS] basic variable input  UNPLOTTABLE

   Port 3 has 3 variables:

      1 stateIndexDup3                 duplicate of fluidStateIndex1       
      2 fluidFlowIndex3                fluid flow index (port3)             [smoFFL]  basic variable input  UNPLOTTABLE
      3 fluidFlowActivationSignal3     fluid flow activation signal (port3) [smoFFAS] basic variable input  UNPLOTTABLE
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

void smo_tpipe_junction_(int *n, double *fluidStateIndex1
      , double *fluidFlowIndex1, double *fluidFlowActivationSignal1
      , double *fluidFlowIndex2, double *fluidFlowActivationSignal2
      , double *fluidFlowIndex3, double *fluidFlowActivationSignal3
      , double *pressure, double *temperature, double *density
      , double *specificEnthalpy, double *gasMassFraction
      , double *superHeat, double *totalMass, double *state1
      , double *state1Dot, double *state2, double *state2Dot
      , double rp[6], int ip[3], int ic[3], void *ps[7])

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

/*   *fluidStateIndex1 *= ??; CONVERSION UNKNOWN [smoTDS] */
/*   *fluidFlowIndex1 *= ??; CONVERSION UNKNOWN [smoFFL] */
/*   *fluidFlowActivationSignal1 *= ??; CONVERSION UNKNOWN [smoFFAS] */
/*   *fluidFlowIndex2 *= ??; CONVERSION UNKNOWN [smoFFL] */
/*   *fluidFlowActivationSignal2 *= ??; CONVERSION UNKNOWN [smoFFAS] */
/*   *fluidFlowIndex3 *= ??; CONVERSION UNKNOWN [smoFFL] */
/*   *fluidFlowActivationSignal3 *= ??; CONVERSION UNKNOWN [smoFFAS] */

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
		_fluidFlow1 = FluidFlow_get(*fluidFlowIndex1);
		_fluidFlow2 = FluidFlow_get(*fluidFlowIndex2);
		_fluidFlow3 = FluidFlow_get(*fluidFlowIndex3);

		TPipeJunction_initFlows(_component, _fluidFlow1, _fluidFlow2, _fluidFlow3);
	}

	TPipeJunction_compute(_component);
	TPipeJunction_getStateDerivatives(_component, state1Dot, state2Dot);

	*pressure = MediumState_p(_fluidState1);
	*temperature = MediumState_T(_fluidState1);
	*density = MediumState_rho(_fluidState1);
	*specificEnthalpy = MediumState_h(_fluidState1);
	*gasMassFraction = MediumState_q(_fluidState1);
	*superHeat  = MediumState_deltaTSat(_fluidState1);
	*totalMass  = TPipeJunction_getFluidMass(_component);
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *fluidStateIndex1 /= ??; CONVERSION UNKNOWN [smoTDS] */
/*   *fluidFlowIndex1 /= ??; CONVERSION UNKNOWN [smoFFL] */
/*   *fluidFlowActivationSignal1 /= ??; CONVERSION UNKNOWN [smoFFAS] */
/*   *fluidFlowIndex2 /= ??; CONVERSION UNKNOWN [smoFFL] */
/*   *fluidFlowActivationSignal2 /= ??; CONVERSION UNKNOWN [smoFFAS] */
/*   *fluidFlowIndex3 /= ??; CONVERSION UNKNOWN [smoFFL] */
/*   *fluidFlowActivationSignal3 /= ??; CONVERSION UNKNOWN [smoFFAS] */
   *pressure /= 1.00000000000000e+005;
   *specificEnthalpy /= 1.00000000000000e+003;
}

extern double smo_tpipe_junction_macro0_(int *n, double *state1
      , double *state2, double rp[6], int ip[3], int ic[3]
      , void *ps[7])

{
   double fluidStateIndex1;
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

   fluidStateIndex1 = ??;
*/


/* >>>>>>>>>>>>Macro Function macro0 Executable Statements. */
	SMOCOMPONENt_PRINT_MACRO
	TPipeJunction_setStateValues(_component, *state1, *state2);
	fluidStateIndex1 = _fluidStateIndex1;
/* <<<<<<<<<<<<End of Macro macro0 Executable Statements. */

/*   *fluidStateIndex1 /= ??; CONVERSION UNKNOWN [smoTDS] */

   return fluidStateIndex1;
}

