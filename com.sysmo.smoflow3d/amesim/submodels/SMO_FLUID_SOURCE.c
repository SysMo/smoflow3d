/* Submodel SMO_FLUID_SOURCE skeleton created by AME Submodel editing utility
   Wed Jul 24 23:14:37 2013 */



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
#include "media/MediumState.h"
#define fluidStateIndex ic[1]
#define fluidState ps[1]
/* <<<<<<<<<<<<End of Private Code. */

/* There is 1 integer parameter:

   mediumIndex medium index
*/

void smo_fluid_sourcein_(int *n, int ip[1], int ic[1], void *ps[1])

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
   fluidState = create_mstate(mediumIndex);
   fluidStateIndex = mstate_register(fluidState);
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

/*  There are 3 ports.

   Port 1 has 2 variables:

      1 stateIndex     state index [smoTDS] basic variable output  UNPLOTTABLE
      2 flowIndex      flow index  [smoFFL] basic variable input  UNPLOTTABLE

   Port 2 has 1 variable:

      1 stateValue1     thermodynamic state value 1 [null] basic variable input  UNPLOTTABLE

   Port 3 has 1 variable:

      1 stateValue2     thermodynamic state value 2 [null] basic variable input
*/

/*  There are 0 internal variables.

*/

void smo_fluid_source_(int *n, double *stateIndex, double *flowIndex
      , double *stateValue1, double *stateValue2, int ip[1], int ic[1]
      , void *ps[1], int *flag)

{
   int loop, logi;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   int mediumIndex;

   mediumIndex = ip[0];
   logi = 0;
   loop = 0;

/* Common -> SI units conversions. */

/*   *flowIndex *= ??; CONVERSION UNKNOWN */

/*
   Set all submodel outputs below:

   *stateIndex = ??;
*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
   mstate_update_Tp(fluidState, *stateValue2, *stateValue1);
   *stateIndex = (double) fluidStateIndex;
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *stateIndex /= ??; CONVERSION UNKNOWN */
/*   *flowIndex /= ??; CONVERSION UNKNOWN */
}

