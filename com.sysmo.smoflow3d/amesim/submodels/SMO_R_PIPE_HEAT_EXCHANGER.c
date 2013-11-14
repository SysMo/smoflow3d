/* Submodel SMO_R_PIPE_HEAT_EXCHANGER skeleton created by AME Submodel editing utility
   Thu Nov 14 18:45:47 2013 */



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

#define _SUBMODELNAME_ "SMO_R_PIPE_HEAT_EXCHANGER"

/* >>>>>>>>>>>>Insert Private Code Here. */
#include "SmoFlowAme.h"
#include "flow_R/Pipe_R.h"
#include "flow_R/ManagerComponents_R.h"

#define _component ps[0]
#define _componentIndex ic[0]

#define _manager ps[1]
#define _managerIndex ic[1]

#define _wallHeatFlow ps[2]
#define _wallHeatFlowIndex ic[2]
/* <<<<<<<<<<<<End of Private Code. */


/* There are 6 real parameters:

   hydraulicDiameter hydraulic diameter          [mm -> m]
   pipeLength        pipe length                 [m]
   flowArea          flow (cross sectional) area [mm**2 -> m**2]
   absoluteRoughness absolute roughness          [mm -> m]
   pressureDropGain  pressure drop gain          [null]
   heatExchangeGain  heat exchange gain          [null]
*/


/* There is 1 integer parameter:

   geometryType geometry type
*/

void smo_r_pipe_heat_exchangerin_(int *n, double rp[6], int ip[1]
      , int ic[3], void *ps[3], double stateValues[2])

{
   int loop, error;
/* >>>>>>>>>>>>Extra Initialization Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Initialization declarations. */
   int geometryType;
   double hydraulicDiameter, pipeLength, flowArea, absoluteRoughness, 
      pressureDropGain, heatExchangeGain;

   geometryType = ip[0];

   hydraulicDiameter = rp[0];
   pipeLength = rp[1];
   flowArea   = rp[2];
   absoluteRoughness = rp[3];
   pressureDropGain = rp[4];
   heatExchangeGain = rp[5];
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


/* >>>>>>>>>>>>Initialization Function Executable Statements. */
   if (geometryType == 1) {
	   _component = CylindricalStraightPipeHeatExchanger_R_new(
			   hydraulicDiameter,
			   pipeLength,
			   absoluteRoughness,
			   pressureDropGain,
			   heatExchangeGain,
			   0 //heatExchangerLimitOutput (0-no, 1-yes)
	   );
   } else {
	   _component = NonCylindricalStraightPipeHeatExchanger_R_new(
			   hydraulicDiameter,
			   pipeLength,
			   flowArea,
			   absoluteRoughness,
			   pressureDropGain,
			   heatExchangeGain,
			   0 //heatExchangerLimitOutput (0-no, 1-yes)
	   );
   }
   _componentIndex = Component_R_register(_component);
   SMOCOMPONENT_SET_PROPS(_component)
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

      1 outputRCompID3      R-component ID (output, port3) [smoRCompID] multi line macro 'smo_r_pipe_heat_exchanger_macro0_'  UNPLOTTABLE
      2 smoRChainIDDupl     duplicate of smoRChainID      
      3 inputRCompID3       R-component ID (input, port3)  [smoRCompID] basic variable input  UNPLOTTABLE
*/

/*  There are 7 internal variables.

      1 port1Temperature          port 1 temperature     [K]         basic variable
      2 port3Temperature          port 3 temperature     [K]         basic variable
      3 stateValues[2]            state values           [null]      explicit state (derivative `stateValuesDot')
      4 reynoldsNumber            Reynolds number        [null]      basic variable
      5 convectionCoefficient     convection coefficient [W/m**2/K]  basic variable
      6 heatFlowRateFromWall      heat flow rate         [W]         basic variable
      7 totalPressureLoss         total pressure loss    [bar -> Pa] basic variable
*/

void smo_r_pipe_heat_exchanger_(int *n, double *outputRCompID1
      , double *inputRCompID1, double *smoRChainID
      , double *heatFlowIndex, double *thermalNodeIndex
      , double *outputRCompID3, double *inputRCompID3
      , double *port1Temperature, double *port3Temperature
      , double stateValues[2], double stateValuesDot[2]
      , double *reynoldsNumber, double *convectionCoefficient
      , double *heatFlowRateFromWall, double *totalPressureLoss
      , double rp[6], int ip[1], int ic[3], void *ps[3], int *flag)

{
   int loop, logi;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   int geometryType;
   double hydraulicDiameter, pipeLength, flowArea, absoluteRoughness, 
      pressureDropGain, heatExchangeGain;

   geometryType = ip[0];

   hydraulicDiameter = rp[0];
   pipeLength = rp[1];
   flowArea   = rp[2];
   absoluteRoughness = rp[3];
   pressureDropGain = rp[4];
   heatExchangeGain = rp[5];
   logi = 0;
   loop = 0;

/* Common -> SI units conversions. */

/*   *inputRCompID1 *= ??; CONVERSION UNKNOWN */
/*   *smoRChainID *= ??; CONVERSION UNKNOWN */
/*   *thermalNodeIndex *= ??; CONVERSION UNKNOWN */
/*   *outputRCompID3 *= ??; CONVERSION UNKNOWN */
/*   *inputRCompID3 *= ??; CONVERSION UNKNOWN */

/*
   Set all submodel outputs below:

   *outputRCompID1 = ??;
   *heatFlowIndex = ??;
   *port1Temperature = ??;
   *port3Temperature = ??;
   stateValuesDot[0..1] = ??;
   *reynoldsNumber = ??;
   *convectionCoefficient = ??;
   *heatFlowRateFromWall = ??;
   *totalPressureLoss = ??;
*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *outputRCompID1 /= ??; CONVERSION UNKNOWN */
/*   *inputRCompID1 /= ??; CONVERSION UNKNOWN */
/*   *smoRChainID /= ??; CONVERSION UNKNOWN */
/*   *heatFlowIndex /= ??; CONVERSION UNKNOWN */
/*   *thermalNodeIndex /= ??; CONVERSION UNKNOWN */
/*   *outputRCompID3 /= ??; CONVERSION UNKNOWN */
/*   *inputRCompID3 /= ??; CONVERSION UNKNOWN */
   *totalPressureLoss /= 1.00000000000000e+005;
}

extern double smo_r_pipe_heat_exchanger_macro0_(int *n
      , double *inputRCompID1, double *smoRChainID
      , double *thermalNodeIndex, double rp[6], int ip[1], int ic[3]
      , void *ps[3], int *flag)

{
   double outputRCompID3;
   int loop, logi;
/* >>>>>>>>>>>>Extra Macro Function macro0 Declarations Here. */
/* <<<<<<<<<<<<End of Extra Macro macro0 declarations. */
   int geometryType;
   double hydraulicDiameter, pipeLength, flowArea, absoluteRoughness, 
      pressureDropGain, heatExchangeGain;

   geometryType = ip[0];

   hydraulicDiameter = rp[0];
   pipeLength = rp[1];
   flowArea   = rp[2];
   absoluteRoughness = rp[3];
   pressureDropGain = rp[4];
   heatExchangeGain = rp[5];
   logi = 0;
   loop = 0;

/* Common -> SI units conversions. */

/*   *inputRCompID1 *= ??; CONVERSION UNKNOWN */
/*   *smoRChainID *= ??; CONVERSION UNKNOWN */
/*   *thermalNodeIndex *= ??; CONVERSION UNKNOWN */

/*
   Define and return the following macro variable:

   outputRCompID3 = ??;
*/


/* >>>>>>>>>>>>Macro Function macro0 Executable Statements. */
   SMOCOMPONENt_PRINT_MACRO_MSG("state2")
   if (firstc_()) {
	   _managerIndex = *smoRChainID;
	   _manager = ManagerComponents_R_get(_managerIndex);

	   ManagerComponents_R_addComponent(_manager, _component, *inputRCompID1);
   }
   //Valve_R_setRegulatingSignal(_component, *regulatingSignal); //SMO_WORK

   outputRCompID3 = _componentIndex;
/* <<<<<<<<<<<<End of Macro macro0 Executable Statements. */

/* SI -> Common units conversions. */

/*   *inputRCompID1 /= ??; CONVERSION UNKNOWN */
/*   *smoRChainID /= ??; CONVERSION UNKNOWN */
/*   *thermalNodeIndex /= ??; CONVERSION UNKNOWN */

/*   *outputRCompID3 /= ??; CONVERSION UNKNOWN */

   return outputRCompID3;
}

