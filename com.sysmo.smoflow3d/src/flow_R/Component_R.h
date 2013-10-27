/*
 * Component_R.h
 *
 *  Created on: Jul 31, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#ifndef COMPONENT_R_H_
#define COMPONENT_R_H_

#include "util/CommonDefinitions.h"
#include "media/MediumState.h"
#include "flow/FlowBase.h"

#ifdef __cplusplus

class Component_R : public SmoComponent {
public:
	Component_R();
	virtual ~Component_R();

	virtual void init(MediumState* state1, MediumState* state2);
	virtual bool compute(double massFlowRate, double minDownstreamPressure) = 0;

	MediumState* getUpstreamState(double massFlowRate);
	MediumState* getDownstreamState(double massFlowRate);

protected:
	MediumState* state1;
	MediumState* state2;
};

#else //_cplusplus
DECLARE_C_STRUCT(Component_R)
#endif //_cplusplus

#endif /* COMPONENT_R_H_ */
