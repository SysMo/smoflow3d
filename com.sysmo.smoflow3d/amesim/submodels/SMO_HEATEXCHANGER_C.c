/* Submodel SMO_HEATEXCHANGER_C skeleton created by AME Submodel editing utility
   Thu Oct 31 11:23:36 2013 */



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

#define _SUBMODELNAME_ "SMO_HEATEXCHANGER_C"

/* >>>>>>>>>>>>Insert Private Code Here. */
#include "SmoFlowAme.h"
#include "volumes/PipeHeatExch_C.h"

#define _wallHeatFlow ps[0]
#define _wallHeatFlowIndex ic[0]

#define _pipeState ps[1]
#define _pipeStateIndex ic[1]

#define _convection ps[2]
#define _component ps[3]
/* <<<<<<<<<<<<End of Private Code. */


/* There are 6 real parameters:

   hydraulicDiameter hydraulic diameter          [mm -> m]
   pipeLength        pipe length                 [m]
   flowArea          flow (cross sectional) area [mm**2 -> m**2]
   heatExchangeGain  heat exchange gain          [null]
   initP             initial pressure            [bar -> Pa]
   initT             initial temperature         [K]
*/


/* There are 2 integer parameters:

   fluidIndex   fluid index  
   geometryType geometry type
*/

void smo_heatexchanger_cin_(int *n, double rp[6], int ip[2], int ic[2]
      , void *ps[4], double stateValues[2])

{
   int loop, error;
/* >>>>>>>>>>>>Extra Initialization Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Initialization declarations. */
   int fluidIndex, geometryType;
   double hydraulicDiameter, pipeLength, flowArea, heatExchangeGain, 
      initP, initT;

   fluidIndex = ip[0];
   geometryType = ip[1];

   hydraulicDiameter = rp[0];
   pipeLength = rp[1];
   flowArea   = rp[2];
   heatExchangeGain = rp[3];
   initP      = rp[4];
   initT      = rp[5];
   loop = 0;
   error = 0;

/*
   If necessary, check values of the following:

   rp[0..5]
   stateValues[0..1]
*/


/* >>>>>>>>>>>>Initialization Function Check Statements. */
/* <<<<<<<<<<<<End of Initialization Check Statements. */

/*   Integer parameter checking:   */

   if (fluidIndex < 1 || fluidIndex > 99)
   {
      amefprintf(stderr, "\nfluid index must be in range [1..99].\n");
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

   rp[0]    *= 1.00000000000000e-003;
   hydraulicDiameter = rp[0];
   rp[2]    *= 1.00000000000000e-006;
   flowArea   = rp[2];
   rp[4]    *= 1.00000000000000e+005;
   initP      = rp[4];


/* >>>>>>>>>>>>Initialization Function Executable Statements. */
   double flowAreaValue;
   if (geometryType == 1) {
	   flowAreaValue = M_PI / 4 * hydraulicDiameter * hydraulicDiameter;
   } else {
	   flowAreaValue = flowArea;
   }

   _convection = ForcedConvection_StraightPipe_new(hydraulicDiameter, flowArea, pipeLength);
   Convection_setHeatExchangeGain(_convection, heatExchangeGain);

   double internalVolume = flowArea * pipeLength;
   Medium* fluid = Medium_get(fluidIndex);
   _component = PipeHeatExch_C_new(fluid, internalVolume, _convection);
   SMOCOMPONENT_SET_PROPS(_component)

   _pipeState = PipeHeatExch_C_getFluidState(_component);
   _pipeStateIndex = SmoObject_getInstanceIndex(_pipeState);

   MediumState_update_Tp(_pipeState, initT, initP);
   PipeHeatExch_C_getStateValues(_component, &stateValues[0], &stateValues[1]);
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

/*  There are 3 ports.

   Port 1 has 2 variables:

      1 port1FluidStateIndex     fluid state index outlet   [smoTDS] multi line macro 'smo_heatexchanger_c_macro0_'  UNPLOTTABLE
      2 port1FluidFlowIndex      fluid flow index at port 1 [smoFFL] basic variable input  UNPLOTTABLE

   Port 2 has 2 variables:

      1 heatFlowIndex        heat flow index    [smoHFL] basic variable output  UNPLOTTABLE
      2 thermalNodeIndex     thermal node index [smoTHN] basic variable input  UNPLOTTABLE

   Port 3 has 2 variables:

      1 port3FluidStateIndexDupl     duplicate of port1FluidStateIndex
      2 port3FluidFlowIndex          fluid flow index at port 3 [smoFFL] basic variable input  UNPLOTTABLE
*/

/*  There are 11 internal variables.

      1 pressure                  pressure                   [bar -> Pa]     basic variable
      2 temperature               temperature                [K]             basic variable
      3 density                   density                    [kg/m**3]       basic variable
      4 specificEnthalpy          specific enthalpy          [kJ/kg -> J/kg] basic variable
      5 gasMassFraction           gas mass fraction          [null]          basic variable
      6 superHeat                 subcooling / superheat     [degC]          basic variable
      7 internalVolume            volume                     [L -> m**3]     basic variable
      8 stateValues[2]            state values               [null]          explicit state (derivative `stateValuesDot')
      9 reynoldsNumber            Reynolds number            [null]          basic variable
     10 convectionCoefficient     convection coefficient     [W/m**2/K]      basic variable
     11 wallHeatFlowRate          heat flow rate to the wall [W]             basic variable
*/

void smo_heatexchanger_c_(int *n, double *port1FluidStateIndex
      , double *port1FluidFlowIndex, double *heatFlowIndex
      , double *thermalNodeIndex, double *port3FluidFlowIndex
      , double *pressure, double *temperature, double *density
      , double *specificEnthalpy, double *gasMassFraction
      , double *superHeat, double *internalVolume
      , double stateValues[2], double stateValuesDot[2]
      , double *reynoldsNumber, double *convectionCoefficient
      , double *wallHeatFlowRate, double rp[6], int ip[2], int ic[2]
      , void *ps[4], int *flag)

{
   int loop, logi;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   int fluidIndex, geometryType;
   double hydraulicDiameter, pipeLength, flowArea, heatExchangeGain, 
      initP, initT;

   fluidIndex = ip[0];
   geometryType = ip[1];

   hydraulicDiameter = rp[0];
   pipeLength = rp[1];
   flowArea   = rp[2];
   heatExchangeGain = rp[3];
   initP      = rp[4];
   initT      = rp[5];
   logi = 0;
   loop = 0;

/* Common -> SI units conversions. */

/*   *port1FluidStateIndex *= ??; CONVERSION UNKNOWN */
/*   *port1FluidFlowIndex *= ??; CONVERSION UNKNOWN */
/*   *thermalNodeIndex *= ??; CONVERSION UNKNOWN */
/*   *port3FluidFlowIndex *= ??; CONVERSION UNKNOWN */

/*
   Set all submodel outputs below:

   *heatFlowIndex = ??;
   *pressure   = ??;
   *temperature = ??;
   *density    = ??;
   *specificEnthalpy = ??;
   *gasMassFraction = ??;
   *superHeat  = ??;
   *internalVolume = ??;
   stateValuesDot[0..1] = ??;
   *reynoldsNumber = ??;
   *convectionCoefficient = ??;
   *wallHeatFlowRate = ??;
*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
  // Initialization at first run
   if (firstc_()) {
	   FluidFlow* port1Flow = FluidFlow_get(*port1FluidFlowIndex);
	   FluidFlow* port3Flow = FluidFlow_get(*port3FluidFlowIndex);
	   PipeHeatExch_C_init(_component, port1Flow, port3Flow);

	   _wallHeatFlow = PipeHeatExch_C_getWallHeatFlow(_component);
	   _wallHeatFlowIndex = SmoObject_getInstanceIndex(_wallHeatFlow);
   }

   PipeHeatExch_C_compute(_component);
   PipeHeatExch_C_getStateDerivatives(_component, &stateValuesDot[0], &stateValuesDot[1]);

   *heatFlowIndex = _wallHeatFlowIndex;
   *reynoldsNumber = ForcedConvection_getReynoldsNumber(_convection);
   *convectionCoefficient = Convection_getConvectionCoefficient(_convection);
   *wallHeatFlowRate = -HeatFlow_getEnthalpyFlowRate(_wallHeatFlow);

   *pressure = MediumState_p(_pipeState);
   *temperature = MediumState_T(_pipeState);
   *density = MediumState_rho(_pipeState);
   *specificEnthalpy = MediumState_h(_pipeState);
   *gasMassFraction = MediumState_q(_pipeState);
   *superHeat  = MediumState_deltaTSat(_pipeState);
   *internalVolume = PipeHeatExch_C_getVolume(_component);
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *port1FluidStateIndex /= ??; CONVERSION UNKNOWN */
/*   *port1FluidFlowIndex /= ??; CONVERSION UNKNOWN */
/*   *heatFlowIndex /= ??; CONVERSION UNKNOWN */
/*   *thermalNodeIndex /= ??; CONVERSION UNKNOWN */
/*   *port3FluidFlowIndex /= ??; CONVERSION UNKNOWN */
   *pressure /= 1.00000000000000e+005;
   *specificEnthalpy /= 1.00000000000000e+003;
   *internalVolume /= 1.00000000000000e-003;
}

extern double smo_heatexchanger_c_macro0_(int *n
      , double *thermalNodeIndex, double stateValues[2], double rp[6]
      , int ip[2], int ic[2], void *ps[4], int *flag)

{
   double port1FluidStateIndex;
   int loop, logi;
/* >>>>>>>>>>>>Extra Macro Function macro0 Declarations Here. */
/* <<<<<<<<<<<<End of Extra Macro macro0 declarations. */
   int fluidIndex, geometryType;
   double hydraulicDiameter, pipeLength, flowArea, heatExchangeGain, 
      initP, initT;

   fluidIndex = ip[0];
   geometryType = ip[1];

   hydraulicDiameter = rp[0];
   pipeLength = rp[1];
   flowArea   = rp[2];
   heatExchangeGain = rp[3];
   initP      = rp[4];
   initT      = rp[5];
   logi = 0;
   loop = 0;

/* Common -> SI units conversions. */

/*   *thermalNodeIndex *= ??; CONVERSION UNKNOWN */

/*
   Define and return the following macro variable:

   port1FluidStateIndex = ??;
*/


/* >>>>>>>>>>>>Macro Function macro0 Executable Statements. */
   if (firstc_()) {
	   ThermalNode* wallNode = ThermalNode_get(*thermalNodeIndex);
	   PipeHeatExch_C_setWallNode(_component, wallNode);
   }

   PipeHeatExch_C_setStateValues(_component, stateValues[0], stateValues[1]);
   port1FluidStateIndex = _pipeStateIndex;
/* <<<<<<<<<<<<End of Macro macro0 Executable Statements. */

/* SI -> Common units conversions. */

/*   *thermalNodeIndex /= ??; CONVERSION UNKNOWN */

/*   *port1FluidStateIndex /= ??; CONVERSION UNKNOWN */

   return port1FluidStateIndex;
}

