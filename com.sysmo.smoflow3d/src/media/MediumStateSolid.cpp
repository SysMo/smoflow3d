/*
 * MediumStateSolid.cpp
 *
 *  Created on: Aug 5, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "MediumStateSolid.h"

MediumState_Solid::MediumState_Solid(Medium_Solid* medium) : MediumState (medium) {
	this->solid = medium;
	densityCache = medium->densityFunction->createCache();
	heatCapacityCache = medium->heatCapacityFunction->createCache();
	thermalConductivityCache = medium->thermalConductivityFunction->createCache();
}

MediumState_Solid::~MediumState_Solid() {
	// TODO Auto-generated destructor stub
}

void MediumState_Solid::update_Tp(double T, double p) {
	clearPropertyCache();
	_p = p;
	_T = T;
	_rho = (*solid->densityFunction)(_T, densityCache);
	_h = 0;
}

double MediumState_Solid::u() {
	return _h;
}

double MediumState_Solid::cp() {
	if (!_cp) {
		_cp = (*solid->heatCapacityFunction)(_T, heatCapacityCache);
	}
	return _cp;
}

double MediumState_Solid::lambda() {
	if (!_lambda) {
		_lambda = (*solid->thermalConductivityFunction)(_T, thermalConductivityCache);
	}
	return _lambda;
}

double MediumState_Solid::mu() {
	return _HUGE;
}

MediumState_Solid* MediumStateSolid_new(Medium_Solid* medium) {
	return new MediumState_Solid(medium);
}
