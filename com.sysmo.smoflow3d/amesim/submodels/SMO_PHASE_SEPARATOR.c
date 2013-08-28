/* Submodel SMO_PHASE_SEPARATOR skeleton created by AME Submodel editing utility
   Wed Aug 28 11:46:30 2013 */



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

#define _SUBMODELNAME_ "SMO_PHASE_SEPARATOR"

/* >>>>>>>>>>>>Insert Private Code Here. */
/* <<<<<<<<<<<<End of Private Code. */
void smo_phase_separatorin_(int *n, int ic[5], void *ps[5]
      , double *regSignal)

{
   int loop, error;
/* >>>>>>>>>>>>Extra Initialization Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Initialization declarations. */
   loop = 0;
   error = 0;

/* Assign default values to input(s) with default.  */

   *regSignal =     0.00000000000000e+000;


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

      1 port1FlowIndex      duplicate of port2FlowIndex
      2 port1StateIndex     state index at port 1 [smoTDS] basic variable input  UNPLOTTABLE

   Port 2 has 2 variables:

      1 port2StateIndex     state index at port 2 [smoTDS] multi line macro 'smo_phase_separator_macro0_'  UNPLOTTABLE
      2 port2FlowIndex      flow index at port 2  [smoFFL] basic variable input  UNPLOTTABLE

   Port 3 has 1 variable:

      1 regSignal     regulating signal [null] basic variable input with default 0.000000e+000
*/

/*  There are 0 internal variables.

*/

void smo_phase_separator_(int *n, double *port1StateIndex
      , double *port2StateIndex, double *port2FlowIndex
      , double *regSignal, int ic[5], void *ps[5])

{
   int loop;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   loop = 0;

/* Common -> SI units conversions. */

/*   *port1StateIndex *= ??; CONVERSION UNKNOWN */
/*   *port2StateIndex *= ??; CONVERSION UNKNOWN */
/*   *port2FlowIndex *= ??; CONVERSION UNKNOWN */

/*
   Set all submodel outputs below:

*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *port1StateIndex /= ??; CONVERSION UNKNOWN */
/*   *port2StateIndex /= ??; CONVERSION UNKNOWN */
/*   *port2FlowIndex /= ??; CONVERSION UNKNOWN */
}

extern double smo_phase_separator_macro0_(int *n
      , double *port1StateIndex, double *regSignal, int ic[5]
      , void *ps[5])

{
   double port2StateIndex;
   int loop;
/* >>>>>>>>>>>>Extra Macro Function macro0 Declarations Here. */
/* <<<<<<<<<<<<End of Extra Macro macro0 declarations. */
   loop = 0;

/* Common -> SI units conversions. */

/*   *port1StateIndex *= ??; CONVERSION UNKNOWN */

/*
   Define and return the following macro variable:

   port2StateIndex = ??;
*/


/* >>>>>>>>>>>>Macro Function macro0 Executable Statements. */
/* <<<<<<<<<<<<End of Macro macro0 Executable Statements. */

/* SI -> Common units conversions. */

/*   *port1StateIndex /= ??; CONVERSION UNKNOWN */

/*   *port2StateIndex /= ??; CONVERSION UNKNOWN */

   return port2StateIndex;
}
