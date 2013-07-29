/*
 * Arrays.h
 *
 *  Created on: Oct 22, 2013
 *      Author: Milen Borisov
 */
#ifndef STRING_H_
#define STRING_H_

#include "util/Common.h"

/**
 * String - declaration
 */
typedef struct {
	char* chars;
	size_t length;
} String;

String* String_new(const char* content);
void String_free(String** pSelf);

void String_trim(String* self);

#endif /* STRING_H_ */
