/*
 * PneumaticPiston.cpp
 *
 *  Created on: Dec 15, 2021
 *      Author: Milen Borisov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "PneumaticPiston.h"
#include "math/MathDefinitions.h"
using namespace smoflow;

/**
 * PneumaticFlapperNozzleValve - C++
 */
PneumaticPiston::PneumaticPiston(double diameterPistion, double diameterRod) {
	this->diameterPiston = diameterPistion; //dp
	this->diameterRod = diameterRod; //dr

	this->pistonArea = m::pi * (diameterPiston*diameterPiston - diameterRod*diameterRod)/4.;

	this->state1 = NULL;
}

PneumaticPiston::~PneumaticPiston() {
}

void PneumaticPiston::init(MediumState* state1) {
	this->state1 = state1;
}

double PneumaticPiston::getPressureForceOnPiston() {
	return state1->p() * getPistonArea();
}

double PneumaticPiston::getPistonArea() {
	return pistonArea;
}

/**
 * PneumaticValve - C
 */
PneumaticPiston* PneumaticPiston_new(double diameterPiston, double diameterRod) {
	return new PneumaticPiston(diameterPiston, diameterRod);
}

void PneumaticPiston_init(PneumaticPiston* piston, MediumState* state1) {
	piston->init(state1);
}

double PneumaticPiston_getPressureForceOnPiston(PneumaticPiston* piston) {
	return piston->getPressureForceOnPiston();
}

double PneumaticPiston_getPistonArea(PneumaticPiston* piston) {
	return piston->getPistonArea();
}
