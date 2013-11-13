/*
 * Component_R.cpp
 *
 *  Created on: Jul 31, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "Component_R.h"

using namespace smoflow;

/**
 * Component_R - C++
 */


/**
 * Component_R - C
 */
static std::vector<Component_R*> Component_Registry;

int Component_R_register(Component_R* component) {
	Component_Registry.push_back(component);
	size_t instanceIndex = Component_Registry.size();
	component->instanceIndex = instanceIndex;
	return instanceIndex;
}

Component_R* Component_R_get(int componentIndex) {
	return Component_Registry.at(componentIndex - 1);
}
