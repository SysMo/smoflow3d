/*
 * SmoObject.c
 *
 *  Created on: Oct 23, 2013
 *      Author: Atanas Pavlov
 */

#include "SmoObject.h"
#include <string.h>

static SmoObject defaultBase;
ComponentId currentComponent = {
		.name = "Global scope",
		.index = -1
};

ComponentId*ComponentId_create(const char *componentName, int componentIndex) {
	NEW_OBJECT(ComponentId, self);
	strcpy(self->name, componentName);
	self->index = componentIndex;
	return self;
}

void setCurrentComponent_(const char *componentName, int componentIndex) {
	strcpy(currentComponent.name, componentName);
	currentComponent.index = componentIndex;
}

SmoObject* getDummyBase() {
	strcpy(defaultBase.component.name, currentComponent.name);
	defaultBase.component.index = currentComponent.index;
	return &defaultBase;
}
