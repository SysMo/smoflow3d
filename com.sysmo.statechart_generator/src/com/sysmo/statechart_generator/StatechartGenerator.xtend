package com.sysmo.statechart_generator

import com.google.inject.Inject
import java.io.File
import java.io.FileOutputStream
import org.eclipse.xtext.generator.IFileSystemAccess
import org.yakindu.sct.generator.core.AbstractWorkspaceGenerator
import org.yakindu.sct.generator.core.impl.IExecutionFlowGenerator
import org.yakindu.sct.model.sexec.ExecutionFlow
import org.yakindu.sct.model.sgen.GeneratorEntry

class StatechartGenerator extends AbstractWorkspaceGenerator implements IExecutionFlowGenerator {
	@Inject extension StatechartHeader
	@Inject extension StatechartImplementation
	
	

	override generate(ExecutionFlow flow, GeneratorEntry entry, IFileSystemAccess access) {
		entry.targetFolder.write(flow.name+'.h', flow.generateHeader)
		entry.targetFolder.write(flow.name+'.cpp', flow.generateImplementation)
		entry.targetFolder.write('Makefile', flow.generateMakefile)
		refreshTargetProject(entry)
	}
	
	def String generateMakefile(ExecutionFlow flow)'''
		build : «flow.name».so
		
		«flow.name».so: «flow.name».cpp «flow.name».h
			gcc -o «flow.name».so -shared -fPIC -I../../smoflow3d/com.sysmo.smoflow3d/src «flow.name».cpp			  
	'''

	def write(File dir, String filename, String content) {
		try {
			dir.mkdirs
			val bos = new FileOutputStream(new File(dir.path+File::separator+filename))
			bos.write(content.bytes)
			bos.close
		} catch(Exception e) {
			writeToConsole(e)
		}
	}
		
}
