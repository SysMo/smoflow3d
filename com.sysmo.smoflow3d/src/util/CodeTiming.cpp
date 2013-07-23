/*
 * CodeTiming.cpp
 *
 *  Created on: Jul 23, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "CodeTiming.h"

#include <stdint.h>
#ifdef WIN32
#include <Windows.h>
#else
#include <sys/time.h>
#include <ctime>
#endif

BEGIN_C_LINKAGE

Timer* createTimer() {
	Timer* timer = new Timer();
	timer->running = false;
	timer_reset(timer);
	return timer;
}

void timer_start(Timer* timer) {
	timer->startTime = GetTimeMs64();
	timer->running = true;
}

void timer_stop(Timer* timer) {
	timer->stopTime = GetTimeMs64();
	timer->running = false;
}

double timer_read(Timer* timer) {
	if (timer->running) {
		return (GetTimeMs64() - timer->startTime);
	} else {
		return (timer->stopTime - timer->startTime);
	}
}

void timer_reset(Timer* timer) {
	timer->startTime = GetTimeMs64();
	timer->stopTime = GetTimeMs64();
}

END_C_LINKAGE

/* Returns the amount of milliseconds elapsed since the UNIX epoch. Works on both
 * windows and linux. */

uint64_t GetTimeMs64()
{
#ifdef WIN32
 /* Windows */
 FILETIME ft;
 LARGE_INTEGER li;

 /* Get the amount of 100 nano seconds intervals elapsed since January 1, 1601 (UTC) and copy it
  * to a LARGE_INTEGER structure. */
 GetSystemTimeAsFileTime(&ft);
 li.LowPart = ft.dwLowDateTime;
 li.HighPart = ft.dwHighDateTime;

 uint64_t ret = li.QuadPart;
 ret -= 116444736000000000LL; /* Convert from file time to UNIX epoch time. */
 ret /= 10000; /* From 100 nano seconds (10^-7) to 1 millisecond (10^-3) intervals */

 return ret;
#else
 /* Linux */
 struct timeval tv;

 gettimeofday(&tv, NULL);

 uint64_t ret = tv.tv_usec;
 /* Convert from micro seconds (10^-6) to milliseconds (10^-3) */
 ret /= 1000;

 /* Adds the seconds (10^0) after converting them to milliseconds (10^-3) */
 ret += (tv.tv_sec * 1000);

 return ret;
#endif
}
