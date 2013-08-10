import os
import sys
import csv

path_GasPak = "/data/SysMo/SoftwareLibs/PyFluid"
dataPath_GasPak = os.path.join(path_GasPak, 'FluidData')
sys.path.append(path_GasPak)

from GaspakFluidState import GaspakFluidState

fluidName_GasPak = 'parahydrogen'
fluid_GasPak = GaspakFluidState(fluidName_GasPak, dataPath_GasPak)

import h2_transport as h2

import numpy as np

p = 500e5
TList = np.linspace(30, 300, 300)
rhoList = TList * 0
muListGP = TList * 0
muListSmo = TList * 0
lambdaListGP = TList * 0
lambdaListSmo = TList * 0

i = 0
for T in TList:
    fluid_GasPak.setState('P', p, 'T', T)
    rhoList[i] = fluid_GasPak.density
    muListGP[i] = fluid_GasPak.dynamicViscosity
    muListSmo[i] = h2.viscosity(T, fluid_GasPak.density / 1000)
    lambdaListGP[i] = fluid_GasPak.thermalConductivity
    lambdaListSmo[i] = h2.thermalConductivity(T, fluid_GasPak.density / 1000)
    i += 1

# Statistics
muMean = np.mean(muListGP)
muErr = np.sqrt(np.sum((muListGP - muListSmo)**2)//np.size(muListGP))
print ("muMean = %e, muErr = %e"%(muMean, muErr))

lambdaMean = np.mean(lambdaListGP)
lambdaErr = np.sqrt(np.sum((lambdaListGP - lambdaListSmo)**2)//np.size(lambdaListGP))
print ("lambdaMean = %e, lambdaErr = %e"%(lambdaMean, lambdaErr))


import pylab as plt
plt.hold(True)
#plt.plot(TList, muListGP)
#plt.plot(TList, muListSmo)
plt.plot(TList, lambdaListGP)
plt.plot(TList, lambdaListSmo, '.')
plt.show()

