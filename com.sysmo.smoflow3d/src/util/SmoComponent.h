/*
 * SmoComponent.h
 *
 *  Created on: Aug 6, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#ifndef SMOCOMPONENT_H_
#define SMOCOMPONENT_H_

struct SmoComponent {
	SmoComponent* parent;
	virtual ~SmoComponent(){}
};

#endif /* SMOCOMPONENT_H_ */
