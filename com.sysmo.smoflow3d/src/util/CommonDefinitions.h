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
#include "CoolProp/GlobalConstants.h"
typedef enum params ThermodynamicVariable;

/***************************************
 * END C interface
 **************************************/

/* Macros */
#include "Macros.h"


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

/**
 * Types
 */

typedef std::string String;

/**
 * Constants
 */
namespace cst {
	const double RGas = 8.3144621; // J/mol-K
	const double N_a = 6.02e23; // Particles per mole
	const double StandardPressure = 1e5; // Pa
	const double StandardTemperature = 288.15; // K

	const double StefanBoltzmannConstant = 5.67e-8; // Stefan Boltzmann Constant [W/(m^2*K^4)]
	const double earthAcceleration = 9.81; // [m/s^2]
}

#include "math/MathDefinitions.h"


#endif //__cplusplus
/**************************************
 * END C++ definitions
 **************************************/

#include "util/SmoComponent.h"
#include "SimulationEnvironment.h"


#endif /* COMMONDECLARATIONS_H_ */
