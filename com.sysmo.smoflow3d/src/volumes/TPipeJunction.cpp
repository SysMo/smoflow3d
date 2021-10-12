/*
 * TPipeJunction.cpp
 *
 *  Created on: Aug 30, 2019
 *      Author: Milen Borisov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "TPipeJunction.h"
#include "math/Interpolators.h"
using namespace smoflow;

/**
 * TPipeJunction - C++
 */
TPipeJunction::TPipeJunction(Medium *fluid,
		double internalVolume,
		double flowArea,
		int stateVariableSelection) {
	this->flowArea = flowArea;
	if (flowArea <= 0) {
		RaiseComponentError(this, "The flow area should be positive.");
	}

	accFluid = FluidChamber_new(fluid);
	SMOCOMPONENT_SET_PARENT(accFluid, this);
	accFluid->setVolume(internalVolume);

	if (stateVariableSelection == 1) {
		accFluid->selectStates(iT, iD);
	} else if (stateVariableSelection == 2) {
		accFluid->selectStates(iP, iT);
	} else if (stateVariableSelection == 3) {
		accFluid->selectStates(iP, iD);
	} else if (stateVariableSelection == 4) {
		accFluid->selectStates(iP, iH);
	} else {
		RaiseComponentError(this, "Unsupported type of state variables.");
	}

	port1Flow = NULL;
	port2Flow = NULL;
	port3Flow = NULL;

	fluidState1 = NULL;
	fluidState2 = NULL;
	fluidState3 = NULL;

	pressureLoss2 = 0;
	pressureLoss3 = 0;

	dragCoeff2 = 0;
	dragCoeff3 = 0;
}

TPipeJunction::~TPipeJunction() {
}

void TPipeJunction::initFluidStates(
		int initConditionsChoice, double initialPressure,
		double initialTemperature, double initialTemperatureC, double initialGasMassFraction) {
	fluidState1 = accFluid->getFluidState();
	Medium* fluid = fluidState1->getMedium();

	fluidState2 = MediumState_new(fluid);
	MediumState_register(fluidState2);

	fluidState3 = MediumState_new(fluid);
	MediumState_register(fluidState3);

	if (initConditionsChoice == 1) {
		fluidState1->update_Tp(initialTemperature, initialPressure);
		fluidState2->update_Tp(initialTemperature, initialPressure);
		fluidState3->update_Tp(initialTemperature, initialPressure);
	} else if (initConditionsChoice == 2) {
		fluidState1->update_Tp(initialTemperatureC + 273.15, initialPressure);
		fluidState2->update_Tp(initialTemperatureC + 273.15, initialPressure);
		fluidState3->update_Tp(initialTemperatureC + 273.15, initialPressure);
	} else if (initConditionsChoice == 3) {
		fluidState1->update_pq(initialPressure, initialGasMassFraction);
		fluidState2->update_pq(initialPressure, initialGasMassFraction);
		fluidState3->update_pq(initialPressure, initialGasMassFraction);
	} else {
		RaiseComponentError(this, "Unsupported type of initialization.");
	}
}

void TPipeJunction::setFluidFlow1(FluidFlow* port1Flow) {
	this->port1Flow = port1Flow;
}

void TPipeJunction::setFluidFlow2(FluidFlow* port2Flow) {
	this->port2Flow = port2Flow;
}

void TPipeJunction::setFluidFlow3(FluidFlow* port3Flow) {
	this->port3Flow = port3Flow;
}

void TPipeJunction::getStateValues(double* value1, double* value2) {
	accFluid->getStateValues(value1, value2, true);
}

void TPipeJunction::setStateValues(double value1, double value2) {
	accFluid->setStateValues(value1, value2);
}

void TPipeJunction::getStateDerivatives(double* value1, double* value2) {
	accFluid->getStateDerivatives(value1, value2);
}

double TPipeJunction::getFluidMass() {
	return accFluid->getFluidMass();
}

void TPipeJunction::compute() {
	double netMassFlowRate = port1Flow->massFlowRate + port2Flow->massFlowRate + port3Flow->massFlowRate;
	double netEnthalpyFlow = port1Flow->enthalpyFlowRate + port2Flow->enthalpyFlowRate + port3Flow->enthalpyFlowRate;

	accFluid->compute(netMassFlowRate, netEnthalpyFlow, 0, 0); // netHeatFlowRate = netVolumeChangeRate = 0
}

void TPipeJunction::updateFluidStates23AtZeroMassFlow() {
	MediumState_copy(fluidState1, fluidState2, 2); //:TRICKY: 2 -- use (p,T)
	MediumState_copy(fluidState1, fluidState3, 2);

	pressureLoss2 = 0;
	pressureLoss3 = 0;

	dragCoeff2 = 0;
	dragCoeff3 = 0;
}

HeatFlow* TPipeJunction::getWallHeatFlow() {
	RaiseError("Unimplemented virtual method 'TPipeJunction::getWallHeatFlow'")
	return NULL;
}

void TPipeJunction::setWallNode(ThermalNode* wallNode) {
	RaiseError("Unimplemented virtual method 'TPipeJunction::setWallNode'")
}

void TPipeJunction::initWallHeatFlow() {
	RaiseError("Unimplemented virtual method 'TPipeJunction::initWallHeatFlow'")
}


/**
 * TPipeJunction_ConstantDragCoefficients - C++
 */
class TPipeJunction_ConstantDragCoefficients : public TPipeJunction {
public:
	TPipeJunction_ConstantDragCoefficients (
			Medium *fluid,
			double internalVolume,
			double flowArea,
			double dragCoeff2,
			double dragCoeff3,
			int stateVariableSelection) :
			TPipeJunction(
					fluid,
					internalVolume,
					flowArea,
					stateVariableSelection) {
		this->dragCoeff2 = dragCoeff2;
		this->dragCoeff3 = dragCoeff3;
	}

	virtual ~TPipeJunction_ConstantDragCoefficients() {
	}

	virtual void updateFluidStates23(double mDotRatio21) {
		//:TRICKY: mDotRatio21 is not used for calculation of the drag coefficients, because they are constant

		// FluidFlow in port-1 is not initialized
		if (port1Flow == NULL) {
			updateFluidStates23AtZeroMassFlow();
			return;
		}

		// FluidFlow in port-1 is initialized
		double rho1 = fluidState1->rho();
		double mDot1 = port1Flow->massFlowRate;
		double vFlow1 = mDot1 / (rho1 * flowArea);
		double dynamicPressure1 = rho1 * vFlow1 * vFlow1 / 2.;

		pressureLoss2 = dragCoeff2*dynamicPressure1;
		pressureLoss3 = dragCoeff3*dynamicPressure1;

		if (mDot1 < 0) { //:TRICKY: the T-junction has an inlet branch pipe (i.e. the flow convergence)
			pressureLoss2 = -pressureLoss2;
			pressureLoss3 = -pressureLoss3;
		}

		fluidState2->update_ph(fluidState1->p() - pressureLoss2, fluidState1->h());
		fluidState3->update_ph(fluidState1->p() - pressureLoss3, fluidState1->h());
	}
};


/**
 * TPipeJunction_RegulatingMassFlowRate - C++
 */
class TPipeJunction_RegulatingMassFlowRatio : public TPipeJunction {
public:
	TPipeJunction_RegulatingMassFlowRatio(
			Medium *fluid,
			double internalVolume,
			double flowArea,
			int stateVariableSelection) :
			TPipeJunction(
					fluid,
					internalVolume,
					flowArea,
					stateVariableSelection) {
	}

	virtual void updateFluidStates23(double mDotRatio21) {
		// FluidFlow in port-1 is not initialized
		if (port1Flow == NULL) {
			updateFluidStates23AtZeroMassFlow();
			return;
		}

		// Get mass flow rate in port-1
		double mDot1 = port1Flow->massFlowRate;
		if (mDot1 == 0.0) {
			updateFluidStates23AtZeroMassFlow();
			return;
		}

		// Limit the mass flow ratio (port1/port2) in the interval [0, 1]
		m::limitVariable(mDotRatio21, 0.0, 1.0);

		// Compute the dynamic pressure of the flow in port-1
		double rho1 = fluidState1->rho();
		double vFlow1 = mDot1 / (rho1 * flowArea);
		double dynamicPressure1 = rho1 * vFlow1 * vFlow1 / 2.;

		// Compute the drag coefficient of port-2
		if (mDot1 < 0) {  //T-junction has an inlet branch pipe
			static FunctorOneVariable* dc2Function_inletBranch = NULL;
			if (dc2Function_inletBranch == NULL) {
				ArrayXd inputValues(11); //mass flow ratio (Qa/Qt)
				inputValues <<   0.00,  0.10,  0.20,  0.30, 0.40, 0.50, 0.60, 0.70, 0.80, 0.90, 1.00;
				ArrayXd outputValues(11); //drag coefficients applicable to the outgoing connection
				outputValues << -0.60, -0.37, -0.18, -0.07, 0.26, 0.46, 0.62, 0.78, 0.94, 1.08, 1.20;

				dc2Function_inletBranch = new Interpolator1D(&inputValues, &outputValues);
			}
			FunctorCache* dc2FunctionCache_inletBranch = dc2Function_inletBranch->createCache();
			dragCoeff2 = (*dc2Function_inletBranch)(mDotRatio21, dc2FunctionCache_inletBranch);
		} else { //T-junction has an outgoing branch pipe
			static FunctorOneVariable* dc2Function_outgoingBranch = NULL;
			if (dc2Function_outgoingBranch == NULL) {
				ArrayXd inputValues(11); //mass flow ratio (Qa/Qt)
				inputValues <<  0.00, 0.10, 0.20, 0.30, 0.40, 0.50, 0.60, 0.70, 0.80, 0.90, 1.00;
				ArrayXd outputValues(11); //drag coefficients applicable to the outgoing connection
				outputValues << 1.00, 1.00, 1.01, 1.03, 1.05, 1.09, 1.15, 1.22, 1.32, 1.38, 1.45;

				dc2Function_outgoingBranch = new Interpolator1D(&inputValues, &outputValues);
			}
			FunctorCache* dc2FunctionCache_outgoingBranch = dc2Function_outgoingBranch->createCache();
			dragCoeff2 = (*dc2Function_outgoingBranch)(mDotRatio21, dc2FunctionCache_outgoingBranch);
		}
		if (mDotRatio21 == 0.0) {
			dragCoeff2 = 0.0;
		}

		// Compute the drag coefficient of port-3
		if (mDot1 < 0) {  //T-junction has an inlet branch pipe
			static FunctorOneVariable* dc3Function_inletBranch = NULL;
			if (dc3Function_inletBranch == NULL) {
				ArrayXd inputValues(11); //mass flow ratio (Qa/Qt)
				inputValues <<  0.00, 0.10, 0.20, 0.30, 0.40, 0.50, 0.60, 0.70, 0.80, 0.90, 1.00;
				ArrayXd outputValues(11); //drag coefficients applicable to the straight connection
				outputValues << 0.00, 0.16, 0.27, 0.38, 0.46, 0.53, 0.57, 0.59, 0.60, 0.59, 0.55;

				dc3Function_inletBranch = new Interpolator1D(&inputValues, &outputValues);
			}
			FunctorCache* dc3FunctionCache_inletBranch = dc3Function_inletBranch->createCache();
			dragCoeff3 = (*dc3Function_inletBranch)(mDotRatio21, dc3FunctionCache_inletBranch);
		} else { //T-junction has an outgoing branch pipe
			static FunctorOneVariable* dc3Function_outgoingBranch = NULL;
			if (dc3Function_outgoingBranch == NULL) {
				ArrayXd inputValues(11); //mass flow ratio (Qa/Qt)
				inputValues <<  0.00, 0.100, 0.20, 0.30, 0.40, 0.50, 0.60, 0.70, 0.80, 0.90, 1.00;
				ArrayXd outputValues(11); //drag coefficients applicable to the straight connection
				outputValues << 0.00, 0.004, 0.02, 0.04, 0.06, 0.10, 0.15, 0.20, 0.26, 0.32, 0.40;

				dc3Function_outgoingBranch = new Interpolator1D(&inputValues, &outputValues);
			}
			FunctorCache* dc3FunctionCache_outgoingBranch = dc3Function_outgoingBranch->createCache();
			dragCoeff3 = (*dc3Function_outgoingBranch)(mDotRatio21, dc3FunctionCache_outgoingBranch);
		}
		if (mDotRatio21 == 1.0) {
			dragCoeff3 = 0.0;
		}

		// Compute the pressure losses
		pressureLoss2 = dragCoeff2*dynamicPressure1;
		pressureLoss3 = dragCoeff3*dynamicPressure1;

		if (mDot1 < 0) {  //:TRICKY: the T-junction has an inlet branch pipe (i.e. the flow convergence)
			pressureLoss2 = -pressureLoss2;
			pressureLoss3 = -pressureLoss3;
		}

		// Update the fluid states of port-2 and port-3
		fluidState2->update_ph(fluidState1->p() - pressureLoss2, fluidState1->h());
		fluidState3->update_ph(fluidState1->p() - pressureLoss3, fluidState1->h());
	}
};

/**
 * TPipeJunction_ConstantDragCoefficients_HeatExchanger - C++
 */

class TPipeJunction_ConstantDragCoefficients_HeatExchanger : public TPipeJunction_ConstantDragCoefficients {
public:
	TPipeJunction_ConstantDragCoefficients_HeatExchanger(
			Medium *fluid,
			double internalVolume,
			double flowArea,
			double dragCoeff2,
			double dragCoeff3,
			ForcedConvection* convection,
			int stateVariableSelection) :
				TPipeJunction_ConstantDragCoefficients(
					fluid,
					internalVolume,
					flowArea,
					dragCoeff2,
					dragCoeff3,
					stateVariableSelection) {
		this->convection = convection;
		SMOCOMPONENT_SET_PARENT(this->convection, this);

		this->wallHeatFlow = NULL;
		this->wallNode = NULL;
	}

	virtual ~TPipeJunction_ConstantDragCoefficients_HeatExchanger() {
	}

	virtual HeatFlow* getWallHeatFlow() {
		return wallHeatFlow;
	}

	virtual void setWallNode(ThermalNode* wallNode) {
		this->wallNode = wallNode;
	}

	virtual void initWallHeatFlow() {
		wallHeatFlow = HeatFlow_new();
		HeatFlow_register(this->wallHeatFlow);

		convection->init(fluidState1, fluidState1, wallNode); //:TRICKY: the both states of the convection are the internal state
		convection->setLimitOutput(false);
	}

	virtual void compute() {
		double netMassFlowRate = port1Flow->massFlowRate + port2Flow->massFlowRate + port3Flow->massFlowRate;
		double netEnthalpyFlow = port1Flow->enthalpyFlowRate + port2Flow->enthalpyFlowRate + port3Flow->enthalpyFlowRate;

		convection->compute(port1Flow->massFlowRate); //TRICKY
		convection->updateHeatFlow(wallHeatFlow);
		double netHeatFlowRate = convection->getHeatFlowRate();

		accFluid->compute(netMassFlowRate, netEnthalpyFlow, netHeatFlowRate, 0); //netVolumeChangeRate = 0
	}

private:
	ForcedConvection* convection;

	// Thermal port
	ThermalNode* wallNode; // input
	HeatFlow* wallHeatFlow;	// output
};


/**
 * TPipeJunction - C
 */
TPipeJunction* TPipeJunction_ConstantDragCoefficients_new(
		Medium *fluid,
		double internalVolume,
		double flowArea,
		double dragCoeff2,
		double dragCoeff3,
		int stateVariableSelection) {
	return new TPipeJunction_ConstantDragCoefficients(
			fluid,
			internalVolume,
			flowArea,
			dragCoeff2,
			dragCoeff3,
			stateVariableSelection);
}

TPipeJunction* TPipeJunction_RegulatingMassFlowRatio_new(
		Medium* fluid,
		double internalVolume,
		double flowArea,
		int stateVariableSelection) {
	return new TPipeJunction_RegulatingMassFlowRatio(
				fluid,
				internalVolume,
				flowArea,
				stateVariableSelection);
}

TPipeJunction* TPipeJunction_ConstantDragCoefficients_HeatExchanger_new(
			Medium* fluid,
			double internalVolume,
			double flowArea,
			double dragCoeff2,
			double dragCoeff3,
			ForcedConvection* convection,
			int stateVariableSelection) {
	return new TPipeJunction_ConstantDragCoefficients_HeatExchanger(
				fluid,
				internalVolume,
				flowArea,
				dragCoeff2,
				dragCoeff3,
				convection,
				stateVariableSelection);
}

void TPipeJunction_initFluidStates(
		TPipeJunction* component,
		int initConditionsChoice,
		double initialPressure,
		double initialTemperature,
		double initialTemperatureC,
		double initialGasMassFraction) {
	component->initFluidStates(
			initConditionsChoice,
			initialPressure,
			initialTemperature,
			initialTemperatureC,
			initialGasMassFraction);
}

void TPipeJunction_setFluidFlow1(TPipeJunction* component, FluidFlow* port1Flow) {
	component->setFluidFlow1(port1Flow);
}

void TPipeJunction_setFluidFlow2(TPipeJunction* component, FluidFlow* port2Flow) {
	component->setFluidFlow2(port2Flow);
}

void TPipeJunction_setFluidFlow3(TPipeJunction* component, FluidFlow* port3Flow) {
	component->setFluidFlow3(port3Flow);
}

void TPipeJunction_setStateValues(TPipeJunction* component, double value1, double value2) {
	component->setStateValues(value1, value2);
}

void TPipeJunction_getStateValues(TPipeJunction* component, double* value1, double* value2) {
	component->getStateValues(value1, value2);
}

void TPipeJunction_getStateDerivatives(TPipeJunction* component, double* value1, double* value2) {
	component->getStateDerivatives(value1, value2);
}

MediumState* TPipeJunction_getFluidState1(TPipeJunction* component) {
	return component->getFluidState1();
}

MediumState* TPipeJunction_getFluidState2(TPipeJunction* component) {
	return component->getFluidState2();
}

MediumState* TPipeJunction_getFluidState3(TPipeJunction* component) {
	return component->getFluidState3();
}

double TPipeJunction_getPressureLoss2(TPipeJunction* component) {
	return component->getPressureLoss2();
}

double TPipeJunction_getPressureLoss3(TPipeJunction* component) {
	return component->getPressureLoss3();
}

double TPipeJunction_getFluidMass(TPipeJunction* component) {
	return component->getFluidMass();
}

double TPipeJunction_getDragCoeff2(TPipeJunction* component) {
	return component->getDragCoeff2();
}

double TPipeJunction_getDragCoeff3(TPipeJunction* component) {
	return component->getDragCoeff3();
}

void TPipeJunction_compute(TPipeJunction* component) {
	component->compute();
}

void TPipeJunction_updateFluidStates23(TPipeJunction* component, double mDotRatio21) {
	component->updateFluidStates23(mDotRatio21);
}

void TPipeJunction_HeatExchanger_setWallNode(
		TPipeJunction* component, ThermalNode* wallNode) {
	component->setWallNode(wallNode);
}

void TPipeJunction_HeatExchanger_initWallHeatFlow(TPipeJunction* component) {
	component->initWallHeatFlow();
}

HeatFlow* TPipeJunction_HeatExchanger_getWallHeatFlow(
		TPipeJunction* component) {
	return component->getWallHeatFlow();
}

