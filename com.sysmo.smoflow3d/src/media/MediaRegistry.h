/*
 * MediaRegistry.h
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

struct MediaRegistryClass {
	typedef std::map<int, Fluid*> type; //:TODO: (MILEN) rename type to ???
	typedef type::iterator iterator;
	type fluids;
	std::map<std::string, int> fluidNames;
};

#else

DECLARE_C_STRUCT(Medium)

#endif //__cplusplus

BEGIN_C_LINKAGE
void register_medium(const char *mediumName, int mediumIndex); //:TODO: (MILEN) rename medium_register to Medium_register, Medium_get
Medium* get_medium(int mediumIndex);
END_C_LINKAGE

#endif /* MEDIAREGISTRY_H_ */
