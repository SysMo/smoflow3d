/* Submodel SMO_ORIFICE_COMPRESSIBLE_IDEAL_GAS skeleton created by AME Submodel editing utility
   Sun Aug 4 15:25:47 2013 */



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
#include "media/MediumState.h"
#include "flow/FlowBase.h"
#include "flow/Orifice.h"

#define _orifice ps[0]

#define _fluidFlowIndex1 ic[1]
#define _fluidFlow1 ps[1]

#define _fluidFlowIndex3 ic[2]
#define _fluidFlow3 ps[2]

#define _fluidStateIndex1 ic[3]
#define _fluidState1 ps[3]

#define _fluidStateIndex3 ic[4]
#define _fluidState3 ps[4]
/* <<<<<<<<<<<<End of Private Code. */


/* There are 2 real parameters:

   orificeArea      orifice area    [mm**2 -> m**2]
   flowCoefficient flow coefficient [null]
*/

void smo_orifice_compressible_ideal_gasin_(int *n, double rp[2]
      , int ic[5], void *ps[5])

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
   _orifice = Orifice_new();
   Orifice* orificeObj = _orifice;
   orificeObj->orificeArea = orificeArea;
   orificeObj->flowCoefficient = flowCoefficient;
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

/*  There are 3 ports.

   Port 1 has 2 variables:

      1 flowIndex1      flow index 1  [smoFFL] basic variable output  UNPLOTTABLE
      2 stateIndex1     state index 1 [smoTDS] basic variable input  UNPLOTTABLE

   Port 2 has 1 variable:

      1 regulatingSignal     regulating signal [null] basic variable input

   Port 3 has 2 variables:

      1 flowIndex3      flow index 3 [smoFFL] basic variable output  UNPLOTTABLE
      2 stateIndex3     state index3 [smoTDS] basic variable input  UNPLOTTABLE
*/

/*  There are 3 internal variables.

      1 massFlowRate         mass flow rate      [kg/s]        basic variable
      2 enthalpyFlowRate     enthalpy flow rate  [W]           basic variable
      3 pressureLoss         total pressure loss [barA -> PaA] basic variable
*/

void smo_orifice_compressible_ideal_gas_(int *n, double *flowIndex1
      , double *stateIndex1, double *regulatingSignal
      , double *flowIndex3, double *stateIndex3, double *massFlowRate
      , double *enthalpyFlowRate, double *pressureLoss, double rp[2]
      , int ic[5], void *ps[5], int *flag)

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

/*   *stateIndex1 *= ??; CONVERSION UNKNOWN */
/*   *stateIndex3 *= ??; CONVERSION UNKNOWN */

/*
   Set all submodel outputs below:

   *flowIndex1 = ??;
   *flowIndex3 = ??;
   *massFlowRate = ??;
   *enthalpyFlowRate = ??;
   *pressureLoss = ??;
*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
   // Initialization at first run
   if (firstc_()) {
	   _fluidFlow1 = (void*) FluidFlow_new();
	   _fluidFlowIndex1 = FluidFlow_register(_fluidFlow1);

	   _fluidFlow3 = (void*) FluidFlow_new();
	   _fluidFlowIndex3 = FluidFlow_register(_fluidFlow3);

	   _fluidStateIndex1 = *stateIndex1;
	   _fluidState1 = MediumState_get(_fluidStateIndex1);

	   _fluidStateIndex3 = *stateIndex3;
	   _fluidState3 = MediumState_get(_fluidStateIndex3);

	   int mediumIndex1 = Medium_index(MediumState_getMedium(_fluidState1));
	   int mediumIndex3 = Medium_index(MediumState_getMedium(_fluidState3));
	   if (mediumIndex1 != mediumIndex3) {
		   amefprintf(stderr, "\nFatal error in %s instance %d.\n", _SUBMODELNAME_, *n);
		   amefprintf(stderr, "\nThe orifice connects two components with different fluid indices: %d and %d.\n", mediumIndex1, mediumIndex3);
		   AmeExit(1);
	   }

	   Orifice_init(_orifice, _fluidState1, _fluidState3);
   }

   Orifice_computeMassFlow_CompressibleIdealGas(_orifice, *regulatingSignal);
   Orifice_computeEnthalpyFlow(_orifice);

   // Retrieving the objects from the storage
   Orifice* orificeObj = (Orifice*) _orifice;

   FluidFlow_setMassFlowRate(_fluidFlow3, orificeObj->massFlowRate);
   FluidFlow_setEnthalpyFlowRate(_fluidFlow3, orificeObj->enthalpyFlowRate);

   FluidFlow_setMassFlowRate(_fluidFlow1, -orificeObj->massFlowRate);
   FluidFlow_setEnthalpyFlowRate(_fluidFlow1, -orificeObj->enthalpyFlowRate);

   *massFlowRate = fabs(orificeObj->massFlowRate);
   *enthalpyFlowRate = fabs(orificeObj->enthalpyFlowRate);
   *pressureLoss = fabs(MediumState_p(_fluidState1) - MediumState_p(_fluidState3));

   *flowIndex1 = _fluidFlowIndex1;
   *flowIndex3 = _fluidFlowIndex3;
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *flowIndex1 /= ??; CONVERSION UNKNOWN */
/*   *stateIndex1 /= ??; CONVERSION UNKNOWN */
/*   *flowIndex3 /= ??; CONVERSION UNKNOWN */
/*   *stateIndex3 /= ??; CONVERSION UNKNOWN */
   *pressureLoss /= 1.00000000000000e+005;
}

