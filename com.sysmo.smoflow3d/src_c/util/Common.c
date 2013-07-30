/*
 * Common.c
 *
 *  Created on: Oct 16, 2013
 *      Author: Atanas Pavlov
 */

#include "Common.h"
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

PlatformFunctions currentPlatform = {
		.printMessage = printf,
		.printError = printf,
		.exit = exit
};

void raiseWarning(SmoObject *obj, const char* message, ...) {
	char buffer[256];
	va_list args;
	va_start (args, message);
	vsnprintf(buffer, 256, message, args);
	va_end (args);

	currentPlatform.printError("\nWarning in ");
	currentPlatform.printError("object {Component: '%s', Instance: %d}.\n",
			obj->component.name, obj->component.index);
	currentPlatform.printError(buffer);
	currentPlatform.printError("\n");

}

void raiseError(SmoObject *obj, const char* message, ...) {
	char buffer[256];
	va_list args;
	va_start (args, message);
	vsnprintf(buffer, 256, message, args);
	va_end (args);

	currentPlatform.printError("\n------------------------------------------------\n");
	currentPlatform.printError("\nFatal error in ");
	currentPlatform.printError("object {Component: '%s', Instance: %d}.\n",
			obj->component.name, obj->component.index);
	currentPlatform.printError(buffer);
	currentPlatform.printError("\nTerminating the program.\n");
	currentPlatform.printError("\n------------------------------------------------\n");
	currentPlatform.exit(1);
}

