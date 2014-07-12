/*
 * SmoComponent.cpp
 *
 *  Created on: Aug 6, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "SmoComponent.h"

size_t SmoComponent_getInstanceIndex(SmoComponent* component) {
	return component->instanceIndex;
}
