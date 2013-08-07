/*
 * Functors.cpp
 *
 *  Created on: Aug 4, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "math/Functors.h"
#include <sstream>

int main(int argc, char** argv) {
	std::cout << "Begin test" << std::endl;

	const char expr[] = "(4+x)*log(y)";
	FunctorTwoVariables* f1 = FunctorTwoVariables_Expression_new(expr, "x", "y");
	for (int i = 0; i < 20; i++) {
		double result = (*f1)(i, i);
		std::cout << "x = " << i << ", y = " << i << ", " << expr << " = " << result << std::endl;
	}

	std::cout << "End test" << std::endl;
	return 0;
}
