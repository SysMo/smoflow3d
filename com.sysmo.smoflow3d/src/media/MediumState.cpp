/*
 * MediumState.cpp
 *
 *  Created on: Jul 22, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "MediumState.h"
#include <vector>

static std::vector<MediumState*> MediumStateRegistry;


/**
 * MediumState C++ Class Functions
 */
MediumState::MediumState(Medium* medium) : CoolPropStateClassSI(medium) {
	this->mediumIndex = -1;
	start();
}

MediumState::MediumState(int mediumIndex) : CoolPropStateClassSI(Medium_get(mediumIndex)) {
	this->mediumIndex = mediumIndex;
	start();
}

MediumState::~MediumState() {
}

void MediumState::start() {
	// Reset all the internal variables to _HUGE
	_T = _HUGE;
	_p = _HUGE;
	_logp = _HUGE;
	_h = _HUGE;
	_s = _HUGE;
	_rho = _HUGE;
	_logrho = _HUGE;
	_Q = _HUGE;
}

void MediumState::pre_update() {
	// Clear the cached helmholtz energy derivative terms
	this->cache.clear();


	// Reset the cached values for _h and _s
	s_cached = false;
	h_cached = false;

	// Only build the Saturation classes if this is a top-level CPState for which no_SatLSatV() has not been called
	if (!_noSatLSatV){
		if (SatL == NULL){
			SatL = new CoolPropStateClassSI(pFluid);
			SatL->no_SatLSatV(); // Kill the recursive building of the saturation classes
		}
		if (SatV == NULL){
			SatV = new CoolPropStateClassSI(pFluid);
			SatV->no_SatLSatV(); // Kill the recursive building of the saturation classes
		}
	}

	// Don't know if it is single phase or not, so assume it isn't
	SinglePhase = false;
}

void MediumState::post_update() {
	CoolPropStateClassSI::_post_update();
}

// TODO see what variables are updated when. Make sure caches are cleared when updating state
// TODO check out calculations (e.g. enthalpy) for incompressible solution
void MediumState::update_Tp(double T, double p) {
	pre_update();
	_T = T;
	_p = p;
	if (ValidNumber(_rho)) {
		_rho = pFluid->density_Tp(T, p, _rho);
	} else {
		CoolPropStateClassSI::update_Tp(iT, T, iP, p);
		//std::cout << "Slow call to density calc" << std::endl;
		//_rho = pFluid->density_Tp(T, p);
	}
	_h = h();
	h_cached = true;
	post_update();
}

void MediumState::update_Trho(double T, double rho) {
	pre_update();
	_T = T;
	_rho = rho;
	_p = pFluid->pressure_Trho(T, rho);
	_h = h();
	h_cached = true;
	post_update();
}

void MediumState::update_ph(double p, double h) {
	pre_update();
	_p = p;
	_h = h;
	if (ValidNumber(_T) && ValidNumber(_rho)) {
		pFluid->temperature_ph(_p, _h, _T, _rho, rhosatL, rhosatV, TsatL, TsatV, _T, _rho);
	} else {
		CoolPropStateClassSI::update_ph(iP, p, iH, h);
	}
	h_cached = true;
	post_update();
}

void MediumState::update_prho(double p, double rho) {
	pre_update();
	_p = p;
	_rho = rho;
	RaiseError_UnimplementedFunction();
	post_update();
}

void MediumState::update_ps(double p, double s) {
	pre_update();
	_p = p;
	_s = s;
	RaiseError_UnimplementedFunction();
	post_update();
}

double MediumState::u() {
	return h() - p() / rho();
}



/**
 * MediumState C Functions
 */
BEGIN_C_LINKAGE

MediumState* MediumState_new(int mediumIndex) {
	return new MediumState(mediumIndex);
}

int MediumState_register(MediumState* mstate) {
	MediumStateRegistry.push_back(mstate);
	return MediumStateRegistry.size();
}

MediumState* MediumState_get(int mstateIndex) {
	return MediumStateRegistry.at(mstateIndex - 1);
}

int MediumState_getMediumIndex(MediumState* mstate) {
	return mstate->mediumIndex;
}

void MediumState_update_Tp(MediumState* mstate, double T, double p) {
	mstate->update_Tp(T, p);
}

void MediumState_update_Trho(MediumState* mstate, double T, double rho) {
	mstate->update_Trho(T, rho);
}

void MediumState_update_ph(MediumState* mstate, double p, double h) {
	mstate->update_ph(p, h);
}

double MediumState_T(MediumState* mstate) {
	return mstate->T();
}

double MediumState_p(MediumState* mstate) {
	return mstate->p();
}

double MediumState_rho(MediumState* mstate) {
	return mstate->rho();
}

double MediumState_u(MediumState* mstate) {
	return  mstate->u();
}

double MediumState_h(MediumState* mstate) {
	return mstate->h();
}

double MediumState_mu(MediumState* mstate) {
	return mstate->viscosity();
}

double MediumState_lambda(MediumState* mstate) {
	return mstate->conductivity();
}

double MediumState_dpdt_v(MediumState* mstate) {
	return mstate->dpdT_constrho();
}

//TODO check this
double MediumState_dpdv_t(MediumState* mstate) {
	return - mstate->rho() * mstate->rho() * mstate->dpdrho_constT();
}

double MediumState_cp(MediumState* mstate) {
	return mstate->cp();
}

double MediumState_beta(MediumState* mstate) {
	return mstate->rho() * mstate->dvdT_constp();
}

double MediumState_Pr(MediumState* mstate) {
	return mstate->cp() * mstate->viscosity() / mstate->conductivity();
}

END_C_LINKAGE
