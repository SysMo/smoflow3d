/*
 * CachedProperty.cpp
 *
 *  Created on: Jul 28, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "CachedProperty.h"
#include "CommonDefinitions.h"

CachedProperty::CachedProperty() {
	clear();
}

void CachedProperty::operator=( const double& value){
	this->value = value;
	this->is_cached = true;
};

CachedProperty::operator bool() const {
	return is_cached;
}

CachedProperty::operator double() const {
	return value;
}

void CachedProperty::clear(){
	is_cached = false;
	this->value = _HUGE;
}

