//
// Heccer : a compartmental solver that implements efficient Crank-Nicolson
// integration for neuronal models.
//

//////////////////////////////////////////////////////////////////////////////
//'
//' Heccer : testbed C implementation
//'
//' Copyright (C) 2006-2007 Hugo Cornelis
//'
//' functional ideas ..	Hugo Cornelis, hugo.cornelis@gmail.com
//'
//' coding ............	Hugo Cornelis, hugo.cornelis@gmail.com
//'
//////////////////////////////////////////////////////////////////////////////


#ifndef MECHANISM_H
#define MECHANISM_H


#include <float.h>

#include "mathcomponent.h"


//s spring mass parameters

struct SpringMassParameters
{
    //m first time constant

    double dTau1;

    //m second time constant

    double dTau2;
};

//s spring mass channel (synaptic channel)

struct ChannelSpringMass
{
    //m administration overhead

    struct MathComponent mc;

    //m initial reversal potential

    double dReversalPotential;

    //m get reversal potential from this intermediary, -1 for none

    int iReversalPotential;

    //m maximal conductance

    double dMaximalConductance;

    //m contributes to this concentration pool, -1 for none, boolean indicator only.

    int iPool;

    //m random activation frequency

    double dFrequency;

    //m first exponential initial value

    double dInitX;

    //m second exponential initial value

    double dInitY;

    //m corresponding index in tables, set to -1 for initialization.

    int iTable;

    //m event time table (FLT_MAX terminated)

    double *pdEventTimes;

    //m yaml file with event time table, the previous must be NULL.

    //! during compilation, the file is converted to a double array
    //! and fills the previous entry.

    char *pcEventTimes;

    //m parameters

    struct SpringMassParameters parameters;
};


//s expential decaying ion concentration

struct ExponentialDecay
{
    //m administration overhead

    struct MathComponent mc;

    //m initial value

    double dInitValue;

    //m beta

    double dBeta;

    //m steady state

    double dSteadyState;

    //m tau

    double dTau;

    //m external contribution delivered by these intermediaries

#define EXPONENTIALDECAY_CONTRIBUTORS 4

    int piExternal[EXPONENTIALDECAY_CONTRIBUTORS];
};


/* //s GHK, not sure if correct, use at own risk */

/* struct GHK */
/* { */
/*     //m administration overhead */

/*     struct MathComponent mc; */

/*     double dCin; */
/*     double dCout; */
/*     double dT; */
/*     int iValency; */
/* }; */


/* //s channel magnesium blocking */

/* struct MGBlocker */
/* { */
/*     //m administration overhead */

/*     struct MathComponent mc; */

/*     double dCMg; */
/*     double dKMg_A; */
/*     double dKMg_B; */
/* }; */


//s nernst potential: constant

struct ConstantNernst
{
    //m administration overhead

    struct MathComponent mc;

    double dCin;
    double dConstant;
    double dCout;
};


//s nernst potential: external variable

struct ExternalNernst
{
    //m administration overhead

    struct MathComponent mc;

    //m nernst constant

    double dConstant;

    //m constant internal concentration

    double dInternal;

    //m link to external concentration

    int iExternal;

    //m initial nernst potential

    double dInitPotential;
};


//s nernst potential: internal variable

struct InternalNernst
{
    //m administration overhead

    struct MathComponent mc;

    //m nernst constant

    double dConstant;

    //m link to internal concentration

    int iInternal;

    //m constant external concentration

    double dExternal;

    //m initial nernst potential

    double dInitPotential;
};


//s spike generator

struct SpikeGenerator
{
    //m administration overhead

    struct MathComponent mc;

    //m refractory time

    double dRefractory;

    //m spiking threshold

    double dThreshold;

    //m reset value, FLT_MAX for none

    double dReset;

    //m table in event distributor with targets

    int iTable;
};


//s transition model for a gate concept

struct GateKinetic
{
    //! need parameters as follows:

    //! 1   A
    //! 2   (Vm - V0)          (factor is present or not, membrane dependence)
    //! 3   /                  (choose between division and multiplication)
    //! 4   (cte +
    //! 5    exp((Vm - V0)
    //! 6        / B))

    //! and relating, in YAML, to table 1 in EDS1994:

    //! 1: A, E
    //! 2: not done, always DBL_MAX
    //! 3: division
    //! 4: B, F
    //! 5: -C, -G
    //! 6: D, H

    //m 1: multiplier

    double dMultiplier;

    //m 2: multiplier membrane dependence, 0.0 for no dependence

    double dMembraneDependence;

    //m 3: choose between nominator or denominator, 1 means nominator, -1
    //m means denominator

    int iNominator;

    //m 4: nominator or denominator offset

    double dDeNominatorOffset;

    //m 5: membrane offset

    double dMembraneOffset;

    //m 6: denormalized time constant

    double dTauDenormalizer;
};

//s channel gate concept

struct GateConceptParameters
{
    //m forward kinetiks, commonly denoted with alpha or non-perm to perm rate

    struct GateKinetic gkForward;

    //m backward kinetiks, commonly denoted with beta or perm to non-perm rate

    struct GateKinetic gkBackward;

};

struct GateConcept
{
    //m initial value, commonly forward over backward steady states

    double dInitActivation;

    //m corresponding index in tables, set to -1 for initialization.

    int iTable;

    struct GateConceptParameters parameters;
};

//s gate with a power

struct PoweredGateConcept
{
    //m power, for a standard heccer, something between 1 and 4 or so.

    //! you need more ?  Let me know, I will adapt the code (or check
    //! for yourself what needs to be done in the byte code emulator,
    //! not difficult to do, but let me know in any case).

    int iPower;

    //m gate definition

    struct GateConcept gc;
};

//s HH alike channel, activation and inactivation

struct ChannelActInact
{
    //m administration overhead

    struct MathComponent mc;

    //m initial reversal potential

    double dReversalPotential;

    //m get reversal potential from this intermediary, -1 for none

    int iReversalPotential;

    //m maximal conductance when all channels are permissive

    double dMaximalConductance;

    //m contributes to this concentration pool, -1 for none, boolean indicator only.

    int iPool;

    //m activation description

    struct PoweredGateConcept pgcActivation;

    //m inactivation description

    struct PoweredGateConcept pgcInactivation;
};

//s HH alike channel, only activation

struct ChannelAct
{
    //m administration overhead

    struct MathComponent mc;

    //m initial reversal potential

    double dReversalPotential;

    //m get reversal potential from this intermediary, -1 for none

    int iReversalPotential;

    //m maximal conductance when all channels are permissive

    double dMaximalConductance;

    //m contributes to this concentration pool, -1 for none, boolean indicator only.

    int iPool;

    //m activation description

    struct PoweredGateConcept pgc;

};

struct DualTauParameters
{
    //m fast component steady state

    double dSteadyState;

    //m tau

    struct dualtaucomponent
    {
	//m 1: nominator multiplier

	double dMultiplier;

	//m 2: denominator offset

	double dDeNominatorOffset;

	//m 5: membrane offset

	double dMembraneOffset;

	//m 6: denormalized time constant

	double dTauDenormalizer;

    } tau;

};

struct ChannelPersistentSteadyStateDualTau
{
    //m administrative overhead

    struct MathComponent mc;

    //m initial reversal potential

    double dReversalPotential;

    //m get reversal potential from this intermediary, -1 for none

    int iReversalPotential;

    //m maximal conductance when all channels are permissive

    double dMaximalConductance;

    //m contributes to this concentration pool, -1 for none, boolean indicator only.

    int iPool;

    //m first power

    int iFirstPower;

    //m second power

    int iSecondPower;

    //m first gate table, -1 for initialization

    int iFirstTable;

    //m second gate table, -1 for initialization

    int iSecondTable;

    //m first gate initial value

    double dFirstInitActivation;

    //m second gate initial value

    double dSecondInitActivation;

    struct DualTauParameters parameters1;

    struct DualTauParameters parameters2;

};

struct ChannelPersistentSteadyStateTau
{
    //m administrative overhead

    struct MathComponent mc;

    //m initial reversal potential

    double dReversalPotential;

    //m get reversal potential from this intermediary, -1 for none

    int iReversalPotential;

    //m maximal conductance when all channels are permissive

    double dMaximalConductance;

    //m contributes to this concentration pool, -1 for none, boolean indicator only.

    int iPool;

    //m power

    int iPower;

    //m gate table, -1 for initialization

    int iTable;

    //m gate initial value

    double dInitActivation;

    struct SteadyStateParameters
    {
	//m steady state definition

	struct single_steady_state
	{
	    //m 1: nominator

	    double dNominator;

	    //m 2: denominator multiplier 1

	    double dMultiplier1;

	    //m 5: membrane offset 1

	    double dMembraneOffset1;

	    //m 6: denormalized time constant 1

	    double dTauDenormalizer1;

	    //m 2: denominator multiplier 2

	    double dMultiplier2;

	    //m 5: membrane offset 2

	    double dMembraneOffset2;

	    //m 6: denormalized time constant 2

	    double dTauDenormalizer2;

	} ss;

	//m time constant definition

	struct single_time_constant
	{
	    //m 1: nominator

	    double dNominator;

	    //m 2: denominator offset

	    double dDeNominatorOffset;

	    //m 5: membrane offset 1

	    double dMembraneOffset;

	    //m 6: denormalized time constant 1

	    double dTauDenormalizer;

	} tc;

    } parameters;
};


//s gate steady state definition

struct DualSteadyStateParameters
{
    //m first kinetiks

    struct dual_steadystate_kinetic
    {
	//m part a

	struct dual_steadystate_kinetic_part_a
	{
	    //m 1: multiplier
	
	    double dMultiplier;
	
	    //m 2: multiplier membrane dependence offset, 0.0 for no offset
	
	    double dMembraneDependenceOffset;
	
	    //m 4: nominator or denominator offset
	
	    double dDeNominatorOffset;
	
	    //m 5: membrane offset
	
	    double dMembraneOffset;
	
	    //m 6: denormalized time constant
	
	    double dTauDenormalizer;
	} a;

	//m part b

	struct dual_steadystate_kinetic_part_b
	{
	    //m 1: multiplier

	    double dMultiplier;

	    //m 2: multiplier membrane dependence, 0.0 for no dependence

	    double dTauDenormalizer;

	    //m 2: multiplier membrane dependence offset, 0.0 for no offset
	
	    double dMembraneDependenceOffset;
	
	} b;

    } first;

    //m second kinetiks

    struct dual_steadystate_kinetic second;
};

//s gate time constant definition

struct SteppedTimeConstantParameters
{
    //m part a

    struct
    {
	//m threshold

	double dThreshold;

	//m low membrane potential target value

	double dLowTarget;

	//m above membrane potential target value

	double dHighTarget;

    } a;

    //m part b

    struct
    {
	//m 4: nominator or denominator offset

	double dDeNominatorOffset;

	//m 5: membrane offset

	double dMembraneOffset;

	//m 6: denormalized time constant

	double dTauDenormalizer;

    } b;
};

//s HH alike channel, steady state and time constant

struct ChannelSteadyStateSteppedTau
{
    //m administration overhead

    struct MathComponent mc;

    //m initial reversal potential

    double dReversalPotential;

    //m get reversal potential from this intermediary, -1 for none

    int iReversalPotential;

    //m maximal conductance when all channels are permissive

    double dMaximalConductance;

    //m contributes to this concentration pool, -1 for none, boolean indicator only.

    int iPool;

    //m first power

    int iFirstPower;

    //m second power

    int iSecondPower;

    //m first table, -1 for initialization

    int iFirstTable;

    //m second table, -1 for initialization

    int iSecondTable;

    //m first initial value

    double dFirstInitActivation;

    //m second initial value

    double dSecondInitActivation;

    //m steady state definition

    struct DualSteadyStateParameters ss_parameters;

    //m time constant definition

    struct SteppedTimeConstantParameters tc_parameters;
};

//s activator concept, mostly related to concentration pools

struct ActivatorParameters
{
    //m basal level, A in EDS1994

    double dBasalLevel;

    //m time constant, B in EDS1994

    double dTau;

};

struct Activator
{
    //m initial value, commonly steady state

    double dInitActivation;

    //m corresponding index in tables, set to -1 for initialization.

    int iTable;

    //m is activated by the output of this mechanism, must be filled in

    int iActivator;

    struct ActivatorParameters parameters;
};

//s gate with a power

struct PoweredActivatorConcept
{
    //m power, for a standard heccer, something between 1 and 4 or so.

    int iPower;

    //m activator definition

    struct Activator ac;
};

//s HH alike channel, activation and concentration dependent

struct ChannelActConc
{
    //m administration overhead

    struct MathComponent mc;

    //m initial reversal potential

    double dReversalPotential;

    //m get reversal potential from this intermediary, -1 for none

    int iReversalPotential;

    //m maximal conductance when all channels are permissive

    double dMaximalConductance;

    //m contributes to this concentration pool, -1 for none, boolean indicator only.

    int iPool;

    //m potential dependence description

    struct PoweredGateConcept pgc;

    //m activator dependence description

    struct PoweredActivatorConcept pac;
};


struct Heccer;


//f prototypes

int HeccerMechanismCompile(struct Heccer *pheccer);

int HeccerMechanismLink(struct Heccer *pheccer);

int HeccerMechanismSolveCN(struct Heccer *pheccer);

int HeccerMechanismSort(struct Heccer *pheccer);


#endif


