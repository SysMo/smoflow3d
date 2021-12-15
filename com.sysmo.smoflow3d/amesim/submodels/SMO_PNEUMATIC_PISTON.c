/* Submodel SMO_PNEUMATIC_PISTON skeleton created by AME Submodel editing utility
   ?? ??? 15 12:55:26 2021 */



#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
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

#define _SUBMODELNAME_ "SMO_PNEUMATIC_PISTON"

/* >>>>>>>>>>>>Insert Private Code Here. */
#include "SmoFlowAme.h"
#include "pneumatic/PneumaticPiston.h"

#define _component ps[0]

#define _fluidFlow1 ps[1]
#define _fluidFlow1Index ic[1]
/* <<<<<<<<<<<<End of Private Code. */


/* There are 2 real parameters:

   dp piston diameter [mm -> m]
   dr rod diameter    [mm -> m]
*/

void smo_pneumatic_pistonin_(int *n, double rp[2], int ic[2]
      , void *ps[2])

{
   int loop, error;
/* >>>>>>>>>>>>Extra Initialization Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Initialization declarations. */
   double dp, dr;

   dp         = rp[0];
   dr         = rp[1];
   loop = 0;
   error = 0;

/*
   If necessary, check values of the following:

   rp[0..1]
*/


/* >>>>>>>>>>>>Initialization Function Check Statements. */
/* <<<<<<<<<<<<End of Initialization Check Statements. */

   if (ameHandleSubmodelError(_SUBMODELNAME_, *n, error))
   {
      return;
   }

/* Common -> SI units conversions. */

   rp[0]    *= 1.00000000000000e-03;
   dp         = rp[0];
   rp[1]    *= 1.00000000000000e-03;
   dr         = rp[1];


/* >>>>>>>>>>>>Initialization Function Executable Statements. */
   _component = PneumaticPiston_new(
   		dp, //diameterPiston
   		dr //diameterRod
		);
   	SMOCOMPONENT_SET_PROPS(_component)

   _fluidFlow1 = FluidFlow_new();
   FluidFlow_zero(_fluidFlow1);
   _fluidFlow1Index = FluidFlow_register(_fluidFlow1);
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

/*  There are 3 ports.

   Port 1 has 3 variables:

      1 fluidFlow1Index               fluid flow1 index                                                      [smoFFL]  multi line macro 'smo_pneumatic_piston_macro0_'  UNPLOTTABLE
      2 fluidFlowActivationSignal     flow activation signal = {-1 - not used; 0 - deactivate; 1 - activate} [smoFFAS] multi line macro shared with 'fluidFlow1Index'
      3 fluidState1Index              fluid state1 index                                                     [smoTDS]  basic variable input  UNPLOTTABLE

   Port 2 has 3 variables:

      1 v2     duplicate of v3       
      2 x2     duplicate of x3       
      3 f2     force at port2         [N] basic variable input

   Port 3 has 3 variables:

      1 f3     force at port3        [N]   multi line macro 'smo_pneumatic_piston_macro1_'
      2 v3     velocity at port3     [m/s] basic variable input
      3 x3     displacement at port3 [m]   basic variable input
*/

/*  There are 0 internal variables.

*/

void smo_pneumatic_piston_(int *n, double *fluidFlow1Index
      , double *fluidFlowActivationSignal, double *fluidState1Index
      , double *f2, double *f3, double *v3, double *x3, double rp[2]
      , int ic[2], void *ps[2])

{
   int loop;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   double dp, dr;

   dp         = rp[0];
   dr         = rp[1];
   loop = 0;

/* Common -> SI units conversions. */

/*   *fluidFlow1Index *= ??; CONVERSION UNKNOWN [smoFFL] */
/*   *fluidFlowActivationSignal *= ??; CONVERSION UNKNOWN [smoFFAS] */
/*   *fluidState1Index *= ??; CONVERSION UNKNOWN [smoTDS] */

/*
   Set all submodel outputs below:

*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *fluidFlow1Index /= ??; CONVERSION UNKNOWN [smoFFL] */
/*   *fluidFlowActivationSignal /= ??; CONVERSION UNKNOWN [smoFFAS] */
/*   *fluidState1Index /= ??; CONVERSION UNKNOWN [smoTDS] */
}

extern double smo_pneumatic_piston_macro0_(int *n
      , double *fluidFlowActivationSignal, double rp[2], int ic[2]
      , void *ps[2])

{
   double fluidFlow1Index;
   int loop;
/* >>>>>>>>>>>>Extra Macro Function macro0 Declarations Here. */
/* <<<<<<<<<<<<End of Extra Macro macro0 declarations. */
   double dp, dr;

   dp         = rp[0];
   dr         = rp[1];
   loop = 0;

/*
   Define and return the following macro variable:

   fluidFlow1Index = ??;

   Define the following shared macro variable(s):

   *fluidFlowActivationSignal = ??;
*/


/* >>>>>>>>>>>>Macro Function macro0 Executable Statements. */
   fluidFlow1Index = _fluidFlow1Index;
   *fluidFlowActivationSignal = -1; //-1 - not used
/* <<<<<<<<<<<<End of Macro macro0 Executable Statements. */

/* SI -> Common units conversions. */

/*   *fluidFlowActivationSignal /= ??; CONVERSION UNKNOWN [smoFFAS] */

/*   *fluidFlow1Index /= ??; CONVERSION UNKNOWN [smoFFL] */

   return fluidFlow1Index;
}

extern double smo_pneumatic_piston_macro1_(int *n
      , double *fluidState1Index, double *f2, double rp[2], int ic[2]
      , void *ps[2])

{
   double f3;
   int loop;
/* >>>>>>>>>>>>Extra Macro Function macro1 Declarations Here. */
/* <<<<<<<<<<<<End of Extra Macro macro1 declarations. */
   double dp, dr;

   dp         = rp[0];
   dr         = rp[1];
   loop = 0;

/* Common -> SI units conversions. */

/*   *fluidState1Index *= ??; CONVERSION UNKNOWN [smoTDS] */

/*
   Define and return the following macro variable:

   f3         = ??;
*/


/* >>>>>>>>>>>>Macro Function macro1 Executable Statements. */
    SMOCOMPONENt_PRINT_MACRO
	if (firstc_()) {
		MediumState* state1 = MediumState_get(*fluidState1Index);
		PneumaticPiston_init(_component, state1);
	}


   f3 = *f2 + PneumaticPiston_getPressureForceOnPiston(_component) ;
/* <<<<<<<<<<<<End of Macro macro1 Executable Statements. */

/* SI -> Common units conversions. */

/*   *fluidState1Index /= ??; CONVERSION UNKNOWN [smoTDS] */


   return f3;
}

