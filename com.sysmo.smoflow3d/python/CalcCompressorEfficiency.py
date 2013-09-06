import numpy as np
import numpy.linalg
import matplotlib.pyplot as plt
from Media import Medium, MediumState


""" Parameters """
fluid = Medium.create(Medium.sCompressibleFluidCoolProp, 'ParaHydrogen', 1)

T_out_arr = np.array([43.5, 44, 44.5, 45, 46, 48, 49, 50, 56, 63]) #[K]
p_out_arr = np.array([10, 20, 50, 60, 100, 200, 300, 400, 600, 800]) #[bar]
#T_out_arr = T_out_arr[:6]
#p_out_arr = p_out_arr[:6]
p_out_arr = p_out_arr*1e5 # convert bar to Pa



""" Define states """
p_in = 2e5 #[Pa]
fstate_in = MediumState(fluid)
fstate_in.update_pq(p_in, 0) #pressure [Pa], gas mass fraction [-]

fstate_out_ideal = MediumState(fluid)
fstate_out_real = MediumState(fluid)



""" Find  isentropic efficiency """
eff_arr = np.zeros(len(p_out_arr)) #isentropic efficiency
for i in range(len(p_out_arr)):
    p = p_out_arr[i]
    T = T_out_arr[i]

    fstate_out_ideal.update_ps(p, fstate_in.s())
    h_ideal =  fstate_out_ideal.h()

    fstate_out_real.update_Tp(T, p)
    h_real = fstate_out_real.h()

    eff_arr[i] = (h_ideal - fstate_in.h())/(h_real - fstate_in.h())

print "isoentropic efficiency = ", eff_arr



""" Find a fit in term 'c - exp(a*tau+b)' of the isoentropic efficiency by tau """
tau_arr = p_out_arr/p_in

def f_fit(x, a, b, c):
    return c - np.exp(a*x + b) 
    
c = 0.85 # when tau -> 1000 then eff_arr -> 0.85 
f_eff_arr = np.log(c - eff_arr) # create a temporary function

n=len(tau_arr)
B=numpy.array(f_eff_arr)
A=numpy.array(([[tau_arr[j], 1] for j in range(n)]))
X=numpy.linalg.lstsq(A,B)[0]
a=X[0]; b=X[1]
#print "Line is: y=",a,"x+",b

# Round the coefficients a, b
a = -1.24e-2
b = -0.11

print ""
print "The fit of the isoentropic efficiency in term 'c - exp(a*tau + b)' is " 
print "a = ", a, "; b = ", b, "; c = ", c
print ""


if True: # show or hide plot
    f_eff_arr_fit = a*tau_arr + b
    plt.plot(tau_arr, f_eff_arr, "-x")
    plt.plot(tau_arr, f_eff_arr_fit, "-o")
    plt.show()

    plt.plot(tau_arr, eff_arr, "-x")
    plt.plot(tau_arr, f_fit(tau_arr, a, b, c), "-o")
    plt.show
    
    
if False: #Plot the isenthropic efficiency of pumps (BMW and LLNL)
    tau_bmw_pump_arr = np.array([14.6361111111, 23.8582792208, 43.7614718615, 69.7800239234, 92.1720700986, 113.8622377622, 131.5602564103])
    p_out_bmw_pump_arr = tau_bmw_pump_arr * 2
    eff_bmw_pump_arr = np.array([0.5308768134, 0.6782333, 0.7810306597, 0.877752864, 0.8923481106, 0.9114939209, 0.9178579336])
    
    plt.plot(p_out_bmw_pump_arr, eff_bmw_pump_arr, "-o", label="BMW Pump")
    plt.plot(p_out_arr/1e5, eff_arr, "-o", label="LLNL Pump")
    plt.title('Isentropic efficiency of pumps')
    plt.legend()
    plt.xlabel('Outlet pressure [bar]')
    plt.ylabel('isentropic efficiency [-]')
    plt.show()



""" Find a fit in term '1 - 1/(a*tau + b)' of the isoentropic efficiency by tau """
"""
def f_fit1(x, a, b):
    return 1 - 1/(a*x + b)

degree = 2
f_eff_arr = 1/(1-eff_arr)
A = np.vander(tau_arr, degree)
(coeffs, residuals, rank, sing_vals) = np.linalg.lstsq(A, f_eff_arr)
a = coeffs[0]
b = coeffs[1]

print ""
print "The fit of the isoentropic efficiency in term '1 - 1/(a*tau + b)' is " 
print "a = ", a, "; b = ", b
print ""

if True: # show or hide plot
    poly_f_eff_arr = np.poly1d(coeffs)
    plt.plot(tau_arr, f_eff_arr, 'x-')
    plt.plot(tau_arr, poly_f_eff_arr(tau_arr), 'o-')
    plt.show()

    
    plt.plot(tau_arr, eff_arr, "-x")
    plt.plot(tau_arr, f_fit1(tau_arr, a, b), "-o")
    plt.show()
"""
