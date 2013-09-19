/* Submodel SMO_STATEMACHINECONTROLLER skeleton created by AME Submodel editing utility
   Mon Jul 29 15:08:35 2013 */



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
#include "controller/StateMachineController.h"

#define _component ps[0]
/* <<<<<<<<<<<<End of Private Code. */


/* There is 1 real parameter:

   realParameters[] real parameters [null]
*/


/* There are 6 integer parameters:

   numInputs              number of inputs               
   numOutputs             number of outputs              
   numRealParameters      number of real parameters      
   numIntegerParameters   number of integer parameters   
   initialState           initial state of the controller
   integerParameters[]    integer parameters             
*/


/* There are 2 text parameters:

   controllerName    controller name         
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
   int realParameters_size;
   int integerParameters_size;
   int param_offset;  /* Offset used to assign parameter values. */
   int numInputs, numOutputs, numRealParameters, numIntegerParameters
      , initialState, *integerParameters;
   double *realParameters;
   char *controllerName, *controllerLibrary;

   param_offset = 0;
   numInputs  = ip[0];
   numOutputs = ip[1];
   numRealParameters = ip[2];
   numIntegerParameters = ip[3];
   initialState = ip[4];
   integerParameters = &(ip[5]);
   integerParameters_size = numIntegerParameters;
   param_offset += integerParameters_size-1;

   param_offset = 0;
   realParameters = &(rp[0]);
   realParameters_size = numRealParameters;
   param_offset += realParameters_size-1;

   param_offset = 0;
   controllerName = tp[0];
   controllerLibrary = tp[1];
   param_offset = 0;
   inputs_size = numInputs;
   outputs_size = numOutputs;
   loop = 0;
   error = 0;

/*
   If necessary, check values of the following:

   rp[0..0]
*/

/*
   Check and/or reset the following fixed and/or discrete variables

   outputs   [] = ??;
   *controllerState = ??;
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
   if (initialState < 0 || initialState > 1000)
   {
      amefprintf(stderr, "\ninitial state of the controller must be in range [0..1000].\n");
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
   AME_SET_CURRENT_COMPONENT;
   _component = StateMachineController_new(
		   controllerName,
		   controllerLibrary,
		   numRealParameters,
		   numIntegerParameters,
		   numInputs,
		   numOutputs);

   StateMachineController* controller = (StateMachineController*)_component;
   controller->setParameters(controller, realParameters, integerParameters);
   controller->time = 0;
   controller->init(controller, initialState);
   *controllerState = initialState;
   controller->getOutputs(controller, outputs);
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
   int realParameters_size;
   int integerParameters_size;
   int param_offset;  /* Offset used to assign parameter values. */
   int numInputs, numOutputs, numRealParameters, numIntegerParameters
      , initialState, *integerParameters;
   double *realParameters;
   char *controllerName, *controllerLibrary;

   param_offset = 0;
   numInputs  = ip[0];
   numOutputs = ip[1];
   numRealParameters = ip[2];
   numIntegerParameters = ip[3];
   initialState = ip[4];
   integerParameters = &(ip[5]);
   integerParameters_size = numIntegerParameters;
   param_offset += integerParameters_size-1;

   param_offset = 0;
   realParameters = &(rp[0]);
   realParameters_size = numRealParameters;
   param_offset += realParameters_size-1;

   param_offset = 0;
   controllerName = tp[0];
   controllerLibrary = tp[1];
   param_offset = 0;
   inputs_size = numInputs;
   outputs_size = numOutputs;
   loop = 0;
   error = 0;


/* >>>>>>>>>>>>Terminate Function Executable Statements. */
   StateMachineController* controller = (StateMachineController*)_component;
   StateMachineController_free(&controller);
/* <<<<<<<<<<<<End of Terminate Executable Statements. */
}



/*  There are 3 ports.

   Port 1 has 1 variable:

      1 inputs[]   input variables [null] basic variable input

   Port 2 has 1 variable:

      1 outputs[]   outputs [null] discrete

   Port 3 has 1 variable:

      1 controllerState     controller state [null] discrete
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
   int realParameters_size;
   int integerParameters_size;
   int param_offset;  /* Offset used to assign parameter values. */
   int numInputs, numOutputs, numRealParameters, numIntegerParameters
      , initialState, *integerParameters;
   double *realParameters;
   char *controllerName, *controllerLibrary;

   param_offset = 0;
   numInputs  = ip[0];
   numOutputs = ip[1];
   numRealParameters = ip[2];
   numIntegerParameters = ip[3];
   initialState = ip[4];
   integerParameters = &(ip[5]);
   integerParameters_size = numIntegerParameters;
   param_offset += integerParameters_size-1;

   param_offset = 0;
   realParameters = &(rp[0]);
   realParameters_size = numRealParameters;
   param_offset += realParameters_size-1;

   param_offset = 0;
   controllerName = tp[0];
   controllerLibrary = tp[1];
   param_offset = 0;
   inputs_size = numInputs;
   outputs_size = numOutputs;
   logi = 0;
   loop = 0;

/*
   Set all submodel outputs below:

*/


/*
   The following discrete variable(s) can be reset when the discontinuity flag is zero:

   outputs   [] = ??;
   *controllerState = ??;
*/



/* >>>>>>>>>>>>Calculation Function Executable Statements. */
   StateMachineController* controller = (StateMachineController*)_component;

   controller->time = *t;
   controller->setInputs(controller, inputs);

   // Checking for discontinuity
   int newState = controller->checkForTransition(controller);
   if (newState != -1) {
	   logi = 1;
   }
   disloc_(&logi);

   // Already found the discontinuity and switching the controller state
   if (*flag == 0 && newState != -1) {
	   controller->switchState(controller);
	   controller->getOutputs(controller, outputs);
	   *controllerState = newState;
   }
/* <<<<<<<<<<<<End of Calculation Executable Statements. */
}

