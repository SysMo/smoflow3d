/* Submodel SMO_R_ORIFICE_COMPRESSIBLE_IDEAL_GAS skeleton created by AME Submodel editing utility
   Thu Mar 16 11:19:11 2017 */



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

#define _SUBMODELNAME_ "SMO_R_ORIFICE_COMPRESSIBLE_IDEAL_GAS"

/* >>>>>>>>>>>>Insert Private Code Here. */
#include "SmoFlowAme.h"
#include "flow_R/Valve_R.h"
#include "flow_R/ManagerComponents_R.h"

#define _component ps[0]
#define _componentIndex ic[0]

#define _manager ps[1]
#define _managerIndex ic[1]

#define _fluidFlow1 ps[2]
#define _fluidFlow1Index ic[2]

#define _fluidFlow2 ps[3]
#define _fluidFlow2Index ic[3]
/* <<<<<<<<<<<<End of Private Code. */


/* There are 2 real parameters:

   orificeArea      orifice area    [mm**2 -> m**2]
   flowCoefficient flow coefficient [null]
*/


/* There is 1 integer parameter:

   allowBidirectionalFlow allow bi-directional flow
*/

void smo_r_orifice_compressible_ideal_gasin_(int *n, double rp[2]
      , int ip[1], int ic[4], void *ps[4])

{
   int loop, error;
/* >>>>>>>>>>>>Extra Initialization Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Initialization declarations. */
   int allowBidirectionalFlow;
   double orificeArea, flowCoefficient;

   allowBidirectionalFlow = ip[0];

   orificeArea = rp[0];
   flowCoefficient = rp[1];
   loop = 0;
   error = 0;

/*
   If necessary, check values of the following:

   rp[0..1]
*/


/* >>>>>>>>>>>>Initialization Function Check Statements. */
/* <<<<<<<<<<<<End of Initialization Check Statements. */

/*   Integer parameter checking:   */

   if (allowBidirectionalFlow < 1 || allowBidirectionalFlow > 2)
   {
      amefprintf(stderr, "\nallow bi-directional flow must be in range [1..2].\n");
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

   rp[0]    *= 1.00000000000000e-006;
   orificeArea = rp[0];


/* >>>>>>>>>>>>Initialization Function Executable Statements. */
	_component = Valve_OrificeCompressibleIdealGas_R_new(
		   allowBidirectionalFlow - 1, //:TRICKY: allowBidirectionalFlow =  '{1-no, 2-yes} - 1'  =  '{0-no, 1-yes}'
		   orificeArea,
		   flowCoefficient);
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

   Port 2 has 1 variable:

      1 regulatingSignal     regulating signal [null] basic variable input

   Port 3 has 3 variables:

      1 outputRCompID3      R-component ID (output, port3) [smoRCompID] multi line macro 'smo_r_orifice_compressible_ideal_gas_macro0_'  UNPLOTTABLE
      2 smoRChainIDDupl     duplicate of smoRChainID      
      3 inputRCompID3       R-component ID (input, port3)  [smoRCompID] basic variable input  UNPLOTTABLE
*/

/*  There are 4 internal variables.

      1 massFlowRate         mass flow rate                        [kg/s]      basic variable
      2 enthalpyFlowRate     enthalpy flow rate                    [W]         basic variable
      3 pressureLoss         total pressure loss                   [bar -> Pa] basic variable
      4 flowType             flow type = {0 - subsonic, 1 - sonic} [null]      basic variable
*/

void smo_r_orifice_compressible_ideal_gas_(int *n
      , double *outputRCompID1, double *inputRCompID1
      , double *smoRChainID, double *regulatingSignal
      , double *outputRCompID3, double *inputRCompID3
      , double *massFlowRate, double *enthalpyFlowRate
      , double *pressureLoss, double *flowType, double rp[2]
      , int ip[1], int ic[4], void *ps[4], int *flag)

{
   int loop, logi;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   int allowBidirectionalFlow;
   double orificeArea, flowCoefficient;

   allowBidirectionalFlow = ip[0];

   orificeArea = rp[0];
   flowCoefficient = rp[1];
   logi = 0;
   loop = 0;

/* Common -> SI units conversions. */

/*   *inputRCompID1 *= ??; CONVERSION UNKNOWN [smoRCompID] */
/*   *smoRChainID *= ??; CONVERSION UNKNOWN [smoRChainID] */
/*   *outputRCompID3 *= ??; CONVERSION UNKNOWN [smoRCompID] */
/*   *inputRCompID3 *= ??; CONVERSION UNKNOWN [smoRCompID] */

/*
   Set all submodel outputs below:

   *outputRCompID1 = ??;
   *massFlowRate = ??;
   *enthalpyFlowRate = ??;
   *pressureLoss = ??;
   *flowType   = ??;
*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
	SMOCOMPONENT_PRINT_MAIN_CALC
	if (firstc_()) {
		ManagerComponents_R_addOuterState2(_manager, *inputRCompID3);
	}
	ManagerComponents_R_compute(_manager);

	*massFlowRate = FluidFlow_getMassFlowRate(_fluidFlow2);
	*enthalpyFlowRate = FluidFlow_getEnthalpyFlowRate(_fluidFlow2);
	*pressureLoss = FlowComponent_R_getAbsolutePressureDrop(_component);
	*flowType = Valve_R_getFlowType(_component);

	*outputRCompID1 = _componentIndex;
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *outputRCompID1 /= ??; CONVERSION UNKNOWN [smoRCompID] */
/*   *inputRCompID1 /= ??; CONVERSION UNKNOWN [smoRCompID] */
/*   *smoRChainID /= ??; CONVERSION UNKNOWN [smoRChainID] */
/*   *outputRCompID3 /= ??; CONVERSION UNKNOWN [smoRCompID] */
/*   *inputRCompID3 /= ??; CONVERSION UNKNOWN [smoRCompID] */
   *pressureLoss /= 1.00000000000000e+005;
}

extern double smo_r_orifice_compressible_ideal_gas_macro0_(int *n
      , double *inputRCompID1, double *smoRChainID
      , double *regulatingSignal, double rp[2], int ip[1], int ic[4]
      , void *ps[4], int *flag)

{
   double outputRCompID3;
   int loop, logi;
/* >>>>>>>>>>>>Extra Macro Function macro0 Declarations Here. */
/* <<<<<<<<<<<<End of Extra Macro macro0 declarations. */
   int allowBidirectionalFlow;
   double orificeArea, flowCoefficient;

   allowBidirectionalFlow = ip[0];

   orificeArea = rp[0];
   flowCoefficient = rp[1];
   logi = 0;
   loop = 0;

/* Common -> SI units conversions. */

/*   *inputRCompID1 *= ??; CONVERSION UNKNOWN [smoRCompID] */
/*   *smoRChainID *= ??; CONVERSION UNKNOWN [smoRChainID] */

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
	}
	//ValveRegSignal_R_setRegulatingSignal(_component, *regulatingSignal);

	outputRCompID3 = _componentIndex;
/* <<<<<<<<<<<<End of Macro macro0 Executable Statements. */

/* SI -> Common units conversions. */

/*   *inputRCompID1 /= ??; CONVERSION UNKNOWN [smoRCompID] */
/*   *smoRChainID /= ??; CONVERSION UNKNOWN [smoRChainID] */

/*   *outputRCompID3 /= ??; CONVERSION UNKNOWN [smoRCompID] */

   return outputRCompID3;
}

