//
// Heccer : a compartmental solver that implements efficient Crank-Nicolson
// integration for neuronal models.
//

//////////////////////////////////////////////////////////////////////////////
//'
//' Heccer : testbed C implementation
//'
//' Copyright (C) 2006-2008 Hugo Cornelis
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
#include "table.h"


/// \struct spring mass parameters

struct SpringMassParameters
{
    /// first time constant

    double dTau1;

    /// second time constant

    double dTau2;
};

/// \struct spring mass channel (synaptic channel)

struct ChannelSpringMass
{
    /// administration overhead

    struct MathComponent mc;

    /// initial reversal potential

    double dReversalPotential;

    /// get reversal potential from this intermediary, -1 for none

    int iReversalPotential;

    /// maximal conductance

    double dMaximalConductance;

    /// contributes to this concentration pool, -1 for none, boolean indicator only.

    int iPool;

    /// random activation frequency

    double dFrequency;

    /// first exponential initial value

    double dInitX;

    /// second exponential initial value

    double dInitY;

    /// corresponding index in tables, set to -1 for initialization.

    int iTable;

    /// event time table (FLT_MAX terminated)

    double *pdEventTimes;

    /// yaml file with event time table, the previous must be NULL.

    /// \note during compilation, the file is converted to a double array
    /// \note and fills the previous entry.

    char *pcEventTimes;

    /// parameters

    struct SpringMassParameters parameters;
};


/// \struct expential decaying ion concentration

struct ExponentialDecay
{
    /// administration overhead

    struct MathComponent mc;

    /// initial value

    double dInitValue;

    /// beta

    double dBeta;

    /// steady state

    double dSteadyState;

    /// tau

    double dTau;

    /// external contribution delivered by these intermediaries

#define EXPONENTIALDECAY_CONTRIBUTORS 4

    int piExternal[EXPONENTIALDECAY_CONTRIBUTORS];
};


/* /// \struct GHK, not sure if correct, use at own risk */

/* struct GHK */
/* { */
/*     /// administration overhead */

/*     struct MathComponent mc; */

/*     double dCin; */
/*     double dCout; */
/*     double dT; */
/*     int iValency; */
/* }; */


/* /// \struct channel magnesium blocking */

/* struct MGBlocker */
/* { */
/*     /// administration overhead */

/*     struct MathComponent mc; */

/*     double dCMg; */
/*     double dKMg_A; */
/*     double dKMg_B; */
/* }; */


/// \struct nernst potential: constant

struct ConstantNernst
{
    /// administration overhead

    struct MathComponent mc;

    double dCin;
    double dConstant;
    double dCout;
};


/// \struct nernst potential: external variable

struct ExternalNernst
{
    /// administration overhead

    struct MathComponent mc;

    /// nernst constant

    double dConstant;

    /// constant internal concentration

    double dInternal;

    /// link to external concentration

    int iExternal;

    /// initial nernst potential

    double dInitPotential;
};


/// \struct nernst potential: internal variable

struct InternalNernst
{
    /// administration overhead

    struct MathComponent mc;

    /// nernst constant

    double dConstant;

    /// link to internal concentration

    int iInternal;

    /// constant external concentration

    double dExternal;

    /// initial nernst potential

    double dInitPotential;
};


/// \struct spike generator

struct SpikeGenerator
{
    /// administration overhead

    struct MathComponent mc;

    /// refractory time

    double dRefractory;

    /// spiking threshold

    double dThreshold;

    /// reset value, FLT_MAX for none

    double dReset;

    /// table in event distributor with targets

    int iTable;
};


/// \struct transition model for a gate concept

struct GateKinetic
{
    /// \note need parameters as follows:

    /// \note 1   A
    /// \note 2a  (ct1 * Vm                (factor is present or not, membrane dependence)
    /// \note 2b            - V0)          (membrane offset)
    /// \note 3   /                        (choose between division and multiplication)
    /// \note 4   (ct2 +
    /// \note 5    exp((Vm - V0)
    /// \note 6        / B))

    /// \note and relating, in YAML, to table 1 in EDS1994:

    /// \note 1: A, E
    /// \note 2: not done, always DBL_MAX
    /// \note 3: division
    /// \note 4: B, F
    /// \note 5: -C, -G
    /// \note 6: D, H

    /// 1: multiplier

    double dHHScale;

    /// 2a: multiplier membrane dependence, 0.0 for no dependence

    double dHHMult;

    /// 2b: multiplier membrane dependence offset, 0.0 for no dependence

    double dHHOffsetM;

    /// 3: choose between nominator or denominator, 1 means nominator, -1
    /// means denominator

    int iHHFactorFlag;

    /// 4: nominator or denominator offset

    double dHHAdd;

    /// 5: membrane offset

    double dHHOffsetE;

    /// 6: denormalized time constant

    double dHHTau;

};

/// \struct channel gate concept

struct GateConceptParameters
{
    /// forward kinetiks, commonly denoted with alpha or non-perm to perm rate

    struct GateKinetic gkA;

    /// backward kinetiks, commonly denoted with beta or perm to non-perm rate

    struct GateKinetic gkB;

};

struct GateConcept
{
    /// initial value, commonly forward over backward steady states

    double dInitActivation;

    /// corresponding index in tables, set to -1 for initialization.

    int iTable;

    /// or parameterized

    struct GateConceptParameters parameters;

    /// or using an external tables

    struct HeccerTabulatedGate htg;

};

/// \struct gate with a power

struct PoweredGateConcept
{
    /// power, for a standard heccer, something between 1 and 4 or so.

    /// \note you need more ?  Let me know, I will adapt the code (or check
    /// \note for yourself what needs to be done in the byte code emulator,
    /// \note not difficult to do, but let me know in any case).

    int iPower;

    /// gate definition

    struct GateConcept gc;
};

/// \struct HH alike channel, activation and inactivation

struct ChannelActInact
{
    /// administration overhead

    struct MathComponent mc;

    /// initial reversal potential

    double dReversalPotential;

    /// get reversal potential from this intermediary, -1 for none

    int iReversalPotential;

    /// maximal conductance when all channels are permissive

    double dMaximalConductance;

    /// contributes to this concentration pool, -1 for none, boolean indicator only.

    int iPool;

    /// activation description

    struct PoweredGateConcept pgcActivation;

    /// inactivation description

    struct PoweredGateConcept pgcInactivation;
};

/// \struct HH alike channel, only activation

struct ChannelAct
{
    /// administration overhead

    struct MathComponent mc;

    /// initial reversal potential

    double dReversalPotential;

    /// get reversal potential from this intermediary, -1 for none

    int iReversalPotential;

    /// maximal conductance when all channels are permissive

    double dMaximalConductance;

    /// contributes to this concentration pool, -1 for none, boolean indicator only.

    int iPool;

    /// activation description

    struct PoweredGateConcept pgc;

};

struct DualTauParameters
{
    /// fast component steady state

    double dSteadyState;

    /// tau

    struct dualtaucomponent
    {
	/// 1: nominator multiplier

	double dMultiplier;

	/// 2: denominator offset

	double dDeNominatorOffset;

	/// 5: membrane offset

	double dMembraneOffset;

	/// 6: denormalized time constant

	double dTauDenormalizer;

    } tau;

};

struct ChannelPersistentSteadyStateDualTau
{
    /// administrative overhead

    struct MathComponent mc;

    /// initial reversal potential

    double dReversalPotential;

    /// get reversal potential from this intermediary, -1 for none

    int iReversalPotential;

    /// maximal conductance when all channels are permissive

    double dMaximalConductance;

    /// contributes to this concentration pool, -1 for none, boolean indicator only.

    int iPool;

    /// first power

    int iFirstPower;

    /// second power

    int iSecondPower;

    /// first gate table, -1 for initialization

    int iFirstTable;

    /// second gate table, -1 for initialization

    int iSecondTable;

    /// first gate initial value

    double dFirstInitActivation;

    /// second gate initial value

    double dSecondInitActivation;

    struct DualTauParameters parameters1;

    struct DualTauParameters parameters2;

};

struct ChannelPersistentSteadyStateTau
{
    /// administrative overhead

    struct MathComponent mc;

    /// initial reversal potential

    double dReversalPotential;

    /// get reversal potential from this intermediary, -1 for none

    int iReversalPotential;

    /// maximal conductance when all channels are permissive

    double dMaximalConductance;

    /// contributes to this concentration pool, -1 for none, boolean indicator only.

    int iPool;

    /// power

    int iPower;

    /// gate table, -1 for initialization

    int iTable;

    /// gate initial value

    double dInitActivation;

    struct SteadyStateParameters
    {
	/// steady state definition

	struct single_steady_state
	{
	    /// 1: nominator

	    double dNominator;

	    /// 2: denominator multiplier 1

	    double dMultiplier1;

	    /// 5: membrane offset 1

	    double dMembraneOffset1;

	    /// 6: denormalized time constant 1

	    double dTauDenormalizer1;

	    /// 2: denominator multiplier 2

	    double dMultiplier2;

	    /// 5: membrane offset 2

	    double dMembraneOffset2;

	    /// 6: denormalized time constant 2

	    double dTauDenormalizer2;

	} ss;

	/// time constant definition

	struct single_time_constant
	{
	    /// 1: nominator

	    double dNominator;

	    /// 2: denominator offset

	    double dDeNominatorOffset;

	    /// 5: membrane offset 1

	    double dMembraneOffset;

	    /// 6: denormalized time constant 1

	    double dTauDenormalizer;

	} tc;

    } parameters;
};


/// \struct gate steady state definition

struct DualSteadyStateParameters
{
    /// first kinetiks

    struct dual_steadystate_kinetic
    {
	/// part a

	struct dual_steadystate_kinetic_part_a
	{
	    /// 1: multiplier
	
	    double dMultiplier;
	
	    /// 2: multiplier membrane dependence offset, 0.0 for no offset
	
	    double dMembraneDependenceOffset;
	
	    /// 4: nominator or denominator offset
	
	    double dDeNominatorOffset;
	
	    /// 5: membrane offset
	
	    double dMembraneOffset;
	
	    /// 6: denormalized time constant
	
	    double dTauDenormalizer;
	} a;

	/// part b

	struct dual_steadystate_kinetic_part_b
	{
	    /// 1: multiplier

	    double dMultiplier;

	    /// 2: multiplier membrane dependence, 0.0 for no dependence

	    double dTauDenormalizer;

	    /// 2: multiplier membrane dependence offset, 0.0 for no offset
	
	    double dMembraneDependenceOffset;
	
	} b;

    } first;

    /// second kinetiks

    struct dual_steadystate_kinetic second;
};

/// \struct gate time constant definition

struct SteppedTimeConstantParameters
{
    /// part a

    struct
    {
	/// threshold

	double dThreshold;

	/// low membrane potential target value

	double dLowTarget;

	/// above membrane potential target value

	double dHighTarget;

    } a;

    /// part b

    struct
    {
	/// 4: nominator or denominator offset

	double dDeNominatorOffset;

	/// 5: membrane offset

	double dMembraneOffset;

	/// 6: denormalized time constant

	double dTauDenormalizer;

    } b;
};

/// \struct HH alike channel, steady state and time constant

struct ChannelSteadyStateSteppedTau
{
    /// administration overhead

    struct MathComponent mc;

    /// initial reversal potential

    double dReversalPotential;

    /// get reversal potential from this intermediary, -1 for none

    int iReversalPotential;

    /// maximal conductance when all channels are permissive

    double dMaximalConductance;

    /// contributes to this concentration pool, -1 for none, boolean indicator only.

    int iPool;

    /// first power

    int iFirstPower;

    /// second power

    int iSecondPower;

    /// first table, -1 for initialization

    int iFirstTable;

    /// second table, -1 for initialization

    int iSecondTable;

    /// first initial value

    double dFirstInitActivation;

    /// second initial value

    double dSecondInitActivation;

    /// steady state definition

    struct DualSteadyStateParameters ss_parameters;

    /// time constant definition

    struct SteppedTimeConstantParameters tc_parameters;
};

/// \struct activator concept, mostly related to concentration pools

struct ActivatorParameters
{
    /// basal level, A in EDS1994

    double dBasalLevel;

    /// time constant, B in EDS1994

    double dTau;

};

struct ConcentrationActivator
{
    /// initial value, commonly steady state

    double dInitActivation;

    /// corresponding index in tables, set to -1 for initialization.

    int iTable;

    /// is activated by the output of this mechanism, must be filled in

    int iActivator;

    struct ActivatorParameters parameters;

    /// or using an external tables

    struct HeccerTabulatedGate htg;

};

/// \struct gate with a power

struct PoweredActivatorConcept
{
    /// power, for a standard heccer, something between 1 and 4 or so.

    int iPower;

    /// activator definition

    struct ConcentrationActivator ca;
};

/// \struct HH alike channel, activation and concentration dependent

struct ChannelActConc
{
    /// administration overhead

    struct MathComponent mc;

    /// initial reversal potential

    double dReversalPotential;

    /// get reversal potential from this intermediary, -1 for none

    int iReversalPotential;

    /// maximal conductance when all channels are permissive

    double dMaximalConductance;

    /// contributes to this concentration pool, -1 for none, boolean indicator only.

    int iPool;

    /// potential dependence description

    struct PoweredGateConcept pgc;

    /// activator dependence description

    struct PoweredActivatorConcept pac;
};


struct Heccer;



int HeccerMechanismCompile(struct Heccer *pheccer);

int HeccerMechanismIndex(struct Heccer *pheccer);

int HeccerMechanismLink(struct Heccer *pheccer);

int HeccerMechanismSolveCN(struct Heccer *pheccer);

int HeccerMechanismSort(struct Heccer *pheccer);


#endif


