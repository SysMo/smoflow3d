/* Submodel SMO_HEAT_FLOW_SPLITTER_5PORT skeleton created by AME Submodel editing utility
   Fri Mar 24 10:51:00 2017 */



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

#define _SUBMODELNAME_ "SMO_HEAT_FLOW_SPLITTER_5PORT"

/* >>>>>>>>>>>>Insert Private Code Here. */
#include "flow/FlowBase.h"
 
#define _heatFlowIndexOutlet ic[0]
#define _heatFlowOutlet ps[0]
/* <<<<<<<<<<<<End of Private Code. */
void smo_heat_flow_splitter_5portin_(int *n, int ic[1], void *ps[1])

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
   _heatFlowOutlet = HeatFlow_new();
   _heatFlowIndexOutlet = HeatFlow_register(_heatFlowOutlet);
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

/*  There are 5 ports.

   Port 1 has 2 variables:

      1 thermalNodeIndexDup1     duplicate of thermalNodeIndex
      2 heatFlowIndex1           heat flow index at port 1 [smoHFL] basic variable input  UNPLOTTABLE

   Port 2 has 2 variables:

      1 heatFlowIndexOut     heat flow index out [smoHFL] multi line macro 'smo_heat_flow_splitter_5port_macro0_'  UNPLOTTABLE
      2 thermalNodeIndex     thermal node index  [smoTHN] basic variable input  UNPLOTTABLE

   Port 3 has 2 variables:

      1 thermalNodeIndexDup3     duplicate of thermalNodeIndex
      2 heatFlowIndex3           heat flow index at port 3 [smoHFL] basic variable input  UNPLOTTABLE

   Port 4 has 2 variables:

      1 thermalNodeIndexDup4     duplicate of thermalNodeIndex
      2 heatFlowIndex4           heat flow index at port 4 [smoHFL] basic variable input  UNPLOTTABLE

   Port 5 has 2 variables:

      1 thermalNodeIndexDup5     duplicate of thermalNodeIndex
      2 heatFlowIndex5           heat flow index at port 5 [smoHFL] basic variable input  UNPLOTTABLE
*/

/*  There are 0 internal variables.

*/

#if 0

/* THE CALCULATION FUNCTION WILL NOT BE CALLED. */

void smo_heat_flow_splitter_5port_(int *n, double *heatFlowIndex1
      , double *heatFlowIndexOut, double *thermalNodeIndex
      , double *heatFlowIndex3, double *heatFlowIndex4
      , double *heatFlowIndex5, int ic[1], void *ps[1])

{
   int loop;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   loop = 0;

/* Common -> SI units conversions. */

/*   *heatFlowIndex1 *= ??; CONVERSION UNKNOWN [smoHFL] */
/*   *heatFlowIndexOut *= ??; CONVERSION UNKNOWN [smoHFL] */
/*   *thermalNodeIndex *= ??; CONVERSION UNKNOWN [smoTHN] */
/*   *heatFlowIndex3 *= ??; CONVERSION UNKNOWN [smoHFL] */
/*   *heatFlowIndex4 *= ??; CONVERSION UNKNOWN [smoHFL] */
/*   *heatFlowIndex5 *= ??; CONVERSION UNKNOWN [smoHFL] */

/*
   Set all submodel outputs below:

*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *heatFlowIndex1 /= ??; CONVERSION UNKNOWN [smoHFL] */
/*   *heatFlowIndexOut /= ??; CONVERSION UNKNOWN [smoHFL] */
/*   *thermalNodeIndex /= ??; CONVERSION UNKNOWN [smoTHN] */
/*   *heatFlowIndex3 /= ??; CONVERSION UNKNOWN [smoHFL] */
/*   *heatFlowIndex4 /= ??; CONVERSION UNKNOWN [smoHFL] */
/*   *heatFlowIndex5 /= ??; CONVERSION UNKNOWN [smoHFL] */
}

#endif
extern double smo_heat_flow_splitter_5port_macro0_(int *n
      , double *heatFlowIndex1, double *heatFlowIndex3
      , double *heatFlowIndex4, double *heatFlowIndex5, int ic[1]
      , void *ps[1])

{
   double heatFlowIndexOut;
   int loop;
/* >>>>>>>>>>>>Extra Macro Function macro0 Declarations Here. */
/* <<<<<<<<<<<<End of Extra Macro macro0 declarations. */
   loop = 0;

/* Common -> SI units conversions. */

/*   *heatFlowIndex1 *= ??; CONVERSION UNKNOWN [smoHFL] */
/*   *heatFlowIndex3 *= ??; CONVERSION UNKNOWN [smoHFL] */
/*   *heatFlowIndex4 *= ??; CONVERSION UNKNOWN [smoHFL] */
/*   *heatFlowIndex5 *= ??; CONVERSION UNKNOWN [smoHFL] */

/*
   Define and return the following macro variable:

   heatFlowIndexOut = ??;
*/


/* >>>>>>>>>>>>Macro Function macro0 Executable Statements. */
   HeatFlow* flowIn1 = HeatFlow_get(*heatFlowIndex1);
   HeatFlow* flowIn3 = HeatFlow_get(*heatFlowIndex3);
   HeatFlow* flowIn4 = HeatFlow_get(*heatFlowIndex4);
   HeatFlow* flowIn5 = HeatFlow_get(*heatFlowIndex5);
 
   double enthalpyFlowIn = HeatFlow_getEnthalpyFlowRate(flowIn1) + HeatFlow_getEnthalpyFlowRate(flowIn3)
		   + HeatFlow_getEnthalpyFlowRate(flowIn4) + HeatFlow_getEnthalpyFlowRate(flowIn5);
   HeatFlow_setEnthalpyFlowRate(_heatFlowOutlet, enthalpyFlowIn);
 
   heatFlowIndexOut = _heatFlowIndexOutlet;
/* <<<<<<<<<<<<End of Macro macro0 Executable Statements. */

/* SI -> Common units conversions. */

/*   *heatFlowIndex1 /= ??; CONVERSION UNKNOWN [smoHFL] */
/*   *heatFlowIndex3 /= ??; CONVERSION UNKNOWN [smoHFL] */
/*   *heatFlowIndex4 /= ??; CONVERSION UNKNOWN [smoHFL] */
/*   *heatFlowIndex5 /= ??; CONVERSION UNKNOWN [smoHFL] */

/*   *heatFlowIndexOut /= ??; CONVERSION UNKNOWN [smoHFL] */

   return heatFlowIndexOut;
}

