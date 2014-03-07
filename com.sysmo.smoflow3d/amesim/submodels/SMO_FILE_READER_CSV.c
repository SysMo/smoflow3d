/* Submodel SMO_FILE_READER_CSV skeleton created by AME Submodel editing utility
   Fri Mar 7 09:10:03 2014 */



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

#define _SUBMODELNAME_ "SMO_FILE_READER_CSV"

/* >>>>>>>>>>>>Insert Private Code Here. */
#include "SmoFlowAme.h"
#include "file_reader/FileReader.h"

#define _component ps[0]
/* <<<<<<<<<<<<End of Private Code. */

/* There are 5 integer parameters:

   fileReaderIndex     file reader index                     
   timeColumnIndex     time column index                     
   headerLineNumber    number of the line with column headers
   dataFirstLineNumber number of the line with the first data
   maxLinesToRead      maximum number of lines to read       
*/


/* There are 2 text parameters:

   dataFile       data file     
   dataSeparators data separator
*/

void smo_file_reader_csvin_(int *n, int ip[5], char *tp[2]
      , void *ps[1])

{
   int loop, error;
/* >>>>>>>>>>>>Extra Initialization Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Initialization declarations. */
   int fileReaderIndex, timeColumnIndex, headerLineNumber, 
      dataFirstLineNumber, maxLinesToRead;
   char *dataFile, *dataSeparators;

   fileReaderIndex = ip[0];
   timeColumnIndex = ip[1];
   headerLineNumber = ip[2];
   dataFirstLineNumber = ip[3];
   maxLinesToRead = ip[4];

   dataFile   = tp[0];
   dataSeparators = tp[1];
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
   if (timeColumnIndex < 1 || timeColumnIndex > 99)
   {
      amefprintf(stderr, "\ntime column index must be in range [1..99].\n");
      error = 2;
   }
   if (headerLineNumber < 0 || headerLineNumber > 1000)
   {
      amefprintf(stderr, "\nnumber of the line with column headers must be in range [0..1000].\n");
      error = 2;
   }
   if (dataFirstLineNumber < 1 || dataFirstLineNumber > 1000)
   {
      amefprintf(stderr, "\nnumber of the line with the first data must be in range [1..1000].\n");
      error = 2;
   }
   if (maxLinesToRead < -1 || maxLinesToRead > 100000000)
   {
      amefprintf(stderr, "\nmaximum number of lines to read must be in range [-1..100000000].\n");
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
   FileReader_register(fileReaderIndex, timeColumnIndex);
   _component = FileReader_get(fileReaderIndex);
   SMOCOMPONENT_SET_PROPS(_component)

   FileReader_readDataFromFile(
		   _component,
		   dataFile,
		   dataSeparators,
		   headerLineNumber,
		   dataFirstLineNumber,
		   maxLinesToRead);
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

/*  There are 0 ports.
*/

/*  There are 0 internal variables.

*/

#if 0

/* THE CALCULATION FUNCTION WILL NOT BE CALLED. */

void smo_file_reader_csv_(int *n, int ip[5], char *tp[2], void *ps[1])

{
   int loop;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   int fileReaderIndex, timeColumnIndex, headerLineNumber, 
      dataFirstLineNumber, maxLinesToRead;
   char *dataFile, *dataSeparators;

   fileReaderIndex = ip[0];
   timeColumnIndex = ip[1];
   headerLineNumber = ip[2];
   dataFirstLineNumber = ip[3];
   maxLinesToRead = ip[4];

   dataFile   = tp[0];
   dataSeparators = tp[1];
   loop = 0;


/* >>>>>>>>>>>>Calculation Function Executable Statements. */
/* <<<<<<<<<<<<End of Calculation Executable Statements. */
}

#endif
