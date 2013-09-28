/* Submodel SMO_ORIFICE_COMPRESSIBLE_IDEAL_GAS skeleton created by AME Submodel editing utility
   Thu Sep 19 17:15:34 2013 */



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

#define _SUBMODELNAME_ "SMO_ORIFICE_COMPRESSIBLE_IDEAL_GAS"

/* >>>>>>>>>>>>Insert Private Code Here. */
#include "SmoFlowAme.h"
#include "flow/Orifice.h"

#define _component ps[0]

#define _fluidFlow1 ps[1]
#define _fluidFlow1Index ic[1]

#define _fluidFlow2 ps[2]
#define _fluidFlow2Index ic[2]
/* <<<<<<<<<<<<End of Private Code. */


/* There are 2 real parameters:

   orificeArea      orifice area    [mm**2 -> m**2]
   flowCoefficient flow coefficient [null]
*/

void smo_orifice_compressible_ideal_gasin_(int *n, double rp[2]
      , int ic[3], void *ps[3])

{
   int loop, error;
/* >>>>>>>>>>>>Extra Initialization Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Initialization declarations. */
   double orificeArea, flowCoefficient;

   orificeArea = rp[0];
   flowCoefficient = rp[1];
   loop = 0;
   error = 0;

/*
   If necessary, check values of the following:

   rp[0..1]
*/


/* >>>>>>>>>>>>Initialization Function Check Statements. */
   if (flowCoefficient < 0.0 || flowCoefficient > 1.0)
   {
	   amefprintf(stderr, "\nflow coefficient = %f, but must be in range [0.0 .. 1.0].\n", flowCoefficient);
	   error = 2;
   }
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

/* Common -> SI units conversions. */

   rp[0]    *= 1.00000000000000e-006;
   orificeArea = rp[0];


/* >>>>>>>>>>>>Initialization Function Executable Statements. */
   _component = Orifice_new();
   SMOCOMPONENT_SET_PROPS(_component)

   Orifice_setOrificeArea(_component, orificeArea);
   Orifice_setFlowCoefficient(_component, flowCoefficient);

   _fluidFlow1 = FluidFlow_new();
   _fluidFlow1Index = FluidFlow_register(_fluidFlow1);
   _fluidFlow2 = FluidFlow_new();
   _fluidFlow2Index = FluidFlow_register(_fluidFlow2);
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

/*  There are 3 ports.

   Port 1 has 2 variables:

      1 fluidFlow1Index      fluid flow1 index  [smoFFL] basic variable output  UNPLOTTABLE
      2 fluidState1Index     fluid state1 index [smoTDS] basic variable input  UNPLOTTABLE

   Port 2 has 1 variable:

      1 regulatingSignal     regulating signal [null] basic variable input

   Port 3 has 2 variables:

      1 fluidFlow2Index      fluid flow2 index  [smoFFL] basic variable output  UNPLOTTABLE
      2 fluidState2Index     fluid state2 index [smoTDS] basic variable input  UNPLOTTABLE
*/

/*  There are 4 internal variables.

      1 massFlowRate         mass flow rate                        [kg/s]        basic variable
      2 enthalpyFlowRate     enthalpy flow rate                    [W]           basic variable
      3 pressureLoss         total pressure loss                   [barA -> PaA] basic variable
      4 flowType             flow type = {0 - subsonic, 1 - sonic} [null]        basic variable
*/

void smo_orifice_compressible_ideal_gas_(int *n
      , double *fluidFlow1Index, double *fluidState1Index
      , double *regulatingSignal, double *fluidFlow2Index
      , double *fluidState2Index, double *massFlowRate
      , double *enthalpyFlowRate, double *pressureLoss
      , double *flowType, double rp[2], int ic[3], void *ps[3]
      , int *flag)

{
   int loop, logi;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   double orificeArea, flowCoefficient;

   orificeArea = rp[0];
   flowCoefficient = rp[1];
   logi = 0;
   loop = 0;

/* Common -> SI units conversions. */

/*   *fluidState1Index *= ??; CONVERSION UNKNOWN */
/*   *fluidState2Index *= ??; CONVERSION UNKNOWN */

/*
   Set all submodel outputs below:

   *fluidFlow1Index = ??;
   *fluidFlow2Index = ??;
   *massFlowRate = ??;
   *enthalpyFlowRate = ??;
   *pressureLoss = ??;
   *flowType   = ??;
*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
   // Initialization at first run
   if (firstc_()) {
	   MediumState* inletState = MediumState_get(*fluidState1Index);
	   MediumState* outletState = MediumState_get(*fluidState2Index);
	   Orifice_init(_component, inletState, outletState);
   }

   Orifice_setRegulatingSignal(_component, *regulatingSignal);
   Orifice_compute_CompressibleIdealGas(_component);
   Orifice_getFlowRates(_component, _fluidFlow1, _fluidFlow2);

   *massFlowRate = Orifice_getMassFlowRate(_component);
   *enthalpyFlowRate = Orifice_getEnthalpyFlowRate(_component);
   *pressureLoss = Orifice_getPressureLoss(_component);
   *flowType = Orifice_getFlowType(_component);

   *fluidFlow1Index = _fluidFlow1Index;
   *fluidFlow2Index = _fluidFlow2Index;
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *fluidFlow1Index /= ??; CONVERSION UNKNOWN */
/*   *fluidState1Index /= ??; CONVERSION UNKNOWN */
/*   *fluidFlow2Index /= ??; CONVERSION UNKNOWN */
/*   *fluidState2Index /= ??; CONVERSION UNKNOWN */
   *pressureLoss /= 1.00000000000000e+005;
}

