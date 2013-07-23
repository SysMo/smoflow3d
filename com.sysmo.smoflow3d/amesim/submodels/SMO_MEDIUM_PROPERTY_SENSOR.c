/* Submodel SMO_MEDIUM_PROPERTY_SENSOR skeleton created by AME Submodel editing utility
   Tue Jul 23 18:35:04 2013 */



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

#define _SUBMODELNAME_ "SMO_MEDIUM_PROPERTY_SENSOR"

/* >>>>>>>>>>>>Insert Private Code Here. */
/* <<<<<<<<<<<<End of Private Code. */


/* There are 2 real parameters:

   offset signal offset [null]
   gain   signal gain   [null]
*/


/* There is 1 integer parameter:

   propertyIndex measured fluid property
*/

void smo_medium_property_sensorin_(int *n, double rp[2], int ip[1]
      , double c[15], int ic[5])

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

   if (propertyIndex < 1 || propertyIndex > 18)
   {
      amefprintf(stderr, "\nmeasured fluid property must be in range [1..18].\n");
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

      1 stateIndexDup     duplicate of stateIndex  
      2 dmh1              enthalpy flow rate port 1 [W]    basic variable input  UNPLOTTABLE
      3 dm1               mass flow rate port 1     [kg/s] basic variable input  UNPLOTTABLE

   Port 2 has 1 variable:

      1 measuredValue     measured value [null] multi line macro 'smo_medium_property_sensor_macro0_'

   Port 3 has 3 variables:

      1 dmh3           duplicate of dmh1        
      2 dm3            duplicate of dm1         
      3 stateIndex     state index               [smoTDS] basic variable input  UNPLOTTABLE
*/

/*  There are 16 internal variables.

      1 specificVolume              specific volume                     [m**3/kg]           basic variable
      2 temperatureC                temperature                         [degC]              basic variable
      3 internalEnergy              specific internal energy            [kJ/kg -> J/kg]     basic variable
      4 enthalpy                    specific enthalpy                   [kJ/kg -> J/kg]     basic variable
      5 specificEntropy             specific entropy                    [kJ/kg/K -> J/kg/K] basic variable
      6 cp                          specific heat  at constant pressure [J/kg/degC]         basic variable
      7 cv                          specific heat  at constant volume   [J/kg/degC]         basic variable
      8 specificHelmholtzEnergy     specific helmholtz energy           [kJ/kg -> J/kg]     basic variable
      9 specificGibbsEnergy         specific gibbs energy               [kJ/kg -> J/kg]     basic variable
     10 gasMassFraction             gas mass fraction                   [null]              basic variable
     11 superHeating                superheat / subcooling              [degC]              basic variable
     12 dpc                         (p - pcrit)                         [barA -> PaA]       basic variable
     13 mu                          absolute viscosity                  [kg/m/s -> Ns/m**2] basic variable
     14 lambda                      thermal conductivity                [W/m/degC]          basic variable
     15 Pr                          Prandtl number                      [null]              basic variable
     16 sigma                       surface tension                     [N/m]               basic variable
*/

void smo_medium_property_sensor_(int *n, double *dmh1, double *dm1
      , double *measuredValue, double *stateIndex
      , double *specificVolume, double *temperatureC
      , double *internalEnergy, double *enthalpy
      , double *specificEntropy, double *cp, double *cv
      , double *specificHelmholtzEnergy, double *specificGibbsEnergy
      , double *gasMassFraction, double *superHeating, double *dpc
      , double *mu, double *lambda, double *Pr, double *sigma
      , double rp[2], int ip[1], double c[15], int ic[5])

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

/*   *stateIndex *= ??; CONVERSION UNKNOWN */

/*
   Set all submodel outputs below:

   *specificVolume = ??;
   *temperatureC = ??;
   *internalEnergy = ??;
   *enthalpy   = ??;
   *specificEntropy = ??;
   *cp         = ??;
   *cv         = ??;
   *specificHelmholtzEnergy = ??;
   *specificGibbsEnergy = ??;
   *gasMassFraction = ??;
   *superHeating = ??;
   *dpc        = ??;
   *mu         = ??;
   *lambda     = ??;
   *Pr         = ??;
   *sigma      = ??;
*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *stateIndex /= ??; CONVERSION UNKNOWN */
   *internalEnergy /= 1.00000000000000e+003;
   *enthalpy /= 1.00000000000000e+003;
   *specificEntropy /= 1.00000000000000e+003;
   *specificHelmholtzEnergy /= 1.00000000000000e+003;
   *specificGibbsEnergy /= 1.00000000000000e+003;
   *dpc      /= 1.00000000000000e+005;
}

extern double smo_medium_property_sensor_macro0_(int *n
      , double *stateIndex, double rp[2], int ip[1], double c[15]
      , int ic[5])

{
   double measuredValue;
   int loop;
/* >>>>>>>>>>>>Extra Macro Function macro0 Declarations Here. */
/* <<<<<<<<<<<<End of Extra Macro macro0 declarations. */
   int propertyIndex;
   double offset, gain;

   propertyIndex = ip[0];

   offset     = rp[0];
   gain       = rp[1];
   loop = 0;

/* Common -> SI units conversions. */

/*   *stateIndex *= ??; CONVERSION UNKNOWN */

/*
   Define and return the following macro variable:

   measuredValue = ??;
*/


/* >>>>>>>>>>>>Macro Function macro0 Executable Statements. */
/* <<<<<<<<<<<<End of Macro macro0 Executable Statements. */

/* SI -> Common units conversions. */

/*   *stateIndex /= ??; CONVERSION UNKNOWN */


   return measuredValue;
}

