/*
 * Interpolators.h
 *
 *  Created on: Aug 7, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#ifndef INTERPOLATORS_H_
#define INTERPOLATORS_H_

#include "util/CommonDefinitions.h"
#include "Functors.h"

#ifdef __cplusplus

enum InterpolationBoundaryHandling {
	ibhConstant = 0,
	ibhConstantSlope = 1
};

#include "Eigen/Core"
using namespace Eigen;

class Interpolator1D : public FunctorOneVariable {

struct Interpolator1DCache : public FunctorCache {
	size_t cacheIndex;
};
public:
	Interpolator1D(ArrayXd* xValues, ArrayXd* yValues, bool copyValues = true,
			size_t interpolationOrder = 2, InterpolationBoundaryHandling boundaryHandling = ibhConstant);

	virtual ~Interpolator1D();
	virtual double operator()(double value, FunctorCache* cache);
	virtual FunctorCache* createCache();
protected:
	size_t hunt(double xValue, Interpolator1DCache* cache);
	double rawInterp(size_t xIndex, double value);

	bool keepValues;
	ArrayXd* xValues;
	ArrayXd* yValues;

	size_t numValues;
	size_t interpolationOrder;
	InterpolationBoundaryHandling boundaryHandling;

};

#else //__cplusplus
DECLARE_C_STRUCT(Interpolator1D)
#endif //__cplusplus

#endif /* INTERPOLATORS_H_ */
