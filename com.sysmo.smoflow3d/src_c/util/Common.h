/*
 * Common.h
 *
 *  Created on: Oct 16, 2013
 *      Author: Atanas Pavlov
 */

#ifndef UTIL_COMMON_H_
#define UTIL_COMMON_H_

#include "SmoObject.h"

typedef int Boolean;

typedef struct {
	int (*printMessage)(const char *message, ...);
	int (*printError)(const char *message, ...);
	void (*exit)(int status);
} PlatformFunctions;

extern PlatformFunctions currentPlatform;

#define STANDALONE_EXE \
	currentPlatform.printMessage = printf; \
	currentPlatform.printError = printf; \
	currentPlatform.exit = exit; \

void raiseWarning(SmoObject *obj, const char* message, ...);
void raiseError(SmoObject *obj, const char* message, ...);


#endif /* UTIL_COMMON_H_ */
