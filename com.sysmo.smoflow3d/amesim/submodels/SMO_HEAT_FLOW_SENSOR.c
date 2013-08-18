/* Submodel SMO_HEAT_FLOW_SENSOR skeleton created by AME Submodel editing utility
   Sun Aug 18 14:38:59 2013 */



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

#define _SUBMODELNAME_ "SMO_HEAT_FLOW_SENSOR"

/* >>>>>>>>>>>>Insert Private Code Here. */
#include "flow/FlowBase.h"

#define _heatFlowIndex ic[0]
#define _heatFlow ps[0]

#define _heatFlowRate c[0]
/* <<<<<<<<<<<<End of Private Code. */


/* There are 2 real parameters:

   offset signal offset [null]
   gain   signal gain   [null]
*/

void smo_heat_flow_sensorin_(int *n, double rp[2], double c[1]
      , int ic[1], void *ps[1])

{
   int loop, error;
/* >>>>>>>>>>>>Extra Initialization Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Initialization declarations. */
   double offset, gain;

   offset     = rp[0];
   gain       = rp[1];
   loop = 0;
   error = 0;

/*
   If necessary, check values of the following:

   rp[0..1]
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
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

/*  There are 3 ports.

   Port 1 has 2 variables:

      1 thermalNodeIndexDup     duplicate of thermalNodeIndex
      2 heatFlowIndex           heat flow index [smoHFL] basic variable input  UNPLOTTABLE

   Port 2 has 1 variable:

      1 measuredValue     measured value [null] multi line macro 'smo_heat_flow_sensor_macro0_'

   Port 3 has 2 variables:

      1 heatFlowIndexDup     duplicate of heatFlowIndex
      2 thermalNodeIndex     thermal node index [smoTHN] basic variable input  UNPLOTTABLE
*/

/*  There is 1 internal variable.

      1 heatFlowRate     heat flow rate [W] basic variable
*/

void smo_heat_flow_sensor_(int *n, double *heatFlowIndex
      , double *measuredValue, double *thermalNodeIndex
      , double *heatFlowRate, double rp[2], double c[1], int ic[1]
      , void *ps[1])

{
   int loop;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   double offset, gain;

   offset     = rp[0];
   gain       = rp[1];
   loop = 0;

/* Common -> SI units conversions. */

/*   *heatFlowIndex *= ??; CONVERSION UNKNOWN */
/*   *thermalNodeIndex *= ??; CONVERSION UNKNOWN */

/*
   Set all submodel outputs below:

   *heatFlowRate = ??;
*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
   *heatFlowRate = _heatFlowRate;
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *heatFlowIndex /= ??; CONVERSION UNKNOWN */
/*   *thermalNodeIndex /= ??; CONVERSION UNKNOWN */
}

extern double smo_heat_flow_sensor_macro0_(int *n
      , double *heatFlowIndex, double rp[2], double c[1], int ic[1]
      , void *ps[1])

{
   double measuredValue;
   int loop;
/* >>>>>>>>>>>>Extra Macro Function macro0 Declarations Here. */
/* <<<<<<<<<<<<End of Extra Macro macro0 declarations. */
   double offset, gain;

   offset     = rp[0];
   gain       = rp[1];
   loop = 0;

/* Common -> SI units conversions. */

/*   *heatFlowIndex *= ??; CONVERSION UNKNOWN */

/*
   Define and return the following macro variable:

   measuredValue = ??;
*/


/* >>>>>>>>>>>>Macro Function macro0 Executable Statements. */
   if (firstc_()) {
	   _heatFlowIndex = *heatFlowIndex;
	   _heatFlow = HeatFlow_get(_heatFlowIndex);
   }

   _heatFlowRate = HeatFlow_getEnthalpyFlowRate(_heatFlow);
   measuredValue = _heatFlowRate * gain + offset;
/* <<<<<<<<<<<<End of Macro macro0 Executable Statements. */

/* SI -> Common units conversions. */

/*   *heatFlowIndex /= ??; CONVERSION UNKNOWN */


   return measuredValue;
}

