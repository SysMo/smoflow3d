/* Submodel SMO_HEATEXCHANGER_CR skeleton created by AME Submodel editing utility
   Sat Nov 2 11:54:17 2013 */



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

#define _SUBMODELNAME_ "SMO_HEATEXCHANGER_CR"

/* >>>>>>>>>>>>Insert Private Code Here. */
#include "SmoFlowAme.h"
#include "volumes/PipeHeatExchNoPrDropNoMassAcc_CR.h"

#define _component ps[0]
/* <<<<<<<<<<<<End of Private Code. */


/* There is 1 real parameter:

   heatExhcangeEfficienccy heat exchanger efficiency [null]
*/

void smo_heatexchanger_crin_(int *n, double rp[1], void *ps[1])

{
   int loop, error;
/* >>>>>>>>>>>>Extra Initialization Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Initialization declarations. */
   double heatExhcangeEfficienccy;

   heatExhcangeEfficienccy = rp[0];
   loop = 0;
   error = 0;

/*
   If necessary, check values of the following:

   rp[0..0]
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


/* >>>>>>>>>>>>Initialization Function Executable Statements. */
   _component = PipeHeatExchNoPrDropNoMassAcc_CR_new(heatExhcangeEfficienccy);
   SMOCOMPONENT_SET_PROPS(_component)
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

/*  There are 3 ports.

   Port 1 has 2 variables:

      1 outletFluidStateIndexDup     duplicate of outletFluidStateIndex
      2 inletFluidFlowIndex          inlet fluid flow index   [smoFFL] basic variable input  UNPLOTTABLE

   Port 2 has 2 variables:

      1 heatFlowIndex        heat flow index    [smoHFL] basic variable output  UNPLOTTABLE
      2 thermalNodeIndex     thermal node index [smoTHN] basic variable input  UNPLOTTABLE

   Port 3 has 2 variables:

      1 outletFluidFlowIndex      outlet fluid flow index  [smoFFL] basic variable output  UNPLOTTABLE
      2 outletFluidStateIndex     outlet fluid state index [smoTDS] basic variable input  UNPLOTTABLE
*/

/*  There are 5 internal variables.

      1 inletTemperature         inlet temperature       [K]    basic variable
      2 outletTemperature        outlet temperature      [K]    basic variable
      3 wallTemperature          temperature of the wall [K]    basic variable
      4 heatFlowRateFromWall     heat flow rate          [W]    basic variable
      5 massFlowRateInlet        mass flow rate at inlet [kg/s] basic variable
*/

void smo_heatexchanger_cr_(int *n, double *inletFluidFlowIndex
      , double *heatFlowIndex, double *thermalNodeIndex
      , double *outletFluidFlowIndex, double *outletFluidStateIndex
      , double *inletTemperature, double *outletTemperature
      , double *wallTemperature, double *heatFlowRateFromWall
      , double *massFlowRateInlet, double rp[1], void *ps[1]
      , int *flag)

{
   int loop, logi;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
   double T2;
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   double heatExhcangeEfficienccy;

   heatExhcangeEfficienccy = rp[0];
   logi = 0;
   loop = 0;

/* Common -> SI units conversions. */

/*   *inletFluidFlowIndex *= ??; CONVERSION UNKNOWN */
/*   *thermalNodeIndex *= ??; CONVERSION UNKNOWN */
/*   *outletFluidStateIndex *= ??; CONVERSION UNKNOWN */

/*
   Set all submodel outputs below:

   *heatFlowIndex = ??;
   *outletFluidFlowIndex = ??;
   *inletTemperature = ??;
   *outletTemperature = ??;
   *wallTemperature = ??;
   *heatFlowRateFromWall = ??;
   *massFlowRateInlet = ??;
*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
   // Initialization at first run
   if (firstc_()) {
	   PipeHeatExchNoPrDropNoMassAcc_CR_init(_component,
			   ThermalNode_get(*thermalNodeIndex),
			   MediumState_get(*outletFluidStateIndex),
			   FluidFlow_get(*inletFluidFlowIndex));
   }

   PipeHeatExchNoPrDropNoMassAcc_CR_compute(_component);

   *inletTemperature = PipeHeatExchNoPrDropNoMassAcc_CR_getInletTemperature(_component);
   *outletTemperature = PipeHeatExchNoPrDropNoMassAcc_CR_getOutletTemperature(_component);
   *wallTemperature = PipeHeatExchNoPrDropNoMassAcc_CR_getWallTemperature(_component);
   *heatFlowRateFromWall = -PipeHeatExchNoPrDropNoMassAcc_CR_getWallHeatFlowRate(_component);
   *massFlowRateInlet = PipeHeatExchNoPrDropNoMassAcc_CR_getMassFlowRateInlet(_component);

   *outletFluidFlowIndex = PipeHeatExchNoPrDropNoMassAcc_CR_getFluidFlowOutletIndex(_component);
   *heatFlowIndex = PipeHeatExchNoPrDropNoMassAcc_CR_getWallHeatFlowIndex(_component);
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *inletFluidFlowIndex /= ??; CONVERSION UNKNOWN */
/*   *heatFlowIndex /= ??; CONVERSION UNKNOWN */
/*   *thermalNodeIndex /= ??; CONVERSION UNKNOWN */
/*   *outletFluidFlowIndex /= ??; CONVERSION UNKNOWN */
/*   *outletFluidStateIndex /= ??; CONVERSION UNKNOWN */
}

