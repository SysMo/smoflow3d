/*
 * FluidChamber.h
 *
 *  Created on: Jul 26, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#ifndef FLUIDCHAMBER_H_
#define FLUIDCHAMBER_H_

#include "MediumState.h"

class FluidChamber {
public:
	FluidChamber();
	virtual ~FluidChamber();

	MediumState* state;
	double volume;

	BasicState stateTimeDerivatives;
	void computeStateDerivatives(double mDot, double HDot, double VDot);

};

#endif /* FLUIDCHAMBER_H_ */
