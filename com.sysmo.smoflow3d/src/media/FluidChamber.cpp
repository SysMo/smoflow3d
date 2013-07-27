/*
 * FluidChamber.cpp
 *
 *  Created on: Jul 26, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "FluidChamber.h"

FluidChamber::FluidChamber() {
	// TODO Auto-generated constructor stub

}

FluidChamber::~FluidChamber() {
	// TODO Auto-generated destructor stub
}

void FluidChamber::computeStateDerivatives(double massTimeDerivatie, double energyTimeDerivative, double volumeTimeDerivative) {
	Real fluidMass = state->rho() * volume;
	Real c1 = massTimeDerivatie/fluidMass - volumeTimeDerivative/volume;
	stateTimeDerivatives.rho = state->rho() * c1;
	//stateTimeDerivatives.specificVolume = - specificVolume * c1;

	Real alpha_m = massTimeDerivatie /state->rho();
	Real alpha_T = fluidMass * state->dvdT_constp();
	Real alpha_p = fluidMass / dp_dv_t;
	Real beta_m = massTimeDerivatie * state->u();
	Real beta_T = fluidMass * (state->cp() - state->p * dv_dt_p);
	Real beta_p = - fluidMass * (state->p / dp_dv_t + state->T * dv_dt_p);

	stateTimeDerivatives.T = (beta_p * (volumeTimeDerivative - alpha_m) - alpha_p * (energyTimeDerivative - beta_m)) /
			(alpha_T * beta_p - alpha_p * beta_T);
	stateTimeDerivatives.p = ( - beta_T * (volumeTimeDerivative - alpha_m) + alpha_T * (energyTimeDerivative - beta_m)) /
			(alpha_T * beta_p - alpha_p * beta_T);


}
