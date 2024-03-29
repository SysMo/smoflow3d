/* Submodel SMO_R_PIPE_CONSTANT_DRAC_COEFF skeleton created by AME Submodel editing utility
   ???? ??? 15 10:59:58 2019 */



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

#define _SUBMODELNAME_ "SMO_R_PIPE_CONSTANT_DRAC_COEFF"

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

#define _friction ps[3]
/* <<<<<<<<<<<<End of Private Code. */


/* There are 6 real parameters:

   pipeLength          pipe length                 [m]
   hydraulicDiameter   hydraulic diameter          [mm -> m]
   flowArea            flow (cross sectional) area [mm**2 -> m**2]
   absoluteRoughness   absolute roughness          [mm -> m]
   pressureDropGain    pressure drop gain          [null]
   dragCoefficientInit drag coefficient            [null]
*/


/* There is 1 integer parameter:

   computeFrictionalPressureDrop compute frictional pressure drop
*/

void smo_r_pipe_constant_drac_coeffin_(int *n, double rp[6], int ip[1]
      , int ic[3], void *ps[4])

{
   int loop, error;
/* >>>>>>>>>>>>Extra Initialization Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Initialization declarations. */
   int computeFrictionalPressureDrop;
   double pipeLength, hydraulicDiameter, flowArea, absoluteRoughness, 
      pressureDropGain, dragCoefficientInit;

   computeFrictionalPressureDrop = ip[0];

   pipeLength = rp[0];
   hydraulicDiameter = rp[1];
   flowArea   = rp[2];
   absoluteRoughness = rp[3];
   pressureDropGain = rp[4];
   dragCoefficientInit = rp[5];
   loop = 0;
   error = 0;

/*
   If necessary, check values of the following:

   rp[0..5]
*/


/* >>>>>>>>>>>>Initialization Function Check Statements. */
/* <<<<<<<<<<<<End of Initialization Check Statements. */

/*   Integer parameter checking:   */

   if (computeFrictionalPressureDrop < 1 || computeFrictionalPressureDrop > 2)
   {
      amefprintf(stderr, "\ncompute frictional pressure drop must be in range [1..2].\n");
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
   if (computeFrictionalPressureDrop == 1) { //yes
	   _component = ConstantDragCoefficientStraightPipe_new(pipeLength, hydraulicDiameter, flowArea, absoluteRoughness, dragCoefficientInit, pressureDropGain);
   } else { //no
	   _component = ConstantDragCoefficientPipe_new(flowArea, dragCoefficientInit, pressureDropGain);
   }

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

      1 outputRCompID2      R-component ID (output, port2) [smoRCompID] multi line macro 'smo_r_pipe_constant_drac_coeff_macro0_'  UNPLOTTABLE
      2 smoRChainIDDupl     duplicate of smoRChainID      
      3 inputRCompID2       R-component ID (input, port2)  [smoRCompID] basic variable input  UNPLOTTABLE
*/

/*  There are 6 internal variables.

      1 massFlowRate         mass flow rate (port1 -> port3)     [kg/s]      basic variable
      2 enthalpyFlowRate     enthalpy flow rate (port1 -> port3) [W]         basic variable
      3 pressureLoss         total pressure loss                 [bar -> Pa] basic variable
      4 pressureLoss13       pressure loss (port1 - port3)       [bar -> Pa] basic variable
      5 reynoldsNumber       Reynolds number                     [null]      basic variable
      6 dragCoefficient      drag coefficient                    [null]      basic variable
*/

void smo_r_pipe_constant_drac_coeff_(int *n, double *outputRCompID1
      , double *inputRCompID1, double *smoRChainID
      , double *outputRCompID2, double *inputRCompID2
      , double *massFlowRate, double *enthalpyFlowRate
      , double *pressureLoss, double *pressureLoss13
      , double *reynoldsNumber, double *dragCoefficient, double rp[6]
      , int ip[1], int ic[3], void *ps[4])

{
   int loop;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   int computeFrictionalPressureDrop;
   double pipeLength, hydraulicDiameter, flowArea, absoluteRoughness, 
      pressureDropGain, dragCoefficientInit;

   computeFrictionalPressureDrop = ip[0];

   pipeLength = rp[0];
   hydraulicDiameter = rp[1];
   flowArea   = rp[2];
   absoluteRoughness = rp[3];
   pressureDropGain = rp[4];
   dragCoefficientInit = rp[5];
   loop = 0;

/* Common -> SI units conversions. */

/*   *inputRCompID1 *= ??; CONVERSION UNKNOWN [smoRCompID] */
/*   *smoRChainID *= ??; CONVERSION UNKNOWN [smoRChainID] */
/*   *outputRCompID2 *= ??; CONVERSION UNKNOWN [smoRCompID] */
/*   *inputRCompID2 *= ??; CONVERSION UNKNOWN [smoRCompID] */

/*
   Set all submodel outputs below:

   *outputRCompID1 = ??;
   *massFlowRate = ??;
   *enthalpyFlowRate = ??;
   *pressureLoss = ??;
   *pressureLoss13 = ??;
   *reynoldsNumber = ??;
   *dragCoefficient = ??;
*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
   SMOCOMPONENT_PRINT_MAIN_CALC
   if (firstc_()) {
	   ManagerComponents_R_addOuterState2(_manager, *inputRCompID2);
	   _friction = Pipe_R_getFrictionFlowPipe(_component);
   }
   ManagerComponents_R_compute(_manager);

   *massFlowRate = FluidFlow_getMassFlowRate(_fluidFlow2);
   *enthalpyFlowRate = FluidFlow_getEnthalpyFlowRate(_fluidFlow2);
   *pressureLoss = FlowComponent_R_getAbsolutePressureDrop(_component);
   *pressureLoss13 = FlowComponent_R_getPressureDrop12(_component);
   *reynoldsNumber = FrictionFlowPipe_getReynoldsNumber(_friction);
   *dragCoefficient = FrictionFlowPipe_getDragCoefficient(_friction);

   *outputRCompID1 = _componentIndex;
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *outputRCompID1 /= ??; CONVERSION UNKNOWN [smoRCompID] */
/*   *inputRCompID1 /= ??; CONVERSION UNKNOWN [smoRCompID] */
/*   *smoRChainID /= ??; CONVERSION UNKNOWN [smoRChainID] */
/*   *outputRCompID2 /= ??; CONVERSION UNKNOWN [smoRCompID] */
/*   *inputRCompID2 /= ??; CONVERSION UNKNOWN [smoRCompID] */
   *pressureLoss /= 1.00000000000000e+005;
   *pressureLoss13 /= 1.00000000000000e+005;
}

extern double smo_r_pipe_constant_drac_coeff_macro0_(int *n
      , double *inputRCompID1, double *smoRChainID, double rp[6]
      , int ip[1], int ic[3], void *ps[4])

{
   double outputRCompID2;
   int loop;
/* >>>>>>>>>>>>Extra Macro Function macro0 Declarations Here. */
/* <<<<<<<<<<<<End of Extra Macro macro0 declarations. */
   int computeFrictionalPressureDrop;
   double pipeLength, hydraulicDiameter, flowArea, absoluteRoughness, 
      pressureDropGain, dragCoefficientInit;

   computeFrictionalPressureDrop = ip[0];

   pipeLength = rp[0];
   hydraulicDiameter = rp[1];
   flowArea   = rp[2];
   absoluteRoughness = rp[3];
   pressureDropGain = rp[4];
   dragCoefficientInit = rp[5];
   loop = 0;

/* Common -> SI units conversions. */

/*   *inputRCompID1 *= ??; CONVERSION UNKNOWN [smoRCompID] */
/*   *smoRChainID *= ??; CONVERSION UNKNOWN [smoRChainID] */

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

/*   *inputRCompID1 /= ??; CONVERSION UNKNOWN [smoRCompID] */
/*   *smoRChainID /= ??; CONVERSION UNKNOWN [smoRChainID] */

/*   *outputRCompID2 /= ??; CONVERSION UNKNOWN [smoRCompID] */

   return outputRCompID2;
}

