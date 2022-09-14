/* Submodel SMO_TPIPE_JUNCTION_HEAT_EXCHANGER skeleton created by AME Submodel editing utility
   ?? ??? 14 10:05:58 2022 */



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

#define _SUBMODELNAME_ "SMO_TPIPE_JUNCTION_HEAT_EXCHANGER"

/* >>>>>>>>>>>>Insert Private Code Here. */
#include "SmoFlowAme.h"
#include "volumes/TPipeJunction.h"
#include "flow/FlowBase.h"

#define _component ps[0]

#define _fluidStateIndex1 ic[0]
#define _fluidState1 ps[1]

#define _fluidStateIndex2 ic[1]
#define _fluidState2 ps[2]

#define _fluidStateIndex3 ic[2]
#define _fluidState3 ps[3]

#define _fluidFlow1 ps[4]
#define _fluidFlow2 ps[5]
#define _fluidFlow3 ps[6]

#define _wallHeatFlowIndex ic[4]
#define _wallHeatFlow ps[7]

#define _convection ps[8]

/* <<<<<<<<<<<<End of Private Code. */


/* There are 14 real parameters:

   initialPressure        initial pressure                                        [barA -> PaA]
   initialTemperature     initial temperature                                     [K]
   initialTemperatureC    initial temperature (°C)                               [degC]
   initialGasMassFraction initial gas mass fraction                               [null]
   initialSuperheat       initial superheat                                       [K]
   volume                 volume                                                  [L -> m**3]
   dragCoeff2             drag coefficient (port2)                                [null]
   dragCoeff3             drag coefficient (port3)                                [null]
   hydraulicDiameter      hydraulic diameter                                      [mm -> m]
   pipeLength             pipe length (only for heat exchange)                    [m]
   flowArea               flow (cross sectional) area                             [mm**2 -> m**2]
   heatExchangeGain       heat exchange gain                                      [null]
   ReL                    laminar to turbulent transition:  lower Reynolds number [null]
   ReH                    laminar to turbulent transition:  upper Reynolds number [null]
*/


/* There are 6 integer parameters:

   fluidIndex                   fluid index                       
   convCalcMethod               convection calculation method     
   geometryType                 geometry type                     
   forcedConvectionUseFilmState use film state (forced convection)
   initConditionsChoice         type of initialization            
   stateVariableSelection       states variables                  
*/


/* There are 2 text parameters:

   nusseltExpressionLaminarFlow   nusselt correlation expression Nu=f(Re, Pr) in laminar flow  
   nusseltExpressionTurbulentFlow nusselt correlation expression Nu=f(Re, Pr) in turbulent flow
*/

void smo_tpipe_junction_heat_exchangerin_(int *n, double rp[14]
      , int ip[6], char *tp[2], int ic[5], void *ps[9], double *state1
      , double *state2)

{
   int loop, error;
/* >>>>>>>>>>>>Extra Initialization Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Initialization declarations. */
   int fluidIndex, convCalcMethod, geometryType, 
      forcedConvectionUseFilmState, initConditionsChoice, 
      stateVariableSelection;
   double initialPressure, initialTemperature, initialTemperatureC, 
      initialGasMassFraction, initialSuperheat, volume, dragCoeff2, 
      dragCoeff3, hydraulicDiameter, pipeLength, flowArea, 
      heatExchangeGain, ReL, ReH;
   char *nusseltExpressionLaminarFlow, *nusseltExpressionTurbulentFlow;

   fluidIndex = ip[0];
   convCalcMethod = ip[1];
   geometryType = ip[2];
   forcedConvectionUseFilmState = ip[3];
   initConditionsChoice = ip[4];
   stateVariableSelection = ip[5];

   initialPressure = rp[0];
   initialTemperature = rp[1];
   initialTemperatureC = rp[2];
   initialGasMassFraction = rp[3];
   initialSuperheat = rp[4];
   volume     = rp[5];
   dragCoeff2 = rp[6];
   dragCoeff3 = rp[7];
   hydraulicDiameter = rp[8];
   pipeLength = rp[9];
   flowArea   = rp[10];
   heatExchangeGain = rp[11];
   ReL        = rp[12];
   ReH        = rp[13];

   nusseltExpressionLaminarFlow = tp[0];
   nusseltExpressionTurbulentFlow = tp[1];
   loop = 0;
   error = 0;

/*
   If necessary, check values of the following:

   rp[0..13]
   *state1
   *state2
*/


/* >>>>>>>>>>>>Initialization Function Check Statements. */
/* <<<<<<<<<<<<End of Initialization Check Statements. */

/*   Integer parameter checking:   */

   if (fluidIndex < 1 || fluidIndex > 99)
   {
      amefprintf(stderr, "\nfluid index must be in range [1..99].\n");
      error = 2;
   }
   if (convCalcMethod < 1 || convCalcMethod > 2)
   {
      amefprintf(stderr, "\nconvection calculation method must be in range [1..2].\n");
      error = 2;
   }
   if (geometryType < 1 || geometryType > 2)
   {
      amefprintf(stderr, "\ngeometry type must be in range [1..2].\n");
      error = 2;
   }
   if (forcedConvectionUseFilmState < 1 || forcedConvectionUseFilmState > 2)
   {
      amefprintf(stderr, "\nuse film state (forced convection) must be in range [1..2].\n");
      error = 2;
   }
   if (initConditionsChoice < 1 || initConditionsChoice > 4)
   {
      amefprintf(stderr, "\ntype of initialization must be in range [1..4].\n");
      error = 2;
   }
   if (stateVariableSelection < 1 || stateVariableSelection > 4)
   {
      amefprintf(stderr, "\nstates variables must be in range [1..4].\n");
      error = 2;
   }

   if (ameHandleSubmodelError(_SUBMODELNAME_, *n, error))
   {
      return;
   }

/* Common -> SI units conversions. */

   rp[0]    *= 1.00000000000000e+05;
   initialPressure = rp[0];
   rp[5]    *= 1.00000000000000e-03;
   volume     = rp[5];
   rp[8]    *= 1.00000000000000e-03;
   hydraulicDiameter = rp[8];
   rp[10]   *= 1.00000000000000e-06;
   flowArea   = rp[10];


/* >>>>>>>>>>>>Initialization Function Executable Statements. */
	double flowAreaValue;
	if (geometryType == 1) { //cylindrical pipe
		flowAreaValue = M_PI * hydraulicDiameter * hydraulicDiameter / 4.;
	} else { //non-cylindrical pipe
		flowAreaValue = flowArea;
	}

	if (convCalcMethod == 1) { //default expression for Nuselt number
		_convection = ForcedConvection_StraightPipe_new(
				pipeLength, hydraulicDiameter, flowAreaValue);
	} else { //user expression for Nuselt number
		_convection = ForcedConvection_StraightPipe_NusseltExpression_new(
				pipeLength, hydraulicDiameter, flowAreaValue,
				nusseltExpressionLaminarFlow, nusseltExpressionTurbulentFlow, ReL, ReH);
	}
	Convection_setHeatExchangeGain(_convection, heatExchangeGain);
	Convection_setUseFilmState(_convection, forcedConvectionUseFilmState - 1); //:TRICKY: (0-no, 1-yes)
	ForcedConvection_setLimitOutput(_convection, 1); //:TRICKY: (0-no, 1-yes)

	Medium* fluid = Medium_get(fluidIndex);
	_component = TPipeJunction_ConstantDragCoefficients_HeatExchanger_new(
			fluid,
			volume,
			flowAreaValue,
			dragCoeff2,
			dragCoeff3,
			_convection,
			stateVariableSelection);
	SMOCOMPONENT_SET_PROPS(_component)

	TPipeJunction_initFluidStates(_component,
			initConditionsChoice, initialPressure, initialTemperature,
			initialTemperatureC, initialGasMassFraction);

	_fluidState1 = TPipeJunction_getFluidState1(_component);
	_fluidStateIndex1 = MediumState_index(_fluidState1);

	_fluidState2 = TPipeJunction_getFluidState2(_component);
	_fluidStateIndex2 = MediumState_index(_fluidState2);

	_fluidState3 = TPipeJunction_getFluidState3(_component);
	_fluidStateIndex3 = MediumState_index(_fluidState3);

	TPipeJunction_getStateValues(_component, state1, state2);
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

/*  There are 4 ports.

   Port 1 has 3 variables:

      1 fluidStateIndex1               fluid state index (port1)            [smoTDS]  multi line macro 'smo_tpipe_junction_heat_exchanger_macro0_'  UNPLOTTABLE
      2 fluidFlowIndex1                fluid flow index (port1)             [smoFFL]  basic variable input  UNPLOTTABLE
      3 fluidFlowActivationSignal1     fluid flow activation signal (port1) [smoFFAS] basic variable input  UNPLOTTABLE

   Port 2 has 3 variables:

      1 fluidStateIndex2               fluid state index (port2)            [smoTDS]  multi line macro 'smo_tpipe_junction_heat_exchanger_macro1_'  UNPLOTTABLE
      2 fluidFlowIndex2                fluid flow index (port2)             [smoFFL]  basic variable input  UNPLOTTABLE
      3 fluidFlowActivationSignal2     fluid flow activation signal (port2) [smoFFAS] basic variable input  UNPLOTTABLE

   Port 3 has 3 variables:

      1 fluidStateIndex3               fluid state index (port3)            [smoTDS]  multi line macro shared with 'fluidStateIndex2'  UNPLOTTABLE
      2 fluidFlowIndex3                fluid flow index (port3)             [smoFFL]  basic variable input  UNPLOTTABLE
      3 fluidFlowActivationSignal3     fluid flow activation signal (port3) [smoFFAS] basic variable input  UNPLOTTABLE

   Port 4 has 2 variables:

      1 heatFlowIndex        heat flow index    [smoHFL] basic variable output  UNPLOTTABLE
      2 thermalNodeIndex     thermal node index [smoTHN] basic variable input  UNPLOTTABLE
*/

/*  There are 21 internal variables.

      1 pressure                  pressure (port1)                [barA -> PaA]   basic variable
      2 temperature               temperature (port1)             [K]             basic variable
      3 density                   density (port1)                 [kg/m**3]       basic variable
      4 specificEnthalpy          specific enthalpy (port1)       [kJ/kg -> J/kg] basic variable
      5 gasMassFraction           gas mass fraction (port1)       [null]          basic variable
      6 superHeat                 subcooling / superheat (port1)  [degC]          basic variable
      7 massFlowRate1             mass flow rate (port1)          [kg/s]          basic variable
      8 mass                      fluid mass in pipe              [kg]            basic variable
      9 state1                    state variable 1                [null]          explicit state (derivative `state1Dot')
     10 state2                    state variable 2                [null]          explicit state (derivative `state2Dot')
     11 pressureLoss2             pressure loss (port1 - prort2)  [bar -> Pa]     basic variable
     12 pressure2                 pressure (port2)                [barA -> PaA]   basic variable
     13 temperature2              temperature (port2)             [K]             basic variable
     14 massFlowRate2             mass flow rate (port1 -> port2) [kg/s]          basic variable
     15 pressureLoss3             pressure loss (port1 - port3)   [bar -> Pa]     basic variable
     16 pressure3                 pressure (port3)                [barA -> PaA]   basic variable
     17 temperature3              temperature (port3)             [K]             basic variable
     18 massFlowRate3             mass flow rate (port1 -> port3) [kg/s]          basic variable
     19 reynoldsNumber            Reynolds number                 [null]          basic variable
     20 convectionCoefficient     convection coefficient          [W/m**2/K]      basic variable
     21 heatFlowRateFromWall      heat flow rate                  [W]             basic variable
*/

void smo_tpipe_junction_heat_exchanger_(int *n
      , double *fluidStateIndex1, double *fluidFlowIndex1
      , double *fluidFlowActivationSignal1, double *fluidStateIndex2
      , double *fluidFlowIndex2, double *fluidFlowActivationSignal2
      , double *fluidStateIndex3, double *fluidFlowIndex3
      , double *fluidFlowActivationSignal3, double *heatFlowIndex
      , double *thermalNodeIndex, double *pressure
      , double *temperature, double *density, double *specificEnthalpy
      , double *gasMassFraction, double *superHeat
      , double *massFlowRate1, double *mass, double *state1
      , double *state1Dot, double *state2, double *state2Dot
      , double *pressureLoss2, double *pressure2, double *temperature2
      , double *massFlowRate2, double *pressureLoss3
      , double *pressure3, double *temperature3, double *massFlowRate3
      , double *reynoldsNumber, double *convectionCoefficient
      , double *heatFlowRateFromWall, double rp[14], int ip[6]
      , char *tp[2], int ic[5], void *ps[9])

{
   int loop;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   int fluidIndex, convCalcMethod, geometryType, 
      forcedConvectionUseFilmState, initConditionsChoice, 
      stateVariableSelection;
   double initialPressure, initialTemperature, initialTemperatureC, 
      initialGasMassFraction, initialSuperheat, volume, dragCoeff2, 
      dragCoeff3, hydraulicDiameter, pipeLength, flowArea, 
      heatExchangeGain, ReL, ReH;
   char *nusseltExpressionLaminarFlow, *nusseltExpressionTurbulentFlow;

   fluidIndex = ip[0];
   convCalcMethod = ip[1];
   geometryType = ip[2];
   forcedConvectionUseFilmState = ip[3];
   initConditionsChoice = ip[4];
   stateVariableSelection = ip[5];

   initialPressure = rp[0];
   initialTemperature = rp[1];
   initialTemperatureC = rp[2];
   initialGasMassFraction = rp[3];
   initialSuperheat = rp[4];
   volume     = rp[5];
   dragCoeff2 = rp[6];
   dragCoeff3 = rp[7];
   hydraulicDiameter = rp[8];
   pipeLength = rp[9];
   flowArea   = rp[10];
   heatExchangeGain = rp[11];
   ReL        = rp[12];
   ReH        = rp[13];

   nusseltExpressionLaminarFlow = tp[0];
   nusseltExpressionTurbulentFlow = tp[1];
   loop = 0;

/* Common -> SI units conversions. */

/*   *fluidStateIndex1 *= ??; CONVERSION UNKNOWN [smoTDS] */
/*   *fluidFlowIndex1 *= ??; CONVERSION UNKNOWN [smoFFL] */
/*   *fluidFlowActivationSignal1 *= ??; CONVERSION UNKNOWN [smoFFAS] */
/*   *fluidStateIndex2 *= ??; CONVERSION UNKNOWN [smoTDS] */
/*   *fluidFlowIndex2 *= ??; CONVERSION UNKNOWN [smoFFL] */
/*   *fluidFlowActivationSignal2 *= ??; CONVERSION UNKNOWN [smoFFAS] */
/*   *fluidStateIndex3 *= ??; CONVERSION UNKNOWN [smoTDS] */
/*   *fluidFlowIndex3 *= ??; CONVERSION UNKNOWN [smoFFL] */
/*   *fluidFlowActivationSignal3 *= ??; CONVERSION UNKNOWN [smoFFAS] */
/*   *thermalNodeIndex *= ??; CONVERSION UNKNOWN [smoTHN] */

/*
   Set all submodel outputs below:

   *heatFlowIndex = ??;
   *pressure   = ??;
   *temperature = ??;
   *density    = ??;
   *specificEnthalpy = ??;
   *gasMassFraction = ??;
   *superHeat  = ??;
   *massFlowRate1 = ??;
   *mass       = ??;
   *state1Dot  = ??;
   *state2Dot  = ??;
   *pressureLoss2 = ??;
   *pressure2  = ??;
   *temperature2 = ??;
   *massFlowRate2 = ??;
   *pressureLoss3 = ??;
   *pressure3  = ??;
   *temperature3 = ??;
   *massFlowRate3 = ??;
   *reynoldsNumber = ??;
   *convectionCoefficient = ??;
   *heatFlowRateFromWall = ??;
*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
	SMOCOMPONENT_PRINT_MAIN_CALC
	if (firstc_()) {
		_fluidFlow2 = FluidFlow_get(*fluidFlowIndex2);
		_fluidFlow3 = FluidFlow_get(*fluidFlowIndex3);

		TPipeJunction_setFluidFlow2(_component, _fluidFlow2);
		TPipeJunction_setFluidFlow3(_component, _fluidFlow3);

		TPipeJunction_HeatExchanger_initWallHeatFlow(_component);

		_wallHeatFlow = TPipeJunction_HeatExchanger_getWallHeatFlow(_component);
		_wallHeatFlowIndex = SmoObject_getInstanceIndex(_wallHeatFlow);
	}

	TPipeJunction_compute(_component);
	TPipeJunction_getStateDerivatives(_component, state1Dot, state2Dot);

	*heatFlowIndex = _wallHeatFlowIndex;
	*reynoldsNumber = ForcedConvection_getReynoldsNumber(_convection);
	*convectionCoefficient = Convection_getConvectionCoefficient(_convection);
	*heatFlowRateFromWall = -HeatFlow_getEnthalpyFlowRate(_wallHeatFlow);

	*pressure = MediumState_p(_fluidState1);
	*temperature = MediumState_T(_fluidState1);
	*density = MediumState_rho(_fluidState1);
	*specificEnthalpy = MediumState_h(_fluidState1);
	*gasMassFraction = MediumState_q(_fluidState1);
	*superHeat  = MediumState_deltaTSat(_fluidState1);
	*mass  = TPipeJunction_getFluidMass(_component);
	*pressureLoss2 = TPipeJunction_getPressureLoss2(_component);
	*pressureLoss3 = TPipeJunction_getPressureLoss3(_component);
	*pressure2 = MediumState_p(_fluidState2);
	*temperature2 = MediumState_T(_fluidState2);
	*pressure3 = MediumState_p(_fluidState3);
	*temperature3 = MediumState_T(_fluidState3);
	*massFlowRate1 = FluidFlow_getMassFlowRate(_fluidFlow1);
	*massFlowRate2 = -FluidFlow_getMassFlowRate(_fluidFlow2);
	*massFlowRate3 = -FluidFlow_getMassFlowRate(_fluidFlow3);
/* <<<<<<<<<<<<End of Calculation Executable Statements. */

/* SI -> Common units conversions. */

/*   *fluidStateIndex1 /= ??; CONVERSION UNKNOWN [smoTDS] */
/*   *fluidFlowIndex1 /= ??; CONVERSION UNKNOWN [smoFFL] */
/*   *fluidFlowActivationSignal1 /= ??; CONVERSION UNKNOWN [smoFFAS] */
/*   *fluidStateIndex2 /= ??; CONVERSION UNKNOWN [smoTDS] */
/*   *fluidFlowIndex2 /= ??; CONVERSION UNKNOWN [smoFFL] */
/*   *fluidFlowActivationSignal2 /= ??; CONVERSION UNKNOWN [smoFFAS] */
/*   *fluidStateIndex3 /= ??; CONVERSION UNKNOWN [smoTDS] */
/*   *fluidFlowIndex3 /= ??; CONVERSION UNKNOWN [smoFFL] */
/*   *fluidFlowActivationSignal3 /= ??; CONVERSION UNKNOWN [smoFFAS] */
/*   *heatFlowIndex /= ??; CONVERSION UNKNOWN [smoHFL] */
/*   *thermalNodeIndex /= ??; CONVERSION UNKNOWN [smoTHN] */
   *pressure /= 1.00000000000000e+05;
   *specificEnthalpy /= 1.00000000000000e+03;
   *pressureLoss2 /= 1.00000000000000e+05;
   *pressure2 /= 1.00000000000000e+05;
   *pressureLoss3 /= 1.00000000000000e+05;
   *pressure3 /= 1.00000000000000e+05;
}

extern double smo_tpipe_junction_heat_exchanger_macro0_(int *n
      , double *thermalNodeIndex, double *state1, double *state2
      , double rp[14], int ip[6], char *tp[2], int ic[5], void *ps[9])

{
   double fluidStateIndex1;
   int loop;
/* >>>>>>>>>>>>Extra Macro Function macro0 Declarations Here. */
/* <<<<<<<<<<<<End of Extra Macro macro0 declarations. */
   int fluidIndex, convCalcMethod, geometryType, 
      forcedConvectionUseFilmState, initConditionsChoice, 
      stateVariableSelection;
   double initialPressure, initialTemperature, initialTemperatureC, 
      initialGasMassFraction, initialSuperheat, volume, dragCoeff2, 
      dragCoeff3, hydraulicDiameter, pipeLength, flowArea, 
      heatExchangeGain, ReL, ReH;
   char *nusseltExpressionLaminarFlow, *nusseltExpressionTurbulentFlow;

   fluidIndex = ip[0];
   convCalcMethod = ip[1];
   geometryType = ip[2];
   forcedConvectionUseFilmState = ip[3];
   initConditionsChoice = ip[4];
   stateVariableSelection = ip[5];

   initialPressure = rp[0];
   initialTemperature = rp[1];
   initialTemperatureC = rp[2];
   initialGasMassFraction = rp[3];
   initialSuperheat = rp[4];
   volume     = rp[5];
   dragCoeff2 = rp[6];
   dragCoeff3 = rp[7];
   hydraulicDiameter = rp[8];
   pipeLength = rp[9];
   flowArea   = rp[10];
   heatExchangeGain = rp[11];
   ReL        = rp[12];
   ReH        = rp[13];

   nusseltExpressionLaminarFlow = tp[0];
   nusseltExpressionTurbulentFlow = tp[1];
   loop = 0;

/* Common -> SI units conversions. */

/*   *thermalNodeIndex *= ??; CONVERSION UNKNOWN [smoTHN] */

/*
   Define and return the following macro variable:

   fluidStateIndex1 = ??;
*/


/* >>>>>>>>>>>>Macro Function macro0 Executable Statements. */
	SMOCOMPONENt_PRINT_MACRO
	if (firstc_()) {
		   ThermalNode* wallNode = ThermalNode_get(*thermalNodeIndex);
		   TPipeJunction_HeatExchanger_setWallNode(_component, wallNode);
	}

	TPipeJunction_setStateValues(_component, *state1, *state2);
	fluidStateIndex1 = _fluidStateIndex1;
/* <<<<<<<<<<<<End of Macro macro0 Executable Statements. */

/* SI -> Common units conversions. */

/*   *thermalNodeIndex /= ??; CONVERSION UNKNOWN [smoTHN] */

/*   *fluidStateIndex1 /= ??; CONVERSION UNKNOWN [smoTDS] */

   return fluidStateIndex1;
}

extern double smo_tpipe_junction_heat_exchanger_macro1_(int *n
      , double *fluidFlowIndex1, double *fluidStateIndex3
      , double *thermalNodeIndex, double *state1, double *state2
      , double rp[14], int ip[6], char *tp[2], int ic[5], void *ps[9])

{
   double fluidStateIndex2;
   int loop;
/* >>>>>>>>>>>>Extra Macro Function macro1 Declarations Here. */
/* <<<<<<<<<<<<End of Extra Macro macro1 declarations. */
   int fluidIndex, convCalcMethod, geometryType, 
      forcedConvectionUseFilmState, initConditionsChoice, 
      stateVariableSelection;
   double initialPressure, initialTemperature, initialTemperatureC, 
      initialGasMassFraction, initialSuperheat, volume, dragCoeff2, 
      dragCoeff3, hydraulicDiameter, pipeLength, flowArea, 
      heatExchangeGain, ReL, ReH;
   char *nusseltExpressionLaminarFlow, *nusseltExpressionTurbulentFlow;

   fluidIndex = ip[0];
   convCalcMethod = ip[1];
   geometryType = ip[2];
   forcedConvectionUseFilmState = ip[3];
   initConditionsChoice = ip[4];
   stateVariableSelection = ip[5];

   initialPressure = rp[0];
   initialTemperature = rp[1];
   initialTemperatureC = rp[2];
   initialGasMassFraction = rp[3];
   initialSuperheat = rp[4];
   volume     = rp[5];
   dragCoeff2 = rp[6];
   dragCoeff3 = rp[7];
   hydraulicDiameter = rp[8];
   pipeLength = rp[9];
   flowArea   = rp[10];
   heatExchangeGain = rp[11];
   ReL        = rp[12];
   ReH        = rp[13];

   nusseltExpressionLaminarFlow = tp[0];
   nusseltExpressionTurbulentFlow = tp[1];
   loop = 0;

/* Common -> SI units conversions. */

/*   *fluidFlowIndex1 *= ??; CONVERSION UNKNOWN [smoFFL] */
/*   *thermalNodeIndex *= ??; CONVERSION UNKNOWN [smoTHN] */

/*
   Define and return the following macro variable:

   fluidStateIndex2 = ??;

   Define the following shared macro variable(s):

   *fluidStateIndex3 = ??;
*/


/* >>>>>>>>>>>>Macro Function macro1 Executable Statements. */
	SMOCOMPONENt_PRINT_MACRO
	if (firstc_()) {
		ThermalNode* wallNode = ThermalNode_get(*thermalNodeIndex);
		TPipeJunction_HeatExchanger_setWallNode(_component, wallNode);

		_fluidFlow1 = FluidFlow_get(*fluidFlowIndex1);

		TPipeJunction_setFluidFlow1(_component, _fluidFlow1);
	}
	TPipeJunction_setStateValues(_component, *state1, *state2);
	TPipeJunction_updateFluidStates23(_component, 0); //:TRICKY: the second parameter 'mass flow ratio' is not used for calculation of the drag coefficients

	fluidStateIndex2 = _fluidStateIndex2;
	*fluidStateIndex3 = _fluidStateIndex3;
/* <<<<<<<<<<<<End of Macro macro1 Executable Statements. */

/* SI -> Common units conversions. */

/*   *fluidFlowIndex1 /= ??; CONVERSION UNKNOWN [smoFFL] */
/*   *fluidStateIndex3 /= ??; CONVERSION UNKNOWN [smoTDS] */
/*   *thermalNodeIndex /= ??; CONVERSION UNKNOWN [smoTHN] */

/*   *fluidStateIndex2 /= ??; CONVERSION UNKNOWN [smoTDS] */

   return fluidStateIndex2;
}

