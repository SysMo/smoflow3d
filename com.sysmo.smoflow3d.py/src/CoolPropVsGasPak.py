import os
import sys
import csv


""" Import CoolProp """
path_CoolProp = '/data/SysMo/SoftwareLibs/CoolProp'
sys.path.append(path_CoolProp)
from CoolProp import CoolProp

fluidName_CoolProp = 'parahydrogen'


""" Import GasPak """
path_GasPak = "/data/SysMo/SoftwareLibs/PyFluid"
dataPath_GasPak = os.path.join(path_GasPak, 'FluidData')
sys.path.append(path_GasPak)

from GaspakFluidState import GaspakFluidState

fluidName_GasPak = 'parahydrogen'
ph2_GasPak = GaspakFluidState(fluidName_GasPak, dataPath_GasPak)



""" Util Functions """
def getDensity_CoolProp(p, t):
    return CoolProp.PropsSI('D', 'P', p, 'T', t, fluidName_CoolProp)

def getThermalConductivity_CoolProp(p, t):
    return CoolProp.PropsSI('L', 'P', p, 'T', t, fluidName_CoolProp)

def getDynamicViscosity_CoolProp(p, t):
    return CoolProp.PropsSI('V', 'P', p, 'T', t, fluidName_CoolProp)


def getDenisyt_GasPak(p, t):
    ph2_GasPak.setState('P', p, 'T', t)
    return ph2_GasPak.density

def getThermalConductivity_GasPak(p, t):
    ph2_GasPak.setState('P', p, 'T', t)
    return ph2_GasPak.thermalConductivity

def getDynamicViscosity_GasPak(p, t):
    ph2_GasPak.setState('P', p, 'T', t)
    return ph2_GasPak.dynamicViscosity


""" Test GasProp vs GasPak """
def testGasPropVsGasPak():
    p = 700e5
    t = 60
    
    print "Density: (CoolProp) = ", getDensity_CoolProp(p, t), "; (GasPak) = ", getDenisyt_GasPak(p, t)
    print "Thermal Conductivity: (CoolProp) = ", getThermalConductivity_CoolProp(p, t), "; (GasPak) = ", getThermalConductivity_GasPak(p, t)
    print "Dynamic Viscosity: (CoolProp) = ", getDynamicViscosity_CoolProp(p, t), "; (GasPak) = ", getDynamicViscosity_GasPak(p, t)


""" Test GasProp vs GasPak """
def test():
    print "=== START: GasProp vs GasPak ==="
    
    resultFile = "../results/GasPropVsGasPak.csv"
    with open(resultFile, 'w') as csvFile:
        csvWriter = csv.writer(csvFile, delimiter = ',')
        csvWriter.writerow([
            'Pressure', 'Temperature', 
            'Density - CoolProp', 'Thermal Conductivity - CoolProp','Dynamic Viscosity - CoolProp',
            'Density - GasPak', 'Thermal Conductivity - GasPak', 'Dynamic Viscosity - GasPak'
        ])
            
        p = 200e5
        step = 1
        for t in range(50, 300 + step, step):      
            csvWriter.writerow([
                p, t,  
                getDensity_CoolProp(p, t), getThermalConductivity_CoolProp(p, t), getDynamicViscosity_CoolProp(p, t),
                getDenisyt_GasPak(p, t), getThermalConductivity_GasPak(p, t), getDynamicViscosity_GasPak(p, t)
            ])
      
    print "The result is in '" + os.path.abspath(resultFile) + "'"
    print "=== END: GasProp vs GasPak ==="
      
      
# Execute main function
if __name__ == "__main__":    
    test()
