import os
import sys
import csv
import pylab as plt
import numpy as np


############ GasPak #############
path_GasPak = "/data/SysMo/SoftwareLibs/PyFluid"
dataPath_GasPak = os.path.join(path_GasPak, 'FluidData')
sys.path.append(path_GasPak)
from GaspakFluidState import GaspakFluidState
ph2_GasPak = GaspakFluidState('pH2', dataPath_GasPak)
nh2_GasPak = GaspakFluidState('nH2', dataPath_GasPak)
n2_GasPak = GaspakFluidState('nitrogen', dataPath_GasPak)

############ CoolProp ############
path_CoolProp = "/data/SysMo/SoftwareLibs/CoolProp"
sys.path.append(path_CoolProp)
from CoolProp.CoolProp import PropsSI as CP

############# SmoFlow ###############
import h2_transport as smoh2

class FluidData:
    def __init__(self):
        self.T = []
        self.p = []
        self.rho = []
        self.h = []
        self.cp = []
        self.mu = []
        self.cond = []
        self.numPs = 0

    def createArrays(self, pDef, TDef):
    #    if (not isinstance(TList[0], np.array)
        self.numPs = len(pDef)
        for pVal in pDef:
            pArray = np.ones(np.size(TDef)) * pVal
            TArray = TDef * 0
            TArray[:] = TDef[:]
            self.p.append(pArray)
            self.T.append(TArray)
            self.rho.append(TDef * 0)
            self.h.append(TDef * 0)
            self.cp.append(TDef * 0)
            self.mu.append(TDef * 0)
            self.cond.append(TDef * 0)
                    
                
def computeGasPak(fdata, gpc):
    for iP in range(fdata.numPs):
        for iT in range(len(fdata.p[iP])):
            gpc.setState('P', fdata.p[iP][iT], 'T', fdata.T[iP][iT])
            fdata.rho[iP][iT] = gpc.density
            fdata.h[iP][iT] = gpc.enthalpy
            fdata.cp[iP][iT] = gpc.cp
            fdata.mu[iP][iT] = gpc.dynamicViscosity
            fdata.cond[iP][iT] = gpc.thermalConductivity

def computeCoolProp(fdata, fluidName):
    for iP in range(fdata.numPs):
        for iT in range(len(fdata.p[iP])):
            fdata.rho[iP][iT] = CP('D', 'P', fdata.p[iP][iT], 'T', fdata.T[iP][iT], fluidName)
            fdata.h[iP][iT] = CP('H', 'P', fdata.p[iP][iT], 'T', fdata.T[iP][iT], fluidName)
            fdata.cp[iP][iT] = CP('C', 'P', fdata.p[iP][iT], 'T', fdata.T[iP][iT], fluidName)
            fdata.mu[iP][iT] = CP('V', 'P', fdata.p[iP][iT], 'T', fdata.T[iP][iT], fluidName)
            fdata.cond[iP][iT] = CP('L', 'P', fdata.p[iP][iT], 'T', fdata.T[iP][iT], fluidName)
            
def computeSmoFlow(fdata, fluidName):
    if fluidName == "ParaHydrogen":
        muFunc = smoh2.ParaHydrogen_viscosity
        lambdaFunc = smoh2.ParaHydrogen_thermalConductivity
    for iP in range(fdata.numPs):
        for iT in range(len(fdata.p[iP])):
            fdata.rho[iP][iT] = CP('D', 'P', fdata.p[iP][iT], 'T', fdata.T[iP][iT], fluidName)
            fdata.h[iP][iT] = CP('H', 'P', fdata.p[iP][iT], 'T', fdata.T[iP][iT], fluidName)
            fdata.cp[iP][iT] = CP('C', 'P', fdata.p[iP][iT], 'T', fdata.T[iP][iT], fluidName)
            fdata.mu[iP][iT] = muFunc(fdata.T[iP][iT], fdata.rho[iP][iT]) 
            fdata.cond[iP][iT] = lambdaFunc(fdata.T[iP][iT], fdata.rho[iP][iT]) 


def comparativePlot(plotType, fluidDataList, lineStyles, lineLabels):
    plt.hold(True)
    
    for fd, lineType, lineLabel in zip(fluidDataList, lineStyles, lineLabels):
        for iP in range(fd.numPs):
            if plotType == "p":
                plt.plot(fd.T[iP], fd.p[iP], lineType, label = lineLabel)
                plt.ylabel("Pressure [Pa]")
            elif plotType == "rho":
                plt.plot(fd.T[iP], fd.rho[iP], lineType, label = lineLabel)
                plt.ylabel("Density [kg/m**3]")
            elif plotType == "h":
                plt.plot(fd.T[iP], fd.h[iP], lineType, label = lineLabel)
                plt.ylabel("Specific enthalpy [J/kg]")
            elif plotType == "cp":
                plt.plot(fd.T[iP], fd.cp[iP], lineType, label = lineLabel)
                plt.ylabel("Cp [J/kg-K]")
            elif plotType == "mu":
                plt.plot(fd.T[iP], fd.mu[iP], lineType, label = lineLabel)          
                plt.ylabel("Dynamic viscosity [Pa-s]")
            elif plotType == "lambda":
                plt.plot(fd.T[iP], fd.cond[iP], lineType, label = lineLabel)
                plt.ylabel("Thermal conductivity [W/m**2-K]")
            
    plt.xlabel("Temperature [K]")
    plt.xscale('log')
    plt.xlim([TMin,TMax])
    plt.gca().get_xaxis().get_major_formatter().labelOnlyBase = False
    #plt.legend()
    plt.title("Comparison plot")

TMin = 33
TMax = 1300

pDef = [10e5, 20e5, 50e5, 100e5, 200e5, 400e5, 900e5]
TDef = np.logspace(np.log10(TMin), np.log10(TMax), 1000)

fGP = FluidData()
fCP = FluidData()
fSM = FluidData()

fGP.createArrays(pDef, TDef)
fCP.createArrays(pDef, TDef)
fSM.createArrays(pDef, TDef)

computeGasPak(fGP, ph2_GasPak)
#computeCoolProp(fCP, "ParaHydrogen")
computeSmoFlow(fSM, "ParaHydrogen")

#computeGasPak(fGP, n2_GasPak)
#computeCoolProp(fCP, "Nitrogen")

comparativePlot("lambda", [fGP, fSM], ["b-", "ro"], ["GasPak", "CoolProp"])
plt.show()

# rhoList = TList * 0
# muListGP = TList * 0
# muListSmo = TList * 0
# lambdaListGP = TList * 0
# lambdaListSmo = TList * 0
# 
# i = 0
# for T in TList:
#     ph2_GasPak.setState('P', pVal, 'T', T)
#     rhoList[i] = ph2_GasPak.density
#     muListGP[i] = ph2_GasPak.dynamicViscosity
#     muListSmo[i] = h2.viscosity(T, ph2_GasPak.density)
#     lambdaListGP[i] = ph2_GasPak.thermalConductivity
#     lambdaListSmo[i] = h2.thermalConductivity(T, ph2_GasPak.density)
#     i += 1
# 
# # Statistics
# muMean = np.mean(muListGP)
# muErr = np.sqrt(np.sum((muListGP - muListSmo)**2) / np.size(muListGP))
# print ("muMean = %e, muErr = %e"%(muMean, muErr))
# 
# lambdaMean = np.mean(lambdaListGP)
# lambdaErr = np.sqrt(np.sum((lambdaListGP - lambdaListSmo)**2) / np.size(lambdaListGP))
# print ("lambdaMean = %e, lambdaErr = %e"%(lambdaMean, lambdaErr))
# 
# 
# import pylab as plt
# plt.hold(True)
# #plt.plot(TList, muListGP, label = 'GasPak')
# #plt.plot(TList, muListSmo, '.', label = 'CoolProp')
# plt.plot(TList, lambdaListGP, label = 'GasPak')
# plt.plot(TList, lambdaListSmo, '.', label = 'CoolProp')
# plt.legend()
# plt.show()

