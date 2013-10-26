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

Pipe_R* createStraightPipe(double diameter, double length, double surfaceRoughness) {
	FrictionFlowPipe* friction = FrictionFlowPipe_StraightPipe_new(diameter, length, surfaceRoughness);
	friction->setPressureDropGain(1.0); //???
	return Pipe_R_new(friction);
}


/**
 * Test R components
 */


void testRComponents() {
	// Create inlet and outlet states of the RComponents chain
	Medium* fluid = Medium_get(1);
	MediumState* mainState1 = MediumState_new(fluid);
	MediumState* mainState2 = MediumState_new(fluid);

	mainState1->update_Tp(60, 300e5); //[K], [Pa]
	mainState2->update_Tp(300, 10e5);


	// Create pipes
	Pipe_R* pipe1 = createStraightPipe(
					0.005, //diameter [m]
					0.5,   //length [m]
					0.025  //surfaceRoughness
	);

	Pipe_R* pipe2 = createStraightPipe(
					0.005, //diameter [m]
					0.5,   //length [m]
					0.025  //surfaceRoughness
	);

	// Create components vector
	std::vector<Component_R*> components;
	components.push_back(pipe1);
	components.push_back(pipe2);
	int numComponents = (int) components.size();

	// Create and set virtual states of the components
	MediumState* state1 = MediumState_new(fluid);;
	for (int i = 0; i < numComponents; i++) {
		MediumState* state2 = MediumState_new(fluid);
		components[i]->init(state1, state2);
		state1 = state2;
	}



	// Get first and last components
	MediumState* mainUpstreamState = mainState1;
	MediumState* mainDownstreamState = mainState2;
	Component_R* firstComponent = components.front();
	Component_R* lastComponent = components.back();
	bool reverseStream = false;

	if (mainState1->p() < mainState2->p()) { //reverse stream
		mainUpstreamState = mainState2;
		mainDownstreamState = mainState1;
		firstComponent = components.back();
		lastComponent = components.front();
		reverseStream = true;
	}

	// Initialize
	double up_MassFlowRate = 0.0;
	bool up_MassFlowRate_isInit = false;
	double down_MassFlowRate = 0.0;
	bool down_MassFlowRate_isInit = false;
	double massFlowRate = 0.001;
	if (reverseStream) {
		massFlowRate = -massFlowRate;
	}

	double down_downstreamPressure = 0.0;
	double up_downstreamPressure = 0.0;
	bool up_downstreamPressure_isInit = false;

	firstComponent->getUpstreamState(massFlowRate)->update_Tp(mainUpstreamState->T(), mainUpstreamState->p());

	// Compute mass flow rate using iteration
	double stepCoeff = 2.0;
	static const int maxNumIter = 100;
	static const double relTolerance = 1e-08;

	double downstreamPressure = mainDownstreamState->p();
	double minDownstreamPressure = m::max(1e-5, downstreamPressure - 1e5); // m::min(1.0*1e5, 0.5*downstreamPressure); //:TODO: (???)
	std::cout << "numIter, massFlowRate, calcDownstreamPressure, relError, down_MassFlowRate, up_MassFlowRate" << std::endl;
	for (int numIter = 1; numIter < maxNumIter; numIter++) {
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
			std::cout << "UP1: " << numIter << ", " << massFlowRate << ", " << 0.0 << ", " << 1.0 << ", " << down_MassFlowRate << ", " << up_MassFlowRate << std::endl;
			continue;
		}


		double calcDownstreamPressure = lastComponent->getDownstreamState(massFlowRate)->p();
		double relError = (calcDownstreamPressure - downstreamPressure) / downstreamPressure;
		if (m::fabs(relError) < relTolerance) {
			std::cout << "END: " << numIter << ", " << massFlowRate << ", " << calcDownstreamPressure << ", " << relError << ", " << down_MassFlowRate << ", " << up_MassFlowRate << std::endl;
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
			std::cout << "UP0: " << numIter << ", " << massFlowRate << ", " << calcDownstreamPressure << ", " << relError << ", " << down_MassFlowRate << ", " << up_MassFlowRate << std::endl;
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
			std::cout << "DN0: " << numIter << ", " << massFlowRate << ", " << calcDownstreamPressure << ", " << relError << ", " << down_MassFlowRate << ", " << up_MassFlowRate << std::endl;
		}
	}

	std::cout << std::endl;
	std::cout << "state1 = "; displayState(mainState1); std::cout << std::endl;
	std::cout << "state2 = "; displayState(mainState2); std::cout << std::endl;
	std::cout << "mass flow rate (state1->state2) = " << massFlowRate << " [kg/s]" << std::endl;
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
