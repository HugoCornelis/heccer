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

#ifdef HECCER_SOURCE_NEUROSPACES

    //m identification

    int iSerial;

#endif

#ifdef HECCER_SIZED_MATH_STRUCTURES

    //m size of this structure

    int iSize;

#endif

    //m type of structure

    int iType;

};


#define MATH_TYPE_ChannelActConc 8
#define MATH_TYPE_ChannelActInact 7
#define MATH_TYPE_ChannelSpringMass 9
#define MATH_TYPE_Compartment 1
#define MATH_TYPE_ExponentialDecay 2
#define MATH_TYPE_GHK 3
#define MATH_TYPE_MGBlocker 4
#define MATH_TYPE_Nernst 5
#define MATH_TYPE_SpikeGenerator 6


#define MATH_TYPE_CallOut_flag			0x8000

#define MATH_TYPE_CallOut_conductance_current	( 0x8000 | 2 )


#endif


