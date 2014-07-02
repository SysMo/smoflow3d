/*
 * MediumStateFluidCoolProp.cpp
 *
 *  Created on: Jul 28, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "MediumStateFluidCoolProp.h"

MediumState_FluidCoolProp::MediumState_FluidCoolProp(Medium_CompressibleFluid_CoolProp* medium)
: MediumState(medium), pFluid(medium->fluid), cps(pFluid){
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
		_rho = pFluid->density_Tp(T, p, _rho);
		cps.update_Trho(iT, T, iD, _rho);
	} else {
		cps.update_Tp(iT, T, iP, p);
		_rho = cps.rho();
	}
	post_update();
	_h = cps.h();
}

void MediumState_FluidCoolProp::update_Trho(double T, double rho) {
	pre_update();
	_T = T;
	_rho = rho;
	cps.update_Trho(iT, _T, iD, _rho);
	post_update();
	_p = cps.p();
	_h = cps.h();
}

void MediumState_FluidCoolProp::update_prho(double p, double rho) {
	pre_update();
	_p = p;
	_rho = rho;
	if (ValidNumber(_T)) {
		_T = pFluid->temperature_prho(_p, _rho, _T);
		cps.update_Trho(iT, _T, iD, _rho);
	} else {
		cps.update_prho(iP, _p, iD, _rho);
		_T = cps.T();
	}
	post_update();
	_h = cps.h();
}

void MediumState_FluidCoolProp::update_ph(double p, double h) {
	pre_update();
	_p = p;
	_h = h;
	if (ValidNumber(_T) && ValidNumber(_rho)) {
		double rhosatL, rhosatV, TsatL, TsatV;
		pFluid->temperature_ph(_p, _h, _T, _rho, rhosatL, rhosatV, TsatL, TsatV, _T, _rho);
		cps.update_Trho(iT, _T, iD, _rho);
	} else {
		cps.update_ph(iP, p, iH, h);
		_T = cps.T();
		_rho = cps.rho();
	}
	post_update();
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
		_dpdt_v = cps.dpdT_constrho();
	}
	return _dpdt_v;
}

double MediumState_FluidCoolProp::dpdv_t() {
	if (!_dpdv_t) {
		_dpdv_t = - _rho * _rho * dpdrho_t();
	}
	return _dpdv_t;
}

double MediumState_FluidCoolProp::dpdrho_t() {
	if (!_dpdrho_t) {
		_dpdrho_t = cps.dpdrho_constT();
	}
	return _dpdrho_t;
}

double MediumState_FluidCoolProp::dvdt_p() {
	if (!_dvdt_p) {
		_dvdt_p = cps.dvdT_constp();
	}
	return _dvdt_p;
}

double MediumState_FluidCoolProp::beta()  {
	if (!_beta) {
		_beta = _rho * cps.dvdT_constp();
	}
	return _beta;
}

double MediumState_FluidCoolProp::mu() {
	if (!_mu) {
		_mu = pFluid->viscosity_Trho(_T,_rho);
	}
	return _mu;
}

double MediumState_FluidCoolProp::lambda() {
	if (!_lambda) {
		_lambda = pFluid->conductivity_Trho(_T,_rho);
	}
	return _lambda;
}

double MediumState_FluidCoolProp::R() {
	return pFluid->R();
}
