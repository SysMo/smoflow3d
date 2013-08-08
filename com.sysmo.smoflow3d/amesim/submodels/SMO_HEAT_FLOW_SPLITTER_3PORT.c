/* Submodel SMO_HEAT_FLOW_SPLITTER_3PORT skeleton created by AME Submodel editing utility
   Thu Aug 8 18:29:55 2013 */



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

#define _SUBMODELNAME_ "SMO_HEAT_FLOW_SPLITTER_3PORT"

/* >>>>>>>>>>>>Insert Private Code Here. */
#include "flow/FlowBase.h"
#define _heatFlowOutIndex ic[0]
#define _heatFlowOut ps[0]
/* <<<<<<<<<<<<End of Private Code. */
void smo_heat_flow_splitter_3portin_(int *n, int ic[1], void *ps[1])

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
   _heatFlowOut = HeatFlow_new();
   _heatFlowOutIndex = HeatFlow_register(_heatFlowOut);
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

/*  There are 3 ports.

   Port 1 has 2 variables:

      1 thermalNodeIndexDup1     duplicate of thermalNodeIndex
      2 heatFlowIndex1           heat flow index at port 1 [smoHFL] basic variable input  UNPLOTTABLE

   Port 2 has 2 variables:

      1 heatFlowIndexOut     heat flow index out [smoHFL] multi line macro 'smo_heat_flow_splitter_3port_macro0_'  UNPLOTTABLE
      2 thermalNodeIndex     thermal node index  [smoTHN] basic variable input  UNPLOTTABLE

   Port 3 has 2 variables:

      1 thermalNodeIndexDup3     duplicate of thermalNodeIndex
      2 heatFlowIndex3           heat flow index at port 3 [smoHFL] basic variable input  UNPLOTTABLE
*/

/*  There are 0 internal variables.

*/

#if 0

/* THE CALCULATION FUNCTION WILL NOT BE CALLED. */

void smo_heat_flow_splitter_3port_(int *n, double *heatFlowIndex1
      , double *heatFlowIndexOut, double *thermalNodeIndex
      , double *heatFlowIndex3, int ic[1], void *ps[1])

{
   int loop;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   loop = 0;

/* Common -> SI units conversions. */

/*   *heatFlowIndex1 *= ??; CONVERSION UNKNOWN */
/*   *heatFlowIndexOut *= ??; CONVERSION UNKNOWN */
/*   *thermalNodeIndex *= ??; CONVERSION UNKNOWN */
/*   *heatFlowIndex3 *= ??; CONVERSION UNKNOWN */

/*
   Set all submodel outputs below:

*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *heatFlowIndex1 /= ??; CONVERSION UNKNOWN */
/*   *heatFlowIndexOut /= ??; CONVERSION UNKNOWN */
/*   *thermalNodeIndex /= ??; CONVERSION UNKNOWN */
/*   *heatFlowIndex3 /= ??; CONVERSION UNKNOWN */
}

#endif
extern double smo_heat_flow_splitter_3port_macro0_(int *n
      , double *heatFlowIndex1, double *heatFlowIndex3, int ic[1]
      , void *ps[1])

{
   double heatFlowIndexOut;
   int loop;
/* >>>>>>>>>>>>Extra Macro Function macro0 Declarations Here. */
/* <<<<<<<<<<<<End of Extra Macro macro0 declarations. */
   loop = 0;

/* Common -> SI units conversions. */

/*   *heatFlowIndex1 *= ??; CONVERSION UNKNOWN */
/*   *heatFlowIndex3 *= ??; CONVERSION UNKNOWN */

/*
   Define and return the following macro variable:

   heatFlowIndexOut = ??;
*/


/* >>>>>>>>>>>>Macro Function macro0 Executable Statements. */
   HeatFlow* flowIn1 = HeatFlow_get(*heatFlowIndex1);
   HeatFlow* flowIn3 = HeatFlow_get(*heatFlowIndex3);

   double enthalpyFlowIn = HeatFlow_getEnthalpyFlowRate(flowIn1) + HeatFlow_getEnthalpyFlowRate(flowIn3);
   HeatFlow_setEnthalpyFlowRate(_heatFlowOut, enthalpyFlowIn);

   heatFlowIndexOut = _heatFlowOutIndex;
/* <<<<<<<<<<<<End of Macro macro0 Executable Statements. */

/* SI -> Common units conversions. */

/*   *heatFlowIndex1 /= ??; CONVERSION UNKNOWN */
/*   *heatFlowIndex3 /= ??; CONVERSION UNKNOWN */

/*   *heatFlowIndexOut /= ??; CONVERSION UNKNOWN */

   return heatFlowIndexOut;
}

