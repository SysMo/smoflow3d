/*
 * Adaptor_R.h
 *
 *  Created on: Sep 19, 2014
 *      Author: Milen Borisov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#ifndef ADAPTOR_R_H_
#define ADAPTOR_R_H_

#include "flow_R/Component_R.h"
#include "media/MediumState.h"

#ifdef __cplusplus

class Adaptor_R : public Component_R {
public:
	Adaptor_R() {outerStateIndex = -1;}
	virtual ~Adaptor_R() {}

	int getOuterStateIndex() {return outerStateIndex;}
	void setOuterstateIndex(int stateIndex) {outerStateIndex = stateIndex;}

private:
	int outerStateIndex;
};


class BeginAdaptor_R : public Adaptor_R {
public:
	BeginAdaptor_R() {}
	virtual ~BeginAdaptor_R() {}
};


class EndAdaptor_R : public Adaptor_R {
public:
	EndAdaptor_R();
	virtual ~EndAdaptor_R();
};

#else //_cplusplus
DECLARE_C_STRUCT(Adaptor_R)
DECLARE_C_STRUCT(BeginAdaptor_R)
DECLARE_C_STRUCT(EndAdaptor_R)
#endif //_cplusplus


BEGIN_C_LINKAGE
int Component_R_isBeginAdaptor(Component_R* component);
int Component_R_isEndAdaptor(Component_R* component);

BeginAdaptor_R* BeginAdaptor_R_new(int allowBidirectionalFlow);
EndAdaptor_R* EndAdaptor_R_new(int allowBidirectionalFlow);

int Adaptor_R_getOuterStateIndex(Adaptor_R* adaptor);
void Adaptor_R_setOuterStateIndex(Adaptor_R* adaptor, int stateIndex);

void EndAdaptor_R_setActivatingSignal(EndAdaptor_R* endAdaptor, double activatingSignal);
END_C_LINKAGE


#endif /* ADAPTOR_R_H_ */
