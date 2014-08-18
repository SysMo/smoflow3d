/* Submodel SMO_ADAPTOR_FLUID_HEAT skeleton created by AME Submodel editing utility
   Thu Sep 19 17:09:57 2013 */



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

#define _SUBMODELNAME_ "SMO_ADAPTOR_FLUID_HEAT"

/* >>>>>>>>>>>>Insert Private Code Here. */
#include "media/MediumState.h"
#include "flow/FlowBase.h"
#include "volumes/ThermalNode.h"

#define _thermalNode ps[0]
#define _thermalNodeIndex ic[0]

#define _heatFlowIndex ic[1]
#define _heatFlow ps[1]

#define _fluidStateIndex ic[2]
#define _fluidState ps[2]

#define _fluidFlowIndex ic[3]
#define _fluidFlow ps[3]
/* <<<<<<<<<<<<End of Private Code. */
void smo_adaptor_fluid_heatin_(int *n, int ic[4], void *ps[4])

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
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

/*  There are 2 ports.

   Port 1 has 2 variables:

      1 thermalNodeIndex     thermal node index [smoTHN] multi line macro 'smo_adaptor_fluid_heat_macro0_'  UNPLOTTABLE
      2 heatFlowIndex        heat flow index    [smoHFL] basic variable input  UNPLOTTABLE

   Port 2 has 2 variables:

      1 fluidFlowIndex      fluid flow index  [smoFFL] basic variable output  UNPLOTTABLE
      2 fluidStateIndex     fluid state index [smoTDS] basic variable input  UNPLOTTABLE
*/

/*  There are 0 internal variables.

*/

void smo_adaptor_fluid_heat_(int *n, double *thermalNodeIndex
      , double *heatFlowIndex, double *fluidFlowIndex
      , double *fluidStateIndex, int ic[4], void *ps[4])

{
   int loop;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   loop = 0;

/* Common -> SI units conversions. */

/*   *thermalNodeIndex *= ??; CONVERSION UNKNOWN */
/*   *heatFlowIndex *= ??; CONVERSION UNKNOWN */
/*   *fluidStateIndex *= ??; CONVERSION UNKNOWN */

/*
   Set all submodel outputs below:

   *fluidFlowIndex = ??;
*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
   if (firstc_()) {
	   _heatFlowIndex = *heatFlowIndex;
	   _heatFlow = HeatFlow_get(_heatFlowIndex);

	   _fluidFlow = FluidFlow_new();
	   _fluidFlowIndex = FluidFlow_register(_fluidFlow);
   }

   FluidFlow_setMassFlowRate(_fluidFlow, 0.0);
   FluidFlow_setEnthalpyFlowRate(_fluidFlow, HeatFlow_getEnthalpyFlowRate(_heatFlow));

   *fluidFlowIndex = _fluidFlowIndex;
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *thermalNodeIndex /= ??; CONVERSION UNKNOWN */
/*   *heatFlowIndex /= ??; CONVERSION UNKNOWN */
/*   *fluidFlowIndex /= ??; CONVERSION UNKNOWN */
/*   *fluidStateIndex /= ??; CONVERSION UNKNOWN */
}

extern double smo_adaptor_fluid_heat_macro0_(int *n
      , double *fluidStateIndex, int ic[4], void *ps[4])

{
   double thermalNodeIndex;
   int loop;
/* >>>>>>>>>>>>Extra Macro Function macro0 Declarations Here. */
/* <<<<<<<<<<<<End of Extra Macro macro0 declarations. */
   loop = 0;

/* Common -> SI units conversions. */

/*   *fluidStateIndex *= ??; CONVERSION UNKNOWN */

/*
   Define and return the following macro variable:

   thermalNodeIndex = ??;
*/


/* >>>>>>>>>>>>Macro Function macro0 Executable Statements. */
   if (firstc_()) {
	   _thermalNode = ThermalNode_new(sThermalNode_Source);
	   _thermalNodeIndex = ThermalNode_register(_thermalNode);

	   _fluidStateIndex = *fluidStateIndex;
	   _fluidState = MediumState_get(_fluidStateIndex);
   }

   ThermalNode_setTemperature(_thermalNode, MediumState_T(_fluidState));
   thermalNodeIndex = _thermalNodeIndex;
/* <<<<<<<<<<<<End of Macro macro0 Executable Statements. */

/* SI -> Common units conversions. */

/*   *fluidStateIndex /= ??; CONVERSION UNKNOWN */

/*   *thermalNodeIndex /= ??; CONVERSION UNKNOWN */

   return thermalNodeIndex;
}

