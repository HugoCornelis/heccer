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


#include <stdlib.h>

#include "../../heccer/compartment.h"
#include "../../heccer/heccer.h"


#define HECCER_TEST_REPORTING_GRANULARITY 100
#define HECCER_TEST_STEPS 1000
#define HECCER_TEST_TESTED_THINGS ( HECCER_DUMP_VM_COMPARTMENT_MATRIX \
				    | HECCER_DUMP_VM_COMPARTMENT_DATA \
				    | HECCER_DUMP_VM_COMPARTMENT_OPERATIONS \
				    | HECCER_DUMP_VM_CHANNEL_POOL_FLUXES \
				    | HECCER_DUMP_VM_MECHANISM_DATA \
				    | HECCER_DUMP_VM_MECHANISM_OPERATIONS \
				    | HECCER_DUMP_VM_SUMMARY \
	)
#define HECCER_TEST_TIME_STEP (2e-5)


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

/* 	//m first mechanism */

/* 	NULL, */

/* 	//m number of mechanisms */

/* 	0, */

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


//v a simple fast sodium channel

struct ChannelActInact pcaiCaT[] =
{
    {
	//m administrative overhead

	{
	    //m type of structure

	    MECHANISM_TYPE_ChannelActInact,
	},

	//m first set of descriptive values, alphabetical order

	//m reversal potential

	0.1375262439,

	//m maximal conductance when all channels are permissive

	1.394928884e-08,

	//m contributes to this concentration pool

	1,

	//m activation description

	{
	    //m power, for a standard heccer, something between 1 and 4 or so.

	    1,

	    //m gate definition

	    {
		//m initial value, commonly forward over backward steady states

		0.9889635316,

		//m corresponding index in tables, set to -1 for initialization.

		-1,

		//m forward kinetiks, commonly denoted with alpha or non-perm to perm rate

		{
		    //m multiplier

		    2.6e3,

		    //m multiplier membrane dependence, 0.0 for no dependence

		    0.0,

		    //m choose between nominator or denominator, 1 means nominator, -1
		    //m means denominator

		    -1.0,

		    //m nominator or denominator offset

		    1.0,

		    //m membrane offset

		    0.021,

		    //m denormalized time constant

		    -8e-3,
		},

		//m backward kinetiks, commonly denoted with beta or perm to non-perm rate

		{
		    //m multiplier

		    0.18e3,

		    //m multiplier membrane dependence, 0.0 for no dependence

		    0.0,

		    //m choose between nominator or denominator, 1 means nominator, -1
		    //m means denominator

		    -1.0,

		    //m nominator or denominator offset

		    1.0,

		    //m membrane offset

		    0.04,

		    //m denormalized time constant

		    4e-3,
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

		0.002659210635,

		//m corresponding index in tables, set to -1 for initialization.

		-1,

		//m forward kinetiks, commonly denoted with alpha or non-perm to perm rate

		{
		    //m multiplier

		    0.0025e3,

		    //m multiplier membrane dependence, 0.0 for no dependence

		    0.0,

		    //m choose between nominator or denominator, 1 means nominator, -1
		    //m means denominator

		    -1.0,

		    //m nominator or denominator offset

		    1.0,

		    //m membrane offset

		    0.04,

		    //m denormalized time constant

		    8e-3,
		},

		//m backward kinetiks, commonly denoted with beta or perm to non-perm rate

		{
		    //m multiplier

		    0.19e3,

		    //m multiplier membrane dependence, 0.0 for no dependence

		    0.0,

		    //m choose between nominator or denominator, 1 means nominator, -1
		    //m means denominator

		    -1.0,

		    //m nominator or denominator offset

		    1.0,

		    //m membrane offset

		    0.05,

		    //m denormalized time constant

		    -10.0e-3,
		},
	    },
	},
    },

    {
	//m administrative overhead

	{
	    //m type of structure

	    MECHANISM_TYPE_ChannelActInact,
	},

	//m first set of descriptive values, alphabetical order

	//m reversal potential

	0.1470214874,

	//m maximal conductance when all channels are permissive

	1.754672296e-09,

	//m contributes to this concentration pool

	3,

	//m activation description

	{
	    //m power, for a standard heccer, something between 1 and 4 or so.

	    1,

	    //m gate definition

	    {
		//m initial value, commonly forward over backward steady states

		0.03891870645,

		//m corresponding index in tables, set to -1 for initialization.

		-1,

		//m forward kinetiks, commonly denoted with alpha or non-perm to perm rate

		{
		    //m multiplier

		    2.6e3,

		    //m multiplier membrane dependence, 0.0 for no dependence

		    0.0,

		    //m choose between nominator or denominator, 1 means nominator, -1
		    //m means denominator

		    -1.0,

		    //m nominator or denominator offset

		    1.0,

		    //m membrane offset

		    0.021,

		    //m denormalized time constant

		    -8e-3,
		},

		//m backward kinetiks, commonly denoted with beta or perm to non-perm rate

		{
		    //m multiplier

		    0.18e3,

		    //m multiplier membrane dependence, 0.0 for no dependence

		    0.0,

		    //m choose between nominator or denominator, 1 means nominator, -1
		    //m means denominator

		    -1.0,

		    //m nominator or denominator offset

		    1.0,

		    //m membrane offset

		    0.04,

		    //m denormalized time constant

		    4e-3,
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

		0.08260212813,

		//m corresponding index in tables, set to -1 for initialization.

		-1,

		//m forward kinetiks, commonly denoted with alpha or non-perm to perm rate

		{
		    //m multiplier

		    0.0025e3,

		    //m multiplier membrane dependence, 0.0 for no dependence

		    0.0,

		    //m choose between nominator or denominator, 1 means nominator, -1
		    //m means denominator

		    -1.0,

		    //m nominator or denominator offset

		    1.0,

		    //m membrane offset

		    0.04,

		    //m denormalized time constant

		    8e-3,
		},

		//m backward kinetiks, commonly denoted with beta or perm to non-perm rate

		{
		    //m multiplier

		    0.19e3,

		    //m multiplier membrane dependence, 0.0 for no dependence

		    0.0,

		    //m choose between nominator or denominator, 1 means nominator, -1
		    //m means denominator

		    -1.0,

		    //m nominator or denominator offset

		    1.0,

		    //m membrane offset

		    0.05,

		    //m denormalized time constant

		    -10.0e-3,
		},
	    },
	},
    },
};


struct ExponentialDecay pexdecCa[] =
{
    {
	//m administrative overhead

	{
	    //m type of structure

	    MECHANISM_TYPE_ExponentialDecay,
	},

	//m flux contributor index, -1 for not initialized

	-1,

	//m initial value

	4e-5,

	//m beta

	9412391936.0,

	//m steady state

	4e-05,

	//m tau

	0.00010,
    },

    {
	//m administrative overhead

	{
	    //m type of structure

	    MECHANISM_TYPE_ExponentialDecay,
	},

	//m flux contributor index, -1 for not initialized

	-1,

	//m initial value

	4e-5,

	//m beta

	9412391936.0,

	//m steady state

	4e-05,

	//m tau

	0.00010,
    }
};


int piC2m[] =
{
    2,
    4,
    -1,
};


struct Intermediary inter =
{
    //m compartment array

    2,

    pcomp,

    //m number of mechanisms

    2,

    //m mechanism data

    NULL,

    //m compartment 2 first mechanism number

    piC2m,
};


int main(int argc, char *argv[])
{
    //- prepare the mechanism intermediary

    //! I add 32, to avoid alignment issues, not sure how to do this
    //! in a clean, portable and error free way.

    void *pvMechanism = calloc(1, sizeof(*pcaiCaT) + sizeof(*pexdecCa) + 32);

    struct ChannelActInact *pcai0 = (struct ChannelActInact *)pvMechanism;

    struct ExponentialDecay *pexdec0 = (struct ExponentialDecay *)&pcai0[1];

    struct ChannelActInact *pcai1 = (struct ChannelActInact *)&pexdec0[1];

    struct ExponentialDecay *pexdec1 = (struct ExponentialDecay *)&pcai1[1];

    *pcai0 = pcaiCaT[0];

    *pexdec0 = pexdecCa[0];

    *pcai1 = pcaiCaT[1];

    *pexdec1 = pexdecCa[1];

    //- link the intermediary

    inter.pvMechanism = pvMechanism;

    //- do the simulation

    simulate(argc,argv);
}


#define main(argc,argv) simulate(argc,argv)

//t this prototype can give warning and perhaps errors.

int main(int argc, char *argv[]);


#include "main.c"


