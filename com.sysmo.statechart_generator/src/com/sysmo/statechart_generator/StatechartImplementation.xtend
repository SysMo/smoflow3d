package com.sysmo.statechart_generator

import com.google.inject.Inject
import java.util.List
import org.yakindu.sct.model.sexec.Check
import org.yakindu.sct.model.sexec.EnterState
import org.yakindu.sct.model.sexec.Execution
import org.yakindu.sct.model.sexec.ExecutionFlow
import org.yakindu.sct.model.sexec.ExecutionState
import org.yakindu.sct.model.sexec.ExitState
import org.yakindu.sct.model.sexec.If
import org.yakindu.sct.model.sexec.Sequence
import org.yakindu.sct.model.sexec.StateSwitch
import org.yakindu.sct.model.sexec.Step
import org.yakindu.sct.model.sexec.extensions.SExecExtensions
import org.yakindu.sct.model.sexec.naming.INamingService
import org.yakindu.sct.model.stext.stext.VariableDefinition
import org.yakindu.sct.model.sexec.Call

class StatechartImplementation {
	@Inject extension Util
	@Inject extension SExecExtensions
	@Inject extension INamingService
	@Inject extension Naming
	@Inject extension ExpressionCode
	
	protected boolean eventMode = false;
	protected boolean actionFound = false;
	
	
	new() {
		this.eventMode = true
	}
	
	def generateImplementation(ExecutionFlow it) {'''
		#include "«name».h"

		SimEnv_MessageFunc _message;
		SimEnv_ErrorFunc _error;
		
		const char* stateNames[«states.size»] = {
			«FOR ExecutionState state : states SEPARATOR ','»
				"«state.shortName»"
			«ENDFOR»
		};

		const char* parameterNames[«getScope("parameters").variables.size»] = {
			«FOR v : getScope("parameters").variables SEPARATOR ','»
				"«v.name»"
			«ENDFOR»
		};
		
		const char* inputNames[«getScope("inputs").variables.size»] = {
			«FOR v : getScope("inputs").variables SEPARATOR ','»
				"«v.name»"
			«ENDFOR»
		};
		
		const char* outputNames[«getScope("outputs").variables.size»] = {
			«FOR v : getScope("outputs").variables SEPARATOR ','»
				"«v.name»"
			«ENDFOR»
		};

		«name»::«name»(SimEnv_MessageFunc messageFunc, SimEnv_ErrorFunc errorFunc) {
			_message = messageFunc;
			_error = errorFunc;
			_message("Controller state list:\n");	
			for (int i = 0; i < «states.size»; i++) {
				_message(stateNames[i]);
				_message("\n");
			}
		}
		
		«name»::~«name»() {
			
		}
		
		void «name»::init() {
			for (int i = 0; i < «orthogonalStatesConst»; ++i)
				stateConfVector[i] = «last_state»;
			
			stateConfVectorPosition = 0;
		
			«initSequence.code»
		}
		
		void «name»::setParameters(
				double realParameterValues[],
				int integerParameterValues[]) {			
			«setValuesFromArray(realParameters,
			"parameters", "realParameterValues")»

			«setValuesFromArray(integerParameters,
			"parameters", "integerParameterValues")»
		}

		void «name»::setInputs(double inputValues[]) {
			«setValuesFromArray(inputs, "inputs", "inputValues")»
		}

		void «name»::setTime(double t) {
			this->t = t;	
		}
		
		void «name»::getOutputs(double outputValues[]) {
			«getValuesToArray(outputs, "outputs", "outputValues")»
		}

		void «name»::getState(int stateVector[]) {
			for (int i = 0; i < maxOrthogonalStates; i++) {
				stateVector[i] = stateConfVector[i];	
			}
		}
		«enterFunction»
		
		/* Function which checks if any discrete event is about to occur */
		bool «name»::isActionRequested() {
			bool actionRequested = false;
			for (stateConfVectorPosition = 0; 
					stateConfVectorPosition < maxOrthogonalStates; 
					stateConfVectorPosition++) { 
				switch (stateConfVector[stateConfVectorPosition]) {
				«reactFunctions.checkTransitionCases»
				default:
					break;
				}
				if (actionRequested) {
					break;
				}
			}
			return actionRequested;
		}

		/* Function called at discrete event (after integrator restart) */
		void «name»::react() {
			for (stateConfVectorPosition = 0;
					stateConfVectorPosition < «orthogonalStatesConst»;
					stateConfVectorPosition++) {
					
				switch (stateConfVector[stateConfVectorPosition]) {
				«FOR state : states»
					«IF state.reactSequence!=null»
					case «state.shortName.asEscapedIdentifier»: {
						«state.reactSequence.shortName»();
						break;
					}
					«ENDIF»
				«ENDFOR»
				default:
					break;
				}
			}
		}

		«reactFunctions.toImplementation»
		
		/* C interface functions */		
		«name»* createController(SimEnv_MessageFunc messageFunc, SimEnv_ErrorFunc errorFunc) {
			return new «module»(messageFunc, errorFunc);
		}
		
		void getSizes(«module»* controller, 
			int* numRealParameters, int* numIntegerParameters,
			int* numInputs, int* numOutputs, int* maxNumOrthogonalStates) {
				controller->getSizes(*numRealParameters, *numIntegerParameters,
						*numInputs, *numOutputs, *maxNumOrthogonalStates);
		}
		
		void init(«module»* controller) {
			controller->init();
		}
		
		void setParameters(«module»* controller,
				double realParameterValues[],
				int integerParameterValues[]) {
			controller->setParameters(realParameterValues, integerParameterValues);
		}
		
		void setInputs(«module»* controller, double inputValues[]) {
			controller->setInputs(inputValues);
		}
		
		void setTime(«module»* controller, double t) {
			controller->setTime(t);
		}
		
		void getOutputs(«module»* controller, double outputValues[]) {
			controller->getOutputs(outputValues);
		}
		
		void getState(«module»* controller, int stateVector[]) {
			controller->getState(stateVector);	
		}
		
		void enter(«module»* controller) {
			controller->enter();			
		}
		
		int isActionRequested(«module»* controller) {
			if (controller->isActionRequested()) {
				return 1;
			} else {
				return 0;
			}
		}
		
		void react(«module»* controller) {
			controller->react();
		}
		
	'''.toString}
	
	def enterFunction(ExecutionFlow it) {
		this.eventMode = true		
		'''
		void «name»::enter() {
			«enterSequences.defaultSequence.code»
		}
		
	'''}
		
	def toImplementation(List<Step> steps) { 
		this.eventMode = true
	'''
		«FOR s : steps»
			«s.functionImplementation»
		«ENDFOR»
	'''
	}

	def checkTransitionCases(List<Step> steps) {
		this.eventMode = false
	'''
		«FOR s : steps»
			«s.functionImplementation»
		«ENDFOR»
	'''
	}
	
	def functionImplementation(Step it) {
	 	if (this.eventMode) {'''
			void «execution_flow.module»::«shortName»() {
				«code»
			}
		'''} else {
			this.actionFound = false
			'''
			case «it.shortName.substring(6)»:
				«code»
				break;
		'''}
	}
	
	def dispatch CharSequence code(Step it) '''
		«stepComment»
		//«it»
		#error ActionCode for Step '«getClass().name»' not defined
	'''

	def dispatch CharSequence code(Sequence it) '''
		«IF (this.eventMode)»«stepComment»«ENDIF»
		«FOR s : steps»
			«IF (!this.eventMode && this.actionFound)»«ELSE»«s.code»«ENDIF»
		«ENDFOR»
	'''	

	def dispatch CharSequence code(If it) {
		var result = ''''''
		if (this.eventMode) {
			result = result + stepComment
		}
		this.actionFound = false
		result = result + '''
		if («check.code») {
			«thenStep.code»
		} '''
		if (elseStep!=null) {
			this.actionFound = false
			result = result + '''
			else {
				«elseStep.code»
			}'''}
		return result;
	}
	
	def dispatch CharSequence code(Check it) {
	'''
		«stepComment»
		«IF condition != null»«condition.code»«ELSE»true«ENDIF»'''		
	}

	def dispatch CharSequence code(Execution it){
		if (this.eventMode) {'''
			«stepComment»
			«statement.code»;'''
		} else {
			this.requestAction
		}
	}

	def dispatch CharSequence code(EnterState it) { 
		if (this.eventMode) {'''
			stateConfVector[«state.stateVector.offset»] = «state.shortName»;
			stateConfVectorPosition = «state.stateVector.offset»;
			ShowMessage("«execution_flow.name» : at time t = " << t << " entering state '«state.shortName»'\n");
		'''} else {
			this.requestAction
		}
	}

	def dispatch CharSequence code(ExitState it) {
		if (this.eventMode) {'''
			stateConfVector[«state.stateVector.offset»] = «last_state»;
			stateConfVectorPosition = «state.stateVector.offset»;
			ShowMessage("«execution_flow.name» : at time t = " << t << " exiting state '«state.shortName»'\n");
		'''} else {
			this.requestAction
		}
	}
	
	def dispatch CharSequence code(StateSwitch it)  {
		if (this.eventMode) {'''
			«stepComment»
				switch(stateConfVector[ «stateConfigurationIdx» ]) {
				«FOR caseid : cases»
					case «caseid.state.shortName» : {
						«caseid.step.code»
						break;
					}
				«ENDFOR»
				default: break;
			}
		'''} else {
			this.requestAction
		}
	}
	
	def dispatch CharSequence code(Call it) 
	'''«step.shortName»();'''
	
	
	def CharSequence requestAction() {			
			if (!this.actionFound) {
				this.actionFound = true
				'''
				actionRequested = true;'''
			} else ''''''		
	}
}

