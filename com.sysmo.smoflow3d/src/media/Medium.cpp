/*
 * Medium.cpp
 *
 *  Created on: Jul 22, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "Medium.h"
#include "util/CommonDefinitions.h"

extern FluidsContainer Fluids;

static MediumRegistryClass MediumRegistry;

BEGIN_C_LINKAGE
void Medium_register(const char* mediumName, int mediumIndex) {
	MediumRegistryClass::iterator it = MediumRegistry.mediums.find(mediumIndex);
	if (it != MediumRegistry.mediums.end()) {
		RaiseError("Medium index " << mediumIndex << " already used");
	}
	std::string mediumNameStr(mediumName);
	Fluid* mediumFluid = Fluids.get_fluid(mediumNameStr);
	MediumRegistry.mediums[mediumIndex] = mediumFluid;
	MediumRegistry.mediumNames[mediumNameStr] = mediumIndex;

}

Medium* Medium_get(int mediumIndex) {
	MediumRegistryClass::iterator it = MediumRegistry.mediums.find(mediumIndex);
	if (it == MediumRegistry.mediums.end()) {
		RaiseError("No medium defined with index " << mediumIndex);
	}
	return (*it).second;
}

END_C_LINKAGE
