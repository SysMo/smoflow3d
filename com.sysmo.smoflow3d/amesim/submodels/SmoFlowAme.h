/*
 * SmoFlowAme.h
 *
 *  Created on: Aug 8, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#ifndef SMOFLOWAME_H_
#define SMOFLOWAME_H_

#define AME_RAISE_ERROR(msg) \
	amefprintf(stderr, "\n"msg"\n"); \
	amefprintf(stderr, "Fatal error in %s instance %d.\n", _SUBMODELNAME_, *n); \
	amefprintf(stderr, "Terminating the program.\n"); \
	AmeExit(1);		  \


#define SMOCOMPONEN_SET_PROPS(_component) \
	SmoComponent_setInstanceIndex(_component, *n); \
	SmoComponent_setComponentName(_component, _SUBMODELNAME_); \

#endif /* SMOFLOWAME_H_ */
