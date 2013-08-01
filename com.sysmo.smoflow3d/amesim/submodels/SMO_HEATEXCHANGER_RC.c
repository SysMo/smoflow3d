/* Submodel SMO_HEATEXCHANGER_RC skeleton created by AME Submodel editing utility
   Thu Aug 1 08:35:08 2013 */



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
/* DELME
#include "FluidPoint.h"
#define INLET_NODE ps[0]
#define OUTLET_NODE ps[1]
*/
/* <<<<<<<<<<<<End of Private Code. */


/* There are 3 real parameters:

   initialOutletTemperature initial outlet temperature [K]
   efficienccy              heat exchanger efficiency  [null]
   tauOutput                output time constant       [s]
*/


/* There is 1 integer parameter:

   fluidIndex index of fluid
*/

void smo_heatexchanger_rcin_(int *n, double rp[3], int ip[1]
      , void *ps[10], double *outletComIndex
      , double *outletTemperature)

{
   int loop, error;
/* >>>>>>>>>>>>Extra Initialization Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Initialization declarations. */
   int fluidIndex;
   double initialOutletTemperature, efficienccy, tauOutput;

   fluidIndex = ip[0];

   initialOutletTemperature = rp[0];
   efficienccy = rp[1];
   tauOutput  = rp[2];
   loop = 0;
   error = 0;

/*
   If necessary, check values of the following:

   rp[0..2]
   *outletTemperature
*/

/*
   Check and/or reset the following fixed and/or discrete variable

   *outletComIndex = ??;
*/


/* >>>>>>>>>>>>Initialization Function Check Statements. */
/* <<<<<<<<<<<<End of Initialization Check Statements. */

/*   Integer parameter checking:   */

   if (fluidIndex < 1 || fluidIndex > 99)
   {
      amefprintf(stderr, "\nindex of fluid must be in range [1..99].\n");
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


/* >>>>>>>>>>>>Initialization Function Executable Statements. */
/* DELME
 	AME_SET_CURRENT_COMPONENT;

	INLET_NODE = FluidPoint_new(fluidIndex);

	OUTLET_NODE = FluidPoint_new(fluidIndex);
	FluidPoint* outletNode = (FluidPoint*) OUTLET_NODE;

	*outletTemperature = initialOutletTemperature;
	outletNode->p = 1e6;
	outletNode->T = initialOutletTemperature;
	FluidPoint_init(outletNode, -1, 2);
	*outletComIndex = outletNode->volumeIndex;*/
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

/*  There are 3 ports.

   Port 1 has 5 variables:

      1 inletEnthalpyFlowRate     enthalpy flow rate at inlet [W]           basic variable output
      2 inletMassFlowRate         duplicate of outletMassFlowRate
      3 inletPressure             pressure at inlet           [barA -> PaA] basic variable input
      4 inletDensity              density at inlet            [kg/m**3]     basic variable input
      5 inletComIndex             com index at inlet          [null]        basic variable input  UNPLOTTABLE

   Port 2 has 2 variables:

      1 wallHeatFlowRate     heat flow rate at wall  [W]    basic variable output
      2 wallTemperature      temperature of the wall [degC] basic variable input

   Port 3 has 5 variables:

      1 outletPressure             duplicate of inletPressure   
      2 outletDensity              density at outlet             [kg/m**3] multi line macro 'smo_heatexchanger_rc_macro0_'  UNPLOTTABLE
      3 outletComIndex             communication index at outlet [null]    fixed  UNPLOTTABLE
      4 outletEnthalpyFlowRate     enthalpy flow rate at outlet  [W]       basic variable input
      5 outletMassFlowRate         mass flow rate at outlet      [kg/s]    basic variable input
*/

/*  There are 2 internal variables.

      1 inletTemperature      inlet temperature  [K] basic variable
      2 outletTemperature     outlet temperature [K] explicit state (derivative `outletTemperatureDot')
*/

void smo_heatexchanger_rc_(int *n, double *inletEnthalpyFlowRate
      , double *inletPressure, double *inletDensity
      , double *inletComIndex, double *wallHeatFlowRate
      , double *wallTemperature, double *outletDensity
      , double *outletEnthalpyFlowRate, double *outletMassFlowRate
      , double *inletTemperature, double *outletTemperature
      , double *outletTemperatureDot, double rp[3], int ip[1]
      , void *ps[10], int *flag)

{
   int loop, logi;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
   double T2;
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   int fluidIndex;
   double initialOutletTemperature, efficienccy, tauOutput;

   fluidIndex = ip[0];

   initialOutletTemperature = rp[0];
   efficienccy = rp[1];
   tauOutput  = rp[2];
   logi = 0;
   loop = 0;

/* Common -> SI units conversions. */

   *inletPressure *= 1.00000000000000e+005;

/*
   Set all submodel outputs below:

   *inletEnthalpyFlowRate = ??;
   *wallHeatFlowRate = ??;
   *inletTemperature = ??;
   *outletTemperatureDot = ??;
*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
/* DELME

   // Initialization at first run
   if (firstc_()) {
	   FluidPoint* inletNode = (FluidPoint*) INLET_NODE;
	   FluidPoint_init(inletNode, (int)(*inletComIndex), -1);
   }
   if (*outletMassFlowRate > 0) {
	   raiseError(OUTLET_NODE, "Reverse flow encouuntered. "
			   "Restrict the flow direction, e.g. by adding check valve.");
   }
   T2 = *wallTemperature + 273.15;
   FluidPoint* inletNode = (FluidPoint*) INLET_NODE;
   FluidPoint* outletNode = (FluidPoint*) OUTLET_NODE;
   FluidPoint_computeState_p_rho(inletNode, *inletPressure, *inletDensity);
   FluidPoint_computeState_p_T(outletNode, *inletPressure, *outletTemperature);
   *inletTemperature = inletNode->T;
   double outletTemperatureTarget = inletNode->T +
		   (T2 - inletNode->T) * efficienccy;

   *inletEnthalpyFlowRate = inletNode->h * (*outletMassFlowRate);
   *wallHeatFlowRate = (*outletMassFlowRate) * outletNode->h - (*inletEnthalpyFlowRate);
   *outletTemperatureDot = (outletTemperatureTarget - *outletTemperature)/tauOutput;
*/

/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

   *inletPressure /= 1.00000000000000e+005;
}

extern double smo_heatexchanger_rc_macro0_(int *n
      , double *inletPressure, double *outletTemperature, double rp[3]
      , int ip[1], void *ps[10], int *flag)

{
   double outletDensity;
   int loop, logi;
/* >>>>>>>>>>>>Extra Macro Function macro0 Declarations Here. */
/* <<<<<<<<<<<<End of Extra Macro macro0 declarations. */
   int fluidIndex;
   double initialOutletTemperature, efficienccy, tauOutput;

   fluidIndex = ip[0];

   initialOutletTemperature = rp[0];
   efficienccy = rp[1];
   tauOutput  = rp[2];
   logi = 0;
   loop = 0;

/* Common -> SI units conversions. */

   *inletPressure *= 1.00000000000000e+005;

/*
   Define and return the following macro variable:

   outletDensity = ??;
*/


/* >>>>>>>>>>>>Macro Function macro0 Executable Statements. */
/* DELME
   FluidPoint* outletNode = (FluidPoint*) OUTLET_NODE;
   FluidPoint_computeState_p_T(outletNode, *inletPressure, *outletTemperature);
   outletDensity = outletNode->rho;*/
/* <<<<<<<<<<<<End of Macro macro0 Executable Statements. */

/* SI -> Common units conversions. */

   *inletPressure /= 1.00000000000000e+005;


   return outletDensity;
}

