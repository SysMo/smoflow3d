/* Submodel SMO_MEDIUM_DEFINITION skeleton created by AME Submodel editing utility
   Wed Jan 29 10:24:11 2014 */



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
#include "SmoFlowAme.h"
#include "media/Medium.h"

static const char* solidNames[] = {
	"Aluminium6061",
	"StainlessSteel304",
	"CarbonFiberComposite",
	"CarbonFiberCompositeWarm",
	"GlassFiberComposite",
	"Teflon", //:SMO_TODO: (Milen)
	"HighDensityPolyethylene",
	"HighDensityPolyethyleneWarm",
	"ArmaflexLTD",
	"ArmaflexAF"
};

static const char* liquidNames[] = {
	"water",
	"ethylene glycol"
};

static const char* realFluidNames[26] = {
	"ParaHydrogen",
	"OrthoHydrogen",
	"Hydrogen",
	"Water",
	"Air",
	"Nitrogen",
	"Oxygen",
	"CarbonDioxide",
	"CarbonMonoxide",
	"R134a",
	"R1234yf",
	"R1234ze(Z)",
	"Ammonia",
	"Argon",
	"Neon",
	"Helium",
	"Methane",
	"Ethane",
	"Ethylene",
	"n-Propane",
	"n-Butane",
	"IsoButane",
	"n-Pentane",
	"Isopentane",
	"Methanol",
	"Ethanol"
};
/* <<<<<<<<<<<<End of Private Code. */

/* There are 5 integer parameters:

   mediumIndex        medium index   
   mediumType         medium type    
   solidNameIndex     solid name     
   liquidNameIndex    liquid name    
   realFluidNameIndex real fluid name
*/

void smo_medium_definitionin_(int *n, int ip[5])

{
   int loop, error;
/* >>>>>>>>>>>>Extra Initialization Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Initialization declarations. */
   int mediumIndex, mediumType, solidNameIndex, liquidNameIndex, 
      realFluidNameIndex;

   mediumIndex = ip[0];
   mediumType = ip[1];
   solidNameIndex = ip[2];
   liquidNameIndex = ip[3];
   realFluidNameIndex = ip[4];
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
   if (mediumType < 1 || mediumType > 3)
   {
      amefprintf(stderr, "\nmedium type must be in range [1..3].\n");
      error = 2;
   }
   if (solidNameIndex < 1 || solidNameIndex > 8)
   {
      amefprintf(stderr, "\nsolid name must be in range [1..8].\n");
      error = 2;
   }
   if (liquidNameIndex < 1 || liquidNameIndex > 2)
   {
      amefprintf(stderr, "\nliquid name must be in range [1..2].\n");
      error = 2;
   }
   if (realFluidNameIndex < 1 || realFluidNameIndex > 26)
   {
      amefprintf(stderr, "\nreal fluid name must be in range [1..26].\n");
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
   if (mediumType == 1) {
	   Medium_register(sSolidThermal,
			   solidNames[solidNameIndex - 1], mediumIndex);
   } else if (mediumType == 2) {
	   Medium_register(sIncompressibleLiquidCoolProp,
			   liquidNames[liquidNameIndex - 1], mediumIndex);
   } else if (mediumType == 3) {
	   Medium_register(sCompressibleFluidCoolProp,
			   realFluidNames[realFluidNameIndex - 1], mediumIndex);
   } else {
	   AME_RAISE_ERROR("Unsupported medium type.")
   }
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

void smo_medium_definitionend_(int *n, int ip[5])

{
   int loop, error;
/* >>>>>>>>>>>>Extra Terminate Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Terminate declarations. */
   int mediumIndex, mediumType, solidNameIndex, liquidNameIndex, 
      realFluidNameIndex;

   mediumIndex = ip[0];
   mediumType = ip[1];
   solidNameIndex = ip[2];
   liquidNameIndex = ip[3];
   realFluidNameIndex = ip[4];
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

void smo_medium_definition_(int *n, int ip[5])

{
   int loop;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   int mediumIndex, mediumType, solidNameIndex, liquidNameIndex, 
      realFluidNameIndex;

   mediumIndex = ip[0];
   mediumType = ip[1];
   solidNameIndex = ip[2];
   liquidNameIndex = ip[3];
   realFluidNameIndex = ip[4];
   loop = 0;


/* >>>>>>>>>>>>Calculation Function Executable Statements. */
/* <<<<<<<<<<<<End of Calculation Executable Statements. */
}

#endif
