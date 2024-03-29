/*
 * SolidRegistryClass.h
 *
 *  Created on: Aug 7, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#ifndef SOLIDREGISTRYCLASS_H_
#define SOLIDREGISTRYCLASS_H_

#include "util/CommonDefinitions.h"
#include "Medium.h"

class SolidRegistryClass {
public:
	SolidRegistryClass();
	virtual ~SolidRegistryClass();
	Medium_Solid* getSolid(const char* solidName);

	void addSolidUserDefined(const char* solidName, const char* density, const char* thermalConductivity, const char* heatCapacity, const char* enthalpy);

protected:
	void addSolid(Medium_Solid* solidInstance);

	std::map<std::string, Medium_Solid*> solidNameMap;
	std::vector <Medium_Solid*> solidList;
};

extern SolidRegistryClass SolidRegistry;

#endif /* SOLIDREGISTRYCLASS_H_ */
