Refprop
=======

Parahydrogen
------------
#TCX               !thermal conductivity model specification
TC0  pure fluid thermal conductivity model of McCarty and Weber (1972).
?LITERATURE REFERENCE \
?McCarty, R.D. and Weber, L.A.,
? "Thermophysical properties of parahydrogen from the freezing liquid line to
? 5000 R for pressures to 10,000 psia,"
? Natl. Bur. Stand., Tech. Note 617, 1972.

#ETA               !viscosity model specification
VS0  pure fluid viscosity model of McCarty and Weber (1972).
?LITERATURE REFERENCE \
?McCarty, R.D. and Weber, L.A.,
? "Thermophysical properties of parahydrogen from the freezing liquid line to
? 5000 R for pressures to 10,000 psia,"
? Natl. Bur. Stand., Tech. Note 617, 1972.

Normal Hydrogen
---------------
#TCX               !thermal conductivity model specification
TC0  pure fluid thermal conductivity model of McCarty and Weber (1972).
?LITERATURE REFERENCE \
?McCarty, R.D. and Weber, L.A.,
? "Thermophysical properties of parahydrogen from the freezing liquid line to
? 5000 R for pressures to 10,000 psia,"
? Natl. Bur. Stand., Tech. Note 617, 1972.

#ETA               !viscosity model specification
VS0  pure fluid viscosity model of McCarty and Weber (1972).
?LITERATURE REFERENCE \
?McCarty, R.D. and Weber, L.A.,
? "Thermophysical properties of parahydrogen from the freezing liquid line to
? 5000 R for pressures to 10,000 psia,"
? Natl. Bur. Stand., Tech. Note 617, 1972.


GasPak
======

IDX Coeff:
    7    1    2    2
   10   -4   40    1
    1    1    0    0

Model
-----
IF (IDX(8) .EQ. 0) THEN
   PROP(21) = 0.
ELSE IF (IDX(2).EQ.2) THEN
   PROP(21) = 1.D-06*VISCW1 (DML,T)
ELSE 
   DGC=DML*GMW/1000.D0
   IF((IDX(4).EQ.2 .OR. IDX(4).EQ.4) .AND. T.GE.TUP) THEN
      CALL VISDIS (PROP, T, DGC)
   ELSE
      PROP(21) = 1.D-06*(DILVIS(T) + VFDC(DGC,T) + EXCSV(DGC,T))
   ENDIF
ENDIF
 
 mu = 1e-6*(DILVIS(T) + VFDC(DGC,T) + EXCSV(DGC,T))
 mu [uPa-s], T[K], D[gm/cm^3]
 
 
 
 
DILVIS(T)
~~~~~~~~~
Dilute gas viscosity [microPa-s] for NW=0 fluids
Coefficients: GV()

SUM=0.0D0
TF  = T**(1.D0/3.D0)
TFF = TF**(-4)
DO 10 I=1,9
TFF = TFF*TF
SUM = SUM + GV(I)*TFF
DILVIS=SUM

 
 
VFDC(DGC,T)
~~~~~~~~~~~
First density correction for viscosity [microPa-s] of NW=0 fluids, density D [gm/cm3]
Coefficients: FV()

VFDC = (FV(1)+FV(2)*(FV(3)-DLOG(T/FV(4)))**2) *D
 
EXCSV(DGC,T)
~~~~~~~~~~~~
Calculates excess viscosity [microPa-s] for NW=0 fluids, density D [gm/cm3]

R2 = SQRT(D) * ((D-EV(8))/EV(8))
R  = D**(.1D0)
X  = EV(1) + EV(2)*R2 + EV(3)*R + (EV(4)*R2/T + EV(5)*R/SQRT(T)
A     +EV(6) + EV(7)*R2) /T
X1 = EV(1)+EV(6)/T
EXCSV = DEXP(X)- DEXP(X1)

 
Parahydrogen
------------
Transport properties from Roder, H. M.,NBSIR 84-3006
"(1984) and Roder et al NBS Monograph 24.
ah
Normal hydrogen
---------------
Unpublished source

AMESim
======

CoolProp
========

Parahydrogen
------------

Normal hydrogen
---------------
Viscosity: Muzny, JCED, 2013
Conductivity: Assael, JPCRD, 2011
