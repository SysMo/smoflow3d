/*
 * ThermalConductionElement.h
 *
 *  Created on: Aug 5, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#ifndef THERMALCONDUCTIONELEMENT_H_
#define THERMALCONDUCTIONELEMENT_H_

#include "media/Medium.h"
#include "volumes/ThermalNode.h"
#include "flow/FlowBase.h"
#include "Eigen/Core"

#ifdef __cplusplus

class ThermalConductionElement {
public:
	ThermalConductionElement(Medium* medium, int numNodes);
	virtual ~ThermalConductionElement();
	void assignNode(size_t nodeIndex, ThermalNode* node);
	void setInteractionCoefficient(size_t row, size_t column, double value);
	void computeExplicit();
	double getHeatFlow(size_t nodeIndex);
	void getFlow(size_t nodeIndex, HeatFlow* flow);
protected:
	int numNodes;
	std::vector<ThermalNode*> nodes;
	std::vector<double> heatFlows;
	MediumState* internalState;
	Eigen::MatrixXd interactionCoefficients;
};

#else //__cplusplus
DECLARE_C_STRUCT(ThermalConductionElement)
#endif //__cplusplus

BEGIN_C_LINKAGE
ThermalConductionElement* ThermalConductionElement_new(
		Medium* medium, int numNodes);
ThermalConductionElement* ThermalConductionElement_Line_new(
		Medium_Solid* medium, double area, double length);
void ThermalConductionElement_assignNode(
		ThermalConductionElement* element, size_t nodeIndex, ThermalNode* node);
void ThermalConductionElement_setInteractionCoefficient(
		ThermalConductionElement* element, size_t row, size_t column, double value);
void ThermalConductionElement_computeExplicit(
		ThermalConductionElement* element);
double ThermalConductionElement_getHeatFlow(
		ThermalConductionElement* element, size_t nodeIndex);
void ThermalConductionElement_getFlow(
		ThermalConductionElement* element, size_t nodeIndex, FluidFlow* flow);
END_C_LINKAGE

#endif /* THERMALCONDUCTIONELEMENT_H_ */
