/* Submodel SMO_PHASE_SEPARATOR skeleton created by AME Submodel editing utility
   Wed Aug 28 18:02:52 2013 */



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

#define _SUBMODELNAME_ "SMO_PHASE_SEPARATOR"

/* >>>>>>>>>>>>Insert Private Code Here. */
#include "SmoFlowAme.h"
#include "flow/PhaseSeparator.h"

#define _component ps[0]
#define _port2FluidStateIndex ic[0]
/* <<<<<<<<<<<<End of Private Code. */

/* There is 1 integer parameter:

   phaseSelectionMethod phase selection method
*/

void smo_phase_separatorin_(int *n, int ip[1], int ic[5], void *ps[5])

{
   int loop, error;
/* >>>>>>>>>>>>Extra Initialization Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Initialization declarations. */
   int phaseSelectionMethod;

   phaseSelectionMethod = ip[0];
   loop = 0;
   error = 0;


/* >>>>>>>>>>>>Initialization Function Check Statements. */
/* <<<<<<<<<<<<End of Initialization Check Statements. */

/*   Integer parameter checking:   */

   if (phaseSelectionMethod < 1 || phaseSelectionMethod > 5)
   {
      amefprintf(stderr, "\nphase selection method must be in range [1..5].\n");
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
   PhaseSelection phaseSelection;
   if (phaseSelectionMethod == 1) {
	   phaseSelection = PhaseSelection_Overall;
   } else if (phaseSelectionMethod == 2) {
	   phaseSelection = PhaseSelection_Liquid;
   } else if (phaseSelectionMethod == 3) {
	   phaseSelection = PhaseSelection_Gas;
   } else if (phaseSelectionMethod == 4) {
	   phaseSelection = PhaseSelection_varDiscrete;
   } else {
	   phaseSelection = PhaseSelection_varContinuous;
   }

   _component = PhaseSeparator_new(phaseSelection);
   SMOCOMPONEN_SET_PROPS(_component)
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

/*  There are 3 ports.

   Port 1 has 2 variables:

      1 port1FlowIndex      duplicate of port2FlowIndex
      2 port1StateIndex     state index at port 1 [smoTDS] basic variable input  UNPLOTTABLE

   Port 2 has 2 variables:

      1 port2StateIndex     state index at port 2 [smoTDS] multi line macro 'smo_phase_separator_macro0_'  UNPLOTTABLE
      2 port2FlowIndex      flow index at port 2  [smoFFL] basic variable input  UNPLOTTABLE

   Port 3 has 1 variable:

      1 regSignal     regulating signal [null] basic variable input  UNPLOTTABLE
*/

/*  There are 0 internal variables.

*/

#if 0

/* THE CALCULATION FUNCTION WILL NOT BE CALLED. */

void smo_phase_separator_(int *n, double *port1StateIndex
      , double *port2StateIndex, double *port2FlowIndex
      , double *regSignal, int ip[1], int ic[5], void *ps[5])

{
   int loop;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   int phaseSelectionMethod;

   phaseSelectionMethod = ip[0];
   loop = 0;

/* Common -> SI units conversions. */

/*   *port1StateIndex *= ??; CONVERSION UNKNOWN */
/*   *port2StateIndex *= ??; CONVERSION UNKNOWN */
/*   *port2FlowIndex *= ??; CONVERSION UNKNOWN */

/*
   Set all submodel outputs below:

*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *port1StateIndex /= ??; CONVERSION UNKNOWN */
/*   *port2StateIndex /= ??; CONVERSION UNKNOWN */
/*   *port2FlowIndex /= ??; CONVERSION UNKNOWN */
}

#endif
extern double smo_phase_separator_macro0_(int *n
      , double *port1StateIndex, double *regSignal, int ip[1]
      , int ic[5], void *ps[5])

{
   double port2StateIndex;
   int loop;
/* >>>>>>>>>>>>Extra Macro Function macro0 Declarations Here. */
/* <<<<<<<<<<<<End of Extra Macro macro0 declarations. */
   int phaseSelectionMethod;

   phaseSelectionMethod = ip[0];
   loop = 0;

/* Common -> SI units conversions. */

/*   *port1StateIndex *= ??; CONVERSION UNKNOWN */

/*
   Define and return the following macro variable:

   port2StateIndex = ??;
*/


/* >>>>>>>>>>>>Macro Function macro0 Executable Statements. */
   if (firstc_()) {
	   MediumState* port1State = MediumState_get(*port1StateIndex);
	   PhaseSeparator_init(_component, port1State);
	   MediumState* port2State = PhaseSeparator_getPort2State(_component);
	   _port2FluidStateIndex = SmoObject_getInstanceIndex((SmoObj*)port2State);
   }

   PhaseSeparator_updateState(_component, *regSignal);
   port2StateIndex = _port2FluidStateIndex;
/* <<<<<<<<<<<<End of Macro macro0 Executable Statements. */

/* SI -> Common units conversions. */

/*   *port1StateIndex /= ??; CONVERSION UNKNOWN */

/*   *port2StateIndex /= ??; CONVERSION UNKNOWN */

   return port2StateIndex;
}

