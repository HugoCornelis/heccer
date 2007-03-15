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


//v a anomalous rectifier potassium channel

struct ChannelPersistentSteadyStateDualTau csstKH =
{
    //m administrative overhead

    {
	//m type of structure

	MATH_TYPE_ChannelPersistentSteadyStateDualTau,
    },

    //m first set of descriptive values, alphabetical order

    //m reversal potential

    -0.085,

    //m maximal conductance when all channels are permissive

    8.369573479e-09,

    //m contributes to this concentration pool, -1 for none, boolean indicator only.

    -1,

    //m first power

    1,

    //m second power

    1,

    //m first gate table, -1 for initialization

    -1,

    //m second gate table, -1 for initialization

    -1,

    //m first gate initial value

    0.1443111543,

    //m second gate initial value

    0.03607778857,

    //m fast component steady state

    0.0076,

    //m slow component steady state

    0.0368,

    //m tau 1

    {
	//m 1: nominator multiplier

	0.8,

	//m 2: denominator offset

	1.0,

	//m 5: membrane offset

	0.082,

	//m 6: denormalized time constant

	0.007,

    },

    //m tau 2

    {
	//m 1: nominator multiplier

	0.2,

	//m 2: denominator offset

	1.0,

	//m 5: membrane offset

	0.082,

	//m 6: denormalized time constant

	0.007,

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

    &csstKH.mc,

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


