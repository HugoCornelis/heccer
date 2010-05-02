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


#include "../../heccer/compartment.h"
#include "../../heccer/heccer.h"


#define HECCER_TEST_INTERPOL_INTERVAL_DEFAULT_ENTRIES		20
#define HECCER_TEST_INTERVAL_DEFAULT_START			(-0.1)
#define HECCER_TEST_INTERVAL_DEFAULT_END			(0.05)
#define HECCER_TEST_INTERVAL_DEFAULT_ENTRIES			50
#define HECCER_TEST_STEPS 1
#define HECCER_TEST_TESTED_THINGS (HECCER_DUMP_ALL_EXTENDED)


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
    },

    {
	//m administrative overhead

	{
	    //m type of structure

	    MATH_TYPE_Compartment,
	},

	//m index of parent compartment, -1 for none

	0,

/* 	//m first mechanism */

/* 	NULL, */

/* 	//m number of mechanisms */

/* 	0, */

	//m descriptive values, alphabetical order

/*     double dCm; */

	5.755329373e-12, // unscaled 0.0164,

/*     double dEm; */

	-0.08,

/*     double dInitVm; */

	-0.068,

/*     double dInject;		 */

	0,

/*     double dRa; */

	772813.4375, // unscaled 2.5,

/*     double dRm; */

	8.548598272e9, // unscaled 3
    },
};


//v a muscarinic potassium channel

struct ChannelPersistentSteadyStateTau pcsstKM[] =
{
    {
	//m administrative overhead

	{
	    //m type of structure

	    MATH_TYPE_ChannelPersistentSteadyStateTau,
	},

	//m first set of descriptive values, alphabetical order

	//m initial reversal potential

	-0.085,

	//m get reversal potential from this intermediary, -1 for none

	-1,

	//m maximal conductance when all channels are permissive

	1.115943116e-09,

	//m contributes to this concentration pool, -1 for none, boolean indicator only.

	-1,

	//m power

	1,

	//m gate table, -1 for initialization

	-1,

	//m gate initial value

	0.03540844397,

	{
	    //m steady state definition

	    {
		//m 1: nominator

		0.2,

		//m 2: denominator multiplier 1

		3.3,

		//m 5: membrane offset 1

		0.035,

		//m 6: denormalized time constant 1

		0.02,

		//m 2: denominator multiplier 2

		1.0,

		//m 5: membrane offset 2

		0.035,

		//m 6: denormalized time constant 2

		-0.02,

	    },

	    //m time constant definition

	    {
		//m 1: nominator

		1.0,

		//m 2: denominator offset

		1.0,

		//m 5: membrane offset 1

		0.035,

		//m 6: denormalized time constant 1

		-0.01,

	    },
	},
    },

    {
	//m administrative overhead

	{
	    //m type of structure

	    MATH_TYPE_ChannelPersistentSteadyStateTau,
	},

	//m first set of descriptive values, alphabetical order

	//m initial reversal potential

	-0.085,

	//m get reversal potential from this intermediary, -1 for none

	-1,

	//m maximal conductance when all channels are permissive

	3.509344551e-11,

	//m contributes to this concentration pool, -1 for none, boolean indicator only.

	-1,

	//m power

	1,

	//m gate table, -1 for initialization

	-1,

	//m gate initial value

	0.03540844397,

	{
	    //m steady state definition

	    {
		//m 1: nominator

		0.2,

		//m 2: denominator multiplier 1

		3.3,

		//m 5: membrane offset 1

		0.035,

		//m 6: denormalized time constant 1

		0.02,

		//m 2: denominator multiplier 2

		1.0,

		//m 5: membrane offset 2

		0.035,

		//m 6: denormalized time constant 2

		-0.02,

	    },

	    //m time constant definition

	    {
		//m 1: nominator

		1.0,

		//m 2: denominator offset

		1.0,

		//m 5: membrane offset 1

		0.035,

		//m 6: denormalized time constant 1

		-0.01,

	    },
	},
    },
};


int piC2m[] =
{
    1,
    2,
    -1,
};


struct MathComponentArray mca =
{
    //m number of math components

    2,

    //m math component data

    &pcsstKM[0].mc,

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


