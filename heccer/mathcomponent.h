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


#ifndef HECCER_MATHCOMPONENT_H
#define HECCER_MATHCOMPONENT_H


/*s a math component starts with ... */

struct MathComponent
{

    //m type of structure

    int iType;

#ifdef HECCER_SOURCE_NEUROSPACES

    //m identification

    int iSerial;

#endif

#ifdef HECCER_SIZED_MATH_STRUCTURES

    //m size of this structure

    int iSize;

#endif

};


#define MATH_TYPE_ChannelActConc 8
#define MATH_TYPE_ChannelActInact 7
#define MATH_TYPE_ChannelAct 13
#define MATH_TYPE_ChannelPersistentSteadyStateDualTau 12
#define MATH_TYPE_ChannelPersistentSteadyStateTau 11
#define MATH_TYPE_ChannelSpringMass 9
#define MATH_TYPE_ChannelSteadyStateSteppedTau 10
#define MATH_TYPE_Compartment 1
#define MATH_TYPE_ExponentialDecay 2
#define MATH_TYPE_GHK 3
#define MATH_TYPE_MGBlocker 4
#define MATH_TYPE_InternalNernst 5
#define MATH_TYPE_SpikeGenerator 6

#define MATH_TYPE_BasalActivator 20
#define MATH_TYPE_GateConcept 21


#define MATH_TYPE_CallOut_flag			0x8000

#define MATH_TYPE_CallOut_conductance_current	( 0x8000 | 2 )


struct MathComponentArray
{
    //m number of math components

    int iMathComponents;

    //m math component data

    struct MathComponent *pmc;

    //m math component index, initialize to NULL

    struct MathComponent **ppmcIndex;

    //m cursor for iterations

    int iCursor;

    struct MathComponent *pmcCursor;
};


struct MathComponentInfo
{
    int iType;

    int iChars;
};


int MathComponentArrayCallocData(struct MathComponentArray *pmca, int *iTypes);

/* int MathComponentArrayCursorInitialize(struct MathComponentArray *pmca); */

/* int MathComponentArrayCursorNext(struct MathComponentArray *pmca); */

#ifdef HECCER_SOURCE_NEUROSPACES

int
MathComponentArrayLookupSerial
(struct MathComponentArray *pmca, int iSerial);

#endif

int
MathComponentArraySetAdvance
(struct MathComponentArray *pmca, struct MathComponent *pmc);

struct MathComponent *
MathComponentCopyNext
(struct MathComponent *pmcTarget, struct MathComponent *pmcSource);

struct MathComponentInfo * MathComponentInfoLookup(int iType);

struct MathComponent *MathComponentNext(struct MathComponent *pmc);


#endif


