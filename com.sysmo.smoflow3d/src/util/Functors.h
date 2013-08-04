/*
 * Functors.h
 *
 *  Created on: Jul 31, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#ifndef FUNCTORS_H_
#define FUNCTORS_H_

#include "util/CommonDefinitions.h"

#ifdef __cplusplus

class FunctorOneVariable {
public:
	virtual double operator()(double value) = 0;
	virtual ~FunctorOneVariable(){}
};

class FunctorTwoVariables {
public:
	virtual double operator()(double value1, double value2) = 0;
	virtual ~FunctorTwoVariables(){}
};


#else //__cplusplus
DECLARE_C_STRUCT(FunctorOneVariable)
DECLARE_C_STRUCT(FunctorTwoVariables)
#endif //__cplusplus

BEGIN_C_LINKAGE

FunctorOneVariable* FunctorOneVariable_Expression_new(const char* expressionString,
		const char* varName);
double FunctorOneVariable_evaluate(FunctorOneVariable* functor, double value);

FunctorTwoVariables* FunctorTwoVariables_Constant_new(double constantValue);
FunctorTwoVariables* FunctorTwoVariables_Expression_new(const char* expressionString,
		const char* var1Name, const char* var2Name);
double FunctorTwoVariables_evaluate(FunctorTwoVariables* functor, double value1, double value2);
END_C_LINKAGE

#endif /* FUNCTORS_H_ */
