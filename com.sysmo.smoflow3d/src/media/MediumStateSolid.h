/*
 * MediumStateSolid.h
 *
 *  Created on: Aug 5, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#ifndef MEDIUMSTATESOLID_H_
#define MEDIUMSTATESOLID_H_

#include "MediumState.h"
#include "Medium.h"

#ifdef __cplusplus

class MediumState_Solid : public MediumState {
public:
	MediumState_Solid(Medium_Solid* medium);
	virtual ~MediumState_Solid();

	virtual void update_Tp(double T, double p);

	virtual double u();
	virtual double cp();
	virtual double lambda();
	virtual double mu();

protected:
	Medium_Solid* solid;
	FunctorCache* densityCache;
	FunctorCache* heatCapacityCache;
	FunctorCache* thermalConductivityCache;
};

#else // __cplusplus
DECLARE_C_STRUCT(MediumState_Solid)
#endif //__cplusplus

BEGIN_C_LINKAGE
MediumState_Solid* MediumStateSolid_new(Medium_Solid* medium);
END_C_LINKAGE

#endif /* MEDIUMSTATESOLID_H_ */
