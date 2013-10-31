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

void testCoolProp() {
	Medium* fluid = Medium_get(1);
	MediumState* fp1 = MediumState_new(fluid);
	MediumState* fp2 = MediumState_new(fluid);

	MediumState_update_Tp(fp1, 288.15, 1e5);
	std::cout << "entalpy = " << MediumState_h(fp1) << std::endl;

	MediumState_update_Trho(fp2, 29.765734268475395, 0.84329344123579586);
	std::cout << "entalpy = " << MediumState_h(fp2) << std::endl;

	MediumState_update_ph(fp2, 1e5, fp1->h());
	std::cout << "entalpy = " << MediumState_h(fp1) << std::endl;
}

void testCriticalPoint() {
	Medium* fluid = Medium_get(1);
	MediumState* fp1 = MediumState_new(fluid);

	fp1->update_Trho(32.798321531316866, 38.007425381953652);
	double gamma = fp1->gamma();
	double Pr = fp1->Pr();
	std::cout << gamma << std::endl;
	std::cout << Pr << std::endl;

}

void testTwoPhase() {
	Medium* fluid = Medium_get(1);
	MediumState* fp1 = MediumState_new(fluid);
	fp1->update_pq(10.34736e5, 0.7503882);
	std::cout << "T = " << fp1->T() << std::endl;
	std::cout << "cv = " << fp1->cv() << std::endl;
	std::cout << "dp_dT_rho = " << fp1->dpdt_v() << std::endl;
	std::cout << "dp_drho_T = " << fp1->dpdrho_t() << std::endl;

}

void test_updateprho() {
	Medium* fluid = Medium_get(1);
	MediumState* fp1 = MediumState_new(fluid);
	fp1->update_prho(206584, 2.57367);
	std::cout << "T = " << fp1->T() << std::endl;
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
	const char* fluidName = "ParaHydrogen";
	Medium_register(sCompressibleFluidCoolProp, fluidName, 1);
	//testCoolPropCalculationTiming();
	//testCoolProp();
	//testCriticalPoint();
	//testTwoPhase();
	test_updateprho();
	//std::cout << "eps(double) = " << std::numeric_limits<double>::epsilon() << std::endl;
	//std::cout << "eps(float) = " << std::numeric_limits<float>::epsilon() << std::endl;
	return 0;
}
