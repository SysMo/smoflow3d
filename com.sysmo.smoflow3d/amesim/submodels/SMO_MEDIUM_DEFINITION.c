/* Submodel SMO_MEDIUM_DEFINITION skeleton created by AME Submodel editing utility
   Tue Jul 23 18:06:10 2013 */



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

#define _SUBMODELNAME_ "SMO_MEDIUM_DEFINITION"

/* >>>>>>>>>>>>Insert Private Code Here. */
#include "media/MediaRegistry.h"
const char* ameMediaNames[] = {
	"parahydrogen",
	"nitrogen",
	"water"
};
/* <<<<<<<<<<<<End of Private Code. */

/* There are 2 integer parameters:

   mediumIndex     medium index
   mediumNameIndex medium name 
*/

void smo_medium_definitionin_(int *n, int ip[2])

{
   int loop, error;
/* >>>>>>>>>>>>Extra Initialization Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Initialization declarations. */
   int mediumIndex, mediumNameIndex;

   mediumIndex = ip[0];
   mediumNameIndex = ip[1];
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
   if (mediumNameIndex < 1 || mediumNameIndex > 3)
   {
      amefprintf(stderr, "\nmedium name must be in range [1..3].\n");
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
   register_medium(ameMediaNames[mediumNameIndex - 1], mediumIndex);
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

void smo_medium_definitionend_(int *n, int ip[2])

{
   int loop, error;
/* >>>>>>>>>>>>Extra Terminate Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Terminate declarations. */
   int mediumIndex, mediumNameIndex;

   mediumIndex = ip[0];
   mediumNameIndex = ip[1];
   loop = 0;
   error = 0;


/* >>>>>>>>>>>>Terminate Function Executable Statements. */
/* <<<<<<<<<<<<End of Terminate Executable Statements. */
}



/*  There are 0 ports.
*/

/*  There are 0 internal variables.

*/

#if 0

/* THE CALCULATION FUNCTION WILL NOT BE CALLED. */

void smo_medium_definition_(int *n, int ip[2])

{
   int loop;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   int mediumIndex, mediumNameIndex;

   mediumIndex = ip[0];
   mediumNameIndex = ip[1];
   loop = 0;


/* >>>>>>>>>>>>Calculation Function Executable Statements. */
/* <<<<<<<<<<<<End of Calculation Executable Statements. */
}

#endif
