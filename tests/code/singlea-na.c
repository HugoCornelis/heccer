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


#include "../../compartment.h"
#include "../../heccer.h"


struct Compartment compSoma =
{
    //m administrative overhead

    {
	//m type of structure

	MATH_TYPE_Compartment,
    },

    //m index of parent compartment, -1 for none

    -1,

    //m first mechanism

    NULL,

    //m number of mechanisms

    0,

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


//v activation for a simple fast sodium channel

struct PoweredGateConcept pgcNaFActivation =
{
};

//v a simple fast sodium channel

struct ChannelActInact caiNaF =
{
    //m administrative overhead

    {
	//m type of structure

	MECHANISM_TYPE_ChannelActInact,
    },

    //m first set of descriptive values, alphabetical order

    //m reversal potential

    0.045,

    //m maximal conductance when all channels are permissive

    0.0002092393115,

    //m activation description

    {
	//m power, for a standard heccer, something between 1 and 4 or so.

	3,

	//m gate definition

	{
	    //m forward kinetiks, commonly denoted with alpha or non-perm to perm rate

	    {
		//m multiplier

		35.0,

		//m multiplier membrane dependence, DBL_MAX for no dependence

		DBL_MAX,

		//m choose between nominator or denominator, 1 means nominator, -1
		//m means denominator

		-1.0,

		//m nominator or denominator offset

		0.0,

		//m membrane offset

		-5.0,

		//m denormalized time constant

		-10.0,
	    },

	    //m backward kinetiks, commonly denoted with beta or perm to non-perm rate

	    {
		//m multiplier

		7.0,

		//m multiplier membrane dependence, DBL_MAX for no dependence

		DBL_MAX,

		//m choose between nominator or denominator, 1 means nominator, -1
		//m means denominator

		-1.0,

		//m nominator or denominator offset

		0.0,

		//m membrane offset

		-65.0,

		//m denormalized time constant

		20.0,
	    },
	},
    },

    //m inactivation description

    {
	//m power, for a standard heccer, something between 1 and 4 or so.

	1,

	//m gate definition

	{
	    //m forward kinetiks, commonly denoted with alpha or non-perm to perm rate

	    {
		//m multiplier

		0.225,

		//m multiplier membrane dependence, DBL_MAX for no dependence

		DBL_MAX,

		//m choose between nominator or denominator, 1 means nominator, -1
		//m means denominator

		-1.0,

		//m nominator or denominator offset

		1.0,

		//m membrane offset

		-80.0,

		//m denormalized time constant

		10.0,
	    },

	    //m backward kinetiks, commonly denoted with beta or perm to non-perm rate

	    {
		//m multiplier

		7.5,

		//m multiplier membrane dependence, DBL_MAX for no dependence

		DBL_MAX,

		//m choose between nominator or denominator, 1 means nominator, -1
		//m means denominator

		-1.0,

		//m nominator or denominator offset

		0.0,

		//m membrane offset

		3.0,

		//m denormalized time constant

		-18.0,
	    },
	},
    },
};


struct Intermediary inter =
{
    //m compartment array

    1,

    &compSoma,

    //m mechanism index

    0,

    NULL,

    //m mechanism data

    NULL,
};


#include "main.c"


