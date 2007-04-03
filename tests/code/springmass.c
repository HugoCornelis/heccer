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


#include "../../heccer/compartment.h"
#include "../../heccer/heccer.h"


#define HECCER_TEST_REPORTING_GRANULARITY 10
#define HECCER_TEST_STEPS 100


struct Compartment pcomp[] =
{
    {
	//m administrative overhead

	{
	    //m type of structure

	    MATH_TYPE_Compartment,
	},

	//m index of parent compartment, -1 for none

	-1,

	//m descriptive values, alphabetical order

/*     double dCm; */

	4.57537e-11, // unscaled 0.0164,

/*     double dEm; */

	-0.08,

/*     double dInitVm; */

	-0.08,

/*     double dInject;		 */

	0,

/*     double dRa; */

	360502, // unscaled 2.5,

/*     double dRm; */

	3.58441e+08, // unscaled 1
    },

    {
	//m administrative overhead

	{
	    //m type of structure

	    MATH_TYPE_Compartment,
	},

	//m index of parent compartment, -1 for none

	0,

	//m descriptive values, alphabetical order

/*     double dCm; */

	5.755329373e-12, // unscaled 0.0164,

/*     double dEm; */

	-0.08,

/*     double dInitVm; */

	-0.08,

/*     double dInject;		 */

	0,

/*     double dRa; */

	772813.4375, // unscaled 2.5,

/*     double dRm; */

	8.548598272e9, // unscaled 3
    },
};


double pdEvents[] =
{
    0.0001,
    FLT_MAX,
};


//s spring mass channel (synaptic channel)

struct ChannelSpringMass csm =
{
    //m administrative overhead

    {
	//m type of structure

	MATH_TYPE_ChannelSpringMass,
    },

    //m initial reversal potential

    0.0,

    //m get reversal potential from this intermediary, -1 for none

    -1,

    //m maximal conductance

    6.87071723162637e-10,

    //m contributes to this concentration pool, -1 for none, boolean indicator only.

    -1,

    //m random activation frequency

    0.0,

    //m first exponential initial value

    0.0,

    //m second exponential initial value

    0.0,

    //m corresponding index in tables, set to -1 for initialization.

    -1,

    //m event time table (FLT_MAX terminated)

    pdEvents,

    //m parameters

    {
	//m first time constant

	5e-4,

	//m second time constant

	1.2e-3,
    },

};


int piC2m[] =
{
    0,
    1,
    -1,
};


struct MathComponentArray mca =
{
    //m number of math components

    1,

    //m math component data

    &csm.mc,

    //m math component index, initialize to NULL

    NULL,

};


struct Intermediary inter =
{
    //m compartment array

    2,

    pcomp,

    //m all other mathematical components

    &mca,

    //m compartment 2 first mechanism number

    piC2m,
};


#include "main.c"


