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


#include <stdlib.h>

#include "../../heccer/addressing.h"
#include "../../heccer/compartment.h"
#include "../../heccer/heccer.h"


#define HECCER_TEST_OPTIONS ( HECCER_OPTION_ENABLE_INDIVIDUAL_CURRENTS	\
			      | HECCER_OPTION_ENABLE_AGGREGATORS	\
	)
#define HECCER_TEST_TESTED_THINGS ( HECCER_DUMP_VM_COMPARTMENT_MATRIX \
				    | HECCER_DUMP_VM_COMPARTMENT_DATA \
				    | HECCER_DUMP_VM_COMPARTMENT_OPERATIONS \
				    | HECCER_DUMP_VM_MECHANISM_DATA \
				    | HECCER_DUMP_VM_MECHANISM_OPERATIONS \
				    | HECCER_DUMP_VM_SUMMARY \
				    | HECCER_DUMP_VM_AGGREGATORS \
	)


struct Compartment comp =
{
    //m administrative overhead

    {
	//m type of structure

	MATH_TYPE_Compartment,

#ifdef HECCER_SOURCE_NEUROSPACES

	//m identification

	ADDRESSING_NEUROSPACES_2_HECCER(1000),

#endif

#ifdef HECCER_SOURCE_TYPING

	//m model source type number

	//! source typing is used to compute aggregate currents ao
	//! things.

	-1,

#endif

    },

    //m index of parent compartment, -1 for none

    -1,

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
};


struct ChannelActInact caiCaT =
{
    //m administrative overhead

    {
	//m type of structure

	MATH_TYPE_ChannelActInact,

#ifdef HECCER_SOURCE_NEUROSPACES

	//m identification

	ADDRESSING_NEUROSPACES_2_HECCER(2000),

#endif

#ifdef HECCER_SOURCE_TYPING

	//m model source type number

	//! source typing is used to compute aggregate currents ao
	//! things.

	-1,

#endif

    },

    //m first set of descriptive values, alphabetical order

    //m initial reversal potential

    0.14702148735523224,

    //m get reversal potential from this intermediary, -1 for none

    -1,

    //m maximal conductance when all channels are permissive

    1.7546722963501793e-09,

    //m contributes to this concentration pool, -1 for none, boolean indicator only.

    1,

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

	    {
		//m forward kinetiks, commonly denoted with alpha or non-perm to perm rate

		{
		    //m multiplier

		    2.6e3,

		    //m multiplier membrane dependence, 0.0 for no dependence

		    0.0,

		    //m 2b: multiplier membrane dependence offset, 0.0 for no dependence

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

		    //m 2b: multiplier membrane dependence offset, 0.0 for no dependence

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

	    {
		//m forward kinetiks, commonly denoted with alpha or non-perm to perm rate

		{
		    //m multiplier

		    0.0025e3,

		    //m multiplier membrane dependence, 0.0 for no dependence

		    0.0,

		    //m 2b: multiplier membrane dependence offset, 0.0 for no dependence

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

		    //m 2b: multiplier membrane dependence offset, 0.0 for no dependence

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


struct ExponentialDecay exdecCa =
{
    //m administrative overhead

    {
	//m type of structure

	MATH_TYPE_ExponentialDecay,

#ifdef HECCER_SOURCE_NEUROSPACES

	//m identification

	ADDRESSING_NEUROSPACES_2_HECCER(3000),

#endif

#ifdef HECCER_SOURCE_TYPING

	//m model source type number

	//! source typing is used to compute aggregate currents ao
	//! things.

	0,

#endif

    },

    //m initial value

    4e-5,

    //m beta

    7.579027046e+10,

    //m steady state

    4e-05,

    //m tau

    0.00010,

    //m external contribution delivered by these intermediaries

    {
	3,
	-1,
	-1,
	-1,
    },
};


struct ChannelActConc pcacKC[] =
{
    {
	//m administrative overhead

	{
	    //m type of structure

	    MATH_TYPE_ChannelActConc,

#ifdef HECCER_SOURCE_NEUROSPACES

	    //m identification

	    ADDRESSING_NEUROSPACES_2_HECCER(4000),

#endif

#ifdef HECCER_SOURCE_TYPING

	    //m model source type number

	    //! source typing is used to compute aggregate currents ao
	    //! things.

	    0,

#endif

	},

	//m first set of descriptive values, alphabetical order

	//m initial reversal potential

	-0.085,

	//m get reversal potential from this intermediary, -1 for none

	-1,

	//m maximal conductance when all channels are permissive

	2.80747571e-07,

	//m contributes to this concentration pool, -1 for none, boolean indicator only.

	-1,

	//m activation description

	{
	    //m power, for a standard heccer, something between 1 and 4 or so.

	    1,

	    //m gate definition

	    {
		//m initial value, commonly forward over backward steady states

		0.063531859768213905,

		//m corresponding index in tables, set to -1 for initialization.

		-1,

		{
		    //m forward kinetiks, commonly denoted with alpha or non-perm to perm rate

		    {
			//m multiplier

			7.5e3,

			//m multiplier membrane dependence, 0.0 for no dependence

			0.0,

			//m 2b: multiplier membrane dependence offset, 0.0 for no dependence

			0.0,

			//m choose between nominator or denominator, 1 means nominator, -1
			//m means denominator

			-1.0,

			//m nominator or denominator offset

			0.0,

			//m membrane offset

			0.0,

			//m denormalized time constant

			1e12,
		    },

		    //m backward kinetiks, commonly denoted with beta or perm to non-perm rate

		    {
			//m multiplier

			0.11e3,

			//m multiplier membrane dependence, 0.0 for no dependence

			0.0,

			//m 2b: multiplier membrane dependence offset, 0.0 for no dependence

			0.0,

			//m choose between nominator or denominator, 1 means nominator, -1
			//m means denominator

			-1.0,

			//m nominator or denominator offset

			0.0,

			//m membrane offset

			-0.035,

			//m denormalized time constant

			14.9e-3,
		    },
		},
	    },
	},

	//m activator dependence description

	{
	    //m power, for a standard heccer, something between 1 and 4 or so.

	    2,

	    //m activator definition

	    {
		//m initial value, commonly steady state

		0.0099009900989999993,

		//m corresponding index in tables, set to -1 for initialization.

		-1,

		//m is activated by the output of this mechanism, must be filled in

		2,

		{
		    //m basal level, A in EDS1994

		    4.0e-3,

		    //m time constant, B in EDS1994

		    0.010,
		},
	    },
	},
    },

    {
	//m administrative overhead

	{
	    //m type of structure

	    MATH_TYPE_ChannelActConc,

#ifdef HECCER_SOURCE_NEUROSPACES

	    //m identification

	    ADDRESSING_NEUROSPACES_2_HECCER(5000),

#endif

#ifdef HECCER_SOURCE_TYPING

	    //m model source type number

	    //! source typing is used to compute aggregate currents ao
	    //! things.

	    0,

#endif

	},

	//m first set of descriptive values, alphabetical order

	//m initial reversal potential

	-0.085,

	//m get reversal potential from this intermediary, -1 for none

	-1,

	//m maximal conductance when all channels are permissive

	2.80747571e-07,

	//m contributes to this concentration pool, -1 for none, boolean indicator only.

	-1,

	//m activation description

	{
	    //m power, for a standard heccer, something between 1 and 4 or so.

	    1,

	    //m gate definition

	    {
		//m initial value, commonly forward over backward steady states

		0.063531859768213905,

		//m corresponding index in tables, set to -1 for initialization.

		-1,

		{
		    //m forward kinetiks, commonly denoted with alpha or non-perm to perm rate

		    {
			//m multiplier

			7.5e3,

			//m multiplier membrane dependence, 0.0 for no dependence

			0.0,

			//m 2b: multiplier membrane dependence offset, 0.0 for no dependence

			0.0,

			//m choose between nominator or denominator, 1 means nominator, -1
			//m means denominator

			-1.0,

			//m nominator or denominator offset

			0.0,

			//m membrane offset

			0.0,

			//m denormalized time constant

			1e12,
		    },

		    //m backward kinetiks, commonly denoted with beta or perm to non-perm rate

		    {
			//m multiplier

			0.11e3,

			//m multiplier membrane dependence, 0.0 for no dependence

			0.0,

			//m 2b: multiplier membrane dependence offset, 0.0 for no dependence

			0.0,

			//m choose between nominator or denominator, 1 means nominator, -1
			//m means denominator

			-1.0,

			//m nominator or denominator offset

			0.0,

			//m membrane offset

			-0.035,

			//m denormalized time constant

			14.9e-3,
		    },
		},
	    },
	},

	//m activator dependence description

	{
	    //m power, for a standard heccer, something between 1 and 4 or so.

	    2,

	    //m activator definition

	    {
		//m initial value, commonly steady state

		0.0099009900989999993,

		//m corresponding index in tables, set to -1 for initialization.

		-1,

		//m is activated by the output of this mechanism, must be filled in

		2,

		{
		    //m basal level, A in EDS1994

		    4.0e-3,

		    //m time constant, B in EDS1994

		    0.010,
		},
	    },
	},
    },

};


int piC2m[] =
{
    4,
    -1,
};


struct MathComponentArray mca =
{
    //m number of math components

    4,

    //m math component data

    NULL,

    //m math component index, initialize to NULL

    NULL,

};


struct Intermediary inter =
{
    //m compartment array

    1,

    &comp,

    //m all other mathematical components

    &mca,

    //m compartment 2 first mechanism number

    piC2m,
};


int main(int argc, char *argv[])
{
    //- determine intermediary size, and allocate

    struct MathComponentInfo *pmciCaT = MathComponentInfoLookup(caiCaT.mc.iType);

    struct MathComponentInfo *pmciCa = MathComponentInfoLookup(exdecCa.mc.iType);

    struct MathComponentInfo *pmciKC2 = MathComponentInfoLookup(pcacKC[0].mc.iType);

    int iChars = pmciCaT->iChars + pmciCa->iChars + pmciKC2->iChars * 2;

    void *pmc = calloc(sizeof(char), iChars);

    //- prepare the mechanism intermediary

    struct ChannelActConc *pcac = (struct ChannelActConc *)pmc;

    *pcac = pcacKC[0];

    pcac = &pcac[1];

    *pcac = pcacKC[1];

    struct ExponentialDecay *pexdec = (struct ExponentialDecay *)&((char *)pcac)[pmciKC2->iChars];

    *pexdec = exdecCa;

    struct ChannelActInact *pcai = (struct ChannelActInact *)&((char *)pexdec)[pmciCa->iChars];

    *pcai = caiCaT;

    //- link the intermediary

    mca.pmc = pmc;

    //- do the simulation

    simulate(argc,argv);
}


#define main(argc,argv) simulate(argc,argv)

//t this prototype can give warning and perhaps errors.

int main(int argc, char *argv[]);


#include "main.c"


