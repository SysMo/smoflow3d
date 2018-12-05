/* Submodel SMO_FREE_CONVECTION skeleton created by AME Submodel editing utility
   Thu Sep 28 11:39:04 2017 */



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
#include "SmoFlowAme.h"
#include "flow/FreeConvection.h"
 
#define _heatFlowIndex ic[0]
#define _heatFlow ps[0]
 
#define _fluidFlowIndex ic[1]
#define _fluidFlow ps[1]
 
#define _component ps[2]
/* <<<<<<<<<<<<End of Private Code. */


/* There are 13 real parameters:

   heatExchangeGain           heat exchange gain                                         [null]
   convectionCoefficientGiven convection coefficient (given)                             [W/m**2/K]
   characteristicLength       characteristic length                                      [m]
   heatExchangeArea           heat exchange area                                         [m**2]
   length                     length                                                     [m]
   height                     height                                                     [m]
   width                      width                                                      [m]
   diameter                   diameter                                                   [m]
   basePipeDiameter           base pipe diameter                                         [m]
   finSpacing                 fin spacing                                                [m]
   finThickness               fin thickness                                              [m]
   finHeight                  fin height                                                 [m]
   angleOfInclination         angle of inclination (top surface > 0, bottom surface < 0) [degree -> rad]
*/


/* There are 3 integer parameters:

   calculationMethod     convection calculation method
   useFilmState          use film state               
   areaCalculationMethod area calculation method      
*/


/* There is 1 text parameter:

   nusseltCorrelationExpr Nusselt correlation expression Nu=f(Ra, Pr)
*/

void smo_free_convectionin_(int *n, double rp[13], int ip[3]
      , char *tp[1], int ic[4], void *ps[4]
      , double *fluidFlowActivationSignal)

{
   int loop, error;
/* >>>>>>>>>>>>Extra Initialization Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Initialization declarations. */
   int calculationMethod, useFilmState, areaCalculationMethod;
   double heatExchangeGain, convectionCoefficientGiven, 
      characteristicLength, heatExchangeArea, length, height, width, 
      diameter, basePipeDiameter, finSpacing, finThickness, finHeight
      , angleOfInclination;
   char *nusseltCorrelationExpr;

   calculationMethod = ip[0];
   useFilmState = ip[1];
   areaCalculationMethod = ip[2];

   heatExchangeGain = rp[0];
   convectionCoefficientGiven = rp[1];
   characteristicLength = rp[2];
   heatExchangeArea = rp[3];
   length     = rp[4];
   height     = rp[5];
   width      = rp[6];
   diameter   = rp[7];
   basePipeDiameter = rp[8];
   finSpacing = rp[9];
   finThickness = rp[10];
   finHeight  = rp[11];
   angleOfInclination = rp[12];

   nusseltCorrelationExpr = tp[0];
   loop = 0;
   error = 0;

/*
   If necessary, check values of the following:

   rp[0..12]
*/

/*
   Check and/or reset the following fixed and/or discrete variable

   *fluidFlowActivationSignal = ??;
*/


/* >>>>>>>>>>>>Initialization Function Check Statements. */
/* <<<<<<<<<<<<End of Initialization Check Statements. */

/*   Integer parameter checking:   */

   if (calculationMethod < 1 || calculationMethod > 10)
   {
      amefprintf(stderr, "\nconvection calculation method must be in range [1..10].\n");
      error = 2;
   }
   if (useFilmState < 1 || useFilmState > 2)
   {
      amefprintf(stderr, "\nuse film state must be in range [1..2].\n");
      error = 2;
   }
   if (areaCalculationMethod < 1 || areaCalculationMethod > 2)
   {
      amefprintf(stderr, "\narea calculation method must be in range [1..2].\n");
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

   rp[12]   *= 1.74532925199433e-002;
   angleOfInclination = rp[12];


/* >>>>>>>>>>>>Initialization Function Executable Statements. */
   _heatFlow = HeatFlow_new();
   _heatFlowIndex = HeatFlow_register(_heatFlow);
 
   _fluidFlow = FluidFlow_new();
   _fluidFlowIndex = FluidFlow_register(_fluidFlow);
 
   if (calculationMethod == 1) {
	   _component = FreeConvection_GivenConvectionCoefficient_new(convectionCoefficientGiven, heatExchangeArea);
   } else if (calculationMethod == 2) {
	   _component = FreeConvection_NusseltExpression_new(characteristicLength, heatExchangeArea, nusseltCorrelationExpr);
   } else if (calculationMethod == 3) {
	   _component = FreeConvection_VerticalSurface_new(height, width);
   } else if (calculationMethod == 4) {
	   _component = FreeConvection_HorizontalSurfaceTop_new(length, width);
   } else if (calculationMethod == 5) {
	   _component = FreeConvection_HorizontalSurfaceBottom_new(length, width);
   } else if (calculationMethod == 6) {
	   if (areaCalculationMethod == 1) {
		   _component = FreeConvection_CylindricalHorizontalSurface_new(length, diameter);
	   } else {
		   _component = FreeConvection_CylindricalHorizontalSurfaceWithArea_new(length, diameter, heatExchangeArea);
	   }
   } else if (calculationMethod == 7) {
	   if (areaCalculationMethod == 1) {
		   _component = FreeConvection_CylindricalVerticalSurface_new(height, diameter);
	   } else {
		   _component = FreeConvection_CylindricalVerticalSurfaceWithArea_new(height, diameter, heatExchangeArea);
	   }
   } else if (calculationMethod == 8) {
	   _component = FreeConvection_SphericalSurface_new(diameter);
   } else if (calculationMethod == 9) {
	   _component = FreeConvection_FinnedPipe_new(length, basePipeDiameter, finSpacing, finThickness, finHeight);
   } else if (calculationMethod == 10) {
	   _component = FreeConvection_InclinedSurface_new(length, width, angleOfInclination);
   }
   SMOCOMPONENT_SET_PROPS(_component)
 
   Convection_setHeatExchangeGain(_component, heatExchangeGain);
   Convection_setUseFilmState(_component, useFilmState - 1); //:TRICKY: 0-no, 1-yes
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

/*  There are 2 ports.

   Port 1 has 2 variables:

      1 heatFlowIndex        heat flow index    [smoHFL] basic variable output  UNPLOTTABLE
      2 thermalNodeIndex     thermal node index [smoTHN] basic variable input  UNPLOTTABLE

   Port 2 has 3 variables:

      1 fluidFlowIndex                fluid flow index             [smoFFL]  basic variable output  UNPLOTTABLE
      2 fluidFlowActivationSignal     fluid flow activation signal [smoFFAS] fixed  UNPLOTTABLE
      3 fluidStateIndex               fluid state index            [smoTDS]  basic variable input  UNPLOTTABLE
*/

/*  There are 4 internal variables.

      1 Ra       Rayleigh number              [null]     basic variable
      2 Nu       Nusselt number               [null]     basic variable
      3 h        convection coefficient       [W/m**2/K] basic variable
      4 qDot     heat flow rate from the wall [W]        basic variable
*/

void smo_free_convection_(int *n, double *heatFlowIndex
      , double *thermalNodeIndex, double *fluidFlowIndex
      , double *fluidStateIndex, double *Ra, double *Nu, double *h
      , double *qDot, double rp[13], int ip[3], char *tp[1], int ic[4]
      , void *ps[4])

{
   int loop;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   int calculationMethod, useFilmState, areaCalculationMethod;
   double heatExchangeGain, convectionCoefficientGiven, 
      characteristicLength, heatExchangeArea, length, height, width, 
      diameter, basePipeDiameter, finSpacing, finThickness, finHeight
      , angleOfInclination;
   char *nusseltCorrelationExpr;

   calculationMethod = ip[0];
   useFilmState = ip[1];
   areaCalculationMethod = ip[2];

   heatExchangeGain = rp[0];
   convectionCoefficientGiven = rp[1];
   characteristicLength = rp[2];
   heatExchangeArea = rp[3];
   length     = rp[4];
   height     = rp[5];
   width      = rp[6];
   diameter   = rp[7];
   basePipeDiameter = rp[8];
   finSpacing = rp[9];
   finThickness = rp[10];
   finHeight  = rp[11];
   angleOfInclination = rp[12];

   nusseltCorrelationExpr = tp[0];
   loop = 0;

/* Common -> SI units conversions. */

/*   *thermalNodeIndex *= ??; CONVERSION UNKNOWN [smoTHN] */
/*   *fluidStateIndex *= ??; CONVERSION UNKNOWN [smoTDS] */

/*
   Set all submodel outputs below:

   *heatFlowIndex = ??;
   *fluidFlowIndex = ??;
   *Ra         = ??;
   *Nu         = ??;
   *h          = ??;
   *qDot       = ??;
*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
   SMOCOMPONENT_PRINT_MAIN_CALC
   if (firstc_()) {
	   MediumState* fluidState = MediumState_get(*fluidStateIndex);
	   ThermalNode* wallNode = ThermalNode_get(*thermalNodeIndex);
	   FreeConvection_init(_component, fluidState, wallNode);
   }
 
   FreeConvection_compute(_component);
   Convection_updateFluidFlow(_component, _fluidFlow);
   Convection_updateHeatFlow(_component, _heatFlow);
   *Ra = FreeConvection_getRayleighNumber(_component);
   *Nu = Convection_getNusseltNumber(_component);
   *h = Convection_getConvectionCoefficient(_component);
   *qDot = Convection_getHeatFlowRate(_component);
 
   *fluidFlowIndex = _fluidFlowIndex;
   *heatFlowIndex = _heatFlowIndex;
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *heatFlowIndex /= ??; CONVERSION UNKNOWN [smoHFL] */
/*   *thermalNodeIndex /= ??; CONVERSION UNKNOWN [smoTHN] */
/*   *fluidFlowIndex /= ??; CONVERSION UNKNOWN [smoFFL] */
/*   *fluidStateIndex /= ??; CONVERSION UNKNOWN [smoTDS] */
}

