/* Submodel SMO_HEATEXCHANGER_CR skeleton created by AME Submodel editing utility
   Wed Aug 21 16:22:50 2013 */



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

#define _SUBMODELNAME_ "SMO_HEATEXCHANGER_CR"

/* >>>>>>>>>>>>Insert Private Code Here. */
#include "media/MediumState.h"
#include "flow/FlowBase.h"
#include "volumes/ThermalNode.h"

#define _fluidFlowIndexInlet ic[0]
#define _fluidFlowInlet ps[0]

#define _fluidFlowIndexOutlet ic[1]
#define _fluidFlowOutlet ps[1]

#define _fluidStateIndexInlet ic[2]
#define _fluidStateInlet ps[2]

#define _fluidStateIndexOutlet ic[3]
#define _fluidStateOutlet ps[3]

#define _thermalNodeIndex ic[4]
#define _thermalNode ps[4]

#define _heatFlowIndex ic[5]
#define _heatFlow ps[5]
#define _actualFluidStateInlet ps[6]
/* <<<<<<<<<<<<End of Private Code. */


/* There is 1 real parameter:

   efficienccy heat exchanger efficiency [null]
*/

void smo_heatexchanger_crin_(int *n, double rp[1], int ic[6]
      , void *ps[7])

{
   int loop, error;
/* >>>>>>>>>>>>Extra Initialization Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Initialization declarations. */
   double efficienccy;

   efficienccy = rp[0];
   loop = 0;
   error = 0;

/*
   If necessary, check values of the following:

   rp[0..0]
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

/*  There are 3 ports.

   Port 1 has 2 variables:

      1 stateIndexInlet     state index inlet [smoTDS] multi line macro 'smo_heatexchanger_cr_macro0_'  UNPLOTTABLE
      2 flowIndexInlet      flow index inlet  [smoFFL] basic variable input  UNPLOTTABLE

   Port 2 has 2 variables:

      1 heatFlowIndex        heat flow index    [smoHFL] basic variable output  UNPLOTTABLE
      2 thermalNodeIndex     thermal node index [smoTHN] basic variable input  UNPLOTTABLE

   Port 3 has 2 variables:

      1 flowIndexOutlet      flow index outlet  [smoFFL] basic variable output  UNPLOTTABLE
      2 stateIndexOutlet     state index outlet [smoTDS] basic variable input  UNPLOTTABLE
*/

/*  There are 5 internal variables.

      1 inletTemperature      inlet temperature       [K]    basic variable
      2 outletTemperature     outlet temperature      [K]    basic variable
      3 wallTemperature       temperature of the wall [K]    basic variable
      4 wallHeatFlowRate      heat flow rate at wall  [W]    basic variable
      5 massFlowRateInlet     mass flow rate at inlet [kg/s] basic variable
*/

void smo_heatexchanger_cr_(int *n, double *stateIndexInlet
      , double *flowIndexInlet, double *heatFlowIndex
      , double *thermalNodeIndex, double *flowIndexOutlet
      , double *stateIndexOutlet, double *inletTemperature
      , double *outletTemperature, double *wallTemperature
      , double *wallHeatFlowRate, double *massFlowRateInlet
      , double rp[1], int ic[6], void *ps[7], int *flag)

{
   int loop, logi;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
   double T2;
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   double efficienccy;

   efficienccy = rp[0];
   logi = 0;
   loop = 0;

/* Common -> SI units conversions. */

/*   *stateIndexInlet *= ??; CONVERSION UNKNOWN */
/*   *flowIndexInlet *= ??; CONVERSION UNKNOWN */
/*   *thermalNodeIndex *= ??; CONVERSION UNKNOWN */
/*   *stateIndexOutlet *= ??; CONVERSION UNKNOWN */

/*
   Set all submodel outputs below:

   *heatFlowIndex = ??;
   *flowIndexOutlet = ??;
   *inletTemperature = ??;
   *outletTemperature = ??;
   *wallTemperature = ??;
   *wallHeatFlowRate = ??;
   *massFlowRateInlet = ??;
*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
   // Initialization at first run
   if (firstc_()) {
	   _fluidFlowInlet = FluidFlow_get(*flowIndexInlet);
	   _fluidFlowIndexInlet = *flowIndexInlet;

	   _fluidFlowOutlet = FluidFlow_new();
	   _fluidFlowIndexOutlet = FluidFlow_register(_fluidFlowOutlet);

	   _thermalNode = ThermalNode_get(*thermalNodeIndex);
	   _thermalNodeIndex = *thermalNodeIndex;

	   _heatFlow = HeatFlow_new();
	   _heatFlowIndex = HeatFlow_register(_heatFlow);
   }

   if (FluidFlow_getMassFlowRate(_fluidFlowInlet) < 0.0) {
	   amefprintf(stderr, "\nFatal error in %s instance %d.\n", _SUBMODELNAME_, *n);
	   amefprintf(stderr, "\nReverse flow encouuntered. Restrict the flow direction, e.g. by adding check valve.");
	   AmeExit(1);
   }

   *wallTemperature = MediumState_T(_thermalNode);
   if (FluidFlow_getMassFlowRate(_fluidFlowInlet) > 1e-8) {
	  double inletSpecificEnthalpy = FluidFlow_getEnthalpyFlowRate(_fluidFlowInlet) / FluidFlow_getMassFlowRate(_fluidFlowInlet);
	  // TODO (Nasko) This should not be so. Different state should be used
	  MediumState_update_ph(_actualFluidStateInlet, MediumState_p(_fluidStateOutlet), inletSpecificEnthalpy);

	  *inletTemperature = MediumState_T(_actualFluidStateInlet);
	  *outletTemperature = *inletTemperature + (*wallTemperature - *inletTemperature) * efficienccy;
	  MediumState_update_Tp(_fluidStateOutlet, *outletTemperature, MediumState_p(_fluidStateOutlet));
   } else {
	   //:TODO: (Nasko) no mass flow rate
   }

   FluidFlow_setMassFlowRate(_fluidFlowOutlet, FluidFlow_getMassFlowRate(_fluidFlowInlet));
   FluidFlow_setEnthalpyFlowRate(_fluidFlowOutlet, MediumState_h(_fluidStateOutlet) * FluidFlow_getMassFlowRate(_fluidFlowInlet));

   HeatFlow_setEnthalpyFlowRate(_heatFlow, FluidFlow_getEnthalpyFlowRate(_fluidFlowInlet) - FluidFlow_getEnthalpyFlowRate(_fluidFlowOutlet));

   *wallHeatFlowRate = HeatFlow_getEnthalpyFlowRate(_heatFlow);
   *massFlowRateInlet = FluidFlow_getMassFlowRate(_fluidFlowInlet);

   *heatFlowIndex = _heatFlowIndex;
   *flowIndexOutlet = _fluidFlowIndexOutlet;
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *stateIndexInlet /= ??; CONVERSION UNKNOWN */
/*   *flowIndexInlet /= ??; CONVERSION UNKNOWN */
/*   *heatFlowIndex /= ??; CONVERSION UNKNOWN */
/*   *thermalNodeIndex /= ??; CONVERSION UNKNOWN */
/*   *flowIndexOutlet /= ??; CONVERSION UNKNOWN */
/*   *stateIndexOutlet /= ??; CONVERSION UNKNOWN */
}

extern double smo_heatexchanger_cr_macro0_(int *n
      , double *stateIndexOutlet, double rp[1], int ic[6], void *ps[7]
      , int *flag)

{
   double stateIndexInlet;
   int loop, logi;
/* >>>>>>>>>>>>Extra Macro Function macro0 Declarations Here. */
/* <<<<<<<<<<<<End of Extra Macro macro0 declarations. */
   double efficienccy;

   efficienccy = rp[0];
   logi = 0;
   loop = 0;

/* Common -> SI units conversions. */

/*   *stateIndexOutlet *= ??; CONVERSION UNKNOWN */

/*
   Define and return the following macro variable:

   stateIndexInlet = ??;
*/


/* >>>>>>>>>>>>Macro Function macro0 Executable Statements. */
   if (firstc_()) {
  	   _fluidStateIndexOutlet = *stateIndexOutlet;
  	   _fluidStateOutlet = MediumState_get(_fluidStateIndexOutlet);

  	   int mediumIndexOutlet = Medium_index(MediumState_getMedium(_fluidStateOutlet));

  	   Medium* fluid = Medium_get(mediumIndexOutlet);
  	   _fluidStateInlet = MediumState_new(fluid);
  	   _fluidStateIndexInlet = MediumState_register(_fluidStateInlet);

  	   _actualFluidStateInlet = MediumState_new(fluid);
  	   MediumState_register(_actualFluidStateInlet);
   }

   MediumState_update_ph(_fluidStateInlet, MediumState_p(_fluidStateOutlet), MediumState_h(_fluidStateOutlet));

   stateIndexInlet = _fluidStateIndexInlet;
/* <<<<<<<<<<<<End of Macro macro0 Executable Statements. */

/* SI -> Common units conversions. */

/*   *stateIndexOutlet /= ??; CONVERSION UNKNOWN */

/*   *stateIndexInlet /= ??; CONVERSION UNKNOWN */

   return stateIndexInlet;
}

