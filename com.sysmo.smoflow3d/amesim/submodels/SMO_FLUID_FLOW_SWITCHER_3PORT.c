/* Submodel SMO_FLUID_FLOW_SWITCHER_3PORT skeleton created by AME Submodel editing utility
   Sun Feb 23 16:53:48 2014 */



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

#define _SUBMODELNAME_ "SMO_FLUID_FLOW_SWITCHER_3PORT"

/* >>>>>>>>>>>>Insert Private Code Here. */
#include "SmoFlowAme.h"
#include "flow/FlowBase.h"
#include "media/MediumState.h"

#define _isPort1Active (*switchingSignal < 0.5)
#define _isPort3Active (*switchingSignal > 0.5)


#define _fluidState1In ps[0]
#define _fluidState1IndexIn ic[0]

#define _fluidState2Out ps[1]
#define _fluidState2IndexOut ic[1]

#define _fluidState3In ps[2]
#define _fluidState3IndexIn ic[2]


#define _fluidFlow1Out ps[3]
#define _fluidFlow1IndexOut ic[3]

#define _fluidFlow2In ps[4]
#define _fluidFlow2IndexIn ic[4]

#define _fluidFlow3Out ps[5]
#define _fluidFlow3IndexOut ic[5]

#define _fluidFlow2In_isInit ic[6]

#define _isSwitchingSignalChanged ic[7]
#define _discFlag_isSwitchingSignalChanged ic[8]
/* <<<<<<<<<<<<End of Private Code. */

/* There is 1 integer parameter:

   useFluidFlowActivationSignal use fluid flow activation signal
*/

void smo_fluid_flow_switcher_3portin_(int *n, int ip[1], int ic[9]
      , void *ps[6])

{
   int loop, error;
/* >>>>>>>>>>>>Extra Initialization Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Initialization declarations. */
   int useFluidFlowActivationSignal;

   useFluidFlowActivationSignal = ip[0];
   loop = 0;
   error = 0;


/* >>>>>>>>>>>>Initialization Function Check Statements. */
/* <<<<<<<<<<<<End of Initialization Check Statements. */

/*   Integer parameter checking:   */

   if (useFluidFlowActivationSignal < 1 || useFluidFlowActivationSignal > 2)
   {
      amefprintf(stderr, "\nuse fluid flow activation signal must be in range [1..2].\n");
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
   _fluidFlow2In_isInit = 0;
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

/*  There are 4 ports.

   Port 1 has 3 variables:

      1 fluidFlow1IndexOut                fluid flow index (port1)             [smoFFL]  multi line macro 'smo_fluid_flow_switcher_3port_macro0_'  UNPLOTTABLE
      2 fluidFlowActivationSignal1Out     fluid flow activation signal (port1) [smoFFAS] multi line macro 'smo_fluid_flow_switcher_3port_macro1_'
      3 fluidState1IndexIn                fluid state index (port1)            [smoTDS]  basic variable input  UNPLOTTABLE

   Port 2 has 3 variables:

      1 fluidState2IndexOut              fluid state index (port2)            [smoTDS]  multi line macro 'smo_fluid_flow_switcher_3port_macro2_'  UNPLOTTABLE
      2 fluidFlow2IndexIn                fluid flow index  (port2)            [smoFFL]  basic variable input  UNPLOTTABLE
      3 fluidFlowActivationSignal2In     fluid flow activation signal (port2) [smoFFAS] basic variable input

   Port 3 has 3 variables:

      1 fluidFlow3IndexOut                fluid flow index (port3)             [smoFFL]  multi line macro 'smo_fluid_flow_switcher_3port_macro3_'  UNPLOTTABLE
      2 fluidFlowActivationSignal3Out     fluid flow activation signal (port3) [smoFFAS] multi line macro 'smo_fluid_flow_switcher_3port_macro4_'
      3 fluidState3IndexIn                fluid state index (port3)            [smoTDS]  basic variable input  UNPLOTTABLE

   Port 4 has 1 variable:

      1 switchingSignal     switching signal (0-port1; 1-port3) [null] basic variable input
*/

/*  There are 0 internal variables.

*/

void smo_fluid_flow_switcher_3port_(int *n, double *fluidFlow1IndexOut
      , double *fluidFlowActivationSignal1Out
      , double *fluidState1IndexIn, double *fluidState2IndexOut
      , double *fluidFlow2IndexIn
      , double *fluidFlowActivationSignal2In
      , double *fluidFlow3IndexOut
      , double *fluidFlowActivationSignal3Out
      , double *fluidState3IndexIn, double *switchingSignal, int ip[1]
      , int ic[9], void *ps[6], int *flag)

{
   int loop, logi;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   int useFluidFlowActivationSignal;

   useFluidFlowActivationSignal = ip[0];
   logi = 0;
   loop = 0;

/* Common -> SI units conversions. */

/*   *fluidFlow1IndexOut *= ??; CONVERSION UNKNOWN */
/*   *fluidFlowActivationSignal1Out *= ??; CONVERSION UNKNOWN */
/*   *fluidState1IndexIn *= ??; CONVERSION UNKNOWN */
/*   *fluidState2IndexOut *= ??; CONVERSION UNKNOWN */
/*   *fluidFlow2IndexIn *= ??; CONVERSION UNKNOWN */
/*   *fluidFlowActivationSignal2In *= ??; CONVERSION UNKNOWN */
/*   *fluidFlow3IndexOut *= ??; CONVERSION UNKNOWN */
/*   *fluidFlowActivationSignal3Out *= ??; CONVERSION UNKNOWN */
/*   *fluidState3IndexIn *= ??; CONVERSION UNKNOWN */

/*
   Set all submodel outputs below:

*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
   SMOCOMPONENT_PRINT_MAIN_CALC
   _isSwitchingSignalChanged = *switchingSignal < 0.5;

   if (firstc_()) {
	   _discFlag_isSwitchingSignalChanged = _isSwitchingSignalChanged;
   }

   if (*flag == 0) { //in a discontinuity
	   _discFlag_isSwitchingSignalChanged = _isSwitchingSignalChanged;
   }

   if (_isSwitchingSignalChanged != _discFlag_isSwitchingSignalChanged) {
	   logi = 1;
   }

   // Finally call disloc to register a discontinuity when logi is 1 (i.e. trigger a discontinuity)
   disloc_(&logi);
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *fluidFlow1IndexOut /= ??; CONVERSION UNKNOWN */
/*   *fluidFlowActivationSignal1Out /= ??; CONVERSION UNKNOWN */
/*   *fluidState1IndexIn /= ??; CONVERSION UNKNOWN */
/*   *fluidState2IndexOut /= ??; CONVERSION UNKNOWN */
/*   *fluidFlow2IndexIn /= ??; CONVERSION UNKNOWN */
/*   *fluidFlowActivationSignal2In /= ??; CONVERSION UNKNOWN */
/*   *fluidFlow3IndexOut /= ??; CONVERSION UNKNOWN */
/*   *fluidFlowActivationSignal3Out /= ??; CONVERSION UNKNOWN */
/*   *fluidState3IndexIn /= ??; CONVERSION UNKNOWN */
}

extern double smo_fluid_flow_switcher_3port_macro0_(int *n
      , double *fluidFlow2IndexIn, double *switchingSignal, int ip[1]
      , int ic[9], void *ps[6], int *flag)

{
   double fluidFlow1IndexOut;
   int loop, logi;
/* >>>>>>>>>>>>Extra Macro Function macro0 Declarations Here. */
/* <<<<<<<<<<<<End of Extra Macro macro0 declarations. */
   int useFluidFlowActivationSignal;

   useFluidFlowActivationSignal = ip[0];
   logi = 0;
   loop = 0;

/* Common -> SI units conversions. */

/*   *fluidFlow2IndexIn *= ??; CONVERSION UNKNOWN */

/*
   Define and return the following macro variable:

   fluidFlow1IndexOut = ??;
*/


/* >>>>>>>>>>>>Macro Function macro0 Executable Statements. */
   SMOCOMPONENt_PRINT_MACRO_MSG("fluidFlow1IndexOut")

   if (firstc_()) {
	   if (_fluidFlow2In_isInit == 0) {
		   _fluidFlow2IndexIn = *fluidFlow2IndexIn;
		   _fluidFlow2In = FluidFlow_get(_fluidFlow2IndexIn);
		   _fluidFlow2In_isInit = 1;
	   }

	   _fluidFlow1Out = FluidFlow_new();
	   _fluidFlow1IndexOut = FluidFlow_register(_fluidFlow1Out);
   }

   if (_isPort1Active) {
	   FluidFlow_copy(_fluidFlow2In, _fluidFlow1Out);
   } else {
	   FluidFlow_zero(_fluidFlow1Out);
   }

   fluidFlow1IndexOut = _fluidFlow1IndexOut;
/* <<<<<<<<<<<<End of Macro macro0 Executable Statements. */

/* SI -> Common units conversions. */

/*   *fluidFlow2IndexIn /= ??; CONVERSION UNKNOWN */

/*   *fluidFlow1IndexOut /= ??; CONVERSION UNKNOWN */

   return fluidFlow1IndexOut;
}

extern double smo_fluid_flow_switcher_3port_macro1_(int *n
      , double *fluidFlowActivationSignal2In, double *switchingSignal
      , int ip[1], int ic[9], void *ps[6], int *flag)

{
   double fluidFlowActivationSignal1Out;
   int loop, logi;
/* >>>>>>>>>>>>Extra Macro Function macro1 Declarations Here. */
/* <<<<<<<<<<<<End of Extra Macro macro1 declarations. */
   int useFluidFlowActivationSignal;

   useFluidFlowActivationSignal = ip[0];
   logi = 0;
   loop = 0;

/* Common -> SI units conversions. */

/*   *fluidFlowActivationSignal2In *= ??; CONVERSION UNKNOWN */

/*
   Define and return the following macro variable:

   fluidFlowActivationSignal1Out = ??;
*/


/* >>>>>>>>>>>>Macro Function macro1 Executable Statements. */
   SMOCOMPONENt_PRINT_MACRO_MSG("fluidFlowActivationSignal1Out")

   if (useFluidFlowActivationSignal == 1) { //no
	   fluidFlowActivationSignal1Out = -1; //not used
   } else { // yes
	   fluidFlowActivationSignal1Out = *fluidFlowActivationSignal2In;
   }
/* <<<<<<<<<<<<End of Macro macro1 Executable Statements. */

/* SI -> Common units conversions. */

/*   *fluidFlowActivationSignal2In /= ??; CONVERSION UNKNOWN */

/*   *fluidFlowActivationSignal1Out /= ??; CONVERSION UNKNOWN */

   return fluidFlowActivationSignal1Out;
}

extern double smo_fluid_flow_switcher_3port_macro2_(int *n
      , double *fluidState1IndexIn, double *fluidState3IndexIn
      , double *switchingSignal, int ip[1], int ic[9], void *ps[6]
      , int *flag)

{
   double fluidState2IndexOut;
   int loop, logi;
/* >>>>>>>>>>>>Extra Macro Function macro2 Declarations Here. */
/* <<<<<<<<<<<<End of Extra Macro macro2 declarations. */
   int useFluidFlowActivationSignal;

   useFluidFlowActivationSignal = ip[0];
   logi = 0;
   loop = 0;

/* Common -> SI units conversions. */

/*   *fluidState1IndexIn *= ??; CONVERSION UNKNOWN */
/*   *fluidState3IndexIn *= ??; CONVERSION UNKNOWN */

/*
   Define and return the following macro variable:

   fluidState2IndexOut = ??;
*/


/* >>>>>>>>>>>>Macro Function macro2 Executable Statements. */
   SMOCOMPONENt_PRINT_MACRO_MSG("fluidState2IndexOut")

   if (firstc_()) {
	   _fluidState1IndexIn = *fluidState1IndexIn;
	   _fluidState1In = MediumState_get(_fluidState1IndexIn);
	   int medium1Index = Medium_index(MediumState_getMedium(_fluidState1In));

	   _fluidState3IndexIn = *fluidState3IndexIn;
	   _fluidState3In = MediumState_get(_fluidState3IndexIn);
	   int medium3Index = Medium_index(MediumState_getMedium(_fluidState3In));

	   if (medium1Index != medium3Index) {
		   AME_RAISE_ERROR("Different media connected to the fluid flow switcher component!")
	   }

	   Medium* fluid = Medium_get(medium1Index);
	   _fluidState2Out = MediumState_new(fluid);
	   _fluidState2IndexOut = MediumState_register(_fluidState2Out);
   }

   //:TODO: (Milen) create a copy function for fluid states
   if (_isPort1Active) { //Port1 is active
	   MediumState_update_ph(_fluidState2Out, MediumState_p(_fluidState1In), MediumState_h(_fluidState1In));
   } else { //Port3 is active
	   MediumState_update_ph(_fluidState2Out, MediumState_p(_fluidState3In), MediumState_h(_fluidState3In));
   }

   fluidState2IndexOut = _fluidState2IndexOut;
/* <<<<<<<<<<<<End of Macro macro2 Executable Statements. */

/* SI -> Common units conversions. */

/*   *fluidState1IndexIn /= ??; CONVERSION UNKNOWN */
/*   *fluidState3IndexIn /= ??; CONVERSION UNKNOWN */

/*   *fluidState2IndexOut /= ??; CONVERSION UNKNOWN */

   return fluidState2IndexOut;
}

extern double smo_fluid_flow_switcher_3port_macro3_(int *n
      , double *fluidFlow2IndexIn, double *switchingSignal, int ip[1]
      , int ic[9], void *ps[6], int *flag)

{
   double fluidFlow3IndexOut;
   int loop, logi;
/* >>>>>>>>>>>>Extra Macro Function macro3 Declarations Here. */
/* <<<<<<<<<<<<End of Extra Macro macro3 declarations. */
   int useFluidFlowActivationSignal;

   useFluidFlowActivationSignal = ip[0];
   logi = 0;
   loop = 0;

/* Common -> SI units conversions. */

/*   *fluidFlow2IndexIn *= ??; CONVERSION UNKNOWN */

/*
   Define and return the following macro variable:

   fluidFlow3IndexOut = ??;
*/


/* >>>>>>>>>>>>Macro Function macro3 Executable Statements. */
   SMOCOMPONENt_PRINT_MACRO_MSG("fluidFlow3IndexOut")

   if (firstc_()) {
	   if (_fluidFlow2In_isInit == 0) {
		   _fluidFlow2IndexIn = *fluidFlow2IndexIn;
		   _fluidFlow2In = FluidFlow_get(_fluidFlow2IndexIn);
		   _fluidFlow2In_isInit = 1;
	   }

	   _fluidFlow3Out = FluidFlow_new();
	   _fluidFlow3IndexOut = FluidFlow_register(_fluidFlow3Out);
   }

   if (_isPort3Active) {
	   FluidFlow_copy(_fluidFlow2In, _fluidFlow3Out);
   } else {
	   FluidFlow_zero(_fluidFlow3Out);
   }

   fluidFlow3IndexOut = _fluidFlow3IndexOut;
/* <<<<<<<<<<<<End of Macro macro3 Executable Statements. */

/* SI -> Common units conversions. */

/*   *fluidFlow2IndexIn /= ??; CONVERSION UNKNOWN */

/*   *fluidFlow3IndexOut /= ??; CONVERSION UNKNOWN */

   return fluidFlow3IndexOut;
}

extern double smo_fluid_flow_switcher_3port_macro4_(int *n
      , double *fluidFlowActivationSignal2In, double *switchingSignal
      , int ip[1], int ic[9], void *ps[6], int *flag)

{
   double fluidFlowActivationSignal3Out;
   int loop, logi;
/* >>>>>>>>>>>>Extra Macro Function macro4 Declarations Here. */
/* <<<<<<<<<<<<End of Extra Macro macro4 declarations. */
   int useFluidFlowActivationSignal;

   useFluidFlowActivationSignal = ip[0];
   logi = 0;
   loop = 0;

/* Common -> SI units conversions. */

/*   *fluidFlowActivationSignal2In *= ??; CONVERSION UNKNOWN */

/*
   Define and return the following macro variable:

   fluidFlowActivationSignal3Out = ??;
*/


/* >>>>>>>>>>>>Macro Function macro4 Executable Statements. */
   SMOCOMPONENt_PRINT_MACRO_MSG("fluidFlowActivationSignal3Out")

   if (useFluidFlowActivationSignal == 1) { //no
	   fluidFlowActivationSignal3Out = -1; //not used
   } else { // yes
	   fluidFlowActivationSignal3Out = *fluidFlowActivationSignal2In;
   }
/* <<<<<<<<<<<<End of Macro macro4 Executable Statements. */

/* SI -> Common units conversions. */

/*   *fluidFlowActivationSignal2In /= ??; CONVERSION UNKNOWN */

/*   *fluidFlowActivationSignal3Out /= ??; CONVERSION UNKNOWN */

   return fluidFlowActivationSignal3Out;
}

