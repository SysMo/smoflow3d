/*
 * DynamicLoader.h
 *
 *  Created on: Oct 24, 2013
 *      Author: Atanas Pavlov
 */

#ifndef DYNAMICLOADER_H_
#define DYNAMICLOADER_H_

#ifdef _WINDOWS
#define WINDOWS
#endif

#ifdef WINDOWS
#include <windows.h>
#else
#include <dlfcn.h>
#endif

#include "String.h"

typedef struct {
	String* libraryPath;
	String* methodPrefix;
#ifdef WINDOWS
	HINSTANCE libraryHandle;
#else
	void* libraryHandle;
#endif

} DynamicLoader;

DynamicLoader* DynamicLoader_new(const char* libraryPath, const char* methodPrefix);
void DynamicLoader_load(DynamicLoader* self);
void* DynamicLoader_getMethodAddress(DynamicLoader* self, const char* methodName);
void DynamicLoader_free(DynamicLoader** pSelf);
#endif /* DYNAMICLOADER_H_ */
