/*
 * MediaHydrogen.cpp
 *
 *  Created on: Jul 22, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "CoolProp.h"
#include "CPState.h"
#include "CoolPropTools.h"
#include <string>
#include <iostream>

extern FluidsContainer Fluids;

class MediaState : public CoolPropStateClassSI {
public:
	MediaState(Fluid *pFluid) : CoolPropStateClassSI(pFluid) {
		_rho = _HUGE;
	}
	void update_Tp(double T, double p) {
		//CoolPropStateClassSI::update_Tp(iT, T, iP, p);
		_T = T;
		_p = p;
		//_rho = _HUGE;
		if (ValidNumber(_rho)) {
			_rho = pFluid->density_Tp(T, p, _rho);
		} else {
			//std::cout << "Slow call to density calc" << std::endl;
			_rho = pFluid->density_Tp(T, p);
		}
	}
	void update_Tp(double T, double p) {

	}

};

int main(int argc, char** argv) {
	std::string fluidName = "parahydrogen";
	Fluid* pFluid;
	pFluid = Fluids.get_fluid(fluidName);
	MediaState cps(pFluid);
	for (int i = 0; i < 1e6; i++) {
		cps.update_Tp(288, 700e5);
	}
	std::cout << cps.T() << std::endl;
	std::cout << cps.p() << std::endl;
	std::cout << cps.rho() << std::endl;
	return 0;
}
