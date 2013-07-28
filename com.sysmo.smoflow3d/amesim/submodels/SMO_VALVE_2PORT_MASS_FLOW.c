/* Submodel SMO_VALVE_2PORT_MASS_FLOW skeleton created by AME Submodel editing utility
   Sun Jul 28 17:41:44 2013 */



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

#define _SUBMODELNAME_ "SMO_VALVE_2PORT_MASS_FLOW"

/* >>>>>>>>>>>>Insert Private Code Here. */
#include "media/FluidFlow.h"
#include "media/MediumState.h"

#define fluidFlowIndex1 ic[1]
#define fluidFlow1 ps[1]

#define fluidFlowIndex3 ic[2]
#define fluidFlow3 ps[2]

#define fluidStateIndex1 ic[3]
#define fluidState1 ps[3]

#define fluidStateIndex3 ic[4]
#define fluidState3 ps[4]
/* <<<<<<<<<<<<End of Private Code. */
void smo_valve_2port_mass_flowin_(int *n, int ic[5], void *ps[5])

{
   int loop, error;
/* >>>>>>>>>>>>Extra Initialization Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Initialization declarations. */
   loop = 0;
   error = 0;


/* >>>>>>>>>>>>Initialization Function Check Statements. */
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


/* >>>>>>>>>>>>Initialization Function Executable Statements. */
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

/*  There are 3 ports.

   Port 1 has 2 variables:

      1 flowIndex1      flow index 1  [smoFFL] basic variable output  UNPLOTTABLE
      2 stateIndex1     state index 1 [smoTDS] basic variable input  UNPLOTTABLE

   Port 2 has 1 variable:

      1 regulatingSignal     regulating signal [kg/s] basic variable input

   Port 3 has 2 variables:

      1 flowIndex3      flow index 3 [smoFFL] basic variable output  UNPLOTTABLE
      2 stateIndex3     state index3 [smoTDS] basic variable input  UNPLOTTABLE
*/

/*  There are 3 internal variables.

      1 massFlowRate         mass flow rate      [kg/s]        basic variable
      2 enthalpyFlowRate     enthalpy flow rate  [W]           basic variable
      3 pressureLoss         total pressure loss [barA -> PaA] basic variable
*/

void smo_valve_2port_mass_flow_(int *n, double *flowIndex1
      , double *stateIndex1, double *regulatingSignal
      , double *flowIndex3, double *stateIndex3, double *massFlowRate
      , double *enthalpyFlowRate, double *pressureLoss, int ic[5]
      , void *ps[5], int *flag)

{
   int loop, logi;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
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
	   fluidFlow1 = FluidFlow_new();
	   fluidFlowIndex1 = FluidFlow_register(fluidFlow1);

	   fluidFlow3 = FluidFlow_new();
	   fluidFlowIndex3 = FluidFlow_register(fluidFlow3);

	   fluidStateIndex1 = *stateIndex1;
	   fluidState1 = MediumState_get(fluidStateIndex1);

	   fluidStateIndex3 = *stateIndex3;
	   fluidState3 = MediumState_get(fluidStateIndex3);

	   int mediumIndex1 = MediumState_getMediumIndex(fluidState1);
	   int mediumIndex3 = MediumState_getMediumIndex(fluidState3);
	   if (mediumIndex1 != mediumIndex3) {
		   amefprintf(stderr, "\nFatal error in %s instance %d.\n", _SUBMODELNAME_, *n);
		   amefprintf(stderr, "\nThe valve connects two components with different fluid indices: %d and %d.\n", mediumIndex1, mediumIndex3);
		   AmeExit(1);
	   }
   }

   FluidFlow* fluidFlowObj3 = (FluidFlow*) fluidFlow3;
   FluidFlow* fluidFlowObj1 = (FluidFlow*) fluidFlow1;

   fluidFlowObj3->massFlowRate = *regulatingSignal;
   double upstreamSpecificEnthalpy = 0.0;
   if (*regulatingSignal > 0) {
	   upstreamSpecificEnthalpy = MediumState_h(fluidState1);
   } else {
	   upstreamSpecificEnthalpy = MediumState_h(fluidState3);
   }
   fluidFlowObj3->enthalpyFlowRate = fluidFlowObj3->massFlowRate * upstreamSpecificEnthalpy;


   fluidFlowObj1->massFlowRate = -fluidFlowObj3->massFlowRate;
   fluidFlowObj1->enthalpyFlowRate = -fluidFlowObj3->enthalpyFlowRate;

   *massFlowRate = fabs(fluidFlowObj3->massFlowRate);
   *enthalpyFlowRate = fabs(fluidFlowObj3->enthalpyFlowRate);
   *pressureLoss = fabs(MediumState_p(fluidState1) - MediumState_p(fluidState3));

   *flowIndex1 = fluidFlowIndex1;
   *flowIndex3 = fluidFlowIndex3;
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *flowIndex1 /= ??; CONVERSION UNKNOWN */
/*   *stateIndex1 /= ??; CONVERSION UNKNOWN */
/*   *flowIndex3 /= ??; CONVERSION UNKNOWN */
/*   *stateIndex3 /= ??; CONVERSION UNKNOWN */
   *pressureLoss /= 1.00000000000000e+005;
}

