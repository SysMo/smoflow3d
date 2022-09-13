/* Submodel SMO_CRYOPUMP_HEAT_EXCHANGER skeleton created by AME Submodel editing utility
   ?? ??? 13 14:50:33 2022 */



#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
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
#include "flow/CryopumpHeatExch.h"
#include "math/Functors.h"

#define _component ps[0]

#define _inletFluidFlow ps[1]
#define _inletFluidFlowIndex ic[1]

#define _outletFluidFlow ps[2]
#define _outletFluidFlowIndex ic[2]

#define _heatFlowIndex ic[3]
#define _heatFlow ps[3]
/* <<<<<<<<<<<<End of Private Code. */


/* There are 3 real parameters:

   displacementVolume             displacement volume                          [cm**3 -> m**3]
   heatFlowRateToPumpReservoirPrm heat flow rate to pump reservoir (parameter) [W]
   fractionOfExtraHeatToFluid     fraction of extra heat going to fluid        [null]
*/


/* There are 2 integer parameters:

   computationMethod            computation method of outlet conditions
   useFluidFlowActivationSignal use fluid flow activation signal       
*/


/* There are 4 text parameters:

   etaVolumetricExpression     expression for volumetric efficiency [-] = f(N[rev/min], pOut[barA]) 
   etaIsentropicExpression     expression for isentropic efficiency [-] = f(N[rev/min],  pOut[barA])
   etaMechanicalExpression     expression for mechanical efficiency [-] = f(N[rev/min],  pOut[barA])
   outletTemperatureExpression expression for outlet temperature [K] = f(N[rev/min],  pOut[barA])   
*/

void smo_cryopump_heat_exchangerin_(int *n, double rp[3], int ip[2]
      , char *tp[4], int ic[4], void *ps[4])

{
   int loop, error;
/* >>>>>>>>>>>>Extra Initialization Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Initialization declarations. */
   int computationMethod, useFluidFlowActivationSignal;
   double displacementVolume, heatFlowRateToPumpReservoirPrm, 
      fractionOfExtraHeatToFluid;
   char *etaVolumetricExpression, *etaIsentropicExpression, 
      *etaMechanicalExpression, *outletTemperatureExpression;

   computationMethod = ip[0];
   useFluidFlowActivationSignal = ip[1];

   displacementVolume = rp[0];
   heatFlowRateToPumpReservoirPrm = rp[1];
   fractionOfExtraHeatToFluid = rp[2];

   etaVolumetricExpression = tp[0];
   etaIsentropicExpression = tp[1];
   etaMechanicalExpression = tp[2];
   outletTemperatureExpression = tp[3];
   loop = 0;
   error = 0;

/*
   If necessary, check values of the following:

   rp[0..2]
*/


/* >>>>>>>>>>>>Initialization Function Check Statements. */
/* <<<<<<<<<<<<End of Initialization Check Statements. */

/*   Integer parameter checking:   */

   if (computationMethod < 1 || computationMethod > 2)
   {
      amefprintf(stderr, "\ncomputation method of outlet conditions must be in range [1..2].\n");
      error = 2;
   }
   if (useFluidFlowActivationSignal < 1 || useFluidFlowActivationSignal > 2)
   {
      amefprintf(stderr, "\nuse fluid flow activation signal must be in range [1..2].\n");
      error = 2;
   }

   if (ameHandleSubmodelError(_SUBMODELNAME_, *n, error))
   {
      return;
   }

/* Common -> SI units conversions. */

   rp[0]    *= 1.00000000000000e-06;
   displacementVolume = rp[0];


/* >>>>>>>>>>>>Initialization Function Executable Statements. */
   _component = CryopumpHeatExch_new();
   SMOCOMPONENT_SET_PROPS(_component)

   CryopumpHeatExch_setDisplacementVolume(_component, displacementVolume);
   CryopumpHeatExch_setVolumetricEfficiencyFunction(_component, FunctorTwoVariables_Expression_new(etaVolumetricExpression, "N", "pOut"));
   CryopumpHeatExch_setMechanicalEfficiencyFunction(_component, FunctorTwoVariables_Expression_new(etaMechanicalExpression, "N", "pOut"));

   CryopumpHeatExch_setComputationMethod(_component, computationMethod);
   if (computationMethod == 1) { //using outlet temperature
	   CryopumpHeatExch_setOutletTemperatureFunction(_component, FunctorTwoVariables_Expression_new(outletTemperatureExpression, "N", "pOut"));
	   CryopumpHeatExch_setHeatFlowRateToPumpReservoir(_component, heatFlowRateToPumpReservoirPrm);
   } else { //using isentropic efficiency
	   CryopumpHeatExch_setIsentropicEfficiencyFunction(_component, FunctorTwoVariables_Expression_new(etaIsentropicExpression, "N", "pOut"));
	   CryopumpHeatExch_setFractionOfExtraHeatToFluid(_component, fractionOfExtraHeatToFluid);
   }

   _inletFluidFlow = FluidFlow_new();
   _inletFluidFlowIndex = FluidFlow_register(_inletFluidFlow);

   _outletFluidFlow = FluidFlow_new();
   _outletFluidFlowIndex = FluidFlow_register(_outletFluidFlow);

   _heatFlow = HeatFlow_new();
   _heatFlowIndex = HeatFlow_register(_heatFlow);
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

/*  There are 8 internal variables.

      1 pressureRatio                   pressure ratio                       [null] basic variable
      2 etaVolumetric                   volumetric efficiency                [null] basic variable
      3 etaIsentropic                   isentropic efficiency                [null] basic variable
      4 etaMechanical                   mechanical efficiency                [null] basic variable
      5 massFlowRate                    mass flow rate                       [kg/s] basic variable
      6 compressorWork                  compressor work                      [W]    basic variable
      7 outletTemperature               outlet temperature                   [K]    basic variable
      8 heatFlowRateToPumpReservoir     heat flow rate to the pump reservoir [W]    basic variable
*/

void smo_cryopump_heat_exchanger_(int *n, double *inletFluidFlowIndex
      , double *inletFluidStateIndex, double *outletFluidFlowIndex
      , double *fluidFlowActivationSignal
      , double *outletFluidStateIndex, double *torque
      , double *rotarySpeed, double *heatFlowIndex
      , double *thermalNodeIndex, double *pressureRatio
      , double *etaVolumetric, double *etaIsentropic
      , double *etaMechanical, double *massFlowRate
      , double *compressorWork, double *outletTemperature
      , double *heatFlowRateToPumpReservoir, double rp[3], int ip[2]
      , char *tp[4], int ic[4], void *ps[4])

{
   int loop;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   int computationMethod, useFluidFlowActivationSignal;
   double displacementVolume, heatFlowRateToPumpReservoirPrm, 
      fractionOfExtraHeatToFluid;
   char *etaVolumetricExpression, *etaIsentropicExpression, 
      *etaMechanicalExpression, *outletTemperatureExpression;

   computationMethod = ip[0];
   useFluidFlowActivationSignal = ip[1];

   displacementVolume = rp[0];
   heatFlowRateToPumpReservoirPrm = rp[1];
   fractionOfExtraHeatToFluid = rp[2];

   etaVolumetricExpression = tp[0];
   etaIsentropicExpression = tp[1];
   etaMechanicalExpression = tp[2];
   outletTemperatureExpression = tp[3];
   loop = 0;

/* Common -> SI units conversions. */

/*   *inletFluidStateIndex *= ??; CONVERSION UNKNOWN [smoTDS] */
/*   *outletFluidStateIndex *= ??; CONVERSION UNKNOWN [smoTDS] */
   *rotarySpeed *= 1.04719755119660e-01;
/*   *thermalNodeIndex *= ??; CONVERSION UNKNOWN [smoTHN] */

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
   *outletTemperature = ??;
   *heatFlowRateToPumpReservoir = ??;
*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
   SMOCOMPONENT_PRINT_MAIN_CALC
   if (firstc_()) {
	   MediumState* inletState = MediumState_get(*inletFluidStateIndex);
	   MediumState* outletState = MediumState_get(*outletFluidStateIndex);
	   CryopumpHeatExch_init(_component, inletState, outletState);
   }

   if (*rotarySpeed > 1e-12) {
	   CryopumpHeatExch_setRotationalSpeed(_component, *rotarySpeed);
	   CryopumpHeatExch_compute(_component);
	   CryopumpHeatExch_updateFluidFlows(_component, _inletFluidFlow, _outletFluidFlow);

	   *pressureRatio = CryopumpHeatExch_getPressureRatio(_component);
	   *torque = CryopumpHeatExch_getTorque(_component);
	   *etaVolumetric = CryopumpHeatExch_getVolumetricEfficiency(_component);
	   *etaIsentropic = CryopumpHeatExch_getIsentropicEfficiency(_component);
	   *etaMechanical = CryopumpHeatExch_getMechanicalEfficiency(_component);
	   *massFlowRate = FluidFlow_getMassFlowRate(_outletFluidFlow);
	   *compressorWork = CryopumpHeatExch_getPumpWork(_component);
	   *outletTemperature = CryopumpHeatExch_getOutletTemperature(_component);
	   *heatFlowRateToPumpReservoir = CryopumpHeatExch_getHeatFlowRateToPumpReservoir(_component);
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
	   *outletTemperature = 0.0;
	   *heatFlowRateToPumpReservoir = 0.0;
   }
   HeatFlow_setEnthalpyFlowRate(_heatFlow, *heatFlowRateToPumpReservoir);

   *inletFluidFlowIndex = _inletFluidFlowIndex;
   *outletFluidFlowIndex = _outletFluidFlowIndex;
   *heatFlowIndex = _heatFlowIndex;


   if (useFluidFlowActivationSignal == 1) { //no
	   *fluidFlowActivationSignal = -1; //not used
   } else { // yes
	   if (*rotarySpeed <= 1e-12) {
		   *fluidFlowActivationSignal = 0; //deactivate flow
	   } else {
		   *fluidFlowActivationSignal = 1; //activate flow
	   }
   }
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *inletFluidFlowIndex /= ??; CONVERSION UNKNOWN [smoFFL] */
/*   *inletFluidStateIndex /= ??; CONVERSION UNKNOWN [smoTDS] */
/*   *outletFluidFlowIndex /= ??; CONVERSION UNKNOWN [smoFFL] */
/*   *fluidFlowActivationSignal /= ??; CONVERSION UNKNOWN [smoFFAS] */
/*   *outletFluidStateIndex /= ??; CONVERSION UNKNOWN [smoTDS] */
   *rotarySpeed /= 1.04719755119660e-01;
/*   *heatFlowIndex /= ??; CONVERSION UNKNOWN [smoHFL] */
/*   *thermalNodeIndex /= ??; CONVERSION UNKNOWN [smoTHN] */
}

