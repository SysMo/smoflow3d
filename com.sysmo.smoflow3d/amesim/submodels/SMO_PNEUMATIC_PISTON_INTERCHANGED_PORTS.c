/* Submodel SMO_PNEUMATIC_PISTON_INTERCHANGED_PORTS skeleton created by AME Submodel editing utility
   ?? ??? 14 16:45:52 2022 */



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

#define _SUBMODELNAME_ "SMO_PNEUMATIC_PISTON_INTERCHANGED_PORTS"

/* >>>>>>>>>>>>Insert Private Code Here. */
#include "SmoFlowAme.h"
#include "pneumatic/PneumaticPiston.h"

#define _component ps[0]

#define _fluidFlow1 ps[1]
#define _fluidFlow1Index ic[1]
/* <<<<<<<<<<<<End of Private Code. */


/* There are 3 real parameters:

   dp piston diameter                            [mm -> m]
   dr rod diameter                               [mm -> m]
   x0 length of the chamber at zero displacement [mm -> m]
*/

void smo_pneumatic_piston_interchanged_portsin_(int *n, double rp[3]
      , int ic[2], void *ps[2])

{
   int loop, error;
/* >>>>>>>>>>>>Extra Initialization Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Initialization declarations. */
   double dp, dr, x0;

   dp         = rp[0];
   dr         = rp[1];
   x0         = rp[2];
   loop = 0;
   error = 0;

/*
   If necessary, check values of the following:

   rp[0..2]
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
   rp[2]    *= 1.00000000000000e-03;
   x0         = rp[2];


/* >>>>>>>>>>>>Initialization Function Executable Statements. */
	_component = PneumaticPiston_new(
			dp, //diameterPiston
			dr, //diameterRod
			x0); //chamber length at zero displacement

	SMOCOMPONENT_SET_PROPS(_component)

	_fluidFlow1 = FluidFlow_new();
	FluidFlow_zero(_fluidFlow1);
	_fluidFlow1Index = FluidFlow_register(_fluidFlow1);
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

/*  There are 3 ports.

   Port 1 has 3 variables:

      1 fluidFlow1Index               fluid flow1 index                                                      [smoFFL]  basic variable output  UNPLOTTABLE
      2 fluidFlowActivationSignal     flow activation signal = {-1 - not used; 0 - deactivate; 1 - activate} [smoFFAS] basic variable output
      3 fluidState1Index              fluid state1 index                                                     [smoTDS]  basic variable input  UNPLOTTABLE

   Port 2 has 3 variables:

      1 f2     force at port2        [N]   multi line macro 'smo_pneumatic_piston_interchanged_ports_macro0_'
      2 v2     velocity at port2     [m/s] basic variable input
      3 x2     displacement at port2 [m]   basic variable input

   Port 3 has 3 variables:

      1 v3     duplicate of v2      
      2 x3     duplicate of x2      
      3 f3     force at port3        [N] basic variable input
*/

/*  There are 5 internal variables.

      1 pistonArea      piston area                    [mm**2 -> m**2] multi line macro shared with 'f2'
      2 pistonForce     piston force                   [N]             multi line macro shared with 'f2'
      3 length          length of chamber              [mm -> m]       basic variable
      4 volume          volume at port-1               [L -> m**3]     basic variable
      5 volumeDot       derivative of volume at port-1 [L/s -> m**3/s] basic variable
*/

void smo_pneumatic_piston_interchanged_ports_(int *n
      , double *fluidFlow1Index, double *fluidFlowActivationSignal
      , double *fluidState1Index, double *f2, double *v2, double *x2
      , double *f3, double *pistonArea, double *pistonForce
      , double *length, double *volume, double *volumeDot
      , double rp[3], int ic[2], void *ps[2])

{
   int loop;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   double dp, dr, x0;

   dp         = rp[0];
   dr         = rp[1];
   x0         = rp[2];
   loop = 0;

/* Common -> SI units conversions. */

/*   *fluidState1Index *= ??; CONVERSION UNKNOWN [smoTDS] */
   *pistonArea *= 1.00000000000000e-06;

/*
   Set all submodel outputs below:

   *fluidFlow1Index = ??;
   *fluidFlowActivationSignal = ??;
   *length     = ??;
   *volume     = ??;
   *volumeDot  = ??;
*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
   	PneumaticPiston_compute(_component, -(*x2), -(*v2));

	*length = PneumaticPiston_getLength(_component);
	*volume = PneumaticPiston_getVolume(_component);
	*volumeDot = PneumaticPiston_getVolumeDot(_component);

	FluidFlow_setVolume(_fluidFlow1, *volume);
	FluidFlow_setVolumeDot(_fluidFlow1, *volumeDot);
	*fluidFlow1Index = _fluidFlow1Index;

	*fluidFlowActivationSignal = -1; //-1 - not used
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *fluidFlow1Index /= ??; CONVERSION UNKNOWN [smoFFL] */
/*   *fluidFlowActivationSignal /= ??; CONVERSION UNKNOWN [smoFFAS] */
/*   *fluidState1Index /= ??; CONVERSION UNKNOWN [smoTDS] */
   *pistonArea /= 1.00000000000000e-06;
   *length   /= 1.00000000000000e-03;
   *volume   /= 1.00000000000000e-03;
   *volumeDot /= 1.00000000000000e-03;
}

extern double smo_pneumatic_piston_interchanged_ports_macro0_(int *n
      , double *fluidState1Index, double *f3, double *pistonArea
      , double *pistonForce, double rp[3], int ic[2], void *ps[2])

{
   double f2;
   int loop;
/* >>>>>>>>>>>>Extra Macro Function macro0 Declarations Here. */
/* <<<<<<<<<<<<End of Extra Macro macro0 declarations. */
   double dp, dr, x0;

   dp         = rp[0];
   dr         = rp[1];
   x0         = rp[2];
   loop = 0;

/* Common -> SI units conversions. */

/*   *fluidState1Index *= ??; CONVERSION UNKNOWN [smoTDS] */

/*
   Define and return the following macro variable:

   f2         = ??;

   Define the following shared macro variable(s):

   *pistonArea = ??;
   *pistonForce = ??;
*/


/* >>>>>>>>>>>>Macro Function macro0 Executable Statements. */
   SMOCOMPONENt_PRINT_MACRO
   if (firstc_()) {
	   MediumState* state1 = MediumState_get(*fluidState1Index);
	   PneumaticPiston_init(_component, state1);
   }

   *pistonArea = PneumaticPiston_getPistonArea(_component);
   *pistonForce = PneumaticPiston_getPressureForceOnPiston(_component);
   f2 = *f3 - *pistonForce;
/* <<<<<<<<<<<<End of Macro macro0 Executable Statements. */

/* SI -> Common units conversions. */

/*   *fluidState1Index /= ??; CONVERSION UNKNOWN [smoTDS] */
   *pistonArea /= 1.00000000000000e-06;


   return f2;
}

