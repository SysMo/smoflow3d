/* Submodel SMO_VALVE_2PORT_REGULATING_SIGNAL skeleton created by AME Submodel editing utility
   Sun Jul 28 10:43:06 2013 */



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
/*
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


/* There are 3 integer parameters:

   fluidIndex             index of fluid                       
   transitionChoice       choice of transition to linear region
   allowBidirectionalFlow Allow bi-directional flow            
*/

void smo_valve_2port_regulating_signalin_(int *n, double rp[4]
      , int ip[3], void *ps[10])

{
   int loop, error;
/* >>>>>>>>>>>>Extra Initialization Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Initialization declarations. */
   int fluidIndex, transitionChoice, allowBidirectionalFlow;
   double Kv, transitionMassFlowRate, transitionPressureDifference, 
      maximumMassFlowRate;

   fluidIndex = ip[0];
   transitionChoice = ip[1];
   allowBidirectionalFlow = ip[2];

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

   if (fluidIndex < 1 || fluidIndex > 99)
   {
      amefprintf(stderr, "\nindex of fluid must be in range [1..99].\n");
      error = 2;
   }
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
/*	AME_SET_CURRENT_COMPONENT;

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

   Port 1 has 5 variables:

      1 port1EnthalpyFlowRate     duplicate of port3EnthalpyFlowRate (sign reversed)
      2 port1MassFlowRate         duplicate of port3MassFlowRate (sign reversed)
      3 port1Pressure             pressure at port1            [barA -> PaA] basic variable input
      4 port1Density              density at port1             [kg/m**3]     basic variable input  UNPLOTTABLE
      5 port1ComIndex             communication index at port1 [null]        basic variable input  UNPLOTTABLE

   Port 2 has 1 variable:

      1 regulatingSignal     regulating signal [null] basic variable input

   Port 3 has 5 variables:

      1 port3EnthalpyFlowRate     enthalpy flow rate at port 3  [W]           basic variable output
      2 port3MassFlowRate         mass flow rate at port 3      [kg/s]        basic variable output
      3 port3Pressure             pressure at port 3            [barA -> PaA] basic variable input
      4 port3Density              density at port 3             [kg/m**3]     basic variable input  UNPLOTTABLE
      5 port3ComIndex             communication index at port 3 [null]        basic variable input  UNPLOTTABLE
*/

/*  There are 2 internal variables.

      1 pressureLoss         total pressure loss      [barA -> PaA] basic variable
      2 port1Temperature     fluid temperature port 1 [K]           basic variable
*/

void smo_valve_2port_regulating_signal_(int *n, double *port1Pressure
      , double *port1Density, double *port1ComIndex
      , double *regulatingSignal, double *port3EnthalpyFlowRate
      , double *port3MassFlowRate, double *port3Pressure
      , double *port3Density, double *port3ComIndex
      , double *pressureLoss, double *port1Temperature, double rp[4]
      , int ip[3], void *ps[10], int *flag)

{
   int loop, logi;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   int fluidIndex, transitionChoice, allowBidirectionalFlow;
   double Kv, transitionMassFlowRate, transitionPressureDifference, 
      maximumMassFlowRate;

   fluidIndex = ip[0];
   transitionChoice = ip[1];
   allowBidirectionalFlow = ip[2];

   Kv         = rp[0];
   transitionMassFlowRate = rp[1];
   transitionPressureDifference = rp[2];
   maximumMassFlowRate = rp[3];
   logi = 0;
   loop = 0;

/* Common -> SI units conversions. */

   *port1Pressure *= 1.00000000000000e+005;
   *port3Pressure *= 1.00000000000000e+005;

/*
   Set all submodel outputs below:

   *port3EnthalpyFlowRate = ??;
   *port3MassFlowRate = ??;
   *pressureLoss = ??;
   *port1Temperature = ??;
*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
/*
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

   *port1Pressure /= 1.00000000000000e+005;
   *port3Pressure /= 1.00000000000000e+005;
   *pressureLoss /= 1.00000000000000e+005;
}

