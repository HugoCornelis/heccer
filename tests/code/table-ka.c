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


#define HECCER_TEST_INTERVAL_DEFAULT_START			(-0.1)
#define HECCER_TEST_INTERVAL_DEFAULT_END			(0.05)
#define HECCER_TEST_INTERVAL_DEFAULT_ENTRIES			50
#define HECCER_TEST_STEPS 1


struct Compartment compSoma =
{
    //m administrative overhead

    {
	//m type of structure

	MATH_TYPE_Compartment,
    },

    //m index of parent compartment, -1 for none

    -1,

/*     //m first mechanism */

/*     NULL, */

/*     //m number of mechanisms */

/*     0, */

    //m descriptive values, alphabetical order

/*     double dCm; */

    4.57537e-11, // unscaled 0.0164,

/*     double dEm; */

    -0.08,

/*     double dInitVm; */

    -0.068,

/*     double dInject;		 */

    0,

/*     double dRa; */

    360502, // unscaled 2.5,

/*     double dRm; */

    3.58441e+08, // unscaled 1
};


//v a simple fast sodium channel

struct ChannelActInact caiKA =
{
    //m administrative overhead

    {
	//m type of structure

	MECHANISM_TYPE_ChannelActInact,
    },

    //m first set of descriptive values, alphabetical order

    //m reversal potential

    -0.085,

    //m maximal conductance when all channels are permissive

    4.184786349e-07,

    //m contributes to this concentration pool, -1 for none

    -1,

    //m activation description

    {
	//m power, for a standard heccer, something between 1 and 4 or so.

	4,

	//m gate definition

	{
	    //m initial value, commonly forward over backward steady states

	    0.0,

	    //m corresponding index in tables, set to -1 for initialization.

	    -1,

	    //m forward kinetiks, commonly denoted with alpha or non-perm to perm rate

	    {
		//m multiplier

		1.40e3,

		//m multiplier membrane dependence, 0.0 for no dependence

		0.0,

		//m choose between nominator or denominator, 1 means nominator, -1
		//m means denominator

		-1.0,

		//m nominator or denominator offset

		1.0,

		//m membrane offset

		0.027,

		//m denormalized time constant

		-12.0e-3,
	    },

	    //m backward kinetiks, commonly denoted with beta or perm to non-perm rate

	    {
		//m multiplier

		0.49e3,

		//m multiplier membrane dependence, 0.0 for no dependence

		0.0,

		//m choose between nominator or denominator, 1 means nominator, -1
		//m means denominator

		-1.0,

		//m nominator or denominator offset

		1.0,

		//m membrane offset

		30.0e-3,

		//m denormalized time constant

		4.0e-3,
	    },
	},
    },

    //m inactivation description

    {
	//m power, for a standard heccer, something between 1 and 4 or so.

	1,

	//m gate definition

	{
	    //m initial value, commonly forward over backward steady states

	    0.0,

	    //m corresponding index in tables, set to -1 for initialization.

	    -1,

	    //m forward kinetiks, commonly denoted with alpha or non-perm to perm rate

	    {
		//m multiplier

		0.0175e3,

		//m multiplier membrane dependence, 0.0 for no dependence

		0.0,

		//m choose between nominator or denominator, 1 means nominator, -1
		//m means denominator

		-1.0,

		//m nominator or denominator offset

		1.0,

		//m membrane offset

		50.0e-3,

		//m denormalized time constant

		8.0e-3,
	    },

	    //m backward kinetiks, commonly denoted with beta or perm to non-perm rate

	    {
		//m multiplier

		1.3e3,

		//m multiplier membrane dependence, 0.0 for no dependence

		0.0,

		//m choose between nominator or denominator, 1 means nominator, -1
		//m means denominator

		-1.0,

		//m nominator or denominator offset

		1.0,

		//m membrane offset

		13.0e-3,

		//m denormalized time constant

		-10.0e-3,
	    },
	},
    },
};


int piC2m[] =
{
    1,
    -1,
};


struct Intermediary inter =
{
    //m compartment array

    1,

    &compSoma,

    //m number of mechanisms

    1,

    //m mechanism data

    &caiKA,

    //m mechanism index, initialize to NULL

    NULL,

    //m compartment 2 first mechanism number

    piC2m,
};


#include "main.c"


