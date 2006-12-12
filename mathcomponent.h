//
// Heccer : a compartmental solver that implements efficient Crank-Nicolson
// integration for neuronal models.
//

//////////////////////////////////////////////////////////////////////////////
//'
//' Heccer : testbed C implementation
//'
//' Copyright (C) 2006 Hugo Cornelis
//'
//' functional ideas ..	Hugo Cornelis, hugo.cornelis@gmail.com
//'
//' coding ............	Hugo Cornelis, hugo.cornelis@gmail.com
//'
//////////////////////////////////////////////////////////////////////////////


#ifndef MATHCOMPONENT_H
#define MATHCOMPONENT_H


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


#define MATH_TYPE_Compartment			1

#define MATH_TYPE_ChannelSpringMass		102
#define MATH_TYPE_Concen			103
#define MATH_TYPE_GHK				104
#define MATH_TYPE_MGBlocker			105
#define MATH_TYPE_Nernst			106
#define MATH_TYPE_SpikeGenerator		107
#define MATH_TYPE_TabulatedHHChannel		108

#define MATH_TYPE_CallOut_flag			0x8000

#define MATH_TYPE_CallOut_conductance		( 0x8000 | 2 )


#endif


