/* Submodel SMO_FLUID_FLOW_SOURCE skeleton created by AME Submodel editing utility
   Thu Sep 19 17:06:00 2013 */



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

#define _SUBMODELNAME_ "SMO_FLUID_FLOW_SOURCE"

/* >>>>>>>>>>>>Insert Private Code Here. */
#include "SmoFlowAme.h"
#include "flow/FlowBase.h"

#define _fluidFlowIndex ic[0]
#define _fluidFlow ps[0]
/* <<<<<<<<<<<<End of Private Code. */
void smo_fluid_flow_sourcein_(int *n, int ic[1], void *ps[1])

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
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

/*  There are 3 ports.

   Port 1 has 2 variables:

      1 fluidFlowIndex      fluid flow index   [smoFFL] multi line macro 'smo_fluid_flow_source_macro0_'  UNPLOTTABLE
      2 fluidStateIndex     fluid state index  [smoTDS] basic variable input  UNPLOTTABLE

   Port 2 has 1 variable:

      1 massFlowRate     mass flow rate [kg/s] basic variable input

   Port 3 has 1 variable:

      1 enthalpyFlowRate     enthalpy flow rate [W] basic variable input
*/

/*  There are 0 internal variables.

*/

#if 0

/* THE CALCULATION FUNCTION WILL NOT BE CALLED. */

void smo_fluid_flow_source_(int *n, double *fluidFlowIndex
      , double *fluidStateIndex, double *massFlowRate
      , double *enthalpyFlowRate, int ic[1], void *ps[1])

{
   int loop;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   loop = 0;

/* Common -> SI units conversions. */

/*   *fluidFlowIndex *= ??; CONVERSION UNKNOWN */
/*   *fluidStateIndex *= ??; CONVERSION UNKNOWN */

/*
   Set all submodel outputs below:

*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *fluidFlowIndex /= ??; CONVERSION UNKNOWN */
/*   *fluidStateIndex /= ??; CONVERSION UNKNOWN */
}

#endif
extern double smo_fluid_flow_source_macro0_(int *n
      , double *massFlowRate, double *enthalpyFlowRate, int ic[1]
      , void *ps[1])

{
   double fluidFlowIndex;
   int loop;
/* >>>>>>>>>>>>Extra Macro Function macro0 Declarations Here. */
/* <<<<<<<<<<<<End of Extra Macro macro0 declarations. */
   loop = 0;

/*
   Define and return the following macro variable:

   fluidFlowIndex = ??;
*/


/* >>>>>>>>>>>>Macro Function macro0 Executable Statements. */
   SMOCOMPONENt_PRINT_MACRO
   if (firstc_()) {
  	   _fluidFlow = FluidFlow_new();
  	   _fluidFlowIndex = FluidFlow_register(_fluidFlow);
     }

     FluidFlow_setMassFlowRate(_fluidFlow, *massFlowRate);
     FluidFlow_setEnthalpyFlowRate(_fluidFlow, *enthalpyFlowRate);

     fluidFlowIndex = _fluidFlowIndex;
/* <<<<<<<<<<<<End of Macro macro0 Executable Statements. */

/*   *fluidFlowIndex /= ??; CONVERSION UNKNOWN */

   return fluidFlowIndex;
}

