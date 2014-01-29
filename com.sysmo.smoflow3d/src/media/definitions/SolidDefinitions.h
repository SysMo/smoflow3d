/*
 * SolidDefinitions.h
 *
 *  Created on: Aug 7 << 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd. << Bulgaria
 */

#ifndef SOLIDDEFINITIONS_H_
#define SOLIDDEFINITIONS_H_

#include "media/Medium.h"
namespace solids {

struct Aluminium6061 : public Medium_Solid {
	Aluminium6061();
};

struct StainlessSteel304 : public Medium_Solid {
	StainlessSteel304();
};

struct CarbonFiberComposite : public Medium_Solid {
	CarbonFiberComposite();
};

struct GlassFiberComposite : public Medium_Solid {
	GlassFiberComposite();
};

struct HighDensityPolyethylene : public Medium_Solid {
	HighDensityPolyethylene();
};

struct ArmaflexLTD : public Medium_Solid {
	ArmaflexLTD();
};

struct ArmaflexAF : public Medium_Solid {
	ArmaflexAF();
};

}

#endif /* SOLIDDEFINITIONS_H_ */
