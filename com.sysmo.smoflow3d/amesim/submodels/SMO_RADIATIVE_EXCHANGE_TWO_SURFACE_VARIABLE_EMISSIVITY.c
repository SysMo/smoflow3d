/* Submodel SMO_RADIATIVE_EXCHANGE_TWO_SURFACE_VARIABLE_EMISSIVITY skeleton created by AME Submodel editing utility
   ?? ??? 26 11:38:31 2021 */



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

#define _SUBMODELNAME_ "SMO_RADIATIVE_EXCHANGE_TWO_SURFACE_VARIABLE_EMISSIVITY"

/* >>>>>>>>>>>>Insert Private Code Here. */
#include "SmoFlowAme.h"
#include "flow/RadiationTwoSurfaces.h"

#define _heatFlow1Index ic[0]
#define _heatFlow1 ps[0]

#define _heatFlow2Index ic[1]
#define _heatFlow2 ps[1]

#define _component ps[2]
/* <<<<<<<<<<<<End of Private Code. */


/* There are 4 real parameters:

   heatExchangeGain  heat exchange gain                                 [null]
   heatExchangeArea1 emitting area of body-1                            [m**2]
   heatExchangeArea2 emitting area of body-2                            [m**2]
   shapeFactor12     shape factor from which surface-1 "sees" surface-2 [null]
*/


/* There are 2 text parameters:

   emissivity1Var emissivity values of body-1
   emissivity2Var emissivity values of body-2
*/

void smo_radiative_exchange_two_surface_variable_emissivityin_(int *n
      , double rp[4], char *tp[2], int ic[3], void *ps[3])

{
   int loop, error;
/* >>>>>>>>>>>>Extra Initialization Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Initialization declarations. */
   double heatExchangeGain, heatExchangeArea1, heatExchangeArea2, 
      shapeFactor12;
   char *emissivity1Var, *emissivity2Var;

   heatExchangeGain = rp[0];
   heatExchangeArea1 = rp[1];
   heatExchangeArea2 = rp[2];
   shapeFactor12 = rp[3];

   emissivity1Var = tp[0];
   emissivity2Var = tp[1];
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


/* >>>>>>>>>>>>Initialization Function Executable Statements. */
	_heatFlow1 = HeatFlow_new();
	_heatFlow1Index = HeatFlow_register(_heatFlow1);

	_heatFlow2 = HeatFlow_new();
	_heatFlow2Index = HeatFlow_register(_heatFlow2);

	_component = RadiationTwoSurfaces_VariableEmissivity_new(
			emissivity1Var, emissivity2Var,
			heatExchangeArea1, heatExchangeArea2,
			shapeFactor12);
	SMOCOMPONENT_SET_PROPS(_component)

	Radiation_setHeatExchangeGain(_component, heatExchangeGain);
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

/*  There are 2 ports.

   Port 1 has 2 variables:

      1 heatFlow1Index        heat flow index (port-1)    [smoHFL] basic variable output  UNPLOTTABLE
      2 thermalNode1Index     thermal node index (port-1) [smoTHN] basic variable input  UNPLOTTABLE

   Port 2 has 2 variables:

      1 heatFlow2Index        heat flow index (port-2)    [smoHFL] basic variable output  UNPLOTTABLE
      2 thermalNode2Index     thermal node index (port-2) [smoTHN] basic variable input  UNPLOTTABLE
*/

/*  There are 3 internal variables.

      1 qDot1           heat flow rate from port-1 [W]    basic variable
      2 emissivity1     emissivity of body-1       [null] basic variable
      3 emissivity2     emissivity of body-2       [null] basic variable
*/

void smo_radiative_exchange_two_surface_variable_emissivity_(int *n
      , double *heatFlow1Index, double *thermalNode1Index
      , double *heatFlow2Index, double *thermalNode2Index
      , double *qDot1, double *emissivity1, double *emissivity2
      , double rp[4], char *tp[2], int ic[3], void *ps[3])

{
   int loop;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   double heatExchangeGain, heatExchangeArea1, heatExchangeArea2, 
      shapeFactor12;
   char *emissivity1Var, *emissivity2Var;

   heatExchangeGain = rp[0];
   heatExchangeArea1 = rp[1];
   heatExchangeArea2 = rp[2];
   shapeFactor12 = rp[3];

   emissivity1Var = tp[0];
   emissivity2Var = tp[1];
   loop = 0;

/* Common -> SI units conversions. */

/*   *thermalNode1Index *= ??; CONVERSION UNKNOWN [smoTHN] */
/*   *thermalNode2Index *= ??; CONVERSION UNKNOWN [smoTHN] */

/*
   Set all submodel outputs below:

   *heatFlow1Index = ??;
   *heatFlow2Index = ??;
   *qDot1      = ??;
   *emissivity1 = ??;
   *emissivity2 = ??;
*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
   SMOCOMPONENT_PRINT_MAIN_CALC
   	if (firstc_()) {
   		ThermalNode* wallNode1 = ThermalNode_get(*thermalNode1Index);
   		ThermalNode* wallNode2 = ThermalNode_get(*thermalNode2Index);
   		RadiationTwoSurfaces_init(_component, wallNode1, wallNode2);
   	}

   	RadiationTwoSurfaces_compute(_component);
   	RadiationTwoSurfaces_updateHeatFlow1(_component, _heatFlow1);
   	RadiationTwoSurfaces_updateHeatFlow2(_component, _heatFlow2);
   	*qDot1 = Radiation_getHeatFlowRate(_component);
   	*emissivity1 = RadiationTwoSurfaces_getEmissivity1(_component);
   	*emissivity2 = RadiationTwoSurfaces_getEmissivity2(_component);

   	*heatFlow1Index = _heatFlow1Index;
   	*heatFlow2Index = _heatFlow2Index;
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *heatFlow1Index /= ??; CONVERSION UNKNOWN [smoHFL] */
/*   *thermalNode1Index /= ??; CONVERSION UNKNOWN [smoTHN] */
/*   *heatFlow2Index /= ??; CONVERSION UNKNOWN [smoHFL] */
/*   *thermalNode2Index /= ??; CONVERSION UNKNOWN [smoTHN] */
}

