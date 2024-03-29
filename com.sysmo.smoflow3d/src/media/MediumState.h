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
	double q;
} BasicState;

typedef struct {
	ThermodynamicVariable state1;
	double state1Value;
	ThermodynamicVariable state2;
	double state2Value;
} StateVariableSet;

typedef enum {
	PhaseSelection_Overall,
	PhaseSelection_Liquid,
	PhaseSelection_Gas,
	PhaseSelection_varDiscrete,
	PhaseSelection_varContinuous
} PhaseSelection;
END_C_LINKAGE

#ifdef __cplusplus

#include "util/CachedProperty.h"

class MediumState : public SmoObject {
public:
	virtual ~MediumState();

	Medium* getMedium();
	virtual void init(ThermodynamicVariable state1, double state1Value,
			ThermodynamicVariable state2, double state2Value);
	virtual void init(std::string state1, double state1Value,
			std::string state2, double state2Value);
	void init(StateVariableSet& stateStruct);
	virtual void clearState();
	virtual void clearPropertyCache();

	virtual void update_Tp(double T, double p);
	virtual void update_Trho(double T, double rho);
	virtual void update_prho(double p, double rho);
	virtual void update_ph(double p, double h);
	virtual void update_ps(double p, double s);
	virtual void update_pq(double p, double q);
	virtual void update_Tq(double T, double q);

	double T();
	double p();
	double rho();
	double h();
	virtual double s();
	virtual double u();
	virtual double cp();
	virtual double cv();
	virtual double speed_sound();
	virtual double dpdt_v();
	virtual double dpdv_t();
	virtual double dpdrho_t();
	virtual double dvdt_p();
	virtual double beta();
	virtual double mu();
	virtual double lambda();
	virtual double Pr();
	virtual double gamma();
	virtual double R(); //mass-specific gas constant [J/kg/K]

	// Two-phase related functions
	virtual double q(); // Gas mass fraction
	virtual double qV(); //Gas volume fraction
	virtual bool isSupercritical();
	virtual bool isTwoPhase();
	virtual double deltaTSat();
	virtual double TSat();
	virtual double dpdTSat();

	void setCacheStateVariables(bool ifCache);

protected:
	MediumState(Medium* medium);

	bool triggerDiscontinuity_NegativeStateValue(double stateValue);

	Medium* medium;
	double _T;
	double _p;
	double _rho;
	double _h;
	double _q;
	CachedProperty _u;
	CachedProperty _s;
	CachedProperty _cp;
	CachedProperty _cv;
	CachedProperty _speed_sound;
	CachedProperty _dpdt_v;
	CachedProperty _dpdv_t;
	CachedProperty _dpdrho_t;
	CachedProperty _dvdt_p;
	CachedProperty _beta;
	CachedProperty _mu;
	CachedProperty _lambda;
	CachedProperty _Pr;
	CachedProperty _gamma;

	bool cacheStateVariables;
	BasicState prevState;
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

void MediumState_init(MediumState* mstate,
		ThermodynamicVariable state1, double state1Value,
		ThermodynamicVariable state2, double state2Value);
void MediumState_initStruct(MediumState* mstate, StateVariableSet stateStruct);

void MediumState_update_Tp(MediumState* mstate, double T, double p);
void MediumState_update_Trho(MediumState* mstate, double T, double rho);
void MediumState_update_prho(MediumState* mstate, double p, double rho);
void MediumState_update_ph(MediumState* mstate, double p, double h);
void MediumState_update_ps(MediumState* mstate, double p, double s);
void MediumState_update_pq(MediumState* mstate, double p, double q);
void MediumState_update_Tq(MediumState* mstate, double T, double q);

void MediumState_copy(MediumState* sourceState, MediumState* targetState, int stateVariableSelection);

double MediumState_T(MediumState* mstate);
double MediumState_p(MediumState* mstate);
double MediumState_rho(MediumState* mstate);
double MediumState_h(MediumState* mstate);
double MediumState_q(MediumState* mstate);
double MediumState_qV(MediumState* mstate);

double MediumState_u(MediumState* mstate);
double MediumState_cp(MediumState* mstate);
double MediumState_cv(MediumState* mstate);
double MediumState_speed_sound(MediumState* mstate);
double MediumState_dpdt_v(MediumState* mstate);
double MediumState_dpdv_t(MediumState* mstate);
double MediumState_dpdrho_t(MediumState* mstate);
double MediumState_dvdt_p(MediumState* mstate);
double MediumState_beta(MediumState* mstate);
double MediumState_mu(MediumState* mstate);
double MediumState_lambda(MediumState* mstate);
double MediumState_Pr(MediumState* mstate);
double MediumState_gamma(MediumState* mstate);
double MediumState_R(MediumState* mstate);

// Two-phase related functions
int MediumState_isSupercritical(MediumState* mstate);
int MediumState_isTwoPhase(MediumState* mstate);
double MediumState_deltaTSat(MediumState* mstate);
double MediumState_TSat(MediumState* mstate);
END_C_LINKAGE


#endif /* MEDIUMSTATE_H_ */
