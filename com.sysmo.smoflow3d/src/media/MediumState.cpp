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
using namespace smoflow;

/**
 * MediumState C++ Class Functions
 */
MediumState::MediumState(Medium* medium) {
	this->medium = medium;
	clearState();
}

MediumState::~MediumState() {
}

Medium* MediumState::getMedium() {
	return medium;
}

void MediumState::clearState() {
	// Reset all the internal variables to _HUGE
	_T = _HUGE;
	_p = _HUGE;
	_h = _HUGE;
	_rho = _HUGE;
}

void MediumState::clearPropertyCache() {
	_u.clear();
	_s.clear();
	_cp.clear();
	_cv.clear();
	_dpdt_v.clear();
	_dpdv_t.clear();
	_dpdrho_t.clear();
	_dvdt_p.clear();
	_beta.clear();
	_mu.clear();
	_lambda.clear();
	_Pr.clear();
	_gamma.clear();
}

void MediumState::update_Tp(double T, double p) {
	RaiseError("Unimplemented virtual method 'MediumState::update_Tp'")
}

void MediumState::update_Trho(double T, double rho) {
	RaiseError("Unimplemented virtual method 'MediumState::update_Trho'")
}

void MediumState::update_prho(double p, double rho) {
	RaiseError("Unimplemented virtual method 'MediumState::update_prho'")
}

void MediumState::update_ph(double p, double h) {
	RaiseError("Unimplemented virtual method 'MediumState::update_ph'")
}

void MediumState::update_ps(double p, double s) {
	RaiseError("Unimplemented virtual method 'MediumState::update_ps'")
}

void MediumState::update_pq(double p, double q) {
	RaiseError("Unimplemented virtual method 'MediumState::update_px'")
}

void MediumState::update_Tq(double T, double q) {
	RaiseError("Unimplemented virtual method 'MediumState::update_Tx'")
}

double MediumState::T() {
	return _T;
}

double MediumState::p() {
	return _p;
}


double MediumState::rho() {
	return _rho;
}

double MediumState::h() {
	return _h;
}

double MediumState::u() {
	RaiseError("Unimplemented virtual method 'MediumState::u()'")
}

double MediumState::s() {
	RaiseError("Unimplemented virtual method 'MediumState::s()'")
}

double MediumState::cp() {
	RaiseError("Unimplemented virtual method 'MediumState::cp()'")
}

double MediumState::cv() {
	RaiseError("Unimplemented virtual method 'MediumState::cv()'")
}

double MediumState::dpdt_v() {
	RaiseError("Unimplemented virtual method 'MediumState::dpdt_v()'")
}

double MediumState::dpdv_t() {
	RaiseError("Unimplemented virtual method 'MediumState::dpdv_t()'")
}

double MediumState::dpdrho_t() {
	RaiseError("Unimplemented virtual method 'MediumState::dpdrho_t()'")
}

double MediumState::dvdt_p() {
	RaiseError("Unimplemented virtual method 'MediumState::dvdt_p()'")
}

double MediumState::beta() {
	RaiseError("Unimplemented virtual method 'MediumState::beta()'")
}

double MediumState::mu() {
	RaiseError("Unimplemented virtual method 'MediumState::mu()'")
}

double MediumState::lambda() {
	RaiseError("Unimplemented virtual method 'MediumState::lambda()'")
}

double MediumState::Pr() {
	if (!_Pr) {
		_Pr = cp() * mu() / lambda();
	}
	return _Pr;
}

double MediumState::gamma() {
	if (!_gamma) {
		_gamma = cp() / cv();
	}
	return _gamma;
}

double MediumState::R() {
	RaiseError("Unimplemented virtual method 'MediumState::R()'")
}

bool MediumState::isSupercritical() {
	RaiseError("Unimplemented virtual method 'MediumState::isSupercritical()'")
}

bool MediumState::isTwoPhase() {
	RaiseError("Unimplemented virtual method 'MediumState::isTwoPhase()'")
}

double MediumState::q() {
	RaiseError("Unimplemented virtual method 'MediumState::q()'")
}

double MediumState::deltaTSat() {
	RaiseError("Unimplemented virtual method 'MediumState::deltaTSat()'")
}

double MediumState::TSat() {
	RaiseError("Unimplemented virtual method 'MediumState::TSat()'")
}

double MediumState::dpdTSat() {
	RaiseError("Unimplemented virtual method 'MediumState::TSat()'")
}

/**
 * MediumState C Functions
 */

/** Medium state subclasses */
#include "MediumStateFluidCoolProp.h"
#include "MediumStateSolid.h"

MediumState* MediumState_new(Medium* medium) {
	MediumState* state = NULL;
	if (dynamic_cast<Medium_CompressibleFluid_CoolProp*>(medium) != NULL) {
		Medium_CompressibleFluid_CoolProp* actualMedium =
				dynamic_cast<Medium_CompressibleFluid_CoolProp*>(medium);
		state = new MediumState_FluidCoolProp(actualMedium);
	} else if (dynamic_cast<Medium_Solid*>(medium) != NULL) {
		Medium_Solid* actualMedium = dynamic_cast<Medium_Solid*>(medium);
		state = new MediumState_Solid(actualMedium);
	} else {
		RaiseError("Cannot create medium state (unknown medium type)");
	}
	return state;
}

int MediumState_register(MediumState* mstate) {
	MediumStateRegistry.push_back(mstate);
	size_t instanceIndex = MediumStateRegistry.size();
	mstate->instanceIndex = instanceIndex;
	return instanceIndex;
}

MediumState* MediumState_get(int mstateIndex) {
	return MediumStateRegistry.at(mstateIndex - 1);
}

int MediumState_index(MediumState* mstate) {
	for (size_t i = 0; i < MediumStateRegistry.size(); i++) {
		if (MediumStateRegistry[i] == mstate)
			return i + 1;
	}
	return -1;
}

Medium* MediumState_getMedium(MediumState* mstate) {
	return mstate->getMedium();
}

void MediumState_update_Tp(MediumState* mstate, double T, double p) {
	mstate->update_Tp(T, p);
}

void MediumState_update_Trho(MediumState* mstate, double T, double rho) {
	mstate->update_Trho(T, rho);
}

void MediumState_update_prho(MediumState* mstate, double p, double rho) {
	mstate->update_prho(p, rho);
}

void MediumState_update_ph(MediumState* mstate, double p, double h) {
	mstate->update_ph(p, h);
}

void MediumState_update_ps(MediumState* mstate, double p, double s) {
	mstate->update_ps(p, s);
}

void MediumState_update_pq(MediumState* mstate, double p, double q) {
	mstate->update_pq(p, q);
}

void MediumState_update_Tq(MediumState* mstate, double T, double q) {
	mstate->update_Tq(T, q);
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

double MediumState_h(MediumState* mstate) {
	return mstate->h();
}

double MediumState_u(MediumState* mstate) {
	return  mstate->u();
}

double MediumState_cp(MediumState* mstate) {
	return mstate->cp();
}

double MediumState_cv(MediumState* mstate) {
	return mstate->cv();
}

double MediumState_dpdt_v(MediumState* mstate) {
	return mstate->dpdt_v();
}

double MediumState_dpdv_t(MediumState* mstate) {
	return mstate->dpdv_t();
}

double MediumState_dpdrho_t(MediumState* mstate) {
	return mstate->dpdrho_t();
}

double MediumState_dvdt_p(MediumState* mstate) {
	return mstate->dvdt_p();
}

double MediumState_beta(MediumState* mstate) {
	return mstate->beta();
}

double MediumState_mu(MediumState* mstate) {
	return mstate->mu();
}

double MediumState_lambda(MediumState* mstate) {
	return mstate->lambda();
}

double MediumState_Pr(MediumState* mstate) {
	return mstate->Pr();
}

double MediumState_gamma(MediumState* mstate) {
	return mstate->gamma();
}

double MediumState_R(MediumState* mstate) {
	return mstate->R();
}

int MediumState_isSupercritical(MediumState* mstate) {
	return mstate->isSupercritical();
}

int MediumState_isTwoPhase(MediumState* mstate) {
	return mstate->isTwoPhase();
}

double MediumState_q(MediumState* mstate) {
	return mstate->q();
}

double MediumState_deltaTSat(MediumState* mstate) {
	return mstate->deltaTSat();
}

double MediumState_TSat(MediumState* mstate) {
	return mstate->TSat();
}
