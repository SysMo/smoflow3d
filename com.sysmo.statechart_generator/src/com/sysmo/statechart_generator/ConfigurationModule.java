package com.sysmo.statechart_generator;

import java.lang.reflect.InvocationTargetException;

import org.eclipse.emf.common.notify.Adapter;
import org.eclipse.emf.common.notify.Notification;
import org.eclipse.emf.common.util.EList;
import org.eclipse.emf.common.util.TreeIterator;
import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.EObject;
import org.eclipse.emf.ecore.EOperation;
import org.eclipse.emf.ecore.EReference;
import org.eclipse.emf.ecore.EStructuralFeature;
import org.eclipse.emf.ecore.resource.Resource;
import org.yakindu.sct.generator.c.types.CTypeSystemAccess;
import org.yakindu.sct.generator.core.IGeneratorBridge;
import org.yakindu.sct.generator.core.types.ICodegenTypeSystemAccess;
import org.yakindu.sct.generator.cpp.CppNamingService;
import org.yakindu.sct.model.sexec.naming.INamingService;
import org.yakindu.sct.model.sgen.FeatureConfiguration;
import org.yakindu.sct.model.sgen.GeneratorEntry;

import com.google.inject.Binder;
import com.google.inject.Module;

public class ConfigurationModule implements Module {

	public void configure(Binder binder) {
		binder.bind(ICodegenTypeSystemAccess.class).to(
				CTypeSystemAccess.class);
		binder.bind(INamingService.class).to(CppNamingService.class);
		GeneratorEntry entry = new GeneratorEntry() {
			
			public void eSetDeliver(boolean deliver) {
				// TODO Auto-generated method stub
				
			}
			
			public void eNotify(Notification notification) {
				// TODO Auto-generated method stub
				
			}
			
			public boolean eDeliver() {
				// TODO Auto-generated method stub
				return false;
			}
			
			public EList<Adapter> eAdapters() {
				// TODO Auto-generated method stub
				return null;
			}
			
			public void eUnset(EStructuralFeature feature) {
				// TODO Auto-generated method stub
				
			}
			
			public void eSet(EStructuralFeature feature, Object newValue) {
				// TODO Auto-generated method stub
				
			}
			
			public Resource eResource() {
				// TODO Auto-generated method stub
				return null;
			}
			
			public boolean eIsSet(EStructuralFeature feature) {
				// TODO Auto-generated method stub
				return false;
			}
			
			public boolean eIsProxy() {
				// TODO Auto-generated method stub
				return false;
			}
			
			public Object eInvoke(EOperation operation, EList<?> arguments)
					throws InvocationTargetException {
				// TODO Auto-generated method stub
				return null;
			}
			
			public Object eGet(EStructuralFeature feature, boolean resolve) {
				// TODO Auto-generated method stub
				return null;
			}
			
			public Object eGet(EStructuralFeature feature) {
				// TODO Auto-generated method stub
				return null;
			}
			
			public EList<EObject> eCrossReferences() {
				// TODO Auto-generated method stub
				return null;
			}
			
			public EList<EObject> eContents() {
				// TODO Auto-generated method stub
				return null;
			}
			
			public EReference eContainmentFeature() {
				// TODO Auto-generated method stub
				return null;
			}
			
			public EStructuralFeature eContainingFeature() {
				// TODO Auto-generated method stub
				return null;
			}
			
			public EObject eContainer() {
				// TODO Auto-generated method stub
				return null;
			}
			
			public EClass eClass() {
				// TODO Auto-generated method stub
				return null;
			}
			
			public TreeIterator<EObject> eAllContents() {
				// TODO Auto-generated method stub
				return null;
			}
			
			public void setElementRef(EObject value) {
				// TODO Auto-generated method stub
				
			}
			
			public void setContentType(String value) {
				// TODO Auto-generated method stub
				
			}
			
			public EList<FeatureConfiguration> getFeatures() {
				// TODO Auto-generated method stub
				return null;
			}
			
			public FeatureConfiguration getFeatureConfiguration(String featureName) {
				// TODO Auto-generated method stub
				return null;
			}
			
			public EObject getElementRef() {
				// TODO Auto-generated method stub
				return null;
			}
			
			public String getContentType() {
				// TODO Auto-generated method stub
				return null;
			}
		};
		binder.bind(GeneratorEntry.class).toInstance(entry);
		/*
		
		binder.bind(IGeneratorBridge.class).toInstance(bridge);
		
		throw new IllegalArgumentException("Screw u");
		/*
		Naming
		Navigation
		FlowCode
		GenmodelEntries
		
		ExpressionCode
		ISTextTypeInferrer
		 */
		/*
		 * Done
		ICodegenTypeSystemAccess
		INamingService
		 * 
		 */
	}

}
