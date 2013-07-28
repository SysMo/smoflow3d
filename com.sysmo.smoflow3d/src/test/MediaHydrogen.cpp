/*
 * MediaHydrogen.cpp
 *
 *  Created on: Jul 22, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */
#include <string>
#include <iostream>
#include "media/MediumState.h"
#include "media/Medium.h"
#include "util/CodeTiming.h"

void displayTimingResult(int counter, double duration) {
	std::cout << "Number fluid property calculations: " << counter << std::endl;
	std::cout << "Duration: " << duration << " ms = " << duration/1000 << " s" << std::endl;
	std::cout << "Time per calculation: " << duration / counter << " ms" << std::endl;
}

void displayState (MediumState* fp1) {
	std::cout << "T = " << MediumState_T(fp1)
			<< ", p = " << MediumState_p(fp1)
			<< ", rho = " << MediumState_rho(fp1)
			<< ", h = " << MediumState_h(fp1)
			<< std::endl;
}

void testCoolPropCalculationTiming() {
	int updateCounter ;
	Timer* timer1 = createTimer();
	Medium* fluid = Medium_get(1);
	MediumState* fp1 = MediumState_new(fluid);
	MediumState_register(fp1);
	MediumState* fp2 = MediumState_new(fluid);
	MediumState_register(fp2);
	MediumState* fp3 = MediumState_new(fluid);
	MediumState_register(fp3);


	// Time T, p calculation
	std::cout << "Calculation based on (T,p)" << std::endl;
	updateCounter = 0;
	timer_start(timer1);
	for (double p = 20e5; p <= 700e5; p+=1e5) {
		for (double T = 40; T <= 300; T+= 1) {
			MediumState_update_Tp(fp1, T, p);
			//displayState(fp1);
			updateCounter += 1;
		}
	}
	timer_stop(timer1);
	displayTimingResult(updateCounter, timer_read(timer1));
	timer_reset(timer1);


	// Time T, rho calculation
	std::cout << "Calculation based on (T,rho)" << std::endl;
	updateCounter = 0;
	timer_start(timer1);
	for (double rho = 0.1; rho <= 40; rho+= 0.1) {
		for (double T = 40; T <= 300; T+= 1) {
			MediumState_update_Trho(fp2, T, rho);
			//displayState(fp1);
			updateCounter += 1;
		}
	}
	timer_stop(timer1);
	displayTimingResult(updateCounter, timer_read(timer1));
	timer_reset(timer1);


	// Time p, h calculation
	std::cout << "Calculation based on (p,h)" << std::endl;
	updateCounter = 0;
	timer_start(timer1);
	for (double p = 20e5; p <= 700e5; p+= 1e5) {
		for (double h = 1.5e6; h <= 4e6; h+= 1e4) {
			MediumState_update_ph(fp3, p, h);
			//displayState(fp1);
			updateCounter += 1;
		}
	}
	timer_stop(timer1);
	displayTimingResult(updateCounter, timer_read(timer1));
	timer_reset(timer1);

	delete timer1;
	delete fp1;
	delete fp2;
	delete fp3;

}

int main(int argc, char** argv) {
	const char* fluidName = "parahydrogen";
	Medium_register(sCompressibleFluidCoolProp, fluidName, 1);
	testCoolPropCalculationTiming();

	return 0;
}
