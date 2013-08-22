/* Submodel SMO_HEATEXCHANGER_PRESSURE_DROP_RC skeleton created by AME Submodel editing utility
   Thu Aug 22 15:12:43 2013 */



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

#define _SUBMODELNAME_ "SMO_HEATEXCHANGER_PRESSURE_DROP_RC"

/* >>>>>>>>>>>>Insert Private Code Here. */
/*
#include "volumes/PipeHeatExchNoPrDrNoMassAcc.h"


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
*/
/* <<<<<<<<<<<<End of Private Code. */


/* There are 9 real parameters:

   heatExhcangeEfficienccy heat exchanger efficiency   [null]
   heatExchangeGain        heat exchange gain          [null]
   hydraulicDiameter       hydraulic diameter          [mm -> m]
   pipeLength              pipe length                 [m]
   flowArea                flow (cross sectional) area [mm**2 -> m**2]
   absoluteRoughness       absolute roughness          [mm -> m]
   pressureDropGain        pressure drop gain          [null]
   initP                   initial pressure            [bar -> Pa]
   initT                   initial temperature         [K]
*/


/* There are 2 integer parameters:

   heatExchangeCalculationMethod heat exchange calculation method
   geometryType                  geometry type                   
*/

void smo_heatexchanger_pressure_drop_rcin_(int *n, double rp[9]
      , int ip[2], int ic[6], void *ps[6], double *outletStateValue)

{
   int loop, error;
/* >>>>>>>>>>>>Extra Initialization Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Initialization declarations. */
   int heatExchangeCalculationMethod, geometryType;
   double heatExhcangeEfficienccy, heatExchangeGain, hydraulicDiameter
      , pipeLength, flowArea, absoluteRoughness, pressureDropGain, 
      initP, initT;

   heatExchangeCalculationMethod = ip[0];
   geometryType = ip[1];

   heatExhcangeEfficienccy = rp[0];
   heatExchangeGain = rp[1];
   hydraulicDiameter = rp[2];
   pipeLength = rp[3];
   flowArea   = rp[4];
   absoluteRoughness = rp[5];
   pressureDropGain = rp[6];
   initP      = rp[7];
   initT      = rp[8];
   loop = 0;
   error = 0;

/*
   If necessary, check values of the following:

   rp[0..8]
   *outletStateValue
*/


/* >>>>>>>>>>>>Initialization Function Check Statements. */
/* <<<<<<<<<<<<End of Initialization Check Statements. */

/*   Integer parameter checking:   */

   if (heatExchangeCalculationMethod < 1 || heatExchangeCalculationMethod > 2)
   {
      amefprintf(stderr, "\nheat exchange calculation method must be in range [1..2].\n");
      error = 2;
   }
   if (geometryType < 1 || geometryType > 2)
   {
      amefprintf(stderr, "\ngeometry type must be in range [1..2].\n");
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
   hydraulicDiameter = rp[2];
   rp[4]    *= 1.00000000000000e-006;
   flowArea   = rp[4];
   rp[5]    *= 1.00000000000000e-003;
   absoluteRoughness = rp[5];
   rp[7]    *= 1.00000000000000e+005;
   initP      = rp[7];


/* >>>>>>>>>>>>Initialization Function Executable Statements. */
  /* if (heatExchangeCalculationMethod == 1) {
	   _component = Pipe_HeatExch_NoPrDr_NoMassAcc_Efficiency_new(
			   heatExhcangeEfficienccy, tauOutput);
   } else {
	   double flowAreaValue;
	   if (geometryType == 1) {
		   flowAreaValue = M_PI / 4 * hydraulicDiameter * hydraulicDiameter;
	   } else {
		   flowAreaValue = flowArea;
	   }
	   if (heatExchangeCalculationMethod == 2) {
		   double heatExchangeArea = 4 * flowAreaValue / hydraulicDiameter * pipeLength;
		   _convection = ForcedConvection_GivenConvectionCoefficient_new(
				   heatExchangeArea);
		   Convection_setConvectionCoefficient(_convection, convectionCoefficientGiven);
	   } else {
		   _convection = ForcedConvection_StraightPipe_new(
				   hydraulicDiameter, flowAreaValue, pipeLength);
	   }
	   Convection_setHeatExchangeGain(_convection, heatExchangeGain);
	   _component = Pipe_HeatExch_NoPrDr_NoMassAcc_Convection_new(
			   _convection, tauOutput);
   }*/
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

/*  There are 3 ports.

   Port 1 has 2 variables:

      1 flowIndexInlet      flow index inlet  [smoFFL] basic variable output  UNPLOTTABLE
      2 stateIndexInlet     state index inlet [smoTDS] basic variable input  UNPLOTTABLE

   Port 2 has 2 variables:

      1 heatFlowIndex        heat flow index    [smoHFL] basic variable output  UNPLOTTABLE
      2 thermalNodeIndex     thermal node index [smoTHN] basic variable input  UNPLOTTABLE

   Port 3 has 2 variables:

      1 stateIndexOutlet     state index outlet [smoTDS] multi line macro 'smo_heatexchanger_pressure_drop_rc_macro0_'  UNPLOTTABLE
      2 flowIndexOutlet      flow index outlet  [smoFFL] basic variable input  UNPLOTTABLE
*/

/*  There are 8 internal variables.

      1 inletTemperature          inlet temperature            [K]         basic variable
      2 outletTemperature         outlet temperature           [K]         basic variable
      3 outletPressure            outlet pressure              [bar -> Pa] basic variable
      4 outletStateValue          outlet state value           [null]      explicit state (derivative `outletStateValueDot')
      5 reynoldsNumber            Reynolds number              [null]      basic variable
      6 convectionCoefficient     convection coefficient       [W/m**2/K]  basic variable
      7 wallHeatFlowRate          heat flow rate from the wall [W]         basic variable
      8 totalPressureLoss         total pressure loss          [bar -> Pa] basic variable
*/

void smo_heatexchanger_pressure_drop_rc_(int *n
      , double *flowIndexInlet, double *stateIndexInlet
      , double *heatFlowIndex, double *thermalNodeIndex
      , double *stateIndexOutlet, double *flowIndexOutlet
      , double *inletTemperature, double *outletTemperature
      , double *outletPressure, double *outletStateValue
      , double *outletStateValueDot, double *reynoldsNumber
      , double *convectionCoefficient, double *wallHeatFlowRate
      , double *totalPressureLoss, double rp[9], int ip[2], int ic[6]
      , void *ps[6], int *flag)

{
   int loop, logi;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   int heatExchangeCalculationMethod, geometryType;
   double heatExhcangeEfficienccy, heatExchangeGain, hydraulicDiameter
      , pipeLength, flowArea, absoluteRoughness, pressureDropGain, 
      initP, initT;

   heatExchangeCalculationMethod = ip[0];
   geometryType = ip[1];

   heatExhcangeEfficienccy = rp[0];
   heatExchangeGain = rp[1];
   hydraulicDiameter = rp[2];
   pipeLength = rp[3];
   flowArea   = rp[4];
   absoluteRoughness = rp[5];
   pressureDropGain = rp[6];
   initP      = rp[7];
   initT      = rp[8];
   logi = 0;
   loop = 0;

/* Common -> SI units conversions. */

/*   *stateIndexInlet *= ??; CONVERSION UNKNOWN */
/*   *thermalNodeIndex *= ??; CONVERSION UNKNOWN */
/*   *stateIndexOutlet *= ??; CONVERSION UNKNOWN */
/*   *flowIndexOutlet *= ??; CONVERSION UNKNOWN */

/*
   Set all submodel outputs below:

   *flowIndexInlet = ??;
   *heatFlowIndex = ??;
   *inletTemperature = ??;
   *outletTemperature = ??;
   *outletPressure = ??;
   *outletStateValueDot = ??;
   *reynoldsNumber = ??;
   *convectionCoefficient = ??;
   *wallHeatFlowRate = ??;
   *totalPressureLoss = ??;
*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
 /*  // Initialization at first run
   if (firstc_()) {
	   FluidFlow* outletFlow = FluidFlow_get(*flowIndexOutlet);
	   Pipe_HeatExch_NoPrDr_NoMassAcc_init(
			   _component, outletFlow);
	   _inletFluidFlow = Pipe_HeatExch_NoPrDr_NoMassAcc_getInletFlow(
			   _component);
	   _inletFluidFlowIndex = SmoComponent_getInstanceIndex(_inletFluidFlow);
	   _wallHeatFlow = Pipe_HeatExch_NoPrDr_NoMassAcc_getWallHeatFlow(_component);
	   _wallHeatFlowIndex = SmoComponent_getInstanceIndex(_wallHeatFlow);
   }

   Pipe_HeatExch_NoPrDr_NoMassAcc_compute(_component);

   *flowIndexInlet = _inletFluidFlowIndex;
   *heatFlowIndex = _wallHeatFlowIndex;
   *inletTemperature = MediumState_T(_inletFluidState);
   *outletTemperature = MediumState_T(_outletFluidState);
   *outletStateValueDot = Pipe_HeatExch_NoPrDr_NoMassAcc_getOutletStateDerivative(_component);
   *wallHeatFlowRate = -HeatFlow_getEnthalpyFlowRate(_wallHeatFlow);

   if (heatExchangeCalculationMethod != 1) {
	   *reynoldsNumber = ForcedConvection_getReynoldsNumber(_convection);
	   *convectionCoefficient = Convection_getConvectionCoefficient(_convection);
   }*/
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *flowIndexInlet /= ??; CONVERSION UNKNOWN */
/*   *stateIndexInlet /= ??; CONVERSION UNKNOWN */
/*   *heatFlowIndex /= ??; CONVERSION UNKNOWN */
/*   *thermalNodeIndex /= ??; CONVERSION UNKNOWN */
/*   *stateIndexOutlet /= ??; CONVERSION UNKNOWN */
/*   *flowIndexOutlet /= ??; CONVERSION UNKNOWN */
   *outletPressure /= 1.00000000000000e+005;
   *totalPressureLoss /= 1.00000000000000e+005;
}

extern double smo_heatexchanger_pressure_drop_rc_macro0_(int *n
      , double *stateIndexInlet, double *thermalNodeIndex
      , double *outletStateValue, double rp[9], int ip[2], int ic[6]
      , void *ps[6], int *flag)

{
   double stateIndexOutlet;
   int loop, logi;
/* >>>>>>>>>>>>Extra Macro Function macro0 Declarations Here. */
/* <<<<<<<<<<<<End of Extra Macro macro0 declarations. */
   int heatExchangeCalculationMethod, geometryType;
   double heatExhcangeEfficienccy, heatExchangeGain, hydraulicDiameter
      , pipeLength, flowArea, absoluteRoughness, pressureDropGain, 
      initP, initT;

   heatExchangeCalculationMethod = ip[0];
   geometryType = ip[1];

   heatExhcangeEfficienccy = rp[0];
   heatExchangeGain = rp[1];
   hydraulicDiameter = rp[2];
   pipeLength = rp[3];
   flowArea   = rp[4];
   absoluteRoughness = rp[5];
   pressureDropGain = rp[6];
   initP      = rp[7];
   initT      = rp[8];
   logi = 0;
   loop = 0;

/* Common -> SI units conversions. */

/*   *stateIndexInlet *= ??; CONVERSION UNKNOWN */
/*   *thermalNodeIndex *= ??; CONVERSION UNKNOWN */

/*
   Define and return the following macro variable:

   stateIndexOutlet = ??;
*/


/* >>>>>>>>>>>>Macro Function macro0 Executable Statements. */
/*   if (firstc_()) {
	   // Get the inlet state and wall node
	   _inletFluidState = MediumState_get(*stateIndexInlet);
	   ThermalNode* wallNode = ThermalNode_get(*thermalNodeIndex);
	   // Initialize outlet
	   Pipe_HeatExch_NoPrDr_NoMassAcc_initOutletState(
			   _component, _inletFluidState, wallNode);
	   _outletFluidState =
			   Pipe_HeatExch_NoPrDr_NoMassAcc_getOutletState(_component);
	   _outletFluidStateIndex = SmoComponent_getInstanceIndex(
			   _outletFluidState);
	   *outletStateValue = Pipe_HeatExch_NoPrDr_NoMassAcc_getOutletStateValue(
			   _component);
   } else {
	   Pipe_HeatExch_NoPrDr_NoMassAcc_updateOutletState(
			   _component, *outletStateValue);
   }
   stateIndexOutlet = _outletFluidStateIndex;*/
/* <<<<<<<<<<<<End of Macro macro0 Executable Statements. */

/* SI -> Common units conversions. */

/*   *stateIndexInlet /= ??; CONVERSION UNKNOWN */
/*   *thermalNodeIndex /= ??; CONVERSION UNKNOWN */

/*   *stateIndexOutlet /= ??; CONVERSION UNKNOWN */

   return stateIndexOutlet;
}

