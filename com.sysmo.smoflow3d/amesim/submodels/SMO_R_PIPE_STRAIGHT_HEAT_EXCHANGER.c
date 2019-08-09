/* Submodel SMO_R_PIPE_STRAIGHT_HEAT_EXCHANGER skeleton created by AME Submodel editing utility
   ??? ??? 9 10:17:39 2019 */



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

#define _SUBMODELNAME_ "SMO_R_PIPE_STRAIGHT_HEAT_EXCHANGER"

/* >>>>>>>>>>>>Insert Private Code Here. */
#include "SmoFlowAme.h"
#include "flow_R/PipeHeatExchanger_R.h"
#include "flow_R/ManagerComponents_R.h"

#define _component ps[0]
#define _componentIndex ic[0]

#define _manager ps[1]
#define _managerIndex ic[1]

#define _fluidFlow2 ps[2]
#define _fluidFlow2Index ic[2]

#define _wallHeatFlow ps[3]
#define _wallHeatFlowIndex ic[3]

#define _convection ps[4]
#define _friction ps[5]
/* <<<<<<<<<<<<End of Private Code. */


/* There are 6 real parameters:

   pipeLength        pipe length                 [m]
   hydraulicDiameter hydraulic diameter          [mm -> m]
   flowArea          flow (cross sectional) area [mm**2 -> m**2]
   absoluteRoughness absolute roughness          [mm -> m]
   pressureDropGain  pressure drop gain          [null]
   heatExchangeGain  heat exchange gain          [null]
*/


/* There are 4 integer parameters:

   geometryType                 geometry type                              
   forcedConvectionUseFilmState use film state (forced convection)         
   forcedConvectionLimitOutput  limit the heat exchange (forced convection)
   useDragCoeffGain             use drag coefficient gain                  
*/


/* There is 1 text parameter:

   dragCoeffGainExpression drag coefficient gain expression k=f(Re [-], rho_up [kg/m**3]) 
*/

void smo_r_pipe_straight_heat_exchangerin_(int *n, double rp[6]
      , int ip[4], char *tp[1], int ic[4], void *ps[6])

{
   int loop, error;
/* >>>>>>>>>>>>Extra Initialization Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Initialization declarations. */
   int geometryType, forcedConvectionUseFilmState, 
      forcedConvectionLimitOutput, useDragCoeffGain;
   double pipeLength, hydraulicDiameter, flowArea, absoluteRoughness, 
      pressureDropGain, heatExchangeGain;
   char *dragCoeffGainExpression;

   geometryType = ip[0];
   forcedConvectionUseFilmState = ip[1];
   forcedConvectionLimitOutput = ip[2];
   useDragCoeffGain = ip[3];

   pipeLength = rp[0];
   hydraulicDiameter = rp[1];
   flowArea   = rp[2];
   absoluteRoughness = rp[3];
   pressureDropGain = rp[4];
   heatExchangeGain = rp[5];

   dragCoeffGainExpression = tp[0];
   loop = 0;
   error = 0;

/*
   If necessary, check values of the following:

   rp[0..5]
*/


/* >>>>>>>>>>>>Initialization Function Check Statements. */
/* <<<<<<<<<<<<End of Initialization Check Statements. */

/*   Integer parameter checking:   */

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
   if (forcedConvectionLimitOutput < 1 || forcedConvectionLimitOutput > 2)
   {
      amefprintf(stderr, "\nlimit the heat exchange (forced convection) must be in range [1..2].\n");
      error = 2;
   }
   if (useDragCoeffGain < 1 || useDragCoeffGain > 2)
   {
      amefprintf(stderr, "\nuse drag coefficient gain must be in range [1..2].\n");
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

   rp[1]    *= 1.00000000000000e-003;
   hydraulicDiameter = rp[1];
   rp[2]    *= 1.00000000000000e-006;
   flowArea   = rp[2];
   rp[3]    *= 1.00000000000000e-003;
   absoluteRoughness = rp[3];


/* >>>>>>>>>>>>Initialization Function Executable Statements. */
   double flowAreaValue;
   if (geometryType == 1) { //cylindrical pipe
	   flowAreaValue = M_PI / 4 * hydraulicDiameter * hydraulicDiameter;
   } else { //non-cylindrical pipe
	   flowAreaValue = flowArea;
   }

   _component = StraightPipeHeatExchanger_R_new(
		   pipeLength,
		   hydraulicDiameter,
		   flowAreaValue,
		   absoluteRoughness,
		   pressureDropGain,
		   heatExchangeGain,
		   forcedConvectionLimitOutput - 1, //:TRICKY: (0-no, 1-yes),
		   forcedConvectionUseFilmState - 1, //:TRICKY: (0-no, 1-yes)
		   useDragCoeffGain - 1, //:TRICKY: (0-no, 1-yes)
		   dragCoeffGainExpression
   );

   _componentIndex = Component_R_register(_component);
   SMOCOMPONENT_SET_PROPS(_component)

   _fluidFlow2Index = FlowComponent_R_getFlow2Index(_component);
   _fluidFlow2 = FluidFlow_get(_fluidFlow2Index);
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

/*  There are 3 ports.

   Port 1 has 3 variables:

      1 outputRCompID1     R-component ID (ouput, port1) [smoRCompID]  basic variable output  UNPLOTTABLE
      2 inputRCompID1      R-component ID (input, port1) [smoRCompID]  basic variable input  UNPLOTTABLE
      3 smoRChainID        R-components chain ID         [smoRChainID] basic variable input  UNPLOTTABLE

   Port 2 has 2 variables:

      1 heatFlowIndex        heat flow index    [smoHFL] basic variable output  UNPLOTTABLE
      2 thermalNodeIndex     thermal node index [smoTHN] basic variable input  UNPLOTTABLE

   Port 3 has 3 variables:

      1 outputRCompID3      R-component ID (output, port3) [smoRCompID] multi line macro 'smo_r_pipe_straight_heat_exchanger_macro0_'  UNPLOTTABLE
      2 smoRChainIDDupl     duplicate of smoRChainID      
      3 inputRCompID3       R-component ID (input, port3)  [smoRCompID] basic variable input  UNPLOTTABLE
*/

/*  There are 9 internal variables.

      1 massFlowRate              mass flow rate (port1 -> port3)     [kg/s]        basic variable
      2 enthalpyFlowRate          enthalpy flow rate (port1 -> port3) [W]           basic variable
      3 pressureLoss              total pressure loss                 [bar -> Pa]   basic variable
      4 reynoldsNumber            Reynolds number                     [null]        basic variable
      5 convectionCoefficient     convection coefficient              [W/m**2/K]    basic variable
      6 heatFlowRateFromWall      heat flow rate                      [W]           basic variable
      7 vFlowUp                   velocity (upstream flow)            [m/s]         basic variable
      8 dynamicPressureUp         dynamic pressure (upstream flow)    [barA -> PaA] basic variable
      9 machNumberUp              Mach number (upstream flow)         [null]        basic variable
*/

void smo_r_pipe_straight_heat_exchanger_(int *n
      , double *outputRCompID1, double *inputRCompID1
      , double *smoRChainID, double *heatFlowIndex
      , double *thermalNodeIndex, double *outputRCompID3
      , double *inputRCompID3, double *massFlowRate
      , double *enthalpyFlowRate, double *pressureLoss
      , double *reynoldsNumber, double *convectionCoefficient
      , double *heatFlowRateFromWall, double *vFlowUp
      , double *dynamicPressureUp, double *machNumberUp, double rp[6]
      , int ip[4], char *tp[1], int ic[4], void *ps[6], int *flag)

{
   int loop, logi;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   int geometryType, forcedConvectionUseFilmState, 
      forcedConvectionLimitOutput, useDragCoeffGain;
   double pipeLength, hydraulicDiameter, flowArea, absoluteRoughness, 
      pressureDropGain, heatExchangeGain;
   char *dragCoeffGainExpression;

   geometryType = ip[0];
   forcedConvectionUseFilmState = ip[1];
   forcedConvectionLimitOutput = ip[2];
   useDragCoeffGain = ip[3];

   pipeLength = rp[0];
   hydraulicDiameter = rp[1];
   flowArea   = rp[2];
   absoluteRoughness = rp[3];
   pressureDropGain = rp[4];
   heatExchangeGain = rp[5];

   dragCoeffGainExpression = tp[0];
   logi = 0;
   loop = 0;

/* Common -> SI units conversions. */

/*   *inputRCompID1 *= ??; CONVERSION UNKNOWN [smoRCompID] */
/*   *smoRChainID *= ??; CONVERSION UNKNOWN [smoRChainID] */
/*   *thermalNodeIndex *= ??; CONVERSION UNKNOWN [smoTHN] */
/*   *outputRCompID3 *= ??; CONVERSION UNKNOWN [smoRCompID] */
/*   *inputRCompID3 *= ??; CONVERSION UNKNOWN [smoRCompID] */

/*
   Set all submodel outputs below:

   *outputRCompID1 = ??;
   *heatFlowIndex = ??;
   *massFlowRate = ??;
   *enthalpyFlowRate = ??;
   *pressureLoss = ??;
   *reynoldsNumber = ??;
   *convectionCoefficient = ??;
   *heatFlowRateFromWall = ??;
   *vFlowUp    = ??;
   *dynamicPressureUp = ??;
   *machNumberUp = ??;
*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
   SMOCOMPONENT_PRINT_MAIN_CALC
   if (firstc_()) {
	   ManagerComponents_R_addOuterState2(_manager, *inputRCompID3);

	   _wallHeatFlow = PipeHeatExchanger_R_getWallHeatFlow(_component);
	   _wallHeatFlowIndex = SmoObject_getInstanceIndex(_wallHeatFlow);

	   _convection = PipeHeatExchanger_R_getConvection(_component);
	   _friction = Pipe_R_getFrictionFlowPipe(_component);
   }
   ManagerComponents_R_compute(_manager);

   *massFlowRate = FluidFlow_getMassFlowRate(_fluidFlow2);
   *enthalpyFlowRate = FluidFlow_getEnthalpyFlowRate(_fluidFlow2);
   *pressureLoss = FlowComponent_R_getAbsolutePressureDrop(_component);

   *reynoldsNumber = ForcedConvection_getReynoldsNumber(_convection);
   *convectionCoefficient = Convection_getConvectionCoefficient(_convection);
   *heatFlowRateFromWall = - HeatFlow_getEnthalpyFlowRate(_wallHeatFlow);

   *vFlowUp = FrictionFlowPipe_getUpstreamVelocity(_friction, *massFlowRate);
   *dynamicPressureUp = FrictionFlowPipe_getUpstreamDynamicPressure(_friction, *massFlowRate);
   *machNumberUp = FrictionFlowPipe_getUpstreamMachNumber(_friction, *massFlowRate);

   *heatFlowIndex = _wallHeatFlowIndex;
   *outputRCompID1 = _componentIndex;
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *outputRCompID1 /= ??; CONVERSION UNKNOWN [smoRCompID] */
/*   *inputRCompID1 /= ??; CONVERSION UNKNOWN [smoRCompID] */
/*   *smoRChainID /= ??; CONVERSION UNKNOWN [smoRChainID] */
/*   *heatFlowIndex /= ??; CONVERSION UNKNOWN [smoHFL] */
/*   *thermalNodeIndex /= ??; CONVERSION UNKNOWN [smoTHN] */
/*   *outputRCompID3 /= ??; CONVERSION UNKNOWN [smoRCompID] */
/*   *inputRCompID3 /= ??; CONVERSION UNKNOWN [smoRCompID] */
   *pressureLoss /= 1.00000000000000e+005;
   *dynamicPressureUp /= 1.00000000000000e+005;
}

extern double smo_r_pipe_straight_heat_exchanger_macro0_(int *n
      , double *inputRCompID1, double *smoRChainID
      , double *thermalNodeIndex, double rp[6], int ip[4], char *tp[1]
      , int ic[4], void *ps[6], int *flag)

{
   double outputRCompID3;
   int loop, logi;
/* >>>>>>>>>>>>Extra Macro Function macro0 Declarations Here. */
/* <<<<<<<<<<<<End of Extra Macro macro0 declarations. */
   int geometryType, forcedConvectionUseFilmState, 
      forcedConvectionLimitOutput, useDragCoeffGain;
   double pipeLength, hydraulicDiameter, flowArea, absoluteRoughness, 
      pressureDropGain, heatExchangeGain;
   char *dragCoeffGainExpression;

   geometryType = ip[0];
   forcedConvectionUseFilmState = ip[1];
   forcedConvectionLimitOutput = ip[2];
   useDragCoeffGain = ip[3];

   pipeLength = rp[0];
   hydraulicDiameter = rp[1];
   flowArea   = rp[2];
   absoluteRoughness = rp[3];
   pressureDropGain = rp[4];
   heatExchangeGain = rp[5];

   dragCoeffGainExpression = tp[0];
   logi = 0;
   loop = 0;

/* Common -> SI units conversions. */

/*   *inputRCompID1 *= ??; CONVERSION UNKNOWN [smoRCompID] */
/*   *smoRChainID *= ??; CONVERSION UNKNOWN [smoRChainID] */
/*   *thermalNodeIndex *= ??; CONVERSION UNKNOWN [smoTHN] */

/*
   Define and return the following macro variable:

   outputRCompID3 = ??;
*/


/* >>>>>>>>>>>>Macro Function macro0 Executable Statements. */
   SMOCOMPONENt_PRINT_MACRO_MSG("outputRCompID3")
   if (firstc_()) {
	   _managerIndex = *smoRChainID;
	   _manager = ManagerComponents_R_get(_managerIndex);

	   ManagerComponents_R_addComponent(_manager, _component, *inputRCompID1);

	   ThermalNode* wallNode = ThermalNode_get(*thermalNodeIndex);
	   PipeHeatExchanger_R_setHeatExchangerThermalNode(_component, wallNode);
   }

   outputRCompID3 = _componentIndex;
/* <<<<<<<<<<<<End of Macro macro0 Executable Statements. */

/* SI -> Common units conversions. */

/*   *inputRCompID1 /= ??; CONVERSION UNKNOWN [smoRCompID] */
/*   *smoRChainID /= ??; CONVERSION UNKNOWN [smoRChainID] */
/*   *thermalNodeIndex /= ??; CONVERSION UNKNOWN [smoTHN] */

/*   *outputRCompID3 /= ??; CONVERSION UNKNOWN [smoRCompID] */

   return outputRCompID3;
}

