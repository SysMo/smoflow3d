/*
 * PneumaticFlapperValve.cpp
 *
 *  Created on: 20 Dec 2021
 *      Author: Milen Borisov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "math/MathDefinitions.h"
#include "PneumaticFlapperValve.h"
using namespace smoflow;


/**
 * PneumaticFlapperValve - C++
 */
PneumaticFlapperValve::PneumaticFlapperValve(
		FrictionFlowValve* friction,
		double flapperLift0,
		double xForMinArea,
		double xForMaxArea) : Valve(friction) {
	this->flapperLift0 = flapperLift0; //xlift0
	this->xForMinArea = xForMinArea;
	this->xForMaxArea = xForMaxArea;

	this->flapperLift = 0;
	this->throatArea = 0;
	this->minFlowArea = 0;
	this->maxFlowArea = 0;
}

PneumaticFlapperValve::~PneumaticFlapperValve() {
}

void PneumaticFlapperValve::setFlapperPosition(double flapperDisplacement) {
	// Compute the flapper lift
	flapperLift = flapperLift0 - flapperDisplacement;

	// Get the current flow area
	double flowArea = calcFlowArea(flapperLift);

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

double PneumaticFlapperValve::getFlapperLift() {
	return flapperLift;
}

double PneumaticFlapperValve::getFlowArea() {
	return friction->getFlowArea();
}

double PneumaticFlapperValve::getThroatArea() {
	return throatArea;
}

void PneumaticFlapperValve::updateVolumes(double v4, double x4, FluidFlow* flow1, FluidFlow* flow2) {
	flow1->volume = 0.0;
	flow1->volumeDot = 0.0;

	flow2->volume = 0.0;
	flow2->volumeDot = 0.0;
}


/**
 * PneumaticFlatFlapperNozzleValve - C++
 */
class PneumaticFlatFlapperNozzleValve : public PneumaticFlapperValve {
public:
	PneumaticFlatFlapperNozzleValve(
			FrictionFlowValve* friction,
			double nozzleDiameter,
			double rodDiameter,
			double flapperDiameter,
			double flapperLift0,
			double xForMinArea,
			double xForMaxArea,
			int forceMode,
			int forceContact,
			double xLim,
			double vol10,
			double vol20) :
				PneumaticFlapperValve(friction, flapperLift0, xForMinArea, xForMaxArea) {
		this->nozzleDiameter = nozzleDiameter;
		this->rodDiameter = rodDiameter;
		this->flapperDiameter = flapperDiameter;

		this->forceMode = forceMode;
		this->forceContact = forceContact;
		this->xLim = xLim;

		this->vol10 = vol10;
		this->vol20 = vol20;

		initAreas();
		setFlapperPosition(0); //flapperDisplacement = 0
	}

	virtual double getPressureForceOnFlapper() {
		double forceOnFlapperSeat = 0;
		if (forceMode == 1) {//force calculation mode: 1-constant
			forceOnFlapperSeat = state1->p() * (m::pi/4.) * (flapperDiameter*flapperDiameter - nozzleDiameter*nozzleDiameter);
		} else { // 2 - gradient
			double p1 = state1->p();
			double p2 = state2->p();
			forceOnFlapperSeat = (m::pi/12.) * (flapperDiameter - nozzleDiameter) *
					(flapperDiameter*(2*p1 + p2) + nozzleDiameter*(p1 + 2*p2));
		}

		double forceP2 = state2->p() * (m::pi/4.) * (nozzleDiameter*nozzleDiameter - rodDiameter*rodDiameter);

		// Case-1: pressure force contributes on the flapper seat at zero lift
		if (forceContact == 1) { //1-Yes
			return forceOnFlapperSeat + forceP2;
		}

		// Case-2: pressure force doesn't contribute on the flapper seat at zero lift (i.e. forceOnFlapperSeat = 0 at flapperLift = 0)
		if (flapperLift == 0) {
			double zeroForceOnFlapperSeat = 0;
			return zeroForceOnFlapperSeat + forceP2;
		}

		//   Case-2.1: no transition opening for pressure force on the flapper seat
		if (xLim == 0.0) {
			return forceOnFlapperSeat + forceP2;
		}

		//   Case-2.1: With transition opening for pressure force on the flapper seat
		double forceOnFlapperSeatSmooth = m::polysmooth(flapperLift, 0, xLim, 0, forceOnFlapperSeat);
		return forceOnFlapperSeatSmooth + forceP2;
	}

	virtual void updateVolumes(double v4, double x4, FluidFlow* flow1, FluidFlow* flow2) {
		// Compute the flapper lift
		double xLift = flapperLift0 - x4;

		double area1 = (flapperDiameter*flapperDiameter - nozzleDiameter*nozzleDiameter)/4.;
		double area2 = (nozzleDiameter*nozzleDiameter - rodDiameter*rodDiameter)/4.;
		double vol1 = vol10 + xLift * m::pi * area1;
		double vol2 = vol20 + xLift * m::pi * area2;

		double volDot1 = -v4 * m::pi * area1;
		double volDot2 = -v4 * m::pi * area2;

		flow1->volume = vol1;
		flow1->volumeDot = volDot1;

		flow2->volume = vol2;
		flow2->volumeDot = volDot2;
	}

protected:

	virtual void initAreas() {
		this->throatArea = m::pi * (nozzleDiameter*nozzleDiameter - rodDiameter*rodDiameter) /4.;
		this->minFlowArea = m::pi * nozzleDiameter * xForMinArea;
		this->maxFlowArea = m::pi * nozzleDiameter * xForMaxArea;
	}

	virtual double calcFlowArea(double flapperLift) {
		return m::pi * nozzleDiameter * flapperLift;
	}

protected:
	double nozzleDiameter;
	double rodDiameter;
	double flapperDiameter;

	int forceMode; //pressure acting in the flapper seat area {1-constant, 2-gradient}
	int forceContact; //pressure force contribution on the flapper seat at zero lift {1-Yes, 2-No}
	double xLim; //transition opening for pressure force on the flapper seat

	double vol10; // volume at port-1 corresponding to zero lift
	double vol20; // volume at port-2 corresponding to zero lift
};



/**
 * PneumaticTubularFlapperValve - C++
 */
class PneumaticTubularFlapperValve : public PneumaticFlapperValve {
public:
	PneumaticTubularFlapperValve(
			FrictionFlowValve* friction,
			double tubeInnerDiameter,
			double tubeOuterDiameter,
			double flapperLift0,
			double xForMinArea,
			double xForMaxArea,
			int forceContact,
			double xLim) :
				PneumaticFlapperValve(friction, flapperLift0, xForMinArea, xForMaxArea) {
		this->tubeInnerDiameter = tubeInnerDiameter;
		this->tubeOuterDiameter = tubeOuterDiameter;

		this->forceContact = forceContact;
		this->xLim = xLim;

		initAreas();
		setFlapperPosition(0); //flapperDisplacement = 0
	}

	virtual double getPressureForceOnFlapper() {
		double forceOnFlapper = state2->p() * (m::pi/4.) * (tubeOuterDiameter*tubeOuterDiameter - tubeInnerDiameter*tubeInnerDiameter);

		// Case-1: pressure force contributes on the flapper at zero lift
		if (forceContact == 1) { //1-Yes
			return forceOnFlapper;
		}

		// Case-2: pressure force doesn't contribute on the flapper at zero lift (i.e. forceOnFlapper = 0 at flapperLift = 0)
		if (flapperLift == 0) {
			double zeroForceOnFlapper = 0;
			return zeroForceOnFlapper;
		}

		//   Case-2.1: no transition opening for pressure force on the flapper
		if (xLim == 0.0) {
			return forceOnFlapper;
		}

		//   Case-2.1: With transition opening for pressure force on the flapper
		double forceOnFlapperSmooth = m::polysmooth(flapperLift, 0, xLim, 0, forceOnFlapper);
		return forceOnFlapperSmooth;
	}

protected:

	virtual void initAreas() {
		this->throatArea = m::pi * (tubeInnerDiameter*tubeInnerDiameter) /4.;
		this->minFlowArea = m::pi * tubeInnerDiameter * xForMinArea;
		this->maxFlowArea = m::pi * tubeInnerDiameter * xForMaxArea;
	}

	virtual double calcFlowArea(double flapperLift) {
		return m::pi * tubeInnerDiameter * flapperLift;
	}

protected:
	double tubeInnerDiameter;
	double tubeOuterDiameter;

	int forceContact; //pressure force contribution on the flapper seat at zero lift {1-Yes, 2-No}
	double xLim; //transition opening for pressure force on the flapper seat
};





/**
 * PneumaticValve - C
 */
Valve* PneumaticFlatFlapperNozzleValve_new(
		double nozzleDiameter,
		double rodDiameter,
		double flapperDiameter,
		double flapperLift0,
		double xForMinArea,
		double xForMaxArea,
		int forceMode,
		int forceContact,
		double xLim,
		double vol10,
		double vol20,
		double flowCoefficient) {
	FrictionFlowValve* friction = FrictionFlowValve_OrificeCompressibleRealGas_new(
			1, //allowBidirectionalFlow = 1 - yes
			0, //orificeArea = 0
			flowCoefficient);

	return new PneumaticFlatFlapperNozzleValve(
			friction,
			nozzleDiameter,
			rodDiameter,
			flapperDiameter,
			flapperLift0,
			xForMinArea,
			xForMaxArea,
			forceMode,
			forceContact,
			xLim,
			vol10,
			vol20);
}

Valve* PneumaticTubularFlapperValve_new(
		double tubeInnerDiameter,
		double tubeOuterDiameter,
		double flapperLift0,
		double xForMinArea,
		double xForMaxArea,
		int forceContact,
		double xLim,
		double flowCoefficient) {
	FrictionFlowValve* friction = FrictionFlowValve_OrificeCompressibleRealGas_new(
			1, //allowBidirectionalFlow = 1 - yes
			0, //orificeArea = 0
			flowCoefficient);

	return new PneumaticTubularFlapperValve(
			friction,
			tubeInnerDiameter,
			tubeOuterDiameter,
			flapperLift0,
			xForMinArea,
			xForMaxArea,
			forceContact,
			xLim);
}

void PneumaticFlapperValve_setFlapperPosition(PneumaticFlapperValve* valve, double flapperDisplacement) {
	valve->setFlapperPosition(flapperDisplacement);
}

double PneumaticFlapperValve_getPressureForceOnFlapper(PneumaticFlapperValve* valve) {
	return valve->getPressureForceOnFlapper();
}


double PneumaticFlapperValve_getFlapperLift(PneumaticFlapperValve* valve) {
	return valve->getFlapperLift();
}


double PneumaticFlapperValve_getFlowArea(PneumaticFlapperValve* valve) {
	return valve->getFlowArea();
}

double PneumaticFlapperValve_getThroatArea(PneumaticFlapperValve* valve) {
	return valve->getThroatArea();
}

void PneumaticFlapperValve_updateVolumes(PneumaticFlapperValve* valve,
		double v4, double x4, FluidFlow* flow1, FluidFlow* flow2) {
	valve->updateVolumes(v4, x4, flow1, flow2);
}

