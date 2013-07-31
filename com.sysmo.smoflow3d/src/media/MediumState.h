/*
 * MediaState.h
 *
 *  Created on: Jul 22, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#ifndef MEDIUMSTATE_H_
#define MEDIUMSTATE_H_

#include "util/CommonDefinitions.h"
#include "Medium.h"

BEGIN_C_LINKAGE
typedef struct {
	double p;
	double T;
	double rho;
	double h;
} BasicState;
END_C_LINKAGE


#ifdef __cplusplus

#include "CoolProp/CPState.h"
#include "util/CachedProperty.h"


class MediumState {
public:
	virtual ~MediumState();

	Medium* getMedium();
	virtual void clearState();
	virtual void clearPropertyCache();

	virtual void update_Tp(double T, double p);
	virtual void update_Trho(double T, double rho);
	virtual void update_prho(double p, double rho);
	virtual void update_ph(double p, double h);
	virtual void update_ps(double p, double s);

	double T();
	double p();
	double rho();
	double h();
	virtual double u();
	virtual double cp();
	virtual double cv();
	virtual double dpdt_v();
	virtual double dpdv_t();
	virtual double dpdrho_t();
	virtual double dvdt_p();
	virtual double beta();
	virtual double mu();
	virtual double lambda();
	virtual double Pr();
protected:
	MediumState(Medium* medium);

	Medium* medium;
	double _T;
	double _p;
	double _rho;
	double _h;
	CachedProperty _u;
	CachedProperty _cp;
	CachedProperty _cv;
	CachedProperty _dpdt_v;
	CachedProperty _dpdv_t;
	CachedProperty _dpdrho_t;
	CachedProperty _dvdt_p;
	CachedProperty _beta;
	CachedProperty _mu;
	CachedProperty _lambda;
	CachedProperty _Pr;
};

#else //no __cplusplus

DECLARE_C_STRUCT(MediumState)

#endif //__cplusplus



BEGIN_C_LINKAGE
MediumState* MediumState_new(Medium* medium);
int MediumState_register(MediumState* mstate);
MediumState* MediumState_get(int mstateIndex);
int MediumState_index(MediumState* mstate);
Medium* MediumState_getMedium(MediumState* mstate);

void MediumState_update_Tp(MediumState* mstate, double T, double p);
void MediumState_update_Trho(MediumState* mstate, double T, double rho);
void MediumState_update_prho(MediumState* mstate, double p, double rho);
void MediumState_update_ph(MediumState* mstate, double p, double h);
void MediumState_update_ps(MediumState* mstate, double p, double s);

double MediumState_T(MediumState* mstate);
double MediumState_p(MediumState* mstate);
double MediumState_rho(MediumState* mstate);
double MediumState_h(MediumState* mstate);
double MediumState_u(MediumState* mstate);
double MediumState_cp(MediumState* mstate);
double MediumState_cv(MediumState* mstate);
double MediumState_dpdt_v(MediumState* mstate);
double MediumState_dpdv_t(MediumState* mstate);
double MediumState_dpdrho_t(MediumState* mstate);
double MediumState_dvdt_p(MediumState* mstate);
double MediumState_beta(MediumState* mstate);
double MediumState_mu(MediumState* mstate);
double MediumState_lambda(MediumState* mstate);
double MediumState_Pr(MediumState* mstate);
END_C_LINKAGE


#endif /* MEDIUMSTATE_H_ */
