/* Submodel SMO_THERMAL_CONDUCTION skeleton created by AME Submodel editing utility
   Thu Sep 19 17:48:19 2013 */



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

#define _SUBMODELNAME_ "SMO_THERMAL_CONDUCTION"

/* >>>>>>>>>>>>Insert Private Code Here. */
#include "SmoFlowAme.h"
#include "flow/ThermalConductionElement.h"

#define _component ps[0]

#define _heatFlow1 ps[1]
#define _heatFlow1Index ic[1]

#define _heatFlow2 ps[2]
#define _heatFlow2Index ic[2]
/* <<<<<<<<<<<<End of Private Code. */


/* There are 2 real parameters:

   conductionArea   conduction area   [mm**2 -> m**2]
   conductionLength conduction length [mm -> m]
*/


/* There are 2 integer parameters:

   conductionType conduction type
   materialIndex  material  index
*/

void smo_thermal_conductionin_(int *n, double rp[2], int ip[2]
      , int ic[3], void *ps[3])

{
   int loop, error;
/* >>>>>>>>>>>>Extra Initialization Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Initialization declarations. */
   int conductionType, materialIndex;
   double conductionArea, conductionLength;

   conductionType = ip[0];
   materialIndex = ip[1];

   conductionArea = rp[0];
   conductionLength = rp[1];
   loop = 0;
   error = 0;

/*
   If necessary, check values of the following:

   rp[0..1]
*/


/* >>>>>>>>>>>>Initialization Function Check Statements. */
/* <<<<<<<<<<<<End of Initialization Check Statements. */

/*   Integer parameter checking:   */

   if (conductionType < 1 || conductionType > 1)
   {
      amefprintf(stderr, "\nconduction type must be in range [1..1].\n");
      error = 2;
   }
   if (materialIndex < 1 || materialIndex > 99)
   {
      amefprintf(stderr, "\nmaterial  index must be in range [1..99].\n");
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
   conductionArea = rp[0];
   rp[1]    *= 1.00000000000000e-003;
   conductionLength = rp[1];


/* >>>>>>>>>>>>Initialization Function Executable Statements. */
   Medium* medium = Medium_get(materialIndex);
   if (Medium_getConcreteType(medium) != sSolidThermal) {
	   AME_RAISE_ERROR("Medium concrete type expected to be 'solid thermal'")
   }
   _heatFlow1 = HeatFlow_new();
   _heatFlow1Index = HeatFlow_register(_heatFlow1);
   _heatFlow2 = HeatFlow_new();
   _heatFlow2Index = HeatFlow_register(_heatFlow2);
   _component = ThermalConductionElement_Line_new((Medium_Solid*) medium, conductionArea, conductionLength);
   SMOCOMPONENT_SET_PROPS(_component)
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

/*  There are 2 ports.

   Port 1 has 2 variables:

      1 heatFlow1Index        heat flow index 1    [smoHFL] basic variable output  UNPLOTTABLE
      2 thermalNode1Index     thermal node index 1 [smoTHN] basic variable input  UNPLOTTABLE

   Port 2 has 2 variables:

      1 heatFlow2Index        heat flow index 2 [smoHFL] basic variable output  UNPLOTTABLE
      2 thermalNode2Index     state index 2     [smoTHN] basic variable input  UNPLOTTABLE
*/

/*  There is 1 internal variable.

      1 qDot2     heat flow rate at port 2 [W] basic variable
*/

void smo_thermal_conduction_(int *n, double *heatFlow1Index
      , double *thermalNode1Index, double *heatFlow2Index
      , double *thermalNode2Index, double *qDot2, double rp[2]
      , int ip[2], int ic[3], void *ps[3])

{
   int loop;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   int conductionType, materialIndex;
   double conductionArea, conductionLength;

   conductionType = ip[0];
   materialIndex = ip[1];

   conductionArea = rp[0];
   conductionLength = rp[1];
   loop = 0;

/* Common -> SI units conversions. */

/*   *thermalNode1Index *= ??; CONVERSION UNKNOWN */
/*   *thermalNode2Index *= ??; CONVERSION UNKNOWN */

/*
   Set all submodel outputs below:

   *heatFlow1Index = ??;
   *heatFlow2Index = ??;
   *qDot2      = ??;
*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
   SMOCOMPONENT_PRINT_MAIN_CALC
   if (firstc_()) {
	   ThermalNode* node1 = ThermalNode_get(*thermalNode1Index);
	   ThermalNode* node2 = ThermalNode_get(*thermalNode2Index);
	   ThermalConductionElement_assignNode(_component, 1, node1);
	   ThermalConductionElement_assignNode(_component, 2, node2);
   }
   ThermalConductionElement_computeExplicit(_component);
   ThermalConductionElement_updateHeatFlow(_component, 1, _heatFlow1);
   ThermalConductionElement_updateHeatFlow(_component, 2, _heatFlow2);
   *qDot2 = ThermalConductionElement_getHeatFlowRate(_component, 2);
   *heatFlow1Index = _heatFlow1Index;
   *heatFlow2Index = _heatFlow2Index;
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *heatFlow1Index /= ??; CONVERSION UNKNOWN */
/*   *thermalNode1Index /= ??; CONVERSION UNKNOWN */
/*   *heatFlow2Index /= ??; CONVERSION UNKNOWN */
/*   *thermalNode2Index /= ??; CONVERSION UNKNOWN */
}

