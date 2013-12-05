/* Submodel SMO_FLUID_FLOW_ACTIVATION_SIGNAL_DEACTIVATOR_RC skeleton created by AME Submodel editing utility
   Thu Dec 5 11:47:25 2013 */



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

#define _SUBMODELNAME_ "SMO_FLUID_FLOW_ACTIVATION_SIGNAL_DEACTIVATOR_RC"

/* >>>>>>>>>>>>Insert Private Code Here. */
#include "SmoFlowAme.h"
#include "volumes/PipeHeatExchPrDropMassAcc_RC.h"

#define _port1FluidFlow ps[0]
#define _port1FluidFlowIndex ic[0]

#define _port3FluidState ps[1]
#define _port3FluidStateIndex ic[1]

#define _wallHeatFlow ps[2]
#define _wallHeatFlowIndex ic[2]

#define _port1FluidState ps[3]
#define _friction ps[4]
#define _convection ps[5]
#define _component ps[6]
/* <<<<<<<<<<<<End of Private Code. */
void smo_fluid_flow_activation_signal_deactivator_rcin_(int *n
      , double *fluidFlowActivationSignal1)

{
   int loop, error;
/* >>>>>>>>>>>>Extra Initialization Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Initialization declarations. */
   loop = 0;
   error = 0;

/*
   Check and/or reset the following fixed and/or discrete variable

   *fluidFlowActivationSignal1 = ??;
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
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

/*  There are 2 ports.

   Port 1 has 3 variables:

      1 fluidFlowIndexDup              duplicate of fluidFlowIndex         
      2 fluidFlowActivationSignal1     fluid flow activation signal (port1) [smoFFAS] fixed
      3 fluidStateIndex                fluid state index                    [smoTDS]  basic variable input  UNPLOTTABLE

   Port 2 has 3 variables:

      1 fluidStateIndexDup             duplicate of fluidStateIndex         
      2 fluidFlowIndex                 fluid flow index                      [smoFFL]  basic variable input  UNPLOTTABLE
      3 fluidFlowActivationSignal2     fluid flow activation signal (port 2) [smoFFAS] basic variable input
*/

/*  There are 0 internal variables.

*/

void smo_fluid_flow_activation_signal_deactivator_rc_(int *n
      , double *fluidStateIndex, double *fluidFlowIndex
      , double *fluidFlowActivationSignal2)

{
   int loop;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   loop = 0;

/* Common -> SI units conversions. */

/*   *fluidStateIndex *= ??; CONVERSION UNKNOWN */
/*   *fluidFlowIndex *= ??; CONVERSION UNKNOWN */
/*   *fluidFlowActivationSignal2 *= ??; CONVERSION UNKNOWN */

/*
   Set all submodel outputs below:

*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
   SMOCOMPONENT_PRINT_MAIN_CALC
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *fluidStateIndex /= ??; CONVERSION UNKNOWN */
/*   *fluidFlowIndex /= ??; CONVERSION UNKNOWN */
/*   *fluidFlowActivationSignal2 /= ??; CONVERSION UNKNOWN */
}

