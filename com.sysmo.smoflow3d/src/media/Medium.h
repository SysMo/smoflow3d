/*
 * Medium.h
 *
 *  Created on: Jul 22, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#ifndef MEDIAREGISTRY_H_
#define MEDIAREGISTRY_H_

#include "util/CommonDefinitions.h"


#ifdef __cplusplus

#include <map>
#include "CoolProp.h"

typedef Fluid Medium;

struct MediumRegistryClass {
	typedef std::map<int, Medium*> MediumContainer;
	typedef MediumContainer::iterator iterator;

	MediumContainer mediums;
	std::map<std::string, int> mediumNames;
};

#else

DECLARE_C_STRUCT(Medium)

#endif //__cplusplus


BEGIN_C_LINKAGE
void Medium_register(const char* mediumName, int mediumIndex);
Medium* Medium_get(int mediumIndex);
END_C_LINKAGE

#endif /* MEDIAREGISTRY_H_ */
