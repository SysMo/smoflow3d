/* Submodel SMO_MECHANICAL_COMPRESSOR skeleton created by AME Submodel editing utility
   Fri Aug 9 12:11:22 2013 */



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
#include "SmoFlowAme.h"
#include "flow/MechanicalCompressor.h"
#include "math/Functors.h"

#define _component ps[0]

#define _inletFlow ps[1]
#define _inletFlowIndex ic[1]

#define _outletFlow ps[2]
#define _outletFlowIndex ic[2]
/* <<<<<<<<<<<<End of Private Code. */


/* There is 1 real parameter:

   displacementVolume displacement volume [cm**3 -> m**3]
*/


/* There is 1 integer parameter:

   flowRateCalculationMethod flow rate calculation method
*/


/* There are 4 text parameters:

   etaVolumetricExpression      expression for volumetric efficiency [-] = f(N[rev/min], tau[-l])  
   volumetricFlowRateExpression expression for volumetric flow rate [m^3/s] = f(N[rev/min], tau[-])
   etaIsentropicExpression      expression for isentropic efficiency [-] = f(N[rev/min], tau[-])   
   etaMechanicalExpression      expression for mechanical efficiency [-] = f(N[rev/min], tau[-])   
*/

void smo_mechanical_compressorin_(int *n, double rp[1], int ip[1]
      , char *tp[4], int ic[3], void *ps[3])

{
   int loop, error;
/* >>>>>>>>>>>>Extra Initialization Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Initialization declarations. */
   int flowRateCalculationMethod;
   double displacementVolume;
   char *etaVolumetricExpression, *volumetricFlowRateExpression, 
      *etaIsentropicExpression, *etaMechanicalExpression;

   flowRateCalculationMethod = ip[0];

   displacementVolume = rp[0];

   etaVolumetricExpression = tp[0];
   volumetricFlowRateExpression = tp[1];
   etaIsentropicExpression = tp[2];
   etaMechanicalExpression = tp[3];
   loop = 0;
   error = 0;

/*
   If necessary, check values of the following:

   rp[0..0]
*/


/* >>>>>>>>>>>>Initialization Function Check Statements. */
/* <<<<<<<<<<<<End of Initialization Check Statements. */

/*   Integer parameter checking:   */

   if (flowRateCalculationMethod < 1 || flowRateCalculationMethod > 2)
   {
      amefprintf(stderr, "\nflow rate calculation method must be in range [1..2].\n");
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
   _component = MechanicalCompressor_new();
   SMOCOMPONEN_SET_PROPS(_component)

   _inletFlow = FluidFlow_new();
   _inletFlowIndex = FluidFlow_register(_inletFlow);
   _outletFlow = FluidFlow_new();
   _outletFlowIndex = FluidFlow_register(_outletFlow);

   if (flowRateCalculationMethod == 1) {
	   MechanicalCompressor_setDisplacementVolume(_component, displacementVolume);
	   MechanicalCompressor_setVolumetricEfficiencyFunction(_component,
			   FunctorTwoVariables_Expression_new(etaVolumetricExpression, "N", "tau"));
   } else {
	   MechanicalCompressor_setVolumetricFlowRateFunction(_component,
			   FunctorTwoVariables_Expression_new(volumetricFlowRateExpression, "N", "tau"));
   }
   MechanicalCompressor_setIsentropicEfficiencyFunction(_component,
		   FunctorTwoVariables_Expression_new(etaIsentropicExpression, "N", "tau"));
   MechanicalCompressor_setMechanicalEfficiencyFunction(_component,
		   FunctorTwoVariables_Expression_new(etaMechanicalExpression, "N", "tau"));
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

/*  There are 3 ports.

   Port 1 has 2 variables:

      1 inletFlowIndex      inlet flow index  [smoFFL] basic variable output  UNPLOTTABLE
      2 inletStateIndex     inlet state index [smoTDS] basic variable input  UNPLOTTABLE

   Port 2 has 2 variables:

      1 outletFlowIndex      outlet flow index  [smoFFL] basic variable output  UNPLOTTABLE
      2 outletStateIndex     outlet state index [smoTDS] basic variable input  UNPLOTTABLE

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

void smo_mechanical_compressor_(int *n, double *inletFlowIndex
      , double *inletStateIndex, double *outletFlowIndex
      , double *outletStateIndex, double *torque, double *rotarySpeed
      , double *pressureRatio, double *etaVolumetric
      , double *etaIsentropic, double *etaMechanical
      , double *massFlowRate, double *compressorWork, double rp[1]
      , int ip[1], char *tp[4], int ic[3], void *ps[3])

{
   int loop;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   int flowRateCalculationMethod;
   double displacementVolume;
   char *etaVolumetricExpression, *volumetricFlowRateExpression, 
      *etaIsentropicExpression, *etaMechanicalExpression;

   flowRateCalculationMethod = ip[0];

   displacementVolume = rp[0];

   etaVolumetricExpression = tp[0];
   volumetricFlowRateExpression = tp[1];
   etaIsentropicExpression = tp[2];
   etaMechanicalExpression = tp[3];
   loop = 0;

/* Common -> SI units conversions. */

/*   *inletStateIndex *= ??; CONVERSION UNKNOWN */
/*   *outletStateIndex *= ??; CONVERSION UNKNOWN */
   *rotarySpeed *= 1.04719755119660e-001;

/*
   Set all submodel outputs below:

   *inletFlowIndex = ??;
   *outletFlowIndex = ??;
   *torque     = ??;
   *pressureRatio = ??;
   *etaVolumetric = ??;
   *etaIsentropic = ??;
   *etaMechanical = ??;
   *massFlowRate = ??;
   *compressorWork = ??;
*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
   if (firstc_()) {
	   MediumState* inletState = MediumState_get(*inletStateIndex);
	   MediumState* outletState = MediumState_get(*outletStateIndex);
	   MechanicalCompressor_init(_component, inletState, outletState);
   }

   if (*rotarySpeed > 1e-12) {
	   MechanicalCompressor_setRotationalSpeed(_component, *rotarySpeed);
	   MechanicalCompressor_compute(_component);
	   MechanicalCompressor_getInletFlowRates(_component, _inletFlow);
	   MechanicalCompressor_getOutletFlowRates(_component, _outletFlow);

	   *pressureRatio = MechanicalCompressor_getPressureRatio(_component);
	   *torque = MechanicalCompressor_getTorque(_component);
	   *etaVolumetric = MechanicalCompressor_getVolumetricEfficiency(_component);
	   *etaIsentropic = MechanicalCompressor_getIsentropicEfficiency(_component);
	   *etaMechanical = MechanicalCompressor_getMechanicalEfficiency(_component);
	   *massFlowRate = FluidFlow_getMassFlowRate(_outletFlow);
	   *compressorWork = MechanicalCompressor_getCompressorWork(_component);
   } else {
	   FluidFlow_setMassFlowRate(_inletFlow, 0.0);
	   FluidFlow_setEnthalpyFlowRate(_inletFlow, 0.0);

	   FluidFlow_setMassFlowRate(_outletFlow, 0.0);
	   FluidFlow_setEnthalpyFlowRate(_outletFlow, 0.0);

	   *pressureRatio = 0.0;
	   *torque = 0.0;
	   *etaVolumetric = 0.0;
	   *etaIsentropic = 0.0;
	   *etaMechanical = 0.0;
	   *massFlowRate = FluidFlow_getMassFlowRate(_outletFlow);
	   *compressorWork = 0.0;
   }

   *inletFlowIndex = _inletFlowIndex;
   *outletFlowIndex = _outletFlowIndex;

/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *inletFlowIndex /= ??; CONVERSION UNKNOWN */
/*   *inletStateIndex /= ??; CONVERSION UNKNOWN */
/*   *outletFlowIndex /= ??; CONVERSION UNKNOWN */
/*   *outletStateIndex /= ??; CONVERSION UNKNOWN */
   *rotarySpeed /= 1.04719755119660e-001;
}

