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

struct SmoObject {
	SmoObject()	: instanceIndex(-1), parent(NULL) {}
	virtual ~SmoObject() {}

	int instanceIndex;
	SmoObject* parent;
};

struct SmoComponent {
	SmoComponent() : instanceIndex(-1), componentName(""), parent(NULL) {}
	virtual ~SmoComponent() {}

	int instanceIndex;
	String componentName;
	SmoComponent* parent;
};

#else //__cplusplus
DECLARE_C_STRUCT(SmoObject)
DECLARE_C_STRUCT(SmoComponent)
#endif //__cplusplus

BEGIN_C_LINKAGE
void SmoObject_setInstanceIndex(SmoObject* obj, int index);
int SmoObject_getInstanceIndex(SmoObject* obj);

void SmoComponent_setInstanceIndex(SmoComponent* component, int index);
void SmoComponent_setComponentName(SmoComponent* component, const char* componentName);
END_C_LINKAGE

#endif /* SMOCOMPONENT_H_ */
