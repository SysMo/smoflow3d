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

#include "CommonDefinitions.h"

#ifdef __cplusplus

class DynamicLoader {
public:
	DynamicLoader();
	~DynamicLoader();
	void load(const char* libraryPath, const char* methodPrefix = NULL);
	void* getMethodAddress(const char* methodName);
protected:
	String libraryPath;
	String methodPrefix;
#ifdef WINDOWS
	HINSTANCE libraryHandle;
#else
	void* libraryHandle;
#endif

};

#else //__cplusplus
DECLARE_C_STRUCT(DynamicLoader)
#endif //__cplusplus

DynamicLoader* DynamicLoader_new(const char* libraryPath, const char* methodPrefix);
void DynamicLoader_load(DynamicLoader* self);
void* DynamicLoader_getMethodAddress(DynamicLoader* self, const char* methodName);
//void DynamicLoader_free(DynamicLoader** pSelf);

#endif /* DYNAMICLOADER_H_ */
