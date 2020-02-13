/*
 * Radiation.cpp
 *
 *  Created on: Oct 26, 2016
 *      Author: Atanas Pavlov, Milen Borisov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "Radiation.h"

/**
 * Radiation - C++
 */
Radiation::Radiation() {
	heatExchangeGain = 1.0;
	heatFlowRate = 0.0;
}

Radiation::~Radiation() {
}

/**
 * Radiation - C
 */
void Radiation_setHeatExchangeGain(Radiation* radiation, double gain) {
	radiation->setHeatExchangeGain(gain);
}

double Radiation_getHeatFlowRate(Radiation* radiation) {
	return radiation->getHeatFlowRate();
}
