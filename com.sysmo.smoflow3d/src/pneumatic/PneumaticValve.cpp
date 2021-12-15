/*
 * PneumaticValve.cpp
 *
 *  Created on: Jul 28, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "PneumaticValve.h"
#include "math/MathDefinitions.h"
using namespace smoflow;

/**
 * PneumaticFlapperNozzleValve - C++
 */
PneumaticFlapperNozzleValve::PneumaticFlapperNozzleValve(
		FrictionFlowValve* friction,
		double diameterNozzle,
		double diameterRod,
		double diameterFlapper,
		double flapperLift0,
		double xForMinArea,
		double xForMaxArea) : Valve(friction) {
	this->diameterNozzle = diameterNozzle; //di
	this->diameterRod = diameterRod; //dr
	this->diameterFlapper = diameterFlapper; //df
	this->flapperLift0 = flapperLift0; //xlift0

	this->throatArea = m::pi * (diameterNozzle*diameterNozzle - diameterRod*diameterRod) /4.;
	this->minFlowArea = m::pi * diameterFlapper * xForMinArea;
	this->maxFlowArea = m::pi * diameterFlapper * xForMaxArea;

	setFlapperPosition(0); //flapperDisplacement = 0
}

PneumaticFlapperNozzleValve::~PneumaticFlapperNozzleValve() {
}

void PneumaticFlapperNozzleValve::setFlapperPosition(double flapperDisplacement) {
	// Compute the flapper lift
	flapperLift = flapperLift0 - flapperDisplacement;

	// Compute the flow area
	double flowArea = m::pi * diameterFlapper * flapperLift;

	// Restrict the flow area
	if (flowArea > throatArea ) {
		flowArea = throatArea;
	}

	if (flowArea > maxFlowArea) {
		flowArea = maxFlowArea;
	}

	if (flowArea < minFlowArea) {
		flowArea = minFlowArea;
	}

	// Set flow area
	friction->setFlowArea(flowArea);
}

double PneumaticFlapperNozzleValve::getFlapperLift() {
	return flapperLift;
}

double PneumaticFlapperNozzleValve::getFlowArea() {
	return friction->getFlowArea();
}

double PneumaticFlapperNozzleValve::getThroatArea() {
	return throatArea;
}

double PneumaticFlapperNozzleValve::getPressureForceOnFlapper() {
	double forceFlapperP1 = state1->p() * (m::pi/4.) * (diameterFlapper*diameterFlapper - diameterNozzle*diameterNozzle);
	double forceFlapperP2 = state2->p() * (m::pi/4.) * (diameterNozzle*diameterNozzle - diameterRod*diameterRod);
	return forceFlapperP1 + forceFlapperP2;
}


/**
 * PneumaticValve - C
 */
Valve* Valve_PneumaticFlapperNozzleValve_new(
		double diameterNozzle,
		double diameterRod,
		double diameterFlapper,
		double flapperLift0,
		double xForMinArea,
		double xForMaxArea,
		double flowCoefficient) {
	FrictionFlowValve* friction = FrictionFlowValve_OrificeCompressibleRealGas_new(
			1, //allowBidirectionalFlow = 1 - yes
			0, //orificeArea = 0
			flowCoefficient);

	return new PneumaticFlapperNozzleValve(
			friction,
			diameterNozzle,
			diameterRod,
			diameterFlapper,
			flapperLift0,
			xForMinArea,
			xForMaxArea);
}

void Valve_PneumaticFlapperNozzleValve_setFlapperPosition(
		PneumaticFlapperNozzleValve* valve,
		double flapperDisplacement) {
	valve->setFlapperPosition(flapperDisplacement);
}

double Valve_PneumaticFlapperNozzleValve_getPressureForceOnFlapper(PneumaticFlapperNozzleValve* valve) {
	return valve->getPressureForceOnFlapper();
}


double Valve_PneumaticFlapperNozzleValve_getFlapperLift(PneumaticFlapperNozzleValve* valve) {
	return valve->getFlapperLift();
}


double Valve_PneumaticFlapperNozzleValve_getFlowArea(PneumaticFlapperNozzleValve* valve) {
	return valve->getFlowArea();
}

double Valve_PneumaticFlapperNozzleValve_getThroatArea(PneumaticFlapperNozzleValve* valve) {
	return valve->getThroatArea();
}

