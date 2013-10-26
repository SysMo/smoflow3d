/*
 * Pipe_R.h
 *
 *  Created on: Sep 19, 2014
 *      Author: Milen Borisov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#ifndef PIPE_R_H_
#define PIPE_R_H_

#include "media/MediumState.h"
#include "flow/FrictionFlowPipe.h"
#include "Component_R.h"


#ifdef __cplusplus

class Pipe_R : public Component_R {
public:
	Pipe_R(FrictionFlowPipe* friction);
	virtual ~Pipe_R();

	void init(MediumState* state1, MediumState* state2);
	bool compute(const double& massFlowRate, const double& minDownstreamPressure);

protected:
	FrictionFlowPipe* friction;
};

#else //_cplusplus
DECLARE_C_STRUCT(Pipe_R_new)
#endif //_cplusplus


BEGIN_C_LINKAGE
Pipe_R* Pipe_R_new(FrictionFlowPipe* friction);
END_C_LINKAGE


#endif /* PIPE_R_H_ */
