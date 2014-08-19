/*
 * Arrays.h
 *
 *  Created on: Oct 21, 2013
 *      Author: Atanas Pavlov
 */

#ifndef ARRAYS_H_
#define ARRAYS_H_

#include "util/Common.h"


/**
 * Real array - declaration
 */
typedef struct {
  double* array;
  size_t size;
  size_t capacity;
} RealArray;

RealArray* RealArray_new(size_t initialSize);
void RealArray_free(RealArray** pSelf);

void RealArray_resize(RealArray* self, size_t newSize);
void RealArray_append(RealArray* self, double element);


/**
 * Object array - declaration
 */
typedef struct {
  void** array;
  size_t size;
  size_t capacity;
} ObjectArray;

ObjectArray* ObjectArray_new(size_t initialSize);
void ObjectArray_free(ObjectArray** pSelf);

void ObjectArray_resize(ObjectArray* self, size_t newSize);
void ObjectArray_append(ObjectArray* self, void* element);

#define ObjectArray_get(self, TYPE, index) \
		((TYPE*)self->array[index])

typedef void (*DestructorType)(void**);
void ObjectArray_deleteElements(ObjectArray* self, DestructorType elementDestructor);

#endif /* ARRAYS_H_ */
