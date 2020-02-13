/*
 * Radiation.h
 *
 *  Created on: Oct 26, 2016
 *      Author: Atanas Pavlov, Milen Birisov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#ifndef RADIATION_H_
#define RADIATION_H_

#include "util/CommonDefinitions.h"
#include "media/MediumState.h"
#include "volumes/ThermalNode.h"
#include "flow/FlowBase.h"

#ifdef __cplusplus

class Radiation : public SmoComponent {
public:
	Radiation();
	virtual ~Radiation();

	void setHeatExchangeGain(double gain) {this->heatExchangeGain = gain;}

	double getHeatFlowRate() {return heatFlowRate;} //:TRICKY: heat flow rate from port-1 to port-2

protected:
	double heatExchangeGain;
	double heatFlowRate;
};

#else //__cplusplus
DECLARE_C_STRUCT(Radiation)
#endif //__cplusplus

BEGIN_C_LINKAGE
void Radiation_setHeatExchangeGain(Radiation* radiation, double gain);

double Radiation_getHeatFlowRate(Radiation* radiation);
END_C_LINKAGE

#endif /* RADIATION_H_ */
