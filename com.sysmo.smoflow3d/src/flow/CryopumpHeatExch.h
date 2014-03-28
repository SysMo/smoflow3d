/*
 * CryopumpHeatExch.h
 *
 *  Created on: Jul 31, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#ifndef CRYOPUMPHEATEXCH_H_
#define CRYOPUMPHEATEXCH_H_

#include "math/Functors.h"
#include "flow/FlowBase.h"
#include "media/MediumState.h"

#ifdef __cplusplus

class CryopumpHeatExch : public SmoComponent {
public:
	CryopumpHeatExch();
	virtual ~CryopumpHeatExch();

	virtual void init(MediumState* inletState, MediumState* outletState);

	void setRotationalSpeed(double rotationalSpeed) {this->rotationalSpeed = rotationalSpeed;}

	void setComputationMethod(int computationMethod) {this->computationMethod = computationMethod;}
	bool computeUsingOutletTemperature() {return computationMethod == 1;}

	void setDisplacementVolume(double displacementVolume) {this->displacementVolume = displacementVolume;}
	void setVolumetricEfficiencyFunction(FunctorTwoVariables* volumetricEfficiencyFunction){this->volumetricEfficiencyFunction = volumetricEfficiencyFunction;}
	void setIsentropicEfficiencyFunction(FunctorTwoVariables* isentropicEfficiencyFunction){this->isentropicEfficiencyFunction = isentropicEfficiencyFunction;}
	void setMechanicalEfficiencyFunction(FunctorTwoVariables* mechanicalEfficiencyFunction){this->mechanicalEfficiencyFunction = mechanicalEfficiencyFunction;}
	void setOutletTemperatureFunction(FunctorTwoVariables* outletTemperatureFunction) {this->outletTemperatureFunction = outletTemperatureFunction;}
	void setHeatFlowRateToPumpReservoir(double heatFlowRateToPumpReservoir) {this->heatFlowRateToPumpReservoirParam = heatFlowRateToPumpReservoir;}
	void setFractionOfExtraHeatToFluid(double fractionOfExtraHeatToFluid) {this->fractionOfExtraHeatToFluid = fractionOfExtraHeatToFluid;}

	virtual void compute();
	void updateFluidFlows(FluidFlow* inletFlow, FluidFlow* outletFlow);

	double getIsentropicEfficiency(){return isentropicEfficiency;}
	double getMechanicalEfficiency(){return mechanicalEfficiency;}
	double getVolumetricEfficiency(){return volumetricEfficiency;}
	double getPumpWork() {return pumpWork;}
	double getTorque() {return torque;}
	double getPressureRatio() {return pressureRatio;}
	double getOutletTemperature() {return outletTemperature;}
	double getHeatFlowRateToPumpReservoir() {return heatFlowRateToPumpReservoir;}

protected:
	/* Inputs */
	double rotationalSpeed;

	/* Inputs (parameters) */
	int computationMethod;
	double displacementVolume;
	FunctorTwoVariables* volumetricEfficiencyFunction;
	FunctorTwoVariables* isentropicEfficiencyFunction;
	FunctorTwoVariables* mechanicalEfficiencyFunction;
	FunctorTwoVariables* outletTemperatureFunction;
	double heatFlowRateToPumpReservoirParam;
	double fractionOfExtraHeatToFluid;

	/* Outputs (results) */
	double massFlowRate;
	double pressureRatio;
	double isentropicEfficiency;
	double mechanicalEfficiency;
	double volumetricEfficiency;
	double pumpWork;
	double torque;
	double outletTemperature;
	double heatFlowRateToPumpReservoir;


	/* Intermediate variables */
	MediumState* outletFlowStateIdeal;
	MediumState* outletFlowStateReal;
	double outletEnthalpyReal;

	/* States (external) */
	MediumState* inletState;
	MediumState* outletState;
};

#else //_cplusplus
DECLARE_C_STRUCT(CryopumpHeatExch)
#endif //_cplusplus

BEGIN_C_LINKAGE
CryopumpHeatExch* CryopumpHeatExch_new();
void CryopumpHeatExch_init(CryopumpHeatExch* pump, MediumState* inletState, MediumState* outletState);

void CryopumpHeatExch_setRotationalSpeed(CryopumpHeatExch* pump, double rotationalSpeed);

void CryopumpHeatExch_setComputationMethod(CryopumpHeatExch* pump, int computationMethod);

void CryopumpHeatExch_setDisplacementVolume(CryopumpHeatExch* pump, double displacementVolume);
void CryopumpHeatExch_setVolumetricEfficiencyFunction(CryopumpHeatExch* pump, FunctorTwoVariables* volumetricEfficiencyFunction);
void CryopumpHeatExch_setIsentropicEfficiencyFunction(CryopumpHeatExch* pump, FunctorTwoVariables* isentropicEfficiencyFunction);
void CryopumpHeatExch_setMechanicalEfficiencyFunction(CryopumpHeatExch* pump, FunctorTwoVariables* mechanicalEfficiencyFunction);
void CryopumpHeatExch_setOutletTemperatureFunction(CryopumpHeatExch* pump, FunctorTwoVariables* outletTemperatureFunction);
void CryopumpHeatExch_setHeatFlowRateToPumpReservoir(CryopumpHeatExch* pump, double heatFlowRateToPumpReservoir);
void CryopumpHeatExch_setFractionOfExtraHeatToFluid(CryopumpHeatExch* pump, double fractionOfExtraHeatToFluid);

void CryopumpHeatExch_compute(CryopumpHeatExch* pump);
void CryopumpHeatExch_updateFluidFlows(CryopumpHeatExch* pump, FluidFlow* inletFlow, FluidFlow* outletFlow);

double CryopumpHeatExch_getPressureRatio(CryopumpHeatExch* pump);
double CryopumpHeatExch_getIsentropicEfficiency(CryopumpHeatExch* pump);
double CryopumpHeatExch_getMechanicalEfficiency(CryopumpHeatExch* pump);
double CryopumpHeatExch_getVolumetricEfficiency(CryopumpHeatExch* pump);
double CryopumpHeatExch_getPumpWork(CryopumpHeatExch* pump);
double CryopumpHeatExch_getTorque(CryopumpHeatExch* pump);
double CryopumpHeatExch_getOutletTemperature(CryopumpHeatExch* pump);
double CryopumpHeatExch_getHeatFlowRateToPumpReservoir(CryopumpHeatExch* pump);
END_C_LINKAGE

#endif /* CRYOPUMPHEATEXCH_H_ */
