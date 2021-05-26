/* Submodel SMO_RADIATIVE_EXCHANGE_VARIABLE_EMISSIVITY skeleton created by AME Submodel editing utility
   ?? ??? 26 14:16:34 2021 */



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

#define _SUBMODELNAME_ "SMO_RADIATIVE_EXCHANGE_VARIABLE_EMISSIVITY"

/* >>>>>>>>>>>>Insert Private Code Here. */
#include "SmoFlowAme.h"
#include "flow/RadiationWallFluid.h"

#define _heatFlowIndex ic[0]
#define _heatFlow ps[0]

#define _fluidFlowIndex ic[1]
#define _fluidFlow ps[1]

#define _component ps[2]
/* <<<<<<<<<<<<End of Private Code. */


/* There are 2 real parameters:

   heatExchangeGain heat exchange gain [null]
   heatExchangeArea heat exchange area [m**2]
*/


/* There is 1 text parameter:

   emissivityVar emissivity values of wall
*/

void smo_radiative_exchange_variable_emissivityin_(int *n
      , double rp[2], char *tp[1], int ic[4], void *ps[4]
      , double *fluidFlowActivationSignal)

{
   int loop, error;
/* >>>>>>>>>>>>Extra Initialization Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Initialization declarations. */
   double heatExchangeGain, heatExchangeArea;
   char *emissivityVar;

   heatExchangeGain = rp[0];
   heatExchangeArea = rp[1];

   emissivityVar = tp[0];
   loop = 0;
   error = 0;

/*
   If necessary, check values of the following:

   rp[0..1]
*/

/*
   Check and/or reset the following fixed and/or discrete variable

   *fluidFlowActivationSignal = ??;
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
   _heatFlow = HeatFlow_new();
   _heatFlowIndex = HeatFlow_register(_heatFlow);

   _fluidFlow = FluidFlow_new();
   _fluidFlowIndex = FluidFlow_register(_fluidFlow);

   _component = RadiationWallFluid_VariableEmissivity_new(emissivityVar, heatExchangeArea);
   SMOCOMPONENT_SET_PROPS(_component)

   Radiation_setHeatExchangeGain(_component, heatExchangeGain);
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

/*  There are 2 ports.

   Port 1 has 2 variables:

      1 heatFlowIndex        heat flow index    [smoHFL] basic variable output  UNPLOTTABLE
      2 thermalNodeIndex     thermal node index [smoTHN] basic variable input  UNPLOTTABLE

   Port 2 has 3 variables:

      1 fluidFlowIndex                fluid flow index             [smoFFL]  basic variable output  UNPLOTTABLE
      2 fluidFlowActivationSignal     fluid flow activation signal [smoFFAS] fixed  UNPLOTTABLE
      3 fluidStateIndex               fluid state index            [smoTDS]  basic variable input  UNPLOTTABLE
*/

/*  There are 2 internal variables.

      1 qDot           heat flow rate from the wall [W]    basic variable
      2 emissivity     emissivity of wall           [null] basic variable
*/

void smo_radiative_exchange_variable_emissivity_(int *n
      , double *heatFlowIndex, double *thermalNodeIndex
      , double *fluidFlowIndex, double *fluidStateIndex, double *qDot
      , double *emissivity, double rp[2], char *tp[1], int ic[4]
      , void *ps[4])

{
   int loop;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   double heatExchangeGain, heatExchangeArea;
   char *emissivityVar;

   heatExchangeGain = rp[0];
   heatExchangeArea = rp[1];

   emissivityVar = tp[0];
   loop = 0;

/* Common -> SI units conversions. */

/*   *thermalNodeIndex *= ??; CONVERSION UNKNOWN [smoTHN] */
/*   *fluidStateIndex *= ??; CONVERSION UNKNOWN [smoTDS] */

/*
   Set all submodel outputs below:

   *heatFlowIndex = ??;
   *fluidFlowIndex = ??;
   *qDot       = ??;
   *emissivity = ??;
*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
   SMOCOMPONENT_PRINT_MAIN_CALC
   if (firstc_()) {
	   MediumState* fluidState = MediumState_get(*fluidStateIndex);
	   ThermalNode* wallNode = ThermalNode_get(*thermalNodeIndex);
	   RadiationWallFluid_init(_component, fluidState, wallNode);
   }

   RadiationWallFluid_compute(_component);
   RadiationWallFluid_updateFluidFlow(_component, _fluidFlow);
   RadiationWallFluid_updateHeatFlow(_component, _heatFlow);
   *qDot = Radiation_getHeatFlowRate(_component);
   *emissivity = RadiationWallFluid_getEmissivity(_component);

   *fluidFlowIndex = _fluidFlowIndex;
   *heatFlowIndex = _heatFlowIndex;
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *heatFlowIndex /= ??; CONVERSION UNKNOWN [smoHFL] */
/*   *thermalNodeIndex /= ??; CONVERSION UNKNOWN [smoTHN] */
/*   *fluidFlowIndex /= ??; CONVERSION UNKNOWN [smoFFL] */
/*   *fluidStateIndex /= ??; CONVERSION UNKNOWN [smoTDS] */
}

