import sys
import numpy as np
import pylab as plt

############ CoolProp ############
path_CoolProp = "/data/SysMo/SoftwareLibs/CoolProp"
sys.path.append(path_CoolProp)

from CoolProp.CoolProp import PropsSI as FP
from CoolProp.CoolProp import DerivTerms as DT
from CoolProp.CoolProp import Phase

fluidName = 'ParaHydrogen'

class FluidPoint:
    def __init__(self, fluidName):
        self.fluidName = fluidName;
    def update_Tp(self, T, p):
        rho = FP('D', 'P', p, 'T', T, self.fluidName)
        T = FP('T', 'P', p, 'T', T, self.fluidName)
        self.update_Trho(T, rho)

    def update_px(self, p, x):
        rho = FP('D', 'P', p, 'Q', x, self.fluidName)
        T = FP('T', 'P', p, 'Q', x, self.fluidName)
        self.update_Trho(T, rho)
    
    def update_Trho(self, T, rho):
        self.T = T
        self.rho = rho
        self.v = 1./rho
        self.p = FP('P', 'T', T, 'D', rho, self.fluidName)
        self.h = FP('H', 'T', T, 'D', rho, self.fluidName)
        self.x = FP('Q', 'T', T, 'D', rho, self.fluidName)        
        self.u = FP('U', 'T', T, 'D', rho, self.fluidName)
        self.cv = FP('O', 'T', T, 'D', rho, self.fluidName)
        self.dp_drho_T = DT('dpdrho', T, rho, self.fluidName) * 1e3
        self.dp_dT_rho = DT('dpdT', T, rho, self.fluidName) * 1e3
    
        if (Phase(self.fluidName, self.T, self.p) == 'Two-Phase'):            
            self.cp = 0
            self.dv_dp_T  = 0
            self.dv_dT_p  = 0
            self.uL = FP('U', 'T', T, 'Q', 0, self.fluidName)
            self.uG = FP('U', 'T', T, 'Q', 1, self.fluidName)
            self.hL = FP('H', 'T', T, 'Q', 0, self.fluidName)
            self.hG = FP('H', 'T', T, 'Q', 1, self.fluidName)
            self.rhoL = FP('D', 'T', T, 'Q', 0, self.fluidName)
            self.rhoG = FP('D', 'T', T, 'Q', 1, self.fluidName)
            self.vL = 1./self.rhoL
            self.vG = 1./self.rhoG
            self.cvG = FP('O', 'T', T, 'Q', 1, self.fluidName)
            self.cvL = FP('O', 'T', T, 'Q', 0, self.fluidName)
            self.dp_dT_Sat = (self.hG - self.hL) / (T * (self.vG - self.vL))
        else:
            self.cp = FP('C', 'T', T, 'D', rho, self.fluidName)
            self.dv_dp_T  = - 1 / (self.rho * self.rho * self.dp_drho_T)
            self.dv_dT_p  = - self.dp_dT_rho * self.dv_dp_T
            self.dp_dT_Sat = 0 
            self.uL = 0
            self.uG = 0
            self.hL = 0
            self.hG = 0
            self.rhoL = 0
            self.rhoG = 0
            self.vL = 0
            self.vG = 0
            self.cvG = 0
            self.cvL = 0
    def __str__(self):
        return 'FluidPoint(p={self.p}, T = {self.T}, rho = {self.rho}, x = {self.x}, u = {self.u})'.format(self = self)

        
class NumericalDerivative:
    def compute(self, fp, dy, dx, cst):
        vIsPresent = 0
        if (dy == 'v'):
            vIsPresent = 1
            dy = 'rho'
        elif (dx == 'v'):
            vIsPresent = 2
            dx = 'rho'
        elif (cst == 'v'):
            vIsPresent = 3
            cst = 'rho'
        propMap = {'p' : 'P', 'x' : 'Q', 'rho' : 'D', 'T' : 'T', 'u' : 'U'}
        xCoeff = 0.9999
        xValue = fp.__dict__[dx]
        yValue = fp.__dict__[dy]
        if (cst == 'SatL'):
            y1Value = FP(propMap[dy], propMap[dx], xValue, 'Q', 0.0, fp.fluidName)
            y2Value = FP(propMap[dy], propMap[dx], xValue * xCoeff, 'Q', 0.0, fp.fluidName)
            rhoCorr = FP('D', propMap[dx], xValue, 'Q', 0.0, fp.fluidName)
        elif (cst == 'SatG'):
            y1Value = FP(propMap[dy], propMap[dx], xValue, 'Q', 1.0, fp.fluidName)
            y2Value = FP(propMap[dy], propMap[dx], xValue * xCoeff, 'Q', 1.0, fp.fluidName)
            rhoCorr = FP('D', propMap[dx], xValue, 'Q', 1.0, fp.fluidName)            
        else:
            constValue = fp.__dict__[cst]
            y1Value = yValue
            y2Value = FP(propMap[dy], propMap[dx], xCoeff * xValue, propMap[cst], constValue, fp.fluidName)            
            rhoCorr = fp.rho
        deriv = (y1Value - y2Value) / ((1 - xCoeff) * xValue)
        if (vIsPresent == 1):
            deriv *= (- 1.0 / (rhoCorr * rhoCorr))
        elif (vIsPresent == 2):
            deriv *= (- rhoCorr * rhoCorr )
        return deriv
    
        

p1 = FluidPoint(fluidName)
p2 = FluidPoint(fluidName)

der = NumericalDerivative()

# Single phae
print('=================== Single Phase ======================')
p1.update_Tp(T = 300, p = 1e5)
print p1
d1 = der.compute(fp = p1, dy = 'u', dx = 'T', cst = 'rho')
print("cv(analytical) = %f, cv(numerical) = %f"%(p1.cv, d1))
d1 = der.compute(fp = p1, dy = 'v', dx = 'p', cst = 'T')
print("dv_dp_T(analytical) = %e, dv_dp_T(numerical) = %e"%(p1.dv_dp_T, d1))
d1 = der.compute(fp = p1, dy = 'v', dx = 'T', cst = 'p')
print("dv_dT_p(analytical) = %e, dv_dT_p(numerical) = %e"%(p1.dv_dT_p, d1))
#Two phase
print('=================== Two Phase ======================')
p2.update_px(10.34736e5, 0.7503882)
p2L = FluidPoint(fluidName); p2L.update_Trho(p2.T, 1.0001*p2.rhoL)
p2G = FluidPoint(fluidName); p2G.update_Trho(p2.T, 0.9999*p2.rhoG)
print("Check Clausius-Clyperon")
d2 = der.compute(fp = p2, dy = 'p', dx = 'T', cst = 'SatL')
print("dp_dT_SatL(analytical) = %e, dp_dT_SatL(numerical) = %e"%(p2.dp_dT_Sat, d2))
dv_dt_satG = p2G.dv_dT_p + p2G.dv_dp_T * p2.dp_dT_Sat
dv_dt_satL = p2L.dv_dT_p + p2L.dv_dp_T * p2.dp_dT_Sat
dx_dt_v = der.compute(fp = p2, dy = 'x', dx = 'T', cst = 'v')
#du_dt_v = p2.x * p2G.cv + (1- p2.x) * p2L.cv + (p2G.u - p2L.u) / (p2G.v - p2L.v) * (p2.x * dv_dt_satG + (1 - p2.x) * dv_dt_satL)
du_dt_v = p2.x * p2G.cv + (1- p2.x) * p2L.cv + (p2G.u - p2L.u) * dx_dt_v

d2 = der.compute(fp = p2, dy = 'v', dx = 'T', cst = 'SatG')
print("dv_dT_SatG(analytical) = %e, dv_dT_SatG(numerical) = %e"%(dv_dt_satG, d2))
d2 = der.compute(fp = p2, dy = 'v', dx = 'T', cst = 'SatL')
print("dv_dT_SatL(analytical) = %e, dv_dT_SatL(numerical) = %e"%(dv_dt_satL, d2))
d2 = der.compute(fp = p2, dy = 'u', dx = 'T', cst = 'v')
print("cv(analytical) = %f, cv(anaytical, coolprop) = %f, cv(numerical) = %f"%(du_dt_v, p2.cv, d2))

d2 = der.compute(fp = p2, dy = 'p', dx = 'T', cst = 'rho')
print("dp_dT_rho(analytical) = %e, dp_dT_rho(numerical) = %e"%(p2.dp_dT_rho, d2))
d2 = der.compute(fp = p2, dy = 'p', dx = 'rho', cst = 'T')
print("dp_drho_T(analytical) = %e, dp_drho_T(numerical) = %e"%(p2.dp_drho_T, d2))
