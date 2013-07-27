/* Submodel SMO_FLUID_SOURCE skeleton created by AME Submodel editing utility
   Sat Jul 27 14:50:41 2013 */



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

#define _SUBMODELNAME_ "SMO_FLUID_SOURCE"

/* >>>>>>>>>>>>Insert Private Code Here. */
#include "media/MediumState.h"
#define fluidStateIndex ic[1]
#define fluidState ps[1]
/* <<<<<<<<<<<<End of Private Code. */

/* There is 1 integer parameter:

   mediumIndex medium index
*/

void smo_fluid_sourcein_(int *n, int ip[1], int ic[1], void *ps[1])

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
   fluidState = MediumState_new(mediumIndex);
   fluidStateIndex = MediumState_register(fluidState);
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

/*  There are 3 ports.

   Port 1 has 2 variables:

      1 stateIndex     state index [smoTDS] multi line macro 'smo_fluid_source_macro0_'  UNPLOTTABLE
      2 flowIndex      flow index  [smoFFL] basic variable input  UNPLOTTABLE

   Port 2 has 1 variable:

      1 stateValue1     thermodynamic state value 1 [null] basic variable input  UNPLOTTABLE

   Port 3 has 1 variable:

      1 stateValue2     thermodynamic state value 2 [null] basic variable input  UNPLOTTABLE
*/

/*  There are 6 internal variables.

      1 pressure         pressure          [bar -> Pa]     basic variable
      2 temperature      temperature       [K]             basic variable
      3 temperatureC     temperature (�C)  [degC]          basic variable
      4 density          density           [kg/m**3]       basic variable
      5 enthalpy         specific enthalpy [kJ/kg -> J/kg] basic variable
      6 xx               gas mass fraction [null]          basic variable
*/

void smo_fluid_source_(int *n, double *stateIndex, double *flowIndex
      , double *stateValue1, double *stateValue2, double *pressure
      , double *temperature, double *temperatureC, double *density
      , double *enthalpy, double *xx, int ip[1], int ic[1]
      , void *ps[1], int *flag)

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

/*
   Set all submodel outputs below:

   *pressure   = ??;
   *temperature = ??;
   *temperatureC = ??;
   *density    = ??;
   *enthalpy   = ??;
   *xx         = ??;
*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
   *pressure = MediumState_p(fluidState);
   *temperature = MediumState_T(fluidState);
   *temperatureC = *temperature - 273.15;
   *density = MediumState_rho(fluidState);
   *enthalpy = MediumState_h(fluidState);
   *xx = 0.0; //:TODO: compute gas mass fraction
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *stateIndex /= ??; CONVERSION UNKNOWN */
/*   *flowIndex /= ??; CONVERSION UNKNOWN */
   *pressure /= 1.00000000000000e+005;
   *enthalpy /= 1.00000000000000e+003;
}

extern double smo_fluid_source_macro0_(int *n, double *stateValue1
      , double *stateValue2, int ip[1], int ic[1], void *ps[1]
      , int *flag)

{
   double stateIndex;
   int loop, logi;
/* >>>>>>>>>>>>Extra Macro Function macro0 Declarations Here. */
/* <<<<<<<<<<<<End of Extra Macro macro0 declarations. */
   int mediumIndex;

   mediumIndex = ip[0];
   logi = 0;
   loop = 0;

/*
   Define and return the following macro variable:

   stateIndex = ??;
*/


/* >>>>>>>>>>>>Macro Function macro0 Executable Statements. */
   MediumState_update_Tp(fluidState, *stateValue2, *stateValue1);
   stateIndex = (double) fluidStateIndex;
/* <<<<<<<<<<<<End of Macro macro0 Executable Statements. */

/*   *stateIndex /= ??; CONVERSION UNKNOWN */

   return stateIndex;
}

