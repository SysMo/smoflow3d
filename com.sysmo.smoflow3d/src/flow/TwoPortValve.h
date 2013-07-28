/*
 * TwoPortValve.h
 *
 *  Created on: Jul 28, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#ifndef TWOPORTVALVE_H_
#define TWOPORTVALVE_H_

#include "util/CommonDefinitions.h"


#ifdef __cplusplus

#include "media/MediumState.h"

class TwoPortValve {
public:
	TwoPortValve();
	virtual ~TwoPortValve();
};

#else //no __cplusplus

DECLARE_C_STRUCT(TwoPortValve)

#endif //__cplusplus


BEGIN_C_LINKAGE

END_C_LINKAGE


#endif /* TWOPORTVALVE_H_ */
