package com.sysmo.statechart_generator

import org.yakindu.sct.model.stext.stext.VariableDefinition
import org.yakindu.sct.model.stext.stext.OperationDefinition
import com.google.inject.Inject
import org.yakindu.sct.generator.cpp.Navigation
import org.yakindu.sct.model.sexec.naming.INamingService
import org.yakindu.sct.model.stext.stext.InterfaceScope
import org.yakindu.sct.model.stext.stext.InternalScope

class Naming extends org.yakindu.sct.generator.cpp.Naming {
	@Inject extension Navigation
	@Inject extension INamingService
	
	override dispatch instance(InterfaceScope it) {
		return it.name	
	}
	
	override dispatch access (VariableDefinition it) {
		if (scope instanceof InternalScope) {
			'''«name.asEscapedIdentifier»'''
		} else {
		'''«scope.instance».«name.asEscapedIdentifier»'''
		}	
	}
	
	override dispatch access (OperationDefinition it) {
		if (scope instanceof InternalScope) {
			'''«name.asEscapedIdentifier»'''
		} else {
		'''«scope.instance».«name.asEscapedIdentifier»'''
		}	
	}
}