/*
 * MediumStateSolid.cpp
 *
 *  Created on: Aug 5, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "MediumStateSolid.h"

MediumStateSolid::MediumStateSolid(Medium_Solid* medium) : MediumState (medium) {
	this->solid = medium;
	densityCache = medium->densityFunction->createCache();
	heatCapacityCache = medium->heatCapacityFunction->createCache();
	thermalConductivityCache = medium->thermalConductivityFunction->createCache();
	enthalpyCache = medium->enthalpyFunction->createCache();
}

MediumStateSolid::~MediumStateSolid() {
}

void MediumStateSolid::update_Tp(double T, double p) {
	clearPropertyCache();
	_p = p;
	_T = T;
	_rho = (*solid->densityFunction)(_T, densityCache);
	_h = (*solid->enthalpyFunction)(_T, enthalpyCache);
}

double MediumStateSolid::cp() {
	if (!_cp) {
		_cp = (*solid->heatCapacityFunction)(_T, heatCapacityCache);
	}
	return _cp;
}

double MediumStateSolid::lambda() {
	if (!_lambda) {
		_lambda = (*solid->thermalConductivityFunction)(_T, thermalConductivityCache);
	}
	return _lambda;
}

MediumStateSolid* MediumStateSolid_new(Medium_Solid* medium) {
	return new MediumStateSolid(medium);
}
