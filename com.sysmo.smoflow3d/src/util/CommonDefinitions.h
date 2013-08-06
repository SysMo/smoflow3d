/*
 * CommonDeclarations.h
 *
 *  Created on: Jan 9, 2013
 *     Author: Atanas Pavlov
 *  Revisions:
 *
 *  Copyright: SysMo Ltd.,
 *             Klokotnitza 9A str., ap. 9
 *             Gabrovo 5300, Bulgaria
 *
 *    License: See License.txt in top level directory.
 *             If no licence file was distributed, contact SysMo Ltd.
 */
#ifndef COMMONDECLARATIONS_H_
#define COMMONDECLARATIONS_H_

/***************************************
 * BEGIN C interface
 **************************************/
#include <math.h>

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

#include "CoolProp/GlobalConstants.h"
typedef enum params ThermodynamicVariable;

/***************************************
 * END C interface
 **************************************/

/**************************************
 * BEGIN C++ definitions
 **************************************/
#ifdef __cplusplus

#include <string>
#include <typeinfo>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <limits>
#include <stdexcept>
#include <memory>
#include <cmath>
#include <algorithm>
#include <assert.h>


#include "SmoComponent.h"

typedef double Real;
typedef int Integer;
typedef bool Boolean;
typedef unsigned int Natural;



/**
 * 1) Types
 */
typedef std::string String;
typedef std::vector<Real> RealVector;
typedef Real* RealFunction(Real);



/**
 * 2) Constants
 */
//namespace smoflow {
namespace cst {
//	const Real RGas = 8.3144621; // J/mol-K
//	const Real N_a = 6.02e23; // Particles per mole
	const Real StandardPressure = 1e5; // Pa
//	const Real StandardTemperature = 293.15; // K
//
//	const double StefanBoltzmannConstant = 5.67e-8; // Stefan Boltzmann Constant [W/(m^2*K^4)]
//	const double Pi = 4 * std::atan(1.0f);
//	const double earthAcceleration = 9.81; // [m/s^2]
}
//}



/**
 * 3) Special numbers
 */
/*namespace smoflow {
	inline Real plusInfinity() {
		return std::numeric_limits<Real>::infinity();
	}
	inline Real minusInfinity() {
		return -std::numeric_limits<Real>::infinity();
	}
	inline Real nan() {
		return std::numeric_limits<Real>::quiet_NaN();
	}
}*/



/**
 * 4) Exceptions & asserts
 */
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
	String str(errorStream.str()); \
	throw smoError;  \
	}


//{throw -1;} //:TRICKY: this line remove some warnings and will never be reached

#define RaiseError(message) \
	ThrowSpecificException (message, std::runtime_error)

// Macro for defining an exception object for a unimplemented function.
#define RaiseError_UnimplementedFunction() \
	RaiseError("The '" << std::string(typeid(*this).name()) << "' class doesn't implement '" << __FUNCTION__ << "' function.");

// Asserts
#define assert_h5(h5_herr) assert(h5_herr >= 0)


/**
 * 6) Math
 */
#include "math/MathDefinitions.h"


/**
 * 7) File operations
 */
#define COPY_FILE(sourceFile, destinationFile) \
{ \
	std::ifstream _source(sourceFile, std::ios::binary); \
	std::ofstream _dest(destinationFile, std::ios::binary); \
	_dest << _source.rdbuf(); \
	_source.close(); \
	_dest.close(); \
}


/**
 * 8) String
 */
#define str_EndsWith(s, suffix) \
	s.rfind(suffix) == (s.size()-suffix.size())



#endif //__cplusplus
/**************************************
 * END C++ definitions
 **************************************/


#endif /* COMMONDECLARATIONS_H_ */
