/* Submodel SMO_R_FLUID_FLOW_SENSOR skeleton created by AME Submodel editing utility
   Thu Nov 14 14:10:02 2013 */



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
#include "flow_R/ManagerComponents_R.h"
#include "Flow_R/Adaptor_R.h"

#define _manager ps[0]
#define _managerIndex ic[0]

#define _fluidFlow ps[1]
#define _fluidFlowDirection ic[1]
/* <<<<<<<<<<<<End of Private Code. */


/* There are 2 real parameters:

   offset signal offset [null]
   gain   signal gain   [null]
*/


/* There is 1 integer parameter:

   measuredFlowPropertyIndex measured flow property
*/

void smo_r_fluid_flow_sensorin_(int *n, double rp[2], int ip[1]
      , int ic[2], void *ps[2])

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

      1 outputRCompID3     R-component ID (ouput, port3) [smoRCompID]  basic variable output  UNPLOTTABLE
      2 inputRCompID3      R-component ID (input, port3) [smoRCompID]  basic variable input  UNPLOTTABLE
      3 smoRChainID        R-components chain ID         [smoRChainID] basic variable input  UNPLOTTABLE
*/

/*  There are 2 internal variables.

      1 massFlowRate         mass flow rate (at port 1)    [kg/s] basic variable
      2 enthalpyFlowRate     enthalpy flow rate (at port1) [W]    basic variable
*/

void smo_r_fluid_flow_sensor_(int *n, double *outputRCompID1
      , double *inputRCompID1, double *measuredValue
      , double *outputRCompID3, double *inputRCompID3
      , double *smoRChainID, double *massFlowRate
      , double *enthalpyFlowRate, double rp[2], int ip[1], int ic[2]
      , void *ps[2])

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
   *outputRCompID3 = ??;
   *massFlowRate = ??;
   *enthalpyFlowRate = ??;
*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
   SMOCOMPONENT_PRINT_MAIN_CALC

   // Initialization
   if (firstc_()) {
	   _managerIndex = *smoRChainID;
	   _manager = ManagerComponents_R_get(_managerIndex);

	   ManagerComponents_R_addOuterState2(_manager, *inputRCompID1);
   }

   // Try to compute R-components chain
   ManagerComponents_R_compute(_manager);

   // Set internal variables
   if (firstc_()) {
	   Component_R* inputComponent3 = Component_R_get(*inputRCompID3);

	   if (Component_R_isFlowComponent(inputComponent3) == 1) {
		   FlowComponent_R* component = (FlowComponent_R*) inputComponent3;
		   int fluidFlowIndex = FlowComponent_R_getFlow2Index(component);
		   _fluidFlow = FluidFlow_get(fluidFlowIndex);
		   _fluidFlowDirection = 1;
	   } else if (Component_R_isBeginAdaptor(inputComponent3) == 1) {
		   Component_R* inputComponent1 = Component_R_get(*inputRCompID1);
		   if (Component_R_isFlowComponent(inputComponent1) == 1) {
			   FlowComponent_R* component = (FlowComponent_R*) inputComponent1;
			   int fluidFlowIndex = FlowComponent_R_getFlow1Index(component);
			   _fluidFlow = FluidFlow_get(fluidFlowIndex);
			   _fluidFlowDirection = -1;
		   } else {
			   AME_RAISE_ERROR("The R-components chain should contain less than one R-component.");
		   }
	   } else {
		   AME_RAISE_ERROR("Unexpected R-component type on the side of port3.");
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

   // Set output variables
   *outputRCompID3 = *inputRCompID1;
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *outputRCompID1 /= ??; CONVERSION UNKNOWN */
/*   *inputRCompID1 /= ??; CONVERSION UNKNOWN */
/*   *outputRCompID3 /= ??; CONVERSION UNKNOWN */
/*   *inputRCompID3 /= ??; CONVERSION UNKNOWN */
/*   *smoRChainID /= ??; CONVERSION UNKNOWN */
}

extern double smo_r_fluid_flow_sensor_macro0_(int *n
      , double *inputRCompID3, double rp[2], int ip[1], int ic[2]
      , void *ps[2])

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

