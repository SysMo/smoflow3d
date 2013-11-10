/* Submodel SMO_R_ADAPTOR_BEGIN skeleton created by AME Submodel editing utility
   Sun Nov 10 18:43:12 2013 */



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
#include "flow_R/ManagerComponents_R.h"
#include "flow_R/Adaptor_R.h"

#define _component ps[0]

#define _manager ps[1]
#define _managerIndex ic[1]
/* <<<<<<<<<<<<End of Private Code. */
void smo_r_adaptor_beginin_(int *n, int ic[2], void *ps[2])

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
   _component = BeginAdaptor_R_new();
   SMOCOMPONENT_SET_PROPS(_component);

   _manager = ManagerComponents_R_new();
   _managerIndex = ManagerComponents_R_register(_manager);
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

/*  There are 3 ports.

   Port 1 has 2 variables:

      1 fluidFlow1Index      fluid flow1 index  [smoFFL] basic variable output  UNPLOTTABLE
      2 fluidState1Index     fluid state1 index [smoTDS] basic variable input  UNPLOTTABLE

   Port 2 has 3 variables:

      1 fluidState2Index     fluid state2 index            [smoTDS]      multi line macro 'smo_r_adaptor_begin_macro0_'  UNPLOTTABLE
      2 smoRChainID          R-components chain ID (port2) [smoRChainID] multi line macro 'smo_r_adaptor_begin_macro1_'
      3 fluidFlow2Index      fluid flow2 index             [smoFFL]      basic variable input  UNPLOTTABLE

   Port 3 has 1 variable:

      1 smoRChainIDToEndAdaptor     R-components chain ID (port3) [smoRChainID] basic variable output
*/

/*  There are 0 internal variables.

*/

void smo_r_adaptor_begin_(int *n, double *fluidFlow1Index
      , double *fluidState1Index, double *fluidState2Index
      , double *smoRChainID, double *fluidFlow2Index
      , double *smoRChainIDToEndAdaptor, int ic[2], void *ps[2])

{
   int loop;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   loop = 0;

/* Common -> SI units conversions. */

/*   *fluidState1Index *= ??; CONVERSION UNKNOWN */
/*   *fluidState2Index *= ??; CONVERSION UNKNOWN */
/*   *smoRChainID *= ??; CONVERSION UNKNOWN */
/*   *fluidFlow2Index *= ??; CONVERSION UNKNOWN */

/*
   Set all submodel outputs below:

   *fluidFlow1Index = ??;
   *smoRChainIDToEndAdaptor = ??;
*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
   SMOCOMPONENT_PRINT_MAIN_CALC
   *fluidFlow1Index = *fluidFlow2Index;
   *smoRChainIDToEndAdaptor = _managerIndex;
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *fluidFlow1Index /= ??; CONVERSION UNKNOWN */
/*   *fluidState1Index /= ??; CONVERSION UNKNOWN */
/*   *fluidState2Index /= ??; CONVERSION UNKNOWN */
/*   *smoRChainID /= ??; CONVERSION UNKNOWN */
/*   *fluidFlow2Index /= ??; CONVERSION UNKNOWN */
/*   *smoRChainIDToEndAdaptor /= ??; CONVERSION UNKNOWN */
}

extern double smo_r_adaptor_begin_macro0_(int *n
      , double *fluidState1Index, int ic[2], void *ps[2])

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
   SMOCOMPONENt_PRINT_MACRO_MSG("state2")
   if (firstc_()) {
	   ManagerComponents_R_addMainState1(_manager, _component, *fluidState1Index);
   }

   fluidState2Index = *fluidState1Index;
/* <<<<<<<<<<<<End of Macro macro0 Executable Statements. */

/* SI -> Common units conversions. */

/*   *fluidState1Index /= ??; CONVERSION UNKNOWN */

/*   *fluidState2Index /= ??; CONVERSION UNKNOWN */

   return fluidState2Index;
}

extern double smo_r_adaptor_begin_macro1_(int *n
      , double *fluidState1Index, int ic[2], void *ps[2])

{
   double smoRChainID;
   int loop;
/* >>>>>>>>>>>>Extra Macro Function macro1 Declarations Here. */
/* <<<<<<<<<<<<End of Extra Macro macro1 declarations. */
   loop = 0;

/* Common -> SI units conversions. */

/*   *fluidState1Index *= ??; CONVERSION UNKNOWN */

/*
   Define and return the following macro variable:

   smoRChainID = ??;
*/


/* >>>>>>>>>>>>Macro Function macro1 Executable Statements. */
   SMOCOMPONENt_PRINT_MACRO_MSG("smoRChainIDPort2")
   smoRChainID = _managerIndex;
/* <<<<<<<<<<<<End of Macro macro1 Executable Statements. */

/* SI -> Common units conversions. */

/*   *fluidState1Index /= ??; CONVERSION UNKNOWN */

/*   *smoRChainID /= ??; CONVERSION UNKNOWN */

   return smoRChainID;
}

