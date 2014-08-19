/*
 * StateMachineController.c
 *
 *  Created on: Oct 24, 2013
 *      Author: Atanas Pavlov
 */

#include "StateMachineController.h"
#include <unistd.h>

StateMachineController* StateMachineController_new(
		const char* controllerName,
		const char* controllerPath,
		int numRealParameters,
		int numIntegerParameters,
		int numInputs,
		int numOutputs) {
	NEW_OBJECT(StateMachineController, self);
	CURRENT_COMPONENT_TO_SELF;
	self->name = String_new(controllerName);
	self->loader = DynamicLoader_new(controllerPath, NULL);
	self->platform = &currentPlatform;

	DynamicLoader_load(self->loader);
	currentPlatform.printMessage("Loaded controller '%s' from '%s'\n", controllerName, controllerPath);
	self->new = DynamicLoader_getMethodAddress(self->loader, "new");
	self->init = DynamicLoader_getMethodAddress(self->loader, "init");
	self->checkForTransition = DynamicLoader_getMethodAddress(self->loader, "checkForTransition");
	self->switchState = DynamicLoader_getMethodAddress(self->loader, "switchState");
	self->setParameters = DynamicLoader_getMethodAddress(self->loader, "setParameters");
	self->setInputs = DynamicLoader_getMethodAddress(self->loader, "setInputs");
	self->getOutputs = DynamicLoader_getMethodAddress(self->loader, "getOutputs");

	self->new(self);
	if (self->numRealParameters != numRealParameters) {
		raiseError(&self->base, "Controller '%s' expects %d real parameters, got %d instead",
				self->name->chars, self->numRealParameters, numRealParameters);
	}

	if (self->numIntegerParameters != numIntegerParameters) {
		raiseError(&self->base, "Controller '%s' expects %d integer parameters, got %d instead",
				self->name->chars, self->numIntegerParameters, numIntegerParameters);
	}

	if (self->numInputs != numInputs) {
		raiseError(&self->base, "Controller '%s' expects %d inputs, got %d inputs instead",
				self->name->chars, self->numInputs, numInputs);
	}
	if (self->numOutputs != numOutputs) {
		raiseError(&self->base, "Controller '%s' expects %d outputs, got %d outputs instead",
				self->name->chars, self->numOutputs, numOutputs);
	}
	return self;
}

void StateMachineController_free(StateMachineController** pSelf) {
	if (*pSelf == NULL) return;

	StateMachineController* self = *pSelf;
	String_free(&(self->name));
	DynamicLoader_free(&self->loader);
	free(self->parameters);
	free(self->inputs);
	free(self->outputs);
	free(self->locals);
	free(self);

	*pSelf = NULL;
}
