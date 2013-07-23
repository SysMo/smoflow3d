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

static MediaRegistry mediaRegistry;

BEGIN_C_LINKAGE
void register_medium(const char *mediumName, int mediumIndex) {
	MediaRegistry::iterator it = mediaRegistry.fluids.find(mediumIndex);
	if (it != mediaRegistry.fluids.end()) {
		RaiseError("Medium index " << mediumIndex << " already used");
	}
	std::string mediumNameStr(mediumName);
	Fluid* mediumFluid = Fluids.get_fluid(mediumNameStr);
	mediaRegistry.fluids[mediumIndex] = mediumFluid;
	mediaRegistry.fluidNames[mediumNameStr] = mediumIndex;

}

Medium* get_medium(int mediumIndex) {
	MediaRegistry::iterator it = mediaRegistry.fluids.find(mediumIndex);
	if (it == mediaRegistry.fluids.end()) {
		RaiseError("No medium defined with index " << mediumIndex);
	}
	return (*it).second;
}

END_C_LINKAGE
