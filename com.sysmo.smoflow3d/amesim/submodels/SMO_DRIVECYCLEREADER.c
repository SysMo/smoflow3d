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
#include "SmoFlowAme.h"
#include "io_control/DriveCycleReader.h"

#define _component ps[0]
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
   _component = DriveCycleReader_new(fileName);
   SmoComponent_setInstanceIndex(_component, *n);

   DriveCycleReader_init(_component);
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
   DriveCycleReader_compute(_component, *t, *activationSignal, *breakCurrDrivingPhase);

   *phaseDuration = DriveCycleReader_getCurrentPhaseDuration(_component);
   *loopCounter = DriveCycleReader_getLoopCounter(_component);
   *isActive = DriveCycleReader_getIsActive(_component);

   *mDotExtraction = DriveCycleReader_getMDotExtraction(_component);
   *driveCycleState = DriveCycleReader_getDriveCycleState(_component);
   *phaseRemainingDuration = DriveCycleReader_getPhaseRemainingDuration(_component);
   *phaseIndexInDriveCycle = DriveCycleReader_getPhaseIndex(_component);
/* <<<<<<<<<<<<End of Calculation Executable Statements. */
}

