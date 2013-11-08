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
#include "media/MediumState.h"
#include "flow/FlowBase.h"

#ifdef __cplusplus

class VirtualCapacity_R;

class Component_R : public SmoComponent {
public:
	Component_R();
	virtual ~Component_R();

	virtual void init(MediumState* state1, MediumState* state2);
	virtual bool compute(double massFlowRate, double minDownstreamPressure) = 0;
	void updateFlows(double massFlow);

	int getFlow1Index() {return flow1Index;}
	int getFlow2Index() {return flow2Index;}

	MediumState* getUpstreamState(double massFlowRate);
	MediumState* getDownstreamState(double massFlowRate);

	void addVirtualCapacity(VirtualCapacity_R* virtualCapacity);
	VirtualCapacity_R* getOtherVirtualCapacity(VirtualCapacity_R* virtualCapacity);

	int getPort1StateIndex() {return port1StateIndex;}
	int getPort2StateIndex() {return port2StateIndex;}
	void setPort1StateIndex(int port1StateIndex) {this->port1StateIndex = port1StateIndex;}
	void setPort2StateIndex(int port2StateIndex) {this->port2StateIndex = port2StateIndex;}

	bool isFlowClosed(double massFlowRate);
	void closeFlow() {flagIsFlowOpen = false;}
	void openFlow() {flagIsFlowOpen = true;}

	bool isBidirectionalFlowAllowed() {return flagIsBidirectionalFlowAllowed;}
	void setIsBidirectionalFlowAllowed(bool isBidirectionalFlowAllowed) {this->flagIsBidirectionalFlowAllowed = isBidirectionalFlowAllowed;}

	bool isComputed() {return flagIsComputed;}
	void setIsComputed(bool isComputed) {this->flagIsComputed = isComputed;}

	bool isReversed() {return flagIsReversed;}
	void setIsReversed(bool isReversed) {flagIsReversed = isReversed;}

protected:
	void correctMassFlowRate(double& massFlowRate);

	MediumState* _getUpstreamState(double massFlowRate);
	MediumState* _getDownstreamState(double massFlowRate);

private:
	int flow1Index;
	int flow2Index;

	FluidFlow* flow1;
	FluidFlow* flow2;

	MediumState* state1;
	MediumState* state2;

	VirtualCapacity_R* virtualCapacity1;
	VirtualCapacity_R* virtualCapacity2;

	int port1StateIndex;
	int port2StateIndex;

	bool flagIsFlowOpen;
	bool flagIsBidirectionalFlowAllowed;
	bool flagIsReversed; //:TRICKY: the flag is true when the component ports are reversed in the R-components chain
						 //(e.g. [mainComponent1.port]->...->[port2.Component_R.port1]->...->[port.mainComponent2])

	bool flagIsComputed;
};

#else //_cplusplus
DECLARE_C_STRUCT(Component_R)
#endif //_cplusplus

BEGIN_C_LINKAGE
int Component_R_getFlow1Index(Component_R* component);
int Component_R_getFlow2Index(Component_R* component);
END_C_LINKAGE

#endif /* COMPONENT_R_H_ */
