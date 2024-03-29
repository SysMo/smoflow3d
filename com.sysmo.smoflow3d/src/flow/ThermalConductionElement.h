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

#ifdef __cplusplus

#include "Eigen/Core"

class ThermalConductionElement : SmoComponent {
public:
	ThermalConductionElement(Medium* medium, int numNodes);
	virtual ~ThermalConductionElement();

	void assignNode(size_t nodeIndex, ThermalNode* node);
	void setInteractionCoefficient(size_t row, size_t column, double value);

	void computeExplicit();

	double getHeatFlowRate(size_t nodeIndex);
	void updateHeatFlow(size_t nodeIndex, HeatFlow* flow);

protected:
	std::vector<ThermalNode*> nodes;
	std::vector<double> heatFlows;
	MediumState* internalState;
	Eigen::MatrixXd interactionCoefficients;
};

#else //__cplusplus
DECLARE_C_STRUCT(ThermalConductionElement)
#endif //__cplusplus

BEGIN_C_LINKAGE
ThermalConductionElement* ThermalConductionElement_new(Medium* medium, int numNodes);
ThermalConductionElement* ThermalConductionElement_Line_new(Medium_Solid* medium, double area, double length);

void ThermalConductionElement_assignNode(ThermalConductionElement* element, size_t nodeIndex, ThermalNode* node);
void ThermalConductionElement_setInteractionCoefficient(ThermalConductionElement* element, size_t row, size_t column, double value);

void ThermalConductionElement_computeExplicit(ThermalConductionElement* element);

double ThermalConductionElement_getHeatFlowRate(ThermalConductionElement* element, size_t nodeIndex);
void ThermalConductionElement_updateHeatFlow(ThermalConductionElement* element, size_t nodeIndex, HeatFlow* flow);
END_C_LINKAGE

#endif /* THERMALCONDUCTIONELEMENT_H_ */
