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

typedef std::vector<double> VectorFloat;
typedef std::vector<int> VectorInt;
typedef std::vector<String> VectorString;

#include "math/MathDefinitions.h"


#endif //__cplusplus
/**************************************
 * END C++ definitions
 **************************************/

#include "util/SmoComponent.h"
#include "SimulationEnvironment.h"


#endif /* COMMONDECLARATIONS_H_ */
