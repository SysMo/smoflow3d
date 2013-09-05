import os
import sys
import csv
import pylab as plt
from matplotlib import colors
from matplotlib.ticker import FormatStrFormatter
import matplotlib as mpl
import matplotlib.colorbar as CB
import numpy as np
import os

############ GasPak #############
#path_GasPak = "/data/SysMo/SoftwareLibs/PyFluid"
path_GasPak = r"F:\SysMo\SoftwareLibs\PyFluid"
#os.environ['PATH'] +=";" + path_GasPak
#print os.environ['PATH']
#dataPath_GasPak = os.path.join(path_GasPak, 'FluidData')
sys.path.append(path_GasPak)
from GaspakFluidState import GaspakFluidState
ph2_GasPak = GaspakFluidState('pH2', dataPath_GasPak)
nh2_GasPak = GaspakFluidState('nH2', dataPath_GasPak)
n2_GasPak = GaspakFluidState('nitrogen', dataPath_GasPak)

############ SmoFlow #############
from Media import Medium, MediumState
smo_ph2 = Medium.create(Medium.sCompressibleFluidCoolProp, 'ParaHydrogen', 1)
smo_nh2 = Medium.create(Medium.sCompressibleFluidCoolProp, 'Hydrogen', 2)
smo_n2 = Medium.create(Medium.sCompressibleFluidCoolProp, 'Nitrogen', 3)
ph2_SmoFlow = MediumState(smo_ph2)
nh2_SmoFlow = MediumState(smo_nh2)
n2_SmoFlow = MediumState(smo_n2)

class FluidData:
	def __init__(self, pData, TData):
		arrayShape = (len(pData), len(TData))	
		self.T, self.p = np.meshgrid(TData, pData) 
		self.rho = np.zeros(shape = arrayShape)
		self.h = np.zeros(shape = arrayShape)
		self.cp = np.zeros(shape = arrayShape)
		self.cv = np.zeros(shape = arrayShape)
		self.mu = np.zeros(shape = arrayShape)
		self.cond = np.zeros(shape = arrayShape)
		self.shape = arrayShape					
				
def computeGasPak(fdata, gpc):
	for row in range(fdata.shape[0]):
		for col in range(fdata.shape[1]):
			gpc.setState('P', fdata.p[row, col], 'T', fdata.T[row, col])
			fdata.rho[row, col] = gpc.density
			fdata.h[row, col] = gpc.enthalpy
			fdata.cp[row, col] = gpc.cp
			fdata.cv[row, col] = gpc.cv
			fdata.mu[row, col] = gpc.dynamicViscosity
			fdata.cond[row, col] = gpc.thermalConductivity

def computeSmoFlow(fdata, fluidState):
	for row in range(fdata.shape[0]):
		for col in range(fdata.shape[1]):
			fluidState.update_Tp(fdata.T[row, col], fdata.p[row, col])
			fdata.rho[row, col] = fluidState.rho() 
			fdata.h[row, col] = fluidState.h()
			fdata.cp[row, col] = fluidState.cp()
			fdata.cv[row, col] = fluidState.cv()
			fdata.mu[row, col] = fluidState.mu()
			fdata.cond[row, col] = fluidState.cond()
			
def comparativePlot_LineSeries(plotType, fluidDataList, lineStyles, compNames):
	fig, ax = plt.subplots(2, sharex = False)	
	ax[0].hold(True)
	#plt.rc('text', usetex=True)
	
	# Create property plot
	xValues = []
	yValues = []
	lines = []
	
	# Set up the colors for the lines
	#my_cmap = mpl.colors.LinearSegmentedColormap.from_list('mycolors',['blue','red'])
	#sm = plt.cm.ScalarMappable(cmap=my_cmap, norm=mpl.colors.LogNorm(vmin=10, vmax=1000))
	pressureColorMap = plt.cm.ScalarMappable(norm=mpl.colors.LogNorm(vmin=1, vmax=1000))
	pressureColorMap._A = []
	
	for fd, lineType, lineLabel in zip(fluidDataList, lineStyles, compNames):
		xValues.append(fd.T)
		yScale = 'log'
		if plotType == "p":
			yValues.append(fd.p)
			propName = "pressure"
			propUnit = "Pa"
		elif plotType == "rho":
			yValues.append(fd.rho)
			propName = "density"
			propUnit = "kg/m**3"
		elif plotType == "h":
			yValues.append(fd.h)
			propName = "specific enthalpy" 
			propUnit = "J/kg"
			yScale = 'linear'
		elif plotType == "cp":
			yValues.append(fd.cp)
			propName = "$c_p$"
			propUnit = "J/kg-K"
		elif plotType == "cv":
			yValues.append(fd.cv)
			propName = "$c_v$"
			propUnit = "J/kg-K"
		elif plotType == "mu":
			yValues.append(fd.mu)		  
			propName = "dynamic viscosity"
			propUnit = "Pa-s"
		elif plotType == "lambda":
			yValues.append(fd.cond)
			propName = "thermal conductivity"
			propUnit = "W/m**2-K"
		else:
			raise ValueError("Unknown property plot: " + plotType)
		
		yLabel = propName + ' [' + propUnit + ']'
		yMin = np.min(np.min(yValues[-1]))
		yMax = np.max(np.max(yValues[-1]))
		curves = []
 		for i in range(np.size(xValues[-1], 0)): 			
 			if (i != 0):
 				lineLabel = '_nolegend_'
 			colorVal = pressureColorMap.to_rgba(fd.p[i, 0]/1e5)
 			curves.append(ax[0].plot(xValues[-1][i], yValues[-1][i], lineType, color = colorVal, label = lineLabel))
		#ax[0].plot(yValues[-1].flat, lineType)
		ax[0].get_yaxis().set_label_text(yLabel)
		ax[0].set_yscale(yScale)
		ax[0].set_ylim([0.8 * yMin,1.2 * yMax])

	
	ax[0].get_xaxis().set_label_text("temperature [K]")
	ax[0].set_xscale('log')
	ax[0].set_xlim([TMin,TMax])
	ax[0].set_title("Comparison " + propName + " calculated by " + compNames[0] + " and " + compNames[1])
	ax[0].legend()
	
	cbar = fig.colorbar(pressureColorMap, ax = ax[0], ticks = [1.0, 10.0, 100.0, 1000.])
	cbar.ax.set_yticklabels(['1 bar', '10 bar', '100 bar', '1000 bar'])
	##########################################################################
	# Create error plot
	refFluid = fluidDataList[0]
	absErr = yValues[1] - yValues[0]
	relErr = np.abs(absErr / yValues[0])*100
	errLevels = np.array([0, 1e-2, 2e-2, 3e-2, 4e-2, 5e-2, 6e-2, 7e-2, 8e-2, 9e-2,
							 1e-1, 2e-1, 3e-1, 4e-1, 5e-1, 6e-1, 7e-1, 8e-1, 9e-1,
							 1e0, 2e0, 3e0, 4e0, 5e0, 6, 7, 8, 9, 10])
	errContours = ax[1].contourf(refFluid.T, refFluid.p/1e5, relErr, levels = errLevels, norm = colors.LogNorm())
	cbar = fig.colorbar(errContours, ax=ax[1], ticks = [1e-2, 1e-1, 1e-0, 1e1])
	cbar.ax.set_yticklabels(['0.01%', '0.1%', '1%', '10%'])
	
	
	ax[1].get_xaxis().set_label_text("temperature [K]")
	ax[1].get_yaxis().set_label_text("pressure [bar]")
	ax[1].set_xscale('log')
	ax[1].set_yscale('log')
	ax[1].set_ylim([1, 1000])
	ax[1].set_title("Relative error calculating " + propName + " by " + compNames[1] + " (refrenced to " + compNames[0] +")")

TMin = 120
TMax = 1300

pDef = np.array([1e5, 2e5, 5e5, 10e5, 20e5, 50e5, 100e5, 200e5, 500e5, 900e5])
TDef = np.logspace(np.log10(TMin), np.log10(TMax), 100)

fGP = FluidData(pDef, TDef)
fSM = FluidData(pDef, TDef)

#fGP.createArrays(pDef, TDef)
#fSM.createArrays(pDef, TDef)

computeGasPak(fGP, n2_GasPak)
computeSmoFlow(fSM, n2_SmoFlow)

#computeGasPak(fGP, n2_GasPak)
#computeCoolProp(fCP, "Nitrogen")

comparativePlot_LineSeries("lambda", [fGP, fSM], ["-", "."], ["GasPak", "SmoFlow3D"])
plt.show()

# rhoList = TList * 0
# muListGP = TList * 0
# muListSmo = TList * 0
# lambdaListGP = TList * 0
# lambdaListSmo = TList * 0
# 
# i = 0
# for T in TList:
#	 ph2_GasPak.setState('P', pVal, 'T', T)
#	 rhoList[i] = ph2_GasPak.density
#	 muListGP[i] = ph2_GasPak.dynamicViscosity
#	 muListSmo[i] = h2.viscosity(T, ph2_GasPak.density)
#	 lambdaListGP[i] = ph2_GasPak.thermalConductivity
#	 lambdaListSmo[i] = h2.thermalConductivity(T, ph2_GasPak.density)
#	 i += 1
# 
# # Statistics
# muMean = np.mean(muListGP)
# muErr = np.sqrt(np.sum((muListGP - muListSmo)**2) / np.size(muListGP))
# print ("muMean = %e, muErr = %e"%(muMean, muErr))
# 
# lambdaMean = np.mean(lambdaListGP)
# lambdaErr = np.sqrt(np.sum((lambdaListGP - lambdaListSmo)**2) / np.size(lambdaListGP))
# print ("lambdaMean = %e, lambdaErr = %e"%(lambdaMean, lambdaErr))
# 
# 
# import pylab as plt
# plt.hold(True)
# #plt.plot(TList, muListGP, label = 'GasPak')
# #plt.plot(TList, muListSmo, '.', label = 'CoolProp')
# plt.plot(TList, lambdaListGP, label = 'GasPak')
# plt.plot(TList, lambdaListSmo, '.', label = 'CoolProp')
# plt.legend()
# plt.show()
