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
}

MediumStateSolid::~MediumStateSolid() {
	// TODO Auto-generated destructor stub
}

void MediumStateSolid::update_Tp(double T, double p) {
	clearPropertyCache();
	_p = p;
	_T = T;
	_rho = (*solid->densityFunction)(_T);
	_h = 0;
}

double MediumStateSolid::cp() {
	if (!_cp) {
		_cp = (*solid->heatCapacityFunction)(_T);
	}
	return _cp;
}

double MediumStateSolid::lambda() {
	if (!_lambda) {
		_lambda = (*solid->thermalConductivityFunction)(_T);
	}
	return _lambda;
}

MediumStateSolid* MediumStateSolid_new(Medium_Solid* medium) {
	return new MediumStateSolid(medium);
}
