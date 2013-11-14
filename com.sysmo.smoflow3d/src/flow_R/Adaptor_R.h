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
	Adaptor_R() {}
	virtual ~Adaptor_R() {}
};

class BeginAdaptor_R : public Adaptor_R {
public:
	BeginAdaptor_R();
	virtual ~BeginAdaptor_R();

	void setBeginState(MediumState* state) {beginState = state;}
	MediumState* getBeginState() {return beginState;}

private:
	MediumState* beginState;
};

class EndAdaptor_R : public Adaptor_R {
public:
	EndAdaptor_R();
	virtual ~EndAdaptor_R();

	bool isFlowClosed() {return !flagIsFlowOpen;}
	bool isFlowOpen() {return flagIsFlowOpen;}
	void closeFlow() {flagIsFlowOpen = false;}
	void openFlow() {flagIsFlowOpen = true;}

	void setEndState(MediumState* state) {endState = state;}
	MediumState* getEndState() {return endState;}

private:
	MediumState* endState;

	bool flagIsFlowOpen;
};

#else //_cplusplus
DECLARE_C_STRUCT(Adaptor_R)
DECLARE_C_STRUCT(BeginAdaptor_R)
DECLARE_C_STRUCT(EndAdaptor_R)
#endif //_cplusplus


BEGIN_C_LINKAGE
BeginAdaptor_R* BeginAdaptor_R_new();
EndAdaptor_R* EndAdaptor_R_new();

int Component_R_isBeginAdaptor(Component_R* component);
MediumState* BeginAdaptor_R_getBeginState(BeginAdaptor_R* beginAdaptor);


int Component_R_isEndAdaptor(Component_R* component);
MediumState* EndAdaptor_R_getEndState(EndAdaptor_R* endAdaptor);
void EndAdaptor_R_setEndState(EndAdaptor_R* endAdaptor, MediumState* state);
void EndAdaptor_R_setRegulatingSignal(EndAdaptor_R* endAdaptor, double regulatingSignal);
END_C_LINKAGE


#endif /* ADAPTOR_R_H_ */
