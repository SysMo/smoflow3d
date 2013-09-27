/*
 * DynamicLoader.c
 *
 *  Created on: Oct 24, 2013
 *      Author: Atanas Pavlov
 */

#include "DynamicLoader.h"

DynamicLoader::DynamicLoader() {
}

DynamicLoader::~DynamicLoader() {
}

void DynamicLoader::load(const char* libraryPath, const char* methodPrefix) {
	this->libraryPath = libraryPath;
	if (methodPrefix != NULL) {
		this->methodPrefix = methodPrefix;
	} else {
		this->methodPrefix = "";
	}
#ifdef WINDOWS
	libraryHandle = LoadLibrary(libraryPath);
#else
	libraryHandle = dlopen(libraryPath, RTLD_LAZY);
#endif
	if (!libraryHandle) {
#ifdef WINDOWS
		DWORD errorCode = GetLastError();
		RaiseWarning("Dynamic loader returned error code " << errorCode);
#endif
		RaiseError("Could not load dynamic library '"<< this->libraryPath << "'");
	}
}

void* DynamicLoader::getMethodAddress(const char* methodName){
    String fullMethodName;
    void* fp;
    if (methodPrefix.length() != 0) {
    	fullMethodName = methodName;
    	fullMethodName += "_";
    	fullMethodName += methodPrefix;
    } else {
        fullMethodName = methodName;
    }
#ifdef WINDOWS
    fp = (void*)GetProcAddress(libraryHandle, fullMethodName.c_str());
#else
    fp = (void*)dlsym(libraryHandle, fullMethodName.c_str());
#endif
    if (!fp) {
        RaiseError("Method '"<< fullMethodName <<"' not found in the DLL '"<< libraryPath << "'!");
    }
    return fp;
}

/*
void DynamicLoader_free(DynamicLoader** pSelf) {
	if (*pSelf == NULL) return;
	DynamicLoader* self = *pSelf;
	String_free(&(self->libraryPath));
	String_free(&(self->methodPrefix));
	free(self);

	*pSelf = NULL;
}
*/
