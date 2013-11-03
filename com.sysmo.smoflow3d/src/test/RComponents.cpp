/*
 * RComponents.cpp
 *
 *  Created on: Sep 19, 2014
 *      Author: Milen Borisov
 *	 Copyright: SysMo Ltd., Bulgaria
 */
#include <string>
#include <iostream>
#include "media/MediumState.h"
#include "flow_R/Pipe_R.h"
#include "flow_R/Valve_R.h"

using namespace smoflow;

/**
 * Test functions
 */
void displayState (MediumState* fp1) {
	std::cout << "T = " << MediumState_T(fp1)
			<< ", p = " << MediumState_p(fp1)
			<< ", rho = " << MediumState_rho(fp1)
			<< ", h = " << MediumState_h(fp1);
}

void testMedium() {
	Medium* fluid = Medium_get(1);
	MediumState* fp1 = MediumState_new(fluid);
	fp1->update_Tp(300, 10e5);
	displayState(fp1);
}

/**
 * Util functions
 */
void initMediums() {
	const char* fluidName = "ParaHydrogen";
	Medium_register(sCompressibleFluidCoolProp, fluidName, 1);
}


/**
 * Test R components
 */
void testComputeMassFlowRate(
		MediumState* mainState1,
		MediumState* mainState2,
		std::vector<Component_R*>& components) {
	// Get fluid
	Medium* fluid = mainState1->getMedium();

	// Create and set virtual states of the components
	int numComponents = (int) components.size();
	MediumState* virtualState1 = MediumState_new(fluid);
	for (int i = 0; i < numComponents; i++) {
		MediumState* virtualState2 = MediumState_new(fluid);
		components[i]->init(virtualState1, virtualState2);
		virtualState1 = virtualState2;
	}

	// Get upstream and downstream components
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
	double massFlowRate = 0.001;
	if (reverseStream) {
		massFlowRate = -massFlowRate;
	}

	// Check - is the components chain open
	for (int i = 0; i < numComponents; i++) {
		if (components[i]->isFlowClosed(massFlowRate)) {
			std::cout << std::endl;
			std::cout << "state1 = "; displayState(mainState1); std::cout << std::endl;
			std::cout << "state2 = "; displayState(mainState2); std::cout << std::endl;
			std::cout << std::endl;
			std::cout << "The flow is closed!" << std::endl;
			std::cout << "mass flow rate (state1->state2) = " << 0.0 << " [kg/s]" << std::endl;
			return;
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
	static const int maxNumIter = 100;
	static const double relTolerance = 1e-08;

	double downstreamPressure = mainDownstreamState->p();
	double minDownstreamPressure = m::max(1e-5, downstreamPressure - 1e5); // m::min(1.0*1e5, 0.5*downstreamPressure); //:TODO: (???)
	std::cout << "numIter, massFlowRate, calcDownstreamPressure, relError, down_MassFlowRate, up_MassFlowRate" << std::endl;
	for (int numIter = 1; numIter < maxNumIter; numIter++) {
		double tmpMDot = massFlowRate;
		bool succ;
		std::cout << "Downstream pressures, temperature = ";
		for (int i = 0; i < numComponents; i++) {
			int componentIndex = (reverseStream) ? numComponents - i - 1 : i;
			succ = components[componentIndex]->compute(massFlowRate, minDownstreamPressure);
			if (!succ) {
				break;
			}
			std::cout << "(" << components[componentIndex]->getDownstreamState(massFlowRate)->p() << ", " << components[componentIndex]->getDownstreamState(massFlowRate)->T() << "), " ;
		}
		std::cout << std::endl;

		if (!succ) {
			up_MassFlowRate = massFlowRate; //:TODO: check that massFlowRate < up_MassFlowRate
			up_MassFlowRate_isInit = true;
			if (down_MassFlowRate_isInit) {
				massFlowRate = (up_MassFlowRate + down_MassFlowRate) / 2.0;
			} else {
				massFlowRate /= stepCoeff;
			}
			std::cout << "UP1: " << numIter << ", " << tmpMDot << ", " << 0.0 << ", " << 1.0 << ", " << down_MassFlowRate << ", " << up_MassFlowRate << std::endl;
			continue;
		}


		double calcDownstreamPressure = downstreamComponent->getDownstreamState(massFlowRate)->p();
		double relError = (calcDownstreamPressure - downstreamPressure) / downstreamPressure;
		if (m::fabs(relError) < relTolerance) {
			std::cout << "END: " << numIter << ", " << tmpMDot << ", " << calcDownstreamPressure << ", " << relError << ", " << down_MassFlowRate << ", " << up_MassFlowRate << std::endl;
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
			std::cout << "UP0: " << numIter << ", " << tmpMDot << ", " << calcDownstreamPressure << ", " << relError << ", " << down_MassFlowRate << ", " << up_MassFlowRate << std::endl;
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
			std::cout << "DN0: " << numIter << ", " << tmpMDot << ", " << calcDownstreamPressure << ", " << relError << ", " << down_MassFlowRate << ", " << up_MassFlowRate << std::endl;
		}
	}


	// Update fluid flows
	for (int i = 0; i < numComponents; i++) {
		components[i]->updateFlows(massFlowRate);
	}

	std::cout << std::endl;
	std::cout << "state1 = "; displayState(mainState1); std::cout << std::endl;
	std::cout << "state2 = "; displayState(mainState2); std::cout << std::endl;
	std::cout << "mass flow rate (state1->state2) = " << massFlowRate << " [kg/s]" << std::endl;
}

void testRComponents() {
	// Create inlet and outlet states of the RComponents chain
	Medium* fluid = Medium_get(1);
	MediumState* mainState1 = MediumState_new(fluid);
	MediumState* mainState2 = MediumState_new(fluid);

	mainState1->update_Tp( 60, 300e5); //[K], [Pa]
	mainState2->update_Tp(300,   1e5); //[K], [Pa]

	// Create pipes and valves
	Pipe_R* pipe1 = StraightPipe_R_new(
			5*1e-3, 	//diameter [m]
			0.5,   		//length [m]
			0.025*1e-3, //surfaceRoughness [m]
			1.0			//pressureDropGain
	);

	Pipe_R* pipe2 = StraightPipe_R_new(
			5*1e-3, 	//diameter [m]
			0.5,   		//length [m]
			0.025*1e-3, //surfaceRoughness [m]
			1.0			//pressureDropGain
	);

	Valve_R* valve1 = ValveKv_R_new(
			1,			// allowBidirectionalFlow: 0 - no; 1 - yes
			1.0, 		// Kv
			1, 			// transitionChoice;
			0.0001, 	// transitionMassFlowRate;
			0.001*1e5 	// transitionPressureDifference
	);
	valve1->setRegulatingSignal(1.0);

	Valve_R* valve2 = ValveKv_R_new(
			1,			// allowBidirectionalFlow: 0 - no; 1 - yes
			1.0, 		// Kv
			1, 			// transitionChoice;
			0.0001, 	// transitionMassFlowRate;
			0.001*1e5 	// transitionPressureDifference
	);
	valve2->setRegulatingSignal(1.0);

	Pipe_R* pipeHE1 = StraightPipeHeatExchanger_R_new(
			5*1e-3, 	//diameter [m]
			0.5,   		//length [m]
			0.025*1e-3, //surfaceRoughness [m]
			1.0,		//pressureDropGain
			1.0, 		//heatExchangeGain
			false		//heatExchangerLimitOutput
	);

	ThermalNode* thermalNode1 = ThermalNode_new(sThermalNode_Source);
	thermalNode1->setTemperature(300);
	pipeHE1->setHeatExchangerThermalNode(thermalNode1);

	Pipe_R* pipeHE2 = StraightPipeHeatExchanger_R_new(
			5*1e-3, 	//diameter [m]
			0.5,   		//length [m]
			0.025*1e-3, //surfaceRoughness [m]
			1.0,		//pressureDropGain
			1.0, 		//heatExchangeGain
			false		//heatExchangerLimitOutput
	);

	ThermalNode* thermalNode2 = ThermalNode_new(sThermalNode_Source);
	thermalNode2->setTemperature(300);
	pipeHE2->setHeatExchangerThermalNode(thermalNode1);


	// Create components vector
	std::vector<Component_R*> components;
	//components.push_back(pipe1);
	//components.push_back(pipe2);
	components.push_back(valve1);
	components.push_back(valve2);


	// Compute mass flow rate
	testComputeMassFlowRate(mainState1, mainState2, components);
}


/**
 * Main functions
 */
int main(int argc, char** argv) {
	initMediums();
	//testMedium();
	testRComponents();

	return 0;
}
