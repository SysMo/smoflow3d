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

#ifdef __cplusplus

#include "MediaRegistry.h"
#include "CPState.h"

class MediumState : public CoolPropStateClassSI {
public:
	MediumState(int mediumIndex);
	MediumState(Medium* medium);
	virtual ~MediumState();
	void start();
	void update_Tp(double T, double p);
	void update_Trho(double T, double rho);
	void update_ph(double p, double h);
	void update_prho(double p, double rho);
	void update_ps(double p, double s);
	void post_update();
protected:
	double _mu, _lambda, _dpdt_v, _dpdv_t, _cp, _beta, _Pr;
};
#else
DECLARE_C_STRUCT(MediumState)
#endif //__cplusplus


BEGIN_C_LINKAGE
MediumState* create_mstate(int mediumIndex);
int mstate_register(MediumState* mstate);
MediumState* mstate_get(int mstateIndex);
void mstate_update_Tp(MediumState* mstate, double T, double p);
void mstate_update_Trho(MediumState* mstate, double T, double rho);
void mstate_update_ph(MediumState* mstate, double p, double h);
double mstate_T(MediumState* mstate);
double mstate_p(MediumState* mstate);
double mstate_rho(MediumState* mstate);
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
