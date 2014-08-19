/*
 * Arrays.c
 *
 *  Created on: Oct 21, 2013
 *      Author: Atanas Pavlov
 */
#include "Arrays.h"


/**
 * Real array - functions
 */
RealArray* RealArray_new(size_t initialSize) {
	NEW_OBJECT(RealArray, self);
	NEW_ARRAY(double, initialSize, array);
	self->array = array;
	self->size = initialSize;
	self->capacity = initialSize;
	return self;
}


void RealArray_free(RealArray** pSelf) {
	if (*pSelf == NULL) return;

	RealArray* self = *pSelf;
	free(self->array);
	free(self);

	*pSelf = NULL;
}

void RealArray_resize(RealArray* self, size_t newSize) {
	int oldSize = self->size;
	if (newSize > self->capacity) {
		if (self->capacity == 0)
			self->capacity = 1;
		while (self->capacity < newSize) {
			self->capacity *= 2;
		}
		REALLOCATE_ARRAY(double, self->capacity, self->array);
		for (int i = oldSize; i < self->size; i++) {
			self->array[i] = 0;
		}
	}
	self->size = newSize;
}

void RealArray_append(RealArray* self, double element) {
	RealArray_resize(self, self->size + 1);
	self->array[self->size - 1] = element;
}


/**
 * Object array - functions
 */
ObjectArray* ObjectArray_new(size_t initialSize) {
	NEW_OBJECT(ObjectArray, self);
	NEW_ARRAY(void*, initialSize, array);
	self->array = array;
	self->size = initialSize;
	self->capacity = initialSize;
	for (size_t i = 0; i < self->size; i++) {
		self->array[i] = NULL;
	}
	return self;
}

void ObjectArray_free(ObjectArray** pSelf) {
	if (*pSelf == NULL) return;

	ObjectArray* self = *pSelf;
	free(self->array);
	free(self);

	*pSelf = NULL;
}

void ObjectArray_resize(ObjectArray* self, size_t newSize) {
	int oldSize = self->size;
	if (newSize > self->capacity) {
		// Determine the new capacity needed
		if (self->capacity == 0)
			self->capacity = 1;
		while (self->capacity < newSize) {
			self->capacity *= 2;
		}
		// Move content
		REALLOCATE_ARRAY(void, self->capacity, self->array);
		// Ensure the new elements are set to NULL
		for (int i = oldSize; i < self->size; i++) {
			self->array[i] = NULL;
		}
	}
	self->size = newSize;
}

void ObjectArray_append(ObjectArray* self, void* element) {
	ObjectArray_resize(self, self->size + 1);
	self->array[self->size - 1] = element;
}

void ObjectArray_deleteElements(ObjectArray* self, DestructorType elementDestructor) {
	for (size_t i = 0; i < self->size; i++) {
		if (self->array[i] != NULL) {
			(*elementDestructor)(&self->array[i]);
		}
	}
	self->size = 0;
}
