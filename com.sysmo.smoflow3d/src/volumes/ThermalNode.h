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
#include "media/MediumStateSolid.h"

typedef enum {
	sThermalNode_Source,
	sThermalNode_Material
} ThermalNodeType;

#ifdef __cplusplus

#include <vector>

class ThermalNode : public SmoObj {
public:
	virtual void setTemperature(double temperature);
	double getTemperature() {return temperature;}
	ThermalNodeType getType() {return nodeType;}
protected:
	ThermalNode(ThermalNodeType nodeType);
	const ThermalNodeType nodeType;
	double temperature;
};

class ThermalSourceNode : public ThermalNode {
public:
	ThermalSourceNode();
};

class ThermalMaterialNode : public ThermalNode {
public:
	ThermalMaterialNode();
	void addMaterialMass(Medium_Solid* medium, double mass);
	virtual void setTemperature(double temperature);
	void compute(double heatFlow);
	double getTemperatureDerivative() {return temperatureDerivative;}
	double getTotalHeatCapacity() {return totalHeatCapacity;}
	int getNumSubnodes() {return subnodeStates.size();}
	MediumState* getThermalState(int subnodeIndex = 1) {
		return subnodeStates.at(subnodeIndex - 1);
	}
protected:
	std::vector<MediumState_Solid*> subnodeStates;
	std::vector<double> subnodeMasses;
	double temperatureDerivative;
	double totalHeatCapacity;
};

#else // __cplusplus
DECLARE_C_STRUCT(ThermalNode)
DECLARE_C_STRUCT(ThermalSourceNode)
DECLARE_C_STRUCT(ThermalMaterialNode)
#endif //__cplusplus

BEGIN_C_LINKAGE
ThermalNode* ThermalNode_new(ThermalNodeType nodeType);
int ThermalNode_register(ThermalNode* node);
ThermalNode* ThermalNode_get(int nodeIndex);

void ThermalNode_setTemperature(ThermalNode* node, double temperature);
double ThermalNode_getTemperature(ThermalNode* node);


void ThermalMaterialNode_addMaterialMass(ThermalMaterialNode* node, Medium_Solid* medium, double mass);
void ThermalMaterialNode_compute(ThermalMaterialNode* node, double heatFlow);
double ThermalMaterialNode_getTemperatureDerivative(ThermalMaterialNode* node);
double ThermalMaterialNode_getTotalHeatCapacity(ThermalMaterialNode* node);
ThermalMaterialNode* ThermalMaterialNode_getFromState(MediumState* state);
MediumState* ThermalMaterialNode_getThermalState(ThermalMaterialNode* node, int subnodeIndex);
END_C_LINKAGE

#endif /* THERMALNODE_H_ */
