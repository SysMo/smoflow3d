/*
 * SmoComponent.h
 *
 *  Created on: Aug 6, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#ifndef SMOCOMPONENT_H_
#define SMOCOMPONENT_H_

#include "CommonDefinitions.h"

#ifdef __cplusplus

struct SmoComponent {
	SmoComponent()
	: instanceIndex(0),
	  parent(NULL) {
	}
	virtual ~SmoComponent(){}
	size_t instanceIndex;
	SmoComponent* parent;
};

#else //__cplusplus
DECLARE_C_STRUCT(SmoComponent)
#endif //__cplusplus

BEGIN_C_LINKAGE
size_t SmoComponent_getInstanceIndex(SmoComponent* component);
END_C_LINKAGE

#endif /* SMOCOMPONENT_H_ */
