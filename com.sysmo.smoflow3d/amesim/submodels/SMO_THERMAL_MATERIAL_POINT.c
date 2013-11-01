/* Submodel SMO_THERMAL_MATERIAL_POINT skeleton created by AME Submodel editing utility
   Fri Nov 1 11:05:09 2013 */



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

#define _SUBMODELNAME_ "SMO_THERMAL_MATERIAL_POINT"

/* >>>>>>>>>>>>Insert Private Code Here. */
#include "SmoFlowAme.h"
#include "volumes/ThermalNode.h"
#include "flow/FlowBase.h"

#define _thermalNode ps[0]
#define _thermalNodeIndex ic[0]

#define _heatFlow ps[1]
/* <<<<<<<<<<<<End of Private Code. */


/* There are 2 real parameters:

   materialMasses[]     material masses     [kg]
   initialTemperature   initial temperature [K]
*/


/* There are 2 integer parameters:

   numMaterials      number of materials
   materialIndices[] material indices   
*/

void smo_thermal_material_pointin_(int *n, double *rp, int *ip
      , double c[1], int ic[5], void *ps[5], double *temperature)

{
   int loop, error;
/* >>>>>>>>>>>>Extra Initialization Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Initialization declarations. */
   int materialMasses_size;
   int materialIndices_size;
   int param_offset;  /* Offset used to assign parameter values. */
   int numMaterials, *materialIndices;
   double *materialMasses, initialTemperature;

   param_offset = 0;
   numMaterials = ip[0];
   materialIndices = &(ip[1]);
   materialIndices_size = numMaterials;
   param_offset += materialIndices_size-1;

   param_offset = 0;
   materialMasses = &(rp[0]);
   materialMasses_size = numMaterials;
   param_offset += materialMasses_size-1;
   initialTemperature = rp[1 + param_offset];
   param_offset = 0;
   loop = 0;
   error = 0;

/*
   If necessary, check values of the following:

   rp[0..1]
   *temperature
*/


/* >>>>>>>>>>>>Initialization Function Check Statements. */
/* <<<<<<<<<<<<End of Initialization Check Statements. */

/*   Integer parameter checking:   */

   if (numMaterials < 1 || numMaterials > 10)
   {
      amefprintf(stderr, "\nnumber of materials must be in range [1..10].\n");
      error = 2;
   }
   for (loop=0; loop < materialIndices_size; loop++)
   {
      if (materialIndices[loop] < 1 || materialIndices[loop] > 99)
      {
         amefprintf(stderr, "\nmaterial indices %d must be in range [1..99].\n", loop+1);
         error = 2;
      }
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
   param_offset += materialMasses_size-1;


/* >>>>>>>>>>>>Initialization Function Executable Statements. */
   *temperature = initialTemperature;
   _thermalNode = ThermalNode_new(sThermalNode_Material);
   _thermalNodeIndex = ThermalNode_register(_thermalNode);
   for (int i = 0; i < numMaterials; i++) {
	  Medium* medium = Medium_get(materialIndices[i]);
	  if (Medium_getConcreteType(medium) != sSolidThermal) {
		  AME_RAISE_ERROR("Medium concrete type expected to be 'solid thermal'")
	  }

	  ThermalMaterialNode_addMaterialMass(_thermalNode, (Medium_Solid*) medium, materialMasses[i]);
   }
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

/*  There is 1 port.

   Port 1 has 2 variables:

      1 thermalNodeIndex     thermal node index [smoTHN] multi line macro 'smo_thermal_material_point_thermalNodeIndex_'  UNPLOTTABLE
      2 heatFlowIndex        heat flow index    [smoHFL] basic variable input  UNPLOTTABLE
*/

/*  There are 4 internal variables.

      1 thermalEnergy              thermal energy [J]   basic variable
      2 temperature                temperature    [K]   explicit state (derivative `temperatureDot')
      3 heatFlowRate               heat flow rate [W]   basic variable
      4 temperatureDotInternal     TDot           [K/s] basic variable
*/

void smo_thermal_material_point_(int *n, double *thermalNodeIndex
      , double *heatFlowIndex, double *thermalEnergy
      , double *temperature, double *temperatureDot
      , double *heatFlowRate, double *temperatureDotInternal
      , double *rp, int *ip, double c[1], int ic[5], void *ps[5])

{
   int loop;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   int materialMasses_size;
   int materialIndices_size;
   int param_offset;  /* Offset used to assign parameter values. */
   int numMaterials, *materialIndices;
   double *materialMasses, initialTemperature;

   param_offset = 0;
   numMaterials = ip[0];
   materialIndices = &(ip[1]);
   materialIndices_size = numMaterials;
   param_offset += materialIndices_size-1;

   param_offset = 0;
   materialMasses = &(rp[0]);
   materialMasses_size = numMaterials;
   param_offset += materialMasses_size-1;
   initialTemperature = rp[1 + param_offset];
   param_offset = 0;
   loop = 0;

/* Common -> SI units conversions. */

/*   *thermalNodeIndex *= ??; CONVERSION UNKNOWN */
/*   *heatFlowIndex *= ??; CONVERSION UNKNOWN */

/*
   Set all submodel outputs below:

   *thermalEnergy = ??;
   *temperatureDot = ??;
   *heatFlowRate = ??;
   *temperatureDotInternal = ??;
*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
   if (firstc_()) {
	   _heatFlow = HeatFlow_get(*heatFlowIndex);
   }
   *heatFlowRate = HeatFlow_getEnthalpyFlowRate(_heatFlow);
   ThermalMaterialNode_compute(_thermalNode, *heatFlowRate);
   *temperatureDot = ThermalMaterialNode_getTemperatureDerivative(_thermalNode);
   *temperatureDotInternal = *temperatureDot;
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *thermalNodeIndex /= ??; CONVERSION UNKNOWN */
/*   *heatFlowIndex /= ??; CONVERSION UNKNOWN */
}

extern double smo_thermal_material_point_thermalNodeIndex_(int *n
      , double *temperature, double *rp, int *ip, double c[1]
      , int ic[5], void *ps[5], int *macindex)

{
   double thermalNodeIndex;
   int loop;
/* >>>>>>>>>>>>Extra Macro Function macro0 Declarations Here. */
/* <<<<<<<<<<<<End of Extra Macro macro0 declarations. */
   int materialMasses_size;
   int materialIndices_size;
   int param_offset;  /* Offset used to assign parameter values. */
   int numMaterials, *materialIndices;
   double *materialMasses, initialTemperature;

   param_offset = 0;
   numMaterials = ip[0];
   materialIndices = &(ip[1]);
   materialIndices_size = numMaterials;
   param_offset += materialIndices_size-1;

   param_offset = 0;
   materialMasses = &(rp[0]);
   materialMasses_size = numMaterials;
   param_offset += materialMasses_size-1;
   initialTemperature = rp[1 + param_offset];
   param_offset = 0;
   loop = 0;

/*
   Define and return the following macro variable:

   thermalNodeIndex = ??;
*/


/* >>>>>>>>>>>>Macro Function macro0 Executable Statements. */
   ThermalNode_setTemperature(_thermalNode, *temperature);
   thermalNodeIndex = _thermalNodeIndex;
/* <<<<<<<<<<<<End of Macro macro0 Executable Statements. */

/*   *thermalNodeIndex /= ??; CONVERSION UNKNOWN */

   return thermalNodeIndex;
}

