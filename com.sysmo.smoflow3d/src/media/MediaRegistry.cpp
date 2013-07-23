/*
 * MediaRegistry.cpp
 *
 *  Created on: Jul 22, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "MediaRegistry.h"
#include "util/CommonDefinitions.h"

extern FluidsContainer Fluids;

static MediaRegistryClass MediaRegistry;

BEGIN_C_LINKAGE
void register_medium(const char *mediumName, int mediumIndex) {
	MediaRegistryClass::iterator it = MediaRegistry.fluids.find(mediumIndex);
	if (it != MediaRegistry.fluids.end()) {
		RaiseError("Medium index " << mediumIndex << " already used");
	}
	std::string mediumNameStr(mediumName);
	Fluid* mediumFluid = Fluids.get_fluid(mediumNameStr);
	MediaRegistry.fluids[mediumIndex] = mediumFluid;
	MediaRegistry.fluidNames[mediumNameStr] = mediumIndex;

}

Medium* get_medium(int mediumIndex) {
	MediaRegistryClass::iterator it = MediaRegistry.fluids.find(mediumIndex);
	if (it == MediaRegistry.fluids.end()) {
		RaiseError("No medium defined with index " << mediumIndex);
	}
	return (*it).second;
}

END_C_LINKAGE
