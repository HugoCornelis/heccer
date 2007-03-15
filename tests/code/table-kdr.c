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


#define HECCER_TEST_INTERPOL_INTERVAL_DEFAULT_ENTRIES		20
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


//v a delayed rectifier potassium channel

struct ChannelSteadyStateSteppedTau csstKdr =
{
    //m administrative overhead

    {
	//m type of structure

	MATH_TYPE_ChannelSteadyStateSteppedTau,
    },

    //m first set of descriptive values, alphabetical order

    //m reversal potential

    -0.085,

    //m maximal conductance when all channels are permissive

    4.184786349e-07,

    //m contributes to this concentration pool, -1 for none, boolean indicator only.

    -1,

    //m first power

    2,

    //m second power

    1,

    //m first table, -1 for initialization

    -1,

    //m second table, -1 for initialization

    -1,

    //m first initial value

    0.003599440607,

    //m second initial value

    0.9999799396,

    //m steady state definition

    {
	//m first kinetiks

	{
	    //m part a

	    {
		//m 1: multiplier
	
		-23.5e3,
	
		//m 2: multiplier membrane dependence offset, 0.0 for no offset
	
		0.012,
	
		//m 4: nominator or denominator offset
	
		-1.0,
	
		//m 5: membrane offset
	
		0.012,
	
		//m 6: denormalized time constant
	
		-12e-3,

	    },

	    //m part b

	    {
		//m 1: multiplier

		5e3,

		//m 2: multiplier membrane dependence, 0.0 for no dependence

		0.030,

		//m 2: multiplier membrane dependence offset, 0.0 for no offset
	
		0.147,
	
	    },
	},

	//m second kinetiks

	{
	    //m part a

	    {
		//m 1: multiplier
	
		-23.5e3,
	
		//m 2: multiplier membrane dependence offset, 0.0 for no offset
	
		-0.008,
	
		//m 4: nominator or denominator offset
	
		-1.0,
	
		//m 5: membrane offset
	
		-0.008,
	
		//m 6: denormalized time constant
	
		-12e-3,

	    },

	    //m part b

	    {
		//m 1: multiplier

		5e3,

		//m 2: multiplier membrane dependence, 0.0 for no dependence

		0.030,

		//m 2: multiplier membrane dependence offset, 0.0 for no offset
	
		0.127,
	
	    },
	},
    },

    //m time constant definition

    {
	//m part a

	{
	    //m threshold

	    -0.025,

	    //m low membrane potential target value

	    1.2,

	    //m above membrane potential target value

	    0.010,

	},

	//m part b

	{
	    //m 4: nominator or denominator offset

	    1.0,

	    //m 5: membrane offset

	    0.025,

	    //m 6: denormalized time constant

	    0.004,

	},
    },
};


int piC2m[] =
{
    1,
    -1,
};


struct MathComponentArray mca =
{
    //m number of math components

    1,

    //m math component data

    &csstKdr.mc,

    //m math component index, initialize to NULL

    NULL,

};


struct Intermediary inter =
{
    //m compartment array

    1,

    &compSoma,

    //m all other mathematical components

    &mca,

    //m compartment 2 first mechanism number

    piC2m,
};


#include "main.c"


