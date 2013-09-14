/*
 * SmoFlowAmeFunctions.h
 *
 *  Created on: Sep 13, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#ifndef SMOFLOWAMEFUNCTIONS_H_
#define SMOFLOWAMEFUNCTIONS_H_

#include "ameutils.h"

void message_amesim(const char* text) {
	ameprintf(text);
}

void warning_amesim(const char* text) {
	amefprintf(stderr, text);
}

void error_amesim(const char* text) {
	amefprintf(stderr, text);
	AmeExit(1);
}

void exit_amesim() {
	AmeExit(0);
}

void updateEventIndicator_amesim(int indicator) {
	disloc_(&indicator);
}

extern int EventModeFlag_amesim;

int isEventMode_amesim() {
	int res = (EventModeFlag_amesim == 0);
	return res;
}

int isFirstTimeStep_amesim() {
	return firstc_();
}

void registerTimeEvent_amesim(double t) {
	distim_(&t);
}




#endif /* SMOFLOWAMEFUNCTIONS_H_ */
