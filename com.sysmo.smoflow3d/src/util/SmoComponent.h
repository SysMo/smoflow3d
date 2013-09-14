/*
 * SmoComponent.h
 *
 *  Created on: Aug 6, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#ifndef SMOCOMPONENT_H_
#define SMOCOMPONENT_H_

#include <stddef.h>
#include "Macros.h"

#ifdef __cplusplus

#include <string>
typedef std::string String;

struct SmoObj {
	SmoObj()
	: instanceIndex(-1),
	  parent(NULL) {
	}
	virtual ~SmoObj(){}
	int instanceIndex;
	SmoObj* parent;
};

struct SmoComponent {
	SmoComponent()
	: instanceIndex(-1),
	  parent(NULL) {
	}
	virtual ~SmoComponent(){}

	virtual const char* getComponentName() = 0;
	int instanceIndex;
	SmoComponent* parent;
};

#else //__cplusplus
DECLARE_C_STRUCT(SmoObj)
DECLARE_C_STRUCT(SmoComponent)
#endif //__cplusplus

BEGIN_C_LINKAGE
void SmoObject_setInstanceIndex(SmoObj* obj, int index);
int SmoObject_getInstanceIndex(SmoObj* obj);

void SmoComponent_setInstanceIndex(SmoComponent* component, int index);
int SmoComponent_getInstanceIndex(SmoComponent* component);
END_C_LINKAGE

#endif /* SMOCOMPONENT_H_ */
