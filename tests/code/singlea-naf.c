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


#define HECCER_TEST_REPORTING_GRANULARITY 100
#define HECCER_TEST_STEPS 1000
#define HECCER_TEST_TESTED_THINGS ( HECCER_DUMP_VM_COMPARTMENT_MATRIX \
				    | HECCER_DUMP_VM_COMPARTMENT_DATA \
				    | HECCER_DUMP_VM_COMPARTMENT_OPERATIONS \
				    | HECCER_DUMP_VM_MECHANISM_DATA \
				    | HECCER_DUMP_VM_MECHANISM_OPERATIONS \
				    | HECCER_DUMP_VM_SUMMARY \
	)
#define HECCER_TEST_TIME_STEP (6e-6)


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

    -0.028,

/*     double dInject;		 */

    0,

/*     double dRa; */

    360502, // unscaled 2.5,

/*     double dRm; */

    3.58441e+08, // unscaled 1
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

    //m contributes to this concentration pool, -1 for none

    -1,

    //m activation description

    {
	//m power, for a standard heccer, something between 1 and 4 or so.

	3,

	//m gate definition

	{
	    //m initial value, commonly forward over backward steady states

	    0.7612305421,

	    //m corresponding index in tables, set to -1 for initialization.

	    -1,

	    //m forward kinetiks, commonly denoted with alpha or non-perm to perm rate

	    {
		//m multiplier

		35.0e3,

		//m multiplier membrane dependence, 0.0 for no dependence

		0.0,

		//m choose between nominator or denominator, 1 means nominator, -1
		//m means denominator

		-1.0,

		//m nominator or denominator offset

		0.0,

		//m membrane offset

		5.0e-3,

		//m denormalized time constant

		-10.0e-3,
	    },

	    //m backward kinetiks, commonly denoted with beta or perm to non-perm rate

	    {
		//m multiplier

		7.0e3,

		//m multiplier membrane dependence, 0.0 for no dependence

		0.0,

		//m choose between nominator or denominator, 1 means nominator, -1
		//m means denominator

		-1.0,

		//m nominator or denominator offset

		0.0,

		//m membrane offset

		65.0e-3,

		//m denormalized time constant

		20.0e-3,
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

	    0.0009203489029,

	    //m corresponding index in tables, set to -1 for initialization.

	    -1,

	    //m forward kinetiks, commonly denoted with alpha or non-perm to perm rate

	    {
		//m multiplier

		0.225e3,

		//m multiplier membrane dependence, 0.0 for no dependence

		0.0,

		//m choose between nominator or denominator, 1 means nominator, -1
		//m means denominator

		-1.0,

		//m nominator or denominator offset

		1.0,

		//m membrane offset

		80.0e-3,

		//m denormalized time constant

		10.0e-3,
	    },

	    //m backward kinetiks, commonly denoted with beta or perm to non-perm rate

	    {
		//m multiplier

		7.5e3,

		//m multiplier membrane dependence, 0.0 for no dependence

		0.0,

		//m choose between nominator or denominator, 1 means nominator, -1
		//m means denominator

		-1.0,

		//m nominator or denominator offset

		0.0,

		//m membrane offset

		-3.0e-3,

		//m denormalized time constant

		-18.0e-3,
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

    &caiNaF,

    //m compartment 2 first mechanism number

    piC2m,
};


#include "main.c"


