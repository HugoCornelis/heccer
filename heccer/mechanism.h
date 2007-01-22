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


//s spring mass channel (synaptic channel)

#define MECHANISM_TYPE_ChannelSpringMass 1

struct ChannelSpringMass
{
    //m administration overhead

    struct MathComponent mc;

    //m descriptive values, alphabetical order

    double dEk;
    double dFrequency;
/*     double dNormalizer; */
    double dX;
    double dY;
};


//s expential decaying ion concentration

#define MECHANISM_TYPE_ExponentialDecay 2

struct ExponentialDecay
{
    //m administration overhead

    struct MathComponent mc;

    //m initial value

    double dInitValue;

    //m descriptive values, alphabetical order

    //m beta

    double dBeta;

    //m steady state

    double dSteadyState;

    //m tau

    double dTau;

    //m mechansims influenced by this component

    int piOthers[10];
};


//s GHK, not sure if correct, use at own risk

#define MECHANISM_TYPE_GHK 3

struct GHK
{
    //m administration overhead

    struct MathComponent mc;

    //m descriptive values, alphabetical order

    double dCin;
    double dCout;
    double dT;
    int iValency;
};


//s channel magnesium blocking

#define MECHANISM_TYPE_MGBlocker 4

struct MGBlocker
{
    //m administration overhead

    struct MathComponent mc;

    //m descriptive values, alphabetical order

    double dCMg;
    double dKMg_A;
    double dKMg_B;
};


//s variable channel nernst potential

#define MECHANISM_TYPE_Nernst 5

struct Nernst
{
    //m administration overhead

    struct MathComponent mc;

    //m descriptive values, alphabetical order

    double dCin;
    double dConstant;
    double dCout;
};


//s spike generator

#define MECHANISM_TYPE_SpikeGenerator 6

struct SpikeGenerator
{
    //m administration overhead

    struct MathComponent mc;

    //m descriptive values, alphabetical order

    double dRefract;
    double dThresh;
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

struct GateConcept
{
    //m initial value, commonly forward over backward steady states

    double dInitActivation;

    //m corresponding index in tables, set to -1 for initialization.

    int iTable;

    //m forward kinetiks, commonly denoted with alpha or non-perm to perm rate

    struct GateKinetic gkForward;

    //m backward kinetiks, commonly denoted with beta or perm to non-perm rate

    struct GateKinetic gkBackward;
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

#define MECHANISM_TYPE_ChannelActInact 7

struct ChannelActInact
{
    //m administration overhead

    struct MathComponent mc;

    //m first set of descriptive values, alphabetical order

    //m reversal potential

    double dReversalPotential;

    //m maximal conductance when all channels are permissive

    double dMaximalConductance;

    //m contributes to this concentration pool, -1 for none

    int iPool;

    //m activation description

    struct PoweredGateConcept pgcActivation;

    //m inactivation description

    struct PoweredGateConcept pgcInactivation;
};

//s activator concept, mostly related to concentration pools

struct Activator
{
    //m initial value, commonly steady state

    double dInitActivation;

    //m corresponding index in tables, set to -1 for initialization.

    int iTable;

    //m basal level, A in EDS1994

    double dBasalLevel;

    //m time constant, B in EDS1994

    double dTau;
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

#define MECHANISM_TYPE_ChannelActConc 8

struct ChannelActConc
{
    //m administration overhead

    struct MathComponent mc;

    //m first set of descriptive values, alphabetical order

    //m reversal potential

    double dReversalPotential;

    //m maximal conductance when all channels are permissive

    double dMaximalConductance;

    //m contributes to this concentration pool, -1 for none

    int iPool;

    //m potential dependence description

    struct PoweredGateConcept pgc;

    //m is activated by this mechanism (concentration pool), must be filled in

    int iActivator;

    //m activator dependence description

    struct PoweredActivatorConcept pac;
};


struct Heccer;


//d access a math component, and lookup the next component.

#define RETREIVE_MATH_COMPONENT(pmcSource,pmcTarget,math_type) ({ (pmcTarget) = math_type(pmcSource) ; (pmcSource) = (struct MathComponent *)&(pmcTarget)[1] ; })


//f prototypes

int HeccerMechanismBuildIndex(struct Heccer *pheccer);

int HeccerMechanismCompile(struct Heccer *pheccer);

int HeccerMechanismLink(struct Heccer *pheccer);

struct MathComponent *
HeccerMechanismLookup(struct Heccer *pheccer, int iMechanism);

int HeccerMechanismSolveCN(struct Heccer *pheccer);

int HeccerMechanismSort(struct Heccer *pheccer);


#endif


