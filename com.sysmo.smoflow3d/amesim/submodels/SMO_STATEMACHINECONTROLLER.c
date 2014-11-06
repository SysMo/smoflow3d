/* Submodel SMO_STATEMACHINECONTROLLER skeleton created by AME Submodel editing utility
   Sat Nov 30 15:17:51 2013 */



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

#define _SUBMODELNAME_ "SMO_STATEMACHINECONTROLLER"

/* >>>>>>>>>>>>Insert Private Code Here. */
#include "SmoFlowAme.h"
#include "io_control/StateMachineController.h"

#define _component ps[0]
/* <<<<<<<<<<<<End of Private Code. */


/* There is 1 real parameter:

   realParameters[] real parameters [null]
*/


/* There are 6 integer parameters:

   numInputs                number of inputs               
   numOutputs               number of outputs              
   numRealParameters        number of real parameters      
   numIntegerParameters     number of integer parameters   
   maxNumOrthogonalStates   max number of orthogonal states
   integerParameters[]      integer parameters             
*/


/* There is 1 text parameter:

   controllerLibrary controller library (dll)
*/

void smo_statemachinecontrollerin_(int *n, double *rp, int *ip
      , char **tp, void *ps[1], double *outputs
      , double *controllerState)

{
   int loop, error;
/* >>>>>>>>>>>>Extra Initialization Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Initialization declarations. */
   int inputs_size;
   int outputs_size;
   int controllerState_size;
   int realParameters_size;
   int integerParameters_size;
   int param_offset;  /* Offset used to assign parameter values. */
   int numInputs, numOutputs, numRealParameters, numIntegerParameters
      , maxNumOrthogonalStates, *integerParameters;
   double *realParameters;
   char *controllerLibrary;

   param_offset = 0;
   numInputs  = ip[0];
   numOutputs = ip[1];
   numRealParameters = ip[2];
   numIntegerParameters = ip[3];
   maxNumOrthogonalStates = ip[4];
   integerParameters = &(ip[5]);
   integerParameters_size = numIntegerParameters;
   param_offset += integerParameters_size-1;

   param_offset = 0;
   realParameters = &(rp[0]);
   realParameters_size = numRealParameters;
   param_offset += realParameters_size-1;

   param_offset = 0;
   controllerLibrary = tp[0];
   param_offset = 0;
   inputs_size = numInputs;
   outputs_size = numOutputs;
   controllerState_size = maxNumOrthogonalStates;
   loop = 0;
   error = 0;

/*
   If necessary, check values of the following:

   rp[0..0]
*/

/*
   Check and/or reset the following fixed and/or discrete variables

   outputs   [] = ??;
   controllerState[] = ??;
*/


/* >>>>>>>>>>>>Initialization Function Check Statements. */
/* <<<<<<<<<<<<End of Initialization Check Statements. */

/*   Integer parameter checking:   */

   if (numInputs < 0 || numInputs > 100)
   {
      amefprintf(stderr, "\nnumber of inputs must be in range [0..100].\n");
      error = 2;
   }
   if (numOutputs < 0 || numOutputs > 100)
   {
      amefprintf(stderr, "\nnumber of outputs must be in range [0..100].\n");
      error = 2;
   }
   if (numRealParameters < 0 || numRealParameters > 100)
   {
      amefprintf(stderr, "\nnumber of real parameters must be in range [0..100].\n");
      error = 2;
   }
   if (numIntegerParameters < 0 || numIntegerParameters > 100)
   {
      amefprintf(stderr, "\nnumber of integer parameters must be in range [0..100].\n");
      error = 2;
   }
   if (maxNumOrthogonalStates < 0 || maxNumOrthogonalStates > 100000)
   {
      amefprintf(stderr, "\nmax number of orthogonal states must be in range [0..100000].\n");
      error = 2;
   }
   for (loop=0; loop < integerParameters_size; loop++)
   {
      if (integerParameters[loop] < -100000 || integerParameters[loop] > 100000)
      {
         amefprintf(stderr, "\ninteger parameters %d must be in range [-100000..100000].\n", loop+1);
         error = 2;
      }
   }

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
   param_offset += realParameters_size-1;


/* >>>>>>>>>>>>Initialization Function Executable Statements. */
   _component = StateMachineController_new();
   SMOCOMPONENT_SET_PROPS(_component)

   StateMachineController_loadController(_component, controllerLibrary);
   StateMachineController_init(_component);
   StateMachineController_checkSizes(_component,
		   numRealParameters, numIntegerParameters,
		   numInputs, numOutputs, maxNumOrthogonalStates);
   StateMachineController_setParameters(_component, realParameters, integerParameters);
   StateMachineController_setTime(_component, 0);
   StateMachineController_enter(_component);
/* <<<<<<<<<<<<End of Initialization Executable Statements. */
}

void smo_statemachinecontrollerend_(int *n, double *rp, int *ip
      , char **tp, void *ps[1], double *outputs
      , double *controllerState)

{
   int loop, error;
/* >>>>>>>>>>>>Extra Terminate Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Terminate declarations. */
   int inputs_size;
   int outputs_size;
   int controllerState_size;
   int realParameters_size;
   int integerParameters_size;
   int param_offset;  /* Offset used to assign parameter values. */
   int numInputs, numOutputs, numRealParameters, numIntegerParameters
      , maxNumOrthogonalStates, *integerParameters;
   double *realParameters;
   char *controllerLibrary;

   param_offset = 0;
   numInputs  = ip[0];
   numOutputs = ip[1];
   numRealParameters = ip[2];
   numIntegerParameters = ip[3];
   maxNumOrthogonalStates = ip[4];
   integerParameters = &(ip[5]);
   integerParameters_size = numIntegerParameters;
   param_offset += integerParameters_size-1;

   param_offset = 0;
   realParameters = &(rp[0]);
   realParameters_size = numRealParameters;
   param_offset += realParameters_size-1;

   param_offset = 0;
   controllerLibrary = tp[0];
   param_offset = 0;
   inputs_size = numInputs;
   outputs_size = numOutputs;
   controllerState_size = maxNumOrthogonalStates;
   loop = 0;
   error = 0;


/* >>>>>>>>>>>>Terminate Function Executable Statements. */
/* <<<<<<<<<<<<End of Terminate Executable Statements. */
}



/*  There are 3 ports.

   Port 1 has 1 variable:

      1 inputs[]   input variables [null] basic variable input

   Port 2 has 1 variable:

      1 outputs[]   outputs [null] discrete

   Port 3 has 1 variable:

      1 controllerState[]   controller state [null] discrete
*/

/*  There are 0 internal variables.

*/

void smo_statemachinecontroller_(int *n, double *inputs
      , double *outputs, double *controllerState, double *rp, int *ip
      , char **tp, void *ps[1], int *flag, double *t)

{
   int loop, logi;
/* >>>>>>>>>>>>Extra Calculation Function Declarations Here. */
/* <<<<<<<<<<<<End of Extra Calculation declarations. */
   int inputs_size;
   int outputs_size;
   int controllerState_size;
   int realParameters_size;
   int integerParameters_size;
   int param_offset;  /* Offset used to assign parameter values. */
   int numInputs, numOutputs, numRealParameters, numIntegerParameters
      , maxNumOrthogonalStates, *integerParameters;
   double *realParameters;
   char *controllerLibrary;

   param_offset = 0;
   numInputs  = ip[0];
   numOutputs = ip[1];
   numRealParameters = ip[2];
   numIntegerParameters = ip[3];
   maxNumOrthogonalStates = ip[4];
   integerParameters = &(ip[5]);
   integerParameters_size = numIntegerParameters;
   param_offset += integerParameters_size-1;

   param_offset = 0;
   realParameters = &(rp[0]);
   realParameters_size = numRealParameters;
   param_offset += realParameters_size-1;

   param_offset = 0;
   controllerLibrary = tp[0];
   param_offset = 0;
   inputs_size = numInputs;
   outputs_size = numOutputs;
   controllerState_size = maxNumOrthogonalStates;
   logi = 0;
   loop = 0;

/*
   Set all submodel outputs below:

*/


/*
   The following discrete variable(s) can be reset when the discontinuity flag is zero:

   outputs   [] = ??;
   controllerState[] = ??;
*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
   SMOCOMPONENT_PRINT_MAIN_CALC
   StateMachineController_setInputs(_component, inputs);
   StateMachineController_setTime(_component, *t);
   StateMachineController_step(_component);
   if (*flag == 0) {
	   StateMachineController_getOutputs(_component, outputs);
	   StateMachineController_getState_ToDouble(_component, controllerState);
   }
/* <<<<<<<<<<<<End of Calculation Executable Statements. */
}

