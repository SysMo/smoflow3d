/*
 * MediumStateFluidCoolProp.cpp
 *
 *  Created on: Jul 28, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "MediumStateFluidCoolProp.h"
#include "CoolProp/CPExceptions.h"

/**
 * SmoCoolPropStateClass - C++
 */
double SmoCoolPropStateClass::gamma() {
	if (!TwoPhase) {
		return cp() / cv();
	} else {
		double cp2p = interp_linear(_Q, SatL->cp(), SatV->cp());
		double cv2p = interp_linear(_Q, SatL->cv(), SatV->cv());
		return cp2p / cv2p;
	}
}

double SmoCoolPropStateClass::Pr() {
	if (!TwoPhase) {
		return cp() * viscosity() / conductivity();
	} else {
		double cp2p = interp_linear(_Q, SatL->cp(), SatV->cp());
		return cp2p * viscosity() / conductivity();
	}
}

double SmoCoolPropStateClass::beta() {
	if (!TwoPhase) {
		return _rho * dvdT_constp();
	} else {
		std::cout << "Warning: Calculating beta = dv_dt_p in the two-phase region!" << std::endl;
		return _rho * interp_linear(_Q, SatL->dvdT_constp(), SatV->dvdT_constp());
	}
}

/**
 * MediumState_FluidCoolProp - C++
 */
MediumState_FluidCoolProp::MediumState_FluidCoolProp(Medium_CompressibleFluid_CoolProp* medium)
: MediumState(medium), pFluid(medium->fluid), cps(pFluid){
	cps.enable_EXTTP();
	_q = 0.0;
}

MediumState_FluidCoolProp::~MediumState_FluidCoolProp() {
}

void MediumState_FluidCoolProp::pre_update() {
	clearPropertyCache();
	cps._pre_update();
}

void MediumState_FluidCoolProp::post_update() {
	cps._post_update();
}

void MediumState_FluidCoolProp::update_Tp(double T, double p) {
	pre_update();
	_T = T;
	_p = p;
	if (ValidNumber(_rho)) {
		try {
			_rho = pFluid->density_Tp(T, p, _rho);
			cps.update_Trho(iT, T, iD, _rho);
		} catch (SolutionError e) {
			std::cout << "Update_Tp(T = " << T << ", p = " << p
					<< ") failed, trying to calculate without using cache variables\n";
			cps.update_Tp(iT, T, iP, p);
			_rho = cps.rho();
		}
	} else {
		cps.update_Tp(iT, T, iP, p);
		_rho = cps.rho();
	}
	post_update();
	_h = cps.h();
	_q = cps.Q();
}

void MediumState_FluidCoolProp::update_Trho(double T, double rho) {
	pre_update();
	_T = T;
	_rho = rho;
	cps.update_Trho(iT, _T, iD, _rho);
	post_update();
	_p = cps.p();
	_h = cps.h();
	_q = cps.Q();
}

void MediumState_FluidCoolProp::update_prho(double p, double rho) {
	pre_update();
	_p = p;
	_rho = rho;
	if (ValidNumber(_T)) {
		try {
			_T = pFluid->temperature_prho(_p, _rho, _T);
			cps.update_Trho(iT, _T, iD, _rho);
		} catch (SolutionError e) {
			std::cout << "Update_prho(p = " << p << ", rho = " << rho
					<< ") failed, trying to calculate without using cache variables\n";
			cps.update_prho(iP, _p, iD, _rho);
			_T = cps.T();
		}
	} else {
		cps.update_prho(iP, _p, iD, _rho);
		_T = cps.T();
	}
	post_update();
	_h = cps.h();
	_q = cps.Q();
}

void MediumState_FluidCoolProp::update_ph(double p, double h) {
	pre_update();
	_p = p;
	_h = h;
	if (ValidNumber(_T) && ValidNumber(_rho)) {
		try {
			double rhosatL, rhosatV, TsatL, TsatV;
			pFluid->temperature_ph(_p, _h, _T, _rho, rhosatL, rhosatV, TsatL, TsatV, _T, _rho);
			cps.update_Trho(iT, _T, iD, _rho);
		} catch (SolutionError e) {
			std::cout << "Update_ph(p = " << p << ", h = " << h
					<< ") failed, trying to calculate without using cache variables\n";
			cps.update_ph(iP, p, iH, h);
			_T = cps.T();
			_rho = cps.rho();
		}
	} else {
		cps.update_ph(iP, p, iH, h);
		_T = cps.T();
		_rho = cps.rho();
	}
	post_update();
	_q = cps.Q();
}

void MediumState_FluidCoolProp::update_ps(double p, double s) {
	pre_update();
	_p = p;
//	if (ValidNumber(_T) && ValidNumber(_rho)) {
//		double rhosatL, rhosatV, TsatL, TsatV;
//		pFluid->temperature_ps(_p, s, _T, _rho, rhosatL, rhosatV, TsatL, TsatV);
//		cps.update_Trho(iT, _T, iD, _rho);
//	} else {
//	}
	// TODO (Nasko) Currently no function temperature_ps() with supplyied guess
	// values for T and rho is available for coolprop Fluid class
	cps.update_ps(iP, p, iS, s);
	post_update();
	_T = cps.T();
	_rho = cps.rho();
	_h = cps.h();
	_q = cps.Q();
}

void MediumState_FluidCoolProp::update_pq(double p, double q) {
	pre_update();
	_p = p;
	_q = q;
	cps.update_twophase(iP, p, iQ, q);
	post_update();
	_T = cps.T();
	_rho = cps.rho();
	_h = cps.h();
}

void MediumState_FluidCoolProp::update_Tq(double T, double q) {
	pre_update();
	_T = T;
	_q = q;
	cps.update_twophase(iT, T, iQ, q);
	post_update();
	_p = cps.p();
	_rho = cps.rho();
	_h = cps.h();
}

double MediumState_FluidCoolProp::q() {
	if (isTwoPhase()) {
		return cps.Q();
	} else {
		return -1.0;
	}
}

double MediumState_FluidCoolProp::u() {
	if (!_u) {
		_u = _h - _p / _rho ;
	}
	return _u;
}

double MediumState_FluidCoolProp::s() {
	if (!_s) {
		_s = cps.s();
	}
	return _s;
}

double MediumState_FluidCoolProp::cp() {
	if (!_cp) {
		_cp = cps.cp();
	}
	return _cp;
}

double MediumState_FluidCoolProp::cv() {
	if (!_cv) {
		_cv = cps.cv();
	}
	return _cv;
}

double MediumState_FluidCoolProp::dpdt_v() {
	if (!_dpdt_v) {
		if (isTwoPhase()) {
			_dpdt_v = dpdTSat();
		} else {
			_dpdt_v = cps.dpdT_constrho();
		}
	}
	return _dpdt_v;
}

double MediumState_FluidCoolProp::dpdv_t() {
	if (!_dpdv_t) {
		if (isTwoPhase()) {
			_dpdv_t = 0;
		} else {
			_dpdv_t = - _rho * _rho * dpdrho_t();
		}
	}
	return _dpdv_t;
}

double MediumState_FluidCoolProp::dpdrho_t() {
	if (!_dpdrho_t) {
		if (isTwoPhase()) {
			_dpdrho_t = 0;
		} else {
			_dpdrho_t = cps.dpdrho_constT();
		}
	}
	return _dpdrho_t;
}

double MediumState_FluidCoolProp::dvdt_p() {
	if (!_dvdt_p) {
		if (isTwoPhase()) {
			RaiseError("Cannot calculate dvdt_p in the two-phase region")
		} else {
			_dvdt_p = cps.dvdT_constp();
		}
	}
	return _dvdt_p;
}

double MediumState_FluidCoolProp::beta()  {
	if (!_beta) {
		_beta = cps.beta();
	}
	return _beta;
}

double MediumState_FluidCoolProp::mu() {
	if (!_mu) {
		_mu = cps.viscosity();
	}
	return _mu;
}

double MediumState_FluidCoolProp::lambda() {
	if (!_lambda) {
		_lambda = cps.conductivity();
	}
	return _lambda;
}

double MediumState_FluidCoolProp::R() {
	return pFluid->R();
}

double MediumState_FluidCoolProp::Pr() {
	if (!_Pr) {
		_Pr = cps.Pr();
	}
	return _Pr;
}

double MediumState_FluidCoolProp::gamma() {
	if (!_gamma) {
		_gamma = cps.gamma();
	}
	return _gamma;
}

bool MediumState_FluidCoolProp::isSupercritical() {
	return _p > pFluid->crit.p.Pa;
}

bool MediumState_FluidCoolProp::isTwoPhase() {
	return cps.TwoPhase;
}

double MediumState_FluidCoolProp::deltaTSat() {
	return _T - TSat();
}

double MediumState_FluidCoolProp::TSat() {
	if (isSupercritical()) {
		return pFluid->crit.T;
	} else if (isTwoPhase()) {
		return _T;
	} else {
		double TSatL = pFluid->Tsat_anc(_p, 1);
		return TSatL;
	}
}

double MediumState_FluidCoolProp::dpdTSat() {
	return 1./cps.dTdp_along_sat();
}
