/* Submodel SMO_FORCED_CONVECTION skeleton created by AME Submodel editing utility
   Thu Feb 9 09:58:15 2017 */



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

#define _SUBMODELNAME_ "SMO_FORCED_CONVECTION"

/* >>>>>>>>>>>>Insert Private Code Here. */
#include "SmoFlowAme.h"
#include "flow/ForcedConvection.h"
 
#define _heatFlowIndex ic[0]
#define _heatFlow ps[0]
 
#define _fluidFlowIndex ic[1]
#define _fluidFlow ps[1]
 
#define _component ps[2]
/* <<<<<<<<<<<<End of Private Code. */


/* There are 8 real parameters:

   heatExchangeGain           heat exchange gain                                      [null]
   convectionCoefficientGiven convection coefficient (given)                          [W/m**2/K]
   characteristicLength       characteristic length (hydraulic diameter for a tube)   [mm -> m]
   hydraulicDiameterInjector  hydraulic diameter of the injector                      [mm -> m]
   flowArea                   flow (cross sectional) area                             [m**2]
   heatExchangeArea           heat exchange area                                      [m**2]
   ReL                        laminar to turbulent transition:  lower Reynolds number [null]
   ReH                        laminar to turbulent transition:  upper Reynolds number [null]
*/


/* There are 3 integer parameters:

   convCalcMethod covection calculation method
   useFilmState   use film state              
   useInjector    use an injector             
*/


/* There are 2 text parameters:

   nusseltExpressionLaminarFlow   nusselt correlation expression Nu=f(Re, Pr) in laminar flow  
   nusseltExpressionTurbulentFlow nusselt correlation expression Nu=f(Re, Pr) in turbulent flow
*/

void smo_forced_convectionin_(int *n, double rp[8], int ip[3]
      , char *tp[2], int ic[2], void *ps[3]
      , double *fluidFlowActivationSignal)

{
   int loop, error;
/* >>>>>>>>>>>>Extra Initialization Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Initialization declarations. */
   int convCalcMethod, useFilmState, useInjector;
   double heatExchangeGain, convectionCoefficientGiven, 
      characteristicLength, hydraulicDiameterInjector, flowArea, 
      heatExchangeArea, ReL, ReH;
   char *nusseltExpressionLaminarFlow, *nusseltExpressionTurbulentFlow;

   convCalcMethod = ip[0];
   useFilmState = ip[1];
   useInjector = ip[2];

   heatExchangeGain = rp[0];
   convectionCoefficientGiven = rp[1];
   characteristicLength = rp[2];
   hydraulicDiameterInjector = rp[3];
   flowArea   = rp[4];
   heatExchangeArea = rp[5];
   ReL        = rp[6];
   ReH        = rp[7];

   nusseltExpressionLaminarFlow = tp[0];
   nusseltExpressionTurbulentFlow = tp[1];
   loop = 0;
   error = 0;

/*
   If necessary, check values of the following:

   rp[0..7]
*/

/*
   Check and/or reset the following fixed and/or discrete variable

   *fluidFlowActivationSignal = ??;
*/


/* >>>>>>>>>>>>Initialization Function Check Statements. */
/* <<<<<<<<<<<<End of Initialization Check Statements. */

/*   Integer parameter checking:   */

   if (convCalcMethod < 1 || convCalcMethod > 2)
   {
      amefprintf(stderr, "\ncovection calculation method must be in range [1..2].\n");
      error = 2;
   }
   if (useFilmState < 1 || useFilmState > 2)
   {
      amefprintf(stderr, "\nuse film state must be in range [1..2].\n");
      error = 2;
   }
   if (useInjector < 1 || useInjector > 2)
   {
      amefprintf(stderr, "\nuse an injector must be in range [1..2].\n");
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

   rp[2]    *= 1.00000000000000e-003;
   characteristicLength = rp[2];
   rp[3]    *= 1.00000000000000e-003;
   hydraulicDiameterInjector = rp[3];


/* >>>>>>>>>>>>Initialization Function Executable Statements. */
   _heatFlow = HeatFlow_new();
   _heatFlowIndex = HeatFlow_register(_heatFlow);
 
   _fluidFlow = FluidFlow_new();
   _fluidFlowIndex = FluidFlow_register(_fluidFlow);
 
   if (convCalcMethod == 1) {
	   _component = ForcedConvection_GivenConvectionCoefficient_new(convectionCoefficientGiven, heatExchangeArea);
   } else if (convCalcMethod == 2) {
	   if (useInjector == 1) { //1 - no
		   _component = ForcedConvection_NusseltExpression_new(
		   		characteristicLength,
		   		flowArea,
		   		heatExchangeArea,
		   		nusseltExpressionLaminarFlow,
		   		nusseltExpressionTurbulentFlow,
		   		ReL,
		   		ReH);
	   } else { //2 - yes
		   _component = ForcedConvection_NusseltExpression_WithInjector_new(
				characteristicLength,
				heatExchangeArea,
				nusseltExpressionLaminarFlow,
				nusseltExpressionTurbulentFlow,
				ReL,
				ReH,
				hydraulicDiameterInjector);
	   }
   }
   SMOCOMPONENT_SET_PROPS(_component)
 
   ForcedConvection_setLimitOutput(_component, 0); //yes
   Convection_setHeatExchangeGain(_component, heatExchangeGain);
   Convection_setUseFilmState(_component, useFilmState - 1); //:TRICKY: 0-no, 1-yes
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

/*  There are 3 ports.

   Port 1 has 1 variable:

      1 massFlowRate     mass flow rate [kg/s] basic variable input

   Port 2 has 3 variables:

      1 fluidFlowIndex                fluid flow index             [smoFFL]  basic variable output  UNPLOTTABLE
      2 fluidFlowActivationSignal     fluid flow activation signal [smoFFAS] fixed  UNPLOTTABLE
      3 fluidStateIndex               fluid state index            [smoTDS]  basic variable input  UNPLOTTABLE

   Port 3 has 2 variables:

      1 heatFlowIndex        heat flow index    [smoHFL] basic variable output  UNPLOTTABLE
      2 thermalNodeIndex     thermal node index [smoTHN] basic variable input  UNPLOTTABLE
*/

/*  There are 4 internal variables.

      1 reynoldsNumber            Reynolds number               [null]     basic variable
      2 nusseltNumber             Nusselt number                [null]     basic variable
      3 convectionCoefficient     convection coefficient        [W/m**2/K] basic variable
      4 heatFlowRateFromWall      heat flow rate  from the wall [W]        basic variable
*/

void smo_forced_convection_(int *n, double *massFlowRate
      , double *fluidFlowIndex, double *fluidStateIndex
      , double *heatFlowIndex, double *thermalNodeIndex
      , double *reynoldsNumber, double *nusseltNumber
      , double *convectionCoefficient, double *heatFlowRateFromWall
      , double rp[8], int ip[3], char *tp[2], int ic[2], void *ps[3])

{
   int loop;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   int convCalcMethod, useFilmState, useInjector;
   double heatExchangeGain, convectionCoefficientGiven, 
      characteristicLength, hydraulicDiameterInjector, flowArea, 
      heatExchangeArea, ReL, ReH;
   char *nusseltExpressionLaminarFlow, *nusseltExpressionTurbulentFlow;

   convCalcMethod = ip[0];
   useFilmState = ip[1];
   useInjector = ip[2];

   heatExchangeGain = rp[0];
   convectionCoefficientGiven = rp[1];
   characteristicLength = rp[2];
   hydraulicDiameterInjector = rp[3];
   flowArea   = rp[4];
   heatExchangeArea = rp[5];
   ReL        = rp[6];
   ReH        = rp[7];

   nusseltExpressionLaminarFlow = tp[0];
   nusseltExpressionTurbulentFlow = tp[1];
   loop = 0;

/* Common -> SI units conversions. */

/*   *fluidStateIndex *= ??; CONVERSION UNKNOWN [smoTDS] */
/*   *thermalNodeIndex *= ??; CONVERSION UNKNOWN [smoTHN] */

/*
   Set all submodel outputs below:

   *fluidFlowIndex = ??;
   *heatFlowIndex = ??;
   *reynoldsNumber = ??;
   *nusseltNumber = ??;
   *convectionCoefficient = ??;
   *heatFlowRateFromWall = ??;
*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
   SMOCOMPONENT_PRINT_MAIN_CALC
   if (firstc_()) {
	   MediumState* fluidState = MediumState_get(*fluidStateIndex);
	   ThermalNode* wallNode = ThermalNode_get(*thermalNodeIndex);
	   ForcedConvection_init(_component, fluidState, fluidState, wallNode);
   }
 
   ForcedConvection_compute(_component, *massFlowRate);
   Convection_updateFluidFlow(_component, _fluidFlow);
   Convection_updateHeatFlow(_component, _heatFlow);
 
   *reynoldsNumber = ForcedConvection_getReynoldsNumber(_component);
   *nusseltNumber = Convection_getNusseltNumber(_component);
   *convectionCoefficient = Convection_getConvectionCoefficient(_component);
   *heatFlowRateFromWall = Convection_getHeatFlowRate(_component);
 
   *fluidFlowIndex = _fluidFlowIndex;
   *heatFlowIndex = _heatFlowIndex;
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *fluidFlowIndex /= ??; CONVERSION UNKNOWN [smoFFL] */
/*   *fluidStateIndex /= ??; CONVERSION UNKNOWN [smoTDS] */
/*   *heatFlowIndex /= ??; CONVERSION UNKNOWN [smoHFL] */
/*   *thermalNodeIndex /= ??; CONVERSION UNKNOWN [smoTHN] */
}

