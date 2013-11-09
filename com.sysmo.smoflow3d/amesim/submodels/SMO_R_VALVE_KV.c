/* Submodel SMO_R_VALVE_KV skeleton created by AME Submodel editing utility
   Sat Nov 9 14:28:37 2013 */



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

#define _SUBMODELNAME_ "SMO_R_VALVE_KV"

/* >>>>>>>>>>>>Insert Private Code Here. */
#include "SmoFlowAme.h"
#include "flow_R/Valve_R.h"
#include "flow_R/ManagerComponents_R.h"

#define _component ps[0]

#define _fluidFlow1Index ic[1]
#define _fluidFlow2Index ic[2]
/* <<<<<<<<<<<<End of Private Code. */


/* There are 3 real parameters:

   Kv                           flow coefficient Kv            [null]
   transitionMassFlowRate       transition mass flow rate      [kg/s]
   transitionPressureDifference transition pressure difference [bar -> Pa]
*/


/* There are 2 integer parameters:

   transitionChoice       choice of transition to linear region
   allowBidirectionalFlow allow bi-directional flow            
*/

void smo_r_valve_kvin_(int *n, double rp[3], int ip[2], int ic[2]
      , void *ps[1])

{
   int loop, error;
/* >>>>>>>>>>>>Extra Initialization Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Initialization declarations. */
   int transitionChoice, allowBidirectionalFlow;
   double Kv, transitionMassFlowRate, transitionPressureDifference;

   transitionChoice = ip[0];
   allowBidirectionalFlow = ip[1];

   Kv         = rp[0];
   transitionMassFlowRate = rp[1];
   transitionPressureDifference = rp[2];
   loop = 0;
   error = 0;

/*
   If necessary, check values of the following:

   rp[0..2]
*/


/* >>>>>>>>>>>>Initialization Function Check Statements. */
/* <<<<<<<<<<<<End of Initialization Check Statements. */

/*   Integer parameter checking:   */

   if (transitionChoice < 1 || transitionChoice > 2)
   {
      amefprintf(stderr, "\nchoice of transition to linear region must be in range [1..2].\n");
      error = 2;
   }
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

/* Common -> SI units conversions. */

   rp[2]    *= 1.00000000000000e+005;
   transitionPressureDifference = rp[2];


/* >>>>>>>>>>>>Initialization Function Executable Statements. */
   _component = ValveKv_R_new(
		   allowBidirectionalFlow - 1, //:TRICKY: allowBidirectionalFlow =  '{1-no, 2-yes} - 1'  =  '{0-no, 1-yes}'
		   Kv,
		   transitionChoice,
		   transitionMassFlowRate,
		   transitionPressureDifference);
   SMOCOMPONENT_SET_PROPS(_component)

   _fluidFlow1Index = Component_R_getFlow1Index(_component);
   _fluidFlow2Index = Component_R_getFlow2Index(_component);
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

/*  There are 3 ports.

   Port 1 has 2 variables:

      1 fluidFlow1Index      fluid flow1 index  [smoFFL] basic variable output  UNPLOTTABLE
      2 fluidState1Index     fluid state1 index [smoTDS] basic variable input  UNPLOTTABLE

   Port 2 has 1 variable:

      1 regulatingSignal     regulating signal [null] basic variable input

   Port 3 has 2 variables:

      1 fluidFlow2Index      fluid flow2 index  [smoFFL] multi line macro 'smo_r_valve_kv_macro0_'  UNPLOTTABLE
      2 fluidState2Index     fluid state2 index [smoTDS] basic variable input  UNPLOTTABLE
*/

/*  There are 0 internal variables.

*/

void smo_r_valve_kv_(int *n, double *fluidFlow1Index
      , double *fluidState1Index, double *regulatingSignal
      , double *fluidFlow2Index, double *fluidState2Index
      , double rp[3], int ip[2], int ic[2], void *ps[1], int *flag)

{
   int loop, logi;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   int transitionChoice, allowBidirectionalFlow;
   double Kv, transitionMassFlowRate, transitionPressureDifference;

   transitionChoice = ip[0];
   allowBidirectionalFlow = ip[1];

   Kv         = rp[0];
   transitionMassFlowRate = rp[1];
   transitionPressureDifference = rp[2];
   logi = 0;
   loop = 0;

/* Common -> SI units conversions. */

/*   *fluidState1Index *= ??; CONVERSION UNKNOWN */
/*   *fluidFlow2Index *= ??; CONVERSION UNKNOWN */
/*   *fluidState2Index *= ??; CONVERSION UNKNOWN */

/*
   Set all submodel outputs below:

   *fluidFlow1Index = ??;
*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
   // Initialization at first run
   SMOCOMPONENT_PRINT_MAIN_CALC

   *fluidFlow1Index = _fluidFlow1Index;
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *fluidFlow1Index /= ??; CONVERSION UNKNOWN */
/*   *fluidState1Index /= ??; CONVERSION UNKNOWN */
/*   *fluidFlow2Index /= ??; CONVERSION UNKNOWN */
/*   *fluidState2Index /= ??; CONVERSION UNKNOWN */
}

extern double smo_r_valve_kv_macro0_(int *n, double *fluidState1Index
      , double *regulatingSignal, double rp[3], int ip[2], int ic[2]
      , void *ps[1], int *flag)

{
   double fluidFlow2Index;
   int loop, logi;
/* >>>>>>>>>>>>Extra Macro Function macro0 Declarations Here. */
/* <<<<<<<<<<<<End of Extra Macro macro0 declarations. */
   int transitionChoice, allowBidirectionalFlow;
   double Kv, transitionMassFlowRate, transitionPressureDifference;

   transitionChoice = ip[0];
   allowBidirectionalFlow = ip[1];

   Kv         = rp[0];
   transitionMassFlowRate = rp[1];
   transitionPressureDifference = rp[2];
   logi = 0;
   loop = 0;

/* Common -> SI units conversions. */

/*   *fluidState1Index *= ??; CONVERSION UNKNOWN */

/*
   Define and return the following macro variable:

   fluidFlow2Index = ??;
*/


/* >>>>>>>>>>>>Macro Function macro0 Executable Statements. */
   SMOCOMPONENt_PRINT_MACRO_MSG("flow2")
   if (firstc_()) {
	   ManagerComponents_R_addComponent(_component, *fluidState1Index);
   }
   Valve_R_setRegulatingSignal(_component, *regulatingSignal);

   fluidFlow2Index = _fluidFlow2Index;
/* <<<<<<<<<<<<End of Macro macro0 Executable Statements. */

/* SI -> Common units conversions. */

/*   *fluidState1Index /= ??; CONVERSION UNKNOWN */

/*   *fluidFlow2Index /= ??; CONVERSION UNKNOWN */

   return fluidFlow2Index;
}

