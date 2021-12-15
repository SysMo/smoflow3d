/*
 * PneumaticValve.h
 *
 *  Created on: Dec 10, 2021
 *      Author: Milen Borisov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#ifndef PNEUMATICVALVE_H_
#define PNEUMATICVALVE_H_

#include "media/MediumState.h"
#include "flow/FlowBase.h"
#include "flow/FrictionFlowValve.h"
#include "flow/Valve.h"


#ifdef __cplusplus

class PneumaticFlapperNozzleValve : public Valve {
public:
	PneumaticFlapperNozzleValve(
			FrictionFlowValve* friction,
			double diameterNozzle,
			double diameterRod,
			double diameterFlapper,
			double flapperLift0,
			double xForMinArea,
			double xForMaxArea);
	virtual ~PneumaticFlapperNozzleValve();


	double getFlapperLift();
	double getFlowArea();
	double getThroatArea();

	double getPressureForceOnFlapper();

	void setFlapperPosition(double flapperDisplacement);

protected:
	double diameterNozzle; //di
	double diameterRod; //dr
	double diameterFlapper; //df
	double flapperLift0; //xlift0

	double flapperLift;
	double throatArea;
	double minFlowArea;
	double maxFlowArea;
};

#else //_cplusplus
DECLARE_C_STRUCT(PneumaticFlapperNozzleValve)
#endif //_cplusplus


BEGIN_C_LINKAGE

Valve* Valve_PneumaticFlapperNozzleValve_new(
		double diameterNozzle,
		double diameterRod,
		double diameterFlapper,
		double flapperLift0,
		double xForMinArea,
		double xForMaxArea,
		double flowCoefficient);

void Valve_PneumaticFlapperNozzleValve_setFlapperPosition(
		PneumaticFlapperNozzleValve* valve,
		double flapperDisplacement);

double Valve_PneumaticFlapperNozzleValve_getPressureForceOnFlapper(PneumaticFlapperNozzleValve* valve);

double Valve_PneumaticFlapperNozzleValve_getFlapperLift(PneumaticFlapperNozzleValve* valve);
double Valve_PneumaticFlapperNozzleValve_getFlowArea(PneumaticFlapperNozzleValve* valve);
double Valve_PneumaticFlapperNozzleValve_getThroatArea(PneumaticFlapperNozzleValve* valve);


END_C_LINKAGE

#endif /* PNEUMATICVALVE_H_ */
