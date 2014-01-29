/* Submodel SMO_MEDIUM_DEFINITION_SOLID_CONST_PROPS skeleton created by AME Submodel editing utility
   Wed Jan 29 13:37:18 2014 */



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

#define _SUBMODELNAME_ "SMO_MEDIUM_DEFINITION_SOLID_CONST_PROPS"

/* >>>>>>>>>>>>Insert Private Code Here. */
#include "SmoFlowAme.h"
#include "media/Medium.h"
/* <<<<<<<<<<<<End of Private Code. */


/* There are 4 real parameters:

   density             density              [kg/m**3]
   thermalConductivity thermal conductivity [W/m/K]
   heatCapacity        heat capacity        [J/kg/K]
   enthalpy            enthalpy             [J/kg]
*/


/* There is 1 integer parameter:

   mediumIndex medium index
*/


/* There is 1 text parameter:

   solidName solid name
*/

void smo_medium_definition_solid_const_propsin_(int *n, double rp[4]
      , int ip[1], char *tp[1])

{
   int loop, error;
/* >>>>>>>>>>>>Extra Initialization Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Initialization declarations. */
   int mediumIndex;
   double density, thermalConductivity, heatCapacity, enthalpy;
   char *solidName;

   mediumIndex = ip[0];

   density    = rp[0];
   thermalConductivity = rp[1];
   heatCapacity = rp[2];
   enthalpy   = rp[3];

   solidName  = tp[0];
   loop = 0;
   error = 0;

/*
   If necessary, check values of the following:

   rp[0..3]
*/


/* >>>>>>>>>>>>Initialization Function Check Statements. */
/* <<<<<<<<<<<<End of Initialization Check Statements. */

/*   Integer parameter checking:   */

   if (mediumIndex < 1 || mediumIndex > 100000)
   {
      amefprintf(stderr, "\nmedium index must be in range [1..100000].\n");
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
   Medium_registerSolidConstProps(solidName, mediumIndex, density, thermalConductivity, heatCapacity, enthalpy);
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

/*  There are 0 ports.
*/

/*  There are 0 internal variables.

*/

#if 0

/* THE CALCULATION FUNCTION WILL NOT BE CALLED. */

void smo_medium_definition_solid_const_props_(int *n, double rp[4]
      , int ip[1], char *tp[1])

{
   int loop;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   int mediumIndex;
   double density, thermalConductivity, heatCapacity, enthalpy;
   char *solidName;

   mediumIndex = ip[0];

   density    = rp[0];
   thermalConductivity = rp[1];
   heatCapacity = rp[2];
   enthalpy   = rp[3];

   solidName  = tp[0];
   loop = 0;


/* >>>>>>>>>>>>Calculation Function Executable Statements. */
/* <<<<<<<<<<<<End of Calculation Executable Statements. */
}

#endif
