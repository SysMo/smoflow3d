/* Submodel SMO_R_VIRTUAL_CAPACITY skeleton created by AME Submodel editing utility
   Fri Nov 8 11:22:48 2013 */



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

#define _component ps[0]
#define _fluidState ps[1]
#define _fluidFlow1 ps[2]
/* <<<<<<<<<<<<End of Private Code. */

/* There is 1 integer parameter:

   fluidIndex fluid index
*/

void smo_r_virtual_capacityin_(int *n, int ip[1], void *ps[3]
      , double *fluidStateIndex)

{
   int loop, error;
/* >>>>>>>>>>>>Extra Initialization Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Initialization declarations. */
   int fluidIndex;

   fluidIndex = ip[0];
   loop = 0;
   error = 0;

/*
   Check and/or reset the following fixed and/or discrete variable

   *fluidStateIndex = ??;
*/


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
   *fluidStateIndex = VirtualCapacity_R_getStateIndex(_component);
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

/*  There are 2 ports.

   Port 1 has 3 variables:

      1 fluidStateIndex     fluid state index                    [smoTDS] fixed  UNPLOTTABLE
      2 fluidFlow1Index     fluid flow index 1                   [smoFFL] basic variable input  UNPLOTTABLE
      3 port1R              R-component indentification (port 1) [R]      basic variable input  UNPLOTTABLE

   Port 2 has 3 variables:

      1 stateIndexDup       duplicate of fluidStateIndex        
      2 fluidFlow2Index     fluid flow index 2                   [smoFFL] basic variable input  UNPLOTTABLE
      3 port2R              R-component indentification (port 2) [R]      basic variable input  UNPLOTTABLE
*/

/*  There are 7 internal variables.

      1 massFlowRate         mass flow rate (at port2)     [kg/s]          basic variable
      2 enthalpyFlowRate     enthalpy flow rate (at port2) [W]             basic variable
      3 pressure             flow pressure                 [bar -> Pa]     basic variable
      4 temperature          flow temperature              [K]             basic variable
      5 density              density                       [kg/m**3]       basic variable
      6 specificEnthalpy     specific enthalpy             [kJ/kg -> J/kg] basic variable
      7 gasMassFraction      gas mass fraction             [null]          basic variable
*/

void smo_r_virtual_capacity_(int *n, double *fluidFlow1Index
      , double *port1R, double *fluidFlow2Index, double *port2R
      , double *massFlowRate, double *enthalpyFlowRate
      , double *pressure, double *temperature, double *density
      , double *specificEnthalpy, double *gasMassFraction, int ip[1]
      , void *ps[3])

{
   int loop;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   int fluidIndex;

   fluidIndex = ip[0];
   loop = 0;

/* Common -> SI units conversions. */

/*   *fluidFlow1Index *= ??; CONVERSION UNKNOWN */
/*   *port1R   *= ??; CONVERSION UNKNOWN */
/*   *fluidFlow2Index *= ??; CONVERSION UNKNOWN */
/*   *port2R   *= ??; CONVERSION UNKNOWN */

/*
   Set all submodel outputs below:

   *massFlowRate = ??;
   *enthalpyFlowRate = ??;
   *pressure   = ??;
   *temperature = ??;
   *density    = ??;
   *specificEnthalpy = ??;
   *gasMassFraction = ??;
*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
   SMOCOMPONENT_PRINT_MAIN_CALC
   if (firstc_()) {
   	   _fluidFlow1 = FluidFlow_get(*fluidFlow1Index);
   }

   *massFlowRate = FluidFlow_getMassFlowRate(_fluidFlow1);
   *enthalpyFlowRate = FluidFlow_getEnthalpyFlowRate(_fluidFlow1);

   *pressure = MediumState_p(_fluidState);
   *temperature = MediumState_T(_fluidState);
   *density = MediumState_rho(_fluidState);
   *specificEnthalpy = MediumState_h(_fluidState);
   *gasMassFraction = MediumState_q(_fluidState);
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *fluidFlow1Index /= ??; CONVERSION UNKNOWN */
/*   *port1R   /= ??; CONVERSION UNKNOWN */
/*   *fluidFlow2Index /= ??; CONVERSION UNKNOWN */
/*   *port2R   /= ??; CONVERSION UNKNOWN */
   *pressure /= 1.00000000000000e+005;
   *specificEnthalpy /= 1.00000000000000e+003;
}

