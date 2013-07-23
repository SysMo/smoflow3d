/*
 * CodeTiming.h
 *
 *  Created on: Jul 23, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#ifndef CODETIMING_H_
#define CODETIMING_H_

#include "util/CommonDefinitions.h"

BEGIN_C_LINKAGE

uint64_t GetTimeMs64();

struct Timer {
	uint64_t startTime;
	uint64_t stopTime;
	bool running;
};

Timer* createTimer();
void timer_start(Timer* timer);
void timer_stop(Timer* timer);
double timer_read(Timer* timer);
void timer_reset(Timer* timer);

END_C_LINKAGE

#endif /* CODETIMING_H_ */
