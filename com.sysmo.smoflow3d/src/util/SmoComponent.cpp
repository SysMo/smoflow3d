/*
 * SmoComponent.cpp
 *
 *  Created on: Aug 6, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "SmoComponent.h"

void SmoObject_setInstanceIndex(SmoObject* obj, int index) {
	obj->instanceIndex = index;
}

int SmoObject_getInstanceIndex(SmoObject* obj) {
	return obj->instanceIndex;
}

void SmoComponent_setInstanceIndex(SmoComponent* component, int index) {
	component->instanceIndex = index;
}

void SmoComponent_setComponentName(SmoComponent* component, const char* componentName) {
	component->componentName = componentName;
}
