/*
 * SolidRegistryClass.cpp
 *
 *  Created on: Aug 7, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "SolidRegistryClass.h"
#include "definitions/SolidDefinitions.h"
using namespace solids;

/**
 * SolidRegistryClass - C++
 */
SolidRegistryClass SolidRegistry;

SolidRegistryClass::SolidRegistryClass() {
	addSolid(new Aluminium6061());
	addSolid(new StainlessSteel304());
	addSolid(new CarbonFiberComposite());
	addSolid(new GlassFiberComposite());
	addSolid(new HighDensityPolyethylene());
	addSolid(new ArmaflexLTD());
	addSolid(new ArmaflexAF());
}

SolidRegistryClass::~SolidRegistryClass() {
	for (size_t i = 0; i < solidList.size(); i++) {
		delete solidList[i];
	}
}

void SolidRegistryClass::addSolid(Medium_Solid* solidInstance) {
	// Check
	std::map<std::string, Medium_Solid*>::iterator it = solidNameMap.find(solidInstance->name);
	if (it != solidNameMap.end()) {
		RaiseError("Solid with name '" << solidInstance->name << "' already exists in SolidRegistry")
	}

	// Add solid
	solidList.push_back(solidInstance);
	solidNameMap[solidInstance->name] = solidInstance;
}

void SolidRegistryClass::addSolidUserDefined(
		const char* solidName,
		const char* density,
		const char* thermalConductivity,
		const char* heatCapacity,
		const char* enthalpy) {
	addSolid(new SolidUserDefined(
		solidName,
		density,
		thermalConductivity,
		heatCapacity,
		enthalpy
	));
}

Medium_Solid* SolidRegistryClass::getSolid(const char* solidName) {
	std::map<std::string, Medium_Solid*>::iterator it = solidNameMap.find(solidName);
	if (it == solidNameMap.end()) {
		RaiseError("Solid with name '" << solidName << "' not found in SolidRegistry")
	}
	return (*it).second;
}
