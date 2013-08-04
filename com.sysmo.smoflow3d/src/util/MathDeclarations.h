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

namespace smoflow {
namespace m {
	inline double pow(const double& x, const double& y) {
		return std::pow(x, y);
	}

	inline double sqrt(const double& x) {
		return std::sqrt((long double) x);
	}

	inline double fabs(const double& x) {
		return std::fabs((long double) x);
	}

	inline float max(const double &a, const float &b) {
		return b > a ? (b) : float(a);
	}

	inline float min(const double &a, const float &b) {
		return b < a ? (b) : float(a);
	}

	inline float sign(const double &a, const float &b) {
		return (float) (b >= 0 ? (a >= 0 ? a : -a) : (a >= 0 ? -a : a));
	}
}
}

#endif /* MATHDECLARATIONS_H_ */
