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

/*
    DATA H2X/ .2118172389866036D-01,-.2690064330724328D+02,
   1.6124841965091452D+0,-.9164575525046011D-1,.2635836618419776D+2/
    DATA FN2X/.5809037464731244D+00,-.5942475386282104D+02,
   1 -.1251522808422072D+0,.2879967206401599D-1,.2622478216356694D+2/
    DATA H2GT/.4867367597991E+05, -.3840897821396E+05,
   1.1305714248552E+05, -.2499936065236E+04,.2951804640444E+03,
   2-.2202843407541E+02,.1015716846958E+01,-.2643479681048E-01,
   3.2975245793745E-03/
    DATA FN2GT/
   1-.9873109114265E+02,.1118599784920E+03,-.5311622278158E+02,
   2.1374697385041E+02,-.2117560946903E+01,.1991617788923E+00,
   3-.1108650576066E-01, .3394960379931E-03,-.4384079739987E-05/
    DATA H2GV/ .3597459516279E+06, -.2907864068495E+06,
   1.1010108273374E+06,-.1969542146586E+05,.2357963788723E+04,
   2-.1773345862550E+03,.8211313268144E+01,-.2133279099683E+00,
   3.2385420317913E-02/
    DATA FN2GV/
   1-.7273900514904E+03,.6498303763133E+03,-.1682623850857E+03
   2,-.4719712643829E+01,.6215560253903E+01,-.3440007984008E+00
   3,.3610595253942E-01,-.7142567643153E-03,.6351722000133E-05/
    DATA H2GAV/ .7791433249432E+06,.3438280949718E+06
   1,-.2794947448131E+06,.6411001537068E+05,-.7280622276270E+04
   2,.4534378845259E+03,-.1509587997811E+02,.2264917802515E+00
   3,-.6957031420486E-03/
    DATA FN2GAV/-.9591616190051E+04,.3074256368958E+04
   1,-.3868087010294E+03,.1157470129907E+02,.2625072267414E+01
   2,.7364067495162E-01,.4598124938740E-02,.2625777067162E-03
   3,-.6013169347841E-05/
    DATA H2GAT/ -.1588880396651E+07,.4572557167411E+06
   1,-.3115214134025E+05,-.2876275701444E+04,.4992723913624E+03
   2,-.1973185064936E+02,-.3544923220675E+00,.4229716599154E-01
   3,-.7920497429793E-03/
    DATA FN2GAT/.9010096227074E+04,-.2387445995155E+04
   1,.1625245033947E+03,.8410890804927E+01,-.1408678078238E+01
   2,.2555481434631E-01,.3367971172971E-02,-.1809924243854E-03
   3,.2668354669540E-05/
    DATA H2DISV/ .1585961783778E-01,-.2080285472410E+02
   1,.3838178512297E-01,-.1227097145662E-01/
    DATA H2DIST/ .3755275903354E-01,.9075743755146E+01
   1,.3958918196034E+06/
    DATA H2FACT/431947./
    DATA FN2FACT/941607./
    DATA H2TUP/400./
    DATA H2TUP2/1000./
    DATA FN2TUP/400./
    DATA FN2TUP2/2500./
*/

double viscosity_Trho (double T, double rho) {
    // Convert density to g/cm^3
	rho /= 1000.0;

	static const double dgv[] = {
			-.1802037993618E+04,  .3111075514590E+04, -.2247037886246E+04,
			 .8857940661235E+03, -.2090706479771E+03,  .3050376698249E+02,
			-.2640005961675E+01,  .1270278679308E+00, -.2611834393975E-02,
	};

	static const double dgv_highT[] = {
			.3597459516279E+06, -.2907864068495E+06,
			     .1010108273374E+06,-.1969542146586E+05,.2357963788723E+04,
			     -.1773345862550E+03,.8211313268144E+01,-.2133279099683E+00,
			     .2385420317913E-02	};
/*
	static const double fn2_high[] = {
    -.7273900514904E+03,.6498303763133E+03,-.1682623850857E+03,
    -.4719712643829E+01,.6215560253903E+01,-.3440007984008E+00,
    .3610595253942E-01,-.7142567643153E-03,.6351722000133E-05
	};
*/
	static const double dcv[] = {
			-.1402007673681E+02, .1037805196987E+01, .1058204125616E+01,
			 .2856510589958E+03
	};

	static const double ev[] = {
			-.1390378322784E+02,  -.1079988460118E+01,  .2085176101583E+02,
			-.1303662005733E+03,  -.9527616400889E+02, -.2188376933451E+01,
			 .7399227724603E+02,   .2180138948638E-01
	};

	static const double THigh1 = 400;
	//static const double THigh2 = 1000;

	double viscosity = 0;

	if (T < THigh1) {
		viscosity += computeDiluteGasContribution(T, dgv);
		viscosity += computeDensityCorrection(T, rho, dcv);
		viscosity += computeExcessContribution(T, rho, ev);
	} else {
		viscosity += computeDiluteGasContribution(T, dgv_highT);
		viscosity += computeDensityCorrection(THigh1, rho, dcv);
		viscosity += computeExcessContribution(THigh1, rho, ev);
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

double thermalConductivity_Trho (double T, double rho) {
	// Convert density to g/cm^3
	rho /= 1000.0;


	static const double dgc[] = {
		-.2633914469098E+04, .5171968972149E+04, -.4362593863150E+04,
		.2061546648109E+04, -.5960706319073E+03, .1078532576512E+03,
		-.1191575825713E+02, .7349232451540E+00, -.1938126709603E-01
	};

	static const double dgc_highT[] = {
		      .4867367597991E+05, -.3840897821396E+05,
		     .1305714248552E+05, -.2499936065236E+04,.2951804640444E+03,
		     -.2202843407541E+02,.1015716846958E+01,-.2643479681048E-01,
		     .2975245793745E-03
	};

	static const double dcc[] = {
	   .3240015073128E+00, .5818893460273E-02, -.5894372682930E+01,
	   .2928193900206E+03
	};

	static const double ec[] = {
	  -.1635948767861E+02, .3741426344309E+00, .1823588544776E+02,
	   .3429129395259E+02, .1398979978642E+03,  -.3624394840949E+02,
	  -.6696701230501E+01, .9621511056600E-02

	};


	double lambda = 0;
	static const double THigh1 = 400;
	if (T < THigh1) {
		lambda += computeDiluteGasContribution(T, dgc);
		lambda += computeDensityCorrection(T, rho, dcc);
		lambda += computeExcessContribution(T, rho, ec);
	} else {
		lambda += computeDiluteGasContribution(T, dgc_highT);
		lambda += computeDensityCorrection(THigh1, rho, dcc);
		lambda += computeExcessContribution(THigh1, rho, ec);
	}


	// TODO critical enhancement for thermal conductivity
	//double criticalEnhancement = 0;

	return lambda;
}
