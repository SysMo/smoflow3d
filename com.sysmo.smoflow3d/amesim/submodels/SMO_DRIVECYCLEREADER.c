/* Submodel SMO_DRIVECYCLEREADER skeleton created by AME Submodel editing utility
   Mon Jul 29 13:16:58 2013 */



#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "ameutils.h"
/* *******************************************************************************
TITLE :
 
------------------------------------------------------------------------------
DESCRIPTION :
 
------------------------------------------------------------------------------
USAGE :
 
------------------------------------------------------------------------------
PARAMETER SETTINGS :
 
------------------------------------------------------------------------------
REVISIONS :
 
******************************************************************************* */

#define _SUBMODELNAME_ "SMO_DRIVECYCLEREADER"

/* >>>>>>>>>>>>Insert Private Code Here. */
#include "util/Table.h"

#define phaseIndex ic[0]
#define tReference c[0]
#define tRemaining c[1]

#define DRIVE_CYCLE_TABLE ps[0]

#define getPhaseDuration(phaseIndex) \
	Table_getValue(dataTable, phaseIndex, 0)

#define getExtractionMassFlowRate(phaseIndex) \
	Table_getValue(dataTable, phaseIndex, 1)

#define getDrivingMode(phaseIndex) \
	Table_getValue(dataTable, phaseIndex, 2)
/* <<<<<<<<<<<<End of Private Code. */

/* There is 1 text parameter:

   fileName file name
*/

void smo_drivecyclereaderin_(int *n, char *tp[1], double c[2]
      , int ic[1], void *ps[1], double *phaseDuration
      , double *loopCounter, double *isActive)

{
   int loop, error;
/* >>>>>>>>>>>>Extra Initialization Function Declarations Here. */
   Table* dataTable = NULL;
/* <<<<<<<<<<<<End of Extra Initialization declarations. */
   char *fileName;

   fileName   = tp[0];
   loop = 0;
   error = 0;

/*
   Check and/or reset the following fixed and/or discrete variables

   *phaseDuration = ??;
   *loopCounter = ??;
   *isActive   = ??;
*/


/* >>>>>>>>>>>>Initialization Function Check Statements. */
/* <<<<<<<<<<<<End of Initialization Check Statements. */

   if(error == 1)
   {
      amefprintf(stderr, "\nWarning in %s instance %d.\n", _SUBMODELNAME_, *n);
   }
   else if(error == 2)
   {
      amefprintf(stderr, "\nFatal error in %s instance %d.\n", _SUBMODELNAME_, *n);
      amefprintf(stderr, "Terminating the program.\n");
      AmeExit(1);
   }


/* >>>>>>>>>>>>Initialization Function Executable Statements. */
   AME_SET_CURRENT_COMPONENT;

   // Read drive cycle data from the input csv file
   String* driveCycleFileName = String_new(fileName);
   Table_readCSV(driveCycleFileName, &dataTable);
   String_free(&driveCycleFileName);


   // Check the reading data
   if (dataTable->rowNumber < 1) {
	   raiseError(getDummyBase(), "The drive cycle file is empty.");
   }
   if (dataTable->columnNumber < 3) {
	   raiseError(getDummyBase(), "The drive cycle file has wrong data (less than 3 columns).");
   }


   // Set some variables
   phaseIndex = 0;
   tReference = 0;
   tRemaining = 0;
   DRIVE_CYCLE_TABLE = dataTable;

   *phaseDuration = getPhaseDuration(phaseIndex);
   *loopCounter = 1;
   *isActive   = 0;
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

/*  There are 7 ports.

   Port 1 has 1 variable:

      1 activationSignal     activation signal [null] basic variable input

   Port 2 has 1 variable:

      1 breakCurrDrivingPhase     break the current driving phase (0-don't break; 1-break) [null] basic variable input

   Port 3 has 1 variable:

      1 phaseDuration     phase duration [s] discrete

   Port 4 has 1 variable:

      1 mDotExtraction     extraction mass flow rate [null] basic variable output

   Port 5 has 1 variable:

      1 driveCycleState     state (1-driving; 0-parking; -1-unactive) [null] basic variable output

   Port 6 has 1 variable:

      1 phaseRemainingDuration     phase remaining duration [s] basic variable output

   Port 7 has 1 variable:

      1 loopCounter     loop counter [null] discrete
*/

/*  There are 2 internal variables.

      1 isActive                   activation state (0-unactive; 1-active) [null] discrete
      2 phaseIndexInDriveCycle     phase index                             [null] basic variable
*/

void smo_drivecyclereader_(int *n, double *activationSignal
      , double *breakCurrDrivingPhase, double *phaseDuration
      , double *mDotExtraction, double *driveCycleState
      , double *phaseRemainingDuration, double *loopCounter
      , double *isActive, double *phaseIndexInDriveCycle, char *tp[1]
      , double c[2], int ic[1], void *ps[1], int *flag, double *t)

{
   int loop, logi;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
   Table* dataTable = (Table*)DRIVE_CYCLE_TABLE;
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   char *fileName;

   fileName   = tp[0];
   logi = 0;
   loop = 0;

/*
   Set all submodel outputs below:

   *mDotExtraction = ??;
   *driveCycleState = ??;
   *phaseRemainingDuration = ??;
   *phaseIndexInDriveCycle = ??;
*/


/*
   The following discrete variable(s) can be reset when the discontinuity flag is zero:

   *phaseDuration = ??;
   *loopCounter = ??;
   *isActive   = ??;
*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
   logi = 0; //flag for calling discontinuity (0-no call; 1-call)

   if (*flag == 0) {//in a discontinuity
	   if (*activationSignal >= 0.5) {
		   if (*isActive == 1) {
			   tRemaining -= *t - tReference;
		   }
		   *isActive = 1;
	   } else {
		   if (*isActive == 1) {
			   tRemaining -= *t - tReference;
		   }
		   *isActive = 0;
	   }

	   tReference = *t;

	   if (tRemaining < 1 || (getDrivingMode(phaseIndex-1) != 0 && *breakCurrDrivingPhase > 0.5)) {
		   if (phaseIndex < dataTable->rowNumber) {
			   phaseIndex++;
			   tRemaining = getPhaseDuration(phaseIndex-1);
		   } else if (phaseIndex == dataTable->rowNumber) {
			   (*loopCounter)++;
			   phaseIndex = 0;
			   tRemaining = getPhaseDuration(phaseIndex);
			   phaseIndex++;
		   }
	   }
   }

   // Trigger discontinuity if the activation state of the drive cycle
   // doesn't correspond to the activation input signal.
   if ((*isActive > 0.5) != (*activationSignal > 0.5)) {
	   logi = 1;
   }

   // Trigger discontinuity if the phase has finished
   if ((*isActive > 0.5) && (*t - tReference >= tRemaining)) {
	   logi = 1;
   }

   // Trigger discontinuity if a break of the current driving phase is requested
   if (getDrivingMode(phaseIndex-1) != 0 && *breakCurrDrivingPhase > 0.5) {
	   logi = 1;
   }

   // Set the output variables
   *phaseIndexInDriveCycle = (double) phaseIndex;

   if (*isActive > 0.5) {
	   *mDotExtraction = getExtractionMassFlowRate(phaseIndex-1);
	   *driveCycleState = getDrivingMode(phaseIndex-1);
	   *phaseRemainingDuration = tRemaining - (*t - tReference);

	   *phaseDuration = getPhaseDuration(phaseIndex-1);
   } else {
	   *mDotExtraction = 0;
	   *driveCycleState = -1;
	   *phaseRemainingDuration = tRemaining;
   }

   if (logi == 1) {
	   disloc_(&logi); //trigger discontinuity
   }
/* <<<<<<<<<<<<End of Calculation Executable Statements. */
}

