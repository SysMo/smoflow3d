/*
 * ManagerRComponents.cpp
 *
 *  Created on: Jul 31, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "ManagerComponents_R.h"

using namespace smoflow;

static ManagerComponents_R manager;

/**
 * ManagerRComponents - C++
 */
ManagerComponents_R::ManagerComponents_R() {
	mainState1 = NULL;
	mainState2 = NULL;

	componentMainState1 = NULL;
	componentMainState2 = NULL;

	isComponentsChainContructed = false;

	cache_massFlowRate = 0.001; //:TODO: (???)
}

ManagerComponents_R::~ManagerComponents_R() {
}

/**
 * Construct R-components chain (NEW)
 */
void ManagerComponents_R::addMainState1(int state1Index) {
	mainState1 = MediumState_get(state1Index);
}

void ManagerComponents_R::addMainState2(int state2Index) {
	mainState2 = MediumState_get(state2Index);
}

void ManagerComponents_R::addComponent(Component_R* component_R, int state1Index) {
	MediumState* state1 = MediumState_get(state1Index);
	if (state1 == mainState1) {
		componentMainState1 = component_R;
	} else {
		VirtualCapacity_R* virtualCapacity = getParent_VirtualCapacity(state1);
		if (virtualCapacity == NULL) {
			RaiseComponentError(component_R, "Could not construct R-components chain - the 'Virtual Capacity'-component on port1 is NULL.");
		}

		virtualCapacity->addComponent2(component_R);
		component_R->addVirtualCapacity1(virtualCapacity);
	}
}

void ManagerComponents_R::addVirtualCapacity(VirtualCapacity_R* virtualCapacity, int flow1Index) {
	FluidFlow* flow1 = FluidFlow_get(flow1Index);
	Component_R* component_R = getParent_Component(flow1);
	if (component_R == NULL) {
		RaiseComponentError(virtualCapacity, "Could not construct R-components chain - the R-component on port1 is NULL.");
	}

	component_R->addVirtualCapacity2(virtualCapacity);
	virtualCapacity->addComponent1(component_R);
}

void ManagerComponents_R::addComponentMainState2(EndAdaptor_R* endAdaptor, int flow1Index) {
	FluidFlow* flow1 = FluidFlow_get(flow1Index);
	Component_R* component_R = getParent_Component(flow1);
	if (component_R == NULL) {
		RaiseComponentError(endAdaptor, "Could not construct R-components chain - the R-component on port1 is NULL.");
	}

	componentMainState2 = component_R;
}

void ManagerComponents_R::constructComponentsChain() {
	if (isComponentsChainContructed) {
		RaiseError("Try to construct for the second time the R-components chain.");
	}

	// Start construction of the R-components chain
	Component_R* component_R = componentMainState1;
	VirtualCapacity_R* virtualCapacity = component_R->getVirtualCapacity2();
	if (virtualCapacity == NULL) {
		//:TRICKY: R-components chain contains only one R-component
		Medium* fluid = mainState1->getMedium();
		MediumState* componentState1 = MediumState_new(fluid);
		MediumState_register(componentState1);
		componentState1->update_Tp(cst::StandardTemperature, cst::StandardPressure);

		MediumState* componentState2 = MediumState_new(fluid);
		MediumState_register(componentState2);
		componentState2->update_Tp(cst::StandardTemperature, cst::StandardPressure);

		componentMainState1->init(componentState1, componentState2);
		components.push_back(componentMainState1);

		isComponentsChainContructed = true;
		return;
	}


	// Create R-components chain that contains more than two R-component
	Medium* fluid = mainState1->getMedium();
	MediumState* componentState1 = MediumState_new(fluid);
	MediumState_register(componentState1);
	componentState1->update_Tp(cst::StandardTemperature, cst::StandardPressure);


	do {
		MediumState* componentState2 = virtualCapacity->getState();
		component_R->init(componentState1, componentState2);
		components.push_back(component_R);
		componentState1 = componentState2;


		component_R = virtualCapacity->getComponent2();
		if (component_R == NULL) {
			RaiseComponentError(component_R, "Could not construct R-components chain - there is a bad (R-C-R) connection.");
		}

		virtualCapacity = component_R->getVirtualCapacity2();
	} while (virtualCapacity != NULL);


	MediumState* componentState2 = MediumState_new(fluid);
	MediumState_register(componentState2);
	componentState2->update_Tp(cst::StandardTemperature, cst::StandardPressure);

	component_R->init(componentState1, componentState2);
	components.push_back(component_R);


	if (component_R != componentMainState2) {
		RaiseComponentError(component_R, "Could not construct R-components chain - there are two end R-components.");
	}


	isComponentsChainContructed = true;
}


/**
 * Compute R-components chain
 */
void ManagerComponents_R::compute() {
	// Check - the R-components chain is constructed
	if (!isComponentsChainContructed) {
		constructComponentsChain();
		return;
	}


	// Compute the mass flow rate
	double massFlowRate = computeMassFlowRate();
	if (massFlowRate != cst::zeroMassFlowRate) {
		cache_massFlowRate = massFlowRate;
	}

	// Update flows of the all components
	updateFlows(massFlowRate);
}

double ManagerComponents_R::computeMassFlowRate() {
	int numComponents = getNumComponents();

	// Check for pressure difference
	/*if (m::fabs(mainState1->p() - mainState2->p()) < 10) { //[Pa] //:TODO: (MILEN) (???)
		return cst::zeroMassFlowRate;
	}*/


	// Get upstream and downstream (i.e. first and last component)
	MediumState* mainUpstreamState = mainState1;
	MediumState* mainDownstreamState = mainState2;
	Component_R* upstreamComponent = components.front();
	Component_R* downstreamComponent = components.back();
	bool reverseStream = false;

	if (mainState1->p() < mainState2->p()) { //reverse stream
		mainUpstreamState = mainState2;
		mainDownstreamState = mainState1;
		upstreamComponent = components.back();
		downstreamComponent = components.front();
		reverseStream = true;
	}

	// Initialize mass flow rate
	double massFlowRate = m::fabs(cache_massFlowRate); //:TRICKY: (MILEN) ???
	if (reverseStream) {
		massFlowRate = -massFlowRate;
	}

	// Check - the components chain is closed
	for (int i = 0; i < numComponents; i++) {
		if (components[i]->isFlowClosed(massFlowRate)) {
			return cst::zeroMassFlowRate;
		}
	}

	// Initialize
	double up_MassFlowRate = 0.0;
	bool up_MassFlowRate_isInit = false;
	double down_MassFlowRate = 0.0;
	bool down_MassFlowRate_isInit = false;

	double down_downstreamPressure = 0.0;
	double up_downstreamPressure = 0.0;
	bool up_downstreamPressure_isInit = false;

	upstreamComponent->getUpstreamState(massFlowRate)->update_Tp(mainUpstreamState->T(), mainUpstreamState->p());

	// Compute mass flow rate using iteration
	double stepCoeff = 2.0;
	static const int maxNumIter = 100; //:TODO: (???)
	static const double relTolerance = 1e-08;

	double downstreamPressure = mainDownstreamState->p();
	double minDownstreamPressure = m::max(1e-5, downstreamPressure - 1e5); // m::min(1.0*1e5, 0.5*downstreamPressure); //:TODO: (???)
	int numIter;
	for (numIter = 1; numIter < maxNumIter; numIter++) {
		bool succ;
		for (int i = 0; i < numComponents; i++) {
			int componentIndex = (reverseStream) ? numComponents - i - 1 : i;
			succ = components[componentIndex]->compute(massFlowRate, minDownstreamPressure);
			if (!succ) {
				break;
			}
		}

		if (!succ) {
			up_MassFlowRate = massFlowRate; //:TODO: check that massFlowRate < up_MassFlowRate
			up_MassFlowRate_isInit = true;
			if (down_MassFlowRate_isInit) {
				massFlowRate = (up_MassFlowRate + down_MassFlowRate) / 2.0;
			} else {
				massFlowRate /= stepCoeff;
			}
			continue;
		}


		double calcDownstreamPressure = downstreamComponent->getDownstreamState(massFlowRate)->p();
		double relError = (calcDownstreamPressure - downstreamPressure) / downstreamPressure;
		if (m::fabs(relError) < relTolerance) {
			break;
		}

		if (calcDownstreamPressure < downstreamPressure) {
			up_MassFlowRate = massFlowRate; //:TODO: check that massFlowRate < up_MassFlowRate
			up_MassFlowRate_isInit = true;
			up_downstreamPressure = calcDownstreamPressure;
			up_downstreamPressure_isInit = true;
			if (down_MassFlowRate_isInit) { //:TRICKY: when 'down_MassFlowRate_isInit = true' than and 'down_downstreamPressure_isInit = true'
				//massFlowRate = (up_MassFlowRate + down_MassFlowRate) / 2.0;
				double slope = (down_downstreamPressure - up_downstreamPressure) / (down_MassFlowRate - up_MassFlowRate);
				massFlowRate = down_MassFlowRate + (downstreamPressure - down_downstreamPressure) / slope; //:TODO: check down_MassFlowRate < massFlowRate < up_MassFlowRate
			} else {
				massFlowRate /= stepCoeff;
			}
		} else {
			down_MassFlowRate = massFlowRate; //:TODO: check that massFlowRate > down_MassFlowRate
			down_MassFlowRate_isInit = true;
			down_downstreamPressure = calcDownstreamPressure;
			if (up_downstreamPressure_isInit) {
				//massFlowRate = (up_MassFlowRate + down_MassFlowRate) / 2.0;
				double slope = (down_downstreamPressure - up_downstreamPressure) / (down_MassFlowRate - up_MassFlowRate);
				massFlowRate = down_MassFlowRate + (downstreamPressure - down_downstreamPressure) / slope; //:TODO: check down_MassFlowRate < massFlowRate < up_MassFlowRate
			} else if (up_MassFlowRate_isInit) {
				massFlowRate = (up_MassFlowRate + down_MassFlowRate) / stepCoeff;
			} else {
				massFlowRate *= stepCoeff;
			}
		}
	}

	// Check
	if (numIter >= maxNumIter) {
		RaiseComponentError(upstreamComponent, "Computation of the mass flow rate in a R-components chain did not converge.");
	}

	return massFlowRate;
}

void ManagerComponents_R::updateFlows(double massFlowRate) {
	for (int i = 0; i < getNumComponents(); i++) {
		components[i]->updateFlows(massFlowRate);
	}
}

/**
 * Helpful functions
 */
VirtualCapacity_R* ManagerComponents_R::getParent_VirtualCapacity(MediumState* state) {
	return dynamic_cast<VirtualCapacity_R*>(state->parentComponent);
}

Component_R* ManagerComponents_R::getParent_Component(FluidFlow* flow) {
	return dynamic_cast<Component_R*>(flow->parentComponent);
}

/**
 * ManagerRComponents - C
 */
void ManagerComponents_R_addMainState1(BeginAdaptor_R* beginAdaptor, int state1Index) {
	manager.addMainState1(state1Index);
}

void ManagerComponents_R_addMainState2(EndAdaptor_R* endAdaptor, int state2Index) {
	manager.addMainState2(state2Index);
}

void ManagerComponents_R_addComponent(Component_R* component_R, int state1Index) {
	manager.addComponent(component_R, state1Index);
}

void ManagerComponents_R_addVirtualCapacity(VirtualCapacity_R* virtualCapacity, int flow1Index) {
	manager.addVirtualCapacity(virtualCapacity, flow1Index);
}

void ManagerComponents_R_addComponentMainState2(EndAdaptor_R* endAdaptor, int flow1Index) {
	manager.addComponentMainState2(endAdaptor, flow1Index);
}

void ManagerComponents_R_compute(EndAdaptor_R* endAdaptor) {
	manager.compute();
}
