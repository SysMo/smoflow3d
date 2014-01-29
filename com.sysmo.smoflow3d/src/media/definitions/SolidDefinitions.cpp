/*
 * SolidDefinitions.cpp
 *
 *  Created on: Aug 7, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "util/String.h"
#include "io_control/CSVProcessor.h"
#include "SolidDefinitions.h"
#include "math/Interpolators.h"
#include "Eigen/Core"
using namespace Eigen;

namespace solids {

Aluminium6061::Aluminium6061() {
	name = "Aluminium6061";

	const double numValues = 12;
    ArrayXd TValues(numValues);
    TValues << 20.0 , 50.0 , 75.0 , 100.0 , 125.0 , 150.0 , 175.0 , 200.0 , 225.0 , 250.0 , 275.0 , 300.0;

    double rhoValue = 2700.0;
    densityFunction = FunctorOneVariable_Constant_new(rhoValue);

    ArrayXd cpValues(numValues);
    cpValues << 8.85 , 148.84 , 334.15 , 492.2 , 616.63 , 713.03 , 784.783 , 835.24 , 869.61 , 895.04 , 920.01 , 953.86;
    heatCapacityFunction = new Interpolator1D(&TValues, &cpValues);

    ArrayXd lambdaValues(numValues);
    lambdaValues << 28.47 , 62.14 , 82.26 , 97.84 , 110.31 , 120.54 , 129.05 , 136.22 , 142.3 , 147.46 , 151.84 , 155.54;
    thermalConductivityFunction = new Interpolator1D(&TValues, &lambdaValues);

	ArrayXd enthalpyValues(numValues);
	enthalpyValues << 0.0, 2365.35, 8402.73, 18732.1, 32592.47, 49213.22, 67935.89, 88186.18, 109496.8, 131554.92, 154243.05, 177666.42;
	enthalpyFunction = new Interpolator1D(&TValues, &enthalpyValues);
}

StainlessSteel304::StainlessSteel304() {
	name = "StainlessSteel304";

	const double numValues = 12;

	ArrayXd TValues(numValues);
	TValues << 20.0 , 50.0 , 75.0 , 100.0 , 125.0 , 150.0 , 175.0 , 200.0 , 225.0 , 250.0 , 275.0 , 300.0;

	double rhoValue = 7800.0;
	densityFunction = FunctorOneVariable_Constant_new(rhoValue);

	ArrayXd cpValues(numValues);
	cpValues << 12.6, 100, 182, 250, 300, 347, 388, 419, 432, 439, 445, 477;
	heatCapacityFunction = new Interpolator1D(&TValues, &cpValues);

	ArrayXd lambdaValues(numValues);
	lambdaValues << 1.95, 5.8, 7.94, 9.4, 10.6, 11.5, 12.3, 13, 13.6, 14.1, 14.5, 14.9;
	thermalConductivityFunction = new Interpolator1D(&TValues, &lambdaValues);

	ArrayXd enthalpyValues(numValues);
	enthalpyValues <<0.0, 1689.0, 5214.0, 10614.0, 17489.0, 25576.5, 34764.0, 44851.5, 55489.0, 66376.5, 77426.5, 88951.5;
	enthalpyFunction = new Interpolator1D(&TValues, &enthalpyValues);
}

CarbonFiberComposite::CarbonFiberComposite() {
	name = "CarbonFiberComposite";

	const double numValues = 12;

	ArrayXd TValues(numValues);
	TValues << 20.0 , 50.0 , 75.0 , 100.0 , 125.0 , 150.0 , 175.0 , 200.0 , 225.0 , 250.0 , 275.0 , 300.0;

	double rhoValue = 1810.0;
	densityFunction = FunctorOneVariable_Constant_new(rhoValue);

	ArrayXd cpValues(numValues);
	cpValues << 0.05, 75.53, 197.91, 309.65, 410.77, 501.26, 581.13, 650.38, 709.0, 757.0, 794.36, 821.11;
	heatCapacityFunction = new Interpolator1D(&TValues, &cpValues);

	ArrayXd lambdaValues(numValues);
	lambdaValues << 0.06, 0.19, 0.31, 0.42, 0.51, 0.58, 0.63, 0.66, 0.68, 0.69, 0.7, 0.71;
	thermalConductivityFunction = new Interpolator1D(&TValues, &lambdaValues);

	ArrayXd enthalpyValues(numValues);
	enthalpyValues << 0.0, 1133.7, 4551.7, 10896.2, 19901.45, 31301.82, 44831.7, 60225.57, 77217.82, 95542.82, 114934.83, 135128.2;
	enthalpyFunction = new Interpolator1D(&TValues, &enthalpyValues);
}

GlassFiberComposite::GlassFiberComposite() {
	name = "GlassFiberComposite";

	const double numValues = 12;

	ArrayXd TValues(numValues);
	TValues << 20.0 , 50.0 , 75.0 , 100.0 , 125.0 , 150.0 , 175.0 , 200.0 , 225.0 , 250.0 , 275.0 , 300.0;

	double rhoValue = 1800.0;
	densityFunction = FunctorOneVariable_Constant_new(rhoValue);

	ArrayXd cpValues(numValues);
	cpValues << 47.0, 149.0, 233.0, 317.0, 401.0, 500.0, 577.0, 665.0, 750.0, 836.0, 920.0, 1000.0;
	heatCapacityFunction = new Interpolator1D(&TValues, &cpValues);

	ArrayXd lambdaValues(numValues);
	lambdaValues << 0.15, 0.24, 0.31, 0.38, 0.43, 0.48, 0.51, 0.55, 0.59, 0.63, 0.67, 0.71;
	thermalConductivityFunction = new Interpolator1D(&TValues, &lambdaValues);

	ArrayXd enthalpyValues(numValues);
	enthalpyValues << 0.0, 2940.0, 7715.0, 14590.0, 23565.0, 34827.5, 48290.0, 63815.0, 81502.5, 101327.5, 123277.5, 147277.5;
	enthalpyFunction = new Interpolator1D(&TValues, &enthalpyValues);
}

HighDensityPolyethylene::HighDensityPolyethylene() {
	name = "HighDensityPolyethylene";

	const double numValues = 15;

	ArrayXd TValues(numValues);
	TValues << 223.15, 233.15, 243.15, 253.15, 263.15, 273.15, 283.15, 293.15, 303.15, 313.15, 323.15, 333.15, 343.15, 353.15, 363.15;

	double rhoValue = 945.0;
	densityFunction = FunctorOneVariable_Constant_new(rhoValue);

	double cpValue = 2000.0;
	heatCapacityFunction = FunctorOneVariable_Constant_new(cpValue);

	ArrayXd lambdaValues(numValues);
	lambdaValues << 0.76148, 0.75348, 0.74548, 0.73748, 0.72948, 0.72148, 0.71348, 0.70548, 0.69748, 0.68948, 0.68148, 0.67348, 0.66548, 0.65748, 0.64948;
	thermalConductivityFunction = new Interpolator1D(&TValues, &lambdaValues);

	ArrayXd TValues_h(2);
	TValues_h << 0.0, 400.0;

	ArrayXd enthalpyValues(2);
	enthalpyValues << 0.0, 800000.0;
	enthalpyFunction = new Interpolator1D(&TValues_h, &enthalpyValues, true, 2, ibhConstantSlope);
}

ArmaflexLTD::ArmaflexLTD() {
	name = "ArmaflexLTD";

	const double numValues = 7;

	ArrayXd TValues(numValues);
	TValues << 93.15, 173.15, 223.15, 273.15, 323.15, 373.15, 383.15;

	double rhoValue = 70.0;
	densityFunction = FunctorOneVariable_Constant_new(rhoValue);

	double cpValue = 2000.0; //:TRICKY: this value is only a guess
	heatCapacityFunction = FunctorOneVariable_Constant_new(cpValue);

	ArrayXd lambdaValues(numValues);
	lambdaValues << 0.0307, 0.0390, 0.0395, 0.0400, 0.0435, 0.0530, 0.0559;
	thermalConductivityFunction = new Interpolator1D(&TValues, &lambdaValues);

	ArrayXd TValues_h(2);
	TValues_h << 0, 400;

	ArrayXd enthalpyValues(2);
	enthalpyValues << 0.0, 800000.0;
	enthalpyFunction = new Interpolator1D(&TValues_h, &enthalpyValues, true, 2, ibhConstantSlope);
}

ArmaflexAF::ArmaflexAF() {
	name = "ArmaflexAF";

	const double numValues = 7;

	ArrayXd TValues(numValues);
	TValues << 93.15, 173.15, 223.15, 273.15, 323.15, 373.15, 383.15;

	double rhoValue = 50.0;
	densityFunction = FunctorOneVariable_Constant_new(rhoValue);

	double cpValue = 2000.0; //:TRICKY: this value is only a guess
	heatCapacityFunction = FunctorOneVariable_Constant_new(cpValue);

	ArrayXd lambdaValues(numValues);
	lambdaValues << 0.044, 0.034, 0.033, 0.036, 0.043, 0.054, 0.057;
	thermalConductivityFunction = new Interpolator1D(&TValues, &lambdaValues);

	ArrayXd TValues_h(2);
	TValues_h << 0, 400;

	ArrayXd enthalpyValues(2);
	enthalpyValues << 0.0, 800000.0;
	enthalpyFunction = new Interpolator1D(&TValues_h, &enthalpyValues, true, 2, ibhConstantSlope);
}

SolidConstProps::SolidConstProps(
		const char* solidName,
		double density,
		double thermalConductivity,
		double heatCapacity,
		double enthalpy) {
	name = solidName;

	densityFunction = FunctorOneVariable_Constant_new(density);
	heatCapacityFunction = FunctorOneVariable_Constant_new(heatCapacity);
	thermalConductivityFunction = FunctorOneVariable_Constant_new(thermalConductivity);
	enthalpyFunction = FunctorOneVariable_Constant_new(enthalpy);
}

void setDataFromCsvFile(const char* csvFile, FunctorOneVariable** functor) {
	CSVProcessor csv;
	VectorFloat vecTemperature;
	csv.addFloatColumn(vecTemperature);
	VectorFloat vecValue;
	csv.addFloatColumn(vecValue);
	String fileName(csvFile);
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

SolidUserDefined::SolidUserDefined(
		const char* solidName,
		const char* density,
		const char* thermalConductivity,
		const char* heatCapacity,
		const char* enthalpy) {
	name = solidName;

	double densityConstValue;
	if (smoflow::String::toDouble(density, &densityConstValue)) {
		densityFunction = FunctorOneVariable_Constant_new(densityConstValue);
	} else {
		setDataFromCsvFile(density, &densityFunction);
	}

	double heatCapacityConstValue;
	if (smoflow::String::toDouble(heatCapacity, &heatCapacityConstValue)) {
		heatCapacityFunction = FunctorOneVariable_Constant_new(heatCapacityConstValue);
	} else {
		setDataFromCsvFile(heatCapacity, &heatCapacityFunction);
	}

	double thermalConductivityConstValue;
	if (smoflow::String::toDouble(thermalConductivity, &thermalConductivityConstValue)) {
		thermalConductivityFunction = FunctorOneVariable_Constant_new(thermalConductivityConstValue);
	} else {
		setDataFromCsvFile(thermalConductivity, &thermalConductivityFunction);
	}

	double enthalpyConstValue;
	if (smoflow::String::toDouble(enthalpy, &enthalpyConstValue)) {
		enthalpyFunction = FunctorOneVariable_Constant_new(enthalpyConstValue);
	} else {
		setDataFromCsvFile(enthalpy, &enthalpyFunction);
	}
}

} //end namespace solids
