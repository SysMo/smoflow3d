/* Submodel SMO_HEAT_SOURCE skeleton created by AME Submodel editing utility
   Thu Aug 8 15:47:19 2013 */



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

#define _SUBMODELNAME_ "SMO_HEAT_SOURCE"

/* >>>>>>>>>>>>Insert Private Code Here. */
#include "flow/FlowBase.h"

#define _heatFlowIndex ic[0]
#define _heatFlow ps[0]
/* <<<<<<<<<<<<End of Private Code. */
void smo_heat_sourcein_(int *n, int ic[1], void *ps[1])

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
   _heatFlow = HeatFlow_new();
   _heatFlowIndex = HeatFlow_register(_heatFlow);
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

/*  There are 2 ports.

   Port 1 has 1 variable:

      1 heatFlowRate     heat flow rate [W] basic variable input

   Port 2 has 2 variables:

      1 flowIndex      flow index  [smoHFL] basic variable output  UNPLOTTABLE
      2 stateIndex     state index [smoTNI] basic variable input  UNPLOTTABLE
*/

/*  There are 0 internal variables.

*/

void smo_heat_source_(int *n, double *heatFlowRate, double *flowIndex
      , double *stateIndex, int ic[1], void *ps[1])

{
   int loop;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   loop = 0;

/* Common -> SI units conversions. */

/*   *stateIndex *= ??; CONVERSION UNKNOWN */

/*
   Set all submodel outputs below:

   *flowIndex  = ??;
*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
   HeatFlow_setEnthalpyFlowRate(_heatFlow, *heatFlowRate);
   *flowIndex = _heatFlowIndex;
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *flowIndex /= ??; CONVERSION UNKNOWN */
/*   *stateIndex /= ??; CONVERSION UNKNOWN */
}

