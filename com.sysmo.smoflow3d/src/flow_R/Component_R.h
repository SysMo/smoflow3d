/*
 * Component_R.h
 *
 *  Created on: Jul 31, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#ifndef COMPONENT_R_H_
#define COMPONENT_R_H_

#include "util/CommonDefinitions.h"

#ifdef __cplusplus

class Component_R : public SmoComponent {
public:
	Component_R();
	virtual ~Component_R() {}

	virtual bool isFlowClosed(double massFlowRate);
	void closeFlow() {flagIsFlowOpen = false;}
	void openFlow() {flagIsFlowOpen = true;}

	bool isBidirectionalFlowAllowed() {return flagIsBidirectionalFlowAllowed;}
	void setIsBidirectionalFlowAllowed(bool isBidirectionalFlowAllowed) {this->flagIsBidirectionalFlowAllowed = isBidirectionalFlowAllowed;}

private:
	bool flagIsFlowOpen;
	bool flagIsBidirectionalFlowAllowed;
};

#else //_cplusplus
DECLARE_C_STRUCT(Component_R)
#endif //_cplusplus

BEGIN_C_LINKAGE

Component_R* Component_R_get(int componentIndex);
int Component_R_register(Component_R* component);

END_C_LINKAGE

#endif /* COMPONENT_R_H_ */
