/*
 * MediumSolid.cpp
 *
 *  Created on: Aug 4, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "media/SolidRegistryClass.h"
#include <iostream>

int main(int argc, char** argv) {
	std::cout << "Begin test" << std::endl;

	Medium_Solid* solid = SolidRegistry.getSolid("Aluminium6061");
	std::cout << "medium name = " << solid->name << std::endl;

	std::cout << "rho(20.0) =  " << (*solid->densityFunction)(0) << std::endl;
	std::cout << "rho(300.0) =  " << (*solid->densityFunction)(0) << std::endl;

	FunctorCache* heatCapacityCache = solid->heatCapacityFunction->createCache();
	std::cout << "cp(10.0) =  " << (*solid->heatCapacityFunction)(10.0, heatCapacityCache) << std::endl;
	std::cout << "cp(20.0) =  " << (*solid->heatCapacityFunction)(20.0, heatCapacityCache) << std::endl;
	std::cout << "cp(35.0) =  " << (*solid->heatCapacityFunction)(35.0, heatCapacityCache) << std::endl;
	std::cout << "cp(300.0) =  " << (*solid->heatCapacityFunction)(300.0, heatCapacityCache) << std::endl;
	std::cout << "cp(310.0) =  " << (*solid->heatCapacityFunction)(310.0, heatCapacityCache) << std::endl;

	FunctorCache* enthalpyCache = solid->enthalpyFunction->createCache();
	std::cout << "h(35.0) = " << (*solid->enthalpyFunction)(35.0, enthalpyCache) << std::endl;

	std::cout << "End test" << std::endl;
	return 0;
}
