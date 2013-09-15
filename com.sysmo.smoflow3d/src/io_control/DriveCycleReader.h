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

	void init();
	void compute(double t, double activationSignal, double breakCurrDrivingPhase);

	bool getIsActive();
	int getLoopCounter();
	double getCurrentPhaseDuration();
	double getMDotExtraction();
	double getDriveCycleState();
	double getPhaseRemainingDuration();
	int getPhaseIndex();

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
void DriveCycleReader_init(DriveCycleReader* driveCycleReader);
void DriveCycleReader_compute(DriveCycleReader* driveCycleReader, double t, double activationSignal, double breakCurrDrivingPhase);
double DriveCycleReader_getIsActive(DriveCycleReader* driveCycleReader);
int DriveCycleReader_getLoopCounter(DriveCycleReader* driveCycleReader);
double DriveCycleReader_getCurrentPhaseDuration(DriveCycleReader* driveCycleReader);
double DriveCycleReader_getMDotExtraction(DriveCycleReader* driveCycleReader);
double DriveCycleReader_getDriveCycleState(DriveCycleReader* driveCycleReader);
double DriveCycleReader_getPhaseRemainingDuration(DriveCycleReader* driveCycleReader);
int DriveCycleReader_getPhaseIndex(DriveCycleReader* driveCycleReader);
END_C_LINKAGE

#endif /* DRIVECYCLEREADER_H_ */
