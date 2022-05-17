/*
 * PneumaticPiston.h
 *
 *  Created on: Dec 15, 2021
 *      Author: Milen Borisov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#ifndef PNEUMATICPISTON_H_
#define PNEUMATICPISTON_H_

#include "media/MediumState.h"
#include "flow/FlowBase.h"



#ifdef __cplusplus

class PneumaticPiston : public SmoComponent {
public:
	PneumaticPiston(double diameterPiston, double diameterRod, double x0);
	virtual ~PneumaticPiston();

	void init(MediumState* state1);

	double getPressureForceOnPiston();
	double getPistonArea();
	double getLength();
	double getVolume();
	double getVolumeDot();

	void compute(double x, double v);

protected:
	double diameterPiston; //dp
	double diameterRod; //dr

	double pistonArea;

	MediumState* state1;
	double x0; //chamber length at zero displacement

	double length;
	double volume;
	double volumeDot;
};

#else //_cplusplus
DECLARE_C_STRUCT(PneumaticPiston)
#endif //_cplusplus


BEGIN_C_LINKAGE

PneumaticPiston* PneumaticPiston_new(double diameterPiston, double diameterRod, double x0);

void PneumaticPiston_init(PneumaticPiston* piston, MediumState* state1);

void PneumaticPiston_compute(PneumaticPiston* piston, double x, double v);

double PneumaticPiston_getPressureForceOnPiston(PneumaticPiston* piston);
double PneumaticPiston_getPistonArea(PneumaticPiston* piston);
double PneumaticPiston_getLength(PneumaticPiston* piston);
double PneumaticPiston_getVolume(PneumaticPiston* piston);
double PneumaticPiston_getVolumeDot(PneumaticPiston* piston);

END_C_LINKAGE

#endif /* PNEUMATICPISTON_H_ */
