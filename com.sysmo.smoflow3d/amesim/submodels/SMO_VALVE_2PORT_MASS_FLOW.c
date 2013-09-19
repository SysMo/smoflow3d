/* Submodel SMO_VALVE_2PORT_MASS_FLOW skeleton created by AME Submodel editing utility
   Thu Sep 19 13:10:16 2013 */



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

#define _flow1 ps[1]
#define _flow1Index ic[1]

#define _flow2 ps[2]
#define _flow2Index ic[2]
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
   _component = TwoPortValve_InputMassFlowRate_new(
		   allowBidirectionalFlow - 1); //:TRICKY: allowBidirectionalFlow = {1-no, 2-yes} - 1 = {0-no, 1-yes});
   SMOCOMPONEN_SET_PROPS(_component)

   _flow1 = FluidFlow_new();
   _flow1Index = FluidFlow_register(_flow1);
   _flow2 = FluidFlow_new();
   _flow2Index = FluidFlow_register(_flow2);
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

/*  There are 3 ports.

   Port 1 has 2 variables:

      1 flow1Index      flow1 index  [smoFFL] basic variable output  UNPLOTTABLE
      2 state1Index     state1 index [smoTDS] basic variable input  UNPLOTTABLE

   Port 2 has 1 variable:

      1 regulatingSignal     regulating signal [kg/s] basic variable input

   Port 3 has 2 variables:

      1 flow2Index      flow2 index  [smoFFL] basic variable output  UNPLOTTABLE
      2 state2Index     state2 index [smoTDS] basic variable input  UNPLOTTABLE
*/

/*  There are 3 internal variables.

      1 massFlowRate         mass flow rate (at port3)     [kg/s]        basic variable
      2 enthalpyFlowRate     enthalpy flow rate (at port3) [W]           basic variable
      3 pressureLoss         total pressure loss           [barA -> PaA] basic variable
*/

void smo_valve_2port_mass_flow_(int *n, double *flow1Index
      , double *state1Index, double *regulatingSignal
      , double *flow2Index, double *state2Index, double *massFlowRate
      , double *enthalpyFlowRate, double *pressureLoss, int ip[1]
      , int ic[3], void *ps[3], int *flag)

{
   int loop, logi;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   int allowBidirectionalFlow;

   allowBidirectionalFlow = ip[0];
   logi = 0;
   loop = 0;

/* Common -> SI units conversions. */

/*   *state1Index *= ??; CONVERSION UNKNOWN */
/*   *state2Index *= ??; CONVERSION UNKNOWN */

/*
   Set all submodel outputs below:

   *flow1Index = ??;
   *flow2Index = ??;
   *massFlowRate = ??;
   *enthalpyFlowRate = ??;
   *pressureLoss = ??;
*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
   // Initialization at first run
     if (firstc_()) {
  	   MediumState* state1 = MediumState_get(*state1Index);
  	   MediumState* state2 = MediumState_get(*state2Index);
  	   TwoPortValve_init(_component, state1, state2);
     }

     TwoPortValve_setRegulatingSignal(_component, *regulatingSignal);
     TwoPortValve_compute(_component);
     TwoPortValve_getFlowRates(_component, _flow1, _flow2);

     *massFlowRate = TwoPortValve_getMassFlowRate(_component);
     *enthalpyFlowRate = TwoPortValve_getEnthalpyFlowRate(_component);
     *pressureLoss = TwoPortValve_getPressureLoss(_component);

     *flow1Index = _flow1Index;
     *flow2Index = _flow2Index;
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *flow1Index /= ??; CONVERSION UNKNOWN */
/*   *state1Index /= ??; CONVERSION UNKNOWN */
/*   *flow2Index /= ??; CONVERSION UNKNOWN */
/*   *state2Index /= ??; CONVERSION UNKNOWN */
   *pressureLoss /= 1.00000000000000e+005;
}

