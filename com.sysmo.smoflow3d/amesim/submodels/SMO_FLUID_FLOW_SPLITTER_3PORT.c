/* Submodel SMO_FLUID_FLOW_SPLITTER_3PORT skeleton created by AME Submodel editing utility
   Fri Aug 9 12:14:21 2013 */



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

#define _SUBMODELNAME_ "SMO_FLUID_FLOW_SPLITTER_3PORT"

/* >>>>>>>>>>>>Insert Private Code Here. */
#include "flow/FlowBase.h"

#define _flowOutIndex ic[0]
#define _flowOut ps[0]
/* <<<<<<<<<<<<End of Private Code. */
void smo_fluid_flow_splitter_3portin_(int *n, int ic[1], void *ps[1])

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
   _flowOut = FluidFlow_new();
   _flowOutIndex = FluidFlow_register(_flowOut);
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

/*  There are 3 ports.

   Port 1 has 2 variables:

      1 stateIndexDup1     duplicate of stateIndex
      2 flowIndexIn1       flow index in 1 [smoFFL] basic variable input  UNPLOTTABLE

   Port 2 has 2 variables:

      1 flowIndexOut     flow index out [smoFFL] multi line macro 'smo_fluid_flow_splitter_3port_macro0_'  UNPLOTTABLE
      2 stateIndex       state index    [smoTDS] basic variable input  UNPLOTTABLE

   Port 3 has 2 variables:

      1 stateIndexDup3     duplicate of stateIndex
      2 flowIndexIn3       flow index in 3 [smoFFL] basic variable input  UNPLOTTABLE
*/

/*  There are 0 internal variables.

*/

#if 0

/* THE CALCULATION FUNCTION WILL NOT BE CALLED. */

void smo_fluid_flow_splitter_3port_(int *n, double *flowIndexIn1
      , double *flowIndexOut, double *stateIndex, double *flowIndexIn3
      , int ic[1], void *ps[1])

{
   int loop;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   loop = 0;

/* Common -> SI units conversions. */

/*   *flowIndexIn1 *= ??; CONVERSION UNKNOWN */
/*   *flowIndexOut *= ??; CONVERSION UNKNOWN */
/*   *stateIndex *= ??; CONVERSION UNKNOWN */
/*   *flowIndexIn3 *= ??; CONVERSION UNKNOWN */

/*
   Set all submodel outputs below:

*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *flowIndexIn1 /= ??; CONVERSION UNKNOWN */
/*   *flowIndexOut /= ??; CONVERSION UNKNOWN */
/*   *stateIndex /= ??; CONVERSION UNKNOWN */
/*   *flowIndexIn3 /= ??; CONVERSION UNKNOWN */
}

#endif
extern double smo_fluid_flow_splitter_3port_macro0_(int *n
      , double *flowIndexIn1, double *flowIndexIn3, int ic[1]
      , void *ps[1])

{
   double flowIndexOut;
   int loop;
/* >>>>>>>>>>>>Extra Macro Function macro0 Declarations Here. */
/* <<<<<<<<<<<<End of Extra Macro macro0 declarations. */
   loop = 0;

/* Common -> SI units conversions. */

/*   *flowIndexIn1 *= ??; CONVERSION UNKNOWN */
/*   *flowIndexIn3 *= ??; CONVERSION UNKNOWN */

/*
   Define and return the following macro variable:

   flowIndexOut = ??;
*/


/* >>>>>>>>>>>>Macro Function macro0 Executable Statements. */
   FluidFlow* flowIn1 = FluidFlow_get(*flowIndexIn1);
   FluidFlow* flowIn3 = FluidFlow_get(*flowIndexIn3);

   double massFlowIn = FluidFlow_getMassFlowRate(flowIn1) + FluidFlow_getMassFlowRate(flowIn3);
   double enthalpyFlowIn = FluidFlow_getEnthalpyFlowRate(flowIn1) + FluidFlow_getEnthalpyFlowRate(flowIn3);
   FluidFlow_setMassFlowRate(_flowOut, massFlowIn);
   FluidFlow_setEnthalpyFlowRate(_flowOut, enthalpyFlowIn);

   flowIndexOut = _flowOutIndex;
/* <<<<<<<<<<<<End of Macro macro0 Executable Statements. */

/* SI -> Common units conversions. */

/*   *flowIndexIn1 /= ??; CONVERSION UNKNOWN */
/*   *flowIndexIn3 /= ??; CONVERSION UNKNOWN */

/*   *flowIndexOut /= ??; CONVERSION UNKNOWN */

   return flowIndexOut;
}

