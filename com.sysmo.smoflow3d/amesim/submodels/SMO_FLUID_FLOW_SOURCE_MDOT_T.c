/* Submodel SMO_FLUID_FLOW_SOURCE_MDOT_T skeleton created by AME Submodel editing utility
   Sun Mar 23 16:51:04 2014 */



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

#define _SUBMODELNAME_ "SMO_FLUID_FLOW_SOURCE_MDOT_T"

/* >>>>>>>>>>>>Insert Private Code Here. */
#include "SmoFlowAme.h"
#include "flow/FlowBase.h"
#include "media/MediumState.h"

#define _fluidFlowIndex ic[0]
#define _fluidFlow ps[0]

#define _fluidStateOutletIndex ic[1]
#define _fluidStateOutlet ps[1]

#define _fluidStateInternalIndex ic[2]
#define _fluidStateInternal ps[2]
/* <<<<<<<<<<<<End of Private Code. */

/* There is 1 integer parameter:

   fluidIndex fluid index
*/

void smo_fluid_flow_source_mdot_tin_(int *n, int ip[1], int ic[3]
      , void *ps[3], double *fluidFlowActivationSignal)

{
   int loop, error;
/* >>>>>>>>>>>>Extra Initialization Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Initialization declarations. */
   int fluidIndex;

   fluidIndex = ip[0];
   loop = 0;
   error = 0;

/*
   Check and/or reset the following fixed and/or discrete variable

   *fluidFlowActivationSignal = ??;
*/


/* >>>>>>>>>>>>Initialization Function Check Statements. */
/* <<<<<<<<<<<<End of Initialization Check Statements. */

/*   Integer parameter checking:   */

   if (fluidIndex < 1 || fluidIndex > 99)
   {
      amefprintf(stderr, "\nfluid index must be in range [1..99].\n");
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
    Medium *fluid = Medium_get(fluidIndex);
	_fluidStateInternal = MediumState_new(fluid);
	_fluidStateInternalIndex = MediumState_register(_fluidStateInternal);
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

/*  There are 3 ports.

   Port 1 has 3 variables:

      1 fluidFlowIndex                fluid flow index             [smoFFL]  multi line macro 'smo_fluid_flow_source_mdot_t_macro0_'  UNPLOTTABLE
      2 fluidFlowActivationSignal     fluid flow activation signal [smoFFAS] fixed  UNPLOTTABLE
      3 fluidStateIndex               fluid state index            [smoTDS]  basic variable input  UNPLOTTABLE

   Port 2 has 1 variable:

      1 massFlowRate     mass flow rate [kg/s] basic variable input

   Port 3 has 1 variable:

      1 outletT     outlet temperature [K] basic variable input
*/

/*  There are 0 internal variables.

*/

#if 0

/* THE CALCULATION FUNCTION WILL NOT BE CALLED. */

void smo_fluid_flow_source_mdot_t_(int *n, double *fluidFlowIndex
      , double *fluidStateIndex, double *massFlowRate, double *outletT
      , int ip[1], int ic[3], void *ps[3])

{
   int loop;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   int fluidIndex;

   fluidIndex = ip[0];
   loop = 0;

/* Common -> SI units conversions. */

/*   *fluidFlowIndex *= ??; CONVERSION UNKNOWN */
/*   *fluidStateIndex *= ??; CONVERSION UNKNOWN */

/*
   Set all submodel outputs below:

*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *fluidFlowIndex /= ??; CONVERSION UNKNOWN */
/*   *fluidStateIndex /= ??; CONVERSION UNKNOWN */
}

#endif
extern double smo_fluid_flow_source_mdot_t_macro0_(int *n
      , double *fluidStateIndex, double *massFlowRate, double *outletT
      , int ip[1], int ic[3], void *ps[3])

{
   double fluidFlowIndex;
   int loop;
/* >>>>>>>>>>>>Extra Macro Function macro0 Declarations Here. */
/* <<<<<<<<<<<<End of Extra Macro macro0 declarations. */
   int fluidIndex;

   fluidIndex = ip[0];
   loop = 0;

/* Common -> SI units conversions. */

/*   *fluidStateIndex *= ??; CONVERSION UNKNOWN */

/*
   Define and return the following macro variable:

   fluidFlowIndex = ??;
*/


/* >>>>>>>>>>>>Macro Function macro0 Executable Statements. */
	SMOCOMPONENt_PRINT_MACRO
	if (firstc_()) {
		_fluidFlow = FluidFlow_new();
		_fluidFlowIndex = FluidFlow_register(_fluidFlow);

		_fluidStateOutletIndex = *fluidStateIndex;
		_fluidStateOutlet = MediumState_get(_fluidStateOutletIndex);
	}

	// Compute HDot outlet
    double pOut = MediumState_p(_fluidStateOutlet);
    MediumState_update_Tp(_fluidStateInternal, *outletT, pOut);
    double HDotOut = (*massFlowRate) * MediumState_h(_fluidStateInternal);

	FluidFlow_setMassFlowRate(_fluidFlow, *massFlowRate);
	FluidFlow_setEnthalpyFlowRate(_fluidFlow, HDotOut);

	fluidFlowIndex = _fluidFlowIndex;
/* <<<<<<<<<<<<End of Macro macro0 Executable Statements. */

/* SI -> Common units conversions. */

/*   *fluidStateIndex /= ??; CONVERSION UNKNOWN */

/*   *fluidFlowIndex /= ??; CONVERSION UNKNOWN */

   return fluidFlowIndex;
}

