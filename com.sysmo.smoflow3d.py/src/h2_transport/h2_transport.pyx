cdef extern from "CalcH2TransportProps.h":
    double ParaHydrogen_viscosity_Trho (double T, double rho)
    double ParaHydrogen_thermalConductivity_Trho (double T, double rho)
    
cpdef ParaHydrogen_viscosity(T, rho):
    return ParaHydrogen_viscosity_Trho(T, rho)

cpdef ParaHydrogen_thermalConductivity(T, rho):
    return ParaHydrogen_thermalConductivity_Trho(T, rho)