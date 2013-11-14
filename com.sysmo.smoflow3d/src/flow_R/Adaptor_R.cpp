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
BeginAdaptor_R::BeginAdaptor_R() {
	beginState = NULL;
}

BeginAdaptor_R::~BeginAdaptor_R() {

}

EndAdaptor_R::EndAdaptor_R() {
	flagIsFlowOpen = true;
}

EndAdaptor_R::~EndAdaptor_R() {
}

/**
 * Adaptor_R - C
 */
BeginAdaptor_R* BeginAdaptor_R_new() {
	return new BeginAdaptor_R();
}

EndAdaptor_R* EndAdaptor_R_new() {
	return new EndAdaptor_R();
}

int Component_R_isBeginAdaptor(Component_R* component) {
	if (dynamic_cast<BeginAdaptor_R*>(component) != NULL) {
		return 1;
	} else {
		return 0;
	}
}

MediumState* BeginAdaptor_R_getBeginState(BeginAdaptor_R* beginAdaptor) {
	return beginAdaptor->getBeginState();
}

void EndAdaptor_R_setRegulatingSignal(EndAdaptor_R* endAdaptor, double regulatingSignal) {
	if (regulatingSignal > 0) {
		endAdaptor->openFlow();
	} else {
		endAdaptor->closeFlow();
	}
}
