/* Submodel SMO_TEMPERATURE_SENSOR skeleton created by AME Submodel editing utility
   Sat Mar 1 22:25:23 2014 */



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

#define _SUBMODELNAME_ "SMO_TEMPERATURE_SENSOR"

/* >>>>>>>>>>>>Insert Private Code Here. */
#include "SmoFlowAme.h"
#include "volumes/ThermalNode.h"

#define _thermalNode ps[0]
#define _thermalNodeIndex ic[0]

#define _temperature c[0]
/* <<<<<<<<<<<<End of Private Code. */


/* There are 2 real parameters:

   offset signal offset [null]
   gain   signal gain   [null]
*/

void smo_temperature_sensorin_(int *n, double rp[2], double c[1]
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
      2 heatFlowIndex           heat flow index    [smoHFL] basic variable input  UNPLOTTABLE

   Port 2 has 1 variable:

      1 measuredValue     measured value [null] multi line macro 'smo_temperature_sensor_macro0_'

   Port 3 has 2 variables:

      1 heatFlowIndexDup     duplicate of heatFlowIndex
      2 thermalNodeIndex     thermal node index [smoTHN] basic variable input  UNPLOTTABLE
*/

/*  There is 1 internal variable.

      1 temperature     temperature [K] basic variable
*/

void smo_temperature_sensor_(int *n, double *heatFlowIndex
      , double *measuredValue, double *thermalNodeIndex
      , double *temperature, double rp[2], double c[1], int ic[1]
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

   *temperature = ??;
*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
   SMOCOMPONENT_PRINT_MAIN_CALC
   *temperature = _temperature;
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *heatFlowIndex /= ??; CONVERSION UNKNOWN */
/*   *thermalNodeIndex /= ??; CONVERSION UNKNOWN */
}

extern double smo_temperature_sensor_macro0_(int *n
      , double *thermalNodeIndex, double rp[2], double c[1], int ic[1]
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

/*   *thermalNodeIndex *= ??; CONVERSION UNKNOWN */

/*
   Define and return the following macro variable:

   measuredValue = ??;
*/


/* >>>>>>>>>>>>Macro Function macro0 Executable Statements. */
   SMOCOMPONENt_PRINT_MACRO
   if (firstc_()) {
	   _thermalNodeIndex = *thermalNodeIndex;
	   _thermalNode = ThermalNode_get(_thermalNodeIndex);
   }

   _temperature = ThermalNode_getTemperature(_thermalNode);
   measuredValue =  _temperature * gain + offset;
/* <<<<<<<<<<<<End of Macro macro0 Executable Statements. */

/* SI -> Common units conversions. */

/*   *thermalNodeIndex /= ??; CONVERSION UNKNOWN */


   return measuredValue;
}

