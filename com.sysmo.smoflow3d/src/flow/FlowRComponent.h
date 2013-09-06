/*
 * FlowRComponent.h
 *
 *  Created on: Jul 31, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#ifndef FLOWRCOMPONENT_H_
#define FLOWRCOMPONENT_H_

#include "util/CommonDefinitions.h"
#include "media/MediumState.h"

#ifdef __cplusplus

class FlowRComponent : public SmoComponent {
public:
	FlowRComponent();
	virtual ~FlowRComponent();
	virtual void init(MediumState* state1, MediumState* state2);
protected:
	MediumState* state1;
	MediumState* state2;
};
#else //_cplusplus
DECLARE_C_STRUCT(FlowRComponent)
#endif //_cplusplus

#endif /* FLOWRCOMPONENT_H_ */
