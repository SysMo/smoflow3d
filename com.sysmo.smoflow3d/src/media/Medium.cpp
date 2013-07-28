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

typedef std::map<int, Medium*> MediumContainer;
static MediumContainer MediumRegistry;

BEGIN_C_LINKAGE
void Medium_register(MediumKnownTypes mediumType, const char* mediumName, int mediumIndex) {
	MediumContainer::iterator it = MediumRegistry.find(mediumIndex);
	if (it != MediumRegistry.end()) {
		RaiseError("Medium index " << mediumIndex << " already used");
	}
	if (mediumType == sCompressibleFluidCoolProp) {
		std::string mediumNameStr(mediumName);
		Fluid* mediumFluid = Fluids.get_fluid(mediumNameStr);
		if (mediumFluid == NULL) {
			RaiseError("Fluid with name " << mediumName << "not found in CoolProp fluid list");
		} else {
			MediumRegistry[mediumIndex] = new Medium_CompressibleFluid_CoolProp(mediumFluid);
			//MediumRegistry.mediumNames[mediumNameStr] = mediumIndex;
		}
	}
	else {
		RaiseError("Unimplemented medium type: " << mediumType);
	}
}

Medium* Medium_get(int mediumIndex) {
	MediumContainer::iterator it = MediumRegistry.find(mediumIndex);
	if (it == MediumRegistry.end()) {
		RaiseError("No medium defined with index " << mediumIndex);
	}
	return (*it).second;
}

int Medium_index(Medium* medium) {
	int i = 0;
	for (MediumContainer::iterator it = MediumRegistry.begin(); it != MediumRegistry.end(); it++) {
		if ((*it).second == medium) {
			return i;
		}
		i++;
	}
	return -1;
}

END_C_LINKAGE