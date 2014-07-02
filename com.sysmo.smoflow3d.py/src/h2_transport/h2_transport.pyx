cdef extern from "CalcH2TransportProps.h":
    double viscosity_Trho (double T, double rho)

cpdef viscosity(T, rho):
    return viscosity_Trho(T, rho)