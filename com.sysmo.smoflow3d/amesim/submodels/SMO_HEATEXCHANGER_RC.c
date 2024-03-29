/* Submodel SMO_HEATEXCHANGER_RC skeleton created by AME Submodel editing utility
   Fri Dec 20 17:40:35 2013 */



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
#include "SmoFlowAme.h"
#include "volumes/HeatExchNoPrDropNoMassAcc_RC.h"

#define _inletFluidState ps[0]
#define _inletFluidStateIndex ic[0]

#define _inletFluidFlow ps[1]
#define _inletFluidFlowIndex ic[1]

#define _outletFluidState ps[2]
#define _outletFluidStateIndex ic[2]

#define _wallHeatFlow ps[3]
#define _wallHeatFlowIndex ic[3]

#define _convection ps[4]
#define _component ps[5]
/* <<<<<<<<<<<<End of Private Code. */


/* There are 7 real parameters:

   heatExhcangeEfficienccy    heat exchanger efficiency      [null]
   convectionCoefficientGiven convection coefficient (given) [W/m**2/K]
   heatExchangeGain           heat exchange gain             [null]
   hydraulicDiameter          hydraulic diameter             [mm -> m]
   pipeLength                 pipe length                    [m]
   flowArea                   flow (cross sectional) area    [mm**2 -> m**2]
   tauOutput                  output time constant           [s]
*/


/* There are 3 integer parameters:

   heatExchangeCalculationMethod heat exchange calculation method  
   geometryType                  geometry type                     
   forcedConvectionUseFilmState  use film state (forced convection)
*/

void smo_heatexchanger_rcin_(int *n, double rp[7], int ip[3]
      , int ic[6], void *ps[6], double *outletStateValue)

{
   int loop, error;
/* >>>>>>>>>>>>Extra Initialization Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Initialization declarations. */
   int heatExchangeCalculationMethod, geometryType, 
      forcedConvectionUseFilmState;
   double heatExhcangeEfficienccy, convectionCoefficientGiven, 
      heatExchangeGain, hydraulicDiameter, pipeLength, flowArea, 
      tauOutput;

   heatExchangeCalculationMethod = ip[0];
   geometryType = ip[1];
   forcedConvectionUseFilmState = ip[2];

   heatExhcangeEfficienccy = rp[0];
   convectionCoefficientGiven = rp[1];
   heatExchangeGain = rp[2];
   hydraulicDiameter = rp[3];
   pipeLength = rp[4];
   flowArea   = rp[5];
   tauOutput  = rp[6];
   loop = 0;
   error = 0;

/*
   If necessary, check values of the following:

   rp[0..6]
   *outletStateValue
*/


/* >>>>>>>>>>>>Initialization Function Check Statements. */
/* <<<<<<<<<<<<End of Initialization Check Statements. */

/*   Integer parameter checking:   */

   if (heatExchangeCalculationMethod < 1 || heatExchangeCalculationMethod > 3)
   {
      amefprintf(stderr, "\nheat exchange calculation method must be in range [1..3].\n");
      error = 2;
   }
   if (geometryType < 1 || geometryType > 2)
   {
      amefprintf(stderr, "\ngeometry type must be in range [1..2].\n");
      error = 2;
   }
   if (forcedConvectionUseFilmState < 1 || forcedConvectionUseFilmState > 2)
   {
      amefprintf(stderr, "\nuse film state (forced convection) must be in range [1..2].\n");
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

   rp[3]    *= 1.00000000000000e-003;
   hydraulicDiameter = rp[3];
   rp[5]    *= 1.00000000000000e-006;
   flowArea   = rp[5];


/* >>>>>>>>>>>>Initialization Function Executable Statements. */
   if (heatExchangeCalculationMethod == 1) {
	   _component = HeatExchNoPrDropNoMassAcc_RC_Efficiency_new(heatExhcangeEfficienccy, tauOutput);
   } else {
	   double flowAreaValue;
	   double heatExchangeArea;
	   if (geometryType == 1) { //cylindrical pipe
		   flowAreaValue = M_PI / 4 * hydraulicDiameter * hydraulicDiameter;
		   double perimeter = M_PI * hydraulicDiameter;
		   heatExchangeArea =  perimeter * pipeLength;
	   } else { //non-cylindrical pipe
		   flowAreaValue = flowArea;
		   double perimeter = 4 * flowAreaValue / hydraulicDiameter;
		   heatExchangeArea = perimeter * pipeLength;
	   }

	   if (heatExchangeCalculationMethod == 2) {
		   _convection = ForcedConvection_GivenConvectionCoefficient_new(convectionCoefficientGiven, heatExchangeArea);
	   } else {
		   _convection = ForcedConvection_StraightPipe_new(pipeLength, hydraulicDiameter, flowAreaValue);
	   }

	   Convection_setHeatExchangeGain(_convection, heatExchangeGain);
	   Convection_setUseFilmState(_convection, forcedConvectionUseFilmState - 1); //:TRICKY: (0-no, 1-yes)

	   _component = HeatExchNoPrDropNoMassAcc_RC_Convection_new(_convection, tauOutput);
   }

   SMOCOMPONENT_SET_PROPS(_component)
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

/*  There are 3 ports.

   Port 1 has 3 variables:

      1 inletFluidFlowIndex              inlet fluid flow index       [smoFFL] basic variable output  UNPLOTTABLE
      2 fluidFlowActivationSignalDup     duplicate of fluidFlowActivationSignal
      3 inletFluidStateIndex             inlet fluid state index      [smoTDS] basic variable input  UNPLOTTABLE

   Port 2 has 2 variables:

      1 heatFlowIndex        heat flow index    [smoHFL] basic variable output  UNPLOTTABLE
      2 thermalNodeIndex     thermal node index [smoTHN] basic variable input  UNPLOTTABLE

   Port 3 has 3 variables:

      1 outletFluidStateIndex         outlet fluid state index     [smoTDS]  multi line macro 'smo_heatexchanger_rc_macro0_'  UNPLOTTABLE
      2 outletFluidFlowIndex          outlet fluid flow index      [smoFFL]  basic variable input  UNPLOTTABLE
      3 fluidFlowActivationSignal     fluid flow activation signal [smoFFAS] basic variable input
*/

/*  There are 6 internal variables.

      1 inletTemperature          inlet temperature            [K]        basic variable
      2 outletTemperature         outlet temperature           [K]        basic variable
      3 outletStateValue          outlet state value           [null]     explicit state (derivative `outletStateValueDot')
      4 reynoldsNumber            Reynolds number              [null]     basic variable
      5 convectionCoefficient     convection coefficient       [W/m**2/K] basic variable
      6 heatFlowRateFromWall      heat flow rate from the wall [W]        basic variable
*/

void smo_heatexchanger_rc_(int *n, double *inletFluidFlowIndex
      , double *inletFluidStateIndex, double *heatFlowIndex
      , double *thermalNodeIndex, double *outletFluidStateIndex
      , double *outletFluidFlowIndex
      , double *fluidFlowActivationSignal, double *inletTemperature
      , double *outletTemperature, double *outletStateValue
      , double *outletStateValueDot, double *reynoldsNumber
      , double *convectionCoefficient, double *heatFlowRateFromWall
      , double rp[7], int ip[3], int ic[6], void *ps[6], int *flag)

{
   int loop, logi;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   int heatExchangeCalculationMethod, geometryType, 
      forcedConvectionUseFilmState;
   double heatExhcangeEfficienccy, convectionCoefficientGiven, 
      heatExchangeGain, hydraulicDiameter, pipeLength, flowArea, 
      tauOutput;

   heatExchangeCalculationMethod = ip[0];
   geometryType = ip[1];
   forcedConvectionUseFilmState = ip[2];

   heatExhcangeEfficienccy = rp[0];
   convectionCoefficientGiven = rp[1];
   heatExchangeGain = rp[2];
   hydraulicDiameter = rp[3];
   pipeLength = rp[4];
   flowArea   = rp[5];
   tauOutput  = rp[6];
   logi = 0;
   loop = 0;

/* Common -> SI units conversions. */

/*   *inletFluidStateIndex *= ??; CONVERSION UNKNOWN */
/*   *thermalNodeIndex *= ??; CONVERSION UNKNOWN */
/*   *outletFluidStateIndex *= ??; CONVERSION UNKNOWN */
/*   *outletFluidFlowIndex *= ??; CONVERSION UNKNOWN */
/*   *fluidFlowActivationSignal *= ??; CONVERSION UNKNOWN */

/*
   Set all submodel outputs below:

   *inletFluidFlowIndex = ??;
   *heatFlowIndex = ??;
   *inletTemperature = ??;
   *outletTemperature = ??;
   *outletStateValueDot = ??;
   *reynoldsNumber = ??;
   *convectionCoefficient = ??;
   *heatFlowRateFromWall = ??;
*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
   SMOCOMPONENT_PRINT_MAIN_CALC
   if (firstc_()) {
	   FluidFlow* outletFlow = FluidFlow_get(*outletFluidFlowIndex);
	   HeatExchNoPrDropNoMassAcc_RC_init(_component, outletFlow);

	   _inletFluidFlow = HeatExchNoPrDropNoMassAcc_RC_getPort1Flow(_component);
	   _inletFluidFlowIndex = SmoObject_getInstanceIndex(_inletFluidFlow);

	   _wallHeatFlow = HeatExchNoPrDropNoMassAcc_RC_getWallHeatFlow(_component);
	   _wallHeatFlowIndex = SmoObject_getInstanceIndex(_wallHeatFlow);
   }

   HeatExchNoPrDropNoMassAcc_RC_compute(_component);

   *inletFluidFlowIndex = _inletFluidFlowIndex;
   *heatFlowIndex = _wallHeatFlowIndex;
   *inletTemperature = MediumState_T(_inletFluidState);
   *outletTemperature = MediumState_T(_outletFluidState);
   *outletStateValueDot = HeatExchNoPrDropNoMassAcc_RC_getStateDerivative(_component);
   *heatFlowRateFromWall = -HeatFlow_getEnthalpyFlowRate(_wallHeatFlow);

   if (heatExchangeCalculationMethod != 1) {
	   *reynoldsNumber = ForcedConvection_getReynoldsNumber(_convection);
	   *convectionCoefficient = Convection_getConvectionCoefficient(_convection);
   }
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *inletFluidFlowIndex /= ??; CONVERSION UNKNOWN */
/*   *inletFluidStateIndex /= ??; CONVERSION UNKNOWN */
/*   *heatFlowIndex /= ??; CONVERSION UNKNOWN */
/*   *thermalNodeIndex /= ??; CONVERSION UNKNOWN */
/*   *outletFluidStateIndex /= ??; CONVERSION UNKNOWN */
/*   *outletFluidFlowIndex /= ??; CONVERSION UNKNOWN */
/*   *fluidFlowActivationSignal /= ??; CONVERSION UNKNOWN */
}

extern double smo_heatexchanger_rc_macro0_(int *n
      , double *inletFluidStateIndex, double *thermalNodeIndex
      , double *outletStateValue, double rp[7], int ip[3], int ic[6]
      , void *ps[6], int *flag)

{
   double outletFluidStateIndex;
   int loop, logi;
/* >>>>>>>>>>>>Extra Macro Function macro0 Declarations Here. */
/* <<<<<<<<<<<<End of Extra Macro macro0 declarations. */
   int heatExchangeCalculationMethod, geometryType, 
      forcedConvectionUseFilmState;
   double heatExhcangeEfficienccy, convectionCoefficientGiven, 
      heatExchangeGain, hydraulicDiameter, pipeLength, flowArea, 
      tauOutput;

   heatExchangeCalculationMethod = ip[0];
   geometryType = ip[1];
   forcedConvectionUseFilmState = ip[2];

   heatExhcangeEfficienccy = rp[0];
   convectionCoefficientGiven = rp[1];
   heatExchangeGain = rp[2];
   hydraulicDiameter = rp[3];
   pipeLength = rp[4];
   flowArea   = rp[5];
   tauOutput  = rp[6];
   logi = 0;
   loop = 0;

/* Common -> SI units conversions. */

/*   *inletFluidStateIndex *= ??; CONVERSION UNKNOWN */
/*   *thermalNodeIndex *= ??; CONVERSION UNKNOWN */

/*
   Define and return the following macro variable:

   outletFluidStateIndex = ??;
*/


/* >>>>>>>>>>>>Macro Function macro0 Executable Statements. */
   SMOCOMPONENt_PRINT_MACRO
   if (firstc_()) {
	   // Get the inlet state and wall node
	   _inletFluidState = MediumState_get(*inletFluidStateIndex);
	   ThermalNode* wallNode = ThermalNode_get(*thermalNodeIndex);

	   // Initialize outlet
	   HeatExchNoPrDropNoMassAcc_RC_initStates(_component, _inletFluidState, wallNode);

	   _outletFluidState = HeatExchNoPrDropNoMassAcc_RC_getPort2State(_component);
	   _outletFluidStateIndex = SmoObject_getInstanceIndex(_outletFluidState);

	   *outletStateValue = HeatExchNoPrDropNoMassAcc_RC_getStateValue(_component);
   } else {
	   HeatExchNoPrDropNoMassAcc_RC_setStateValue(_component, *outletStateValue);
   }

   outletFluidStateIndex = _outletFluidStateIndex;
/* <<<<<<<<<<<<End of Macro macro0 Executable Statements. */

/* SI -> Common units conversions. */

/*   *inletFluidStateIndex /= ??; CONVERSION UNKNOWN */
/*   *thermalNodeIndex /= ??; CONVERSION UNKNOWN */

/*   *outletFluidStateIndex /= ??; CONVERSION UNKNOWN */

   return outletFluidStateIndex;
}

