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

#include "Medium.h"
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



BEGIN_C_LINKAGE
MediumState* MediumState_new(int mediumIndex);
int MediumState_register(MediumState* mstate);
MediumState* MediumState_get(int mstateIndex);

int MediumState_getMediumIndex(MediumState* mstate);

void MediumState_update_Tp(MediumState* mstate, double T, double p);
void MediumState_update_Trho(MediumState* mstate, double T, double rho);
void MediumState_update_ph(MediumState* mstate, double p, double h);

double MediumState_T(MediumState* mstate);
double MediumState_p(MediumState* mstate);
double MediumState_rho(MediumState* mstate);
double MediumState_u(MediumState* mstate);
double MediumState_h(MediumState* mstate);
double MediumState_mu(MediumState* mstate);
double MediumState_lambda(MediumState* mstate);
double MediumState_dpdt_v(MediumState* mstate);
double MediumState_dpdv_t(MediumState* mstate);
double MediumState_cp(MediumState* mstate);
double MediumState_beta(MediumState* mstate);
double MediumState_Pr(MediumState* mstate);
END_C_LINKAGE


#endif /* MEDIUMSTATE_H_ */
