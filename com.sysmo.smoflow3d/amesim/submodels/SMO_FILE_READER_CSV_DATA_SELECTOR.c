/* Submodel SMO_FILE_READER_CSV_DATA_SELECTOR skeleton created by AME Submodel editing utility
   Fri Mar 7 08:58:30 2014 */



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

#define _SUBMODELNAME_ "SMO_FILE_READER_CSV_DATA_SELECTOR"

/* >>>>>>>>>>>>Insert Private Code Here. */
#include "file_reader/FileReader.h"

#define _component ps[0]

#define _columnIndex ic[0]
/* <<<<<<<<<<<<End of Private Code. */

/* There is 1 integer parameter:

   fileReaderIndex file reader index
*/


/* There is 1 text parameter:

   columnHeaderName column header name
*/

void smo_file_reader_csv_data_selectorin_(int *n, int ip[1]
      , char *tp[1], int ic[1], void *ps[1])

{
   int loop, error;
/* >>>>>>>>>>>>Extra Initialization Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Initialization declarations. */
   int fileReaderIndex;
   char *columnHeaderName;

   fileReaderIndex = ip[0];

   columnHeaderName = tp[0];
   loop = 0;
   error = 0;


/* >>>>>>>>>>>>Initialization Function Check Statements. */
/* <<<<<<<<<<<<End of Initialization Check Statements. */

/*   Integer parameter checking:   */

   if (fileReaderIndex < 1 || fileReaderIndex > 99)
   {
      amefprintf(stderr, "\nfile reader index must be in range [1..99].\n");
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

/*  There is 1 port.

   Port 1 has 1 variable:

      1 value     data output [null] basic variable output
*/

/*  There are 0 internal variables.

*/

void smo_file_reader_csv_data_selector_(int *n, double *value
      , int ip[1], char *tp[1], int ic[1], void *ps[1], double *t)

{
   int loop;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   int fileReaderIndex;
   char *columnHeaderName;

   fileReaderIndex = ip[0];

   columnHeaderName = tp[0];
   loop = 0;

/*
   Set all submodel outputs below:

   *value      = ??;
*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
   if (firstc_()) {
	   _component = FileReader_get(fileReaderIndex);
	   _columnIndex = FileReader_getColumnIndex(_component, columnHeaderName);
   }

   *value = FileReader_getValue(_component, _columnIndex, *t);
/* <<<<<<<<<<<<End of Calculation Executable Statements. */
}

