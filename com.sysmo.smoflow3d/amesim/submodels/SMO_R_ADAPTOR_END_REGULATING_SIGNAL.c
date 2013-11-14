/* Submodel SMO_R_ADAPTOR_END_REGULATING_SIGNAL skeleton created by AME Submodel editing utility
   Thu Nov 14 12:03:08 2013 */



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

#define _SUBMODELNAME_ "SMO_R_ADAPTOR_END_REGULATING_SIGNAL"

/* >>>>>>>>>>>>Insert Private Code Here. */
#include "SmoFlowAme.h"
#include "flow_R/ManagerComponents_R.h"
#include "flow_R/Adaptor_R.h"

#define _component ps[0]
#define _componentIndex ic[0]

#define _manager ps[1]
#define _managerIndex ic[1]

#define _fluidState2Index ic[2]
#define _fluidFlow2Index ic[3]

#define _stateMacroIsCalled ic[4]
#define _flowMacroIsCalled ic[5]
/* <<<<<<<<<<<<End of Private Code. */
void smo_r_adaptor_end_regulating_signalin_(int *n, int ic[6]
      , void *ps[2], double *regulatingSignal)

{
   int loop, error;
/* >>>>>>>>>>>>Extra Initialization Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Initialization declarations. */
   loop = 0;
   error = 0;

/*
   Check and/or reset the following fixed and/or discrete variable

   *regulatingSignal = ??;
*/


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
   _componentIndex = Component_R_register(_component);
   SMOCOMPONENT_SET_PROPS(_component);

   _manager = NULL;
   _managerIndex = -1;

   _stateMacroIsCalled = 0;
   _flowMacroIsCalled = 0;
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

/*  There are 4 ports.

   Port 1 has 3 variables:

      1 outputRCompID1     R-component ID (output, port1) [smoRCompID]  multi line macro 'smo_r_adaptor_end_regulating_signal_macro0_'  UNPLOTTABLE
      2 inputRCompID1      R-component ID (input, port1)  [smoRCompID]  basic variable input  UNPLOTTABLE
      3 smoRChainID        R-components chain ID (port1)  [smoRChainID] basic variable input  UNPLOTTABLE

   Port 2 has 2 variables:

      1 fluidFlow2Index      fluid flow2 index  [smoFFL] multi line macro 'smo_r_adaptor_end_regulating_signal_macro1_'  UNPLOTTABLE
      2 fluidState2Index     fluid state2 index [smoTDS] basic variable input  UNPLOTTABLE

   Port 3 has 1 variable:

      1 smoRChainIDFromBeginAdaptor     R-components chain ID (port3) [smoRChainID] basic variable input

   Port 4 has 1 variable:

      1 regulatingSignal     regulating signal (0-off, 1-on) [null] discrete
*/

/*  There are 0 internal variables.

*/

void smo_r_adaptor_end_regulating_signal_(int *n
      , double *outputRCompID1, double *inputRCompID1
      , double *smoRChainID, double *fluidFlow2Index
      , double *fluidState2Index, double *smoRChainIDFromBeginAdaptor
      , double *regulatingSignal, int ic[6], void *ps[2], int *flag)

{
   int loop, logi;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   logi = 0;
   loop = 0;

/* Common -> SI units conversions. */

/*   *outputRCompID1 *= ??; CONVERSION UNKNOWN */
/*   *inputRCompID1 *= ??; CONVERSION UNKNOWN */
/*   *smoRChainID *= ??; CONVERSION UNKNOWN */
/*   *fluidFlow2Index *= ??; CONVERSION UNKNOWN */
/*   *fluidState2Index *= ??; CONVERSION UNKNOWN */
/*   *smoRChainIDFromBeginAdaptor *= ??; CONVERSION UNKNOWN */

/*
   Set all submodel outputs below:

*/


/*
   The following discrete variable(s) can be reset when the discontinuity flag is zero:

   *regulatingSignal = ??;
*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
   SMOCOMPONENT_PRINT_MAIN_CALC
   if (*smoRChainID != *smoRChainIDFromBeginAdaptor) {
	   AME_RAISE_ERROR("The two end adaptors of the R-components chain are not connected with each other.")
   }

   _stateMacroIsCalled = 0;
   _flowMacroIsCalled = 0;
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *outputRCompID1 /= ??; CONVERSION UNKNOWN */
/*   *inputRCompID1 /= ??; CONVERSION UNKNOWN */
/*   *smoRChainID /= ??; CONVERSION UNKNOWN */
/*   *fluidFlow2Index /= ??; CONVERSION UNKNOWN */
/*   *fluidState2Index /= ??; CONVERSION UNKNOWN */
/*   *smoRChainIDFromBeginAdaptor /= ??; CONVERSION UNKNOWN */
}

extern double smo_r_adaptor_end_regulating_signal_macro0_(int *n
      , double *fluidState2Index, int ic[6], void *ps[2], int *flag)

{
   double outputRCompID1;
   int loop, logi;
/* >>>>>>>>>>>>Extra Macro Function macro0 Declarations Here. */
/* <<<<<<<<<<<<End of Extra Macro macro0 declarations. */
   logi = 0;
   loop = 0;

/* Common -> SI units conversions. */

/*   *fluidState2Index *= ??; CONVERSION UNKNOWN */

/*
   Define and return the following macro variable:

   outputRCompID1 = ??;
*/


/* >>>>>>>>>>>>Macro Function macro0 Executable Statements. */
   SMOCOMPONENt_PRINT_MACRO_MSG("outputRCompID1")
   if (firstc_()) {
	   _fluidState2Index = *fluidState2Index;

	   if (_flowMacroIsCalled == 1) { //i.e. _manager != NULL
		   ManagerComponents_R_addMainState2(_manager, _component, _fluidState2Index);
	   }
   }

   if (_flowMacroIsCalled == 1) {
	   ManagerComponents_R_compute(_manager, _component);
   }
   _stateMacroIsCalled = 1;

   outputRCompID1 = _componentIndex;
/* <<<<<<<<<<<<End of Macro macro0 Executable Statements. */

/* SI -> Common units conversions. */

/*   *fluidState2Index /= ??; CONVERSION UNKNOWN */

/*   *outputRCompID1 /= ??; CONVERSION UNKNOWN */

   return outputRCompID1;
}

extern double smo_r_adaptor_end_regulating_signal_macro1_(int *n
      , double *inputRCompID1, double *smoRChainID
      , double *regulatingSignal, int ic[6], void *ps[2], int *flag)

{
   double fluidFlow2Index;
   int loop, logi;
/* >>>>>>>>>>>>Extra Macro Function macro1 Declarations Here. */
/* <<<<<<<<<<<<End of Extra Macro macro1 declarations. */
   logi = 0;
   loop = 0;

/* Common -> SI units conversions. */

/*   *inputRCompID1 *= ??; CONVERSION UNKNOWN */
/*   *smoRChainID *= ??; CONVERSION UNKNOWN */

/*
   Define and return the following macro variable:

   fluidFlow2Index = ??;
*/


/* >>>>>>>>>>>>Macro Function macro1 Executable Statements. */
   SMOCOMPONENt_PRINT_MACRO_MSG("flow2")
   if (firstc_()) {
	   _managerIndex = *smoRChainID;
	   _manager = ManagerComponents_R_get(_managerIndex);

	   if (_stateMacroIsCalled == 1) { //i.e. _fluidState2Index != -1
		   ManagerComponents_R_addMainState2(_manager, _component, _fluidState2Index);
	   }

	   ManagerComponents_R_setComponentMainState2(_manager, _component, *inputRCompID1);
   }
   EndAdaptor_R_setRegulatingSignal(_component, *regulatingSignal);

   if (_stateMacroIsCalled == 1) {
	   ManagerComponents_R_compute(_manager, _component);
   }
   _flowMacroIsCalled = 1;


   fluidFlow2Index = ManagerComponents_R_getFlow2Index(_manager);
/* <<<<<<<<<<<<End of Macro macro1 Executable Statements. */

/* SI -> Common units conversions. */

/*   *inputRCompID1 /= ??; CONVERSION UNKNOWN */
/*   *smoRChainID /= ??; CONVERSION UNKNOWN */

/*   *fluidFlow2Index /= ??; CONVERSION UNKNOWN */

   return fluidFlow2Index;
}

