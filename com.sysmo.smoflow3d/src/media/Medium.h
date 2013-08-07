/*
 * Medium.h
 *
 *  Created on: Jul 22, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#ifndef MEDIAREGISTRY_H_
#define MEDIAREGISTRY_H_

#include "util/CommonDefinitions.h"
#include "math/Functors.h"


typedef enum {sMediumPhaseUndefined, sSolid, sLiquid, sGas, sFluid, sAnyPhase} MediumPhase;
typedef enum {sMediumCompressibilityUndefined, sIncompressible, sCompressible} MediumCompressibility;
typedef enum {sMediumCompositionUndefined, sPure, sMixture} MediumComposition;
typedef enum {
	sMediumTypeUndefined,
	sCompressibleFluidCoolProp,
	sIncompressibleLiquidCoolProp,
	sSolidThermal
} MediumKnownTypes;

#ifdef __cplusplus

#include <map>
#include "CoolProp/CoolProp.h"

struct Medium {
	MediumKnownTypes mediumType;
	MediumPhase phase;
	MediumCompressibility compressibility;
	MediumComposition composition;
	int numStates;
	params naturalStates[2];
	char name[];
	Medium() {
		mediumType = sMediumTypeUndefined;
		phase = sMediumPhaseUndefined;
		compressibility = sMediumCompressibilityUndefined;
		composition = sMediumCompositionUndefined;
		numStates = 0;
	}
	virtual ~Medium(){}
};

struct Medium_Fluid : public Medium {
	Medium_Fluid() {phase = sFluid;}
};

struct Medium_CompressibleFluid : public Medium_Fluid {
	Medium_CompressibleFluid() {compressibility = sCompressible;}
};

struct Medium_CompressibleFluid_CoolProp : public Medium_CompressibleFluid {
	Medium_CompressibleFluid_CoolProp(Fluid* fluid) {
		mediumType = sCompressibleFluidCoolProp;
		composition = sPure;
		numStates = 2;
		naturalStates[0] = iT;
		naturalStates[1] = iD;
		this->fluid = fluid;
	}
	Fluid* fluid;
};

struct Medium_IncompressibleLiquid : public Medium_Fluid {
	Medium_IncompressibleLiquid() {compressibility = sIncompressible;}
};

struct Medium_IncompressibleLiquid_CoolProp : public Medium_IncompressibleLiquid {
	Medium_IncompressibleLiquid_CoolProp() {
		mediumType = sIncompressibleLiquidCoolProp;
		composition = sPure;
		numStates = 2;
		naturalStates[0] = iT;
		naturalStates[1] = iP;
	}
};

struct Medium_Solid : public Medium {
	Medium_Solid() {phase = sSolid;}
	FunctorOneVariable* densityFunction;
	FunctorOneVariable* thermalConductivityFunction;
	FunctorOneVariable* heatCapacityFunction;
};

#else

DECLARE_C_STRUCT(Medium)

#endif //__cplusplus


BEGIN_C_LINKAGE
void Medium_register(MediumKnownTypes mediumType, const char* mediumName, int mediumIndex);
Medium* Medium_get(int mediumIndex);
int Medium_index(Medium* medium);
END_C_LINKAGE

#endif /* MEDIAREGISTRY_H_ */
