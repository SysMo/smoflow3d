/* Submodel SMO_FLUID_FLOW_ZERO skeleton created by AME Submodel editing utility
   Fri Dec 6 19:14:46 2013 */



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

#define _SUBMODELNAME_ "SMO_FLUID_FLOW_ZERO"

/* >>>>>>>>>>>>Insert Private Code Here. */
#include "flow/FlowBase.h"

/* <<<<<<<<<<<<End of Private Code. */
void smo_fluid_flow_zeroin_(int *n, double *fluidFlowIndex
      , double *fluidFlowActivationSignal)

{
   int loop, error;
/* >>>>>>>>>>>>Extra Initialization Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Initialization declarations. */
   loop = 0;
   error = 0;

/*
   Check and/or reset the following fixed and/or discrete variables

   *fluidFlowIndex = ??;
   *fluidFlowActivationSignal = ??;
*/


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
   FluidFlow* fluidFlow = FluidFlow_new();
   *fluidFlowIndex = FluidFlow_register(fluidFlow);
   FluidFlow_setMassFlowRate(fluidFlow, 0);
   FluidFlow_setEnthalpyFlowRate(fluidFlow, 0);
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

/*  There is 1 port.

   Port 1 has 3 variables:

      1 fluidFlowIndex                fluid flow index             [smoFFL]  fixed  UNPLOTTABLE
      2 fluidFlowActivationSignal     fluid flow activation signal [smoFFAS] fixed  UNPLOTTABLE
      3 fluidStateIndex               fluid state index            [smoTDS]  basic variable input  UNPLOTTABLE
*/

/*  There are 0 internal variables.

*/

#if 0

/* THE CALCULATION FUNCTION WILL NOT BE CALLED. */

void smo_fluid_flow_zero_(int *n, double *fluidStateIndex)

{
   int loop;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   loop = 0;

/* Common -> SI units conversions. */

/*   *fluidStateIndex *= ??; CONVERSION UNKNOWN */

/*
   Set all submodel outputs below:

*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *fluidStateIndex /= ??; CONVERSION UNKNOWN */
}

#endif
