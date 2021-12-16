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
	PneumaticPiston(double diameterPiston, double diameterRod);
	virtual ~PneumaticPiston();

	void init(MediumState* state1);

	double getPressureForceOnPiston();
	double getPistonArea();

protected:
	double diameterPiston; //dp
	double diameterRod; //dr

	double pistonArea;

	MediumState* state1;
};

#else //_cplusplus
DECLARE_C_STRUCT(PneumaticPiston)
#endif //_cplusplus


BEGIN_C_LINKAGE

PneumaticPiston* PneumaticPiston_new(double diameterPiston, double diameterRod);

void PneumaticPiston_init(PneumaticPiston* piston, MediumState* state1);

double PneumaticPiston_getPressureForceOnPiston(PneumaticPiston* piston);
double PneumaticPiston_getPistonArea(PneumaticPiston* piston);

END_C_LINKAGE

#endif /* PNEUMATICPISTON_H_ */
