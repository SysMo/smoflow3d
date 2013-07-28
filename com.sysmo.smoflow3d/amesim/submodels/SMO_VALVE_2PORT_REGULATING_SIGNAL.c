/* Submodel SMO_VALVE_2PORT_REGULATING_SIGNAL skeleton created by AME Submodel editing utility
   Sun Jul 28 10:50:23 2013 */



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
/* :DELME:
#include "FluidPoint.h"
#include "Valve.h"
#define NODE1 ps[0]
#define NODE2 ps[1]
#define VALVE ps[2]
*/
/* <<<<<<<<<<<<End of Private Code. */


/* There are 4 real parameters:

   Kv                           Flow coefficient Kv            [null]
   transitionMassFlowRate       transition mass flow rate      [kg/s]
   transitionPressureDifference transition pressure difference [bar -> Pa]
   maximumMassFlowRate          maximum mass flow              [kg/s]
*/


/* There are 2 integer parameters:

   transitionChoice       choice of transition to linear region
   allowBidirectionalFlow Allow bi-directional flow            
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
      amefprintf(stderr, "\nAllow bi-directional flow must be in range [1..2].\n");
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
/* :DELME:
 	AME_SET_CURRENT_COMPONENT;

	VALVE = TwoPortValve_new();
	NODE1 = FluidPoint_new(fluidIndex);
	NODE2 = FluidPoint_new(fluidIndex);

	TwoPortValve *valve = VALVE;
	valve->transitionChoice = transitionChoice;
	valve->Kv = Kv;
	valve->transitionMassFlowRate = transitionMassFlowRate;
	valve->transitionPressureDifference = transitionPressureDifference;
	valve->maximumMassFlowRate = maximumMassFlowRate;
	valve->allowedFlowDirection = 2 - allowBidirectionalFlow;*/
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
      2 enthalpzFlowRate     enthalpy flow rate  [W]           basic variable
      3 pressureLoss         total pressure loss [barA -> PaA] basic variable
*/

void smo_valve_2port_regulating_signal_(int *n, double *flowIndex1
      , double *stateIndex1, double *regulatingSignal
      , double *flowIndex3, double *stateIndex3, double *massFlowRate
      , double *enthalpzFlowRate, double *pressureLoss, double rp[4]
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
   *enthalpzFlowRate = ??;
   *pressureLoss = ??;
*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
/* :DELME:
   // Initialization at first run
   if (firstc_()) {
	   FluidPoint_init(NODE1, (int)(*port1ComIndex), -1);
	   FluidPoint_init(NODE2, (int)(*port3ComIndex), -1);
	   TwoPortValve_init(VALVE, NODE1, NODE2);
   }
   // Retrieving the objects from the storage
   TwoPortValve* valve = (TwoPortValve*) VALVE;

   // Setting object inputs
   FluidPoint_computeState_p_rho(NODE1, *port1Pressure, *port1Density);
   FluidPoint_computeState_p_rho(NODE2, *port3Pressure, *port3Density);
   TwoPortValve_computeMassFlow_Kv(valve, *regulatingSignal);
   TwoPortValve_computeEnthalpyFlow(valve);
   *port3MassFlowRate = valve->massFlowRate;
   *port3EnthalpyFlowRate = valve->enthalpyFlowRate;
   *pressureLoss = valve->pressureDrop;
   //:TODO: (Nasko) set port1Temperature
*/
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *flowIndex1 /= ??; CONVERSION UNKNOWN */
/*   *stateIndex1 /= ??; CONVERSION UNKNOWN */
/*   *flowIndex3 /= ??; CONVERSION UNKNOWN */
/*   *stateIndex3 /= ??; CONVERSION UNKNOWN */
   *pressureLoss /= 1.00000000000000e+005;
}

