package com.sysmo.statechart_generator

import com.google.inject.Inject
import org.yakindu.sct.model.sexec.ExecutionFlow
import org.yakindu.sct.model.sexec.ExecutionState
import org.yakindu.sct.model.sgraph.Scope
import org.yakindu.sct.model.stext.stext.InterfaceScope
import org.yakindu.sct.model.stext.stext.InternalScope
import org.yakindu.sct.model.stext.stext.StatechartScope
import org.yakindu.sct.model.sgraph.Variable
import org.yakindu.sct.model.stext.stext.VariableDefinition
import org.yakindu.sct.model.sgraph.Declaration
import org.yakindu.sct.model.sexec.naming.INamingService
import java.util.UUID

class StatechartHeader {
	@Inject extension Util
	@Inject extension INamingService
	@Inject extension Naming

	new() {
	
	}

	def generateHeader(ExecutionFlow it) {'''
		#ifndef «name.toUpperCase»_H_
		#define «name.toUpperCase»_H_
		
		typedef void (*SimEnv_MessageFunc)(const char* text);
		typedef void (*SimEnv_ErrorFunc)(const char* text);

		class «name» {
		public:
			«name»(SimEnv_MessageFunc messageFunc, SimEnv_ErrorFunc errorFunc);
			~«name»();
			const char* getName() {
				return "«name»";
			}
			const char* getUUID() {
				return "«UUID.randomUUID()»";
			}
			typedef enum {
				«FOR ExecutionState state : states»
					«state.shortName»,
				«ENDFOR»
				«last_state»
			} «name»States;
		
			«FOR Scope scope : scopes»
				«scope.createScope()»
			«ENDFOR»
			
			void getSizes(
					int& numRealParameters, int& numIntegerParameters,
					int& numInputs, int& numOutputs, int& maxNumOrthogonalStates) {
				numRealParameters = «realParameters.size»;
				numIntegerParameters = «integerParameters.size»;
				numInputs = «inputs.size»;
				numOutputs = «outputs.size»;
				maxNumOrthogonalStates = «stateVector.size»;
			}
			void setParameters(double realParameterValues[],
				int integerParameterValues[]);
			void setInputs(double inputValues[]);
			void setTime(double t);
			void getOutputs(double outputValues[]);
			void getState(int stateVector[]);
			
			void init();
			void enter();
			bool isActionRequested();
			void react();
		
		protected:
			SimEnv_MessageFunc _message;
			SimEnv_ErrorFunc _error;

			double t;
			//! the maximum number of orthogonal states defines the dimension of the state configuration vector.
			static const int maxOrthogonalStates = «stateVector.size»;
			«name»States stateConfVector[maxOrthogonalStates];
			int stateConfVectorPosition;

			void enact_SequenceImpl(){};
			«FOR state : states»
				«IF state.reactSequence!=null»
					void «state.reactSequence.shortName»();
				«ENDIF»
			«ENDFOR»
					
		};
		
		extern "C" {
		«module»* createController(SimEnv_MessageFunc messageFunc, SimEnv_ErrorFunc errorFunc);
		void getSizes(«module»* controller, 
					int* numRealParameters, int* numIntegerParameters,
					int* numInputs, int* numOutputs, int* maxNumOrthogonalStates);
		void init(«module»* controller);

		void setParameters(«module»* controller,
				double realParameterValues[],
				int integerParameterValues[]);
		void setInputs(«module»* controller, double inputValues[]);
		void setTime(«module»* controller, double t);
		void getOutputs(«module»* controller, double outputValues[]);
		void getState(«module»* controller, int stateVector[]);

		void enter(«module»* controller);
		int isActionRequested(«module»* controller);
		void react(«module»* controller);
		
		}
		
		#endif // «name.toUpperCase»_H_
		
	'''.toString()
	}


	def protected createScope(Scope scope) {
		switch scope {
			InterfaceScope: scope.createScope()
			InternalScope: {
				
			}
		}
	}
	
	def protected createScope(InterfaceScope scope) {'''
		struct {
			«scope.createInterface()»
		} «scope.name»;
		
	'''}
			
	def protected createInterface(StatechartScope scope) {'''
		«FOR Variable variable : scope.variables»
			«variable.structDeclaration()»
		«ENDFOR»			
	'''}
	
	def dispatch structDeclaration(VariableDefinition it) {'''
		«IF type.name != 'void'»«type.targetLanguageName» «name»;«ENDIF»
	'''}

	def dispatch structDeclaration(Declaration it) ''''''
	
}