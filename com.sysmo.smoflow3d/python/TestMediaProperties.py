from Media import Medium, MediumState

f1 = Medium.create(Medium.sCompressibleFluidCoolProp, 'ParaHydrogen', 1)

p1 = MediumState(f1)

p1.update_Tp(288, 700e5)
print p1.rho()
print p1.cond()