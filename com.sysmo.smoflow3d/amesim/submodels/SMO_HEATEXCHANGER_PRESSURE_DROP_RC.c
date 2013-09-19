/* Submodel SMO_HEATEXCHANGER_PRESSURE_DROP_RC skeleton created by AME Submodel editing utility
   Wed Aug 28 14:55:15 2013 */



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
#include "SmoFlowAme.h"
#include "volumes/PipeHeatExchPrDropRC.h"

#define _port1FluidFlow ps[0]
#define _port1FluidFlowIndex ic[0]

#define _port3FluidState ps[1]
#define _port3FluidStateIndex ic[1]

#define _wallHeatFlow ps[2]
#define _wallHeatFlowIndex ic[2]

#define _port1FluidState ps[3]
#define _friction ps[4]
#define _convection ps[5]
#define _component ps[6]
/* <<<<<<<<<<<<End of Private Code. */


/* There are 8 real parameters:

   hydraulicDiameter hydraulic diameter          [mm -> m]
   pipeLength        pipe length                 [m]
   flowArea          flow (cross sectional) area [mm**2 -> m**2]
   absoluteRoughness absolute roughness          [mm -> m]
   pressureDropGain  pressure drop gain          [null]
   heatExchangeGain  heat exchange gain          [null]
   initP             initial pressure            [bar -> Pa]
   initT             initial temperature         [K]
*/


/* There is 1 integer parameter:

   geometryType geometry type
*/

void smo_heatexchanger_pressure_drop_rcin_(int *n, double rp[8]
      , int ip[1], int ic[6], void *ps[6], double stateValues[2])

{
   int loop, error;
/* >>>>>>>>>>>>Extra Initialization Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Initialization declarations. */
   int geometryType;
   double hydraulicDiameter, pipeLength, flowArea, absoluteRoughness, 
      pressureDropGain, heatExchangeGain, initP, initT;

   geometryType = ip[0];

   hydraulicDiameter = rp[0];
   pipeLength = rp[1];
   flowArea   = rp[2];
   absoluteRoughness = rp[3];
   pressureDropGain = rp[4];
   heatExchangeGain = rp[5];
   initP      = rp[6];
   initT      = rp[7];
   loop = 0;
   error = 0;

/*
   If necessary, check values of the following:

   rp[0..7]
   stateValues[0..1]
*/


/* >>>>>>>>>>>>Initialization Function Check Statements. */
/* <<<<<<<<<<<<End of Initialization Check Statements. */

/*   Integer parameter checking:   */

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

   rp[0]    *= 1.00000000000000e-003;
   hydraulicDiameter = rp[0];
   rp[2]    *= 1.00000000000000e-006;
   flowArea   = rp[2];
   rp[3]    *= 1.00000000000000e-003;
   absoluteRoughness = rp[3];
   rp[6]    *= 1.00000000000000e+005;
   initP      = rp[6];


/* >>>>>>>>>>>>Initialization Function Executable Statements. */
   double flowAreaValue;
   if (geometryType == 1) {
	   flowAreaValue = M_PI / 4 * hydraulicDiameter * hydraulicDiameter;
   } else {
	   flowAreaValue = flowArea;
   }
	_friction = FrictionFlowPipe_StraightPipe_new(
			hydraulicDiameter, pipeLength, absoluteRoughness);
	_convection = ForcedConvection_StraightPipe_new(
			hydraulicDiameter, flowArea, pipeLength);

   Convection_setHeatExchangeGain(_convection, heatExchangeGain);
   FrictionFlowPipe_setPressureDropGain(_friction, pressureDropGain);

   double internalVolume = flowArea * pipeLength;
   _component = PipeHeatExchPrDrop_RC_new(internalVolume, _friction, _convection);
   SMOCOMPONEN_SET_PROPS(_component)
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

/*  There are 3 ports.

   Port 1 has 2 variables:

      1 port1FlowIndex      flow index at port 1  [smoFFL] basic variable output  UNPLOTTABLE
      2 port1StateIndex     state index at port 1 [smoTDS] basic variable input  UNPLOTTABLE

   Port 2 has 2 variables:

      1 heatFlowIndex        heat flow index    [smoHFL] basic variable output  UNPLOTTABLE
      2 thermalNodeIndex     thermal node index [smoTHN] basic variable input  UNPLOTTABLE

   Port 3 has 2 variables:

      1 port3StateIndex     state index outlet   [smoTDS] multi line macro 'smo_heatexchanger_pressure_drop_rc_macro0_'  UNPLOTTABLE
      2 port3FlowIndex      flow index at port 3 [smoFFL] basic variable input  UNPLOTTABLE
*/

/*  There are 7 internal variables.

      1 port1Temperature          port 1 temperature           [K]         basic variable
      2 port3Temperature          port 3 temperature           [K]         basic variable
      3 stateValues[2]            state values                 [null]      explicit state (derivative `stateValuesDot')
      4 reynoldsNumber            Reynolds number              [null]      basic variable
      5 convectionCoefficient     convection coefficient       [W/m**2/K]  basic variable
      6 wallHeatFlowRate          heat flow rate from the wall [W]         basic variable
      7 totalPressureLoss         total pressure loss          [bar -> Pa] basic variable
*/

void smo_heatexchanger_pressure_drop_rc_(int *n
      , double *port1FlowIndex, double *port1StateIndex
      , double *heatFlowIndex, double *thermalNodeIndex
      , double *port3StateIndex, double *port3FlowIndex
      , double *port1Temperature, double *port3Temperature
      , double stateValues[2], double stateValuesDot[2]
      , double *reynoldsNumber, double *convectionCoefficient
      , double *wallHeatFlowRate, double *totalPressureLoss
      , double rp[8], int ip[1], int ic[6], void *ps[6], int *flag)

{
   int loop, logi;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   int geometryType;
   double hydraulicDiameter, pipeLength, flowArea, absoluteRoughness, 
      pressureDropGain, heatExchangeGain, initP, initT;

   geometryType = ip[0];

   hydraulicDiameter = rp[0];
   pipeLength = rp[1];
   flowArea   = rp[2];
   absoluteRoughness = rp[3];
   pressureDropGain = rp[4];
   heatExchangeGain = rp[5];
   initP      = rp[6];
   initT      = rp[7];
   logi = 0;
   loop = 0;

/* Common -> SI units conversions. */

/*   *port1StateIndex *= ??; CONVERSION UNKNOWN */
/*   *thermalNodeIndex *= ??; CONVERSION UNKNOWN */
/*   *port3StateIndex *= ??; CONVERSION UNKNOWN */
/*   *port3FlowIndex *= ??; CONVERSION UNKNOWN */

/*
   Set all submodel outputs below:

   *port1FlowIndex = ??;
   *heatFlowIndex = ??;
   *port1Temperature = ??;
   *port3Temperature = ??;
   stateValuesDot[0..1] = ??;
   *reynoldsNumber = ??;
   *convectionCoefficient = ??;
   *wallHeatFlowRate = ??;
   *totalPressureLoss = ??;
*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
  // Initialization at first run
   if (firstc_()) {
	   FluidFlow* port3Flow = FluidFlow_get(*port3FlowIndex);
	   Component_RC_init(_component, port3Flow);
	   _port1FluidFlow = Component_RC_getPort1Flow(_component);
	   _port1FluidFlowIndex = SmoObject_getInstanceIndex(_port1FluidFlow);
	   _wallHeatFlow = Component_RC_getWallHeatFlow(_component);
	   _wallHeatFlowIndex = SmoObject_getInstanceIndex(_wallHeatFlow);
   }

   Component_RC_compute(_component);

   *port1FlowIndex = _port1FluidFlowIndex;
   *heatFlowIndex = _wallHeatFlowIndex;
   *port1Temperature = MediumState_T(_port1FluidState);
   *port3Temperature = MediumState_T(_port3FluidState);
   Component_RC_getStateDerivatives(_component, &stateValuesDot[0], &stateValuesDot[1]);
   *reynoldsNumber = ForcedConvection_getReynoldsNumber(_convection);
   *convectionCoefficient = Convection_getConvectionCoefficient(_convection);
   *wallHeatFlowRate = HeatFlow_getEnthalpyFlowRate(_wallHeatFlow);
   *totalPressureLoss = FrictionFlowPipe_getAbsolutePressureDrop(_friction);
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *port1FlowIndex /= ??; CONVERSION UNKNOWN */
/*   *port1StateIndex /= ??; CONVERSION UNKNOWN */
/*   *heatFlowIndex /= ??; CONVERSION UNKNOWN */
/*   *thermalNodeIndex /= ??; CONVERSION UNKNOWN */
/*   *port3StateIndex /= ??; CONVERSION UNKNOWN */
/*   *port3FlowIndex /= ??; CONVERSION UNKNOWN */
   *totalPressureLoss /= 1.00000000000000e+005;
}

extern double smo_heatexchanger_pressure_drop_rc_macro0_(int *n
      , double *port1StateIndex, double *thermalNodeIndex
      , double stateValues[2], double rp[8], int ip[1], int ic[6]
      , void *ps[6], int *flag)

{
   double port3StateIndex;
   int loop, logi;
/* >>>>>>>>>>>>Extra Macro Function macro0 Declarations Here. */
/* <<<<<<<<<<<<End of Extra Macro macro0 declarations. */
   int geometryType;
   double hydraulicDiameter, pipeLength, flowArea, absoluteRoughness, 
      pressureDropGain, heatExchangeGain, initP, initT;

   geometryType = ip[0];

   hydraulicDiameter = rp[0];
   pipeLength = rp[1];
   flowArea   = rp[2];
   absoluteRoughness = rp[3];
   pressureDropGain = rp[4];
   heatExchangeGain = rp[5];
   initP      = rp[6];
   initT      = rp[7];
   logi = 0;
   loop = 0;

/* Common -> SI units conversions. */

/*   *port1StateIndex *= ??; CONVERSION UNKNOWN */
/*   *thermalNodeIndex *= ??; CONVERSION UNKNOWN */

/*
   Define and return the following macro variable:

   port3StateIndex = ??;
*/


/* >>>>>>>>>>>>Macro Function macro0 Executable Statements. */
   if (firstc_()) {
	   // Get the inlet state and wall node
	   _port1FluidState = MediumState_get(*port1StateIndex);
	   ThermalNode* wallNode = ThermalNode_get(*thermalNodeIndex);
	   // Initialize outlet
	   Component_RC_initState(_component, _port1FluidState, wallNode);
	   _port3FluidState = Component_RC_getPort2State(_component);
	   _port3FluidStateIndex = SmoObject_getInstanceIndex(
			   _port3FluidState);
	   MediumState_update_Tp(_port3FluidState, initT, initP);
	   Component_RC_getStateValues(_component, &stateValues[0], &stateValues[1]);
   } else {
	   Component_RC_setStateValues(_component, stateValues[0], stateValues[1]);
   }
   port3StateIndex = _port3FluidStateIndex;
/* <<<<<<<<<<<<End of Macro macro0 Executable Statements. */

/* SI -> Common units conversions. */

/*   *port1StateIndex /= ??; CONVERSION UNKNOWN */
/*   *thermalNodeIndex /= ??; CONVERSION UNKNOWN */

/*   *port3StateIndex /= ??; CONVERSION UNKNOWN */

   return port3StateIndex;
}

