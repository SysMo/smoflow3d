/*
 * MechanicalCompressor.h
 *
 *  Created on: Jul 31, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#ifndef MECHANICALCOMPRESSOR_H_
#define MECHANICALCOMPRESSOR_H_

#include "math/Functors.h"
#include "FlowBase.h"
#include "FlowComponent_R_2Port.h"

#ifdef __cplusplus

class MechanicalCompressor : public FlowComponent_R_2Port {
public:
	MechanicalCompressor();
	virtual ~MechanicalCompressor();

	virtual void init(MediumState* state1, MediumState* state2);

	void setDisplacementVolume(double displacementVolume) {this->displacementVolume = displacementVolume;}
	void setRotationalSpeed(double rotationalSpeed) {this->rotationalSpeed = rotationalSpeed;};

	void setVolumetricEfficiencyFunction(FunctorTwoVariables* volumetricEfficiencyFunction){this->volumetricEfficiencyFunction = volumetricEfficiencyFunction;}
	void setVolumetricFlowRateFunction(FunctorTwoVariables*  volumetricFlowRateFunction){this->volumetricFlowRateFunction = volumetricFlowRateFunction;}
	void setIsentropicEfficiencyFunction(FunctorTwoVariables* isentropicEfficiencyFunction){this->isentropicEfficiencyFunction = isentropicEfficiencyFunction;}
	void setMechanicalEfficiencyFunction(FunctorTwoVariables* mechanicalEfficiencyFunction){this->mechanicalEfficiencyFunction = mechanicalEfficiencyFunction;}

	void compute();
	void updateFluidFlows(FluidFlow* inletFlow, FluidFlow* outletFlow);

	double getIsentropicEfficiency(){return isentropicEfficiency;}
	double getMechanicalEfficiency(){return mechanicalEfficiency;}
	double getVolumetricEfficiency(){return volumetricEfficiency;}
	double getCompressorWork() {return compressorWork;}
	double getTorque() {return torque;}
	double getPressureRatio() {return pressureRatio;}

protected:
	/* Inputs */
	double displacementVolume;
	double rotationalSpeed;
	FunctorTwoVariables* volumetricEfficiencyFunction;
	FunctorTwoVariables* volumetricFlowRateFunction;
	FunctorTwoVariables* isentropicEfficiencyFunction;
	FunctorTwoVariables* mechanicalEfficiencyFunction;

	/* Results */
	double massFlowRate;
	double pressureRatio;
	double isentropicEfficiency;
	double mechanicalEfficiency;
	double volumetricEfficiency;
	double inletEnthalpyFlowRate;
	double outletEnthalpyFlowRate;
	double compressorWork;
	double torque;

	/* Intermediate variables */
	MediumState* outletFlowStateIdeal;
	double outletEnthalpyReal;
};

#else //_cplusplus
DECLARE_C_STRUCT(MechanicalCompressor)
#endif //_cplusplus

BEGIN_C_LINKAGE
MechanicalCompressor* MechanicalCompressor_new();
void MechanicalCompressor_init(MechanicalCompressor* compressor,
		MediumState* state1, MediumState* state2);

void MechanicalCompressor_setDisplacementVolume(MechanicalCompressor* compressor, double displacementVolume);
void MechanicalCompressor_setVolumetricEfficiencyFunction(MechanicalCompressor* compressor,
		FunctorTwoVariables* volumetricEfficiencyFunction);
void MechanicalCompressor_setVolumetricFlowRateFunction(MechanicalCompressor* compressor,
		FunctorTwoVariables* volumetricFlowRateFunction);
void MechanicalCompressor_setIsentropicEfficiencyFunction(MechanicalCompressor* compressor,
		FunctorTwoVariables* isentropicEfficiencyFunction);
void MechanicalCompressor_setMechanicalEfficiencyFunction(MechanicalCompressor* compressor,
		FunctorTwoVariables* mechanicalEfficiencyFunction);
void MechanicalCompressor_setRotationalSpeed(MechanicalCompressor* compressor, double rotationalSpeed);

void MechanicalCompressor_compute(MechanicalCompressor* compressor);
void MechanicalCompressor_updateFluidFlows(MechanicalCompressor* compressor, FluidFlow* inletFlow, FluidFlow* outletFlow);

double MechanicalCompressor_getPressureRatio(MechanicalCompressor* compressor);
double MechanicalCompressor_getIsentropicEfficiency(MechanicalCompressor* compressor);
double MechanicalCompressor_getMechanicalEfficiency(MechanicalCompressor* compressor);
double MechanicalCompressor_getVolumetricEfficiency(MechanicalCompressor* compressor);
double MechanicalCompressor_getCompressorWork(MechanicalCompressor* compressor);
double MechanicalCompressor_getTorque(MechanicalCompressor* compressor);
END_C_LINKAGE

#endif /* MECHANICALCOMPRESSOR_H_ */
