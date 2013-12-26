/* Submodel SMO_R_ADAPTOR_END_ACTIVATING_SIGNAL skeleton created by AME Submodel editing utility
   Thu Dec 26 14:59:26 2013 */



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

#define _SUBMODELNAME_ "SMO_R_ADAPTOR_END_ACTIVATING_SIGNAL"

/* >>>>>>>>>>>>Insert Private Code Here. */
#include "SmoFlowAme.h"
#include "flow_R/ManagerComponents_R.h"
#include "flow_R/Adaptor_R.h"

#define _component ps[0]
#define _componentIndex ic[0]

#define _manager ps[1]
#define _managerIndex ic[1]
/* <<<<<<<<<<<<End of Private Code. */


/* There are 2 real parameters:

   openingPressDiff opening pressure difference [bar -> Pa]
   closingPressDiff closing pressure difference [bar -> Pa]
*/


/* There are 3 integer parameters:

   allowBidirectionalFlow       allow bi-directional flow              
   useFluidFlowActivationSignal use fluid flow activation signal       
   useOpeningClosingPressDiff   use opening/closing pressure difference
*/

void smo_r_adaptor_end_activating_signalin_(int *n, double rp[2]
      , int ip[3], int ic[2], void *ps[2], double *isFlowOpen)

{
   int loop, error;
/* >>>>>>>>>>>>Extra Initialization Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Initialization declarations. */
   int allowBidirectionalFlow, useFluidFlowActivationSignal, 
      useOpeningClosingPressDiff;
   double openingPressDiff, closingPressDiff;

   allowBidirectionalFlow = ip[0];
   useFluidFlowActivationSignal = ip[1];
   useOpeningClosingPressDiff = ip[2];

   openingPressDiff = rp[0];
   closingPressDiff = rp[1];
   loop = 0;
   error = 0;

/*
   If necessary, check values of the following:

   rp[0..1]
*/

/*
   Check and/or reset the following fixed and/or discrete variable

   *isFlowOpen = ??;
*/


/* >>>>>>>>>>>>Initialization Function Check Statements. */
   if (useOpeningClosingPressDiff == 2 && openingPressDiff < closingPressDiff)
   {
      amefprintf(stderr, "\n Closing pressure difference must be less than opening pressure difference.\n");
      error = 2;
   }
/* <<<<<<<<<<<<End of Initialization Check Statements. */

/*   Integer parameter checking:   */

   if (allowBidirectionalFlow < 1 || allowBidirectionalFlow > 2)
   {
      amefprintf(stderr, "\nallow bi-directional flow must be in range [1..2].\n");
      error = 2;
   }
   if (useFluidFlowActivationSignal < 1 || useFluidFlowActivationSignal > 2)
   {
      amefprintf(stderr, "\nuse fluid flow activation signal must be in range [1..2].\n");
      error = 2;
   }
   if (useOpeningClosingPressDiff < 1 || useOpeningClosingPressDiff > 2)
   {
      amefprintf(stderr, "\nuse opening/closing pressure difference must be in range [1..2].\n");
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

   rp[0]    *= 1.00000000000000e+005;
   openingPressDiff = rp[0];
   rp[1]    *= 1.00000000000000e+005;
   closingPressDiff = rp[1];


/* >>>>>>>>>>>>Initialization Function Executable Statements. */
   _component = EndAdaptor_R_new(allowBidirectionalFlow - 1); //:TRICKY: allowBidirectionalFlow =  '{1-no, 2-yes} - 1'  =  '{0-no, 1-yes}'
   _componentIndex = Component_R_register(_component);
   SMOCOMPONENT_SET_PROPS(_component);

   EndAdaptor_R_setPressureDifferenceParameters(
		   _component, useOpeningClosingPressDiff - 1,  //:TRICKY: useOpeningClosingPressDiff = '{1-no, 2-yes} - 1'  =  '{0-no, 1-yes}'
		   openingPressDiff, closingPressDiff);

   _manager = NULL;
   _managerIndex = -1;
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

/*  There are 4 ports.

   Port 1 has 3 variables:

      1 outputRCompID1     R-component ID (output, port1) [smoRCompID]  multi line macro 'smo_r_adaptor_end_activating_signal_macro0_'  UNPLOTTABLE
      2 inputRCompID1      R-component ID (input, port1)  [smoRCompID]  basic variable input  UNPLOTTABLE
      3 smoRChainID        R-components chain ID (port1)  [smoRChainID] basic variable input  UNPLOTTABLE

   Port 2 has 3 variables:

      1 fluidFlow2Index               fluid flow2 index                                                      [smoFFL]  basic variable output  UNPLOTTABLE
      2 fluidFlowActivationSignal     flow activation signal = {-1 - not used; 0 - deactivate; 1 - activate} [smoFFAS] basic variable output
      3 fluidState2Index              fluid state2 index                                                     [smoTDS]  basic variable input  UNPLOTTABLE

   Port 3 has 1 variable:

      1 smoRChainIDFromBeginAdaptor     R-components chain ID (port3) [smoRChainID] basic variable input

   Port 4 has 1 variable:

      1 activatingSignal     activating signal (0-off, 1-on) (port4) [null] basic variable input
*/

/*  There is 1 internal variable.

      1 isFlowOpen     is flow open (0-no, 1-yes) [null] discrete
*/

void smo_r_adaptor_end_activating_signal_(int *n
      , double *outputRCompID1, double *inputRCompID1
      , double *smoRChainID, double *fluidFlow2Index
      , double *fluidFlowActivationSignal, double *fluidState2Index
      , double *smoRChainIDFromBeginAdaptor, double *activatingSignal
      , double *isFlowOpen, double rp[2], int ip[3], int ic[2]
      , void *ps[2], int *flag)

{
   int loop, logi;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   int allowBidirectionalFlow, useFluidFlowActivationSignal, 
      useOpeningClosingPressDiff;
   double openingPressDiff, closingPressDiff;

   allowBidirectionalFlow = ip[0];
   useFluidFlowActivationSignal = ip[1];
   useOpeningClosingPressDiff = ip[2];

   openingPressDiff = rp[0];
   closingPressDiff = rp[1];
   logi = 0;
   loop = 0;

/* Common -> SI units conversions. */

/*   *outputRCompID1 *= ??; CONVERSION UNKNOWN */
/*   *inputRCompID1 *= ??; CONVERSION UNKNOWN */
/*   *smoRChainID *= ??; CONVERSION UNKNOWN */
/*   *fluidState2Index *= ??; CONVERSION UNKNOWN */
/*   *smoRChainIDFromBeginAdaptor *= ??; CONVERSION UNKNOWN */

/*
   Set all submodel outputs below:

   *fluidFlow2Index = ??;
   *fluidFlowActivationSignal = ??;
*/


/*
   The following discrete variable(s) can be reset when the discontinuity flag is zero:

   *isFlowOpen = ??;
*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
   SMOCOMPONENT_PRINT_MAIN_CALC
   if (*smoRChainID != *smoRChainIDFromBeginAdaptor) {
	   AME_RAISE_ERROR("The two end adaptors of the R-components chain are not connected with each other.")
   }

   if (firstc_()) {
	   _managerIndex = *smoRChainID;
	   _manager = ManagerComponents_R_get(_managerIndex);

	   ManagerComponents_R_checkComponentOuterState2(_manager, _component, *inputRCompID1);
   }

   ManagerComponents_R_clearIsComputed(_manager);

   *isFlowOpen = ManagerComponents_R_getIsFlowOpen(_manager);
   *fluidFlow2Index = ManagerComponents_R_getFlow2Index(_manager);

   if (useFluidFlowActivationSignal == 1) { //no
	   *fluidFlowActivationSignal = -1; //not used
   } else { // yes
	   if (ManagerComponents_R_getIsFlowOpen(_manager) == 0) { //flow is closed
		   *fluidFlowActivationSignal = 0; //deactivate flow
	   } else {
		   *fluidFlowActivationSignal = 1; //activate flow
	   }
   }
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *outputRCompID1 /= ??; CONVERSION UNKNOWN */
/*   *inputRCompID1 /= ??; CONVERSION UNKNOWN */
/*   *smoRChainID /= ??; CONVERSION UNKNOWN */
/*   *fluidFlow2Index /= ??; CONVERSION UNKNOWN */
/*   *fluidFlowActivationSignal /= ??; CONVERSION UNKNOWN */
/*   *fluidState2Index /= ??; CONVERSION UNKNOWN */
/*   *smoRChainIDFromBeginAdaptor /= ??; CONVERSION UNKNOWN */
}

extern double smo_r_adaptor_end_activating_signal_macro0_(int *n
      , double *fluidState2Index, double *activatingSignal
      , double rp[2], int ip[3], int ic[2], void *ps[2], int *flag)

{
   double outputRCompID1;
   int loop, logi;
/* >>>>>>>>>>>>Extra Macro Function macro0 Declarations Here. */
/* <<<<<<<<<<<<End of Extra Macro macro0 declarations. */
   int allowBidirectionalFlow, useFluidFlowActivationSignal, 
      useOpeningClosingPressDiff;
   double openingPressDiff, closingPressDiff;

   allowBidirectionalFlow = ip[0];
   useFluidFlowActivationSignal = ip[1];
   useOpeningClosingPressDiff = ip[2];

   openingPressDiff = rp[0];
   closingPressDiff = rp[1];
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
	   Adaptor_R_setOuterStateIndex(_component, *fluidState2Index);
   }
   EndAdaptor_R_setActivatingSignal(_component, *activatingSignal);

   outputRCompID1 = _componentIndex;
/* <<<<<<<<<<<<End of Macro macro0 Executable Statements. */

/* SI -> Common units conversions. */

/*   *fluidState2Index /= ??; CONVERSION UNKNOWN */

/*   *outputRCompID1 /= ??; CONVERSION UNKNOWN */

   return outputRCompID1;
}

