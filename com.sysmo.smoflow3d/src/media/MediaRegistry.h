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
	typedef std::map<int, Fluid*> type;
	typedef type::iterator iterator;
	type fluids;
	std::map<std::string, int> fluidNames;
};

#else

DECLARE_C_STRUCT(Medium)

#endif //__cplusplus

BEGIN_C_LINKAGE
void register_medium(const char *mediumName, int mediumIndex);
Medium* get_medium(int mediumIndex);
END_C_LINKAGE

#endif /* MEDIAREGISTRY_H_ */
