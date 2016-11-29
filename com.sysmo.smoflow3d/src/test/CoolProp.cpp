/*
 * CoolProp.cpp
 *
 *  Created on: Nov 29, 2016
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */
/*
 * Functors.cpp
 *
 *  Created on: Aug 4, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "windows.h"
#include "stdio.h"

int main() {
	// Define DLL functions
	typedef double (WINAPI *Props1SI)(
			char Refrigerant[20],
			char PropertyToReturn[20]);

	typedef double (WINAPI *PropsSI)(
			char PropertyToReturn[20],
			char InputProperty1[20], double InputValue1,
			char InputProperty2[20], double InputValue2,
			char Refrigerant[20]);

	// Addresses
	Props1SI Props1SIAddress;
	PropsSI PropsSIAddress;
	double result1, result2;

	// Load DLL; change this path as needed
	HINSTANCE CoolPropDll = LoadLibraryA("libCoolProp.dll");

	if (CoolPropDll) {
		// Addresses
		Props1SIAddress = (Props1SI) GetProcAddress(CoolPropDll, "Props1SI@8");
		PropsSIAddress = (PropsSI) GetProcAddress(CoolPropDll, "PropsSI@32");
		// Call function
		if (Props1SIAddress && PropsSIAddress) {
			double result1 = (*Props1SIAddress)("ParaHydrogen", "Tcrit");
			printf("ParaHydrogen Tcrit: %g\n", result1);

			double result2 = (*PropsSIAddress)("D", "T", 300, "P", 1e7, "ParaHydrogen");
			printf("ParaHydrogen density: %g\n", result2);
		} else {
			printf("Could not load functions.");
		}

		// Unload DLL
		FreeLibrary(CoolPropDll);
	} else {
		printf("Could not load CoolProp DLL.");
	}
}

