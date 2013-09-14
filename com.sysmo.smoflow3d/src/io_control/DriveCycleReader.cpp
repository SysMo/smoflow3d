/*
 * DriveCycleReader.cpp
 *
 *  Created on: Sep 7, 2013
 *      Author: Atanas Pavlov
 *	 Copyright: SysMo Ltd., Bulgaria
 */

#include "DriveCycleReader.h"

/**
 * DriveCycleReader - C++
 */
DriveCycleReader::DriveCycleReader(String fileName)
: fileName(fileName) {
	CSVProcessor csv;
	csv.addFloatColumn(phaseDuration);
	csv.addFloatColumn(extractionMassFlowRate);
	csv.addIntegerColumn(mode);
	csv.read(this->fileName, ',', 1);
	numDrivingPhases = phaseDuration.size();
	if (numDrivingPhases < 1) {
		RaiseComponentError(this, "No lines read from the drive cycle file");
	} else {
		ShowMessage("Drive cycle with " << numDrivingPhases << " driving phases read from drive cycle file " << this->fileName << "\n")
	}

	loopCounter = 0;
}

DriveCycleReader::~DriveCycleReader() {
}

void DriveCycleReader::init() {
	phaseIndex = 0;
	tReference = 0;
	tRemaining = 0;
	loopCounter = 1;
	isActive   = 0;
}

void DriveCycleReader::compute(double t, double activationSignal, double breakCurrDrivingPhase) {
	   if (SimEnv.isEventMode()) {//in a discontinuity
		   if (activationSignal >= 0.5) {
			   if (isActive) {
				   tRemaining -= t - tReference;
			   }
			   isActive = true;
		   } else {
			   if (isActive) {
				   tRemaining -= t - tReference;
			   }
			   isActive = false;
		   }

		   tReference = t;

		   if (tRemaining < 1e-3 || (mode[phaseIndex-1] != 0 && breakCurrDrivingPhase > 0.5)) {
			   if (phaseIndex < numDrivingPhases) {
				   phaseIndex++;
				   tRemaining = phaseDuration[phaseIndex-1];
			   } else if (phaseIndex == numDrivingPhases) {
				   loopCounter++;
				   phaseIndex = 0;
				   tRemaining = phaseDuration[phaseIndex];
				   phaseIndex++;
			   }
		   }
	   }

	   bool eventIndicator = false;
	   // Trigger discontinuity if the activation state of the drive cycle
	   // doesn't correspond to the activation input signal.
	   if (isActive != (activationSignal > 0.5)) {
		   eventIndicator = true;
	   }

	   // Trigger discontinuity if the phase has finished
	   if (isActive && (t - tReference >= tRemaining)) {
		   eventIndicator = true;
	   }

	   // Trigger discontinuity if a break of the current driving phase is requested
	   if (mode[phaseIndex-1] != 0 && breakCurrDrivingPhase > 0.5) {
		   eventIndicator = true;
	   }

	   if (isActive) {
		   mDotExtraction = extractionMassFlowRate[phaseIndex-1];
		   driveCycleState = mode[phaseIndex-1];
		   phaseRemainingDuration = tRemaining - (t - tReference);

		   currentPhaseDuration = phaseDuration[phaseIndex-1];
	   } else {
		   mDotExtraction = 0;
		   driveCycleState = -1;
		   phaseRemainingDuration = tRemaining;
	   }

	   SimEnv.updateEventIndicator(eventIndicator); //trigger discontinuity
}

bool DriveCycleReader::getIsActive() {
	return isActive;
}

int DriveCycleReader::getLoopCounter() {
	return loopCounter;
}

double DriveCycleReader::getCurrentPhaseDuration() {
	return currentPhaseDuration;
}

double DriveCycleReader::getMDotExtraction() {
	return mDotExtraction;
}

double DriveCycleReader::getDriveCycleState() {
	return driveCycleState;
}

double DriveCycleReader::getPhaseRemainingDuration() {
	return phaseRemainingDuration;
}

int DriveCycleReader::getPhaseIndex() {
	return phaseIndex;
}

/**
 * DriveCycleReader - C
 */
DriveCycleReader* DriveCycleReader_new(const char* fileName) {
	return new DriveCycleReader(fileName);
}

void DriveCycleReader_init(DriveCycleReader* driveCycleReader) {
	driveCycleReader->init();
}

void DriveCycleReader_compute(DriveCycleReader* driveCycleReader, double t, double activationSignal, double breakCurrDrivingPhase) {
	driveCycleReader->compute(t, activationSignal, breakCurrDrivingPhase);
}

double DriveCycleReader_getIsActive(DriveCycleReader* driveCycleReader) {
	return (double) driveCycleReader->getIsActive();
}

int DriveCycleReader_getLoopCounter(DriveCycleReader* driveCycleReader) {
	return driveCycleReader->getLoopCounter();
}

double DriveCycleReader_getCurrentPhaseDuration(DriveCycleReader* driveCycleReader) {
	return driveCycleReader->getCurrentPhaseDuration();
}

double DriveCycleReader_getMDotExtraction(DriveCycleReader* driveCycleReader) {
	return driveCycleReader->getMDotExtraction();
}

double DriveCycleReader_getDriveCycleState(DriveCycleReader* driveCycleReader) {
	return driveCycleReader->getDriveCycleState();
}

double DriveCycleReader_getPhaseRemainingDuration(DriveCycleReader* driveCycleReader) {
	return driveCycleReader->getPhaseRemainingDuration();
}

int DriveCycleReader_getPhaseIndex(DriveCycleReader* driveCycleReader) {
	return driveCycleReader->getPhaseIndex();
}
