/* Submodel SMO_HEAT_FLOW_GAIN skeleton created by AME Submodel editing utility
   ?? ??? 4 09:29:11 2019 */



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

#define _SUBMODELNAME_ "SMO_HEAT_FLOW_GAIN"

/* >>>>>>>>>>>>Insert Private Code Here. */
#include "flow/FlowBase.h"

#define _heatFlowIndexOut3 ic[0]
#define _heatFlowOut3 ps[0]
/* <<<<<<<<<<<<End of Private Code. */
void smo_heat_flow_gainin_(int *n, int ic[1], void *ps[1])

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
   _heatFlowOut3 = HeatFlow_new();
   _heatFlowIndexOut3 = HeatFlow_register(_heatFlowOut3);
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

/*  There are 3 ports.

   Port 1 has 2 variables:

      1 thermalNodeIndexOut1     duplicate of thermalNodeIndexIn3
      2 heatFlowIndexIn1         heat flow index (in) [smoHFL] basic variable input  UNPLOTTABLE

   Port 2 has 1 variable:

      1 heatFlowGain     heat flow gain [null] basic variable input

   Port 3 has 2 variables:

      1 heatFlowIndexOut3       heat flow index (out)   [smoHFL] multi line macro 'smo_heat_flow_gain_macro0_'  UNPLOTTABLE
      2 thermalNodeIndexIn3     thermal node index (in) [smoTHN] basic variable input  UNPLOTTABLE
*/

/*  There are 0 internal variables.

*/

#if 0

/* THE CALCULATION FUNCTION WILL NOT BE CALLED. */

void smo_heat_flow_gain_(int *n, double *heatFlowIndexIn1
      , double *heatFlowGain, double *heatFlowIndexOut3
      , double *thermalNodeIndexIn3, int ic[1], void *ps[1])

{
   int loop;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   loop = 0;

/* Common -> SI units conversions. */

/*   *heatFlowIndexIn1 *= ??; CONVERSION UNKNOWN [smoHFL] */
/*   *heatFlowIndexOut3 *= ??; CONVERSION UNKNOWN [smoHFL] */
/*   *thermalNodeIndexIn3 *= ??; CONVERSION UNKNOWN [smoTHN] */

/*
   Set all submodel outputs below:

*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *heatFlowIndexIn1 /= ??; CONVERSION UNKNOWN [smoHFL] */
/*   *heatFlowIndexOut3 /= ??; CONVERSION UNKNOWN [smoHFL] */
/*   *thermalNodeIndexIn3 /= ??; CONVERSION UNKNOWN [smoTHN] */
}

#endif
extern double smo_heat_flow_gain_macro0_(int *n
      , double *heatFlowIndexIn1, double *heatFlowGain, int ic[1]
      , void *ps[1])

{
   double heatFlowIndexOut3;
   int loop;
/* >>>>>>>>>>>>Extra Macro Function macro0 Declarations Here. */
/* <<<<<<<<<<<<End of Extra Macro macro0 declarations. */
   loop = 0;

/* Common -> SI units conversions. */

/*   *heatFlowIndexIn1 *= ??; CONVERSION UNKNOWN [smoHFL] */

/*
   Define and return the following macro variable:

   heatFlowIndexOut3 = ??;
*/


/* >>>>>>>>>>>>Macro Function macro0 Executable Statements. */
   HeatFlow* heatFlowIn1 = HeatFlow_get(*heatFlowIndexIn1);

   double enthalpyFlowOut = (*heatFlowGain) * HeatFlow_getEnthalpyFlowRate(heatFlowIn1);
   HeatFlow_setEnthalpyFlowRate(_heatFlowOut3, enthalpyFlowOut);

   heatFlowIndexOut3 = _heatFlowIndexOut3;
/* <<<<<<<<<<<<End of Macro macro0 Executable Statements. */

/* SI -> Common units conversions. */

/*   *heatFlowIndexIn1 /= ??; CONVERSION UNKNOWN [smoHFL] */

/*   *heatFlowIndexOut3 /= ??; CONVERSION UNKNOWN [smoHFL] */

   return heatFlowIndexOut3;
}

