/*
 * DynamicLoader.c
 *
 *  Created on: Oct 24, 2013
 *      Author: Atanas Pavlov
 */

#include "DynamicLoader.h"
#include "SmoObject.h"

DynamicLoader* DynamicLoader_new(const char* libraryPath, const char* methodPrefix) {
	NEW_OBJECT(DynamicLoader, self);
	self->libraryPath = String_new(libraryPath);
	if (methodPrefix != NULL && strlen(methodPrefix) > 0) {
		self->methodPrefix = String_new(methodPrefix);
	} else {
		self->methodPrefix = NULL;
	}
	return self;
}

void DynamicLoader_load(DynamicLoader* self) {
#ifdef WINDOWS
	self->libraryHandle = LoadLibrary(self->libraryPath->chars);
#else
	self->libraryHandle = dlopen(self->libraryPath->chars, RTLD_LAZY);
#endif
	if (!self->libraryHandle) {
#ifdef WINDOWS
		DWORD errorCode = GetLastError();
		raiseWarning(getDummyBase(), "Dynamic loader returned error code %d", errorCode);
#endif
		raiseError(getDummyBase(), "Could not load dynamic library '%s'", self->libraryPath->chars);
	}
}

void* DynamicLoader_getMethodAddress(DynamicLoader* self, const char* methodName){
    char fullMethodName[4096];
    void* fp;
    if (self->methodPrefix != NULL) {
        sprintf(fullMethodName, "%s_%s", self->methodPrefix->chars, methodName);
    } else {
        sprintf(fullMethodName, "%s", methodName);
    }
#ifdef WINDOWS
    fp = (void*)GetProcAddress(self->libraryHandle, fullMethodName);
#else
    fp = (void*)dlsym(self->libraryHandle, fullMethodName);
#endif
    if (!fp) {
        raiseError(getDummyBase(),"Method '%s' not found in the DLL '%s'.", fullMethodName, self->libraryPath->chars);
    }
    return fp;
}

void DynamicLoader_free(DynamicLoader** pSelf) {
	if (*pSelf == NULL) return;
	DynamicLoader* self = *pSelf;
	String_free(&(self->libraryPath));
	String_free(&(self->methodPrefix));
	free(self);

	*pSelf = NULL;
}
