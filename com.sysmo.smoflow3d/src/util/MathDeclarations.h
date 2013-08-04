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

//
// Defines
//
#define POW(x, y) std::pow((long double) x, (long double) y)
#define FABS(x) std::fabs((long double) x)
#define SQRT(x) std::sqrt((long double) x)

inline double pow(double x, double y) {
	return std::pow(x, y);
}

//
// Macro-like inline functions
//
template<class T>
inline T SQR(const T a) {
	return a * a;
}

template<class T>
inline const T &MAX(const T &a, const T &b) {
	return b > a ? (b) : (a);
}

inline float MAX(const double &a, const float &b) {
	return b > a ? (b) : float(a);
}

inline float MAX(const float &a, const double &b) {
	return b > a ? float(b) : (a);
}

template<class T>
inline const T &MIN(const T &a, const T &b) {
	return b < a ? (b) : (a);
}

inline float MIN(const double &a, const float &b) {
	return b < a ? (b) : float(a);
}

inline float MIN(const float &a, const double &b) {
	return b < a ? float(b) : (a);
}

template<class T>
inline T SIGN(const T &a, const T &b) {
	return b >= 0 ? (a >= 0 ? a : -a) : (a >= 0 ? -a : a);
}

inline float SIGN(const float &a, const double &b) {
	return b >= 0 ? (a >= 0 ? a : -a) : (a >= 0 ? -a : a);
}

inline float SIGN(const double &a, const float &b) {
	return (float) (b >= 0 ? (a >= 0 ? a : -a) : (a >= 0 ? -a : a));
}

template<class T>
inline void SWAP(T &a, T &b) {
	T dum = a;
	a = b;
	b = dum;
}

#endif /* MATHDECLARATIONS_H_ */
