/* Submodel SMO_R_FLUID_FLOW_SENSOR skeleton created by AME Submodel editing utility
   Thu Nov 14 11:01:31 2013 */



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

#define _SUBMODELNAME_ "SMO_R_FLUID_FLOW_SENSOR"

/* >>>>>>>>>>>>Insert Private Code Here. */
#include "SmoFlowAme.h"
#include "media/MediumState.h"
#include "Flow_R/FlowComponent_R.h"
#include "Flow_R/Adaptor_R.h"

#define _fluidFlow ps[0]
#define _fluidFlowDirection ic[0]
/* <<<<<<<<<<<<End of Private Code. */


/* There are 2 real parameters:

   offset signal offset [null]
   gain   signal gain   [null]
*/


/* There is 1 integer parameter:

   measuredFlowPropertyIndex measured flow property
*/

void smo_r_fluid_flow_sensorin_(int *n, double rp[2], int ip[1]
      , int ic[3], void *ps[3])

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

   if (measuredFlowPropertyIndex < 1 || measuredFlowPropertyIndex > 2)
   {
      amefprintf(stderr, "\nmeasured flow property must be in range [1..2].\n");
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

      1 outputRCompID1      R-component ID (output, port1) [smoRCompID] multi line macro 'smo_r_fluid_flow_sensor_macro0_'  UNPLOTTABLE
      2 smoRChainIDDupl     duplicate of smoRChainID      
      3 inputRCompID1       R-component ID (input, port1)  [smoRCompID] basic variable input  UNPLOTTABLE

   Port 2 has 1 variable:

      1 measuredValue     measured value [null] basic variable output

   Port 3 has 3 variables:

      1 inputRCompID1Dupl     duplicate of inputRCompID1   
      2 inputRCompID3         R-component ID (input, port3) [smoRCompID]  basic variable input  UNPLOTTABLE
      3 smoRChainID           R-components chain ID         [smoRChainID] basic variable input  UNPLOTTABLE
*/

/*  There are 2 internal variables.

      1 massFlowRate         mass flow rate (at port 1)    [kg/s] basic variable
      2 enthalpyFlowRate     enthalpy flow rate (at port1) [W]    basic variable
*/

void smo_r_fluid_flow_sensor_(int *n, double *outputRCompID1
      , double *inputRCompID1, double *measuredValue
      , double *inputRCompID3, double *smoRChainID
      , double *massFlowRate, double *enthalpyFlowRate, double rp[2]
      , int ip[1], int ic[3], void *ps[3])

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

/*   *outputRCompID1 *= ??; CONVERSION UNKNOWN */
/*   *inputRCompID1 *= ??; CONVERSION UNKNOWN */
/*   *inputRCompID3 *= ??; CONVERSION UNKNOWN */
/*   *smoRChainID *= ??; CONVERSION UNKNOWN */

/*
   Set all submodel outputs below:

   *measuredValue = ??;
   *massFlowRate = ??;
   *enthalpyFlowRate = ??;
*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
   SMOCOMPONENT_PRINT_MAIN_CALC
   if (firstc_()) {
	   Component_R* component_R = Component_R_get(*inputRCompID3);
	   if (Component_R_isFlowComponent(component_R) == 1) {
		   FlowComponent_R* component = (FlowComponent_R*) component_R;
		   int fluidFlowIndex = FlowComponent_R_getFlow2Index(component);
		   _fluidFlow = FluidFlow_get(fluidFlowIndex);

		   _fluidFlowDirection = 1;
	   } else if (Component_R_isBeginAdaptor(component_R) == 1) {
		   Component_R* component_R = Component_R_get(*inputRCompID1);
		   FlowComponent_R* component = (FlowComponent_R*) component_R;
		   int fluidFlowIndex = FlowComponent_R_getFlow1Index(component);
		   _fluidFlow = FluidFlow_get(fluidFlowIndex);

		   _fluidFlowDirection = -1;
	   }
   }

   *massFlowRate = FluidFlow_getMassFlowRate(_fluidFlow) * _fluidFlowDirection;
   *enthalpyFlowRate = FluidFlow_getEnthalpyFlowRate(_fluidFlow) * _fluidFlowDirection;

   if (measuredFlowPropertyIndex == 1) {
	   *measuredValue = *massFlowRate;
   } else if (measuredFlowPropertyIndex == 2) {
	   *measuredValue = *enthalpyFlowRate;
   } else {
	   *measuredValue = 0.0;
   }
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *outputRCompID1 /= ??; CONVERSION UNKNOWN */
/*   *inputRCompID1 /= ??; CONVERSION UNKNOWN */
/*   *inputRCompID3 /= ??; CONVERSION UNKNOWN */
/*   *smoRChainID /= ??; CONVERSION UNKNOWN */
}

extern double smo_r_fluid_flow_sensor_macro0_(int *n
      , double *inputRCompID3, double rp[2], int ip[1], int ic[3]
      , void *ps[3])

{
   double outputRCompID1;
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

/*   *inputRCompID3 *= ??; CONVERSION UNKNOWN */

/*
   Define and return the following macro variable:

   outputRCompID1 = ??;
*/


/* >>>>>>>>>>>>Macro Function macro0 Executable Statements. */
   SMOCOMPONENt_PRINT_MACRO_MSG("outputRCompID1")
   outputRCompID1 = *inputRCompID3;
/* <<<<<<<<<<<<End of Macro macro0 Executable Statements. */

/* SI -> Common units conversions. */

/*   *inputRCompID3 /= ??; CONVERSION UNKNOWN */

/*   *outputRCompID1 /= ??; CONVERSION UNKNOWN */

   return outputRCompID1;
}

