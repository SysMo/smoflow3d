/* Submodel SMO_MEDIUM_DEFINITION_SOLID skeleton created by AME Submodel editing utility
   Mon Feb 3 08:17:20 2014 */



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

#define _SUBMODELNAME_ "SMO_MEDIUM_DEFINITION_SOLID"

/* >>>>>>>>>>>>Insert Private Code Here. */
#include "SmoFlowAme.h"
#include "media/Medium.h"
/* <<<<<<<<<<<<End of Private Code. */

/* There is 1 integer parameter:

   mediumIndex medium index
*/


/* There are 5 text parameters:

   solidName           solid name                  
   density             density [kg/m**3]           
   thermalConductivity thermal conductivity [W/m/K]
   heatCapacity        heat capacity [J/kg/K]      
   enthalpy            enthalpy [J/kg]             
*/

void smo_medium_definition_solidin_(int *n, int ip[1], char *tp[5])

{
   int loop, error;
/* >>>>>>>>>>>>Extra Initialization Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Initialization declarations. */
   int mediumIndex;
   char *solidName, *density, *thermalConductivity, *heatCapacity, 
      *enthalpy;

   mediumIndex = ip[0];

   solidName  = tp[0];
   density    = tp[1];
   thermalConductivity = tp[2];
   heatCapacity = tp[3];
   enthalpy   = tp[4];
   loop = 0;
   error = 0;


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
   Medium_registerSolidUserDefined(solidName, mediumIndex, density, thermalConductivity, heatCapacity, enthalpy);
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

/*  There are 0 ports.
*/

/*  There are 0 internal variables.

*/

#if 0

/* THE CALCULATION FUNCTION WILL NOT BE CALLED. */

void smo_medium_definition_solid_(int *n, int ip[1], char *tp[5])

{
   int loop;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   int mediumIndex;
   char *solidName, *density, *thermalConductivity, *heatCapacity, 
      *enthalpy;

   mediumIndex = ip[0];

   solidName  = tp[0];
   density    = tp[1];
   thermalConductivity = tp[2];
   heatCapacity = tp[3];
   enthalpy   = tp[4];
   loop = 0;


/* >>>>>>>>>>>>Calculation Function Executable Statements. */
/* <<<<<<<<<<<<End of Calculation Executable Statements. */
}

#endif
