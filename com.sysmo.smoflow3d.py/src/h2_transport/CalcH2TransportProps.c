#include <math.h>
#include <stdio.h>
#include "CalcH2TransportProps.h"

double viscosity_Trho (double T, double rho) {
	double viscosity;
	static const double dgv[] = {
			-.1802037993618E+04, .3111075514590E+04, -.2247037886246E+04,
			.8857940661235E+03, -.2090706479771E+03, .3050376698249E+02,
			-.2640005961675E+01, .1270278679308E+00, -.2611834393975E-02,
	};
	static const double fvc[] = {
			-.1402007673681E+02, .1037805196987E+01, .1058204125616E+01,
			   .2856510589958E+03
	};
	static const double evc[] = {
			-.1390378322784E+02,  -.1079988460118E+01,   .2085176101583E+02,
			-.1303662005733E+03,  -.9527616400889E+02,  -.2188376933451E+01,
			.7399227724603E+02,   .2180138948638E-01
	};

	double diluteGasViscosity = 0;
	double tf = pow(T, 1./3);
	// tff = 1 / tf**4
	double tff = 1./tf;
	tff *= tff;
	tff *= tff;

	for (int i = 0; i < 9; i++) {
		tff *= tf;
		diluteGasViscosity += dgv[i] * tff;
	}

	double densityCorrectionViscosity;
	double d1 = fvc[2] - log(T / fvc[3]);
	densityCorrectionViscosity = (fvc[0] + fvc[1] * d1 * d1) * rho;

	double excessViscosity = 0;
	double r2 = sqrt(rho) * ((rho - evc[7])/(evc[7]));
	double r = pow(rho, 0.1);
	double x = evc[0] + evc[1] * r2 + evc[2]* r
			+ (evc[3] * r2/T + evc[4] * r / sqrt(T)
					+ evc[5] + evc[6] * r2) / T;
	double x1 = evc[0] + evc[5] / T;
	excessViscosity = exp(x) - exp(x1);

	viscosity = 1e-6 * (diluteGasViscosity + densityCorrectionViscosity
			+ excessViscosity);
	//printf("Dilute gas viscosity: %e\n", diluteGasViscosity);
	//printf("Viscosity density correction: %e\n", densityCorrectionViscosity);
	//printf("Excess viscosity: %e\n", excessViscosity);
	return viscosity;
}

double thermalConductivity_Trho (double T, double rho) {
	double thermalConductivity = 0;

	static const double dgc[] = {
		-.2633914469098E+04, .5171968972149E+04, -.4362593863150E+04,
		.2061546648109E+04, -.5960706319073E+03, .1078532576512E+03,
		-.1191575825713E+02, .7349232451540E+00, -.1938126709603E-01
	};
	static const double fcc[] = {
	   .3240015073128E+00, .5818893460273E-02, -.5894372682930E+01,
	   .2928193900206E+03
	};
	static const double ecc[] = {
	  -.1635948767861E+02, .3741426344309E+00, .1823588544776E+02,
	   .3429129395259E+02, .1398979978642E+03,  -.3624394840949E+02,
	  -.6696701230501E+01, .9621511056600E-02

	};

	double diluteGasLambda;
	double tf = pow(T, 1./3);
	// tff = 1 / tf**4
	double tff = 1./tf;
	tff *= tff;
	tff *= tff;
	for (int i = 0; i < 9; i++) {
		tff *= tf;
		diluteGasLambda += dgc[i] * tff;
	}

	double densityCorrection;
	double d1 = fcc[2] - log(T / fcc[3]);
	densityCorrection = (fcc[0] + fcc[1] * d1 * d1) * rho;

	double excessLambda;
	double r2 = sqrt(rho) * ((rho - ecc[7])/(ecc[7]));
	double r = pow(rho, 0.1);
	double x = ecc[0] + ecc[1] * r2 + ecc[2]* r
			+ (ecc[3] * r2 / T + ecc[4] * r / sqrt(T)
					+ ecc[5] + ecc[6] * r2) / T;
	double x1 = ecc[0] + ecc[5] / T;
	excessLambda = exp(x) - exp(x1);

	// TODO critical enhancement for thermal conductivity
	double criticalEnhancement;

	thermalConductivity = diluteGasLambda + densityCorrection
			+ excessLambda + criticalEnhancement;
	return thermalConductivity;
}
