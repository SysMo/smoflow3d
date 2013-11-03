import numpy as np
import sys
path_CoolProp = "D:\Workspace\Projects\SysMo\SmoFlow3D\smoflow3d\com.sysmo.smoflow3d\python"
sys.path.append(path_CoolProp)

from Media import Medium, MediumState


""" Create fluids """
para_hydrogen = Medium.create(Medium.sCompressibleFluidCoolProp, 'ParaHydrogen', 1)


""" Pipe class """
class Pipe():
    def __init__(self, diameter, length):
        self.diameter = diameter
        self.length = length
        
        # Set straight pipe properties
        self.hydraulicDiameter = self.diameter
        self.flowArea = np.pi * slef.diameter^2 / 4.
        self.flowFactor = self.length / slef.diameter
        
        # Create states
        self.state1 = MediumState(para_hydrogen)
        self.state2 = MediumState(para_hydrogen)

    def computePressureDrop(self, massFlowRate):
        absMassFlowRate = np.abs(massFlowRate)
        upstreamState = state1
        if massFlowRate < 0:
            upstreamState = state2
        
        
        #@see VDI Heat Atlas, L1.2.1 (page 1057), Eq. (2)
        vFlow = absMassFlowRate / (upstreamState) #volumetric flow
    

""" Valve class """
class Valve():
    pass


""" Test functions """
def testMediaProperties():
    state1 = MediumState(para_hydrogen)
    state1.update_Tp(288, 700e5)
    print state1.rho()
    print state1.cond()

    
""" Execute main function """
if __name__ == "__main__":    
    testMediaProperties()