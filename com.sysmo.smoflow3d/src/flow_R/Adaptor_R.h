/*
 * Adaptor_R.h
 *
 *  Created on: Sep 19, 2014
 *      Author: Milen Borisov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#ifndef ADAPTOR_R_H_
#define ADAPTOR_R_H_

#include "util/CommonDefinitions.h"

#ifdef __cplusplus

class Adaptor_R : public SmoComponent {
public:
	Adaptor_R() {}
	virtual ~Adaptor_R() {}
};

class BeginAdaptor_R : public Adaptor_R {
public:
	BeginAdaptor_R() {}
	virtual ~BeginAdaptor_R() {}
};

class EndAdaptor_R : public Adaptor_R {
public:
	EndAdaptor_R() {}
	virtual ~EndAdaptor_R() {}
};

#else //_cplusplus
DECLARE_C_STRUCT(Adaptor_R)
DECLARE_C_STRUCT(BeginAdaptor_R)
DECLARE_C_STRUCT(EndAdaptor_R)
#endif //_cplusplus


BEGIN_C_LINKAGE
BeginAdaptor_R* BeginAdaptor_R_new();
EndAdaptor_R* EndAdaptor_R_new();
END_C_LINKAGE


#endif /* ADAPTOR_R_H_ */
