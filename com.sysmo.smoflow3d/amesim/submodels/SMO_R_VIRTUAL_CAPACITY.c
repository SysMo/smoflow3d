/* Submodel SMO_R_VIRTUAL_CAPACITY skeleton created by AME Submodel editing utility
   Sun Nov 10 14:11:48 2013 */



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

#define _SUBMODELNAME_ "SMO_R_VIRTUAL_CAPACITY"

/* >>>>>>>>>>>>Insert Private Code Here. */
#include "SmoFlowAme.h"
#include "flow/FlowBase.h"
#include "media/MediumState.h"
#include "flow_R/VirtualCapacity_R.h"
#include "flow_R/ManagerComponents_R.h"

#define _component ps[0]

#define _fluidState ps[1]
#define _fluidStateIndex ic[0]
/* <<<<<<<<<<<<End of Private Code. */

/* There is 1 integer parameter:

   fluidIndex fluid index
*/

void smo_r_virtual_capacityin_(int *n, int ip[1], int ic[1]
      , void *ps[3])

{
   int loop, error;
/* >>>>>>>>>>>>Extra Initialization Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Initialization declarations. */
   int fluidIndex;

   fluidIndex = ip[0];
   loop = 0;
   error = 0;


/* >>>>>>>>>>>>Initialization Function Check Statements. */
/* <<<<<<<<<<<<End of Initialization Check Statements. */

/*   Integer parameter checking:   */

   if (fluidIndex < 1 || fluidIndex > 99)
   {
      amefprintf(stderr, "\nfluid index must be in range [1..99].\n");
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
   Medium* fluid = Medium_get(fluidIndex);
   _component = VirtualCapacity_R_new(fluid);
   SMOCOMPONENT_SET_PROPS(_component);

   _fluidState = VirtualCapacity_R_getState(_component);
   _fluidStateIndex = VirtualCapacity_R_getStateIndex(_component);
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

/*  There are 2 ports.

   Port 1 has 3 variables:

      1 fluidState1Index     fluid state1  index   [smoTDS]      basic variable output  UNPLOTTABLE
      2 fluidFlow1Index      fluid flow1 index     [smoFFL]      basic variable input  UNPLOTTABLE
      3 smoRChainID          R-components chain ID [smoRChainID] basic variable input

   Port 2 has 3 variables:

      1 fluidState2Index     fluid state2 index    [smoTDS] multi line macro 'smo_r_virtual_capacity_macro0_'  UNPLOTTABLE
      2 smoRChainIDDupl      duplicate of smoRChainID
      3 fluidFlow2Index      fluid flow2 index     [smoFFL] basic variable input  UNPLOTTABLE
*/

/*  There are 5 internal variables.

      1 pressure             pressure          [bar -> Pa]     basic variable
      2 temperature          temperature       [K]             basic variable
      3 density              density           [kg/m**3]       basic variable
      4 specificEnthalpy     specific enthalpy [kJ/kg -> J/kg] basic variable
      5 gasMassFraction      gas mass fraction [null]          basic variable
*/

void smo_r_virtual_capacity_(int *n, double *fluidState1Index
      , double *fluidFlow1Index, double *smoRChainID
      , double *fluidState2Index, double *fluidFlow2Index
      , double *pressure, double *temperature, double *density
      , double *specificEnthalpy, double *gasMassFraction, int ip[1]
      , int ic[1], void *ps[3])

{
   int loop;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   int fluidIndex;

   fluidIndex = ip[0];
   loop = 0;

/* Common -> SI units conversions. */

/*   *fluidFlow1Index *= ??; CONVERSION UNKNOWN */
/*   *smoRChainID *= ??; CONVERSION UNKNOWN */
/*   *fluidState2Index *= ??; CONVERSION UNKNOWN */
/*   *fluidFlow2Index *= ??; CONVERSION UNKNOWN */

/*
   Set all submodel outputs below:

   *fluidState1Index = ??;
   *pressure   = ??;
   *temperature = ??;
   *density    = ??;
   *specificEnthalpy = ??;
   *gasMassFraction = ??;
*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
   SMOCOMPONENT_PRINT_MAIN_CALC
   *fluidState1Index = _fluidStateIndex;

   *pressure = MediumState_p(_fluidState);
   *temperature = MediumState_T(_fluidState);
   *density = MediumState_rho(_fluidState);
   *specificEnthalpy = MediumState_h(_fluidState);
   *gasMassFraction = MediumState_q(_fluidState);
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *fluidState1Index /= ??; CONVERSION UNKNOWN */
/*   *fluidFlow1Index /= ??; CONVERSION UNKNOWN */
/*   *smoRChainID /= ??; CONVERSION UNKNOWN */
/*   *fluidState2Index /= ??; CONVERSION UNKNOWN */
/*   *fluidFlow2Index /= ??; CONVERSION UNKNOWN */
   *pressure /= 1.00000000000000e+005;
   *specificEnthalpy /= 1.00000000000000e+003;
}

extern double smo_r_virtual_capacity_macro0_(int *n
      , double *fluidFlow1Index, int ip[1], int ic[1], void *ps[3])

{
   double fluidState2Index;
   int loop;
/* >>>>>>>>>>>>Extra Macro Function macro0 Declarations Here. */
/* <<<<<<<<<<<<End of Extra Macro macro0 declarations. */
   int fluidIndex;

   fluidIndex = ip[0];
   loop = 0;

/* Common -> SI units conversions. */

/*   *fluidFlow1Index *= ??; CONVERSION UNKNOWN */

/*
   Define and return the following macro variable:

   fluidState2Index = ??;
*/


/* >>>>>>>>>>>>Macro Function macro0 Executable Statements. */
   SMOCOMPONENt_PRINT_MACRO_MSG("state2")
   if (firstc_()) {
	   ManagerComponents_R_addVirtualCapacity(_component, *fluidFlow1Index);
   }

   fluidState2Index = _fluidStateIndex;
/* <<<<<<<<<<<<End of Macro macro0 Executable Statements. */

/* SI -> Common units conversions. */

/*   *fluidFlow1Index /= ??; CONVERSION UNKNOWN */

/*   *fluidState2Index /= ??; CONVERSION UNKNOWN */

   return fluidState2Index;
}

