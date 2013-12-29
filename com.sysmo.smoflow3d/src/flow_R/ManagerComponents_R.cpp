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
	outerState1 = NULL;
	outerState2 = NULL;

	componentOuterState1 = NULL;
	componentOuterState2 = NULL;

	beginAdaptor = NULL;
	endAdaptor = NULL;

	isComponentsChainContructed = false;
	isComputed = false;

	isFlowClosed = false;
	discFlag_isFlowClosed = false;
	discFlag_isFlowClosed_isInit = false;

	discFlag_isFlowDirectionChanged = false;
	discFlag_isFlowDirectionChanged_isInit = false;


	isFlowClosed_byPressDiff = false;

	isClosingPressDiffCrossed = false;
	discFlag_isClosingPressDiffCrossed = false;
	discFlag_isClosingPressDiffCrossed_isInit = false;

	isOpeningPressDiffCrossed = false;
	discFlag_isOpeningPressDiffCrossed = false;
	discFlag_isOpeningPressDiffCrossed_isInit = false;

	cache_massFlowRate = cst::zeroMassFlowRate;
}

ManagerComponents_R::~ManagerComponents_R() {
}

/**
 * Construct R-components chain (NEW)
 */
void ManagerComponents_R::addOuterState1(BeginAdaptor_R* beginAdaptor, int state1Index) {
	outerState1 = MediumState_get(state1Index);
	this->beginAdaptor = beginAdaptor;
}

void ManagerComponents_R::addOuterState2(EndAdaptor_R* endAdaptor, int state2Index) {
	outerState2 = MediumState_get(state2Index);
	this->endAdaptor = endAdaptor;
}

void ManagerComponents_R::addComponent(FlowComponent_R* component, int prevComponentID) {
	Component_R* prevComponentR = Component_R_get(prevComponentID);

	BeginAdaptor_R* prevComponent_BebinAdaptor = dynamic_cast<BeginAdaptor_R*>(prevComponentR);
	if (prevComponent_BebinAdaptor != NULL) {
		componentOuterState1 = component;
		return;
	}

	FlowComponent_R* prevComponent = dynamic_cast<FlowComponent_R*>(prevComponentR);
	if (prevComponent) {
		component->setComponent1(prevComponent);
		prevComponent->setComponent2(component);
		return;
	}

	RaiseError("Could not construct the R-components chain - unexpected type of R-component.");
}

void ManagerComponents_R::checkComponentOuterState2(EndAdaptor_R* endAdaptor, int componentOuterState2Index) {
	FlowComponent_R* inputComponentOuterState2 = (FlowComponent_R*) Component_R_get(componentOuterState2Index);
	if (inputComponentOuterState2 != componentOuterState2) {
		RaiseComponentError(endAdaptor, "Could not construct R-components chain - there are two end R-components.");
	}
}

void ManagerComponents_R::constructComponentsChain() {
	if (isComponentsChainContructed) {
		RaiseError("Try to construct for the second time the R-components chain.");
	}

	if (outerState1->getMedium() != outerState2->getMedium()) {
		RaiseComponentError(beginAdaptor, "Different media connected to the R-components chain.");
	}

	if (componentOuterState1 == NULL) {
		RaiseComponentError(beginAdaptor, "The R-components chain is empty.")
	}

	// Create the internal begin state
	Medium* fluid = outerState1->getMedium();
	MediumState* state1 = MediumState_new(fluid);
	MediumState_register(state1);
	SMOOBJECT_SET_PARENT_COMPONENT(state1, beginAdaptor);
	state1->update_Tp(cst::StandardTemperature, cst::StandardPressure);

	// Start construction of the R-components chain
	FlowComponent_R* component = componentOuterState1;
	FlowComponent_R* prevComponent;
	do {
		component->init(state1);
		components.push_back(component);
		state1 = component->getState2();

		prevComponent = component;
		component = component->getComponent2();
	} while (component != NULL);
	componentOuterState2 = prevComponent;

	isComponentsChainContructed = true;
}

/**
 * Compute R-components chain
 */

void ManagerComponents_R::compute() {
	// Check - R-components chain is constructed
	if (!isComponentsChainContructed) {
		constructComponentsChain();
	}

	// Check - R-components chain is computed
	if (isComputed) {
		return;
	}

	// Compute the mass flow rate
	double massFlowRate = computeMassFlowRate();

	// Compute R-components when no mass flow rate
	if (cache_massFlowRate != cst::zeroMassFlowRate && massFlowRate == cst::zeroMassFlowRate) {
		for (int i = 0; i <  getNumComponents(); i++) {
			components[i]->compute_NoMassFlowRate();
		}
	}

	// Cache the mass flow rate
	cache_massFlowRate = massFlowRate;

	// Check for discontinuities
	handleEvent_FlowIsClosed();
	handleEvent_FlowDirectionIsChanged(massFlowRate);
	handleEvent_OpeningClosingPressureDifferenceIsCrossed();

	// Update flows of the all components
	updateFlows(massFlowRate);

	// Set isComputed flag
	isComputed = true;
}

double ManagerComponents_R::computeMassFlowRate() {
	// Get upstream and downstream (i.e. first and last component)
	MediumState* outerUpstreamState = outerState1;
	MediumState* outerDownstreamState = outerState2;
	FlowComponent_R* upstreamComponent = components.front();
	FlowComponent_R* downstreamComponent = components.back();
	bool reverseStream = false;

	if (outerState1->p() < outerState2->p()) { //reverse stream
		outerUpstreamState = outerState2;
		outerDownstreamState = outerState1;
		upstreamComponent = components.back();
		downstreamComponent = components.front();
		reverseStream = true;
	}

	// Initialize mass flow rate
	double massFlowRate;
	if (cache_massFlowRate == cst::zeroMassFlowRate) {
		massFlowRate = 0.001; //:TRICKY:
	} else {
		massFlowRate = m::fabs(cache_massFlowRate);
	}

	if (reverseStream) {
		massFlowRate = -massFlowRate;
	}

	// Use opening/closing pressure difference
	if (endAdaptor->isOpeningClosingPressureDifferenceUsed()) {
		double absOuterPressDrop = getAbsoluteOuterPressureDrop();
		isClosingPressDiffCrossed = absOuterPressDrop < endAdaptor->getClosingPressureDifference();
		isOpeningPressDiffCrossed = absOuterPressDrop > endAdaptor->getOpeningPressureDifference();

		if (SimEnv.isEventMode()) { //in a discontinuity
			if (absOuterPressDrop <= endAdaptor->getClosingPressureDifference()) {
				isFlowClosed_byPressDiff = true;
			}

			if (absOuterPressDrop >= endAdaptor->getOpeningPressureDifference()) {
				isFlowClosed_byPressDiff = false;
			}
		}

		if (isFlowClosed_byPressDiff) {
			isFlowClosed = true;
			return cst::zeroMassFlowRate;
		}
	}

	// Check - R-components chain is closed
	if (checkIsFlowClosed(massFlowRate)) {
		isFlowClosed = true;
		return cst::zeroMassFlowRate;
	}

	// Initialize
	double up_MassFlowRate = 0.0;
	bool up_MassFlowRate_isInit = false;
	double down_MassFlowRate = 0.0;
	bool down_MassFlowRate_isInit = false;

	double down_downstreamPressure = 0.0;
	double up_downstreamPressure = 0.0;
	bool up_downstreamPressure_isInit = false;

	upstreamComponent->getUpstreamState(massFlowRate)->update_Tp(outerUpstreamState->T(), outerUpstreamState->p());

	// Compute mass flow rate using iteration
	int numComponents = getNumComponents();

	double stepCoeff = 1.01; //:SMO_SETTINGS: the value 1.01 is the best for refueling of the CGH2DriveCycle
	if (cache_massFlowRate == cst::zeroMassFlowRate) { //no cache of the mass flow rate
		stepCoeff = 2.0;
	}

	static const int maxNumIter = 106; //:SMO_SETTINGS:
	static const double relTolerance = 1e-08; //:SMO_SETTINGS:

	double downstreamPressure = outerDownstreamState->p();
	double minDownstreamPressure = m::min(1.0*1e5, 0.1*downstreamPressure); //:TRICKY:
	int numIter;
	for (numIter = 1; numIter < maxNumIter; numIter++) {
		if (m::fabs(massFlowRate) < cst::MinMassFlowRate) {
			isFlowClosed = true;
			return cst::zeroMassFlowRate;
		}

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
				iterateStepCoeff(stepCoeff);
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
				iterateStepCoeff(stepCoeff);
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
				massFlowRate = (up_MassFlowRate + down_MassFlowRate) / 2.0;
			} else {
				massFlowRate *= stepCoeff;
				iterateStepCoeff(stepCoeff);
			}
		}
	}

	// Check
	if (numIter >= maxNumIter) {
		RaiseComponentError(upstreamComponent, "Computation of the mass flow rate in a R-components chain did not converge.");
	}

	isFlowClosed = false;
	return massFlowRate;
}

void ManagerComponents_R::iterateStepCoeff(double& stepCoeff) {
	if (stepCoeff < 2) {
		stepCoeff *= stepCoeff;
	}

	if (stepCoeff >= 2.0) {
		stepCoeff = 2.0;
	}
}

void ManagerComponents_R::updateFlows(double massFlowRate) {
	for (int i = 0; i < getNumComponents(); i++) {
		components[i]->updateFlows(massFlowRate);
	}
}

double ManagerComponents_R::getAbsoluteOuterPressureDrop() {
	return m::fabs(outerState1->p() - outerState2->p());
}

void ManagerComponents_R::handleEvent_FlowIsClosed() {
	if (discFlag_isFlowClosed_isInit == false) {
		discFlag_isFlowClosed = isFlowClosed;
		discFlag_isFlowClosed_isInit = true;
	}

	if (SimEnv.isEventMode()) { //in a discontinuity
		discFlag_isFlowClosed = isFlowClosed;
	}

	bool eventIndicator = false;
	if (isFlowClosed != discFlag_isFlowClosed) {
		eventIndicator = true;
	}

	if (eventIndicator) { //trigger a discontinuity
		SimEnv.updateEventIndicator(eventIndicator);
	}
}


bool ManagerComponents_R::checkIsFlowClosed(double massFlowRate) {
	if (getAbsoluteOuterPressureDrop() < cst::MinPressureDrop) {
		return true;
	}

	if (beginAdaptor->isFlowClosed(massFlowRate)) {
		return true;
	}

	if (endAdaptor->isFlowClosed(massFlowRate)) {
		return true;
	}

	for (int i = 0; i < getNumComponents(); i++) {
		if (components[i]->isFlowClosed(massFlowRate)) {
			return true;
		}
	}

	return false;
}

void ManagerComponents_R::handleEvent_FlowDirectionIsChanged(double massFlowRate) {
	bool isFlowDirectionChanged = massFlowRate < 0;
	if (discFlag_isFlowDirectionChanged_isInit == false) {
		discFlag_isFlowDirectionChanged = isFlowDirectionChanged;
		discFlag_isFlowDirectionChanged_isInit = true;
	}

	if (SimEnv.isEventMode()) { //in a discontinuity
		discFlag_isFlowDirectionChanged = isFlowDirectionChanged;
	}

	bool eventIndicator = false;
	if (isFlowDirectionChanged != discFlag_isFlowDirectionChanged) {
		eventIndicator = true;
	}

	if (eventIndicator) { //trigger a discontinuity
		SimEnv.updateEventIndicator(eventIndicator);
	}
}

void ManagerComponents_R::handleEvent_OpeningClosingPressureDifferenceIsCrossed() {
	if (!endAdaptor->isOpeningClosingPressureDifferenceUsed()) {
		return;
	}

	// Handle - Closing pressure difference
	if (isFlowClosed_byPressDiff == false) {
		if (discFlag_isClosingPressDiffCrossed_isInit == false) {
			discFlag_isClosingPressDiffCrossed = isClosingPressDiffCrossed;
			discFlag_isClosingPressDiffCrossed_isInit = true;
		}

		if (SimEnv.isEventMode()) { //in a discontinuity
			discFlag_isClosingPressDiffCrossed = isClosingPressDiffCrossed;
		}

		bool eventIndicator = false;
		if (isClosingPressDiffCrossed != discFlag_isClosingPressDiffCrossed) {
			eventIndicator = true;
		}

		if (eventIndicator) { //trigger a discontinuity
			SimEnv.updateEventIndicator(eventIndicator);
		}
	}

	// Handle - Opening pressure difference
	if (isFlowClosed_byPressDiff == true) {
		if (discFlag_isOpeningPressDiffCrossed_isInit == false) {
			discFlag_isOpeningPressDiffCrossed = isOpeningPressDiffCrossed;
			discFlag_isOpeningPressDiffCrossed_isInit = true;
		}

		if (SimEnv.isEventMode()) { //in a discontinuity
			discFlag_isOpeningPressDiffCrossed = isOpeningPressDiffCrossed;
		}

		bool eventIndicator = false;
		if (isOpeningPressDiffCrossed != discFlag_isOpeningPressDiffCrossed) {
			eventIndicator = true;
		}

		if (eventIndicator) { //trigger a discontinuity
			SimEnv.updateEventIndicator(eventIndicator);
		}
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



void ManagerComponents_R_addOuterState1(ManagerComponents_R* manager, BeginAdaptor_R* beginAdaptor, int state1Index) {
	manager->addOuterState1(beginAdaptor, state1Index);
}

void ManagerComponents_R_addOuterState2(ManagerComponents_R* manager, int componentIndex) {
	Component_R* inputComponent1 = Component_R_get(componentIndex);
	if (Component_R_isEndAdaptor(inputComponent1) == 1) {
		EndAdaptor_R* endAdaptor = (EndAdaptor_R*) inputComponent1;
		int outerStateIndex = Adaptor_R_getOuterStateIndex((Adaptor_R*)endAdaptor);
		manager->addOuterState2(endAdaptor, outerStateIndex);
	}
}

void ManagerComponents_R_addComponent(ManagerComponents_R* manager, FlowComponent_R* component, int prevComponentID) {
	manager->addComponent(component, prevComponentID);
}

void ManagerComponents_R_checkComponentOuterState2(ManagerComponents_R* manager, EndAdaptor_R* endAdaptor, int componentOuterState2Index) {
	manager->checkComponentOuterState2(endAdaptor, componentOuterState2Index);
}

int ManagerComponents_R_getFlow1Index(ManagerComponents_R* manager) {
	return manager->getFlow1Index();
}

int ManagerComponents_R_getFlow2Index(ManagerComponents_R* manager) {
	return manager->getFlow2Index();
}

void ManagerComponents_R_compute(ManagerComponents_R* manager) {
	manager->compute();
}

void ManagerComponents_R_clearIsComputed(ManagerComponents_R* manager) {
	manager->clearIsComputed();
}

int ManagerComponents_R_getIsFlowOpen(ManagerComponents_R* manager) {
	if (manager->isFlowOpen()){
		return 1;
	} else {
		return 0;
	}
}
