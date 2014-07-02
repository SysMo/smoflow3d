cdef extern from "CalcH2TransportProps.h":
    double viscosity_Trho (double T, double rho)
    double thermalConductivity_Trho (double T, double rho)
    
cpdef viscosity(T, rho):
    return viscosity_Trho(T, rho)

cpdef thermalConductivity(T, rho):
    return thermalConductivity_Trho(T, rho)