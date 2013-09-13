/*
 * DriveCycleReader.h
 *
 *  Created on: Sep 7, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#ifndef DRIVECYCLEREADER_H_
#define DRIVECYCLEREADER_H_

#include "CSVProcessor.h"

#ifdef __cplusplus

class DriveCycleReader : SmoComponent {
public:
	DriveCycleReader(String fileName);
	virtual ~DriveCycleReader();
	virtual const char* getComponentName() {
		return "SMO_DRIVECYCLEREADER";
	}
	void init();
	void compute(double t, double activationSignal,
			double breakCurrDrivingPhase);
protected:
	String fileName;
	VectorFloat phaseDuration;
	VectorFloat extractionMassFlowRate;
	VectorInt mode;
	bool isActive;
	double tRemaining;
	double tReference;
	int phaseIndex;
	int numDrivingPhases;
	int loopCounter;

	double mDotExtraction;
	double driveCycleState;
	double phaseRemainingDuration;
	double currentPhaseDuration;

};


#else //__cplusplus
DECLARE_C_STRUCT(DriveCycleReader)
#endif //__cplusplus

BEGIN_C_LINKAGE
DriveCycleReader* DriveCycleReader_new(const char* fileName);
END_C_LINKAGE

#endif /* DRIVECYCLEREADER_H_ */
