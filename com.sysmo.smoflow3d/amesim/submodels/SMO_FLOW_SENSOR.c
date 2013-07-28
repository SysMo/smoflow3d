/* Submodel SMO_FLOW_SENSOR skeleton created by AME Submodel editing utility
   Sun Jul 28 17:45:49 2013 */



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

#define _SUBMODELNAME_ "SMO_FLOW_SENSOR"

/* >>>>>>>>>>>>Insert Private Code Here. */
#include "flow/FluidFlow.h"

#define fluidFlowIndex ic[1]
#define fluidFlow ps[1]
/* <<<<<<<<<<<<End of Private Code. */


/* There are 2 real parameters:

   offset signal offset [null]
   gain   signal gain   [null]
*/


/* There is 1 integer parameter:

   measuredFlowPropertyIndex measured flow property
*/

void smo_flow_sensorin_(int *n, double rp[2], int ip[1], double c[2]
      , int ic[1], void *ps[1])

{
   int loop, error;
/* >>>>>>>>>>>>Extra Initialization Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Initialization declarations. */
   int measuredFlowPropertyIndex;
   double offset, gain;

   measuredFlowPropertyIndex = ip[0];

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

/*   Integer parameter checking:   */

   if (measuredFlowPropertyIndex < 1 || measuredFlowPropertyIndex > 3)
   {
      amefprintf(stderr, "\nmeasured flow property must be in range [1..3].\n");
      error = 2;
   }

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

      1 flowIndexDup     duplicate of flowIndex
      2 stateIndex       state index [smoTDS] basic variable input  UNPLOTTABLE

   Port 2 has 1 variable:

      1 measuredValue     measured value [null] multi line macro 'smo_flow_sensor_macro0_'

   Port 3 has 2 variables:

      1 stateIndexDup     duplicate of stateIndex
      2 flowIndex         flow index  [smoFFL] basic variable input  UNPLOTTABLE
*/

/*  There are 2 internal variables.

      1 massFlowRate         mass flow rate     [kg/s] basic variable
      2 enthalpyFlowRate     enthalpy flow rate [W]    basic variable
*/

void smo_flow_sensor_(int *n, double *stateIndex
      , double *measuredValue, double *flowIndex, double *massFlowRate
      , double *enthalpyFlowRate, double rp[2], int ip[1], double c[2]
      , int ic[1], void *ps[1])

{
   int loop;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   int measuredFlowPropertyIndex;
   double offset, gain;

   measuredFlowPropertyIndex = ip[0];

   offset     = rp[0];
   gain       = rp[1];
   loop = 0;

/* Common -> SI units conversions. */

/*   *stateIndex *= ??; CONVERSION UNKNOWN */
/*   *flowIndex *= ??; CONVERSION UNKNOWN */

/*
   Set all submodel outputs below:

   *massFlowRate = ??;
   *enthalpyFlowRate = ??;
*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
   *massFlowRate = c[0];
   *enthalpyFlowRate = c[1];
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *stateIndex /= ??; CONVERSION UNKNOWN */
/*   *flowIndex /= ??; CONVERSION UNKNOWN */
}

extern double smo_flow_sensor_macro0_(int *n, double *flowIndex
      , double rp[2], int ip[1], double c[2], int ic[1], void *ps[1])

{
   double measuredValue;
   int loop;
/* >>>>>>>>>>>>Extra Macro Function macro0 Declarations Here. */
/* <<<<<<<<<<<<End of Extra Macro macro0 declarations. */
   int measuredFlowPropertyIndex;
   double offset, gain;

   measuredFlowPropertyIndex = ip[0];

   offset     = rp[0];
   gain       = rp[1];
   loop = 0;

/* Common -> SI units conversions. */

/*   *flowIndex *= ??; CONVERSION UNKNOWN */

/*
   Define and return the following macro variable:

   measuredValue = ??;
*/


/* >>>>>>>>>>>>Macro Function macro0 Executable Statements. */
   if (firstc_()) {
	   fluidFlowIndex = *flowIndex;
	   fluidFlow = FluidFlow_get(fluidFlowIndex);
   }

   // Retrieving the objects from the storage
   FluidFlow* fluidFlowObj= (FluidFlow*) fluidFlow;

   c[0] = fluidFlowObj->massFlowRate;
   c[1] = fluidFlowObj->enthalpyFlowRate;

   if (measuredFlowPropertyIndex == 3) {
	   measuredValue = fluidFlowIndex;
   } else {
	   measuredValue = c[measuredFlowPropertyIndex - 1] * gain + offset;
   }
/* <<<<<<<<<<<<End of Macro macro0 Executable Statements. */

/* SI -> Common units conversions. */

/*   *flowIndex /= ??; CONVERSION UNKNOWN */


   return measuredValue;
}

