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
#include "media/MediaRegistry.h"
#include "util/CodeTiming.h"

void displayTimingResult(int counter, double duration) {
	std::cout << "Number fluid property calculations: " << counter << std::endl;
	std::cout << "Duration: " << duration << " ms = " << duration/1000 << " s" << std::endl;
	std::cout << "Time per calculation: " << duration / counter << " ms" << std::endl;
}

void displayState (MediumState* fp1) {
	std::cout << "T = " << mstate_T(fp1)
			<< ", p = " << mstate_p(fp1)
			<< ", rho = " << mstate_rho(fp1)
			<< ", h = " << mstate_h(fp1)
			<< std::endl;
}

void testCoolPropCalculationTiming() {
	int updateCounter ;
	Timer* timer1 = createTimer();
	MediumState* fp1 = mstate_get(mstate_register(create_mstate(1)));
	MediumState* fp2 = mstate_get(mstate_register(create_mstate(1)));;
	MediumState* fp3 = mstate_get(mstate_register(create_mstate(1)));;


	// Time T, p calculation
	std::cout << "Calcupation based on (T,p)" << std::endl;
	updateCounter = 0;
	timer_start(timer1);
	for (double p = 20e5; p <= 700e5; p+=1e5) {
		for (double T = 40; T <= 300; T+= 1) {
			mstate_update_Tp(fp1, T, p);
			//displayState(fp1);
			updateCounter += 1;
		}
	}
	timer_stop(timer1);
	displayTimingResult(updateCounter, timer_read(timer1));
	timer_reset(timer1);


	// Time T, rho calculation
	std::cout << "Calcupation based on (T,rho)" << std::endl;
	updateCounter = 0;
	timer_start(timer1);
	for (double rho = 0.1; rho <= 40; rho+= 0.1) {
		for (double T = 40; T <= 300; T+= 1) {
			mstate_update_Trho(fp2, T, rho);
			//displayState(fp1);
			updateCounter += 1;
		}
	}
	timer_stop(timer1);
	displayTimingResult(updateCounter, timer_read(timer1));
	timer_reset(timer1);


	// Time p, h calculation
	std::cout << "Calcupation based on (p,h)" << std::endl;
	updateCounter = 0;
	timer_start(timer1);
	for (double p = 20e5; p <= 700e5; p+= 1e5) {
		for (double h = 1.5e6; h <= 4e6; h+= 1e4) {
			mstate_update_ph(fp3, p, h);
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
	register_medium(fluidName, 1);
	testCoolPropCalculationTiming();

	return 0;
}
