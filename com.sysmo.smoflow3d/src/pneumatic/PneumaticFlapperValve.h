/*
 * PneumaticFlapperValve.h
 *
 *  Created on: Dec 10, 2021
 *      Author: Milen Borisov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#ifndef PNEUMATICFLAPPERVALVE_H_
#define PNEUMATICFLAPPERVALVE_H_

#include "media/MediumState.h"
#include "flow/FlowBase.h"
#include "flow/FrictionFlowValve.h"
#include "flow/Valve.h"


#ifdef __cplusplus


class PneumaticFlapperValve : public Valve {
public:
	PneumaticFlapperValve(
			FrictionFlowValve* friction,
			double flapperLift0,
			double xForMinArea,
			double xForMaxArea);
	virtual ~PneumaticFlapperValve();

	double getFlapperLift();
	double getFlowArea();
	double getThroatArea();

	virtual double getPressureForceOnFlapper() = 0;

	void setFlapperPosition(double flapperDisplacement);

protected:
	virtual void initAreas() = 0;
	virtual double calcFlowArea(double flapperLift) = 0;

protected:
	double flapperLift0; //xlift0
	double xForMinArea;
	double xForMaxArea;

	double flapperLift;

	double throatArea;
	double minFlowArea;
	double maxFlowArea;
};


#else //_cplusplus
DECLARE_C_STRUCT(PneumaticFlapperValve)
#endif //_cplusplus


BEGIN_C_LINKAGE

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
		double flowCoefficient);

Valve* PneumaticTubularFlapperValve_new(
		double tubeInnerDiameter,
		double tubeOuterDiameter,
		double flapperLift0,
		double xForMinArea,
		double xForMaxArea,
		int forceContact,
		double xLim,
		double flowCoefficient);

void PneumaticFlapperValve_setFlapperPosition(PneumaticFlapperValve* valve, double flapperDisplacement);

double PneumaticFlapperValve_getPressureForceOnFlapper(PneumaticFlapperValve* valve);

double PneumaticFlapperValve_getFlapperLift(PneumaticFlapperValve* valve);
double PneumaticFlapperValve_getFlowArea(PneumaticFlapperValve* valve);
double PneumaticFlapperValve_getThroatArea(PneumaticFlapperValve* valve);

END_C_LINKAGE

#endif /* PNEUMATICFLAPPERVALVE_H_ */
