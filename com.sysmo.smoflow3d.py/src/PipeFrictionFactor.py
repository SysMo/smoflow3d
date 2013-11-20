import numpy as np
import pylab as plt

""" Util - functions """
def myLogspace(start, stop, num):
    return np.logspace(np.log10(start), np.log10(stop), num)


""" Friction factor - functions """
def zetaLaminar(Re):
    return 64/Re;

def zetaTurbulentLow(Re):
    zeta = 0.3164 / Re**0.25
    return zeta

def zetaTurbulentMedium(Re):
    zeta = 0.0054 + 0.3964 / Re**0.3
    return zeta

def zetaPipeFlow(Re, d, e):
    zeta = 1.325 / (np.log(e / (3.7 * d) + 5.74 * Re**(-0.9)) )**2
    return zeta
    
def zetaSmoFlow(Re, d, e):
    zeta = zetaPipeFlow(Re, d, e)
    if (hasattr(Re, '__len__')):
        for i in range(len(Re)):
            if (Re[i] < 2300):
                zetaLam = 64 / Re[i]
                if (zetaLam > zeta[i]):
                    zeta[i] = zetaLam
    else:
        if (Re < 2300):
            zetaLam = 64 / Re
            if (zetaLam > zeta):
                zeta = zetaLam
    return zeta

def zetChurchill(Re, d, e):
    theta1 = (2.457 * np.log((7./Re)**0.9 + 0.27*e/d))**16
    theta2 = (37530./Re)**16
    zeta = 8 * ((8./Re)**12 + 1 / (theta1 + theta2)**1.5)**(1./12)
    return zeta


def ChurchilCorrelation(Re, d, epsilon):
        theta1 = np.power(2.457 * np.log(np.power(7.0 / Re, 0.9) + 0.27 * epsilon / d), 16)
        theta2 = np.power(37530.0 / Re, 16)
        zeta = 8 * np.power(np.power((8.0 / Re), 12) + 1 / np.power((theta1 + theta2), 1.5) , 1./12)

        return zeta

""" Compute - functions """
rho = 69
mu = 5e-6
def computePressureDrop(mDot, d, l, e):
    A = 3.14/4*d*d
    flowFactor = l / d
    v = mDot/(rho * A)
    Re = rho * v * d / mu
    dp = zetaSmoFlow(Re, d, e) * flowFactor * rho * v * v / 2;
    return dp

def computeMassFlowRate(dp, d, l, e):
    A = 3.14/4*d*d
    flowFactor = l / d
    numIter = dp * 0
    zeta = dp * 0
    v = dp * 0
    Re = 1e6
    maxNumIter = 20
    for i in range(len(dp)):
        err = 1
        while (np.abs(err) > 1e-10 and numIter[i] < maxNumIter):
            zeta[i] = zetaPipeFlow(Re, d, e)
            v[i] = np.sqrt(2 * dp[i] / (rho * zeta[i] * flowFactor))
            Re = rho * v[i] * d / mu
            dpCalc = computePressureDrop(rho * v[i] * A, d, l, e)
            err = (dpCalc - dp[i])/dp[i]
            numIter[i] += 1
    mdot = rho * v * A
    return numIter, mdot
    

""" Plot - functions """
def comparativePlot():
    e = 0.025
    d= 10

    ReL = myLogspace(100, 2300, 1000)
    ReTL = myLogspace(3000, 100000, 1000)
    ReTM = myLogspace(2e4, 2e6, 1000)
    RePF = myLogspace(1e2, 1e7, 1000)
    ReChurchil = myLogspace(1e2, 1e7, 1000)
    
    plt.hold(True)
    #plt.plot(ReL, zetaLaminar(ReL), label='ReL')
    #plt.plot(ReTL, zetaTurbulentLow(ReTL), label='ReTL')
    #plt.plot(ReTM, zetaTurbulentMedium(ReTM), label = 'ReTM')
    #plt.plot(RePF, zetaPipeFlow(RePF, d, e), label = 'RePF - PipeFlow')
    plt.plot(RePF, zetaSmoFlow(RePF, d, e), label = 'RePF - SmoFlow')
    plt.plot(ReChurchil, zetChurchill(ReChurchil, d, e), label = 'Re - Churchill')
    plt.plot(ReChurchil, ChurchilCorrelation(ReChurchil, d, e), label = 'Re - Churchill')
    plt.legend()    
    
    plt.xscale('log')
    plt.xlabel('log (Re)')
    plt.yscale('log')
    plt.ylabel('Friction factor')
    
    plt.show()

def plotPressureDrop():
    e = 0.025e-3
    d= 5e-3
    l = 2.0
    mDot = myLogspace(1., 1000., 100)
    dp = computePressureDrop(mDot / 3600., d, l, e)
    numIter, mDotCalc = computeMassFlowRate(dp, d, l, e)
    mDotCalc *= 3600
    

    #plt.plot(mDot, dp/1e5)
    #plt.plot(mDotCalc, dp/1e5)
    #plt.xscale('log')
    #plt.yscale('log')

    plt.subplot(2, 1, 1)

    relErr = np.abs(mDotCalc - mDot)/mDot
    plt.hold(True)
    plt.plot(dp/1e5, relErr, '*')
    plt.xscale('log')
    plt.yscale('log')

    plt.subplot(2, 1, 2)
    plt.plot(dp/1e5, numIter)
    plt.xscale('log')

    plt.show()
    
    
      
# Execute main function
if __name__ == "__main__":    
    comparativePlot()
    #plotPressureDrop()   