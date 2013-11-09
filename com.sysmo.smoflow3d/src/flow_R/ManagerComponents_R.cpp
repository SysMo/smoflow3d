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

void ManagerComponents_R::add(Component_R* component_R, int state1Index, int state2Index) {
	if (isComponentsChainContructed) {
		RaiseComponentError(component_R, "Try to add R-component to R-components chain that is already constructed.");
	}

	component_R->setPort1StateIndex(state1Index);
	component_R->setPort2StateIndex(state2Index);

	MediumState* state1 = MediumState_get(state1Index);
	MediumState* state2 = MediumState_get(state2Index);
	if (state1->getMedium() != state2->getMedium()) {
		RaiseComponentError(component_R, "Different media connected to the R-component!");
	}

	bool state1_hasVirtualCapacityParent = hasVirtualCapacityParent(state1);
	bool state2_hasVirtualCapacityParent = hasVirtualCapacityParent(state2);
	if (!state1_hasVirtualCapacityParent && !state2_hasVirtualCapacityParent) {
		//:TRICKY: R-components chain contains only one R-component (i.e. the input component_R)
		addMainState1(state1, component_R);
		addMainState2(state2, component_R);
		constructComponentsChain_OneComponent();
	} else if (state1_hasVirtualCapacityParent && state2_hasVirtualCapacityParent) {
		VirtualCapacity_R* state1VirtualCapacityParent = getVirtualCapacityParent(state1);
		connectVirtualCapacityAndComponent(state1VirtualCapacityParent, component_R);

		VirtualCapacity_R* state2VirtualCapacityParent = getVirtualCapacityParent(state2);
		connectVirtualCapacityAndComponent(state2VirtualCapacityParent, component_R);

		constructComponentsChain_ManyComponents();
	} else if (!state1_hasVirtualCapacityParent && state2_hasVirtualCapacityParent) {
		VirtualCapacity_R* state2VirtualCapacityParent = getVirtualCapacityParent(state2);
		connectVirtualCapacityAndComponent(state2VirtualCapacityParent, component_R);

		addMainState1(state1, component_R);
		constructComponentsChain_ManyComponents();
	} else if (state1_hasVirtualCapacityParent && !state2_hasVirtualCapacityParent) {
		VirtualCapacity_R* state1VirtualCapacityParent = getVirtualCapacityParent(state1);
		connectVirtualCapacityAndComponent(state1VirtualCapacityParent, component_R);

		addMainState2(state2, component_R);
		constructComponentsChain_ManyComponents();
	} else {
		RaiseComponentError(component_R, "Unreachable source code!");
	}
}

void ManagerComponents_R::connectVirtualCapacityAndComponent(VirtualCapacity_R* virtualCapacity, Component_R* component_R) {
	virtualCapacity->addComponent(component_R);
	component_R->addVirtualCapacity(virtualCapacity);
}

void ManagerComponents_R::addMainState1(MediumState* state, Component_R* component_R) {
	//:TRICKY: the functions addMainState1 and addMainState2 minimize the number of the reversed R-components in the chains
	if (mainState1 == NULL) {
		mainState1 = state;
		componentMainState1 = component_R;
		return;
	}

	if (mainState1 != NULL && mainState2 == NULL) {
			mainState2 = state;
			componentMainState2 = component_R;
			return;
	}

	RaiseComponentError(component_R, "R-components chain has more than two ends.");
}

void ManagerComponents_R::addMainState2(MediumState* state, Component_R* component_R) {
	if (mainState2 == NULL) {
		mainState2 = state;
		componentMainState2 = component_R;
		return;
	}

	if (mainState2 != NULL && mainState1 == NULL) {
		mainState1 = state;
		componentMainState1 = component_R;
		return;
	}

	RaiseComponentError(component_R, "R-components chain has more than two ends.");
}

void ManagerComponents_R::constructComponentsChain_OneComponent() {
	components.push_back(componentMainState1);

	// Initialize states of the input component_R
	Medium* fluid = mainState1->getMedium();
	MediumState* componentState1 = MediumState_new(fluid);
	MediumState_register(componentState1);
	componentState1->update_Tp(cst::StandardTemperature, cst::StandardPressure);

	MediumState* componentState2 = MediumState_new(fluid);
	MediumState_register(componentState2);
	componentState2->update_Tp(cst::StandardTemperature, cst::StandardPressure);

	componentMainState1->init(componentState1, componentState2);
	isComponentsChainContructed = true;
}

bool ManagerComponents_R::isComponentsChainReadyForConstructing_ManyComponents() {
	if (componentMainState1 == NULL) {
		return false;
	}

	Component_R* component_R = componentMainState1;
	VirtualCapacity_R* virtualCapacity = component_R->getOtherVirtualCapacity(NULL); //:TRICKY: get the first virtual capacity
	if (virtualCapacity == NULL) {
		return false;
	}

	do {
		component_R = virtualCapacity->getOtherComponent(component_R);
		if (component_R == NULL) {
			return false;
		}

		virtualCapacity = component_R->getOtherVirtualCapacity(virtualCapacity);
	} while (virtualCapacity != NULL);

	if (component_R != componentMainState2) {
		return false;
	}

	return true;
}

void ManagerComponents_R::constructComponentsChain_ManyComponents() {
	// Check
	if (!isComponentsChainReadyForConstructing_ManyComponents()) {
		return;
	}

	// Start construction of the R-components chain
	Component_R* component_R = componentMainState1;
	VirtualCapacity_R* virtualCapacity = component_R->getOtherVirtualCapacity(NULL); //:TRICKY: get the first virtual capacity
	if (virtualCapacity == NULL) {
		RaiseComponentError(component_R, "Could not construct R-components chain - the first R-component is not connected to the 'Virtual Capacity'-component.");
	}


	// Create R-components chain that contains more than two R-component)
	Medium* fluid = mainState1->getMedium();
	MediumState* componentState1 = MediumState_new(fluid);
	MediumState_register(componentState1);
	componentState1->update_Tp(cst::StandardTemperature, cst::StandardPressure);


	VirtualCapacity_R* prevVirtualCapacity = NULL;
	do {
		MediumState* componentState2 = virtualCapacity->getState();
		if (component_R->getPort2StateIndex() != virtualCapacity->getStateIndex()) {
			component_R->setIsReversed(true);
			component_R->init(componentState2, componentState1);
		} else {
			component_R->init(componentState1, componentState2);
		}
		componentState1 = componentState2;
		components.push_back(component_R);

		component_R = virtualCapacity->getOtherComponent(component_R);
		if (component_R == NULL) {
			RaiseComponentError(component_R, "Could not construct R-components chain - there is a bad (R-C-R) connection.");
		}

		prevVirtualCapacity = virtualCapacity;
		virtualCapacity = component_R->getOtherVirtualCapacity(virtualCapacity);
	} while (virtualCapacity != NULL);


	MediumState* componentState2 = MediumState_new(fluid);
	MediumState_register(componentState2);
	componentState2->update_Tp(cst::StandardTemperature, cst::StandardPressure);

	if (component_R->getPort1StateIndex() != prevVirtualCapacity->getStateIndex()) {
		component_R->setIsReversed(true);
		component_R->init(componentState2, componentState1);
	} else {
		component_R->init(componentState1, componentState2);
	}
	components.push_back(component_R);


	if (component_R != componentMainState2) {
		RaiseComponentError(component_R, "Could not construct R-components chain - there are two end R-components.");
	}


	isComponentsChainContructed = true;
}

void ManagerComponents_R::compute(Component_R* component_R) {
	// Check
	component_R->setIsComputed(true);
	if (!areAllComponentsComputed()) {
		//:TRICKY: the compute method is called only once
		return;
	}

	// Compute the mass flow rate
	double massFlowRate = computeMassFlowRate();
	if (massFlowRate != cst::zeroMassFlowRate) {
		cache_massFlowRate = massFlowRate;
	}

	// Set all components that are not computed
	setAllComponentsNoComputed();

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

bool ManagerComponents_R::areAllComponentsComputed() {
	if (components.empty()) {
		return false;
	}

	for (int i = 0; i < getNumComponents(); i++) {
		if (!components[i]->isComputed()) {
			return false;
		}
	}

	return true;
}

void ManagerComponents_R::setAllComponentsNoComputed() {
	for (int i = 0; i < getNumComponents(); i++) {
		components[i]->setIsComputed(false);
	}
}

bool ManagerComponents_R::hasVirtualCapacityParent(MediumState* state) {
	if (getVirtualCapacityParent(state) != NULL) {
		return true;
	}

	return false;
}

VirtualCapacity_R* ManagerComponents_R::getVirtualCapacityParent(MediumState* state) {
	return dynamic_cast<VirtualCapacity_R*>(state->parentComponent);
}

/**
 * ManagerRComponents - C
 */

void ManagerComponents_R_add(Component_R* component_R, int state1Index, int state2Index) {
	manager.add(component_R, state1Index, state2Index);
}

void ManagerComponents_R_compute(Component_R* component_R) {
	manager.compute(component_R);
}
