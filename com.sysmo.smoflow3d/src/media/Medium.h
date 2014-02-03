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
typedef enum {sMediumCompositionUndefined, sPure, sMixture} MediumCompositionType;
typedef enum {
	sMediumAbstractType,
	sCompressibleFluidCoolProp,
	sIncompressibleLiquidCoolProp,
	sSolidThermal
} MediumConcreteTypes;

#include "CoolProp/GlobalConstants.h"
typedef enum params ThermodynamicVariable;

#ifdef __cplusplus

#include <map>
#include "CoolProp/CoolProp.h"

struct Medium {
	MediumConcreteTypes concreteType;
	MediumPhase phase;
	MediumCompressibility compressibility;
	MediumCompositionType compositionType;
	int numStates;
	params naturalStates[2];
	std::string name;

	Medium() {
		concreteType = sMediumAbstractType;
		phase = sMediumPhaseUndefined;
		compressibility = sMediumCompressibilityUndefined;
		compositionType = sMediumCompositionUndefined;
		numStates = 0;
	}

	virtual ~Medium(){
	}
};

struct Medium_Fluid : public Medium {
	Medium_Fluid() {
		phase = sFluid;
	}
};

struct Medium_CompressibleFluid : public Medium_Fluid {
	Medium_CompressibleFluid() {
		compressibility = sCompressible;
	}
};

struct Medium_CompressibleFluid_CoolProp : public Medium_CompressibleFluid {
	Medium_CompressibleFluid_CoolProp(Fluid* fluid) {
		concreteType = sCompressibleFluidCoolProp;
		compositionType = sPure;
		numStates = 2;
		naturalStates[0] = iT;
		naturalStates[1] = iD;
		this->fluid = fluid;
	}
	Fluid* fluid;
};

struct Medium_IncompressibleLiquid : public Medium_Fluid {
	Medium_IncompressibleLiquid() {
		compressibility = sIncompressible;
	}
};

struct Medium_IncompressibleLiquid_CoolProp : public Medium_IncompressibleLiquid {
	Medium_IncompressibleLiquid_CoolProp() {
		concreteType = sIncompressibleLiquidCoolProp;
		compositionType = sPure;
		numStates = 2;
		naturalStates[0] = iT;
		naturalStates[1] = iP;
	}
};

struct Medium_Solid : public Medium {
	Medium_Solid() {
		phase = sSolid;
		concreteType = sSolidThermal;
		densityFunction = NULL;
		thermalConductivityFunction = NULL;
		heatCapacityFunction = NULL;
		enthalpyFunction = NULL;
	}
	FunctorOneVariable* densityFunction;
	FunctorOneVariable* thermalConductivityFunction;
	FunctorOneVariable* heatCapacityFunction;
	FunctorOneVariable* enthalpyFunction;
};

#else

DECLARE_C_STRUCT(Medium)
DECLARE_C_STRUCT(Medium_Solid)

#endif //__cplusplus


BEGIN_C_LINKAGE
void Medium_register(MediumConcreteTypes mediumType, const char* mediumName, int mediumIndex);
void Medium_registerSolidUserDefined(const char* mediumName, int mediumIndex, const char* density, const char* thermalConductivity, const char* heatCapacity, const char* enthalpy);

Medium* Medium_get(int mediumIndex);
int Medium_index(Medium* medium);

MediumPhase Medium_getPhase(Medium* medium);
MediumCompressibility Medium_getCompressibility(Medium* medium);
MediumCompositionType Medium_getCompositionType(Medium* medium);
MediumConcreteTypes Medium_getConcreteType(Medium* medium);
END_C_LINKAGE

#endif /* MEDIAREGISTRY_H_ */
