/* Submodel SMO_CRYOPUMP_HEAT_EXCHANGER skeleton created by AME Submodel editing utility
   Thu Feb 27 11:55:18 2014 */



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

#define _SUBMODELNAME_ "SMO_CRYOPUMP_HEAT_EXCHANGER"

/* >>>>>>>>>>>>Insert Private Code Here. */
#include "SmoFlowAme.h"
#include "flow/MechanicalCompressor.h"
#include "math/Functors.h"

#define _component ps[0]

#define _inletFluidFlow ps[1]
#define _inletFluidFlowIndex ic[1]

#define _outletFluidFlow ps[2]
#define _outletFluidFlowIndex ic[2]

#define _heatFlowIndex ic[3]
#define _heatFlow ps[3]
/* <<<<<<<<<<<<End of Private Code. */


/* There is 1 real parameter:

   displacementVolume displacement volume [cm**3 -> m**3]
*/


/* There are 2 integer parameters:

   flowRateCalculationMethod    flow rate calculation method    
   useFluidFlowActivationSignal use fluid flow activation signal
*/


/* There are 4 text parameters:

   etaVolumetricExpression      expression for volumetric efficiency [-] = f(N[rev/min], tau[-l])  
   volumetricFlowRateExpression expression for volumetric flow rate [m^3/s] = f(N[rev/min], tau[-])
   etaIsentropicExpression      expression for isentropic efficiency [-] = f(N[rev/min], tau[-])   
   etaMechanicalExpression      expression for mechanical efficiency [-] = f(N[rev/min], tau[-])   
*/

void smo_cryopump_heat_exchangerin_(int *n, double rp[1], int ip[2]
      , char *tp[4], int ic[4], void *ps[4])

{
   int loop, error;
/* >>>>>>>>>>>>Extra Initialization Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Initialization declarations. */
   int flowRateCalculationMethod, useFluidFlowActivationSignal;
   double displacementVolume;
   char *etaVolumetricExpression, *volumetricFlowRateExpression, 
      *etaIsentropicExpression, *etaMechanicalExpression;

   flowRateCalculationMethod = ip[0];
   useFluidFlowActivationSignal = ip[1];

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
   if (useFluidFlowActivationSignal < 1 || useFluidFlowActivationSignal > 2)
   {
      amefprintf(stderr, "\nuse fluid flow activation signal must be in range [1..2].\n");
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
   SMOCOMPONENT_SET_PROPS(_component)

   _inletFluidFlow = FluidFlow_new();
   _inletFluidFlowIndex = FluidFlow_register(_inletFluidFlow);
   _outletFluidFlow = FluidFlow_new();
   _outletFluidFlowIndex = FluidFlow_register(_outletFluidFlow);

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


   _heatFlow = HeatFlow_new();
   _heatFlowIndex = HeatFlow_register(_heatFlow);

   HeatFlow_setEnthalpyFlowRate(_heatFlow, 10.0); //:SMO_WORK: (Milen) cryopump heat flow
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

/*  There are 4 ports.

   Port 1 has 3 variables:

      1 inletFluidFlowIndex              inlet fluid flow index                                                 [smoFFL] basic variable output  UNPLOTTABLE
      2 fluidFlowActivationSignalDup     duplicate of fluidFlowActivationSignal                                
      3 inletFluidStateIndex             inlet fluid state index                                                [smoTDS] basic variable input  UNPLOTTABLE

   Port 2 has 3 variables:

      1 outletFluidFlowIndex          outlet fluid flow index                                                [smoFFL]  basic variable output  UNPLOTTABLE
      2 fluidFlowActivationSignal     flow activation signal = {-1 - not used; 0 - deactivate; 1 - activate} [smoFFAS] basic variable output
      3 outletFluidStateIndex         outlet fluid state index                                               [smoTDS]  basic variable input  UNPLOTTABLE

   Port 3 has 2 variables:

      1 torque          mechanical torque [Nm]               basic variable output
      2 rotarySpeed     rotary speed      [rev/min -> rad/s] basic variable input

   Port 4 has 2 variables:

      1 heatFlowIndex        heat flow index    [smoHFL] basic variable output  UNPLOTTABLE
      2 thermalNodeIndex     thermal node index [smoTHN] basic variable input  UNPLOTTABLE
*/

/*  There are 7 internal variables.

      1 pressureRatio      pressure ratio         [null] basic variable
      2 etaVolumetric      volumetric efficiency  [null] basic variable
      3 etaIsentropic      isentropic efficiency  [null] basic variable
      4 etaMechanical      mechanical efficiency  [null] basic variable
      5 massFlowRate       mass flow rate         [kg/s] basic variable
      6 compressorWork     compressor work        [W]    basic variable
      7 heatFlow           heat flow rate (port4) [W]    basic variable
*/

void smo_cryopump_heat_exchanger_(int *n, double *inletFluidFlowIndex
      , double *inletFluidStateIndex, double *outletFluidFlowIndex
      , double *fluidFlowActivationSignal
      , double *outletFluidStateIndex, double *torque
      , double *rotarySpeed, double *heatFlowIndex
      , double *thermalNodeIndex, double *pressureRatio
      , double *etaVolumetric, double *etaIsentropic
      , double *etaMechanical, double *massFlowRate
      , double *compressorWork, double *heatFlow, double rp[1]
      , int ip[2], char *tp[4], int ic[4], void *ps[4])

{
   int loop;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   int flowRateCalculationMethod, useFluidFlowActivationSignal;
   double displacementVolume;
   char *etaVolumetricExpression, *volumetricFlowRateExpression, 
      *etaIsentropicExpression, *etaMechanicalExpression;

   flowRateCalculationMethod = ip[0];
   useFluidFlowActivationSignal = ip[1];

   displacementVolume = rp[0];

   etaVolumetricExpression = tp[0];
   volumetricFlowRateExpression = tp[1];
   etaIsentropicExpression = tp[2];
   etaMechanicalExpression = tp[3];
   loop = 0;

/* Common -> SI units conversions. */

/*   *inletFluidStateIndex *= ??; CONVERSION UNKNOWN */
/*   *outletFluidStateIndex *= ??; CONVERSION UNKNOWN */
   *rotarySpeed *= 1.04719755119660e-001;
/*   *thermalNodeIndex *= ??; CONVERSION UNKNOWN */

/*
   Set all submodel outputs below:

   *inletFluidFlowIndex = ??;
   *outletFluidFlowIndex = ??;
   *fluidFlowActivationSignal = ??;
   *torque     = ??;
   *heatFlowIndex = ??;
   *pressureRatio = ??;
   *etaVolumetric = ??;
   *etaIsentropic = ??;
   *etaMechanical = ??;
   *massFlowRate = ??;
   *compressorWork = ??;
   *heatFlow   = ??;
*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
   SMOCOMPONENT_PRINT_MAIN_CALC
   if (firstc_()) {
	   MediumState* inletState = MediumState_get(*inletFluidStateIndex);
	   MediumState* outletState = MediumState_get(*outletFluidStateIndex);
	   MechanicalCompressor_init(_component, inletState, outletState);
   }

   if (*rotarySpeed > 1e-12) {
	   MechanicalCompressor_setRotationalSpeed(_component, *rotarySpeed);
	   MechanicalCompressor_compute(_component);
	   MechanicalCompressor_updateFluidFlows(_component, _inletFluidFlow, _outletFluidFlow);

	   *pressureRatio = MechanicalCompressor_getPressureRatio(_component);
	   *torque = MechanicalCompressor_getTorque(_component);
	   *etaVolumetric = MechanicalCompressor_getVolumetricEfficiency(_component);
	   *etaIsentropic = MechanicalCompressor_getIsentropicEfficiency(_component);
	   *etaMechanical = MechanicalCompressor_getMechanicalEfficiency(_component);
	   *massFlowRate = FluidFlow_getMassFlowRate(_outletFluidFlow);
	   *compressorWork = MechanicalCompressor_getCompressorWork(_component);
   } else {
	   FluidFlow_setMassFlowRate(_inletFluidFlow, 0.0);
	   FluidFlow_setEnthalpyFlowRate(_inletFluidFlow, 0.0);

	   FluidFlow_setMassFlowRate(_outletFluidFlow, 0.0);
	   FluidFlow_setEnthalpyFlowRate(_outletFluidFlow, 0.0);

	   *pressureRatio = 0.0;
	   *torque = 0.0;
	   *etaVolumetric = 0.0;
	   *etaIsentropic = 0.0;
	   *etaMechanical = 0.0;
	   *massFlowRate = FluidFlow_getMassFlowRate(_outletFluidFlow);
	   *compressorWork = 0.0;
   }

   *inletFluidFlowIndex = _inletFluidFlowIndex;
   *outletFluidFlowIndex = _outletFluidFlowIndex;

   if (useFluidFlowActivationSignal == 1) { //no
	   *fluidFlowActivationSignal = -1; //not used
   } else { // yes
	   if (*rotarySpeed <= 1e-12) {
		   *fluidFlowActivationSignal = 0; //deactivate flow
	   } else {
		   *fluidFlowActivationSignal = 1; //activate flow
	   }
   }


   *heatFlow = HeatFlow_getEnthalpyFlowRate(_heatFlow);
   *heatFlowIndex = _heatFlowIndex;
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *inletFluidFlowIndex /= ??; CONVERSION UNKNOWN */
/*   *inletFluidStateIndex /= ??; CONVERSION UNKNOWN */
/*   *outletFluidFlowIndex /= ??; CONVERSION UNKNOWN */
/*   *fluidFlowActivationSignal /= ??; CONVERSION UNKNOWN */
/*   *outletFluidStateIndex /= ??; CONVERSION UNKNOWN */
   *rotarySpeed /= 1.04719755119660e-001;
/*   *heatFlowIndex /= ??; CONVERSION UNKNOWN */
/*   *thermalNodeIndex /= ??; CONVERSION UNKNOWN */
}

