/*
 * MediumStateFluidCoolProp.h
 *
 *  Created on: Jul 28, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#ifndef MEDIUMSTATEFLUIDCOOLPROP_H_
#define MEDIUMSTATEFLUIDCOOLPROP_H_

#include "MediumState.h"
#include "Medium.h"
#include "CoolProp/CPState.h"

class SmoCoolPropStateClass : public CoolPropStateClassSI {
	friend class MediumState_FluidCoolProp;
public:
	SmoCoolPropStateClass(Fluid* pFluid) : CoolPropStateClassSI(pFluid) {};
//	double Pr();
//	double gamma();
};

class MediumState_FluidCoolProp : public MediumState {
public:
	MediumState_FluidCoolProp(Medium_CompressibleFluid_CoolProp* medium);
	virtual ~MediumState_FluidCoolProp();

protected:
	void pre_update();
	void post_update();
public:
	virtual void update_Tp(double T, double p);
	virtual void update_Trho(double T, double rho);
	virtual void update_prho(double p, double rho);
	virtual void update_ph(double p, double h);
	virtual void update_ps(double p, double s);

	virtual double u();
	virtual double s();
	virtual double cp();
	virtual double cv();
	virtual double dpdt_v();
	virtual double dpdv_t();
	virtual double dpdrho_t();
	virtual double dvdt_p();
	virtual double beta();
	virtual double mu();
	virtual double lambda();
	virtual double R();
	// Overwritten to allow working in the two-phase region
	virtual double Pr();
	virtual double gamma();
	// Two-phase functions
	virtual bool isSupercritical();
	virtual bool isTwoPhase();
	virtual double x();
	virtual double deltaTSat();
	virtual double TSat();
protected:
	Fluid* pFluid;
	SmoCoolPropStateClass cps;
};

#endif /* MEDIUMSTATEFLUIDCOOLPROP_H_ */
