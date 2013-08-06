/* Submodel SMO_THERMAL_NODE skeleton created by AME Submodel editing utility
   Tue Aug 6 13:05:14 2013 */



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

#define _SUBMODELNAME_ "SMO_THERMAL_NODE"

/* >>>>>>>>>>>>Insert Private Code Here. */
/* <<<<<<<<<<<<End of Private Code. */


/* There is 1 real parameter:

   materialMasses[] material masses [kg]
*/


/* There are 2 integer parameters:

   numMaterials      number of materials
   materialIndices[] material indices   
*/

void smo_thermal_nodein_(int *n, double *rp, int *ip, double c[1]
      , double *temperature)

{
   int loop, error;
/* >>>>>>>>>>>>Extra Initialization Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Initialization declarations. */
   int materialMasses_size;
   int materialIndices_size;
   int param_offset;  /* Offset used to assign parameter values. */
   int numMaterials, *materialIndices;
   double *materialMasses;

   param_offset = 0;
   numMaterials = ip[0];
   materialIndices = &(ip[1]);
   materialIndices_size = numMaterials;
   param_offset += materialIndices_size-1;

   param_offset = 0;
   materialMasses = &(rp[0]);
   materialMasses_size = numMaterials;
   param_offset += materialMasses_size-1;
   param_offset = 0;
   loop = 0;
   error = 0;

/*
   If necessary, check values of the following:

   rp[0..0]
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
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

/*  There is 1 port.

   Port 1 has 2 variables:

      1 stateIndex     state index [smoTDS] multi line macro 'smo_thermal_node_stateIndex_'  UNPLOTTABLE
      2 flowIndex      flow index  [smoFFL] basic variable input  UNPLOTTABLE
*/

/*  There are 3 internal variables.

      1 thermalEnergy     thermal energy [J] basic variable
      2 temperature       temperature    [K] explicit state (derivative `temperatureDot')
      3 heatFlow          heat flow      [W] basic variable
*/

void smo_thermal_node_(int *n, double *stateIndex, double *flowIndex
      , double *thermalEnergy, double *temperature
      , double *temperatureDot, double *heatFlow, double *rp, int *ip
      , double c[1])

{
   int loop;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   int materialMasses_size;
   int materialIndices_size;
   int param_offset;  /* Offset used to assign parameter values. */
   int numMaterials, *materialIndices;
   double *materialMasses;

   param_offset = 0;
   numMaterials = ip[0];
   materialIndices = &(ip[1]);
   materialIndices_size = numMaterials;
   param_offset += materialIndices_size-1;

   param_offset = 0;
   materialMasses = &(rp[0]);
   materialMasses_size = numMaterials;
   param_offset += materialMasses_size-1;
   param_offset = 0;
   loop = 0;

/* Common -> SI units conversions. */

/*   *stateIndex *= ??; CONVERSION UNKNOWN */
/*   *flowIndex *= ??; CONVERSION UNKNOWN */

/*
   Set all submodel outputs below:

   *thermalEnergy = ??;
   *temperatureDot = ??;
   *heatFlow   = ??;
*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *stateIndex /= ??; CONVERSION UNKNOWN */
/*   *flowIndex /= ??; CONVERSION UNKNOWN */
}

extern double smo_thermal_node_stateIndex_(int *n, double *temperature
      , double *rp, int *ip, double c[1], int *macindex)

{
   double stateIndex;
   int loop;
/* >>>>>>>>>>>>Extra Macro Function macro0 Declarations Here. */
/* <<<<<<<<<<<<End of Extra Macro macro0 declarations. */
   int materialMasses_size;
   int materialIndices_size;
   int param_offset;  /* Offset used to assign parameter values. */
   int numMaterials, *materialIndices;
   double *materialMasses;

   param_offset = 0;
   numMaterials = ip[0];
   materialIndices = &(ip[1]);
   materialIndices_size = numMaterials;
   param_offset += materialIndices_size-1;

   param_offset = 0;
   materialMasses = &(rp[0]);
   materialMasses_size = numMaterials;
   param_offset += materialMasses_size-1;
   param_offset = 0;
   loop = 0;

/*
   Define and return the following macro variable:

   stateIndex = ??;
*/


/* >>>>>>>>>>>>Macro Function macro0 Executable Statements. */
/* <<<<<<<<<<<<End of Macro macro0 Executable Statements. */

/*   *stateIndex /= ??; CONVERSION UNKNOWN */

   return stateIndex;
}

