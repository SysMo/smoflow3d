/* Submodel SMO_SIMULATION_ENVIRONMENT skeleton created by AME Submodel editing utility
   Sun Aug 25 17:53:12 2013 */



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

#define _SUBMODELNAME_ "SMO_SIMULATION_ENVIRONMENT"

/* >>>>>>>>>>>>Insert Private Code Here. */
#include "util/SimulationEnvironment.h"
/* <<<<<<<<<<<<End of Private Code. */
void smo_simulation_environmentin_(int *n)

{
   int loop, error;
/* >>>>>>>>>>>>Extra Initialization Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Initialization declarations. */
   loop = 0;
   error = 0;


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
   SimulationEnvironment_registerSimEnvComponent();
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

void smo_simulation_environmentend_(int *n)

{
   int loop, error;
/* >>>>>>>>>>>>Extra Terminate Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Terminate declarations. */
   loop = 0;
   error = 0;


/* >>>>>>>>>>>>Terminate Function Executable Statements. */
/* <<<<<<<<<<<<End of Terminate Executable Statements. */
}



/*  There are 0 ports.
*/

/*  There are 0 internal variables.

*/

void smo_simulation_environment_(int *n, int *flag, double *t)

{
   int loop, logi;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   logi = 0;
   loop = 0;


/* >>>>>>>>>>>>Calculation Function Executable Statements. */
   SimulationEnvironment_setTime(*t);
/* <<<<<<<<<<<<End of Calculation Executable Statements. */
}

