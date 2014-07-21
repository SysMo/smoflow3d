import sys
import numpy as np
import pylab as plt

############ CoolProp ############
path_CoolProp = "/data/SysMo/SoftwareLibs/CoolProp"
sys.path.append(path_CoolProp)

from CoolProp.CoolProp import PropsSI as FP
from CoolProp.CoolProp import DerivTerms as DT

fluidName = 'ParaHydrogen'
pCrit = FP(fluidName, 'pcrit')
TCrit = FP(fluidName, 'Tcrit')
rhoCrit = FP(fluidName, 'rhocrit')
epsCrit = 0.2
print ('Using circle with radius rT = %f, rRho = %f' %(epsCrit * TCrit, epsCrit * rhoCrit))

print('pCrit = %e, TCrit = %f, rhoCrit = %f'%(pCrit, TCrit, rhoCrit))

TList = np.linspace (0.95 * TCrit, 1.05 * TCrit, 10000)
pList1 = TList * 0 + pCrit
pList2 = TList * 0 + pCrit
rhoList1 = TList * 0
rhoList2 = TList * 0

derivProp1 = TList * 0
derivProp2 = TList * 0
#derivName = 'dpdT'
#derivName = 'dpdrho'
derivName = 'C'

def cp_smoothed(T, rho, fluidName):
    TRed = T / TCrit
    rhoRed = rho / rhoCrit
    
    dist2Crit = (TRed - 1)**2 + (rhoRed - 1)**2
    if ( dist2Crit < epsCrit**2):
        distCrit = np.sqrt(dist2Crit)
        TRed = 1 + (TRed - 1) * epsCrit / distCrit
        rhoRed = 1 + (rhoRed - 1) * epsCrit / distCrit
        T = TRed * TCrit
        rho = rhoRed * rhoCrit 
    cp = FP('C', 'T', T, 'D', rho, fluidName)
    return cp

for i in range(len(TList)):
    rhoList1[i] = FP('D', 'P', pList1[i], 'T', TList[i], fluidName) 
    rhoList2[i] = FP('D', 'P', pList2[i], 'T', TList[i], fluidName) 
    #derivProp[i] = DT(derivName, TList[i], rhoList[i], fluidName)
    derivProp1[i] = FP(derivName, 'T', TList[i], 'D', rhoList1[i], fluidName)
    derivProp2[i] = cp_smoothed(TList[i], rhoList2[i], fluidName)

plt.hold(True)
plt.plot(TList, derivProp1, 'r', label = 'Crit')
plt.plot(TList, derivProp2, 'g', label = '2')
plt.plot(TList, rhoList1, 'r', label = 'Crit')
plt.plot(TList, rhoList2, 'g', label = '2')

plt.yscale('log')
plt.title(derivName)
plt.legend()
plt.show()