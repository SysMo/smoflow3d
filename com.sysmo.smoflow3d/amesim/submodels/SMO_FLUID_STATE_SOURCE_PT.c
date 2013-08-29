/* Submodel SMO_FLUID_STATE_SOURCE_PT skeleton created by AME Submodel editing utility
   Thu Aug 29 09:30:15 2013 */



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

#define _SUBMODELNAME_ "SMO_FLUID_STATE_SOURCE_PT"

/* >>>>>>>>>>>>Insert Private Code Here. */
#include "media/MediumState.h"

#define _fluidStateIndex ic[0]
#define _fluidState ps[0]
/* <<<<<<<<<<<<End of Private Code. */

/* There is 1 integer parameter:

   mediumIndex medium index
*/

void smo_fluid_state_source_ptin_(int *n, int ip[1], int ic[1]
      , void *ps[1])

{
   int loop, error;
/* >>>>>>>>>>>>Extra Initialization Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Initialization declarations. */
   int mediumIndex;

   mediumIndex = ip[0];
   loop = 0;
   error = 0;


/* >>>>>>>>>>>>Initialization Function Check Statements. */
/* <<<<<<<<<<<<End of Initialization Check Statements. */

/*   Integer parameter checking:   */

   if (mediumIndex < 1 || mediumIndex > 99)
   {
      amefprintf(stderr, "\nmedium index must be in range [1..99].\n");
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


/* >>>>>>>>>>>>Initialization Function Executable Statements. */
   Medium *fluid = Medium_get(mediumIndex);
   _fluidState = MediumState_new(fluid);
   _fluidStateIndex = MediumState_register(_fluidState);
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

/*  There are 3 ports.

   Port 1 has 2 variables:

      1 stateIndex     state index [smoTDS] multi line macro 'smo_fluid_state_source_pt_macro0_'  UNPLOTTABLE
      2 flowIndex      flow index  [smoFFL] basic variable input  UNPLOTTABLE

   Port 2 has 1 variable:

      1 pressure     pressure [bar -> Pa] basic variable input

   Port 3 has 1 variable:

      1 temperature     temperature [K] basic variable input
*/

/*  There are 4 internal variables.

      1 temperatureC        temperature (°C)  [degC]          basic variable
      2 density             density           [kg/m**3]       basic variable
      3 enthalpy            specific enthalpy [kJ/kg -> J/kg] basic variable
      4 gasMassFraction     gas mass fraction [null]          basic variable
*/

void smo_fluid_state_source_pt_(int *n, double *stateIndex
      , double *flowIndex, double *pressure, double *temperature
      , double *temperatureC, double *density, double *enthalpy
      , double *gasMassFraction, int ip[1], int ic[1], void *ps[1]
      , int *flag)

{
   int loop, logi;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   int mediumIndex;

   mediumIndex = ip[0];
   logi = 0;
   loop = 0;

/* Common -> SI units conversions. */

/*   *stateIndex *= ??; CONVERSION UNKNOWN */
/*   *flowIndex *= ??; CONVERSION UNKNOWN */
   *pressure *= 1.00000000000000e+005;

/*
   Set all submodel outputs below:

   *temperatureC = ??;
   *density    = ??;
   *enthalpy   = ??;
   *gasMassFraction = ??;
*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
   *temperatureC = *temperature - 273.15;
   *density = MediumState_rho(_fluidState);
   *enthalpy = MediumState_h(_fluidState);
   *gasMassFraction = MediumState_q(_fluidState);
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *stateIndex /= ??; CONVERSION UNKNOWN */
/*   *flowIndex /= ??; CONVERSION UNKNOWN */
   *pressure /= 1.00000000000000e+005;
   *enthalpy /= 1.00000000000000e+003;
}

extern double smo_fluid_state_source_pt_macro0_(int *n
      , double *pressure, double *temperature, int ip[1], int ic[1]
      , void *ps[1], int *flag)

{
   double stateIndex;
   int loop, logi;
/* >>>>>>>>>>>>Extra Macro Function macro0 Declarations Here. */
/* <<<<<<<<<<<<End of Extra Macro macro0 declarations. */
   int mediumIndex;

   mediumIndex = ip[0];
   logi = 0;
   loop = 0;

/* Common -> SI units conversions. */

   *pressure *= 1.00000000000000e+005;

/*
   Define and return the following macro variable:

   stateIndex = ??;
*/


/* >>>>>>>>>>>>Macro Function macro0 Executable Statements. */
   MediumState_update_Tp(_fluidState, *temperature, *pressure);
   stateIndex = _fluidStateIndex;
/* <<<<<<<<<<<<End of Macro macro0 Executable Statements. */

/* SI -> Common units conversions. */

   *pressure /= 1.00000000000000e+005;

/*   *stateIndex /= ??; CONVERSION UNKNOWN */

   return stateIndex;
}

