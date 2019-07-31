/* Submodel SMO_FLUID_FLOW_GAIN skeleton created by AME Submodel editing utility
   ?? ??? 31 14:02:43 2019 */



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

#define _SUBMODELNAME_ "SMO_FLUID_FLOW_GAIN"

/* >>>>>>>>>>>>Insert Private Code Here. */
#include "flow/FlowBase.h"

#define _fluidFlowOutIndex ic[0]
#define _fluidFlowOut ps[0]
/* <<<<<<<<<<<<End of Private Code. */
void smo_fluid_flow_gainin_(int *n, int ic[1], void *ps[1])

{
   int loop, error;
/* >>>>>>>>>>>>Extra Initialization Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Initialization declarations. */
   loop = 0;
   error = 0;


/* >>>>>>>>>>>>Initialization Function Check Statements. */
/* <<<<<<<<<<<<End of Initialization Check Statements. */

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
   _fluidFlowOut = FluidFlow_new();
   _fluidFlowOutIndex = FluidFlow_register(_fluidFlowOut);
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

/*  There are 3 ports.

   Port 1 has 1 variable:

      1 fluidFlowGain     fluid flow gain [null] basic variable input

   Port 2 has 3 variables:

      1 fluidFlowIndexOut                fluid flow index out                 [smoFFL] multi line macro 'smo_fluid_flow_gain_macro0_'  UNPLOTTABLE
      2 fluidFlowActivationSignalOut     duplicate of fluidFlowActivationSignalIn3
      3 fluidStateIndex                  fluid state index                    [smoTDS] basic variable input  UNPLOTTABLE

   Port 3 has 3 variables:

      1 fluidStateIndexDup3              duplicate of fluidStateIndex        
      2 fluidFlowIndexIn3                fluid flow index in 3                [smoFFL]  basic variable input  UNPLOTTABLE
      3 fluidFlowActivationSignalIn3     fluid flow activation signal (port3) [smoFFAS] basic variable input
*/

/*  There are 0 internal variables.

*/

#if 0

/* THE CALCULATION FUNCTION WILL NOT BE CALLED. */

void smo_fluid_flow_gain_(int *n, double *fluidFlowGain
      , double *fluidFlowIndexOut, double *fluidStateIndex
      , double *fluidFlowIndexIn3
      , double *fluidFlowActivationSignalIn3, int ic[1], void *ps[1])

{
   int loop;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   loop = 0;

/* Common -> SI units conversions. */

/*   *fluidFlowIndexOut *= ??; CONVERSION UNKNOWN [smoFFL] */
/*   *fluidStateIndex *= ??; CONVERSION UNKNOWN [smoTDS] */
/*   *fluidFlowIndexIn3 *= ??; CONVERSION UNKNOWN [smoFFL] */
/*   *fluidFlowActivationSignalIn3 *= ??; CONVERSION UNKNOWN [smoFFAS] */

/*
   Set all submodel outputs below:

*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *fluidFlowIndexOut /= ??; CONVERSION UNKNOWN [smoFFL] */
/*   *fluidStateIndex /= ??; CONVERSION UNKNOWN [smoTDS] */
/*   *fluidFlowIndexIn3 /= ??; CONVERSION UNKNOWN [smoFFL] */
/*   *fluidFlowActivationSignalIn3 /= ??; CONVERSION UNKNOWN [smoFFAS] */
}

#endif
extern double smo_fluid_flow_gain_macro0_(int *n
      , double *fluidFlowGain, double *fluidFlowIndexIn3, int ic[1]
      , void *ps[1])

{
   double fluidFlowIndexOut;
   int loop;
/* >>>>>>>>>>>>Extra Macro Function macro0 Declarations Here. */
/* <<<<<<<<<<<<End of Extra Macro macro0 declarations. */
   loop = 0;

/* Common -> SI units conversions. */

/*   *fluidFlowIndexIn3 *= ??; CONVERSION UNKNOWN [smoFFL] */

/*
   Define and return the following macro variable:

   fluidFlowIndexOut = ??;
*/


/* >>>>>>>>>>>>Macro Function macro0 Executable Statements. */
   FluidFlow* flowIn3 = FluidFlow_get(*fluidFlowIndexIn3);

   double massFlowIn = (*fluidFlowGain) * FluidFlow_getMassFlowRate(flowIn3);
   double enthalpyFlowIn = (*fluidFlowGain) * FluidFlow_getEnthalpyFlowRate(flowIn3);
   FluidFlow_setMassFlowRate(_fluidFlowOut, massFlowIn);
   FluidFlow_setEnthalpyFlowRate(_fluidFlowOut, enthalpyFlowIn);

   fluidFlowIndexOut = _fluidFlowOutIndex;
/* <<<<<<<<<<<<End of Macro macro0 Executable Statements. */

/* SI -> Common units conversions. */

/*   *fluidFlowIndexIn3 /= ??; CONVERSION UNKNOWN [smoFFL] */

/*   *fluidFlowIndexOut /= ??; CONVERSION UNKNOWN [smoFFL] */

   return fluidFlowIndexOut;
}

