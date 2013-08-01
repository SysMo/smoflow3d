/* Submodel SMO_HEATEXCHANGER_CR skeleton created by AME Submodel editing utility
   Thu Aug 1 10:26:55 2013 */



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
/* <<<<<<<<<<<<End of Private Code. */


/* There is 1 real parameter:

   efficienccy heat exchanger efficiency [null]
*/

void smo_heatexchanger_crin_(int *n, double rp[1], int ic[7]
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

      1 flowIndexHeat      heat flow index  [smoFFL] basic variable output  UNPLOTTABLE
      2 stateIndexHeat     heat state index [smoTDS] basic variable input  UNPLOTTABLE

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
      , double *flowIndexInlet, double *flowIndexHeat
      , double *stateIndexHeat, double *flowIndexOutlet
      , double *stateIndexOutlet, double *inletTemperature
      , double *outletTemperature, double *wallTemperature
      , double *wallHeatFlowRate, double *massFlowRateInlet
      , double rp[1], int ic[7], void *ps[7], int *flag)

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
/*   *stateIndexHeat *= ??; CONVERSION UNKNOWN */
/*   *stateIndexOutlet *= ??; CONVERSION UNKNOWN */

/*
   Set all submodel outputs below:

   *flowIndexHeat = ??;
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
	   fluidFlowInlet = FluidFlow_get(*flowIndexInlet);
	   fluidFlowIndexInlet = *flowIndexInlet;

	   fluidFlowOutlet = FluidFlow_new();
	   fluidFlowIndexOutlet = FluidFlow_register(fluidFlowOutlet);

	   heatState = MediumState_get(*stateIndexHeat);
	   heatStateIndex = *stateIndexHeat;

	   heatFlow = FluidFlow_new();
	   heatFlowIndex = FluidFlow_register(heatFlow);
   }

   FluidFlow* fluidFlowObjInlet = (FluidFlow*) fluidFlowInlet;
   FluidFlow* fluidFlowObjOutlet = (FluidFlow*) fluidFlowOutlet;

   if (fluidFlowObjInlet->massFlowRate < 0.0) {
	   amefprintf(stderr, "\nFatal error in %s instance %d.\n", _SUBMODELNAME_, *n);
	   amefprintf(stderr, "\nReverse flow encouuntered. Restrict the flow direction, e.g. by adding check valve.");
	   AmeExit(1);
   }

   double wallT = MediumState_T(heatState);
   if (fluidFlowObjInlet->massFlowRate > 1e-8) {
	  double inletSpecificEnthalpy = fluidFlowObjInlet->enthalpyFlowRate / fluidFlowObjInlet->massFlowRate;
	  MediumState_update_ph(fluidStateInlet, MediumState_p(fluidStateOutlet), inletSpecificEnthalpy);

	  *inletTemperature = MediumState_T(fluidStateInlet);
	  *outletTemperature = *inletTemperature + (wallT - *inletTemperature) * efficienccy;
	  MediumState_update_Tp(fluidStateOutlet, *outletTemperature, MediumState_p(fluidStateOutlet));
   } else {
	   //:TODO: (Nasko) no mass flow rate
   }

   fluidFlowObjOutlet->massFlowRate = fluidFlowObjInlet->massFlowRate;
   fluidFlowObjOutlet->enthalpyFlowRate = MediumState_h(fluidStateOutlet) * fluidFlowObjInlet->massFlowRate;

   FluidFlow* heatFlowObj = (FluidFlow*) heatFlow;
   heatFlowObj->massFlowRate = 0.0;
   heatFlowObj->enthalpyFlowRate = fluidFlowObjInlet->enthalpyFlowRate - fluidFlowObjOutlet->enthalpyFlowRate; //wall heat flow rate

   *wallTemperature = wallT;
   *wallHeatFlowRate = heatFlowObj->enthalpyFlowRate;
   *massFlowRateInlet = fluidFlowObjInlet->massFlowRate;

   *flowIndexHeat = heatFlowIndex;
   *flowIndexOutlet = fluidFlowIndexOutlet;
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *stateIndexInlet /= ??; CONVERSION UNKNOWN */
/*   *flowIndexInlet /= ??; CONVERSION UNKNOWN */
/*   *flowIndexHeat /= ??; CONVERSION UNKNOWN */
/*   *stateIndexHeat /= ??; CONVERSION UNKNOWN */
/*   *flowIndexOutlet /= ??; CONVERSION UNKNOWN */
/*   *stateIndexOutlet /= ??; CONVERSION UNKNOWN */
}

extern double smo_heatexchanger_cr_macro0_(int *n
      , double *stateIndexOutlet, double rp[1], int ic[7], void *ps[7]
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
  	   fluidStateIndexOutlet = *stateIndexOutlet;
  	   fluidStateOutlet = MediumState_get(fluidStateIndexOutlet);

  	   int mediumIndexOutlet = Medium_index(MediumState_getMedium(fluidStateOutlet));

  	   Medium* fluid = Medium_get(mediumIndexOutlet);
  	   fluidStateInlet = MediumState_new(fluid);
  	   fluidStateIndexInlet = MediumState_register(fluidStateInlet);

  	   MediumState_update_ph(fluidStateInlet, MediumState_p(fluidStateOutlet), MediumState_h(fluidStateOutlet));
     }
   stateIndexInlet = fluidStateIndexInlet;
/* <<<<<<<<<<<<End of Macro macro0 Executable Statements. */

/* SI -> Common units conversions. */

/*   *stateIndexOutlet /= ??; CONVERSION UNKNOWN */

/*   *stateIndexInlet /= ??; CONVERSION UNKNOWN */

   return stateIndexInlet;
}

