cdef extern from "CalcH2TransportProps.h":
    double viscosity_Trho (double T, double rho)

STUFF = "Hi"

def viscosity(T, rho):
    return viscosity_Trho (T, rho)
