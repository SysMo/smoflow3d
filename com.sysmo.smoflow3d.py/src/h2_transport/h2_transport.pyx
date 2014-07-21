cdef extern from "CalcH2TransportProps.h":
    double ParaHydrogen_viscosity_Trho (double T, double rho)
    double ParaHydrogen_thermalConductivity_Trho (double T, double rho)
    
def ParaHydrogen_viscosity(double T, double rho):
    return ParaHydrogen_viscosity_Trho(T, rho)

def ParaHydrogen_thermalConductivity(double T, double rho):
    return ParaHydrogen_thermalConductivity_Trho(T, rho)