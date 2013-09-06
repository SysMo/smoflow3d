/*
 * SmoComponent.cpp
 *
 *  Created on: Aug 6, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "SmoComponent.h"

void SmoObject_setInstanceIndex(SmoObj* obj, int index) {
	obj->instanceIndex = index;
}

int SmoObject_getInstanceIndex(SmoObj* obj) {
	return obj->instanceIndex;
}

void SmoComponent_setInstanceIndex(SmoComponent* component, int index) {
	component->instanceIndex = index;
}

int SmoComponent_getInstanceIndex(SmoComponent* component) {
	return component->instanceIndex;
}
