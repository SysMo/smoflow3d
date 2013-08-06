/*
 * Functors.cpp
 *
 *  Created on: Jul 31, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "Functors.h"

#include <string>
#include <vector>

class FunctorOneVariable_Constant : public FunctorOneVariable {
public:
	FunctorOneVariable_Constant(double value){this->value = value;}
	virtual double operator()(double value) {return this->value;}
protected:
	double value;
};

class FunctorTwoVariables_Constant : public FunctorTwoVariables {
public:
	FunctorTwoVariables_Constant(double value){this->value = value;}
	virtual double operator()(double value1, double value2) {return this->value;}
protected:
	double value;
};

#include "third-party/mu-parser/MuParser.h"
typedef mu::Parser ExprParser;

class MISOExpressionFunctor {
public:
	void init(const char* expressionString, std::vector<const char*> variableNames) {
		parser.SetExpr(_T(expressionString));
		size_t numVariables = variableNames.size();
		this->variableValues.resize(numVariables);
		for (size_t i = 0; i < numVariables; i++) {
			parser.DefineVar(_T(variableNames[i]), &variableValues[i]);
		}
	}
	double operator()(double variableValues[]) {
		for (size_t i = 0; i < this->variableValues.size(); i++) {
			this->variableValues[i] = variableValues[i];
		}
		double result;
		try {
			result = parser.Eval();
		} catch (mu::Parser::exception_type &evalException)	{
			RaiseError(evalException.GetMsg());
		}
		return result;
	}
protected:
	ExprParser parser;
	std::vector<double> variableValues;
};


class FunctorOneVariable_Expression : public FunctorOneVariable {
public:
	FunctorOneVariable_Expression(const char* expressionString,
			const char* varName) {
		std::vector<const char*> variableNames(1);
		variableNames[0] = varName;
		expressionFunctor.init(expressionString, variableNames);
	}
	virtual double operator()(double value) {
		return expressionFunctor(&value);
	}
protected:
	MISOExpressionFunctor expressionFunctor;
};

class FunctorTwoVariables_Expression : public FunctorTwoVariables {
public:
	FunctorTwoVariables_Expression(const char* expressionString,
			const char* var1Name, const char* var2Name) {
		std::vector<const char*> variableNames(2);
		variableNames[0] = var1Name;
		variableNames[1] = var2Name;
		expressionFunctor.init(expressionString, variableNames);
	}
	virtual double operator()(double value1, double value2) {
		double variableValues[2] = {value1, value2};
		return expressionFunctor(variableValues);
	}
protected:
	MISOExpressionFunctor expressionFunctor;
};

BEGIN_C_LINKAGE

FunctorOneVariable* FunctorOneVariable_Constant_new(double constantValue) {
	return new FunctorOneVariable_Constant(constantValue);
}

FunctorOneVariable* FunctorOneVariable_Expression_new(const char* expressionString,
		const char* varName) {
	return new FunctorOneVariable_Expression(expressionString, varName);
}

double FunctorOneVariable_evaluate(FunctorOneVariable* functor, double value) {
	return (*functor)(value);
}

FunctorTwoVariables* FunctorTwoVariables_Constant_new(double constantValue) {
	return new FunctorTwoVariables_Constant(constantValue);
}

FunctorTwoVariables* FunctorTwoVariables_Expression_new(const char* expressionString,
		const char* var1Name, const char* var2Name) {
	return new FunctorTwoVariables_Expression(expressionString, var1Name, var2Name);
}

double FunctorTwoVariables_evaluate(FunctorTwoVariables* functor, double value1, double value2) {
	return (*functor)(value1, value2);
}

END_C_LINKAGE
