/* Submodel SMO_VALVE_2PORT_REGULATING_SIGNAL skeleton created by AME Submodel editing utility
   Sat Aug 3 16:50:31 2013 */



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

#define _SUBMODELNAME_ "SMO_VALVE_2PORT_REGULATING_SIGNAL"

/* >>>>>>>>>>>>Insert Private Code Here. */
#include "media/MediumState.h"
#include "flow/FlowBase.h"
#include "flow/TwoPortValve.h"

#define _valve ps[0]

#define _fluidFlowIndex1 ic[1]
#define _fluidFlow1 ps[1]

#define _fluidFlowIndex3 ic[2]
#define _fluidFlow3 ps[2]

#define _fluidStateIndex1 ic[3]
#define _fluidState1 ps[3]

#define _fluidStateIndex3 ic[4]
#define _fluidState3 ps[4]
/* <<<<<<<<<<<<End of Private Code. */


/* There are 4 real parameters:

   Kv                           flow coefficient Kv            [null]
   transitionMassFlowRate       transition mass flow rate      [kg/s]
   transitionPressureDifference transition pressure difference [bar -> Pa]
   maximumMassFlowRate          maximum mass flow              [kg/s]
*/


/* There are 2 integer parameters:

   transitionChoice       choice of transition to linear region
   allowBidirectionalFlow allow bi-directional flow            
*/

void smo_valve_2port_regulating_signalin_(int *n, double rp[4]
      , int ip[2], int ic[5], void *ps[5])

{
   int loop, error;
/* >>>>>>>>>>>>Extra Initialization Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Initialization declarations. */
   int transitionChoice, allowBidirectionalFlow;
   double Kv, transitionMassFlowRate, transitionPressureDifference, 
      maximumMassFlowRate;

   transitionChoice = ip[0];
   allowBidirectionalFlow = ip[1];

   Kv         = rp[0];
   transitionMassFlowRate = rp[1];
   transitionPressureDifference = rp[2];
   maximumMassFlowRate = rp[3];
   loop = 0;
   error = 0;

/*
   If necessary, check values of the following:

   rp[0..3]
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
   _valve = TwoPortValve_new();
   TwoPortValve* valveObj = _valve;

   valveObj->transitionChoice = transitionChoice;
   valveObj->Kv = Kv;
   valveObj->transitionMassFlowRate = transitionMassFlowRate;
   valveObj->transitionPressureDifference = transitionPressureDifference;
   valveObj->maximumMassFlowRate = maximumMassFlowRate;
   valveObj->allowBidirectionalFlow = allowBidirectionalFlow - 1; //0 - No;  1 - Yes
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

/*  There are 3 ports.

   Port 1 has 2 variables:

      1 flowIndex1      flow index 1  [smoFFL] basic variable output  UNPLOTTABLE
      2 stateIndex1     state index 1 [smoTDS] basic variable input  UNPLOTTABLE

   Port 2 has 1 variable:

      1 regulatingSignal     regulating signal [null] basic variable input

   Port 3 has 2 variables:

      1 flowIndex3      flow index 3 [smoFFL] basic variable output  UNPLOTTABLE
      2 stateIndex3     state index3 [smoTDS] basic variable input  UNPLOTTABLE
*/

/*  There are 3 internal variables.

      1 massFlowRate         mass flow rate      [kg/s]        basic variable
      2 enthalpyFlowRate     enthalpy flow rate  [W]           basic variable
      3 pressureLoss         total pressure loss [barA -> PaA] basic variable
*/

void smo_valve_2port_regulating_signal_(int *n, double *flowIndex1
      , double *stateIndex1, double *regulatingSignal
      , double *flowIndex3, double *stateIndex3, double *massFlowRate
      , double *enthalpyFlowRate, double *pressureLoss, double rp[4]
      , int ip[2], int ic[5], void *ps[5], int *flag)

{
   int loop, logi;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   int transitionChoice, allowBidirectionalFlow;
   double Kv, transitionMassFlowRate, transitionPressureDifference, 
      maximumMassFlowRate;

   transitionChoice = ip[0];
   allowBidirectionalFlow = ip[1];

   Kv         = rp[0];
   transitionMassFlowRate = rp[1];
   transitionPressureDifference = rp[2];
   maximumMassFlowRate = rp[3];
   logi = 0;
   loop = 0;

/* Common -> SI units conversions. */

/*   *stateIndex1 *= ??; CONVERSION UNKNOWN */
/*   *stateIndex3 *= ??; CONVERSION UNKNOWN */

/*
   Set all submodel outputs below:

   *flowIndex1 = ??;
   *flowIndex3 = ??;
   *massFlowRate = ??;
   *enthalpyFlowRate = ??;
   *pressureLoss = ??;
*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
   // Initialization at first run
   if (firstc_()) {
	   _fluidFlow1 = (void*) FluidFlow_new();
	   _fluidFlowIndex1 = FluidFlow_register(_fluidFlow1);

	   _fluidFlow3 = (void*) FluidFlow_new();
	   _fluidFlowIndex3 = FluidFlow_register(_fluidFlow3);

	   _fluidStateIndex1 = *stateIndex1;
	   _fluidState1 = MediumState_get(_fluidStateIndex1);

	   _fluidStateIndex3 = *stateIndex3;
	   _fluidState3 = MediumState_get(_fluidStateIndex3);

	   int mediumIndex1 = Medium_index(MediumState_getMedium(_fluidState1));
	   int mediumIndex3 = Medium_index(MediumState_getMedium(_fluidState3));
	   if (mediumIndex1 != mediumIndex3) {
		   amefprintf(stderr, "\nFatal error in %s instance %d.\n", _SUBMODELNAME_, *n);
		   amefprintf(stderr, "\nThe valve connects two components with different fluid indices: %d and %d.\n", mediumIndex1, mediumIndex3);
		   AmeExit(1);
	   }

	   TwoPortValve_init(_valve, _fluidState1, _fluidState3);
   }

   TwoPortValve_computeMassFlow_Kv(_valve, *regulatingSignal);
   TwoPortValve_computeEnthalpyFlow(_valve);

   // Retrieving the objects from the storage
   TwoPortValve* valveObj = (TwoPortValve*) _valve;

   FluidFlow_setMassFlowRate(_fluidFlow3, valveObj->massFlowRate);
   FluidFlow_setEnthalpyFlowRate(_fluidFlow3, valveObj->enthalpyFlowRate);

   FluidFlow_setMassFlowRate(_fluidFlow1, -valveObj->massFlowRate);
   FluidFlow_setEnthalpyFlowRate(_fluidFlow1, -valveObj->enthalpyFlowRate);

   *massFlowRate = fabs(valveObj->massFlowRate);
   *enthalpyFlowRate = fabs(valveObj->enthalpyFlowRate);
   *pressureLoss = fabs(MediumState_p(_fluidState1) - MediumState_p(_fluidState3));

   *flowIndex1 = _fluidFlowIndex1;
   *flowIndex3 = _fluidFlowIndex3;
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *flowIndex1 /= ??; CONVERSION UNKNOWN */
/*   *stateIndex1 /= ??; CONVERSION UNKNOWN */
/*   *flowIndex3 /= ??; CONVERSION UNKNOWN */
/*   *stateIndex3 /= ??; CONVERSION UNKNOWN */
   *pressureLoss /= 1.00000000000000e+005;
}

