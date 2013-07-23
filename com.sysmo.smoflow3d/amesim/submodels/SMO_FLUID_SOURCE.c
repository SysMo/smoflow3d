/* Submodel SMO_FLUID_SOURCE skeleton created by AME Submodel editing utility
   Tue Jul 23 18:22:56 2013 */



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

#define _SUBMODELNAME_ "SMO_FLUID_SOURCE"

/* >>>>>>>>>>>>Insert Private Code Here. */
/* <<<<<<<<<<<<End of Private Code. */

/* There is 1 integer parameter:

   mediumIndex medium index
*/

void smo_fluid_sourcein_(int *n, int ip[1], double c[5], int ic[5])

{
   int loop, error;
/* >>>>>>>>>>>>Extra Initialization Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Initialization declarations. */
   int mediumIndex;

   mediumIndex = ip[0];
   loop = 0;
   error = 0;


/* >>>>>>>>>>>>Initialization Function Check Statements. */
/* <<<<<<<<<<<<End of Initialization Check Statements. */

/*   Integer parameter checking:   */

   if (mediumIndex < 1 || mediumIndex > 99)
   {
      amefprintf(stderr, "\nmedium index must be in range [1..99].\n");
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
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

/*  There are 3 ports.

   Port 1 has 3 variables:

      1 stateIndex     state index                  [smoTDS] basic variable output  UNPLOTTABLE
      2 hfr            enthalpy flow rate at port 1 [W]      basic variable input  UNPLOTTABLE
      3 mfr            mass flow rate at port 1     [kg/s]   basic variable input  UNPLOTTABLE

   Port 2 has 1 variable:

      1 stateValue1     thermodynamic state value 1 [null] basic variable input  UNPLOTTABLE

   Port 3 has 1 variable:

      1 stateValue2     thermodynamic state value 2 [null] basic variable input
*/

/*  There are 0 internal variables.

*/

void smo_fluid_source_(int *n, double *stateIndex, double *hfr
      , double *mfr, double *stateValue1, double *stateValue2
      , int ip[1], double c[5], int ic[5], int *flag)

{
   int loop, logi;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   int mediumIndex;

   mediumIndex = ip[0];
   logi = 0;
   loop = 0;

/*
   Set all submodel outputs below:

   *stateIndex = ??;
*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *stateIndex /= ??; CONVERSION UNKNOWN */
}

