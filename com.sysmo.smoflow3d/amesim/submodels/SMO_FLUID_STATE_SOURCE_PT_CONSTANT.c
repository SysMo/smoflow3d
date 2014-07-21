/* Submodel SMO_FLUID_STATE_SOURCE_PT_CONSTANT skeleton created by AME Submodel editing utility
   Sat Aug 24 14:39:25 2013 */



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

#define _SUBMODELNAME_ "SMO_FLUID_STATE_SOURCE_PT_CONSTANT"

/* >>>>>>>>>>>>Insert Private Code Here. */
#include "media/MediumState.h"

#define _fluidStateIndex ic[0]
#define _fluidState ps[0]
/* <<<<<<<<<<<<End of Private Code. */


/* There are 2 real parameters:

   initPressure    initial pressure    [bar -> Pa]
   initTemperature initial temperature [K]
*/


/* There is 1 integer parameter:

   mediumIndex medium index
*/

void smo_fluid_state_source_pt_constantin_(int *n, double rp[2]
      , int ip[1], int ic[1], void *ps[1], double *stateIndex
      , double *pressure, double *temperature, double *temperatureC
      , double *density, double *enthalpy, double *xx)

{
   int loop, error;
/* >>>>>>>>>>>>Extra Initialization Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Initialization declarations. */
   int mediumIndex;
   double initPressure, initTemperature;

   mediumIndex = ip[0];

   initPressure = rp[0];
   initTemperature = rp[1];
   loop = 0;
   error = 0;

/*
   If necessary, check values of the following:

   rp[0..1]
*/

/*
   Check and/or reset the following fixed and/or discrete variables

   *stateIndex = ??;
   *pressure   = ??;
   *temperature = ??;
   *temperatureC = ??;
   *density    = ??;
   *enthalpy   = ??;
   *xx         = ??;
*/


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

/* Common -> SI units conversions. */

   rp[0]    *= 1.00000000000000e+005;
   initPressure = rp[0];


/* >>>>>>>>>>>>Initialization Function Executable Statements. */
   Medium *fluid = Medium_get(mediumIndex);
   _fluidState = MediumState_new(fluid);
   _fluidStateIndex = MediumState_register(_fluidState);

   MediumState_update_Tp(_fluidState, initTemperature, initPressure);

   *pressure = initPressure;
   *temperature = initTemperature;
   *temperatureC = MediumState_T(_fluidState) - 273.15;
   *density = MediumState_rho(_fluidState);
   *enthalpy = MediumState_h(_fluidState);
   *xx = 0.0; //:TODO: (Nasko) compute gas mass fraction

   *stateIndex = _fluidStateIndex;
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

/*  There is 1 port.

   Port 1 has 2 variables:

      1 stateIndex     state index [smoTDS] fixed  UNPLOTTABLE
      2 flowIndex      flow index  [smoFFL] basic variable input  UNPLOTTABLE
*/

/*  There are 6 internal variables.

      1 pressure         pressure          [bar]     fixed
      2 temperature      temperature       [K]       fixed
      3 temperatureC     temperature (°C)  [degC]    fixed
      4 density          density           [kg/m**3] fixed
      5 enthalpy         specific enthalpy [kJ/kg]   fixed
      6 xx               gas mass fraction [null]    fixed
*/

#if 0

/* THE CALCULATION FUNCTION WILL NOT BE CALLED. */

void smo_fluid_state_source_pt_constant_(int *n, double *flowIndex
      , double rp[2], int ip[1], int ic[1], void *ps[1], int *flag)

{
   int loop, logi;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   int mediumIndex;
   double initPressure, initTemperature;

   mediumIndex = ip[0];

   initPressure = rp[0];
   initTemperature = rp[1];
   logi = 0;
   loop = 0;

/* Common -> SI units conversions. */

/*   *flowIndex *= ??; CONVERSION UNKNOWN */

/*
   Set all submodel outputs below:

*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *flowIndex /= ??; CONVERSION UNKNOWN */
}

#endif
