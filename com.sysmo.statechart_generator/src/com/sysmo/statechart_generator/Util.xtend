package com.sysmo.statechart_generator

import com.google.inject.Inject
import org.yakindu.base.types.Type
import org.yakindu.base.types.ITypeSystem
import org.yakindu.sct.model.stext.stext.InterfaceScope
import org.yakindu.sct.model.sexec.ExecutionFlow
import org.yakindu.sct.model.sgraph.Scope
import org.yakindu.sct.model.sgraph.Variable
import org.yakindu.sct.model.stext.stext.VariableDefinition
import org.yakindu.sct.model.sexec.Step

class Util {
	@Inject	extension ITypeSystem

	new() {
		
	}

	def getTargetLanguageName(Type type) {
		switch (type) {
			case type == null || isVoidType(type): 'void'
			case isIntegerType(type): 'int'
			case isRealType(type): 'double'
			case isBooleanType(type): 'bool'
			case isStringType(type): 'String'
		}
	}
	
	def InterfaceScope getScope(ExecutionFlow flow, String name) {
		for (Scope scope : flow.scopes) {
			if (scope instanceof InterfaceScope) {
				val iScope = scope as InterfaceScope
				if (iScope.name == name) {
					return iScope
				}
				
			}
		}
		throw new IllegalArgumentException("No scope with name " + name)
	}
	
	def getRealParameters(ExecutionFlow it) {
		getScope("parameters").variables.filter[
				v | (v as VariableDefinition).type.name == "real"
		]
	}
	
	def getIntegerParameters(ExecutionFlow it) {
		getScope("parameters").variables.filter[
				v | (v as VariableDefinition).type.name == "integer"
		]		
	}

	def getInputs(ExecutionFlow it) {
		getScope("inputs").variables
	}

	def getOutputs(ExecutionFlow it) {
		getScope("outputs").variables
	}

	def setValuesFromArray(Iterable<Variable> variables, String groupName, String arrayName) {
		var i = 0
		var result = ''''''
		for (v : variables) {			
			result = result + 
			'''«groupName».«(v as VariableDefinition).name» = «arrayName»[«Integer.toString(i)»];
			'''
			i = i + 1
		}
		return result
		
	}
	
	def getValuesToArray(Iterable<Variable> variables, String groupName, String arrayName) {
		var i = 0
		var result = ''''''
		for (v : variables) {			
			result = result + 
			'''«arrayName»[«Integer.toString(i)»] = «groupName».«(v as VariableDefinition).name»;
			'''
			i = i + 1
		}
		return result
		
	}
	
	def stepComment(Step it) '''
		«IF !comment.nullOrEmpty»
			/* «comment» */
		«ENDIF»
	'''
	
	
}