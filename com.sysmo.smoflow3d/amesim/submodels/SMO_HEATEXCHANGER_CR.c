/* Submodel SMO_HEATEXCHANGER_CR skeleton created by AME Submodel editing utility
   Thu Sep 19 16:51:43 2013 */



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
#include "volumes/PipeHeatExchNoPrDropNoMassAccCR.h"

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
   SMOCOMPONEN_SET_PROPS(_component)
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

/*  There are 3 ports.

   Port 1 has 2 variables:

      1 stateIndexOutletDup     duplicate of stateIndexOutlet
      2 flowIndexInlet          flow index inlet [smoFFL] basic variable input  UNPLOTTABLE

   Port 2 has 2 variables:

      1 heatFlowIndex        heat flow index    [smoHFL] basic variable output  UNPLOTTABLE
      2 thermalNodeIndex     thermal node index [smoTHN] basic variable input  UNPLOTTABLE

   Port 3 has 2 variables:

      1 flowIndexOutlet      flow index outlet  [smoFFL] basic variable output  UNPLOTTABLE
      2 stateIndexOutlet     state index outlet [smoTDS] basic variable input  UNPLOTTABLE
*/

/*  There are 5 internal variables.

      1 inletTemperature      inlet temperature       [K]    basic variable
      2 outletTemperature     outlet temperature      [K]    basic variable
      3 wallTemperature       temperature of the wall [K]    basic variable
      4 wallHeatFlowRate      heat flow rate at wall  [W]    basic variable
      5 massFlowRateInlet     mass flow rate at inlet [kg/s] basic variable
*/

void smo_heatexchanger_cr_(int *n, double *flowIndexInlet
      , double *heatFlowIndex, double *thermalNodeIndex
      , double *flowIndexOutlet, double *stateIndexOutlet
      , double *inletTemperature, double *outletTemperature
      , double *wallTemperature, double *wallHeatFlowRate
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

/*   *flowIndexInlet *= ??; CONVERSION UNKNOWN */
/*   *thermalNodeIndex *= ??; CONVERSION UNKNOWN */
/*   *stateIndexOutlet *= ??; CONVERSION UNKNOWN */

/*
   Set all submodel outputs below:

   *heatFlowIndex = ??;
   *flowIndexOutlet = ??;
   *inletTemperature = ??;
   *outletTemperature = ??;
   *wallTemperature = ??;
   *wallHeatFlowRate = ??;
   *massFlowRateInlet = ??;
*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
   // Initialization at first run
   if (firstc_()) {
	   PipeHeatExchNoPrDropNoMassAcc_CR_init(_component,
			   ThermalNode_get(*thermalNodeIndex),
			   MediumState_get(*stateIndexOutlet),
			   FluidFlow_get(*flowIndexInlet));
   }

   PipeHeatExchNoPrDropNoMassAcc_CR_compute(_component);

   *inletTemperature = PipeHeatExchNoPrDropNoMassAcc_CR_getInletTemperature(_component);
   *outletTemperature = PipeHeatExchNoPrDropNoMassAcc_CR_getOutletTemperature(_component);
   *wallTemperature = PipeHeatExchNoPrDropNoMassAcc_CR_getWallTemperature(_component);
   *wallHeatFlowRate = PipeHeatExchNoPrDropNoMassAcc_CR_getWallHeatFlowRate(_component);
   *massFlowRateInlet = PipeHeatExchNoPrDropNoMassAcc_CR_getMassFlowRateInlet(_component);

   *flowIndexOutlet = PipeHeatExchNoPrDropNoMassAcc_CR_getFluidFlowOutletIndex(_component);
   *heatFlowIndex = PipeHeatExchNoPrDropNoMassAcc_CR_getWallHeatFlowIndex(_component);
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *flowIndexInlet /= ??; CONVERSION UNKNOWN */
/*   *heatFlowIndex /= ??; CONVERSION UNKNOWN */
/*   *thermalNodeIndex /= ??; CONVERSION UNKNOWN */
/*   *flowIndexOutlet /= ??; CONVERSION UNKNOWN */
/*   *stateIndexOutlet /= ??; CONVERSION UNKNOWN */
}

