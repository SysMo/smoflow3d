/*
 * MechanicalCompressor.h
 *
 *  Created on: Jul 31, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#ifndef MECHANICALCOMPRESSOR_H_
#define MECHANICALCOMPRESSOR_H_

#include "FlowRComponent.h"
#include "FluidFlow.h"

#ifdef __cplusplus

#include "util/Functors.h"

class MechanicalCompressor : public FlowRComponent {
public:
	MechanicalCompressor();
	virtual ~MechanicalCompressor();
	virtual void init(MediumState* state1, MediumState* state2);
	void setDisplacementVolume(double displacementVolume) {this->displacementVolume = displacementVolume;}
	void setRotationalSpeed(double rotationalSpeed) {this->rotationalSpeed = rotationalSpeed;};

	void setIsentropicEfficiencyFunction(FunctorTwoVariables* isentropicEfficiencyFunction){this->isentropicEfficiencyFunction = isentropicEfficiencyFunction;}
	void setMechanicalEfficiencyFunction(FunctorTwoVariables* mechanicalEfficiencyFunction){this->mechanicalEfficiencyFunction = mechanicalEfficiencyFunction;}
	void setVolumetricEfficiencyFunction(FunctorTwoVariables* volumetricEfficiencyFunction){this->volumetricEfficiencyFunction = volumetricEfficiencyFunction;}
	void setVolumetricFlowRateFunction(FunctorTwoVariables*  volumetricFlowRateFunction){this->volumetricFlowRateFunction = volumetricFlowRateFunction;}

	void compute();
	void getInletFlowRates(FluidFlow* inletFlow);
	void getOutletFlowRates(FluidFlow* outletFlow);
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
	FunctorTwoVariables* isentropicEfficiencyFunction;
	FunctorTwoVariables* mechanicalEfficiencyFunction;
	FunctorTwoVariables* volumetricEfficiencyFunction;
	FunctorTwoVariables* volumetricFlowRateFunction;


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
void MechanicalCompressor_setRotationalSpeed(MechanicalCompressor* compressor, double rotationalSpeed);
void MechanicalCompressor_setIsentropicEfficiencyFunction(MechanicalCompressor* compressor,
		FunctorTwoVariables* isentropicEfficiencyFunction);
void MechanicalCompressor_setMechanicalEfficiencyFunction(MechanicalCompressor* compressor,
		FunctorTwoVariables* mechanicalEfficiencyFunction);
void MechanicalCompressor_setVolumetricEfficiencyFunction(MechanicalCompressor* compressor,
		FunctorTwoVariables* volumetricEfficiencyFunction);
void MechanicalCompressor_compute(MechanicalCompressor* compressor);
void MechanicalCompressor_getInletFlowRates(MechanicalCompressor* compressor, FluidFlow* inletFlow);
void MechanicalCompressor_getOutletFlowRates(MechanicalCompressor* compressor, FluidFlow* outletFlow);
double MechanicalCompressor_getPressureRatio(MechanicalCompressor* compressor);
double MechanicalCompressor_getIsentropicEfficiency(MechanicalCompressor* compressor);
double MechanicalCompressor_getMechanicalEfficiency(MechanicalCompressor* compressor);
double MechanicalCompressor_getVolumetricEfficiency(MechanicalCompressor* compressor);
double MechanicalCompressor_getCompressorWork(MechanicalCompressor* compressor);
double MechanicalCompressor_getTorque(MechanicalCompressor* compressor);
END_C_LINKAGE

#endif /* MECHANICALCOMPRESSOR_H_ */
