/*
 * Interpolators.cpp
 *
 *  Created on: Aug 7, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "Interpolators.h"
#include "io_control/CSVProcessor.h"
using namespace smoflow;

Interpolator1D::Interpolator1D(ArrayXd* xValues, ArrayXd* yValues, bool copyValues,
		size_t interpolationOrder, InterpolationBoundaryHandling boundaryHandling) {
	this->keepValues = copyValues;
	if (copyValues) {
		this->xValues = new ArrayXd(*xValues);
		this->yValues = new ArrayXd(*yValues);
	} else {
		this->xValues = xValues;
		this->yValues = yValues;
	}

	numValues = xValues->size();
	this->interpolationOrder = interpolationOrder;
	this->boundaryHandling = boundaryHandling;


}

Interpolator1D::~Interpolator1D() {
	if (keepValues) {
		delete xValues;
		delete yValues;
	}
}

FunctorCache* Interpolator1D::createCache() {
	// :SMO_TODO: (Nasko) Delete the cache object in destructor
	return new Interpolator1DCache();
}

void Interpolator1D::createFromCsvFile(const char* csvFile, FunctorOneVariable** functor) {
	CSVProcessor csv;
	VectorFloat vecTemperature;
	csv.addFloatColumn(vecTemperature);
	VectorFloat vecValue;
	csv.addFloatColumn(vecValue);
	std::string fileName(csvFile);
	csv.read(fileName, ',', 1);

	const double numValues = vecTemperature.size();
	ArrayXd arrTValues(numValues);
	ArrayXd arrValues(numValues);
	for (size_t i = 0; i < vecTemperature.size(); i++) {
		arrTValues(i) = vecTemperature.at(i);
		arrValues(i) = vecValue.at(i);
	}
	(*functor) = new Interpolator1D(&arrTValues, &arrValues);
}

size_t Interpolator1D::hunt(double xValue, Interpolator1DCache* cache) {
	size_t jl = cache->cacheIndex, jm, ju, inc = 1;
	if (numValues < 2 || interpolationOrder < 2 || interpolationOrder > numValues)
		throw("hunt size error");

	if (jl < 0 || jl > numValues - 1) {
		jl = 0;
		ju = numValues - 1;
	} else {
		if (xValue >= (*xValues)(jl)) {
			for (;;) {
				ju = jl + inc;
				if (ju >= numValues - 1) {
					ju = numValues - 1;
					break;
				} else if (xValue < (*xValues)(ju))
					break;
				else {
					jl = ju;
					inc += inc;
				}
			}
		} else {
			ju = jl;
			for (;;) {
				jl = jl - inc;
				if (jl <= 0) {
					jl = 0;
					break;
				} else if (xValue >= (*xValues)(jl))
					break;
				else {
					ju = jl;
					inc += inc;
				}
			}
		}
	}
	while (ju - jl > 1) {
		jm = (ju + jl) >> 1;
		if (xValue >= (*xValues)(jm))
			jl = jm;
		else
			ju = jm;
	}
	cache->cacheIndex = jl;
	return m::max(0, m::min(numValues - interpolationOrder, jl - ((interpolationOrder - 2) >> 1)));
}

double Interpolator1D::operator()(double value, FunctorCache* cache) {
	if (m::isNaN(value)) {
		RaiseError("Not-a-number value passesd to interpolator");
	}
	Interpolator1DCache* cacheObj = (Interpolator1DCache*) cache;
	double yValue;
	if (boundaryHandling == ibhConstant && value < (*xValues)(0)) {
		yValue = (*yValues)(0);
		cacheObj->cacheIndex = 0;
	} else if (boundaryHandling == ibhConstant && value > (*xValues)(numValues - 1)) {
		yValue = (*yValues)(numValues - 1);
		cacheObj->cacheIndex = numValues - 1;
	} else {
		size_t i = hunt(value, cacheObj);
		yValue = rawInterp(i, value);
	}
	return yValue;
}

double Interpolator1D::rawInterp(size_t xIndex, double xValue) {
	if ((*xValues)(xIndex) == (*xValues)(xIndex + 1))
		return (*yValues)(xIndex);
	else
		return (*yValues)(xIndex) + ((xValue - (*xValues)(xIndex))
				/ ((*xValues)(xIndex + 1) - (*xValues)(xIndex)))
				* ((*yValues)(xIndex + 1) - (*yValues)(xIndex));

}
