/*
 * ThermalConduction2Node.h
 *
 *  Created on: Dec 13, 2018
 *      Author: Milen Borisov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#ifndef THERMALCONDUCTION2NODE_H_
#define THERMALCONDUCTION2NODE_H_

#include "media/Medium.h"
#include "volumes/ThermalNode.h"
#include "flow/FlowBase.h"

#ifdef __cplusplus

#include "Eigen/Core"

class ThermalConduction2Node : SmoComponent {
public:
	ThermalConduction2Node();
	virtual ~ThermalConduction2Node();

	void init(ThermalNode* node1, ThermalNode* node2);

	virtual void compute() = 0;

	double getHeatFlowRate1();
	double getHeatFlowRate2();
	void updateHeatFlow1(HeatFlow* flow);
	void updateHeatFlow2(HeatFlow* flow);

protected:
	ThermalNode* node1;
	ThermalNode* node2;
	double heatFlowRate1;
	double heatFlowRate2;
};

#else //__cplusplus
DECLARE_C_STRUCT(ThermalConduction2Node)
#endif //__cplusplus

BEGIN_C_LINKAGE
ThermalConduction2Node* ThermalConduction2Node_Linear_new(
		Medium_Solid* medium, double area, double length);

ThermalConduction2Node* ThermalConduction2Node_2Material_new(
			Medium_Solid* medium1, Medium_Solid* medium2,
			double area, double length1, double length2,
			double contactResistance);

void ThermalConduction2Node_init(
		ThermalConduction2Node* conduction,
		ThermalNode* node1, ThermalNode* node2);

void ThermalConduction2Node_compute(ThermalConduction2Node* conduction);

double ThermalConduction2Node_getHeatFlowRate1(ThermalConduction2Node* conduction);
double ThermalConduction2Node_getHeatFlowRate2(ThermalConduction2Node* conduction);
void ThermalConduction2Node_updateHeatFlow1(
		ThermalConduction2Node* conduction, HeatFlow* flow);
void ThermalConduction2Node_updateHeatFlow2(
		ThermalConduction2Node* conduction, HeatFlow* flow);
END_C_LINKAGE

#endif /* THERMALCONDUCTION2NODE_H_ */
