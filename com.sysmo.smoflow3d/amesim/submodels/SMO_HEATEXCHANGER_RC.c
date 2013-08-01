/* Submodel SMO_HEATEXCHANGER_RC skeleton created by AME Submodel editing utility
   Thu Aug 1 10:26:58 2013 */



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

#define _SUBMODELNAME_ "SMO_HEATEXCHANGER_RC"

/* >>>>>>>>>>>>Insert Private Code Here. */
#include "media/MediumState.h"
#include "flow/FluidFlow.h"

#define fluidFlowIndexInlet ic[1]
#define fluidFlowInlet ps[1]

#define fluidFlowIndexOutlet ic[2]
#define fluidFlowOutlet ps[2]

#define fluidStateIndexInlet ic[3]
#define fluidStateInlet ps[3]

#define fluidStateIndexOutlet ic[4]
#define fluidStateOutlet ps[4]

#define heatStateIndex ic[5]
#define heatState ps[5]

#define heatFlowIndex ic[6]
#define heatFlow ps[6]

/* DELME
#include "FluidPoint.h"
#define INLET_NODE ps[0]
#define OUTLET_NODE ps[1]
*/
/* <<<<<<<<<<<<End of Private Code. */


/* There are 3 real parameters:

   initialOutletTemperature initial outlet temperature [K]
   efficienccy              heat exchanger efficiency  [null]
   tauOutput                output time constant       [s]
*/


/* There is 1 integer parameter:

   fluidIndex index of fluid
*/

void smo_heatexchanger_rcin_(int *n, double rp[3], int ip[1]
      , int ic[7], void *ps[7], double *outletTemperature)

{
   int loop, error;
/* >>>>>>>>>>>>Extra Initialization Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Initialization declarations. */
   int fluidIndex;
   double initialOutletTemperature, efficienccy, tauOutput;

   fluidIndex = ip[0];

   initialOutletTemperature = rp[0];
   efficienccy = rp[1];
   tauOutput  = rp[2];
   loop = 0;
   error = 0;

/*
   If necessary, check values of the following:

   rp[0..2]
   *outletTemperature
*/


/* >>>>>>>>>>>>Initialization Function Check Statements. */
/* <<<<<<<<<<<<End of Initialization Check Statements. */

/*   Integer parameter checking:   */

   if (fluidIndex < 1 || fluidIndex > 99)
   {
      amefprintf(stderr, "\nindex of fluid must be in range [1..99].\n");
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


/* >>>>>>>>>>>>Initialization Function Executable Statements. */
   *outletTemperature = initialOutletTemperature;
/* DELME
 	AME_SET_CURRENT_COMPONENT;

	INLET_NODE = FluidPoint_new(fluidIndex);

	OUTLET_NODE = FluidPoint_new(fluidIndex);
	FluidPoint* outletNode = (FluidPoint*) OUTLET_NODE;

	*outletTemperature = initialOutletTemperature;
	outletNode->p = 1e6;
	outletNode->T = initialOutletTemperature;
	FluidPoint_init(outletNode, -1, 2);
	*outletComIndex = outletNode->volumeIndex;*/
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

/*  There are 3 ports.

   Port 1 has 2 variables:

      1 flowIndexInlet      flow index inlet  [smoFFL] basic variable output  UNPLOTTABLE
      2 stateIndexInlet     state index inlet [smoTDS] basic variable input  UNPLOTTABLE

   Port 2 has 2 variables:

      1 flowIndexHeat      heat flow index  [smoFFL] basic variable output  UNPLOTTABLE
      2 stateIndexHeat     heat state index [smoTDS] basic variable input  UNPLOTTABLE

   Port 3 has 2 variables:

      1 stateIndexOutlet     state index outlet [smoTDS] multi line macro 'smo_heatexchanger_rc_macro0_'  UNPLOTTABLE
      2 flowIndexOutlet      flow index outlet  [smoFFL] basic variable input  UNPLOTTABLE
*/

/*  There are 5 internal variables.

      1 inletTemperature       inlet temperature        [K]    basic variable
      2 outletTemperature      outlet temperature       [K]    explicit state (derivative `outletTemperatureDot')
      3 wallTemperature        temperature of the wall  [K]    basic variable
      4 wallHeatFlowRate       heat flow rate at wall   [W]    basic variable
      5 massFlowRateOutlet     mass flow rate at outlet [kg/s] basic variable
*/

void smo_heatexchanger_rc_(int *n, double *flowIndexInlet
      , double *stateIndexInlet, double *flowIndexHeat
      , double *stateIndexHeat, double *stateIndexOutlet
      , double *flowIndexOutlet, double *inletTemperature
      , double *outletTemperature, double *outletTemperatureDot
      , double *wallTemperature, double *wallHeatFlowRate
      , double *massFlowRateOutlet, double rp[3], int ip[1], int ic[7]
      , void *ps[7], int *flag)

{
   int loop, logi;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
   double T2;
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   int fluidIndex;
   double initialOutletTemperature, efficienccy, tauOutput;

   fluidIndex = ip[0];

   initialOutletTemperature = rp[0];
   efficienccy = rp[1];
   tauOutput  = rp[2];
   logi = 0;
   loop = 0;

/* Common -> SI units conversions. */

/*   *stateIndexInlet *= ??; CONVERSION UNKNOWN */
/*   *stateIndexHeat *= ??; CONVERSION UNKNOWN */
/*   *stateIndexOutlet *= ??; CONVERSION UNKNOWN */
/*   *flowIndexOutlet *= ??; CONVERSION UNKNOWN */

/*
   Set all submodel outputs below:

   *flowIndexInlet = ??;
   *flowIndexHeat = ??;
   *inletTemperature = ??;
   *outletTemperatureDot = ??;
   *wallTemperature = ??;
   *wallHeatFlowRate = ??;
   *massFlowRateOutlet = ??;
*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
   // Initialization at first run
   if (firstc_()) {
	   fluidFlowInlet = FluidFlow_new();
	   fluidFlowIndexInlet = FluidFlow_register(fluidFlowInlet);

	   fluidFlowIndexOutlet = *flowIndexOutlet;
	   fluidFlowOutlet = FluidFlow_get(fluidFlowIndexOutlet);

	   heatState = MediumState_get(*stateIndexHeat);
	   heatStateIndex = *stateIndexHeat;

	   heatFlow = FluidFlow_new();
	   heatFlowIndex = FluidFlow_register(heatFlow);
   }

   FluidFlow* fluidFlowObjInlet = (FluidFlow*) fluidFlowInlet;
   FluidFlow* fluidFlowObjOutlet = (FluidFlow*) fluidFlowOutlet;

   if (fluidFlowObjOutlet->massFlowRate > 0) {
	   amefprintf(stderr, "\nFatal error in %s instance %d.\n", _SUBMODELNAME_, *n);
	   amefprintf(stderr, "\nReverse flow encouuntered. Restrict the flow direction, e.g. by adding check valve.");
	   AmeExit(1);
   }

   MediumState_update_Tp(fluidStateOutlet, *outletTemperature, MediumState_p(fluidStateInlet)); //:TODO: (MILEN) ??? in macro is aslo called this function

   double wallT = MediumState_T(heatState);
   double inletT = MediumState_T(fluidStateInlet);
   double outletTemperatureTarget = inletT + (wallT - inletT) * efficienccy;

   fluidFlowObjInlet->massFlowRate = fluidFlowObjOutlet->massFlowRate;
   fluidFlowObjInlet->enthalpyFlowRate = MediumState_h(fluidStateInlet) * fluidFlowObjInlet->massFlowRate;

   FluidFlow* heatFlowObj = (FluidFlow*) heatFlow;
   heatFlowObj->massFlowRate = 0.0;
   heatFlowObj->enthalpyFlowRate = fluidFlowObjOutlet->massFlowRate * MediumState_h(fluidStateOutlet) - fluidFlowObjInlet->enthalpyFlowRate; //wall heat flow rate

   *outletTemperatureDot = (outletTemperatureTarget - *outletTemperature) / tauOutput;

   *wallTemperature = wallT;
   *wallHeatFlowRate = heatFlowObj->enthalpyFlowRate;
   *massFlowRateOutlet = fluidFlowObjOutlet->massFlowRate;

   *inletTemperature = inletT;
   *flowIndexInlet = fluidFlowIndexInlet;
   *flowIndexHeat = heatFlowIndex;
/* DELME

   // Initialization at first run
   if (firstc_()) {
	   FluidPoint* inletNode = (FluidPoint*) INLET_NODE;
	   FluidPoint_init(inletNode, (int)(*inletComIndex), -1);
   }
   if (*outletMassFlowRate > 0) {
	   raiseError(OUTLET_NODE, "Reverse flow encouuntered. "
			   "Restrict the flow direction, e.g. by adding check valve.");
   }
   T2 = *wallTemperature + 273.15;
   FluidPoint* inletNode = (FluidPoint*) INLET_NODE;
   FluidPoint* outletNode = (FluidPoint*) OUTLET_NODE;
   FluidPoint_computeState_p_rho(inletNode, *inletPressure, *inletDensity);
   FluidPoint_computeState_p_T(outletNode, *inletPressure, *outletTemperature);
   *inletTemperature = inletNode->T;
   double outletTemperatureTarget = inletNode->T +
		   (T2 - inletNode->T) * efficienccy;

   *inletEnthalpyFlowRate = inletNode->h * (*outletMassFlowRate);
   *wallHeatFlowRate = (*outletMassFlowRate) * outletNode->h - (*inletEnthalpyFlowRate);
   *outletTemperatureDot = (outletTemperatureTarget - *outletTemperature)/tauOutput;
*/

/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *flowIndexInlet /= ??; CONVERSION UNKNOWN */
/*   *stateIndexInlet /= ??; CONVERSION UNKNOWN */
/*   *flowIndexHeat /= ??; CONVERSION UNKNOWN */
/*   *stateIndexHeat /= ??; CONVERSION UNKNOWN */
/*   *stateIndexOutlet /= ??; CONVERSION UNKNOWN */
/*   *flowIndexOutlet /= ??; CONVERSION UNKNOWN */
}

extern double smo_heatexchanger_rc_macro0_(int *n
      , double *stateIndexInlet, double *outletTemperature
      , double rp[3], int ip[1], int ic[7], void *ps[7], int *flag)

{
   double stateIndexOutlet;
   int loop, logi;
/* >>>>>>>>>>>>Extra Macro Function macro0 Declarations Here. */
/* <<<<<<<<<<<<End of Extra Macro macro0 declarations. */
   int fluidIndex;
   double initialOutletTemperature, efficienccy, tauOutput;

   fluidIndex = ip[0];

   initialOutletTemperature = rp[0];
   efficienccy = rp[1];
   tauOutput  = rp[2];
   logi = 0;
   loop = 0;

/* Common -> SI units conversions. */

/*   *stateIndexInlet *= ??; CONVERSION UNKNOWN */

/*
   Define and return the following macro variable:

   stateIndexOutlet = ??;
*/


/* >>>>>>>>>>>>Macro Function macro0 Executable Statements. */
   if (firstc_()) {
	   fluidStateIndexInlet = *stateIndexInlet;
	   fluidStateInlet = MediumState_get(fluidStateIndexInlet);

	   int mediumIndexInlet = Medium_index(MediumState_getMedium(fluidStateInlet));

	   Medium* fluid = Medium_get(mediumIndexInlet);
	   fluidStateOutlet = MediumState_new(fluid);
	   fluidStateIndexOutlet = MediumState_register(fluidStateOutlet);
   }

   MediumState_update_Tp(fluidStateOutlet, *outletTemperature, MediumState_p(fluidStateInlet));

   stateIndexOutlet = fluidStateIndexOutlet;
   /* DELME
      FluidPoint* outletNode = (FluidPoint*) OUTLET_NODE;
      FluidPoint_computeState_p_T(outletNode, *inletPressure, *outletTemperature);
      outletDensity = outletNode->rho;*/
/* <<<<<<<<<<<<End of Macro macro0 Executable Statements. */

/* SI -> Common units conversions. */

/*   *stateIndexInlet /= ??; CONVERSION UNKNOWN */

/*   *stateIndexOutlet /= ??; CONVERSION UNKNOWN */

   return stateIndexOutlet;
}

