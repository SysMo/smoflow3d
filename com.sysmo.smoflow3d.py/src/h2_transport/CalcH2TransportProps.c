#include <math.h>
#include <stdio.h>
#include "CalcH2TransportProps.h"


inline double computeDiluteGasContribution(double T, const double dgc[9]) {
	double value = 0;
	double tf = pow(T, 1./3);
	double tff = pow(tf, -4);

	for (int i = 0; i < 9; i++) {
		tff *= tf;
		value += dgc[i] * tff;
	}
	return value;
}

inline double computeDensityCorrection(double T, double rho, const double dcc[4]) {
	double d1 = dcc[2] - log(T / dcc[3]);
	double value = (dcc[0] + dcc[1] * d1 * d1) * rho;
	return value;
}

inline double computeExcessContribution(double T, double rho, const double ecc[8]) {
	double r2 = sqrt(rho) * ((rho - ecc[7])/(ecc[7]));
	double r = pow(rho, 0.1);
	double x = ecc[0] + ecc[1] * r2 + ecc[2]* r
			+ (ecc[3] * r2/T + ecc[4] * r / sqrt(T)
					+ ecc[5] + ecc[6] * r2) / T;
	double x1 = ecc[0] + ecc[5] / T;
	double value = exp(x) - exp(x1);
	return value;
}

double ParaHydrogen_viscosity_Trho (double T, double rho) {
    // Convert density to g/cm^3
	rho /= 1000.0;

	static const double dgv[] = {
			-.1802037993618E+04,  .3111075514590E+04, -.2247037886246E+04,
			 .8857940661235E+03, -.2090706479771E+03,  .3050376698249E+02,
			-.2640005961675E+01,  .1270278679308E+00, -.2611834393975E-02,
	};

	static const double dgv_highT[] = {
			 .3597459516279E+06, -.2907864068495E+06,  .1010108273374E+06,
			-.1969542146586E+05,  .2357963788723E+04, -.1773345862550E+03,
			 .8211313268144E+01, -.2133279099683E+00,  .2385420317913E-02
	};

	static const double dcv[] = {
			-.1402007673681E+02, .1037805196987E+01, .1058204125616E+01,
			 .2856510589958E+03
	};

	static const double ev[] = {
			-.1390378322784E+02,  -.1079988460118E+01,  .2085176101583E+02,
			-.1303662005733E+03,  -.9527616400889E+02, -.2188376933451E+01,
			 .7399227724603E+02,   .2180138948638E-01
	};

	static const double THigh = 400;

	double viscosity = 0;
	if (T < THigh) {
		viscosity += computeDiluteGasContribution(T, dgv);
		viscosity += computeDensityCorrection(T, rho, dcv);
		viscosity += computeExcessContribution(T, rho, ev);
	} else {
		viscosity += computeDiluteGasContribution(T, dgv_highT);
		viscosity += computeDensityCorrection(THigh, rho, dcv);
		viscosity += computeExcessContribution(THigh, rho, ev);
	}

	viscosity *= 1e-6;
/*
	printf("---------------------------\n");
	printf("T=%f, rho =%f\n", T, rho);
	printf("Dilute gas viscosity: %e\n", diluteGasViscosity);
	printf("Viscosity density correction: %e\n", densityCorrectionViscosity);
	printf("Excess viscosity: %e\n", excessViscosity);
	*/
	return viscosity;
}

double ParaHydrogen_thermalConductivity_Trho (double T, double rho) {
	// Convert density to g/cm^3
	rho /= 1000.0;


	static const double dgc[] = {
		-.2633914469098E+04,  .5171968972149E+04, -.4362593863150E+04,
		 .2061546648109E+04, -.5960706319073E+03,  .1078532576512E+03,
		-.1191575825713E+02,  .7349232451540E+00, -.1938126709603E-01
	};

	static const double dgc_highT[] = {
		 .4867367597991E+05, -.3840897821396E+05,  .1305714248552E+05,
		-.2499936065236E+04,  .2951804640444E+03, -.2202843407541E+02,
		 .1015716846958E+01, -.2643479681048E-01,  .2975245793745E-03
	};

	static const double dcc[] = {
	   .3240015073128E+00, .5818893460273E-02, -.5894372682930E+01,
	   .2928193900206E+03
	};

	static const double ec[] = {
	  -.1635948767861E+02, .3741426344309E+00,  .1823588544776E+02,
	   .3429129395259E+02, .1398979978642E+03, -.3624394840949E+02,
	  -.6696701230501E+01, .9621511056600E-02

	};

	static const double THigh = 400;

	double lambda = 0;
	if (T < THigh) {
		lambda += computeDiluteGasContribution(T, dgc);
		lambda += computeDensityCorrection(T, rho, dcc);
		lambda += computeExcessContribution(T, rho, ec);
	} else {
		lambda += computeDiluteGasContribution(T, dgc_highT);
		lambda += computeDensityCorrection(THigh, rho, dcc);
		lambda += computeExcessContribution(THigh, rho, ec);
	}

	// TODO critical enhancement for thermal conductivity
	//double criticalEnhancement = 0;

	return lambda;
}
