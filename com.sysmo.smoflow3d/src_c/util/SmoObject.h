/*
 * SmoObject.h
 *
 *  Created on: Oct 23, 2013
 *      Author: Atanas Pavlov
 */

#ifndef SMOOBJECT_H_
#define SMOOBJECT_H_

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#define NEW_OBJECT(TYPE, NAME) \
	TYPE* NAME = (TYPE*)malloc(sizeof(TYPE))

#define NEW_ARRAY(TYPE, SIZE, NAME) \
	TYPE* NAME = (TYPE*)malloc((SIZE) * sizeof(TYPE))

#define REALLOCATE_ARRAY(TYPE, NEW_SIZE, NAME) \
	NAME = (TYPE*) realloc(NAME, NEW_SIZE * sizeof(TYPE))

#define CAST_VAR_TO(TYPE, name, NAME) \
	TYPE* name = (TYPE*) NAME

typedef struct {
	char name[100];
	int index;
} ComponentId;

ComponentId *ComponentId_create(const char *componentName, int componentIndex);
void setCurrentComponent(const char *componentName, int componentIndex);

extern ComponentId currentComponent;

#define AME_SET_CURRENT_COMPONENT \
	setCurrentComponent(_SUBMODELNAME_, *n)
#define CURRENT_COMPONENT_TO_SELF \
	strcpy(self->base.component.name, currentComponent.name); \
	self->base.component.index = currentComponent.index \

typedef struct {
	ComponentId component;
} SmoObject;

SmoObject* getDummyBase();





#endif /* SMOOBJECT_H_ */
