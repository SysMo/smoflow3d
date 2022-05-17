/* Submodel SMO_FLUID_FLOW_SPLITTER_3PORT_01 skeleton created by AME Submodel editing utility
   Sun Mar 23 10:13:21 2014 */



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

#define _SUBMODELNAME_ "SMO_FLUID_FLOW_SPLITTER_3PORT_01"

/* >>>>>>>>>>>>Insert Private Code Here. */
#include "flow/FlowBase.h"

#define _fluidFlowOutIndex ic[0]
#define _fluidFlowOut ps[0]
/* <<<<<<<<<<<<End of Private Code. */
void smo_fluid_flow_splitter_3port_01in_(int *n, int ic[1]
      , void *ps[1])

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
   _fluidFlowOut = FluidFlow_new();
   _fluidFlowOutIndex = FluidFlow_register(_fluidFlowOut);
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

/*  There are 3 ports.

   Port 1 has 3 variables:

      1 fluidStateIndexDup1              duplicate of fluidStateIndex        
      2 fluidFlowIndexIn1                fluid flow index in 1                [smoFFL]  basic variable input  UNPLOTTABLE
      3 fluidFlowActivationSignalIn1     fluid flow activation signal (port1) [smoFFAS] basic variable input

   Port 2 has 3 variables:

      1 fluidFlowIndexOut                fluid flow index out                 [smoFFL]  multi line macro 'smo_fluid_flow_splitter_3port_01_macro0_'  UNPLOTTABLE
      2 fluidFlowActivationSignalOut     fluid flow activation signal (port2) [smoFFAS] multi line macro 'smo_fluid_flow_splitter_3port_01_macro1_'
      3 fluidStateIndex                  fluid state index                    [smoTDS]  basic variable input  UNPLOTTABLE

   Port 3 has 3 variables:

      1 fluidStateIndexDup3              duplicate of fluidStateIndex        
      2 fluidFlowIndexIn3                fluid flow index in 3                [smoFFL]  basic variable input  UNPLOTTABLE
      3 fluidFlowActivationSignalIn3     fluid flow activation signal (port3) [smoFFAS] basic variable input
*/

/*  There are 0 internal variables.

*/

#if 0

/* THE CALCULATION FUNCTION WILL NOT BE CALLED. */

void smo_fluid_flow_splitter_3port_01_(int *n
      , double *fluidFlowIndexIn1
      , double *fluidFlowActivationSignalIn1
      , double *fluidFlowIndexOut
      , double *fluidFlowActivationSignalOut, double *fluidStateIndex
      , double *fluidFlowIndexIn3
      , double *fluidFlowActivationSignalIn3, int ic[1], void *ps[1])

{
   int loop;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   loop = 0;

/* Common -> SI units conversions. */

/*   *fluidFlowIndexIn1 *= ??; CONVERSION UNKNOWN */
/*   *fluidFlowActivationSignalIn1 *= ??; CONVERSION UNKNOWN */
/*   *fluidFlowIndexOut *= ??; CONVERSION UNKNOWN */
/*   *fluidFlowActivationSignalOut *= ??; CONVERSION UNKNOWN */
/*   *fluidStateIndex *= ??; CONVERSION UNKNOWN */
/*   *fluidFlowIndexIn3 *= ??; CONVERSION UNKNOWN */
/*   *fluidFlowActivationSignalIn3 *= ??; CONVERSION UNKNOWN */

/*
   Set all submodel outputs below:

*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *fluidFlowIndexIn1 /= ??; CONVERSION UNKNOWN */
/*   *fluidFlowActivationSignalIn1 /= ??; CONVERSION UNKNOWN */
/*   *fluidFlowIndexOut /= ??; CONVERSION UNKNOWN */
/*   *fluidFlowActivationSignalOut /= ??; CONVERSION UNKNOWN */
/*   *fluidStateIndex /= ??; CONVERSION UNKNOWN */
/*   *fluidFlowIndexIn3 /= ??; CONVERSION UNKNOWN */
/*   *fluidFlowActivationSignalIn3 /= ??; CONVERSION UNKNOWN */
}

#endif
extern double smo_fluid_flow_splitter_3port_01_macro0_(int *n
      , double *fluidFlowIndexIn1, double *fluidFlowIndexIn3
      , int ic[1], void *ps[1])

{
   double fluidFlowIndexOut;
   int loop;
/* >>>>>>>>>>>>Extra Macro Function macro0 Declarations Here. */
/* <<<<<<<<<<<<End of Extra Macro macro0 declarations. */
   loop = 0;

/* Common -> SI units conversions. */

/*   *fluidFlowIndexIn1 *= ??; CONVERSION UNKNOWN */
/*   *fluidFlowIndexIn3 *= ??; CONVERSION UNKNOWN */

/*
   Define and return the following macro variable:

   fluidFlowIndexOut = ??;
*/


/* >>>>>>>>>>>>Macro Function macro0 Executable Statements. */
   FluidFlow* flowIn1 = FluidFlow_get(*fluidFlowIndexIn1);
   FluidFlow* flowIn3 = FluidFlow_get(*fluidFlowIndexIn3);

   double netMassFlowIn = FluidFlow_getMassFlowRate(flowIn1) + FluidFlow_getMassFlowRate(flowIn3);
   double netEnthalpyFlowIn = FluidFlow_getEnthalpyFlowRate(flowIn1) + FluidFlow_getEnthalpyFlowRate(flowIn3);
   double netVolumeIn = FluidFlow_getVolume(flowIn1) + FluidFlow_getVolume(flowIn3);
   double netVolumeDotIn = FluidFlow_getVolumeDot(flowIn1) + FluidFlow_getVolumeDot(flowIn3);
   FluidFlow_setMassFlowRate(_fluidFlowOut, netMassFlowIn);
   FluidFlow_setEnthalpyFlowRate(_fluidFlowOut, netEnthalpyFlowIn);
   FluidFlow_setVolume(_fluidFlowOut, netVolumeIn);
   FluidFlow_setVolumeDot(_fluidFlowOut, netVolumeDotIn);

   fluidFlowIndexOut = _fluidFlowOutIndex;
/* <<<<<<<<<<<<End of Macro macro0 Executable Statements. */

/* SI -> Common units conversions. */

/*   *fluidFlowIndexIn1 /= ??; CONVERSION UNKNOWN */
/*   *fluidFlowIndexIn3 /= ??; CONVERSION UNKNOWN */

/*   *fluidFlowIndexOut /= ??; CONVERSION UNKNOWN */

   return fluidFlowIndexOut;
}

extern double smo_fluid_flow_splitter_3port_01_macro1_(int *n
      , double *fluidFlowActivationSignalIn1
      , double *fluidFlowActivationSignalIn3, int ic[1], void *ps[1])

{
   double fluidFlowActivationSignalOut;
   int loop;
/* >>>>>>>>>>>>Extra Macro Function macro1 Declarations Here. */
/* <<<<<<<<<<<<End of Extra Macro macro1 declarations. */
   loop = 0;

/* Common -> SI units conversions. */

/*   *fluidFlowActivationSignalIn1 *= ??; CONVERSION UNKNOWN */
/*   *fluidFlowActivationSignalIn3 *= ??; CONVERSION UNKNOWN */

/*
   Define and return the following macro variable:

   fluidFlowActivationSignalOut = ??;
*/


/* >>>>>>>>>>>>Macro Function macro1 Executable Statements. */
   if (*fluidFlowActivationSignalIn1 == 1 || *fluidFlowActivationSignalIn3 == 1) {
	   fluidFlowActivationSignalOut = 1; //activate flow
   } else if (*fluidFlowActivationSignalIn1 == -1 || *fluidFlowActivationSignalIn3 == -1) {
	   fluidFlowActivationSignalOut = -1; //not used
   } else {
	   fluidFlowActivationSignalOut = 0; //deactivate flow
   }
/* <<<<<<<<<<<<End of Macro macro1 Executable Statements. */

/* SI -> Common units conversions. */

/*   *fluidFlowActivationSignalIn1 /= ??; CONVERSION UNKNOWN */
/*   *fluidFlowActivationSignalIn3 /= ??; CONVERSION UNKNOWN */

/*   *fluidFlowActivationSignalOut /= ??; CONVERSION UNKNOWN */

   return fluidFlowActivationSignalOut;
}

