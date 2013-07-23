/*
 * MediumState.cpp
 *
 *  Created on: Jul 22, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "MediumState.h"
#include <vector>

std::vector<MediumState*> MediaStateRegistry;

MediumState::MediumState(Medium* medium) : CoolPropStateClassSI(medium) {
	start();
}

MediumState::MediumState(int mediumIndex) : CoolPropStateClassSI(get_medium(mediumIndex)) {
	start();
}

MediumState::~MediumState() {
}

void MediumState::start() {
	CoolPropStateClassSI::_pre_update();
}

// TODO see what variables are updated when
// TODO check out calculations (e.g. enthalpy) for incompressible solution
void MediumState::update_Tp(double T, double p) {
	if (ValidNumber(_rho)) {
		_T = T;
		_p = p;
		_rho = pFluid->density_Tp(T, p, _rho);
		h_cached = false;
		_h = h();
		h_cached = true;
	} else {
		CoolPropStateClassSI::update_Tp(iT, T, iP, p);
		//std::cout << "Slow call to density calc" << std::endl;
		//_rho = pFluid->density_Tp(T, p);
	}
	post_update();
}

void MediumState::update_Trho(double T, double rho) {
	_T = T;
	_rho = rho;
	_p = pFluid->pressure_Trho(T, rho);
	h_cached = false;
	_h = h();
	h_cached = true;
	post_update();
}

void MediumState::update_ph(double p, double h) {
	if (ValidNumber(_T) && ValidNumber(_rho)) {
		_p = p;
		_h = h;
		h_cached = true;
		pFluid->temperature_ph(_p, _h, _T, _rho, rhosatL, rhosatV, TsatL, TsatV, _T, _rho);
	} else {
		CoolPropStateClassSI::update_ph(iP, p, iH, h);
	}
	post_update();
}

void MediumState::update_prho(double p, double rho) {
	_p = p;
	_rho = rho;
	RaiseError_UnimplementedFunction();
	post_update();
}

void MediumState::update_ps(double p, double s) {
	_p = p;
	_s = s;
	RaiseError_UnimplementedFunction();
	post_update();
}

void MediumState::post_update() {
	CoolPropStateClassSI::_post_update();
}

BEGIN_C_LINKAGE

MediumState* create_mstate(int mediumIndex) {
	return new MediumState(mediumIndex);
}

int mstate_register(MediumState* mstate) {
	MediaStateRegistry.push_back(mstate);
	return MediaStateRegistry.size() - 1;
}

MediumState* mstate_get(int mstateIndex) {
	return MediaStateRegistry.at(mstateIndex);
}

void mstate_update_Tp(MediumState* mstate, double T, double p) {
	mstate->update_Tp(T, p);
}

void mstate_update_Trho(MediumState* mstate, double T, double rho) {
	mstate->update_Trho(T, rho);
}

void mstate_update_ph(MediumState* mstate, double p, double h) {
	mstate->update_ph(p, h);
}

double mstate_T(MediumState* mstate) {
	return mstate->T();
}

double mstate_p(MediumState* mstate) {
	return mstate->p();
}

double mstate_rho(MediumState* mstate) {
	return mstate->rho();
}

double mstate_h(MediumState* mstate) {
	return mstate->h();
}

double mstate_mu(MediumState* mstate) {
	return mstate->viscosity();
}

double mstate_lambda(MediumState* mstate) {
	return mstate->conductivity();
}

double mstate_dpdt_v(MediumState* mstate) {
	return mstate->dpdT_constrho();
}

//TODO check this
double mstate_dpdv_t(MediumState* mstate) {
	return - mstate->rho() * mstate->rho() * mstate->dpdrho_constT();
}

double mstate_cp(MediumState* mstate) {
	return mstate->cp();
}

double mstate_beta(MediumState* mstate) {
	return mstate->rho() * mstate->dvdT_constp();
}

double mstate_Pr(MediumState* mstate) {
	return mstate->cp() * mstate->viscosity() / mstate->conductivity();
}

END_C_LINKAGE
