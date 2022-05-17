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
PneumaticPiston::PneumaticPiston(double diameterPistion, double diameterRod, double x0) {
	this->diameterPiston = diameterPistion; //dp
	this->diameterRod = diameterRod; //dr
	this->x0 = x0; //chamber length at zero displacement

	this->state1 = NULL;

	this->pistonArea = m::pi * (diameterPiston*diameterPiston - diameterRod*diameterRod)/4.;
	this->length = x0;
	this->volume = length*pistonArea;
	this->volumeDot = 0;
}

PneumaticPiston::~PneumaticPiston() {
}

void PneumaticPiston::init(MediumState* state1) {
	this->state1 = state1;
}

void PneumaticPiston::compute(
		double x, //displacement of the piston
		double v) { //velocity of the piston
	length = x0 - x;
	volume = length*pistonArea;
	volumeDot = -v*pistonArea;
}

double PneumaticPiston::getPressureForceOnPiston() {
	return state1->p() * getPistonArea();
}

double PneumaticPiston::getPistonArea() {
	return pistonArea;
}

double PneumaticPiston::getLength() {
	return length;
}

double PneumaticPiston::getVolume() {
	return volume;
}

double PneumaticPiston::getVolumeDot() {
	return volumeDot;
}

/**
 * PneumaticValve - C
 */
PneumaticPiston* PneumaticPiston_new(double diameterPiston, double diameterRod, double x0) {
	return new PneumaticPiston(diameterPiston, diameterRod, x0);
}

void PneumaticPiston_init(PneumaticPiston* piston, MediumState* state1) {
	piston->init(state1);
}

void PneumaticPiston_compute(PneumaticPiston* piston, double x, double v) {
	piston->compute(x, v);
}

double PneumaticPiston_getPressureForceOnPiston(PneumaticPiston* piston) {
	return piston->getPressureForceOnPiston();
}

double PneumaticPiston_getPistonArea(PneumaticPiston* piston) {
	return piston->getPistonArea();
}

double PneumaticPiston_getLength(PneumaticPiston* piston) {
	return piston->getLength();
}

double PneumaticPiston_getVolume(PneumaticPiston* piston) {
	return piston->getVolume();
}

double PneumaticPiston_getVolumeDot(PneumaticPiston* piston) {
	return piston->getVolumeDot();
}
