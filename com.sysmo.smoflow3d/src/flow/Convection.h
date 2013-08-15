/*
 * Convection.h
 *
 *  Created on: Aug 10, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#ifndef CONVECTION_H_
#define CONVECTION_H_

#include "util/CommonDefinitions.h"
#include "media/MediumState.h"
#include "volumes/ThermalNode.h"
#include "FlowBase.h"

#ifdef __cplusplus

/*
class ConvectionModel {
public:
	ConvectionModel();
	virtual ~ConvectionModel(){};
	double getCharacteristicLength(){return characteristicLength;}
	double getHeatExchangeArea(){return heatExchangeArea;}
protected:
	double characteristicLength;
	double heatExchangeArea;
};
*/

class Convection {
public:
	Convection();
	virtual ~Convection();
	double getCharacteristicLength(){return characteristicLength;}
	double getHeatExchangeArea(){return heatExchangeArea;}
	void init(MediumState* fluidState, ThermalNode* wallNode);
	void setHeatExchangeGain(double gain) {
		this->heatExchangeGain = gain;}
	double getPrandtlNumber() {return Pr;}
	double getNusseltNumber() {return Nu;}
	void setConvectionCoefficient(double convectionCoefficient) {
		this->convectionCoefficient = convectionCoefficient;}
	double getConvectionCoefficient() {
		return convectionCoefficient;}
	double getHeatFlowRate() {return heatFlowRate;}
	void getFlow_Wall(HeatFlow* flow);
	void getFlow_Fluid(FluidFlow* flow);
protected:
	// Parameters
	double characteristicLength;
	double heatExchangeArea;
	double heatExchangeGain;

	MediumState* fluidState;
	ThermalNode* wallNode;
	MediumState* filmState;

	double Pr;
	double Nu;
	double convectionCoefficient;
	double heatFlowRate;
};

#else //__cplusplus
DECLARE_C_STRUCT(Convection)
#endif //__cplusplus


#endif /* CONVECTION_H_ */
