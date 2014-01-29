/*
 * Medium.cpp
 *
 *  Created on: Jul 22, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "Medium.h"
#include "util/CommonDefinitions.h"
#include "SolidRegistryClass.h"

extern FluidsContainer Fluids;

typedef std::map<int, Medium*> MediumContainer;
static MediumContainer MediumRegistry;

/**
 * Medium - C
 */
void Medium_register(MediumConcreteTypes mediumType, const char* mediumName, int mediumIndex) {
	MediumContainer::iterator it = MediumRegistry.find(mediumIndex);
	if (it != MediumRegistry.end()) {
		RaiseError("Medium index " << mediumIndex << " already used.");
	}
	if (mediumType == sCompressibleFluidCoolProp) {
		std::string mediumNameStr(mediumName);
		Fluid* mediumFluid = Fluids.get_fluid(mediumNameStr);
		if (mediumFluid == NULL) {
			RaiseError("Fluid with name " << mediumName << "not found in CoolProp fluid list");
		} else {
			Medium_CompressibleFluid_CoolProp* medium =  new Medium_CompressibleFluid_CoolProp(mediumFluid);
			medium->name = mediumNameStr;
			MediumRegistry[mediumIndex] = medium;
			std::cout << "Registered fluid " << mediumFluid->get_name() << " (TMin = " << mediumFluid->limits.Tmin << ")\n";
		}
	} else if (mediumType == sSolidThermal) {
		Medium* medium = SolidRegistry.getSolid(mediumName);
		MediumRegistry[mediumIndex] = medium;
	} else {
		RaiseError("Unimplemented medium type: " << mediumType);
	}
}

void Medium_registerSolidConstProps(
		const char* mediumName,
		int mediumIndex,
		double density,
		double thermalConductivity,
		double heatCapacity,
		double enthalpy) {
	// Add a new solid
	SolidRegistry.addSolidConstProps(mediumName, density, thermalConductivity, heatCapacity, enthalpy);

	// Register the solid
	Medium* medium = SolidRegistry.getSolid(mediumName);
	MediumRegistry[mediumIndex] = medium;
}

Medium* Medium_get(int mediumIndex) {
	MediumContainer::iterator it = MediumRegistry.find(mediumIndex);
	if (it == MediumRegistry.end()) {
		RaiseError("No medium defined with index " << mediumIndex);
	}
	return (*it).second;
}

int Medium_index(Medium* medium) {
	for (MediumContainer::iterator it = MediumRegistry.begin(); it != MediumRegistry.end(); it++) {
		if ((*it).second == medium) {
			return (*it).first;
		}
	}
	return -1;
}

MediumPhase Medium_getPhase(Medium* medium) {
	return medium->phase;
}

MediumCompressibility Medium_getCompressibility(Medium* medium) {
	return medium->compressibility;
}

MediumCompositionType Medium_getCompositionType(Medium* medium) {
	return medium->compositionType;
}

MediumConcreteTypes Medium_getConcreteType(Medium* medium) {
	return medium->concreteType;
}
