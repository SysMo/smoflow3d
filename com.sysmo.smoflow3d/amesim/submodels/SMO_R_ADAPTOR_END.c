/* Submodel SMO_R_ADAPTOR_END skeleton created by AME Submodel editing utility
   Sun Nov 10 12:48:27 2013 */



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

#define _SUBMODELNAME_ "SMO_R_ADAPTOR_END"

/* >>>>>>>>>>>>Insert Private Code Here. */
#include "SmoFlowAme.h"
#include "flow_R/ManagerComponents_R.h"
#include "flow_R/Adaptor_R.h"

#define _component ps[0]

#define _stateMacroIsCalled ic[0]
#define _flowMacroIsCalled ic[1]
/* <<<<<<<<<<<<End of Private Code. */
void smo_r_adaptor_endin_(int *n, int ic[2], void *ps[1])

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
   _component = EndAdaptor_R_new();
   SMOCOMPONENT_SET_PROPS(_component);

   _stateMacroIsCalled = 0;
   _flowMacroIsCalled = 0;
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

/*  There are 3 ports.

   Port 1 has 3 variables:

      1 fluidState1Index     fluid state1 index            [smoTDS]      multi line macro 'smo_r_adaptor_end_macro0_'  UNPLOTTABLE
      2 fluidFlow1Index      fluid flow1 index             [smoFFL]      basic variable input  UNPLOTTABLE
      3 smoRChainIDPort1     R-components chain ID (port1) [smoRChainID] basic variable input

   Port 2 has 2 variables:

      1 fluidFlow2Index      fluid flow2 index  [smoFFL] multi line macro 'smo_r_adaptor_end_macro1_'  UNPLOTTABLE
      2 fluidState2Index     fluid state2 index [smoTDS] basic variable input  UNPLOTTABLE

   Port 3 has 1 variable:

      1 smoRChainIDFromBeginAdaptor     R-components chain ID (port3) [smoRChainID] basic variable input
*/

/*  There are 0 internal variables.

*/

void smo_r_adaptor_end_(int *n, double *fluidState1Index
      , double *fluidFlow1Index, double *smoRChainIDPort1
      , double *fluidFlow2Index, double *fluidState2Index
      , double *smoRChainIDFromBeginAdaptor, int ic[2], void *ps[1])

{
   int loop;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   loop = 0;

/* Common -> SI units conversions. */

/*   *fluidState1Index *= ??; CONVERSION UNKNOWN */
/*   *fluidFlow1Index *= ??; CONVERSION UNKNOWN */
/*   *smoRChainIDPort1 *= ??; CONVERSION UNKNOWN */
/*   *fluidFlow2Index *= ??; CONVERSION UNKNOWN */
/*   *fluidState2Index *= ??; CONVERSION UNKNOWN */
/*   *smoRChainIDFromBeginAdaptor *= ??; CONVERSION UNKNOWN */

/*
   Set all submodel outputs below:

*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
   SMOCOMPONENT_PRINT_MAIN_CALC
   *fluidFlow2Index = *fluidFlow1Index;

   if (*smoRChainIDPort1 != *smoRChainIDFromBeginAdaptor) {
	   AME_RAISE_ERROR("The two end adaptors of the R-components chain are not connected with each other.")
   }

   _stateMacroIsCalled = 0;
   _flowMacroIsCalled = 0;
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *fluidState1Index /= ??; CONVERSION UNKNOWN */
/*   *fluidFlow1Index /= ??; CONVERSION UNKNOWN */
/*   *smoRChainIDPort1 /= ??; CONVERSION UNKNOWN */
/*   *fluidFlow2Index /= ??; CONVERSION UNKNOWN */
/*   *fluidState2Index /= ??; CONVERSION UNKNOWN */
/*   *smoRChainIDFromBeginAdaptor /= ??; CONVERSION UNKNOWN */
}

extern double smo_r_adaptor_end_macro0_(int *n
      , double *fluidState2Index, int ic[2], void *ps[1])

{
   double fluidState1Index;
   int loop;
/* >>>>>>>>>>>>Extra Macro Function macro0 Declarations Here. */
/* <<<<<<<<<<<<End of Extra Macro macro0 declarations. */
   loop = 0;

/* Common -> SI units conversions. */

/*   *fluidState2Index *= ??; CONVERSION UNKNOWN */

/*
   Define and return the following macro variable:

   fluidState1Index = ??;
*/


/* >>>>>>>>>>>>Macro Function macro0 Executable Statements. */
   SMOCOMPONENt_PRINT_MACRO_MSG("state1")
   if (firstc_()) {
	   ManagerComponents_R_addMainState2(_component, *fluidState2Index);
   }

   if (_flowMacroIsCalled == 1) {
	   ManagerComponents_R_compute(_component);
   }
   _stateMacroIsCalled = 1;

   fluidState1Index = *fluidState2Index;
/* <<<<<<<<<<<<End of Macro macro0 Executable Statements. */

/* SI -> Common units conversions. */

/*   *fluidState2Index /= ??; CONVERSION UNKNOWN */

/*   *fluidState1Index /= ??; CONVERSION UNKNOWN */

   return fluidState1Index;
}

extern double smo_r_adaptor_end_macro1_(int *n
      , double *fluidFlow1Index, int ic[2], void *ps[1])

{
   double fluidFlow2Index;
   int loop;
/* >>>>>>>>>>>>Extra Macro Function macro1 Declarations Here. */
/* <<<<<<<<<<<<End of Extra Macro macro1 declarations. */
   loop = 0;

/* Common -> SI units conversions. */

/*   *fluidFlow1Index *= ??; CONVERSION UNKNOWN */

/*
   Define and return the following macro variable:

   fluidFlow2Index = ??;
*/


/* >>>>>>>>>>>>Macro Function macro1 Executable Statements. */
   SMOCOMPONENt_PRINT_MACRO_MSG("flow2")
   if (firstc_()) {
	   ManagerComponents_R_addComponentMainState2(_component, *fluidFlow1Index);
   }

   if (_stateMacroIsCalled == 1) {
	   ManagerComponents_R_compute(_component);
   }
   _flowMacroIsCalled = 1;


   fluidFlow2Index = *fluidFlow1Index;
/* <<<<<<<<<<<<End of Macro macro1 Executable Statements. */

/* SI -> Common units conversions. */

/*   *fluidFlow1Index /= ??; CONVERSION UNKNOWN */

/*   *fluidFlow2Index /= ??; CONVERSION UNKNOWN */

   return fluidFlow2Index;
}

