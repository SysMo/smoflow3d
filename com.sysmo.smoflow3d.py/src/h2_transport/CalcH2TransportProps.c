#include <math.h>
#include <stdio.h>
#include "CalcH2TransportProps.h"

double viscosity_Trho (double T, double rho) {
	double viscosity;
	static const double dgvc[] = {
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
		diluteGasViscosity += dgvc[i] * tff;
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
