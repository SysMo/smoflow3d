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

		«name»::«name»(SimulationEnvironment* simEnv) {
			this->simEnv = simEnv;
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

		void «name»::getOutputs(double outputValues[]) {
			«getValuesToArray(outputs, "outputs", "outputValues")»
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
		«name»* createController(SimulationEnvironment* simEnv) {
			return new «module»(simEnv);
		}
		
		void getSizes(«module»* controller, 
			int* numRealParameters, int* numIntegerParameters,
			int* numInputs, int* numOutputs) {
				controller->getSizes(*numRealParameters, *numIntegerParameters,
						*numInputs, *numOutputs);
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
		
		void getOutputs(«module»* controller, double outputValues[]) {
			controller->getOutputs(outputValues);
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
	
	def checkForTransitionCase(ExecutionState state) {'''
	'''			
	}
	
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

	def dispatch CharSequence code(If it) '''
		«IF (this.eventMode)»«stepComment»«ENDIF»
		if («check.code») { 
			«thenStep.code»
		} «IF (elseStep != null)» else {
			«elseStep.code»
		}
		«ENDIF»
	'''
	
	def dispatch CharSequence code(Check it) {
		this.actionFound = false
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
			simEnv->message("«execution_flow.name» : Entering state '«state.shortName»'");
		'''} else {
			this.requestAction
		}
	}

	def dispatch CharSequence code(ExitState it) {
		if (this.eventMode) {'''
			stateConfVector[«state.stateVector.offset»] = «last_state»;
			stateConfVectorPosition = «state.stateVector.offset»;
			simEnv->message("«execution_flow.name» : Exiting state '«state.shortName»'");
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

