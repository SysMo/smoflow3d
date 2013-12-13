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
#include <math.h>

namespace smoflow {

namespace cst {
	const double StandardPressure = 1e5; // [Pa]
	const double StandardTemperature = 288.15; // [K]

	const double MinPressureDrop = 1e-06; // [Pa]
	const double zeroPressureDrop = 0.0; // [Pa]
	const double zeroPressure = 0.0; // [Pa]
	const double MinMassFlowRate = 1e-12; // [kg/s]
	const double zeroMassFlowRate = 0.0; // [kg/s]

	const double RGas = 8.3144621; // [J/mol-K]
	const double N_a = 6.02e23; // Particles per mole
	const double StefanBoltzmannConstant = 5.67e-8; // Stefan Boltzmann Constant [W/(m^2*K^4)]
	const double earthAcceleration = 9.81; // [m/s^2]
} /* end namespace cst */

namespace m {
	// Constants
	static const double pi = 3.1415927;
	static const double NaN = NAN;
	static const double Inf = INFINITY;
	static const double eps = std::numeric_limits<double>::epsilon();

	inline bool isNaN(double value) {
		return std::isnan(value);
	}
	inline bool isPlusInf(double value) {
		return value == Inf;
	}
	inline bool isMinusInf(double value) {
		return value == -Inf;
	}
	inline bool isInf(double value) {
		return ((value == Inf) || (value == -Inf));
	}
	inline bool isNumber(double value) {
		return !(isNaN(value) || isInf(value));
	}

	inline bool isValueInsideInterval(const double& value, double intervalEnd1, double intervalEnd2) {
		if (intervalEnd1 > intervalEnd2) {
			std::swap<double>(intervalEnd1, intervalEnd2);
		}

		return intervalEnd1 < value && value < intervalEnd2;
	}

	inline bool isEqualFloat(double x, double y) {
		long double diff = x - y;
		return (std::fabs(diff) < 5 * m::eps);
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

	inline double exp(const double& x) {
		return std::exp((long double) x);
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

	inline double max(const double& a, const double& b) {
		return b > a ? b : a;
	}

	inline double min(const double& a, const double& b) {
		return b < a ? b : a;
	}

	inline double sign(const double& a, const double& b) {
		return (b >= 0 ? (a >= 0 ? a : -a) : (a >= 0 ? -a : a));
	}

	inline double quadratic_mean(const double& a, const double& b) {
		return sqrt((a*a + b*b)/2.);
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
} /* end namespace m */
} /* end namespace smoflow */

#endif /* MATHDECLARATIONS_H_ */
