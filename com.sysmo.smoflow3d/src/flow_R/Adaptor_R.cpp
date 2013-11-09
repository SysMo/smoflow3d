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


/**
 * Adaptor_R - C
 */
BeginAdaptor_R* BeginAdaptor_R_new() {
	return new BeginAdaptor_R();
}

EndAdaptor_R* EndAdaptor_R_new() {
	return new EndAdaptor_R();
}
