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


BEGIN_C_LINKAGE
typedef struct {
	double p;
	double T;
	double rho;
	double h;
} BasicState;
END_C_LINKAGE


#ifdef __cplusplus

#include "MediaRegistry.h"
#include "CPState.h"

class MediumState : public CoolPropStateClassSI {
public:
	MediumState(Medium* medium);
	MediumState(int mediumIndex);
	virtual ~MediumState();

	void start();
	void pre_update();
	void update_Tp(double T, double p);
	void update_Trho(double T, double rho);
	void update_ph(double p, double h);
	void update_prho(double p, double rho);
	void update_ps(double p, double s);
	void post_update();

	double u();

public:
	int mediumIndex;

protected:
	double _mu, _lambda, _dpdt_v, _dpdv_t, _cp, _beta, _Pr;
};

#else //no __cplusplus

DECLARE_C_STRUCT(MediumState)

#endif //__cplusplus


/**
 * MediumState C Functions
 */
BEGIN_C_LINKAGE
MediumState* create_mstate(int mediumIndex); //:TODO: (MILEN) rename create_mstate to MediumState_new, MediumState_register, MediumState_get, MediumState_update_Tp, MediumState_T
int mstate_register(MediumState* mstate);
MediumState* mstate_get(int mstateIndex);

int mstate_getMediumIndex(MediumState* mstate);

void mstate_update_Tp(MediumState* mstate, double T, double p);
void mstate_update_Trho(MediumState* mstate, double T, double rho);
void mstate_update_ph(MediumState* mstate, double p, double h);

double mstate_T(MediumState* mstate);
double mstate_p(MediumState* mstate);
double mstate_rho(MediumState* mstate);
double mstate_u(MediumState* mstate);
double mstate_h(MediumState* mstate);
double mstate_mu(MediumState* mstate);
double mstate_lambda(MediumState* mstate);
double mstate_dpdt_v(MediumState* mstate);
double mstate_dpdv_t(MediumState* mstate);
double mstate_cp(MediumState* mstate);
double mstate_beta(MediumState* mstate);
double mstate_Pr(MediumState* mstate);
END_C_LINKAGE


#endif /* MEDIUMSTATE_H_ */
