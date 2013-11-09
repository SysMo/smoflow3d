/* Submodel SMO_R_ADAPTOR_BEGIN skeleton created by AME Submodel editing utility
   Sat Nov 9 14:14:44 2013 */



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

#define _SUBMODELNAME_ "SMO_R_ADAPTOR_BEGIN"

/* >>>>>>>>>>>>Insert Private Code Here. */
#include "SmoFlowAme.h"
/* <<<<<<<<<<<<End of Private Code. */
void smo_r_adaptor_beginin_(int *n)

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
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

/*  There are 3 ports.

   Port 1 has 2 variables:

      1 fluidFlow1Index      fluid flow1 index  [smoFFL] basic variable output  UNPLOTTABLE
      2 fluidState1Index     fluid state1 index [smoTDS] basic variable input  UNPLOTTABLE

   Port 2 has 2 variables:

      1 fluidState2Index     fluid state2 index [smoTDS] multi line macro 'smo_r_adaptor_begin_macro0_'  UNPLOTTABLE
      2 fluidFlow2Index      fluid flow2 index  [smoFFL] basic variable input  UNPLOTTABLE

   Port 3 has 1 variable:

      1 RAdaptorSignal     R-adaptor signal (output) [R-adaptor signal] basic variable output
*/

/*  There are 0 internal variables.

*/

void smo_r_adaptor_begin_(int *n, double *fluidFlow1Index
      , double *fluidState1Index, double *fluidState2Index
      , double *fluidFlow2Index, double *RAdaptorSignal)

{
   int loop;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   loop = 0;

/* Common -> SI units conversions. */

/*   *fluidState1Index *= ??; CONVERSION UNKNOWN */
/*   *fluidState2Index *= ??; CONVERSION UNKNOWN */
/*   *fluidFlow2Index *= ??; CONVERSION UNKNOWN */

/*
   Set all submodel outputs below:

   *fluidFlow1Index = ??;
   *RAdaptorSignal = ??;
*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
   SMOCOMPONENT_PRINT_MAIN_CALC
   *fluidFlow1Index = *fluidFlow2Index;
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *fluidFlow1Index /= ??; CONVERSION UNKNOWN */
/*   *fluidState1Index /= ??; CONVERSION UNKNOWN */
/*   *fluidState2Index /= ??; CONVERSION UNKNOWN */
/*   *fluidFlow2Index /= ??; CONVERSION UNKNOWN */
/*   *RAdaptorSignal /= ??; CONVERSION UNKNOWN */
}

extern double smo_r_adaptor_begin_macro0_(int *n
      , double *fluidState1Index)

{
   double fluidState2Index;
   int loop;
/* >>>>>>>>>>>>Extra Macro Function macro0 Declarations Here. */
/* <<<<<<<<<<<<End of Extra Macro macro0 declarations. */
   loop = 0;

/* Common -> SI units conversions. */

/*   *fluidState1Index *= ??; CONVERSION UNKNOWN */

/*
   Define and return the following macro variable:

   fluidState2Index = ??;
*/


/* >>>>>>>>>>>>Macro Function macro0 Executable Statements. */
   SMOCOMPONENt_PRINT_MACRO
   fluidState2Index = *fluidState1Index;
/* <<<<<<<<<<<<End of Macro macro0 Executable Statements. */

/* SI -> Common units conversions. */

/*   *fluidState1Index /= ??; CONVERSION UNKNOWN */

/*   *fluidState2Index /= ??; CONVERSION UNKNOWN */

   return fluidState2Index;
}

