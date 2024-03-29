cdef extern from "media/Medium.h":
	cdef cppclass Medium:
		pass
	ctypedef enum MediumConcreteTypes:
		sMediumAbstractType,
		sCompressibleFluidCoolProp,
		sIncompressibleLiquidCoolProp,
		sSolidThermal
	ctypedef enum PhaseSelection:
		PhaseSelection_Overall,
		PhaseSelection_Liquid,
		PhaseSelection_Gas,
		PhaseSelection_varDiscrete,
		PhaseSelection_varContinuous
	void Medium_register(MediumConcreteTypes mediumType, const char* mediumName, int mediumIndex) except +
	Medium* Medium_get(int mediumIndex) except +
	
cdef extern from "media/MediumState.h":
	cdef cppclass MediumState:
		void update_Tp(double T, double p)
		void update_Trho(double T, double rho)
		void update_prho(double p, double rho)
		void update_ph(double p, double h)
		void update_ps(double p, double s)
		void update_pq(double p, double q)
		void update_Tq(double T, double q)
		double T()
		double p()
		double rho()
		double h()
		double s()
		double u()
		double cp()
		double cv()
		double dpdt_v()
		double dpdv_t()
		double dpdrho_t()
		double dvdt_p()
		double beta()
		double mu()
		double Pr()
		double gamma()
		double R()

		# Two-phase related functions
		double q() #Gas mass fraction
		bint isSupercritical()
		bint isTwoPhase()
		double deltaTSat()
		double TSat()
		double dpdTSat()
		
	# Medium state condtructor function
	MediumState* MediumState_new(Medium* medium) except +
	# Workaround for thermal conductivity as lambda is reserved word on python
	double MediumState_lambda(MediumState* mstate)


