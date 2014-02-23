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


#define SMOCOMPONENT_SET_PROPS(_component) \
	SmoComponent_setInstanceIndex(_component, *n); \
	SmoComponent_setComponentName(_component, _SUBMODELNAME_); \


#define SMOCOMPONENT_PRINT
#ifdef SMOCOMPONENT_PRINT
#define SMOCOMPONENT_PRINT_MAIN_CALC \
	amefprintf(stderr, "\n%s instance %d - main_calc \n", _SUBMODELNAME_, *n);

#define SMOCOMPONENt_PRINT_MACRO \
	amefprintf(stderr, "\n%s instance %d - macro \n", _SUBMODELNAME_, *n);

#define SMOCOMPONENt_PRINT_MACRO_MSG(message) \
	amefprintf(stderr, "\n%s instance %d - macro (%s)\n", _SUBMODELNAME_, *n, message);
#else
#define SMOCOMPONENT_PRINT_MAIN_CALC (void)0;
#define SMOCOMPONENt_PRINT_MACRO (void)0;
#define SMOCOMPONENt_PRINT_MACRO_MSG(message) (void)0;
#endif /* SMOCOMPONENT_PRINT */


#endif /* SMOFLOWAME_H_ */
