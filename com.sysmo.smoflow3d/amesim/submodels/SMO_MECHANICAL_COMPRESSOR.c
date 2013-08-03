/* Submodel SMO_MECHANICAL_COMPRESSOR skeleton created by AME Submodel editing utility
   Sat Aug 3 18:28:55 2013 */



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

#define _SUBMODELNAME_ "SMO_MECHANICAL_COMPRESSOR"

/* >>>>>>>>>>>>Insert Private Code Here. */
/* <<<<<<<<<<<<End of Private Code. */


/* There is 1 real parameter:

   displacementVolume displacement volume [cm**3 -> m**3]
*/


/* There is 1 integer parameter:

   fluidIndex index of fluid
*/


/* There are 3 text parameters:

   etaVolumetricExpression expression for volumetric efficiency [-] = f(N[rev/min], tau[-l])
   etaIsentropicExpression expression for isentropic efficiency [-] = f(N[rev/min], tau[-]) 
   etaMechanicalExpression expression for mechanical efficiency [-] = f(N[rev/min], tau[-]) 
*/

void smo_mechanical_compressorin_(int *n, double rp[1], int ip[1]
      , char *tp[3], double c[15], int ic[15])

{
   int loop, error;
/* >>>>>>>>>>>>Extra Initialization Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Initialization declarations. */
   int fluidIndex;
   double displacementVolume;
   char *etaVolumetricExpression, *etaIsentropicExpression, 
      *etaMechanicalExpression;

   fluidIndex = ip[0];

   displacementVolume = rp[0];

   etaVolumetricExpression = tp[0];
   etaIsentropicExpression = tp[1];
   etaMechanicalExpression = tp[2];
   loop = 0;
   error = 0;

/*
   If necessary, check values of the following:

   rp[0..0]
*/


/* >>>>>>>>>>>>Initialization Function Check Statements. */
/* <<<<<<<<<<<<End of Initialization Check Statements. */

/*   Integer parameter checking:   */

   if (fluidIndex < 1 || fluidIndex > 99)
   {
      amefprintf(stderr, "\nindex of fluid must be in range [1..99].\n");
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

/* Common -> SI units conversions. */

   rp[0]    *= 1.00000000000000e-006;
   displacementVolume = rp[0];


/* >>>>>>>>>>>>Initialization Function Executable Statements. */
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

/*  There are 3 ports.

   Port 1 has 2 variables:

      1 inletFlow      inlet flow  [smoFFL] basic variable output  UNPLOTTABLE
      2 inletState     inlet state [smoTDS] basic variable input  UNPLOTTABLE

   Port 2 has 2 variables:

      1 outletFlow      outlet flow  [smoFFL] basic variable output  UNPLOTTABLE
      2 outletState     outlet state [smoTDS] basic variable input  UNPLOTTABLE

   Port 3 has 2 variables:

      1 torque          mechanical torque [Nm]               basic variable output
      2 rotarySpeed     rotary speed      [rev/min -> rad/s] basic variable input
*/

/*  There are 6 internal variables.

      1 pressureRatio      pressure ratio        [null] basic variable
      2 etaVolumetric      volumetric efficiency [null] basic variable
      3 etaIsentropic      isentropic efficiency [null] basic variable
      4 etaMechanical      mechanical efficiency [null] basic variable
      5 massFlowRate       mass flow rate        [kg/s] basic variable
      6 compressorWork     compressor work       [W]    basic variable
*/

void smo_mechanical_compressor_(int *n, double *inletFlow
      , double *inletState, double *outletFlow, double *outletState
      , double *torque, double *rotarySpeed, double *pressureRatio
      , double *etaVolumetric, double *etaIsentropic
      , double *etaMechanical, double *massFlowRate
      , double *compressorWork, double rp[1], int ip[1], char *tp[3]
      , double c[15], int ic[15])

{
   int loop;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   int fluidIndex;
   double displacementVolume;
   char *etaVolumetricExpression, *etaIsentropicExpression, 
      *etaMechanicalExpression;

   fluidIndex = ip[0];

   displacementVolume = rp[0];

   etaVolumetricExpression = tp[0];
   etaIsentropicExpression = tp[1];
   etaMechanicalExpression = tp[2];
   loop = 0;

/* Common -> SI units conversions. */

/*   *inletState *= ??; CONVERSION UNKNOWN */
/*   *outletState *= ??; CONVERSION UNKNOWN */
   *rotarySpeed *= 1.04719755119660e-001;

/*
   Set all submodel outputs below:

   *inletFlow  = ??;
   *outletFlow = ??;
   *torque     = ??;
   *pressureRatio = ??;
   *etaVolumetric = ??;
   *etaIsentropic = ??;
   *etaMechanical = ??;
   *massFlowRate = ??;
   *compressorWork = ??;
*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *inletFlow /= ??; CONVERSION UNKNOWN */
/*   *inletState /= ??; CONVERSION UNKNOWN */
/*   *outletFlow /= ??; CONVERSION UNKNOWN */
/*   *outletState /= ??; CONVERSION UNKNOWN */
   *rotarySpeed /= 1.04719755119660e-001;
}

