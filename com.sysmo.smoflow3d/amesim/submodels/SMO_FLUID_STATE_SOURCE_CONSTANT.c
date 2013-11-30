/* Submodel SMO_FLUID_STATE_SOURCE_CONSTANT skeleton created by AME Submodel editing utility
   Fri Nov 29 12:53:09 2013 */



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

#define _SUBMODELNAME_ "SMO_FLUID_STATE_SOURCE_CONSTANT"

/* >>>>>>>>>>>>Insert Private Code Here. */
#include "SmoFlowAme.h"
#include "media/MediumState.h"

#define _fluidStateIndex ic[0]
#define _fluidState ps[0]
/* <<<<<<<<<<<<End of Private Code. */


/* There are 4 real parameters:

   initialPressure         pressure          [barA -> PaA]
   initialTemperature      temperature       [K]
   initialSpecificEnthalpy specific enthalpy [kJ/kg -> J/kg]
   initialGasMassFraction  gas mass fraction [null]
*/


/* There are 2 integer parameters:

   mediumIndex          medium index          
   initConditionsChoice type of initialization
*/

void smo_fluid_state_source_constantin_(int *n, double rp[4]
      , int ip[2], int ic[1], void *ps[1], double *fluidStateIndex
      , double *pressure, double *temperature, double *temperatureC
      , double *density, double *specificEnthalpy
      , double *gasMassFraction)

{
   int loop, error;
/* >>>>>>>>>>>>Extra Initialization Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Initialization declarations. */
   int mediumIndex, initConditionsChoice;
   double initialPressure, initialTemperature, initialSpecificEnthalpy
      , initialGasMassFraction;

   mediumIndex = ip[0];
   initConditionsChoice = ip[1];

   initialPressure = rp[0];
   initialTemperature = rp[1];
   initialSpecificEnthalpy = rp[2];
   initialGasMassFraction = rp[3];
   loop = 0;
   error = 0;

/*
   If necessary, check values of the following:

   rp[0..3]
*/

/*
   Check and/or reset the following fixed and/or discrete variables

   *fluidStateIndex = ??;
   *pressure   = ??;
   *temperature = ??;
   *temperatureC = ??;
   *density    = ??;
   *specificEnthalpy = ??;
   *gasMassFraction = ??;
*/


/* >>>>>>>>>>>>Initialization Function Check Statements. */
/* <<<<<<<<<<<<End of Initialization Check Statements. */

/*   Integer parameter checking:   */

   if (mediumIndex < 1 || mediumIndex > 99)
   {
      amefprintf(stderr, "\nmedium index must be in range [1..99].\n");
      error = 2;
   }
   if (initConditionsChoice < 1 || initConditionsChoice > 3)
   {
      amefprintf(stderr, "\ntype of initialization must be in range [1..3].\n");
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
   rp[2]    *= 1.00000000000000e+003;
   initialSpecificEnthalpy = rp[2];


/* >>>>>>>>>>>>Initialization Function Executable Statements. */
   Medium *fluid = Medium_get(mediumIndex);
   _fluidState = MediumState_new(fluid);
   _fluidStateIndex = MediumState_register(_fluidState);

   if (initConditionsChoice == 1) {
	   MediumState_update_Tp(_fluidState, initialTemperature, initialPressure);
   } else if (initConditionsChoice == 2) {
	   MediumState_update_ph(_fluidState, initialPressure, initialSpecificEnthalpy);
   } else if (initConditionsChoice == 3) {
	   MediumState_update_pq(_fluidState, initialPressure, initialGasMassFraction);
   } else {
	   AME_RAISE_ERROR("Unsupported type of initialization.")
   }

   *pressure = MediumState_p(_fluidState) / 1e5;
   *temperature = MediumState_T(_fluidState);
   *temperatureC = MediumState_T(_fluidState) - 273.15;
   *density = MediumState_rho(_fluidState);
   *specificEnthalpy = MediumState_h(_fluidState) / 1e3;
   *gasMassFraction = MediumState_q(_fluidState);

   *fluidStateIndex = _fluidStateIndex;
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

/*  There is 1 port.

   Port 1 has 3 variables:

      1 fluidStateIndex               fluid state index            [smoTDS]  fixed  UNPLOTTABLE
      2 fluidFlowIndex                fluid flow index             [smoFFL]  basic variable input  UNPLOTTABLE
      3 fluidFlowActivationSignal     fluid flow activation signal [smoFFAS] basic variable input  UNPLOTTABLE
*/

/*  There are 6 internal variables.

      1 pressure             pressure           [bar]     fixed
      2 temperature          temperature        [K]       fixed
      3 temperatureC         temperature (°C)   [degC]    fixed
      4 density              density            [kg/m**3] fixed
      5 specificEnthalpy     specific enthalpy  [kJ/kg]   fixed
      6 gasMassFraction      gas mass fraction  [null]    fixed
*/

#if 0

/* THE CALCULATION FUNCTION WILL NOT BE CALLED. */

void smo_fluid_state_source_constant_(int *n, double *fluidFlowIndex
      , double *fluidFlowActivationSignal, double rp[4], int ip[2]
      , int ic[1], void *ps[1], int *flag)

{
   int loop, logi;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   int mediumIndex, initConditionsChoice;
   double initialPressure, initialTemperature, initialSpecificEnthalpy
      , initialGasMassFraction;

   mediumIndex = ip[0];
   initConditionsChoice = ip[1];

   initialPressure = rp[0];
   initialTemperature = rp[1];
   initialSpecificEnthalpy = rp[2];
   initialGasMassFraction = rp[3];
   logi = 0;
   loop = 0;

/* Common -> SI units conversions. */

/*   *fluidFlowIndex *= ??; CONVERSION UNKNOWN */
/*   *fluidFlowActivationSignal *= ??; CONVERSION UNKNOWN */

/*
   Set all submodel outputs below:

*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *fluidFlowIndex /= ??; CONVERSION UNKNOWN */
/*   *fluidFlowActivationSignal /= ??; CONVERSION UNKNOWN */
}

#endif
