/*
 * FlowComponent_R_2Port.h
 *
 *  Created on: Jul 31, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#ifndef FLOWCOMPONENT_R_2PORT_H_
#define FLOWCOMPONENT_R_2PORT_H_

#include "util/CommonDefinitions.h"
#include "media/MediumState.h"

#ifdef __cplusplus

class FlowComponent_R_2Port : public SmoComponent {
public:
	FlowComponent_R_2Port();
	virtual ~FlowComponent_R_2Port();

	virtual void init(MediumState* state1, MediumState* state2);

protected:
	MediumState* state1;
	MediumState* state2;
};

#else //_cplusplus
DECLARE_C_STRUCT(FlowComponent_R_2Port)
#endif //_cplusplus

#endif /* FLOWCOMPONENT_R_2PORT_H_ */
