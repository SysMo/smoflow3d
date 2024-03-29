/*
 * Macros.h
 *
 *  Created on: Sep 5, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#ifndef MACROS_H_
#define MACROS_H_

/** Header macro declarations */

#ifdef __cplusplus
#define BEGIN_C_LINKAGE extern "C" {
#define END_C_LINKAGE }
#else
#define BEGIN_C_LINKAGE
#define END_C_LINKAGE
#endif //__cplusplus

#ifdef HUGE_VAL
#  define _HUGE HUGE_VAL
#else
// GCC Version of huge value macro
#ifdef HUGE
#  define _HUGE HUGE
#endif
#endif

#define DECLARE_C_STRUCT(name) \
	typedef struct name##Struct name; \

#define JOIN_STR(a, b, sep) a##sep##b
#define FULL_FUNC_NAME(a, b) JOIN_STR(a, b, _)
#define KOMPONENT_FUNC(RET_TYPE, FUNC_NAME, ...) \
		RET_TYPE FULL_FUNC_NAME(KOMPONENT, FUNC_NAME)(KOMPONENT* component, __VA_ARGS__)
#define KOMPONENT_FUNC_V(RET_TYPE, FUNC_NAME) \
		RET_TYPE FULL_FUNC_NAME(KOMPONENT, FUNC_NAME)(KOMPONENT* component)

/**
 * Warnings, errors, exceptions
 */

#ifdef __cplusplus

#define ShowMessage(message) \
	std::stringstream messageStream; \
	messageStream << "\n" << message; \
	std::string messageString(messageStream.str()); \
	SimulationEnvironment_message(messageString.c_str());

#define _RaiseEvent(message, _HANDLER) \
	std::stringstream messageStream; \
	messageStream << "\n" << \
	"--------------------------------------------------\n" << \
	"--------------------------------------------------\n" << \
	"Event: " << message << "\n" << \
	"File: " << __FILE__ << "\n" << \
	"Function: " << __FUNCTION__ << "\n" << \
	"Line: " << __LINE__ << "\n" << \
	"--------------------------------------------------\n"; \
	std::string messageString(messageStream.str()); \
	_HANDLER(messageString.c_str()); \

#define RaiseError(message) \
	{ \
	_RaiseEvent(message, SimulationEnvironment_error) \
	throw -1; \
	} \

#define RaiseWarning(message) \
	{ \
	_RaiseEvent(message, SimulationEnvironment_warning) \
	} \


#define RaiseComponentError(component, message) \
	{ \
		std::stringstream messageStream; \
		messageStream << "\n" << \
		"--------------------------------------------------\n" << \
		"--------------------------------------------------\n" << \
		"Critical error: " << message << "\n" << \
		"File: " << __FILE__ << "\n" << \
		"Function: " << __FUNCTION__ << "\n" << \
		"Line: " << __LINE__ << "\n" << \
		"Component: " << SimulationEnvironment_getComponentId(component) << "\n" << \
		"--------------------------------------------------\n"; \
		std::string messageString(messageStream.str()); \
		SimulationEnvironment_error(messageString.c_str()); \
		throw -1; \
	} \

// Assert macros
#define AssertInComponent(assert_statement, component) \
	if (!(assert_statement)) { \
		RaiseComponentError(component, "ASSERT FAIL: " << #assert_statement);\
	} \

#define Assert(assert_statement) \
	if (!(assert_statement)) { \
		RaiseError("ASSERT FAIL: " << #assert_statement);\
	} \

// Macro for defining an exception object for a unimplemented function.
#define RaiseError_UnimplementedFunction() \
	RaiseError("The '" << std::string(typeid(*this).name()) << "' class doesn't implement '" << __FUNCTION__ << "' function.");

// Macro for defining a base exception object.
#define ThrowSpecificException(message, ExceptionClass) \
	{ \
	std::stringstream errorStream; \
	errorStream << "\n" << \
	"--------------------------------------------------\n" << \
	"--------------------------------------------------\n" << \
	"ERROR: " << message << "\n" << \
	"File: " << __FILE__ << "\n" << \
	"Function: " << __FUNCTION__ << "\n" << \
	"Line: " << __LINE__ << "\n" << \
	"--------------------------------------------------\n"; \
	ExceptionClass smoError(errorStream.str()); \
	throw smoError;  \
	}

/**
 * SmoComponent
 */
#define SMOCOMPONENT_SET_PARENT(_component, _parent) \
	_component->parent = _parent

#define SMOOBJECT_SET_PARENT(_object, _parent) \
	_object->parent = _parent

#define SMOOBJECT_SET_PARENT_COMPONENT(_object, _parent) \
	_object->parentComponent = _parent

#endif //__cplusplus


#endif /* MACROS_H_ */
