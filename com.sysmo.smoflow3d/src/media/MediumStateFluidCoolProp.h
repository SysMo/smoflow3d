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
#include "CPState.h"

class MyCoolPropStateClass : public CoolPropStateClassSI {
	friend class MediumState_FluidCoolProp;
	MyCoolPropStateClass(Fluid* pFluid) : CoolPropStateClassSI(pFluid){};
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
	virtual void update_ph(double p, double h);
	virtual void update_ps(double p, double s);

	virtual double u();
	virtual double cp();
	virtual double cv();
	virtual double dpdt_v();
	virtual double dpdv_t();
	virtual double dvdt_p();
	virtual double beta();
	virtual double mu();
	virtual double lambda();
	virtual double Pr();
protected:
	Fluid* pFluid;
	MyCoolPropStateClass cps;

};

#endif /* MEDIUMSTATEFLUIDCOOLPROP_H_ */
