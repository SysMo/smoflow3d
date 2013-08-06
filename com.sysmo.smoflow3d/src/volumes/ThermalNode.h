/*
 * ThermalNode.h
 *
 *  Created on: Aug 5, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#ifndef THERMALNODE_H_
#define THERMALNODE_H_

#include "util/CommonDefinitions.h"

#ifdef __cplusplus

#include <vector>
#include "media/MediumStateSolid.h"

class ThermalNode : public SmoComponent {
public:
	ThermalNode();
	virtual ~ThermalNode();

	void addMaterialMass(Medium_Solid* medium, double mass);
	void setTemperature(double temperature);
	void compute(double heatFlow);
	double getTemperatureDerivative() {return temperatureDerivative;}
	double getTotalHeatCapacity() {return totalHeatCapacity;}
	int getNumSubnodes() {return subnodeStates.size();}
	MediumState* getThermalState(int subnodeIndex = 0) {
		return subnodeStates.at(subnodeIndex);
	}
protected:
	std::vector<MediumStateSolid*> subnodeStates;
	std::vector<double> subnodeMasses;
	double temperatureDerivative;
	double totalHeatCapacity;
};

#endif /* THERMALNODE_H_ */

#else // __cplusplus
DECLARE_C_STRUCT(ThermalNode)
#endif //__cplusplus

BEGIN_C_LINKAGE
ThermalNode* ThermalNode_new();
ThermalNode* ThermalNode_getFromState(MediumStateSolid* state);
void ThermalNode_addMaterialMass(ThermalNode* node, Medium_Solid* medium, double mass);
void ThermalNode_setTemperature(ThermalNode* node, double temperature);
void ThermalNode_compute(ThermalNode* node, double heatFlow);
double ThermalNode_getTemperatureDerivative(ThermalNode* node);
double ThermalNode_getTotalHeatCapacity(ThermalNode* node);
MediumState* getThermalState(ThermalNode* node, int subnodeIndex = 0);
END_C_LINKAGE
