/*
 * SolidDefinitions.cpp
 *
 *  Created on: Aug 7, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "SolidDefinitions.h"
#include "math/Interpolators.h"
#include "Eigen/Core"
using namespace Eigen;

namespace solids {
Aluminium6061::Aluminium6061() {
	const double numValues = 12;
    ArrayXd TValues(numValues);
    ArrayXd cpValues(numValues);
    ArrayXd lambdaValues(numValues);
    //ArrayXd hValues(numValues);
    double rhoValue = 2700;
	TValues << 20.0 , 50.0 , 75.0 , 100.0 , 125.0 , 150.0 , 175.0 , 200.0 , 225.0 , 250.0 , 275.0 , 300.0;
    cpValues << 8.85 , 148.84 , 334.15 , 492.2 , 616.63 , 713.03 , 784.783 , 835.24 , 869.61 , 895.04 , 920.01 , 953.86;
    lambdaValues << 28.47 , 62.14 , 82.26 , 97.84 , 110.31 , 120.54 , 129.05 , 136.22 , 142.3 , 147.46 , 151.84 , 155.54;
    //hValues << 2365.35 , 8402.73 , 18732.1 , 32592.47 , 49213.22 , 67935.89 , 88186.18 , 109496.8 , 131554.92 , 154243.05 , 177666.42;

    densityFunction = FunctorOneVariable_Constant_new(rhoValue);
	thermalConductivityFunction = new Interpolator1D(&TValues, &lambdaValues);
	heatCapacityFunction = new Interpolator1D(&TValues, &cpValues);
}

}
