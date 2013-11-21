/* Submodel SMO_R_PIPE_STRAIGHT skeleton created by AME Submodel editing utility
   Fri Nov 15 11:20:38 2013 */



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

#define _SUBMODELNAME_ "SMO_R_PIPE_STRAIGHT"

/* >>>>>>>>>>>>Insert Private Code Here. */
#include "SmoFlowAme.h"
#include "flow_R/Pipe_R.h"
#include "flow_R/ManagerComponents_R.h"

#define _component ps[0]
#define _componentIndex ic[0]

#define _manager ps[1]
#define _managerIndex ic[1]

#define _fluidFlow2 ps[2]
#define _fluidFlow2Index ic[2]
/* <<<<<<<<<<<<End of Private Code. */


/* There are 4 real parameters:

   hydraulicDiameter hydraulic diameter [mm -> m]
   pipeLength        pipe length        [m]
   absoluteRoughness absolute roughness [mm -> m]
   pressureDropGain  pressure drop gain [null]
*/

void smo_r_pipe_straightin_(int *n, double rp[4], int ic[3]
      , void *ps[3])

{
   int loop, error;
/* >>>>>>>>>>>>Extra Initialization Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Initialization declarations. */
   double hydraulicDiameter, pipeLength, absoluteRoughness, 
      pressureDropGain;

   hydraulicDiameter = rp[0];
   pipeLength = rp[1];
   absoluteRoughness = rp[2];
   pressureDropGain = rp[3];
   loop = 0;
   error = 0;

/*
   If necessary, check values of the following:

   rp[0..3]
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

/* Common -> SI units conversions. */

   rp[0]    *= 1.00000000000000e-003;
   hydraulicDiameter = rp[0];
   rp[2]    *= 1.00000000000000e-003;
   absoluteRoughness = rp[2];


/* >>>>>>>>>>>>Initialization Function Executable Statements. */
   _component = CylindricalStraightPipe_R_new(
		   pipeLength,
		   hydraulicDiameter,
		   absoluteRoughness,
		   pressureDropGain);
   _componentIndex = Component_R_register(_component);
   SMOCOMPONENT_SET_PROPS(_component)

   _fluidFlow2Index = FlowComponent_R_getFlow2Index(_component);
   _fluidFlow2 = FluidFlow_get(_fluidFlow2Index);
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

/*  There are 2 ports.

   Port 1 has 3 variables:

      1 outputRCompID1     R-component ID (ouput, port1) [smoRCompID]  basic variable output  UNPLOTTABLE
      2 inputRCompID1      R-component ID (input, port1) [smoRCompID]  basic variable input  UNPLOTTABLE
      3 smoRChainID        R-components chain ID         [smoRChainID] basic variable input  UNPLOTTABLE

   Port 2 has 3 variables:

      1 outputRCompID2      R-component ID (output, port2) [smoRCompID] multi line macro 'smo_r_pipe_straight_macro0_'  UNPLOTTABLE
      2 smoRChainIDDupl     duplicate of smoRChainID      
      3 inputRCompID2       R-component ID (input, port2)  [smoRCompID] basic variable input  UNPLOTTABLE
*/

/*  There are 3 internal variables.

      1 massFlowRate         mass flow rate (at port3)     [kg/s]      basic variable
      2 enthalpyFlowRate     enthalpy flow rate (at port3) [W]         basic variable
      3 pressureLoss         total pressure loss           [bar -> Pa] basic variable
*/

void smo_r_pipe_straight_(int *n, double *outputRCompID1
      , double *inputRCompID1, double *smoRChainID
      , double *outputRCompID2, double *inputRCompID2
      , double *massFlowRate, double *enthalpyFlowRate
      , double *pressureLoss, double rp[4], int ic[3], void *ps[3])

{
   int loop;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   double hydraulicDiameter, pipeLength, absoluteRoughness, 
      pressureDropGain;

   hydraulicDiameter = rp[0];
   pipeLength = rp[1];
   absoluteRoughness = rp[2];
   pressureDropGain = rp[3];
   loop = 0;

/* Common -> SI units conversions. */

/*   *inputRCompID1 *= ??; CONVERSION UNKNOWN */
/*   *smoRChainID *= ??; CONVERSION UNKNOWN */
/*   *outputRCompID2 *= ??; CONVERSION UNKNOWN */
/*   *inputRCompID2 *= ??; CONVERSION UNKNOWN */

/*
   Set all submodel outputs below:

   *outputRCompID1 = ??;
   *massFlowRate = ??;
   *enthalpyFlowRate = ??;
   *pressureLoss = ??;
*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
   SMOCOMPONENT_PRINT_MAIN_CALC
   if (firstc_()) {
	   ManagerComponents_R_addOuterState2(_manager, *inputRCompID2);
   }
   ManagerComponents_R_compute(_manager);

   *massFlowRate = FluidFlow_getMassFlowRate(_fluidFlow2);
   *enthalpyFlowRate = FluidFlow_getEnthalpyFlowRate(_fluidFlow2);
   *pressureLoss = FlowComponent_R_getAbsolutePressureDrop(_component);

   *outputRCompID1 = _componentIndex;
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *outputRCompID1 /= ??; CONVERSION UNKNOWN */
/*   *inputRCompID1 /= ??; CONVERSION UNKNOWN */
/*   *smoRChainID /= ??; CONVERSION UNKNOWN */
/*   *outputRCompID2 /= ??; CONVERSION UNKNOWN */
/*   *inputRCompID2 /= ??; CONVERSION UNKNOWN */
   *pressureLoss /= 1.00000000000000e+005;
}

extern double smo_r_pipe_straight_macro0_(int *n
      , double *inputRCompID1, double *smoRChainID, double rp[4]
      , int ic[3], void *ps[3])

{
   double outputRCompID2;
   int loop;
/* >>>>>>>>>>>>Extra Macro Function macro0 Declarations Here. */
/* <<<<<<<<<<<<End of Extra Macro macro0 declarations. */
   double hydraulicDiameter, pipeLength, absoluteRoughness, 
      pressureDropGain;

   hydraulicDiameter = rp[0];
   pipeLength = rp[1];
   absoluteRoughness = rp[2];
   pressureDropGain = rp[3];
   loop = 0;

/* Common -> SI units conversions. */

/*   *inputRCompID1 *= ??; CONVERSION UNKNOWN */
/*   *smoRChainID *= ??; CONVERSION UNKNOWN */

/*
   Define and return the following macro variable:

   outputRCompID2 = ??;
*/


/* >>>>>>>>>>>>Macro Function macro0 Executable Statements. */
   SMOCOMPONENt_PRINT_MACRO_MSG("outputRCompID3")
   if (firstc_()) {
	   _managerIndex = *smoRChainID;
	   _manager = ManagerComponents_R_get(_managerIndex);

	   ManagerComponents_R_addComponent(_manager, _component, *inputRCompID1);
   }

   outputRCompID2 = _componentIndex;
/* <<<<<<<<<<<<End of Macro macro0 Executable Statements. */

/* SI -> Common units conversions. */

/*   *inputRCompID1 /= ??; CONVERSION UNKNOWN */
/*   *smoRChainID /= ??; CONVERSION UNKNOWN */

/*   *outputRCompID2 /= ??; CONVERSION UNKNOWN */

   return outputRCompID2;
}

