/*
 * Adaptor_R.cpp
 *
 *  Created on: Sep 19, 2014
 *      Author: Milen Borisov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "Adaptor_R.h"
using namespace smoflow;

/**
 * Adaptor_R - C++
 */
EndAdaptor_R::EndAdaptor_R() {
}

EndAdaptor_R::~EndAdaptor_R() {
}

/**
 * Adaptor_R - C
 */
int Component_R_isBeginAdaptor(Component_R* component) {
	if (dynamic_cast<BeginAdaptor_R*>(component) != NULL) {
		return 1;
	} else {
		return 0;
	}
}

int Component_R_isEndAdaptor(Component_R* component) {
	if (dynamic_cast<EndAdaptor_R*>(component) != NULL) {
		return 1;
	} else {
		return 0;
	}
}

BeginAdaptor_R* BeginAdaptor_R_new(int allowBidirectionalFlow) {
	BeginAdaptor_R* beginAdaptor = new BeginAdaptor_R();
	if (allowBidirectionalFlow == 0) { //0 - no
		beginAdaptor->setIsBidirectionalFlowAllowed(false);
	}

	return beginAdaptor;
}

EndAdaptor_R* EndAdaptor_R_new(int allowBidirectionalFlow) {
	EndAdaptor_R* endAdaptor = new EndAdaptor_R();
	if (allowBidirectionalFlow == 0) { //0 - no
		endAdaptor->setIsBidirectionalFlowAllowed(false);
	}

	return endAdaptor;
}

int Adaptor_R_getOuterStateIndex(Adaptor_R* adaptor) {
	return adaptor->getOuterStateIndex();
}

void Adaptor_R_setOuterStateIndex(Adaptor_R* adaptor, int stateIndex) {
	adaptor->setOuterstateIndex(stateIndex);
}

void EndAdaptor_R_setActivatingSignal(EndAdaptor_R* endAdaptor, double activatingSignal) {
	if (activatingSignal > 0) {
		endAdaptor->openFlow();
	} else {
		endAdaptor->closeFlow();
	}
}
