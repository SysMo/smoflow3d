#include <math.h>
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

	double diluteGasViscosity = 0;
	double tf = pow(T, 1./3);
	double tff = pow(tf, -4);
	int i;
	for (i = 0; i < 9; i++) {
		tff *= tf;
		diluteGasViscosity += dgv[i] * tff;
	}

	double densityCorrectionViscosity;
	double d1 = fvc[2] - log(T / fvc[3]);
	densityCorrectionViscosity = (fvc[0] + fvc[1] * d1 * d1) * rho;

	double excessViscosity = ;



	viscosity = 1e-6 * (diluteGasViscosity + densityCorrectionViscosity
			+ excessViscosity);
	return viscosity;
}
