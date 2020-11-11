/* Submodel SMO_FLUID_STATE_FLOW_SENSOR skeleton created by AME Submodel editing utility
   ?? ??? 11 11:31:54 2020 */



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

#define _SUBMODELNAME_ "SMO_FLUID_STATE_FLOW_SENSOR"

/* >>>>>>>>>>>>Insert Private Code Here. */
#include "SmoFlowAme.h"
#include "flow/FlowBase.h"
#include "media/MediumState.h"

#define _fluidStateIndex ic[0]
#define _fluidState ps[0]

#define _fluidFlowIndex ic[1]
#define _fluidFlow ps[1]
/* <<<<<<<<<<<<End of Private Code. */


/* There is 1 real parameter:

   flowArea flow area [mm**2 -> m**2]
*/


/* There is 1 integer parameter:

   propertyIndex measured flow property
*/

void smo_fluid_state_flow_sensorin_(int *n, double rp[1], int ip[1]
      , double c[3], int ic[2], void *ps[2])

{
   int loop, error;
/* >>>>>>>>>>>>Extra Initialization Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Initialization declarations. */
   int propertyIndex;
   double flowArea;

   propertyIndex = ip[0];

   flowArea   = rp[0];
   loop = 0;
   error = 0;

/*
   If necessary, check values of the following:

   rp[0..0]
*/


/* >>>>>>>>>>>>Initialization Function Check Statements. */
/* <<<<<<<<<<<<End of Initialization Check Statements. */

/*   Integer parameter checking:   */

   if (propertyIndex < 1 || propertyIndex > 4)
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

/* Common -> SI units conversions. */

   rp[0]    *= 1.00000000000000e-006;
   flowArea   = rp[0];


/* >>>>>>>>>>>>Initialization Function Executable Statements. */
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

/*  There are 3 ports.

   Port 1 has 3 variables:

      1 fluidStateIndexDup            duplicate of fluidStateIndex
      2 fluidFlowIndex                fluid flow index             [smoFFL]  basic variable input  UNPLOTTABLE
      3 fluidFlowActivationSignal     fluid flow activation signal [smoFFAS] basic variable input

   Port 2 has 1 variable:

      1 measuredValue     measured value [null] multi line macro 'smo_fluid_state_flow_sensor_macro0_'

   Port 3 has 3 variables:

      1 fluidFlowIndexDup                duplicate of fluidFlowIndex 
      2 fluidFlowActivationSignalDup     duplicate of fluidFlowActivationSignal
      3 fluidStateIndex                  fluid state index            [smoTDS] basic variable input  UNPLOTTABLE
*/

/*  There are 3 internal variables.

      1 vFlow3               velocity of the flow (port3 -> port1)         [m/s]       basic variable
      2 dynamicPressure3     dynamic pressure of the flow (port3 -> port1) [bar -> Pa] basic variable
      3 machNumber3          Mach number of the flow                       [null]      basic variable
*/

void smo_fluid_state_flow_sensor_(int *n, double *fluidFlowIndex
      , double *fluidFlowActivationSignal, double *measuredValue
      , double *fluidStateIndex, double *vFlow3
      , double *dynamicPressure3, double *machNumber3, double rp[1]
      , int ip[1], double c[3], int ic[2], void *ps[2])

{
   int loop;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   int propertyIndex;
   double flowArea;

   propertyIndex = ip[0];

   flowArea   = rp[0];
   loop = 0;

/* Common -> SI units conversions. */

/*   *fluidFlowIndex *= ??; CONVERSION UNKNOWN [smoFFL] */
/*   *fluidFlowActivationSignal *= ??; CONVERSION UNKNOWN [smoFFAS] */
/*   *fluidStateIndex *= ??; CONVERSION UNKNOWN [smoTDS] */

/*
   Set all submodel outputs below:

   *vFlow3     = ??;
   *dynamicPressure3 = ??;
   *machNumber3 = ??;
*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
   	SMOCOMPONENT_PRINT_MAIN_CALC
	*vFlow3 = c[0];
	*dynamicPressure3 = c[1];
	*machNumber3 = c[2];
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *fluidFlowIndex /= ??; CONVERSION UNKNOWN [smoFFL] */
/*   *fluidFlowActivationSignal /= ??; CONVERSION UNKNOWN [smoFFAS] */
/*   *fluidStateIndex /= ??; CONVERSION UNKNOWN [smoTDS] */
   *dynamicPressure3 /= 1.00000000000000e+005;
}

extern double smo_fluid_state_flow_sensor_macro0_(int *n
      , double *fluidFlowIndex, double *fluidStateIndex, double rp[1]
      , int ip[1], double c[3], int ic[2], void *ps[2])

{
   double measuredValue;
   int loop;
/* >>>>>>>>>>>>Extra Macro Function macro0 Declarations Here. */
/* <<<<<<<<<<<<End of Extra Macro macro0 declarations. */
   int propertyIndex;
   double flowArea;

   propertyIndex = ip[0];

   flowArea   = rp[0];
   loop = 0;

/* Common -> SI units conversions. */

/*   *fluidFlowIndex *= ??; CONVERSION UNKNOWN [smoFFL] */
/*   *fluidStateIndex *= ??; CONVERSION UNKNOWN [smoTDS] */

/*
   Define and return the following macro variable:

   measuredValue = ??;
*/


/* >>>>>>>>>>>>Macro Function macro0 Executable Statements. */
	SMOCOMPONENt_PRINT_MACRO
	if (firstc_()) {
		_fluidStateIndex = *fluidStateIndex;
		_fluidState = MediumState_get(_fluidStateIndex);

		_fluidFlowIndex = *fluidFlowIndex;
		_fluidFlow = FluidFlow_get(_fluidFlowIndex);
	}

	static const double outputInternalGain[3] = {
	   1, 1e-5, 1
	};

	// Compute flow variables
	if (flowArea == 0) {
		c[0] = 0;
		c[1] = 0;
		c[2] = 0;
	} else {
		double rho = MediumState_rho(_fluidState);
		double mDot = -FluidFlow_getMassFlowRate(_fluidFlow);
		double vFlow = mDot / (rho * flowArea);
		double dynamicPressure = rho * vFlow * vFlow / 2;
		double machNumber = vFlow / MediumState_speed_sound(_fluidState);
		c[0] = vFlow;
		c[1] = dynamicPressure;
		c[2] = machNumber;
	}

	if (propertyIndex == 4) {
		measuredValue = _fluidStateIndex;
	} else {
		measuredValue = c[propertyIndex - 1] * outputInternalGain[propertyIndex - 1];
	}
/* <<<<<<<<<<<<End of Macro macro0 Executable Statements. */

/* SI -> Common units conversions. */

/*   *fluidFlowIndex /= ??; CONVERSION UNKNOWN [smoFFL] */
/*   *fluidStateIndex /= ??; CONVERSION UNKNOWN [smoTDS] */


   return measuredValue;
}

