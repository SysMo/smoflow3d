/* Submodel SMO_TEMPERATURE_SOURCE_CONSTANT skeleton created by AME Submodel editing utility
   Sat Aug 24 14:39:08 2013 */



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

#define _SUBMODELNAME_ "SMO_TEMPERATURE_SOURCE_CONSTANT"

/* >>>>>>>>>>>>Insert Private Code Here. */
#include "volumes/ThermalNode.h"

#define _thermalNode ps[0]
#define _thermalNodeIndex ic[0]
/* <<<<<<<<<<<<End of Private Code. */


/* There is 1 real parameter:

   initTemperature initial temperature [K]
*/

void smo_temperature_source_constantin_(int *n, double rp[1]
      , int ic[2], void *ps[2], double *thermalNodeIndex)

{
   int loop, error;
/* >>>>>>>>>>>>Extra Initialization Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Initialization declarations. */
   double initTemperature;

   initTemperature = rp[0];
   loop = 0;
   error = 0;

/*
   If necessary, check values of the following:

   rp[0..0]
*/

/*
   Check and/or reset the following fixed and/or discrete variable

   *thermalNodeIndex = ??;
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
   _thermalNode = ThermalNode_new(sThermalNode_Source);
   _thermalNodeIndex = ThermalNode_register(_thermalNode);

   ThermalNode_setTemperature(_thermalNode, initTemperature);
   *thermalNodeIndex = _thermalNodeIndex;
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

/*  There is 1 port.

   Port 1 has 2 variables:

      1 thermalNodeIndex     thermal node index [smoTHN] fixed  UNPLOTTABLE
      2 heatFlowIndex        heat flow index    [smoHFL] basic variable input  UNPLOTTABLE
*/

/*  There are 0 internal variables.

*/

#if 0

/* THE CALCULATION FUNCTION WILL NOT BE CALLED. */

void smo_temperature_source_constant_(int *n, double *heatFlowIndex
      , double rp[1], int ic[2], void *ps[2])

{
   int loop;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   double initTemperature;

   initTemperature = rp[0];
   loop = 0;

/* Common -> SI units conversions. */

/*   *heatFlowIndex *= ??; CONVERSION UNKNOWN */

/*
   Set all submodel outputs below:

*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *heatFlowIndex /= ??; CONVERSION UNKNOWN */
}

#endif
