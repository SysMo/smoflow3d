/* Submodel SMO_VALVE_2PORT_MASS_FLOW skeleton created by AME Submodel editing utility
   Fri Jul 26 15:24:05 2013 */



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
#include "FluidPoint.h"
#define NODE1 ps[0]
#define NODE2 ps[1]
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
	AME_SET_CURRENT_COMPONENT;

	NODE1 = FluidPoint_new(fluidIndex);
	NODE2 = FluidPoint_new(fluidIndex);
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

/*  There are 2 internal variables.

      1 pressureLoss         total pressure loss      [barA -> PaA] basic variable
      2 port1Temperature     fluid temperature port 1 [K]           basic variable
*/

void smo_valve_2port_mass_flow_(int *n, double *flowIndex1
      , double *stateIndex1, double *regulatingSignal
      , double *flowIndex3, double *stateIndex3, double *pressureLoss
      , double *port1Temperature, int ic[5], void *ps[5], int *flag)

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
   *pressureLoss = ??;
   *port1Temperature = ??;
*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
   // Initialization at first run
   if (firstc_()) {
	   FluidPoint_init(NODE1, (int)(*port1ComIndex), -1);
	   FluidPoint_init(NODE2, (int)(*port3ComIndex), -1);
   }
   // Setting object inputs
   FluidPoint_computeState_p_rho(NODE1, *port1Pressure, *port1Density);
   FluidPoint_computeState_p_rho(NODE2, *port3Pressure, *port3Density);

   *port3MassFlowRate = *regulatingSignal;
   double upstreamSpecificEnthalpy;
   if (*regulatingSignal > 0) {
	   upstreamSpecificEnthalpy = ((FluidPoint*)NODE1)->h;
   } else {
	   upstreamSpecificEnthalpy = ((FluidPoint*)NODE2)->h;
   }
   *port3EnthalpyFlowRate = *port3MassFlowRate * upstreamSpecificEnthalpy;
   *pressureLoss = fabs(*port1Pressure - *port3Pressure);
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *flowIndex1 /= ??; CONVERSION UNKNOWN */
/*   *stateIndex1 /= ??; CONVERSION UNKNOWN */
/*   *flowIndex3 /= ??; CONVERSION UNKNOWN */
/*   *stateIndex3 /= ??; CONVERSION UNKNOWN */
   *pressureLoss /= 1.00000000000000e+005;
}

