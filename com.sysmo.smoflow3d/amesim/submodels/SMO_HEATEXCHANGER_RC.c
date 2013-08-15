/* Submodel SMO_HEATEXCHANGER_RC skeleton created by AME Submodel editing utility
   Wed Aug 14 23:19:35 2013 */



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
#include "volumes/PipeHeatExchNoPrDrNoMassAcc.h"

#define _convection ps[0]
#define _component ps[1]

#define _fluidFlowIndexInlet ic[2]
#define _fluidFlowInlet ps[2]

#define _fluidStateIndexOutlet ic[3]
#define _fluidStateOutlet ps[3]

#define _heatFlowIndex ic[4]
#define _heatFlow ps[4]

/*
#define _fluidFlowIndexOutlet ic[1]
#define _fluidFlowOutlet ps[1]

#define _fluidStateIndexInlet ic[2]
#define _fluidStateInlet ps[2]


#define _thermalNodeIndex ic[4]
#define _thermalNode ps[4]
*/
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


/* There is 1 integer parameter:

   heatExchangeCalculationMethod heat exchange calculation method
*/

void smo_heatexchanger_rcin_(int *n, double rp[7], int ip[1]
      , int ic[6], void *ps[6], double *outletTemperature)

{
   int loop, error;
/* >>>>>>>>>>>>Extra Initialization Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Initialization declarations. */
   int heatExchangeCalculationMethod;
   double heatExhcangeEfficienccy, convectionCoefficientGiven, 
      heatExchangeGain, hydraulicDiameter, pipeLength, flowArea, 
      tauOutput;

   heatExchangeCalculationMethod = ip[0];

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
   *outletTemperature
*/


/* >>>>>>>>>>>>Initialization Function Check Statements. */
/* <<<<<<<<<<<<End of Initialization Check Statements. */

/*   Integer parameter checking:   */

   if (heatExchangeCalculationMethod < 1 || heatExchangeCalculationMethod > 3)
   {
      amefprintf(stderr, "\nheat exchange calculation method must be in range [1..3].\n");
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
	   _component = Pipe_HeatExch_NoPrDr_NoMassAcc_HeEfficiency_new(
			   heatExhcangeEfficienccy, tauOutput);
   } else {
	   if (heatExchangeCalculationMethod == 2) {
		   double heatExchangeArea = 4 * flowArea / hydraulicDiameter * pipeLength;
		   _convection = ForcedConvection_GivenConvectionCoefficient_new(
				   heatExchangeArea);
	   } else {
		   _convection = ForcedConvection_StraightPipe_new(
				   hydraulicDiameter, flowArea, pipeLength);
	   }
	   ForcedConvection_setHeatExchangeGain(_convection, heatExchangeGain);
	   _component = Pipe_HeatExch_NoPrDr_NoMassAcc_Convection_new(
			   _convection, tauOutput);
   }
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

      1 stateIndexOutlet     state index outlet [smoTDS] multi line macro 'smo_heatexchanger_rc_macro0_'  UNPLOTTABLE
      2 flowIndexOutlet      flow index outlet  [smoFFL] basic variable input  UNPLOTTABLE
*/

/*  There are 5 internal variables.

      1 inletTemperature          inlet temperature      [K]        basic variable
      2 outletTemperature         outlet temperature     [K]        explicit state (derivative `outletTemperatureDot')
      3 reynoldsNumber            Reynolds number        [null]     basic variable
      4 convectionCoefficient     convection coefficient [W/m**2/K] basic variable
      5 wallHeatFlowRate          heat flow rate at wall [W]        basic variable
*/

void smo_heatexchanger_rc_(int *n, double *flowIndexInlet
      , double *stateIndexInlet, double *heatFlowIndex
      , double *thermalNodeIndex, double *stateIndexOutlet
      , double *flowIndexOutlet, double *inletTemperature
      , double *outletTemperature, double *outletTemperatureDot
      , double *reynoldsNumber, double *convectionCoefficient
      , double *wallHeatFlowRate, double rp[7], int ip[1], int ic[6]
      , void *ps[6], int *flag)

{
   int loop, logi;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   int heatExchangeCalculationMethod;
   double heatExhcangeEfficienccy, convectionCoefficientGiven, 
      heatExchangeGain, hydraulicDiameter, pipeLength, flowArea, 
      tauOutput;

   heatExchangeCalculationMethod = ip[0];

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

/*   *stateIndexInlet *= ??; CONVERSION UNKNOWN */
/*   *thermalNodeIndex *= ??; CONVERSION UNKNOWN */
/*   *stateIndexOutlet *= ??; CONVERSION UNKNOWN */
/*   *flowIndexOutlet *= ??; CONVERSION UNKNOWN */

/*
   Set all submodel outputs below:

   *flowIndexInlet = ??;
   *heatFlowIndex = ??;
   *inletTemperature = ??;
   *outletTemperatureDot = ??;
   *reynoldsNumber = ??;
   *convectionCoefficient = ??;
   *wallHeatFlowRate = ??;
*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
   // Initialization at first run
   /**
   if (firstc_()) {
	   FluidFlow* outletFlow = FluidFlow_get(*flowIndexOutlet);
	   ThermalNode* wallNode = ThermalNode_get(*thermalNodeIndex);
	   MediumState* inletState = MediumState_get(*stateIndexInlet);
	   Pipe_HeatExch_NoPrDr_NoMassAcc_init(_component, inletState,
			   wallNode, outletFlow, flowIndexInlet, xxx, heatFlowIndex);
   }

   if (FluidFlow_getMassFlowRate(_fluidFlowOutlet) > 0) {
	   amefprintf(stderr, "\nFatal error in %s instance %d.\n", _SUBMODELNAME_, *n);
	   amefprintf(stderr, "\nReverse flow encouuntered. Restrict the flow direction, e.g. by adding check valve.");
	   AmeExit(1);
   }

   double wallT = MediumState_T(_thermalNode);
   double inletT = MediumState_T(_fluidStateInlet);
   double outletTemperatureTarget = inletT + (wallT - inletT) * efficienccy;

   FluidFlow_setMassFlowRate(_fluidFlowInlet, FluidFlow_getMassFlowRate(_fluidFlowOutlet));
   FluidFlow_setEnthalpyFlowRate(_fluidFlowInlet, MediumState_h(_fluidStateInlet) * FluidFlow_getMassFlowRate(_fluidFlowInlet));

   HeatFlow_setEnthalpyFlowRate(_heatFlow,
		   FluidFlow_getMassFlowRate(_fluidFlowOutlet) * MediumState_h(_fluidStateOutlet) -  FluidFlow_getEnthalpyFlowRate(_fluidFlowInlet));

   *outletTemperatureDot = (outletTemperatureTarget - *outletTemperature) / tauOutput;

   *wallTemperature = wallT;
   *wallHeatFlowRate = HeatFlow_getEnthalpyFlowRate(_heatFlow);
   *massFlowRateOutlet = FluidFlow_getMassFlowRate(_fluidFlowOutlet);

   *inletTemperature = inletT;
   *flowIndexInlet = _fluidFlowIndexInlet;
   *heatFlowIndex = _heatFlowIndex;
	**/
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *flowIndexInlet /= ??; CONVERSION UNKNOWN */
/*   *stateIndexInlet /= ??; CONVERSION UNKNOWN */
/*   *heatFlowIndex /= ??; CONVERSION UNKNOWN */
/*   *thermalNodeIndex /= ??; CONVERSION UNKNOWN */
/*   *stateIndexOutlet /= ??; CONVERSION UNKNOWN */
/*   *flowIndexOutlet /= ??; CONVERSION UNKNOWN */
}

extern double smo_heatexchanger_rc_macro0_(int *n
      , double *stateIndexInlet, double *outletTemperature
      , double rp[7], int ip[1], int ic[6], void *ps[6], int *flag)

{
   double stateIndexOutlet;
   int loop, logi;
/* >>>>>>>>>>>>Extra Macro Function macro0 Declarations Here. */
/* <<<<<<<<<<<<End of Extra Macro macro0 declarations. */
   int heatExchangeCalculationMethod;
   double heatExhcangeEfficienccy, convectionCoefficientGiven, 
      heatExchangeGain, hydraulicDiameter, pipeLength, flowArea, 
      tauOutput;

   heatExchangeCalculationMethod = ip[0];

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

/*   *stateIndexInlet *= ??; CONVERSION UNKNOWN */

/*
   Define and return the following macro variable:

   stateIndexOutlet = ??;
*/


/* >>>>>>>>>>>>Macro Function macro0 Executable Statements. */
   /**
   if (firstc_()) {
	   _fluidStateIndexInlet = *stateIndexInlet;
	   _fluidStateInlet = MediumState_get(_fluidStateIndexInlet);

	   int mediumIndexInlet = Medium_index(MediumState_getMedium(_fluidStateInlet));

	   Medium* fluid = Medium_get(mediumIndexInlet);
	   _fluidStateOutlet = MediumState_new(fluid);
	   _fluidStateIndexOutlet = MediumState_register(_fluidStateOutlet);
   }

   MediumState_update_Tp(_fluidStateOutlet, *outletTemperature, MediumState_p(_fluidStateInlet));

   stateIndexOutlet = _fluidStateIndexOutlet;
   */
/* <<<<<<<<<<<<End of Macro macro0 Executable Statements. */

/* SI -> Common units conversions. */

/*   *stateIndexInlet /= ??; CONVERSION UNKNOWN */

/*   *stateIndexOutlet /= ??; CONVERSION UNKNOWN */

   return stateIndexOutlet;
}

