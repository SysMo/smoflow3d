/* Submodel SMO_R_VIRTUAL_CAPACITY_SENSOR skeleton created by AME Submodel editing utility
   Sun Nov 10 18:47:09 2013 */



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

#define _SUBMODELNAME_ "SMO_R_VIRTUAL_CAPACITY_SENSOR"

/* >>>>>>>>>>>>Insert Private Code Here. */
#include "SmoFlowAme.h"
#include "media/MediumState.h"

#define _fluidState ps[0]
/* <<<<<<<<<<<<End of Private Code. */


/* There are 2 real parameters:

   offset signal offset [null]
   gain   signal gain   [null]
*/


/* There is 1 integer parameter:

   propertyIndex measured fluid property
*/

void smo_r_virtual_capacity_sensorin_(int *n, double rp[2], int ip[1]
      , double c[19], void *ps[1])

{
   int loop, error;
/* >>>>>>>>>>>>Extra Initialization Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Initialization declarations. */
   int propertyIndex;
   double offset, gain;

   propertyIndex = ip[0];

   offset     = rp[0];
   gain       = rp[1];
   loop = 0;
   error = 0;

/*
   If necessary, check values of the following:

   rp[0..1]
*/


/* >>>>>>>>>>>>Initialization Function Check Statements. */
/* <<<<<<<<<<<<End of Initialization Check Statements. */

/*   Integer parameter checking:   */

   if (propertyIndex < 1 || propertyIndex > 19)
   {
      amefprintf(stderr, "\nmeasured fluid property must be in range [1..19].\n");
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

/*  There are 3 ports.

   Port 1 has 3 variables:

      1 fluidStateIndexDupl     duplicate of fluidStateIndex
      2 smoRChainIDDupl         duplicate of smoRChainID
      3 fluidFlowIndex          fluid flow index      [smoFFL] basic variable input  UNPLOTTABLE

   Port 2 has 1 variable:

      1 measuredValue     measured value [null] basic variable output

   Port 3 has 3 variables:

      1 fluidFlowIndexDupl     duplicate of fluidFlowIndex
      2 fluidStateIndex        fluid state index     [smoTDS]      basic variable input  UNPLOTTABLE
      3 smoRChainID            R-components chain ID [smoRChainID] basic variable input
*/

/*  There are 19 internal variables.

      1 pressure                    pressure                            [bar -> Pa]         basic variable
      2 temperature                 temperature                         [K]                 basic variable
      3 temperatureC                temperature (°C)                    [degC]              basic variable
      4 density                     density                             [kg/m**3]           basic variable
      5 specificVolume              specific volume                     [m**3/kg]           basic variable
      6 internalEnergy              specific internal energy            [kJ/kg -> J/kg]     basic variable
      7 enthalpy                    specific enthalpy                   [kJ/kg -> J/kg]     basic variable
      8 specificEntropy             specific entropy                    [kJ/kg/K -> J/kg/K] basic variable
      9 cp                          specific heat  at constant pressure [J/kg/degC]         basic variable
     10 cv                          specific heat  at constant volume   [J/kg/degC]         basic variable
     11 specificHelmholtzEnergy     specific helmholtz energy           [kJ/kg -> J/kg]     basic variable
     12 specificGibbsEnergy         specific gibbs energy               [kJ/kg -> J/kg]     basic variable
     13 gasMassFraction             gas mass fraction                   [null]              basic variable
     14 superheating                superheating                        [K]                 basic variable
     15 dpc                         (p - pcrit)                         [bar -> Pa]         basic variable
     16 mu                          dynamic viscosity                   [kg/m/s -> Ns/m**2] basic variable
     17 lambda                      thermal conductivity                [W/m/degC]          basic variable
     18 Pr                          Prandtl number                      [null]              basic variable
     19 sigma                       surface tension                     [N/m]               basic variable
*/

void smo_r_virtual_capacity_sensor_(int *n, double *fluidFlowIndex
      , double *measuredValue, double *fluidStateIndex
      , double *smoRChainID, double *pressure, double *temperature
      , double *temperatureC, double *density, double *specificVolume
      , double *internalEnergy, double *enthalpy
      , double *specificEntropy, double *cp, double *cv
      , double *specificHelmholtzEnergy, double *specificGibbsEnergy
      , double *gasMassFraction, double *superheating, double *dpc
      , double *mu, double *lambda, double *Pr, double *sigma
      , double rp[2], int ip[1], double c[19], void *ps[1])

{
   int loop;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   int propertyIndex;
   double offset, gain;

   propertyIndex = ip[0];

   offset     = rp[0];
   gain       = rp[1];
   loop = 0;

/* Common -> SI units conversions. */

/*   *fluidFlowIndex *= ??; CONVERSION UNKNOWN */
/*   *fluidStateIndex *= ??; CONVERSION UNKNOWN */
/*   *smoRChainID *= ??; CONVERSION UNKNOWN */

/*
   Set all submodel outputs below:

   *measuredValue = ??;
   *pressure   = ??;
   *temperature = ??;
   *temperatureC = ??;
   *density    = ??;
   *specificVolume = ??;
   *internalEnergy = ??;
   *enthalpy   = ??;
   *specificEntropy = ??;
   *cp         = ??;
   *cv         = ??;
   *specificHelmholtzEnergy = ??;
   *specificGibbsEnergy = ??;
   *gasMassFraction = ??;
   *superheating = ??;
   *dpc        = ??;
   *mu         = ??;
   *lambda     = ??;
   *Pr         = ??;
   *sigma      = ??;
*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
   SMOCOMPONENT_PRINT_MAIN_CALC
   if (firstc_()) {
	   _fluidState = MediumState_get(*fluidStateIndex);
   }

   static const double outputInternalGain[19] = {
		   1e-5, 1, 1, 1, 1,
		   1e-3, 1e-3, 1e-3, 1e-3, 1,
		   1, 1, 1, 1, 1,
		   1, 1, 1, 1
   };

   c[0] = MediumState_p(_fluidState);
   c[1] = MediumState_T(_fluidState);
   c[2] = c[1] - 273.15;
   c[3] = MediumState_rho(_fluidState);
   c[4] = 1./c[3];
   c[5] = MediumState_u(_fluidState);
   c[6] = MediumState_h(_fluidState);
   //c[7] = MediumState_s(fluidState);
   c[8] = MediumState_cp(_fluidState);
   c[9] = MediumState_cv(_fluidState);
   //c[10] = MediumState_(fluidState);
   //c[11] = MediumState_(fluidState);
   c[12] = MediumState_q(_fluidState);
   c[13] = MediumState_deltaTSat(_fluidState);
   //c[14] = MediumState_(fluidState);
   c[15] = MediumState_mu(_fluidState);
   c[16] = MediumState_lambda(_fluidState);
   c[17] = MediumState_Pr(_fluidState);
   //c[18] = MediumState_(fluidState);


   *measuredValue = c[propertyIndex - 1] * outputInternalGain[propertyIndex - 1] * gain + offset;
   *pressure = c[0];
   *temperature = c[1];
   *temperatureC = c[2];
   *density = c[3];
   *specificVolume = c[4];
   *internalEnergy = c[5];
   *enthalpy = c[6];
   //c[7] = MediumState_s(fluidState);
   *cp = c[8];
   *cv = c[9];
   //c[10] = MediumState_(fluidState);
   //c[11] = MediumState_(fluidState);
   *gasMassFraction = c[12];
   *superheating = c[13];
   //c[14] = MediumState_(fluidState);
   *mu = c[15];
   *lambda = c[16];
   *Pr = c[17];
   //c[18] = MediumState_(fluidState);
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *fluidFlowIndex /= ??; CONVERSION UNKNOWN */
/*   *fluidStateIndex /= ??; CONVERSION UNKNOWN */
/*   *smoRChainID /= ??; CONVERSION UNKNOWN */
   *pressure /= 1.00000000000000e+005;
   *internalEnergy /= 1.00000000000000e+003;
   *enthalpy /= 1.00000000000000e+003;
   *specificEntropy /= 1.00000000000000e+003;
   *specificHelmholtzEnergy /= 1.00000000000000e+003;
   *specificGibbsEnergy /= 1.00000000000000e+003;
   *dpc      /= 1.00000000000000e+005;
}

