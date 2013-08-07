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

SolidRegistryClass SolidRegistry;

SolidRegistryClass::SolidRegistryClass() {
	addSolid("Aluminium6061", new Aluminium6061());
}

SolidRegistryClass::~SolidRegistryClass() {
	for (size_t i = 0; i < solidList.size(); i++) {
		delete solidList[i];
	}
}

void SolidRegistryClass::addSolid(const char* solidName, Medium_Solid* solidInstance) {
	solidList.push_back(solidInstance);
	solidNameMap[solidName] = solidInstance;
}

Medium_Solid* SolidRegistryClass::getSolid(const char* solidName) {
	std::map<std::string, Medium_Solid*>::iterator it = solidNameMap.find(solidName);
	if (it == solidNameMap.end()) {
		RaiseError("Solid with name " << solidName << " not found in SolidRegistry")
	}
	return (*it).second;
}
