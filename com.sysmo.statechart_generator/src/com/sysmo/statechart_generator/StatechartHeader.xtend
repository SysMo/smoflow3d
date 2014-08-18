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

class StatechartHeader {
	@Inject extension Util
	@Inject extension INamingService
	@Inject extension Naming

	new() {
	
	}

	def generateHeader(ExecutionFlow it) {'''
		#ifndef «it.name.toUpperCase»_H_
		#define «it.name.toUpperCase»_H_
		
		#include "util/SimulationEnvironment.h"

		class «it.name» {
		public:
			«it.name»(SimulationEnvironment* simEnv);
			~«it.name»();
			
			typedef enum {
				«FOR ExecutionState state : it.states»
					«state.shortName»,
				«ENDFOR»
				«last_state»
			} «it.name»States;
			
			
		
			«FOR Scope scope : it.scopes»
				«scope.createScope()»
			«ENDFOR»
			
			void setParameters(double realParameterValues[],
				double integerParameterValues[]);
			void setInputs(double inputValues[]);
			void getOutputs(double outputValues[]);
			
			void init();
			void enter();
			void step();
		
		protected:
			SimulationEnvironment* simEnv;
			
			//! the maximum number of orthogonal states defines the dimension of the state configuration vector.
			static const int maxOrthogonalStates = «stateVector.size»;
			«it.name»States stateConfVector[maxOrthogonalStates];
			int stateConfVectorPosition;
			static const char* stateNames[«it.states.size»];

			void enact(){};
			bool isActionRequested();
			void react();
			«FOR state : states»
				«IF state.reactSequence!=null»
					void «state.reactSequence.shortName»();
				«ENDIF»
			«ENDFOR»
		
		};
		
		«it.name»* createController();  
		#endif // «it.name.toUpperCase»_H_
		
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