package com.sysmo.statechart_generator

import org.yakindu.sct.model.stext.stext.VariableDefinition
import com.google.inject.Inject
import org.yakindu.sct.generator.cpp.Navigation
import org.yakindu.sct.generator.core.types.ICodegenTypeSystemAccess
import org.yakindu.sct.model.sexec.naming.INamingService
import org.yakindu.sct.model.stext.stext.InterfaceScope

class Naming extends org.yakindu.sct.generator.cpp.Naming {
	@Inject extension Navigation
	@Inject extension ICodegenTypeSystemAccess
	@Inject extension INamingService
	
	override dispatch instance(InterfaceScope it) {
		return it.name	
	}
	
	override dispatch access (VariableDefinition it) 
	'''«scope.instance».«name.asEscapedIdentifier»'''
}