/* Submodel SMO_FLUID_STATE_SENSOR skeleton created by AME Submodel editing utility
   Fri Feb 3 08:22:03 2017 */



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

#define _SUBMODELNAME_ "SMO_FLUID_STATE_SENSOR"

/* >>>>>>>>>>>>Insert Private Code Here. */
#include "SmoFlowAme.h"
#include "media/MediumState.h"
 
#define _fluidStateIndex ic[0]
#define _fluidState ps[0]
/* <<<<<<<<<<<<End of Private Code. */


/* There are 2 real parameters:

   offset signal offset [null]
   gain   signal gain   [null]
*/


/* There is 1 integer parameter:

   propertyIndex measured fluid property
*/

void smo_fluid_state_sensorin_(int *n, double rp[2], int ip[1]
      , double c[22], int ic[1], void *ps[1])

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

   if (propertyIndex < 1 || propertyIndex > 23)
   {
      amefprintf(stderr, "\nmeasured fluid property must be in range [1..23].\n");
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

      1 fluidStateIndexDup            duplicate of fluidStateIndex
      2 fluidFlowIndex                fluid flow index             [smoFFL]  basic variable input  UNPLOTTABLE
      3 fluidFlowActivationSignal     fluid flow activation signal [smoFFAS] basic variable input

   Port 2 has 1 variable:

      1 measuredValue     measured value [null] multi line macro 'smo_fluid_state_sensor_macro0_'

   Port 3 has 3 variables:

      1 fluidFlowIndexDup                duplicate of fluidFlowIndex 
      2 fluidFlowActivationSignalDup     duplicate of fluidFlowActivationSignal
      3 fluidStateIndex                  fluid state index            [smoTDS] basic variable input  UNPLOTTABLE
*/

/*  There are 22 internal variables.

      1 pressure                    pressure                            [barA -> PaA]       basic variable
      2 pressureG                   gauge pressure                      [bar -> Pa]         basic variable
      3 temperature                 temperature                         [K]                 basic variable
      4 temperatureC                temperature (�C)                    [degC]              basic variable
      5 density                     density                             [kg/m**3]           basic variable
      6 specificVolume              specific volume                     [m**3/kg]           basic variable
      7 internalEnergy              specific internal energy            [kJ/kg -> J/kg]     basic variable
      8 enthalpy                    specific enthalpy                   [kJ/kg -> J/kg]     basic variable
      9 specificEntropy             specific entropy                    [kJ/kg/K -> J/kg/K] basic variable
     10 cp                          specific heat  at constant pressure [J/kg/degC]         basic variable
     11 cv                          specific heat  at constant volume   [J/kg/degC]         basic variable
     12 specificHelmholtzEnergy     specific helmholtz energy           [kJ/kg -> J/kg]     basic variable
     13 specificGibbsEnergy         specific gibbs energy               [kJ/kg -> J/kg]     basic variable
     14 gasMassFraction             gas mass fraction                   [null]              basic variable
     15 superheating                superheating                        [K]                 basic variable
     16 dpc                         (p - pcrit)                         [barA -> PaA]       basic variable
     17 mu                          dynamic viscosity                   [kg/m/s -> Ns/m**2] basic variable
     18 lambda                      thermal conductivity                [W/m/degC]          basic variable
     19 Pr                          Prandtl number                      [null]              basic variable
     20 sigma                       surface tension                     [N/m]               basic variable
     21 gasVolumeFraction           gas volume fraction                 [null]              basic variable
     22 liquidLevel                 liquid level                        [null]              basic variable
*/

void smo_fluid_state_sensor_(int *n, double *fluidFlowIndex
      , double *fluidFlowActivationSignal, double *measuredValue
      , double *fluidStateIndex, double *pressure, double *pressureG
      , double *temperature, double *temperatureC, double *density
      , double *specificVolume, double *internalEnergy
      , double *enthalpy, double *specificEntropy, double *cp
      , double *cv, double *specificHelmholtzEnergy
      , double *specificGibbsEnergy, double *gasMassFraction
      , double *superheating, double *dpc, double *mu, double *lambda
      , double *Pr, double *sigma, double *gasVolumeFraction
      , double *liquidLevel, double rp[2], int ip[1], double c[22]
      , int ic[1], void *ps[1])

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

/*   *fluidFlowIndex *= ??; CONVERSION UNKNOWN [smoFFL] */
/*   *fluidFlowActivationSignal *= ??; CONVERSION UNKNOWN [smoFFAS] */
/*   *fluidStateIndex *= ??; CONVERSION UNKNOWN [smoTDS] */

/*
   Set all submodel outputs below:

   *pressure   = ??;
   *pressureG  = ??;
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
   *gasVolumeFraction = ??;
   *liquidLevel = ??;
*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
   SMOCOMPONENT_PRINT_MAIN_CALC
   *pressure = c[0];
   *pressureG = c[1];
   *temperature = c[2];
   *temperatureC = c[3];
   *density = c[4];
   *specificVolume = c[5];
   *internalEnergy = c[6];
   *enthalpy = c[7];
   //c[8] = MediumState_s(fluidState);
   *cp = c[9];
   *cv = c[10];
   //c[11] = MediumState_(fluidState);
   //c[12] = MediumState_(fluidState);
   *gasMassFraction = c[13];
   *superheating = c[14];
   //c[15] = MediumState_(fluidState);
   *mu = c[16];
   *lambda = c[17];
   *Pr = c[18];
   //c[18] = MediumState_(fluidState);
   *gasVolumeFraction = c[20];
   *liquidLevel = c[21];
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *fluidFlowIndex /= ??; CONVERSION UNKNOWN [smoFFL] */
/*   *fluidFlowActivationSignal /= ??; CONVERSION UNKNOWN [smoFFAS] */
/*   *fluidStateIndex /= ??; CONVERSION UNKNOWN [smoTDS] */
   *pressure /= 1.00000000000000e+005;
   *pressureG /= 1.00000000000000e+005;
   *internalEnergy /= 1.00000000000000e+003;
   *enthalpy /= 1.00000000000000e+003;
   *specificEntropy /= 1.00000000000000e+003;
   *specificHelmholtzEnergy /= 1.00000000000000e+003;
   *specificGibbsEnergy /= 1.00000000000000e+003;
   *dpc      /= 1.00000000000000e+005;
}

extern double smo_fluid_state_sensor_macro0_(int *n
      , double *fluidStateIndex, double rp[2], int ip[1], double c[22]
      , int ic[1], void *ps[1])

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

/*   *fluidStateIndex *= ??; CONVERSION UNKNOWN [smoTDS] */

/*
   Define and return the following macro variable:

   measuredValue = ??;
*/


/* >>>>>>>>>>>>Macro Function macro0 Executable Statements. */
   SMOCOMPONENt_PRINT_MACRO
   if (firstc_()) {
	   _fluidStateIndex = *fluidStateIndex;
	   _fluidState = MediumState_get(_fluidStateIndex);
   }
 
   static const double outputInternalGain[22] = {
		   1e-5, 1e-5, 1, 1, 1, 1,
		   1e-3, 1e-3, 1e-3, 1e-3, 1,
		   1, 1, 1, 1, 1,
		   1, 1, 1, 1, 1, 1
   };
 
   c[0] = MediumState_p(_fluidState);
   c[1] = c[0] - 101325;
   c[2] = MediumState_T(_fluidState);
   c[3] = c[2] - 273.15;
   c[4] = MediumState_rho(_fluidState);
   c[5] = 1./c[4];
   c[6] = MediumState_u(_fluidState);
   c[7] = MediumState_h(_fluidState);
   //c[8] = MediumState_s(fluidState);
   c[9] = MediumState_cp(_fluidState);
   c[10] = MediumState_cv(_fluidState);
   //c[11] = MediumState_(fluidState);
   //c[12] = MediumState_(fluidState);
   c[13] = MediumState_q(_fluidState);
   c[14] = MediumState_deltaTSat(_fluidState);
   //c[15] = MediumState_(fluidState);
   c[16] = MediumState_mu(_fluidState);
   c[17] = MediumState_lambda(_fluidState);
   c[18] = MediumState_Pr(_fluidState);
   //c[19] = MediumState_(fluidState);
   c[20] = MediumState_qV(_fluidState); //gas volume fraction
 
   if (c[20] == -1) {
	   c[21] = -1; //liquid level
   } else {
	   c[21] = 1 - c[20]; //liquid level
   }
 
   if (propertyIndex == 22) {
	   measuredValue = _fluidStateIndex;
   } else {
	   measuredValue = c[propertyIndex - 1]
		 * outputInternalGain[propertyIndex - 1] * gain + offset;
   }
/* <<<<<<<<<<<<End of Macro macro0 Executable Statements. */

/* SI -> Common units conversions. */

/*   *fluidStateIndex /= ??; CONVERSION UNKNOWN [smoTDS] */


   return measuredValue;
}

