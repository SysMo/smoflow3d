/* Submodel SMO_PNEUMATIC_FLAT_FLAPPER_NOZZLE_VALVE skeleton created by AME Submodel editing utility
   ?? ??? 18 16:32:44 2022 */



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

#define _SUBMODELNAME_ "SMO_PNEUMATIC_FLAT_FLAPPER_NOZZLE_VALVE"

/* >>>>>>>>>>>>Insert Private Code Here. */
#include "SmoFlowAme.h"
#include "pneumatic/PneumaticFlapperValve.h"

#define _component ps[0]

#define _fluidFlow1 ps[1]
#define _fluidFlow1Index ic[1]

#define _fluidFlow2 ps[2]
#define _fluidFlow2Index ic[2]
/* <<<<<<<<<<<<End of Private Code. */


/* There are 10 real parameters:

   di              internal diameter of the nozzle (hole)                    [mm -> m]
   dr              rod diameter (nozzle side)                                [mm -> m]
   df              diameter of the flapper                                   [mm -> m]
   xlift0          opening (underlap) corresponding to zero displacement     [mm -> m]
   xmin            opening for minimum area                                  [mm -> m]
   xmax            opening for maximum area                                  [mm -> m]
   xlim            transition opening for pressure force on the flapper seat [mm -> m]
   vol10            volume at port 1 corresponding to zero lift              [cm**3 -> m**3]
   vol20            volume at port 2 corresponding to zero lift              [cm**3 -> m**3]
   flowCoefficient flow coefficient                                          [null]
*/


/* There are 3 integer parameters:

   useFluidFlowActivationSignal use fluid flow activation signal                            
   forcemode                    pressure acting in the flapper seat area                    
   forcecontact                 pressure force contribution on the flapper seat at zero lift
*/

void smo_pneumatic_flat_flapper_nozzle_valvein_(int *n, double rp[10]
      , int ip[3], int ic[3], void *ps[3])

{
   int loop, error;
/* >>>>>>>>>>>>Extra Initialization Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Initialization declarations. */
   int useFluidFlowActivationSignal, forcemode, forcecontact;
   double di, dr, df, xlift0, xmin, xmax, xlim, vol10, vol20, 
      flowCoefficient;

   useFluidFlowActivationSignal = ip[0];
   forcemode  = ip[1];
   forcecontact = ip[2];

   di         = rp[0];
   dr         = rp[1];
   df         = rp[2];
   xlift0     = rp[3];
   xmin       = rp[4];
   xmax       = rp[5];
   xlim       = rp[6];
   vol10      = rp[7];
   vol20      = rp[8];
   flowCoefficient = rp[9];
   loop = 0;
   error = 0;

/*
   If necessary, check values of the following:

   rp[0..9]
*/


/* >>>>>>>>>>>>Initialization Function Check Statements. */
/* <<<<<<<<<<<<End of Initialization Check Statements. */

/*   Integer parameter checking:   */

   if (useFluidFlowActivationSignal < 1 || useFluidFlowActivationSignal > 2)
   {
      amefprintf(stderr, "\nuse fluid flow activation signal must be in range [1..2].\n");
      error = 2;
   }
   if (forcemode < 1 || forcemode > 2)
   {
      amefprintf(stderr, "\npressure acting in the flapper seat area must be in range [1..2].\n");
      error = 2;
   }
   if (forcecontact < 1 || forcecontact > 2)
   {
      amefprintf(stderr, "\npressure force contribution on the flapper seat at zero lift must be in range [1..2].\n");
      error = 2;
   }

   if (ameHandleSubmodelError(_SUBMODELNAME_, *n, error))
   {
      return;
   }

/* Common -> SI units conversions. */

   rp[0]    *= 1.00000000000000e-03;
   di         = rp[0];
   rp[1]    *= 1.00000000000000e-03;
   dr         = rp[1];
   rp[2]    *= 1.00000000000000e-03;
   df         = rp[2];
   rp[3]    *= 1.00000000000000e-03;
   xlift0     = rp[3];
   rp[4]    *= 1.00000000000000e-03;
   xmin       = rp[4];
   rp[5]    *= 1.00000000000000e-03;
   xmax       = rp[5];
   rp[6]    *= 1.00000000000000e-03;
   xlim       = rp[6];
   rp[7]    *= 1.00000000000000e-06;
   vol10      = rp[7];
   rp[8]    *= 1.00000000000000e-06;
   vol20      = rp[8];


/* >>>>>>>>>>>>Initialization Function Executable Statements. */
	_component = PneumaticFlatFlapperNozzleValve_new(
		di, //diameterNozzle
		dr, //diameterRod
		df, //diameterFlapper
		xlift0, //flapperLift0
		xmin, //x for opening minimum area
		xmax, //x for opening maximum area
		forcemode, //pressure acting in the flapper seat area {1-constant, 2-gradient}
		forcecontact, //pressure force contribution on the flapper seat at zero lift {1-Yes, 2-No}
		xlim, //transition opening for pressure force on the flapper seat
		vol10, //volume at port 1 corresponding to zero lift
		vol20, //volume at port 2 corresponding to zero lift
		flowCoefficient);
	SMOCOMPONENT_SET_PROPS(_component)

    Valve_setPressureDifferenceParameters(_component,
		   0, 0, 0); //:TRICKY: useOpeningClosingPressDiff = 0 - no

	Valve_setRegulatingSignal(_component, 1); //regulatingSignal = 1

	_fluidFlow1 = FluidFlow_new();
	_fluidFlow1Index = FluidFlow_register(_fluidFlow1);
	_fluidFlow2 = FluidFlow_new();
	_fluidFlow2Index = FluidFlow_register(_fluidFlow2);
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

/*  There are 4 ports.

   Port 1 has 3 variables:

      1 fluidFlow1Index               fluid flow1 index                                                      [smoFFL]  multi line macro 'smo_pneumatic_flat_flapper_nozzle_valve_macro0_'  UNPLOTTABLE
      2 fluidFlowActivationSignal     flow activation signal = {-1 - not used; 0 - deactivate; 1 - activate} [smoFFAS] multi line macro shared with 'fluidFlow1Index'
      3 fluidState1Index              fluid state1 index                                                     [smoTDS]  basic variable input  UNPLOTTABLE

   Port 2 has 3 variables:

      1 fluidFlow2Index                  fluid flow2 index                                                      [smoFFL] multi line macro shared with 'fluidFlow1Index'  UNPLOTTABLE
      2 fluidFlowActivationSignalDup     duplicate of fluidFlowActivationSignal                                
      3 fluidState2Index                 fluid state2 index                                                     [smoTDS] basic variable input  UNPLOTTABLE

   Port 3 has 3 variables:

      1 v3     duplicate of v4       
      2 x3     duplicate of x4       
      3 f3     force at port3         [N] basic variable input

   Port 4 has 3 variables:

      1 f4     force at port4         [N]   multi line macro 'smo_pneumatic_flat_flapper_nozzle_valve_macro1_'
      2 v4     velocity at port4      [m/s] basic variable input
      3 x4     displacement at port 4 [m]   basic variable input
*/

/*  There are 11 internal variables.

      1 massFlowRate         mass flow rate (port1 -> port2)       [kg/s]            basic variable
      2 enthalpyFlowRate     enthalpy flow rate (port1 -> port2)   [W]               basic variable
      3 pressureLoss         total pressure loss                   [barA -> PaA]     basic variable
      4 flowType             flow type = {0 - subsonic, 1 - sonic} [null]            basic variable
      5 flapperLift          flapper lift                          [mm -> m]         basic variable
      6 flowArea             flow area                             [mm**2 -> m**2]   basic variable
      7 throatArea           throat area                           [mm**2 -> m**2]   basic variable
      8 volume1              volume at port-1                      [L -> m**3]       basic variable
      9 volumeDot1           derivative of volume at port-1        [L/min -> m**3/s] basic variable
     10 volume2              volume at port-2                      [L -> m**3]       basic variable
     11 volumeDot2           derivative of volume at port-2        [L/min -> m**3/s] basic variable
*/

void smo_pneumatic_flat_flapper_nozzle_valve_(int *n
      , double *fluidFlow1Index, double *fluidFlowActivationSignal
      , double *fluidState1Index, double *fluidFlow2Index
      , double *fluidState2Index, double *f3, double *f4, double *v4
      , double *x4, double *massFlowRate, double *enthalpyFlowRate
      , double *pressureLoss, double *flowType, double *flapperLift
      , double *flowArea, double *throatArea, double *volume1
      , double *volumeDot1, double *volume2, double *volumeDot2
      , double rp[10], int ip[3], int ic[3], void *ps[3])

{
   int loop;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   int useFluidFlowActivationSignal, forcemode, forcecontact;
   double di, dr, df, xlift0, xmin, xmax, xlim, vol10, vol20, 
      flowCoefficient;

   useFluidFlowActivationSignal = ip[0];
   forcemode  = ip[1];
   forcecontact = ip[2];

   di         = rp[0];
   dr         = rp[1];
   df         = rp[2];
   xlift0     = rp[3];
   xmin       = rp[4];
   xmax       = rp[5];
   xlim       = rp[6];
   vol10      = rp[7];
   vol20      = rp[8];
   flowCoefficient = rp[9];
   loop = 0;

/* Common -> SI units conversions. */

/*   *fluidFlow1Index *= ??; CONVERSION UNKNOWN [smoFFL] */
/*   *fluidFlowActivationSignal *= ??; CONVERSION UNKNOWN [smoFFAS] */
/*   *fluidState1Index *= ??; CONVERSION UNKNOWN [smoTDS] */
/*   *fluidFlow2Index *= ??; CONVERSION UNKNOWN [smoFFL] */
/*   *fluidState2Index *= ??; CONVERSION UNKNOWN [smoTDS] */

/*
   Set all submodel outputs below:

   *massFlowRate = ??;
   *enthalpyFlowRate = ??;
   *pressureLoss = ??;
   *flowType   = ??;
   *flapperLift = ??;
   *flowArea   = ??;
   *throatArea = ??;
   *volume1    = ??;
   *volumeDot1 = ??;
   *volume2    = ??;
   *volumeDot2 = ??;
*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
	*massFlowRate = FluidFlow_getMassFlowRate(_fluidFlow2);
	*enthalpyFlowRate = FluidFlow_getEnthalpyFlowRate(_fluidFlow2);
	*pressureLoss = Valve_getAbsolutePressureDrop(_component);
	*flowType = Valve_getFlowType(_component);
	*flapperLift = PneumaticFlapperValve_getFlapperLift(_component);
	*flowArea = PneumaticFlapperValve_getFlowArea(_component);
	*throatArea = PneumaticFlapperValve_getThroatArea(_component);

	*volume1 = FluidFlow_getVolume(_fluidFlow1);
	*volumeDot1 = FluidFlow_getVolumeDot(_fluidFlow1);

	*volume2 = FluidFlow_getVolume(_fluidFlow2);
	*volumeDot2 = FluidFlow_getVolumeDot(_fluidFlow2);
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *fluidFlow1Index /= ??; CONVERSION UNKNOWN [smoFFL] */
/*   *fluidFlowActivationSignal /= ??; CONVERSION UNKNOWN [smoFFAS] */
/*   *fluidState1Index /= ??; CONVERSION UNKNOWN [smoTDS] */
/*   *fluidFlow2Index /= ??; CONVERSION UNKNOWN [smoFFL] */
/*   *fluidState2Index /= ??; CONVERSION UNKNOWN [smoTDS] */
   *pressureLoss /= 1.00000000000000e+05;
   *flapperLift /= 1.00000000000000e-03;
   *flowArea /= 1.00000000000000e-06;
   *throatArea /= 1.00000000000000e-06;
   *volume1  /= 1.00000000000000e-03;
   *volumeDot1 /= 1.66666666666667e-05;
   *volume2  /= 1.00000000000000e-03;
   *volumeDot2 /= 1.66666666666667e-05;
}

extern double smo_pneumatic_flat_flapper_nozzle_valve_macro0_(int *n
      , double *fluidFlowActivationSignal, double *fluidState1Index
      , double *fluidFlow2Index, double *fluidState2Index, double *v4
      , double *x4, double rp[10], int ip[3], int ic[3], void *ps[3])

{
   double fluidFlow1Index;
   int loop;
/* >>>>>>>>>>>>Extra Macro Function macro0 Declarations Here. */
/* <<<<<<<<<<<<End of Extra Macro macro0 declarations. */
   int useFluidFlowActivationSignal, forcemode, forcecontact;
   double di, dr, df, xlift0, xmin, xmax, xlim, vol10, vol20, 
      flowCoefficient;

   useFluidFlowActivationSignal = ip[0];
   forcemode  = ip[1];
   forcecontact = ip[2];

   di         = rp[0];
   dr         = rp[1];
   df         = rp[2];
   xlift0     = rp[3];
   xmin       = rp[4];
   xmax       = rp[5];
   xlim       = rp[6];
   vol10      = rp[7];
   vol20      = rp[8];
   flowCoefficient = rp[9];
   loop = 0;

/* Common -> SI units conversions. */

/*   *fluidState1Index *= ??; CONVERSION UNKNOWN [smoTDS] */
/*   *fluidState2Index *= ??; CONVERSION UNKNOWN [smoTDS] */

/*
   Define and return the following macro variable:

   fluidFlow1Index = ??;

   Define the following shared macro variable(s):

   *fluidFlowActivationSignal = ??;
   *fluidFlow2Index = ??;
*/


/* >>>>>>>>>>>>Macro Function macro0 Executable Statements. */
    SMOCOMPONENt_PRINT_MACRO
	if (firstc_()) {
		MediumState* state1 = MediumState_get(*fluidState1Index);
		MediumState* state2 = MediumState_get(*fluidState2Index);
		Valve_init(_component, state1, state2);
	}

	PneumaticFlapperValve_setFlapperPosition(_component, *x4);
	Valve_compute(_component);
	Valve_updateFluidFlows(_component, _fluidFlow1, _fluidFlow2);
	PneumaticFlapperValve_updateVolumes(_component, *v4, *x4, _fluidFlow1, _fluidFlow2);

	fluidFlow1Index = _fluidFlow1Index;
	*fluidFlow2Index = _fluidFlow2Index;

	if (useFluidFlowActivationSignal == 1) { //no
		*fluidFlowActivationSignal = -1; //not used
	} else { // yes
		if (Valve_getIsFlowClosed(_component) == 1) {
		   *fluidFlowActivationSignal = 0; //deactivate flow
		} else {
		   *fluidFlowActivationSignal = 1; //activate flow
		}
	}
/* <<<<<<<<<<<<End of Macro macro0 Executable Statements. */

/* SI -> Common units conversions. */

/*   *fluidFlowActivationSignal /= ??; CONVERSION UNKNOWN [smoFFAS] */
/*   *fluidState1Index /= ??; CONVERSION UNKNOWN [smoTDS] */
/*   *fluidFlow2Index /= ??; CONVERSION UNKNOWN [smoFFL] */
/*   *fluidState2Index /= ??; CONVERSION UNKNOWN [smoTDS] */

/*   *fluidFlow1Index /= ??; CONVERSION UNKNOWN [smoFFL] */

   return fluidFlow1Index;
}

extern double smo_pneumatic_flat_flapper_nozzle_valve_macro1_(int *n
      , double *fluidState1Index, double *fluidState2Index, double *f3
      , double rp[10], int ip[3], int ic[3], void *ps[3])

{
   double f4;
   int loop;
/* >>>>>>>>>>>>Extra Macro Function macro1 Declarations Here. */
/* <<<<<<<<<<<<End of Extra Macro macro1 declarations. */
   int useFluidFlowActivationSignal, forcemode, forcecontact;
   double di, dr, df, xlift0, xmin, xmax, xlim, vol10, vol20, 
      flowCoefficient;

   useFluidFlowActivationSignal = ip[0];
   forcemode  = ip[1];
   forcecontact = ip[2];

   di         = rp[0];
   dr         = rp[1];
   df         = rp[2];
   xlift0     = rp[3];
   xmin       = rp[4];
   xmax       = rp[5];
   xlim       = rp[6];
   vol10      = rp[7];
   vol20      = rp[8];
   flowCoefficient = rp[9];
   loop = 0;

/* Common -> SI units conversions. */

/*   *fluidState1Index *= ??; CONVERSION UNKNOWN [smoTDS] */
/*   *fluidState2Index *= ??; CONVERSION UNKNOWN [smoTDS] */

/*
   Define and return the following macro variable:

   f4         = ??;
*/


/* >>>>>>>>>>>>Macro Function macro1 Executable Statements. */
    SMOCOMPONENt_PRINT_MACRO
   	if (firstc_()) {
   		MediumState* state1 = MediumState_get(*fluidState1Index);
   		MediumState* state2 = MediumState_get(*fluidState2Index);
   		Valve_init(_component, state1, state2);
   	}

    f4 = *f3 + PneumaticFlapperValve_getPressureForceOnFlapper(_component);
/* <<<<<<<<<<<<End of Macro macro1 Executable Statements. */

/* SI -> Common units conversions. */

/*   *fluidState1Index /= ??; CONVERSION UNKNOWN [smoTDS] */
/*   *fluidState2Index /= ??; CONVERSION UNKNOWN [smoTDS] */


   return f4;
}

