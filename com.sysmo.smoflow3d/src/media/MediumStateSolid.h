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
#include "util/Functors.h"

#ifdef __cplusplus

class MediumStateSolid : public MediumState {
public:
	MediumStateSolid(Medium_Solid* medium);
	virtual ~MediumStateSolid();

	virtual void update_Tp(double T, double p);

	virtual double cp();
	virtual double lambda();

protected:
	Medium_Solid* solid;
};

#else // __cplusplus
DECLARE_C_STRUCT(MediumStateSolid)
#endif //__cplusplus

BEGIN_C_LINKAGE
MediumStateSolid* MediumStateSolid_new(Medium_Solid* medium);
END_C_LINKAGE

#endif /* MEDIUMSTATESOLID_H_ */
