/* Submodel SMO_THERMAL_CONDUCTION_01 skeleton created by AME Submodel editing utility
   ??? ??? 14 12:48:18 2018 */



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

#define _SUBMODELNAME_ "SMO_THERMAL_CONDUCTION_01"

/* >>>>>>>>>>>>Insert Private Code Here. */
#include "SmoFlowAme.h"
#include "flow/ThermalConduction2Node.h"

#define _component ps[0]

#define _heatFlow1 ps[1]
#define _heatFlow1Index ic[1]

#define _heatFlow2 ps[2]
#define _heatFlow2Index ic[2]
/* <<<<<<<<<<<<End of Private Code. */


/* There are 5 real parameters:

   conductionArea    conduction area             [mm**2 -> m**2]
   conductionLength  conduction length           [mm -> m]
   conductionLength1 conduction length at port 1 [mm -> m]
   conductionLength2 conduction length at port 2 [mm -> m]
   contactResistance thermal contact resistance  [m**2-K/W]
*/


/* There are 4 integer parameters:

   conductionType conduction type         
   materialIndex  material index          
   materialIndex1 material index at port1 
   materialIndex2 material index at port 2
*/

void smo_thermal_conduction_01in_(int *n, double rp[5], int ip[4]
      , int ic[3], void *ps[3])

{
   int loop, error;
/* >>>>>>>>>>>>Extra Initialization Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Initialization declarations. */
   int conductionType, materialIndex, materialIndex1, materialIndex2;
   double conductionArea, conductionLength, conductionLength1, 
      conductionLength2, contactResistance;

   conductionType = ip[0];
   materialIndex = ip[1];
   materialIndex1 = ip[2];
   materialIndex2 = ip[3];

   conductionArea = rp[0];
   conductionLength = rp[1];
   conductionLength1 = rp[2];
   conductionLength2 = rp[3];
   contactResistance = rp[4];
   loop = 0;
   error = 0;

/*
   If necessary, check values of the following:

   rp[0..4]
*/


/* >>>>>>>>>>>>Initialization Function Check Statements. */
/* <<<<<<<<<<<<End of Initialization Check Statements. */

/*   Integer parameter checking:   */

   if (conductionType < 1 || conductionType > 2)
   {
      amefprintf(stderr, "\nconduction type must be in range [1..2].\n");
      error = 2;
   }
   if (materialIndex < 1 || materialIndex > 99)
   {
      amefprintf(stderr, "\nmaterial index must be in range [1..99].\n");
      error = 2;
   }
   if (materialIndex1 < 1 || materialIndex1 > 99)
   {
      amefprintf(stderr, "\nmaterial index at port1 must be in range [1..99].\n");
      error = 2;
   }
   if (materialIndex2 < 1 || materialIndex2 > 99)
   {
      amefprintf(stderr, "\nmaterial index at port 2 must be in range [1..99].\n");
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
   rp[2]    *= 1.00000000000000e-003;
   conductionLength1 = rp[2];
   rp[3]    *= 1.00000000000000e-003;
   conductionLength2 = rp[3];
/*   *rp[4]    *= ??; CONVERSION UNKNOWN [m**2-K/W] */


/* >>>>>>>>>>>>Initialization Function Executable Statements. */
   _heatFlow1 = HeatFlow_new();
   _heatFlow1Index = HeatFlow_register(_heatFlow1);
   _heatFlow2 = HeatFlow_new();
   _heatFlow2Index = HeatFlow_register(_heatFlow2);

   if (conductionType == 1) { //linear
	   Medium* medium = Medium_get(materialIndex);
	   if (Medium_getConcreteType(medium) != sSolidThermal) {
		   AME_RAISE_ERROR("Medium concrete type expected to be 'solid thermal'")
	   }

	   _component = ThermalConduction2Node_Linear_new(
			   (Medium_Solid*) medium, conductionArea, conductionLength);
   } else if (conductionType == 2) { //different materials
	   Medium* medium1 = Medium_get(materialIndex1);
	   if (Medium_getConcreteType(medium1) != sSolidThermal) {
		   AME_RAISE_ERROR("Medium concrete type expected to be 'solid thermal'")
	   }
	   Medium* medium2 = Medium_get(materialIndex2);
	   if (Medium_getConcreteType(medium2) != sSolidThermal) {
		   AME_RAISE_ERROR("Medium concrete type expected to be 'solid thermal'")
	   }

	   _component = ThermalConduction2Node_2Material_new(
			   (Medium_Solid*) medium1, (Medium_Solid*) medium2, conductionArea,
			   conductionLength1, conductionLength2, contactResistance);
   }

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

void smo_thermal_conduction_01_(int *n, double *heatFlow1Index
      , double *thermalNode1Index, double *heatFlow2Index
      , double *thermalNode2Index, double *qDot2, double rp[5]
      , int ip[4], int ic[3], void *ps[3])

{
   int loop;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   int conductionType, materialIndex, materialIndex1, materialIndex2;
   double conductionArea, conductionLength, conductionLength1, 
      conductionLength2, contactResistance;

   conductionType = ip[0];
   materialIndex = ip[1];
   materialIndex1 = ip[2];
   materialIndex2 = ip[3];

   conductionArea = rp[0];
   conductionLength = rp[1];
   conductionLength1 = rp[2];
   conductionLength2 = rp[3];
   contactResistance = rp[4];
   loop = 0;

/* Common -> SI units conversions. */

/*   *thermalNode1Index *= ??; CONVERSION UNKNOWN [smoTHN] */
/*   *thermalNode2Index *= ??; CONVERSION UNKNOWN [smoTHN] */

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
	   ThermalConduction2Node_init(_component, node1, node2);
   }
   ThermalConduction2Node_compute(_component);
   ThermalConduction2Node_updateHeatFlow1(_component, _heatFlow1);
   ThermalConduction2Node_updateHeatFlow2(_component, _heatFlow2);
   *qDot2 = ThermalConduction2Node_getHeatFlowRate2(_component);
   *heatFlow1Index = _heatFlow1Index;
   *heatFlow2Index = _heatFlow2Index;
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *heatFlow1Index /= ??; CONVERSION UNKNOWN [smoHFL] */
/*   *thermalNode1Index /= ??; CONVERSION UNKNOWN [smoTHN] */
/*   *heatFlow2Index /= ??; CONVERSION UNKNOWN [smoHFL] */
/*   *thermalNode2Index /= ??; CONVERSION UNKNOWN [smoTHN] */
}

