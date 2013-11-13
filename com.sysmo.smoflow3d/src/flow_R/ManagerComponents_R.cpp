/*
 * ManagerRComponents.cpp
 *
 *  Created on: Jul 31, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "ManagerComponents_R.h"

using namespace smoflow;

/**
 * ManagerRComponents - C++
 */
ManagerComponents_R::ManagerComponents_R() {
	mainState1 = NULL;
	mainState2 = NULL;

	componentMainState1 = NULL;
	componentMainState2 = NULL;

	beginAdaptor = NULL;
	endAdaptor = NULL;

	isComponentsChainContructed = false;

	cache_massFlowRate = 0.001; //:SMO_TODO: (???) cache_massFlowRate
}

ManagerComponents_R::~ManagerComponents_R() {
}

/**
 * Construct R-components chain (NEW)
 */
void ManagerComponents_R::addMainState1(BeginAdaptor_R* beginAdaptor, int state1Index) {
	mainState1 = MediumState_get(state1Index);
	this->beginAdaptor = beginAdaptor;
}

void ManagerComponents_R::addMainState2(EndAdaptor_R* endAdaptor, int state2Index) {
	mainState2 = MediumState_get(state2Index);
	this->endAdaptor = endAdaptor;
}

void ManagerComponents_R::addComponent(Component_R* component, int state1Index) {
	MediumState* state1 = MediumState_get(state1Index);
	if (state1 == mainState1) {
		componentMainState1 = component;
	} else {
		Component_R* prevComponent = getParent_Component(state1);
		component->setComponent1(prevComponent);
		prevComponent->setComponent2(component);
	}
}

void ManagerComponents_R::setComponentMainState2(EndAdaptor_R* endAdaptor, int state1Index) {
	MediumState* state1 = MediumState_get(state1Index);
	Component_R* component_R = getParent_Component(state1);
	if (component_R == NULL) {
		RaiseComponentError(endAdaptor, "Could not construct R-components chain - the R-component on port1 is NULL.");
	}

	componentMainState2 = component_R;
}

void ManagerComponents_R::constructComponentsChain() {
	if (isComponentsChainContructed) {
		RaiseError("Try to construct for the second time the R-components chain.");
	}

	// Create the internal begin state
	Medium* fluid = mainState1->getMedium();
	MediumState* state1 = MediumState_new(fluid);
	MediumState_register(state1);
	SMOOBJECT_SET_PARENT_COMPONENT(state1, beginAdaptor);
	state1->update_Tp(cst::StandardTemperature, cst::StandardPressure);

	// Start construction of the R-components chain
	Component_R* component_R = componentMainState1;
	do {
		component_R->init(state1);
		components.push_back(component_R);
		state1 = component_R->getState2();

		component_R = component_R->getComponent2();
	} while (component_R != NULL);

	if (component_R != componentMainState2) {
		RaiseComponentError(component_R, "Could not construct R-components chain - there are two end R-components.");
	}

	isComponentsChainContructed = true;
}

Component_R* ManagerComponents_R::getParent_Component(SmoObject* smoObject) {
	return dynamic_cast<Component_R*>(smoObject->parentComponent);
}

/**
 * Compute R-components chain
 */
void ManagerComponents_R::compute() {
	// Check - the R-components chain is constructed
	if (!isComponentsChainContructed) {
		constructComponentsChain();
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
	//:SMO_FIXME: there is an oscillation of the mass flow rate in a model with two volumes and a valve bettwen them
	/*
	if (m::fabs(mainState1->p() - mainState2->p()) < 10) { //[Pa]
		return cst::zeroMassFlowRate;
	}
	//*/


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
	static const int maxNumIter = 100; //:SMO_TODO: (???) maxNumIter
	static const double relTolerance = 1e-08;

	double downstreamPressure = mainDownstreamState->p();
	double minDownstreamPressure = m::max(1e-5, downstreamPressure - 1e5); //:SMO_TODO: (???) m::min(1.0*1e5, 0.5*downstreamPressure);
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
			up_MassFlowRate = massFlowRate;
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
			up_MassFlowRate = massFlowRate;
			up_MassFlowRate_isInit = true;

			up_downstreamPressure = calcDownstreamPressure;
			up_downstreamPressure_isInit = true;

			if (down_MassFlowRate_isInit) { //:TRICKY: when 'down_MassFlowRate_isInit' is true than and 'down_downstreamPressure_isInit' is also true
				// Find massFlowRate using bisection method
				//massFlowRate = (up_MassFlowRate + down_MassFlowRate) / 2.0;

				// Find massFlowRate using Newton method
				double slope = (down_downstreamPressure - up_downstreamPressure) / (down_MassFlowRate - up_MassFlowRate);
				massFlowRate = down_MassFlowRate + (downstreamPressure - down_downstreamPressure) / slope;

				AssertInComponent(m::isValueInsideInterval(massFlowRate, down_MassFlowRate, up_MassFlowRate), beginAdaptor);
			} else {
				massFlowRate /= stepCoeff;
			}
		} else {
			down_MassFlowRate = massFlowRate;
			down_MassFlowRate_isInit = true;

			//AssertInComponent(!down_MassFlowRate_isInit || (down_downstreamPressure < calcDownstreamPressure), beginAdaptor);
			down_downstreamPressure = calcDownstreamPressure;

			if (up_downstreamPressure_isInit) {
				// Find massFlowRate using bisection method
				//massFlowRate = (up_MassFlowRate + down_MassFlowRate) / 2.0;

				// Find massFlowRate using Newton method
				double slope = (down_downstreamPressure - up_downstreamPressure) / (down_MassFlowRate - up_MassFlowRate);
				massFlowRate = down_MassFlowRate + (downstreamPressure - down_downstreamPressure) / slope;

				AssertInComponent(m::isValueInsideInterval(massFlowRate, down_MassFlowRate, up_MassFlowRate), beginAdaptor);
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
 * ManagerRComponents - C
 */
static std::vector<ManagerComponents_R*> ManagerComponentsRegistry;

ManagerComponents_R* ManagerComponents_R_new() {
	return new ManagerComponents_R();
}

int ManagerComponents_R_register(ManagerComponents_R* manager) {
	ManagerComponentsRegistry.push_back(manager);
	size_t instanceIndex = ManagerComponentsRegistry.size();
	manager->instanceIndex = instanceIndex;
	return instanceIndex;
}

ManagerComponents_R* ManagerComponents_R_get(int managerIndex) {
	return ManagerComponentsRegistry.at(managerIndex - 1);
}



void ManagerComponents_R_addMainState1(ManagerComponents_R* manager, BeginAdaptor_R* beginAdaptor, int state1Index) {
	manager->addMainState1(beginAdaptor, state1Index);
}

void ManagerComponents_R_addMainState2(ManagerComponents_R* manager, EndAdaptor_R* endAdaptor, int state2Index) {
	manager->addMainState2(endAdaptor, state2Index);
}

void ManagerComponents_R_addComponent(ManagerComponents_R* manager, Component_R* component, int state1Index) {
	manager->addComponent(component, state1Index);
}

void ManagerComponents_R_setComponentMainState2(ManagerComponents_R* manager, EndAdaptor_R* endAdaptor, int state1Index) {
	manager->setComponentMainState2(endAdaptor, state1Index);
}

int ManagerComponents_R_getFlow2Index(ManagerComponents_R* manager) {
	manager->getFlow2Index();
}

void ManagerComponents_R_compute(ManagerComponents_R* manager, EndAdaptor_R* endAdaptor) {
	manager->compute();
}
