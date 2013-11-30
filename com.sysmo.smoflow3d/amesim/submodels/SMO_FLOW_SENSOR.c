/* Submodel SMO_FLOW_SENSOR skeleton created by AME Submodel editing utility
   Sat Nov 30 11:32:10 2013 */



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
#include "SmoFlowAme.h"
#include "flow/FlowBase.h"
#include "media/MediumState.h"

#define _fluidFlowIndex ic[0]
#define _fluidFlow ps[0]

#define _fluidStateInternalIndex ic[1]
#define _fluidStateInternal ps[1]

#define _fluidStateInputIndex ic[2]
#define _fluidStateInput ps[2]
/* <<<<<<<<<<<<End of Private Code. */


/* There are 2 real parameters:

   offset signal offset [null]
   gain   signal gain   [null]
*/


/* There is 1 integer parameter:

   measuredFlowPropertyIndex measured flow property
*/

void smo_flow_sensorin_(int *n, double rp[2], int ip[1], int ic[3]
      , void *ps[3])

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

   if (measuredFlowPropertyIndex < 1 || measuredFlowPropertyIndex > 4)
   {
      amefprintf(stderr, "\nmeasured flow property must be in range [1..4].\n");
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

   Port 1 has 3 variables:

      1 fluidFlowIndexDup                duplicate of fluidFlowIndex 
      2 fluidFlowActivationSignalDup     duplicate of fluidFlowActivationSignal
      3 fluidStateIndex                  fluid state index            [smoTDS] basic variable input  UNPLOTTABLE

   Port 2 has 1 variable:

      1 measuredValue     measured value [null] basic variable output

   Port 3 has 3 variables:

      1 fluidStateIndexDup            duplicate of fluidStateIndex
      2 fluidFlowIndex                fluid flow index             [smoFFL]  basic variable input  UNPLOTTABLE
      3 fluidFlowActivationSignal     fluid flow activation signal [smoFFAS] basic variable input
*/

/*  There are 3 internal variables.

      1 massFlowRate         mass flow rate     [kg/s] basic variable
      2 enthalpyFlowRate     enthalpy flow rate [W]    basic variable
      3 flowTemperature      flow temperature   [K]    basic variable
*/

void smo_flow_sensor_(int *n, double *fluidStateIndex
      , double *measuredValue, double *fluidFlowIndex
      , double *fluidFlowActivationSignal, double *massFlowRate
      , double *enthalpyFlowRate, double *flowTemperature
      , double rp[2], int ip[1], int ic[3], void *ps[3])

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

/*   *fluidStateIndex *= ??; CONVERSION UNKNOWN */
/*   *fluidFlowIndex *= ??; CONVERSION UNKNOWN */
/*   *fluidFlowActivationSignal *= ??; CONVERSION UNKNOWN */

/*
   Set all submodel outputs below:

   *measuredValue = ??;
   *massFlowRate = ??;
   *enthalpyFlowRate = ??;
   *flowTemperature = ??;
*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
   SMOCOMPONENT_PRINT_MAIN_CALC
   if (firstc_()) {
	   _fluidFlowIndex = *fluidFlowIndex;
	   _fluidFlow = FluidFlow_get(_fluidFlowIndex);

	   _fluidStateInputIndex = *fluidStateIndex;
	   _fluidStateInput = MediumState_get(_fluidStateInputIndex);

	   int mediumIndex = Medium_index(MediumState_getMedium(_fluidStateInput));
	   Medium* fluid = Medium_get(mediumIndex);

	   _fluidStateInternal = MediumState_new(fluid);
	   _fluidStateInternalIndex = MediumState_register(_fluidStateInternal);
   }

   *massFlowRate = FluidFlow_getMassFlowRate(_fluidFlow);;
   *enthalpyFlowRate = FluidFlow_getEnthalpyFlowRate(_fluidFlow);

   if (fabs(*massFlowRate) > 1e-12) {
	   double h = *enthalpyFlowRate / *massFlowRate;
	   MediumState_update_ph(_fluidStateInternal, MediumState_p(_fluidStateInput), h);
	   *flowTemperature = MediumState_T(_fluidStateInternal);
   } else {
	   *flowTemperature = 0.0;
   }

   if (measuredFlowPropertyIndex == 1) {
	   *measuredValue = *massFlowRate;
   } else if (measuredFlowPropertyIndex == 2) {
	   *measuredValue = *enthalpyFlowRate;
   } else if (measuredFlowPropertyIndex == 3) {
	   *measuredValue = *flowTemperature;
   } else if (measuredFlowPropertyIndex == 4) {
	   *measuredValue = _fluidFlowIndex;
   } else {
	   *measuredValue = 0.0;
   }
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *fluidStateIndex /= ??; CONVERSION UNKNOWN */
/*   *fluidFlowIndex /= ??; CONVERSION UNKNOWN */
/*   *fluidFlowActivationSignal /= ??; CONVERSION UNKNOWN */
}

