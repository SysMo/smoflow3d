/*
 * RadiationTwoSurfaces.cpp
 *
 *  Created on: Feb 13, 2020
 *      Author: Atanas Pavlov, Milen Borisov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "RadiationTwoSurfaces.h"
#include "math/Functors.h"
#include "util/CommonDefinitions.h"

using namespace smoflow;

/**
 * RadiationTwoSurfaces - C++
 */
RadiationTwoSurfaces::RadiationTwoSurfaces(
		double emissivity1, double emissivity2,
		double heatExchangeArea1, double heatExchangeArea2,
		double shapeFactor12) {
	this->emissivity1 = emissivity1;
	this->emissivity2 = emissivity2;
	this->heatExchangeArea1 = heatExchangeArea1;
	this->heatExchangeArea2 = heatExchangeArea2;
	this->shapeFactor12 = shapeFactor12;

	this->wallNode1 = NULL;
	this->wallNode2 = NULL;
}

RadiationTwoSurfaces::~RadiationTwoSurfaces() {
}

void RadiationTwoSurfaces::init(ThermalNode* wallNode1, ThermalNode* wallNode2) {
	this->wallNode1 = wallNode1;
	this->wallNode2 = wallNode2;
}

void RadiationTwoSurfaces::compute() {
	double wallTemperature1 = wallNode1->getTemperature();
	double wallTemperature2 = wallNode2->getTemperature();

	// Calculate the heat flow rate (from wall to the fluid)
	heatFlowRate = heatExchangeGain * cst::StefanBoltzmannConstant *
			(m::pow(wallTemperature1, 4) - m::pow(wallTemperature2, 4)) /
			(
					(1 - emissivity1)/(heatExchangeArea1*emissivity1) +
					(1/(heatExchangeArea1*shapeFactor12)) +
					(1 - emissivity2)/(heatExchangeArea2*emissivity2)
			);
}

void RadiationTwoSurfaces::updateHeatFlow1(HeatFlow* flow1) {
	flow1->enthalpyFlowRate = -heatFlowRate;
}

void RadiationTwoSurfaces::updateHeatFlow2(HeatFlow* flow2) {
	flow2->enthalpyFlowRate = heatFlowRate;
}


/**
 * RadiationTwoSurfaces - C
 */
RadiationTwoSurfaces* RadiationTwoSurfaces_new(
		double emissivity1, double emissivity2,
		double heatExchangeArea1, double heatExchangeArea2,
		double shapeFactor12) {
	return new RadiationTwoSurfaces(
			emissivity1, emissivity2,
			heatExchangeArea1, heatExchangeArea2,
			shapeFactor12);
}

void RadiationTwoSurfaces_init(RadiationTwoSurfaces* radiation, ThermalNode* wallNode1, ThermalNode* wallNode2) {
	radiation->init(wallNode1, wallNode2);
}

void RadiationTwoSurfaces_compute(RadiationTwoSurfaces* radiation) {
	radiation->compute();
}

void RadiationTwoSurfaces_updateHeatFlow1(RadiationTwoSurfaces* radiation, HeatFlow* flow1) {
	radiation->updateHeatFlow1(flow1);
}

void RadiationTwoSurfaces_updateHeatFlow2(RadiationTwoSurfaces* radiation, HeatFlow* flow2) {
	radiation->updateHeatFlow2(flow2);
}
