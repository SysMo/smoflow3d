/*
 * MathDeclarations.h
 *
 *  Created on: Aug 1, 2013
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

#ifndef MATHDECLARATIONS_H_
#define MATHDECLARATIONS_H_

#include <cmath>
#include <limits>

namespace smoflow {
namespace m {

	// Constants
	static const double pi = 3.1415927;

	inline double eps() {
		return std::numeric_limits<double>::epsilon();
	}

	inline double pow(const double& x, const double& y) {
		return std::pow(x, y);
	}

	inline double pow(const double& x, const int& y) {
		return std::pow(x, y);
	}

	inline double sqrt(const double& x) {
		return std::sqrt((long double) x);
	}

	inline double log(const double& x) {
		return std::log((long double) x);
	}

	inline double log10(const double& x) {
		return std::log10((long double) x);
	}

	inline double fabs(const double& x) {
		return std::fabs((long double) x);
	}

	inline double max(const double &a, const double &b) {
		return b > a ? b : a;
	}

	inline double min(const double &a, const double &b) {
		return b < a ? b : a;
	}

	inline double sign(const double &a, const double &b) {
		return (b >= 0 ? (a >= 0 ? a : -a) : (a >= 0 ? -a : a));
	}

	inline void limitVariable(double& variable, double minValue, double maxValue) {
		if (variable < minValue) {
			variable = minValue;
		} else if (variable > maxValue) {
			variable = maxValue;
		}
	}

	/* Trigonometric functions */
	inline double cos(const double& x) {
		return std::cos((long double) x);
	}
	inline double sin(const double& x) {
		return std::sin((long double) x);
	}
	inline double tan(const double& x) {
		return std::tan((long double) x);
	}
	inline double cosh(const double& x) {
		return std::cosh((long double) x);
	}
	inline double tanh(const double& x) {
		return std::tanh((long double) x);
	}

}
}

#endif /* MATHDECLARATIONS_H_ */
