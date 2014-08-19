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
		
		#include "util/SimulationEnvironment.h"

		class «name» {
		public:
			«name»(SimulationEnvironment* simEnv);
			~«name»();
			int getUUID() {
				return «UUID.randomUUID().hashCode()»;
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
					int& numInputs, int& numOutputs) {
				numRealParameters = «realParameters.size»;
				numIntegerParameters = «integerParameters.size»;
				numInputs = «inputs.size»;
				numOutputs = «outputs.size»;
			}
			void setParameters(double realParameterValues[],
				int integerParameterValues[]);
			void setInputs(double inputValues[]);
			void getOutputs(double outputValues[]);
			
			void init();
			void enter();
			bool isActionRequested();
			void react();
		
		protected:
			SimulationEnvironment* simEnv;
			
			//! the maximum number of orthogonal states defines the dimension of the state configuration vector.
			static const int maxOrthogonalStates = «stateVector.size»;
			«name»States stateConfVector[maxOrthogonalStates];
			int stateConfVectorPosition;
			static const char* stateNames[«states.size»];
			static const char* parameterNames[«getScope("parameters").variables.size»];
			static const char* inputNames[«getScope("inputs").variables.size»];
			static const char* outputNames[«getScope("outputs").variables.size»];

			void enact(){};
			«FOR state : states»
				«IF state.reactSequence!=null»
					void «state.reactSequence.shortName»();
				«ENDIF»
			«ENDFOR»
		
		};
		
		BEGIN_C_LINKAGE
		«module»* createController(SimulationEnvironment* simEnv);
		void getSizes(«module»* controller, 
					int* numRealParameters, int* numIntegerParameters,
					int* numInputs, int* numOutputs);
		void init(«module»* controller);

		void setParameters(«module»* controller,
				double realParameterValues[],
				int integerParameterValues[]);
		void setInputs(«module»* controller, double inputValues[]);
		void getOutputs(«module»* controller, double outputValues[]);

		void enter(«module»* controller);
		int isActionRequested(«module»* controller);
		void react(«module»* controller);
		
		END_C_LINKAGE
		
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