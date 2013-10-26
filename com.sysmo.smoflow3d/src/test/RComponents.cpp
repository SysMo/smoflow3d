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

/**
 * Util functions
 */
void displayState (MediumState* fp1) {
	std::cout << "T = " << MediumState_T(fp1)
			<< ", p = " << MediumState_p(fp1)
			<< ", rho = " << MediumState_rho(fp1)
			<< ", h = " << MediumState_h(fp1)
			<< std::endl;
}

void testMedium() {
	Medium* fluid = Medium_get(1);
	MediumState* fp1 = MediumState_new(fluid);
	fp1->update_Tp(300, 10e5);
	displayState(fp1);
}


/**
 * Initialize
 */
void initMediums() {
	const char* fluidName = "ParaHydrogen";
	Medium_register(sCompressibleFluidCoolProp, fluidName, 1);
}


/**
 * Test R components
 */
void testRComponents() {
	// Create inlet and outlet states of the RComponents chain
	Medium* fluid = Medium_get(1);
	MediumState* state1 = MediumState_new(fluid);
	state1->update_Tp(60, 300e5);

	MediumState* state2 = MediumState_new(fluid);
	state2->update_Tp(288.15, 1e5);

	// Create pipes and valves

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
