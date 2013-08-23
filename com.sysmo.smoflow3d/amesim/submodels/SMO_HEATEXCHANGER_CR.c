/* Submodel SMO_HEATEXCHANGER_CR skeleton created by AME Submodel editing utility
   Fri Aug 23 15:54:38 2013 */



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

#define _fluidStateIndexOutlet ic[2]
#define _fluidStateOutlet ps[2]

#define _thermalNodeIndex ic[3]
#define _thermalNode ps[3]

#define _heatFlowIndex ic[4]
#define _heatFlow ps[4]

#define _fluidStateOutletInternal ps[5]
#define _fluidStateInletInternal ps[6]
/* <<<<<<<<<<<<End of Private Code. */


/* There is 1 real parameter:

   efficienccy heat exchanger efficiency [null]
*/

void smo_heatexchanger_crin_(int *n, double rp[1], int ic[5]
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

      1 stateIndexOutletDup     duplicate of stateIndexOutlet
      2 flowIndexInlet          flow index inlet   [smoFFL] basic variable input  UNPLOTTABLE

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

void smo_heatexchanger_cr_(int *n, double *flowIndexInlet
      , double *heatFlowIndex, double *thermalNodeIndex
      , double *flowIndexOutlet, double *stateIndexOutlet
      , double *inletTemperature, double *outletTemperature
      , double *wallTemperature, double *wallHeatFlowRate
      , double *massFlowRateInlet, double rp[1], int ic[5]
      , void *ps[7], int *flag)

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
  	   _fluidStateIndexOutlet = *stateIndexOutlet;
  	   _fluidStateOutlet = MediumState_get(_fluidStateIndexOutlet);

  	   int mediumIndexOutlet = Medium_index(MediumState_getMedium(_fluidStateOutlet));
  	   Medium* fluid = Medium_get(mediumIndexOutlet);

  	   _fluidStateOutletInternal = MediumState_new(fluid);
  	   MediumState_register(_fluidStateOutletInternal);

  	   _fluidStateInletInternal = MediumState_new(fluid);
  	   MediumState_register(_fluidStateInletInternal);


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
	  MediumState_update_ph(_fluidStateInletInternal, MediumState_p(_fluidStateOutlet), inletSpecificEnthalpy);

	  *inletTemperature = MediumState_T(_fluidStateInletInternal);
	  *outletTemperature = *inletTemperature + (*wallTemperature - *inletTemperature) * efficienccy;

	  MediumState_update_Tp(_fluidStateOutletInternal, *outletTemperature, MediumState_p(_fluidStateOutlet));

	  FluidFlow_setMassFlowRate(_fluidFlowOutlet, FluidFlow_getMassFlowRate(_fluidFlowInlet));
	  FluidFlow_setEnthalpyFlowRate(_fluidFlowOutlet, MediumState_h(_fluidStateOutletInternal) * FluidFlow_getMassFlowRate(_fluidFlowInlet));

	  HeatFlow_setEnthalpyFlowRate(_heatFlow, FluidFlow_getEnthalpyFlowRate(_fluidFlowInlet) - FluidFlow_getEnthalpyFlowRate(_fluidFlowOutlet));
   } else {
	   *outletTemperature = 0.0;

	   FluidFlow_setMassFlowRate(_fluidFlowOutlet, 0.0);
	   FluidFlow_setEnthalpyFlowRate(_fluidFlowOutlet, 0.0);

	   HeatFlow_setEnthalpyFlowRate(_heatFlow, 0.0);
   }


   *wallHeatFlowRate = HeatFlow_getEnthalpyFlowRate(_heatFlow);
   *massFlowRateInlet = FluidFlow_getMassFlowRate(_fluidFlowInlet);

   *heatFlowIndex = _heatFlowIndex;
   *flowIndexOutlet = _fluidFlowIndexOutlet;
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *flowIndexInlet /= ??; CONVERSION UNKNOWN */
/*   *heatFlowIndex /= ??; CONVERSION UNKNOWN */
/*   *thermalNodeIndex /= ??; CONVERSION UNKNOWN */
/*   *flowIndexOutlet /= ??; CONVERSION UNKNOWN */
/*   *stateIndexOutlet /= ??; CONVERSION UNKNOWN */
}

