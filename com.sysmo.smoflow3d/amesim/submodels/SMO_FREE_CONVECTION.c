/* Submodel SMO_FREE_CONVECTION skeleton created by AME Submodel editing utility
   Sun Aug 11 18:31:06 2013 */



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

#define _SUBMODELNAME_ "SMO_FREE_CONVECTION"

/* >>>>>>>>>>>>Insert Private Code Here. */
#include "flow/FreeConvection.h"

#define _heatFlowIndex ic[0]
#define _heatFlow ps[0]

#define _fluidFlowIndex ic[1]
#define _fluidFlow ps[1]

#define _freeConvection ps[2]
/* <<<<<<<<<<<<End of Private Code. */


/* There are 8 real parameters:

   heatExchangeGain           heat exchange gain             [null]
   convectionCoefficientGiven convection coefficient (given) [W/m**2/K]
   characteristicLength       characteristic length          [m]
   heatExchangeArea           heat exchange area             [m**2]
   length                     length                         [m]
   height                     height                         [m]
   width                      width                          [m]
   cylinderDiameter           cylinder diameter              [m]
*/


/* There is 1 integer parameter:

   calculationMethod covection calculation method
*/


/* There is 1 text parameter:

   nusseltCorrelationExpr nusselt correlation expression Nu=f(Ra, Pr)
*/

void smo_free_convectionin_(int *n, double rp[8], int ip[1]
      , char *tp[1], int ic[4], void *ps[4])

{
   int loop, error;
/* >>>>>>>>>>>>Extra Initialization Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Initialization declarations. */
   int calculationMethod;
   double heatExchangeGain, convectionCoefficientGiven, 
      characteristicLength, heatExchangeArea, length, height, width, 
      cylinderDiameter;
   char *nusseltCorrelationExpr;

   calculationMethod = ip[0];

   heatExchangeGain = rp[0];
   convectionCoefficientGiven = rp[1];
   characteristicLength = rp[2];
   heatExchangeArea = rp[3];
   length     = rp[4];
   height     = rp[5];
   width      = rp[6];
   cylinderDiameter = rp[7];

   nusseltCorrelationExpr = tp[0];
   loop = 0;
   error = 0;

/*
   If necessary, check values of the following:

   rp[0..7]
*/


/* >>>>>>>>>>>>Initialization Function Check Statements. */
/* <<<<<<<<<<<<End of Initialization Check Statements. */

/*   Integer parameter checking:   */

   if (calculationMethod < 1 || calculationMethod > 6)
   {
      amefprintf(stderr, "\ncovection calculation method must be in range [1..6].\n");
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
   _heatFlow = HeatFlow_new();
   _heatFlowIndex = HeatFlow_register(_heatFlow);

   _fluidFlow = FluidFlow_new();
   _fluidFlowIndex = FluidFlow_register(_fluidFlow);
   FreeConvectionModel* convectionModel = NULL;

   if (calculationMethod == 1) {

   } else if (calculationMethod == 2) {
	   convectionModel =
			   FreeConvectionModel_NusseltExpression_new(
					   characteristicLength, heatExchangeArea, nusseltCorrelationExpr);
   } else if (calculationMethod == 3) {
	   convectionModel =
			   FreeConvectionModel_VerticalSurface_new(height, width);
   } else if (calculationMethod == 4) {
	   convectionModel =
			   FreeConvectionModel_HorizontalSurfaceTop_new(length, width);
   } else if (calculationMethod == 5) {
	   convectionModel =
			   FreeConvectionModel_HorizontalSurfaceBottom_new(length, width);
   } else if (calculationMethod == 6) {
	   convectionModel =
			   FreeConvectionModel_CylindricalHorizontalSurface_new(
					   length, cylinderDiameter);
   }

   _freeConvection = FreeConvection_new(convectionModel);
   if (calculationMethod == 1) {
	   FreeConvection_setParametersDirectly(_freeConvection, heatExchangeArea, convectionCoefficientGiven);
   }
   FreeConvection_setHeatExchangeGain(_freeConvection, heatExchangeGain);
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

/*  There are 2 ports.

   Port 1 has 2 variables:

      1 heatFlowIndex        heat flow index    [smoHFL] basic variable output  UNPLOTTABLE
      2 thermalNodeIndex     thermal node index [smoTHN] basic variable input  UNPLOTTABLE

   Port 2 has 2 variables:

      1 flowIndex      flow index  [smoFFL] basic variable output  UNPLOTTABLE
      2 stateIndex     state index [smoTDS] basic variable input  UNPLOTTABLE
*/

/*  There are 4 internal variables.

      1 Ra       Rayleigh number        [null]     basic variable
      2 Nu       Nusselt number         [null]     basic variable
      3 h        convection coefficient [W/m**2/K] basic variable
      4 qDot     heat flow rate         [W]        basic variable
*/

void smo_free_convection_(int *n, double *heatFlowIndex
      , double *thermalNodeIndex, double *flowIndex
      , double *stateIndex, double *Ra, double *Nu, double *h
      , double *qDot, double rp[8], int ip[1], char *tp[1], int ic[4]
      , void *ps[4])

{
   int loop;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   int calculationMethod;
   double heatExchangeGain, convectionCoefficientGiven, 
      characteristicLength, heatExchangeArea, length, height, width, 
      cylinderDiameter;
   char *nusseltCorrelationExpr;

   calculationMethod = ip[0];

   heatExchangeGain = rp[0];
   convectionCoefficientGiven = rp[1];
   characteristicLength = rp[2];
   heatExchangeArea = rp[3];
   length     = rp[4];
   height     = rp[5];
   width      = rp[6];
   cylinderDiameter = rp[7];

   nusseltCorrelationExpr = tp[0];
   loop = 0;

/* Common -> SI units conversions. */

/*   *thermalNodeIndex *= ??; CONVERSION UNKNOWN */
/*   *stateIndex *= ??; CONVERSION UNKNOWN */

/*
   Set all submodel outputs below:

   *heatFlowIndex = ??;
   *flowIndex  = ??;
   *Ra         = ??;
   *Nu         = ??;
   *h          = ??;
   *qDot       = ??;
*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
   if (firstc_()) {
	   MediumState* fluidState = MediumState_get(*stateIndex);
	   ThermalNode* wallNode = ThermalNode_get(*thermalNodeIndex);
	   FreeConvection_init(_freeConvection, fluidState, wallNode);
   }

   FreeConvection_compute(_freeConvection);
   FreeConvection_getFlow_Fluid(_freeConvection, _fluidFlow);
   FreeConvection_getFlow_Wall(_freeConvection, _heatFlow);
   *Ra = FreeConvection_getRayleighNumber(_freeConvection);
   *Nu = FreeConvection_getNusseltNumber(_freeConvection);
   *h = FreeConvection_getConvectionCoefficient(_freeConvection);
   *qDot = FreeConvection_getHeatFlowRate(_freeConvection);

   *flowIndex = _fluidFlowIndex;
   *heatFlowIndex = _heatFlowIndex;
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *heatFlowIndex /= ??; CONVERSION UNKNOWN */
/*   *thermalNodeIndex /= ??; CONVERSION UNKNOWN */
/*   *flowIndex /= ??; CONVERSION UNKNOWN */
/*   *stateIndex /= ??; CONVERSION UNKNOWN */
}

