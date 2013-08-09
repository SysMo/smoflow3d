/* Submodel SMO_TEMPERATURE_SOURCE skeleton created by AME Submodel editing utility
   Thu Aug 8 17:17:54 2013 */



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

#define _SUBMODELNAME_ "SMO_TEMPERATURE_SOURCE"

/* >>>>>>>>>>>>Insert Private Code Here. */
#include "volumes/ThermalNode.h"

#define _thermalNode ps[0]
#define _thermalNodeIndex ic[0]
/* <<<<<<<<<<<<End of Private Code. */
void smo_temperature_sourcein_(int *n, int ic[2], void *ps[2])

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
   _thermalNode = ThermalNode_new(sThermalNode_Source);
   _thermalNodeIndex = ThermalNode_register(_thermalNode);
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

/*  There are 2 ports.

   Port 1 has 1 variable:

      1 temperatureSignal     input temperature signal [K] basic variable input

   Port 2 has 2 variables:

      1 thermalNodeIndex     thermal node index [smoTHN] multi line macro 'smo_temperature_source_macro0_'  UNPLOTTABLE
      2 heatFlowIndex        heat flow index    [smoHFL] basic variable input
*/

/*  There are 0 internal variables.

*/

#if 0

/* THE CALCULATION FUNCTION WILL NOT BE CALLED. */

void smo_temperature_source_(int *n, double *temperatureSignal
      , double *thermalNodeIndex, double *heatFlowIndex, int ic[2]
      , void *ps[2])

{
   int loop;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   loop = 0;

/* Common -> SI units conversions. */

/*   *thermalNodeIndex *= ??; CONVERSION UNKNOWN */
/*   *heatFlowIndex *= ??; CONVERSION UNKNOWN */

/*
   Set all submodel outputs below:

*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *thermalNodeIndex /= ??; CONVERSION UNKNOWN */
/*   *heatFlowIndex /= ??; CONVERSION UNKNOWN */
}

#endif
extern double smo_temperature_source_macro0_(int *n
      , double *temperatureSignal, int ic[2], void *ps[2])

{
   double thermalNodeIndex;
   int loop;
/* >>>>>>>>>>>>Extra Macro Function macro0 Declarations Here. */
   ThermalNode_setTemperature(_thermalNode, *temperatureSignal);
   thermalNodeIndex = _thermalNodeIndex;
/* <<<<<<<<<<<<End of Extra Macro macro0 declarations. */
   loop = 0;

/*
   Define and return the following macro variable:

   thermalNodeIndex = ??;
*/


/* >>>>>>>>>>>>Macro Function macro0 Executable Statements. */
/* <<<<<<<<<<<<End of Macro macro0 Executable Statements. */

/*   *thermalNodeIndex /= ??; CONVERSION UNKNOWN */

   return thermalNodeIndex;
}

