/* Submodel SMO_ORIFICE_COMPRESSIBLE_IDEAL_GAS skeleton created by AME Submodel editing utility
   ??? ??? 9 10:15:36 2019 */



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

#define _SUBMODELNAME_ "SMO_ORIFICE_COMPRESSIBLE_IDEAL_GAS"

/* >>>>>>>>>>>>Insert Private Code Here. */
#include "SmoFlowAme.h"
#include "flow/Valve.h"

#define _component ps[0]

#define _fluidFlow1 ps[1]
#define _fluidFlow1Index ic[1]

#define _fluidFlow2 ps[2]
#define _fluidFlow2Index ic[2]
/* <<<<<<<<<<<<End of Private Code. */


/* There are 4 real parameters:

   orificeArea       orifice area               [mm**2 -> m**2]
   flowCoefficient  flow coefficient            [null]
   openingPressDiff opening pressure difference [bar -> Pa]
   closingPressDiff closing pressure difference [bar -> Pa]
*/


/* There are 3 integer parameters:

   allowBidirectionalFlow       allow bi-directional flow              
   useFluidFlowActivationSignal use fluid flow activation signal       
   useOpeningClosingPressDiff   use opening/closing pressure difference
*/

void smo_orifice_compressible_ideal_gasin_(int *n, double rp[4]
      , int ip[3], int ic[3], void *ps[3])

{
   int loop, error;
/* >>>>>>>>>>>>Extra Initialization Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Initialization declarations. */
   int allowBidirectionalFlow, useFluidFlowActivationSignal, 
      useOpeningClosingPressDiff;
   double orificeArea, flowCoefficient, openingPressDiff, 
      closingPressDiff;

   allowBidirectionalFlow = ip[0];
   useFluidFlowActivationSignal = ip[1];
   useOpeningClosingPressDiff = ip[2];

   orificeArea = rp[0];
   flowCoefficient = rp[1];
   openingPressDiff = rp[2];
   closingPressDiff = rp[3];
   loop = 0;
   error = 0;

/*
   If necessary, check values of the following:

   rp[0..3]
*/


/* >>>>>>>>>>>>Initialization Function Check Statements. */
   if (flowCoefficient < 0.0 || flowCoefficient > 1.0)
   {
	   amefprintf(stderr, "\nflow coefficient = %f, but must be in range [0.0 .. 1.0].\n", flowCoefficient);
	   error = 2;
   }

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

   rp[0]    *= 1.00000000000000e-006;
   orificeArea = rp[0];
   rp[2]    *= 1.00000000000000e+005;
   openingPressDiff = rp[2];
   rp[3]    *= 1.00000000000000e+005;
   closingPressDiff = rp[3];


/* >>>>>>>>>>>>Initialization Function Executable Statements. */
   _component = Valve_OrificeCompressibleIdealGas_new(
		   allowBidirectionalFlow - 1, //:TRICKY: allowBidirectionalFlow = {1-no, 2-yes} - 1 = {0-no, 1-yes});
		   orificeArea,
		   flowCoefficient);
   SMOCOMPONENT_SET_PROPS(_component)

   Valve_setPressureDifferenceParameters(
		   _component, useOpeningClosingPressDiff - 1,  //:TRICKY: useOpeningClosingPressDiff = '{1-no, 2-yes} - 1'  =  '{0-no, 1-yes}'
		   openingPressDiff, closingPressDiff);

   _fluidFlow1 = FluidFlow_new();
   _fluidFlow1Index = FluidFlow_register(_fluidFlow1);
   _fluidFlow2 = FluidFlow_new();
   _fluidFlow2Index = FluidFlow_register(_fluidFlow2);
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

/*  There are 3 ports.

   Port 1 has 3 variables:

      1 fluidFlow1Index               fluid flow1 index                                                      [smoFFL]  basic variable output  UNPLOTTABLE
      2 fluidFlowActivationSignal     flow activation signal = {-1 - not used; 0 - deactivate; 1 - activate} [smoFFAS] basic variable output
      3 fluidState1Index              fluid state1 index                                                     [smoTDS]  basic variable input  UNPLOTTABLE

   Port 2 has 1 variable:

      1 regulatingSignal     regulating signal [null] basic variable input

   Port 3 has 3 variables:

      1 fluidFlow2Index                  fluid flow2 index                                                      [smoFFL] basic variable output  UNPLOTTABLE
      2 fluidFlowActivationSignalDup     duplicate of fluidFlowActivationSignal                                
      3 fluidState2Index                 fluid state2 index                                                     [smoTDS] basic variable input  UNPLOTTABLE
*/

/*  There are 4 internal variables.

      1 massFlowRate         mass flow rate (port1 -> port3)       [kg/s]        basic variable
      2 enthalpyFlowRate     enthalpy flow rate (port1 -> port3)   [W]           basic variable
      3 pressureLoss         total pressure loss                   [barA -> PaA] basic variable
      4 flowType             flow type = {0 - subsonic, 1 - sonic} [null]        basic variable
*/

void smo_orifice_compressible_ideal_gas_(int *n
      , double *fluidFlow1Index, double *fluidFlowActivationSignal
      , double *fluidState1Index, double *regulatingSignal
      , double *fluidFlow2Index, double *fluidState2Index
      , double *massFlowRate, double *enthalpyFlowRate
      , double *pressureLoss, double *flowType, double rp[4]
      , int ip[3], int ic[3], void *ps[3], int *flag)

{
   int loop, logi;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   int allowBidirectionalFlow, useFluidFlowActivationSignal, 
      useOpeningClosingPressDiff;
   double orificeArea, flowCoefficient, openingPressDiff, 
      closingPressDiff;

   allowBidirectionalFlow = ip[0];
   useFluidFlowActivationSignal = ip[1];
   useOpeningClosingPressDiff = ip[2];

   orificeArea = rp[0];
   flowCoefficient = rp[1];
   openingPressDiff = rp[2];
   closingPressDiff = rp[3];
   logi = 0;
   loop = 0;

/* Common -> SI units conversions. */

/*   *fluidState1Index *= ??; CONVERSION UNKNOWN [smoTDS] */
/*   *fluidState2Index *= ??; CONVERSION UNKNOWN [smoTDS] */

/*
   Set all submodel outputs below:

   *fluidFlow1Index = ??;
   *fluidFlowActivationSignal = ??;
   *fluidFlow2Index = ??;
   *massFlowRate = ??;
   *enthalpyFlowRate = ??;
   *pressureLoss = ??;
   *flowType   = ??;
*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
   SMOCOMPONENT_PRINT_MAIN_CALC
   if (firstc_()) {
	   MediumState* state1 = MediumState_get(*fluidState1Index);
	   MediumState* state2 = MediumState_get(*fluidState2Index);
	   Valve_init(_component, state1, state2);
   }

   Valve_setRegulatingSignal(_component, *regulatingSignal);
   Valve_compute(_component);
   Valve_updateFluidFlows(_component, _fluidFlow1, _fluidFlow2);

   *massFlowRate = FluidFlow_getMassFlowRate(_fluidFlow2);
   *enthalpyFlowRate = FluidFlow_getEnthalpyFlowRate(_fluidFlow2);
   *pressureLoss = Valve_getAbsolutePressureDrop(_component);
   *flowType = Valve_getFlowType(_component);

   *fluidFlow1Index = _fluidFlow1Index;
   *fluidFlow2Index = _fluidFlow2Index;

   if (useFluidFlowActivationSignal == 1) { //no
	   *fluidFlowActivationSignal = -1; //not used
   } else { // yes
	   if (Valve_getIsFlowClosed(_component) == 1) {
		   *fluidFlowActivationSignal = 0; //deactivate flow
	   } else {
		   *fluidFlowActivationSignal = 1; //activate flow
	   }
   }
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *fluidFlow1Index /= ??; CONVERSION UNKNOWN [smoFFL] */
/*   *fluidFlowActivationSignal /= ??; CONVERSION UNKNOWN [smoFFAS] */
/*   *fluidState1Index /= ??; CONVERSION UNKNOWN [smoTDS] */
/*   *fluidFlow2Index /= ??; CONVERSION UNKNOWN [smoFFL] */
/*   *fluidState2Index /= ??; CONVERSION UNKNOWN [smoTDS] */
   *pressureLoss /= 1.00000000000000e+005;
}

