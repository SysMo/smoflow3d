/* Submodel SMO_VALVE_2PORT_MASS_FLOW skeleton created by AME Submodel editing utility
   Sun Nov 10 14:09:42 2013 */



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
#include "SmoFlowAme.h"
#include "flow/TwoPortValve.h"

#define _component ps[0]

#define _fluidFlow1 ps[1]
#define _fluidFlow1Index ic[1]

#define _fluidFlow2 ps[2]
#define _fluidFlow2Index ic[2]
/* <<<<<<<<<<<<End of Private Code. */

/* There is 1 integer parameter:

   allowBidirectionalFlow allow bi-directional flow
*/

void smo_valve_2port_mass_flowin_(int *n, int ip[1], int ic[3]
      , void *ps[3])

{
   int loop, error;
/* >>>>>>>>>>>>Extra Initialization Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Initialization declarations. */
   int allowBidirectionalFlow;

   allowBidirectionalFlow = ip[0];
   loop = 0;
   error = 0;


/* >>>>>>>>>>>>Initialization Function Check Statements. */
/* <<<<<<<<<<<<End of Initialization Check Statements. */

/*   Integer parameter checking:   */

   if (allowBidirectionalFlow < 1 || allowBidirectionalFlow > 2)
   {
      amefprintf(stderr, "\nallow bi-directional flow must be in range [1..2].\n");
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
   _component = TwoPortValve_InputMassFlowRate_new(allowBidirectionalFlow - 1); //:TRICKY: allowBidirectionalFlow = {1-no, 2-yes} - 1 = {0-no, 1-yes});
   SMOCOMPONENT_SET_PROPS(_component)

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

      1 regulatingSignal     regulating signal [kg/s] basic variable input

   Port 3 has 2 variables:

      1 fluidFlow2Index     fluid flow2 index  [smoFFL] basic variable output  UNPLOTTABLE
      2 state2Index         fluid state2 index [smoTDS] basic variable input  UNPLOTTABLE
*/

/*  There are 3 internal variables.

      1 massFlowRate         mass flow rate (at port3)     [kg/s]      basic variable
      2 enthalpyFlowRate     enthalpy flow rate (at port3) [W]         basic variable
      3 pressureLoss         total pressure loss           [bar -> Pa] basic variable
*/

void smo_valve_2port_mass_flow_(int *n, double *fluidFlow1Index
      , double *fluidState1Index, double *regulatingSignal
      , double *fluidFlow2Index, double *state2Index
      , double *massFlowRate, double *enthalpyFlowRate
      , double *pressureLoss, int ip[1], int ic[3], void *ps[3]
      , int *flag)

{
   int loop, logi;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   int allowBidirectionalFlow;

   allowBidirectionalFlow = ip[0];
   logi = 0;
   loop = 0;

/* Common -> SI units conversions. */

/*   *fluidState1Index *= ??; CONVERSION UNKNOWN */
/*   *state2Index *= ??; CONVERSION UNKNOWN */

/*
   Set all submodel outputs below:

   *fluidFlow1Index = ??;
   *fluidFlow2Index = ??;
   *massFlowRate = ??;
   *enthalpyFlowRate = ??;
   *pressureLoss = ??;
*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
   SMOCOMPONENT_PRINT_MAIN_CALC
   if (firstc_()) {
	   MediumState* state1 = MediumState_get(*fluidState1Index);
	   MediumState* state2 = MediumState_get(*state2Index);
	   TwoPortValve_init(_component, state1, state2);
   }

   TwoPortValve_setRegulatingSignal(_component, *regulatingSignal);
   TwoPortValve_compute(_component);
   TwoPortValve_updateFluidFlows(_component, _fluidFlow1, _fluidFlow2);

   *massFlowRate = FluidFlow_getMassFlowRate(_fluidFlow2);
   *enthalpyFlowRate = FluidFlow_getEnthalpyFlowRate(_fluidFlow2);
   *pressureLoss = TwoPortValve_getAbsolutePressureDrop(_component);

   *fluidFlow1Index = _fluidFlow1Index;
   *fluidFlow2Index = _fluidFlow2Index;
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *fluidFlow1Index /= ??; CONVERSION UNKNOWN */
/*   *fluidState1Index /= ??; CONVERSION UNKNOWN */
/*   *fluidFlow2Index /= ??; CONVERSION UNKNOWN */
/*   *state2Index /= ??; CONVERSION UNKNOWN */
   *pressureLoss /= 1.00000000000000e+005;
}

