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


#include <malloc.h>
#include <stdlib.h>

#include "../../heccer/addressing.h"
#include "../../heccer/compartment.h"
#include "../../heccer/heccer.h"


#include "main.h"


#define HECCER_TEST_OPTIONS (HECCER_OPTION_ENABLE_AGGREGATORS | HECCER_OPTION_ENABLE_INDIVIDUAL_CURRENTS)
#define HECCER_TEST_TESTED_THINGS ( HECCER_DUMP_VM_COMPARTMENT_MATRIX \
				    | HECCER_DUMP_VM_COMPARTMENT_MATRIX_DIAGONALS \
				    | HECCER_DUMP_VM_COMPARTMENT_OPERATIONS \
				    | HECCER_DUMP_VM_CHANNEL_POOL_FLUXES \
				    | HECCER_DUMP_VM_MECHANISM_DATA \
				    | HECCER_DUMP_VM_MECHANISM_OPERATIONS \
				    | HECCER_DUMP_VM_SUMMARY \
				    | HECCER_DUMP_VM_AGGREGATORS \
	)
/* #define HECCER_TEST_TIME_STEP (2e-5) */


struct Compartment compSoma =
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

	0,

#endif

    },

    //m first set of descriptive values, alphabetical order

    //m initial reversal potential

    0.1375262439,

    //m get reversal potential from this intermediary, -1 for none

    -1,

    //m maximal conductance when all channels are permissive

    1.394928884e-08,

    //m contributes to this concentration pool, -1 for none, boolean indicator only.

    -1,

    //m activation description

    {
	//m power, for a standard heccer, something between 1 and 4 or so.

	1,

	//m gate definition

	{
	    //m initial value, commonly forward over backward steady states

	    0.039478155609280696,

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

	    0.08211379989188651,

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


//v a delayed rectifier potassium channel

struct ChannelSteadyStateSteppedTau csstKdr =
{
    //m administrative overhead

    {
	//m type of structure

	MATH_TYPE_ChannelSteadyStateSteppedTau,

#ifdef HECCER_SOURCE_NEUROSPACES

	//m identification

	ADDRESSING_NEUROSPACES_2_HECCER(3000),

#endif

#ifdef HECCER_SOURCE_TYPING

	//m model source type number

	//! source typing is used to compute aggregate currents ao
	//! things.

	1,

#endif

    },

    //m first set of descriptive values, alphabetical order

    //m initial reversal potential

    -0.085,

    //m get reversal potential from this intermediary, -1 for none

    -1,

    //m maximal conductance when all channels are permissive

    1.67392e-05,

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


//v a persistent sodium channel

struct ChannelAct caNaP =
{
    //m administrative overhead

    {
	//m type of structure

	MATH_TYPE_ChannelAct,

#ifdef HECCER_SOURCE_NEUROSPACES

	//m identification

	ADDRESSING_NEUROSPACES_2_HECCER(4000),

#endif

#ifdef HECCER_SOURCE_TYPING

	//m model source type number

	//! source typing is used to compute aggregate currents ao
	//! things.

	2,

#endif

    },

    //m first set of descriptive values, alphabetical order

    //m initial reversal potential

    0.045,

    //m get reversal potential from this intermediary, -1 for none

    -1,

    //m maximal conductance when all channels are permissive

    2.789857767e-08,

    //m contributes to this concentration pool, -1 for none, boolean indicator only.

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

	    {
		//m forward kinetiks, commonly denoted with alpha or non-perm to perm rate

		{
		    //m multiplier

		    200.0e3,

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

		    -0.018,

		    //m denormalized time constant

		    -16.0e-3,
		},

		//m backward kinetiks, commonly denoted with beta or perm to non-perm rate

		{
		    //m multiplier

		    25.0e3,

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

		    0.058,

		    //m denormalized time constant

		    8.0e-3,
		},
	    },
	},
    },

};


//v a simple fast sodium channel

struct ChannelActInact caiNaF =
{
    //m administrative overhead

    {
	//m type of structure

	MATH_TYPE_ChannelActInact,

#ifdef HECCER_SOURCE_NEUROSPACES

	//m identification

	ADDRESSING_NEUROSPACES_2_HECCER(5000),

#endif

#ifdef HECCER_SOURCE_TYPING

	//m model source type number

	//! source typing is used to compute aggregate currents ao
	//! things.

	2,

#endif

    },

    //m first set of descriptive values, alphabetical order

    //m initial reversal potential

    0.045,

    //m get reversal potential from this intermediary, -1 for none

    -1,

    //m maximal conductance when all channels are permissive

    0.0002092393115,

    //m contributes to this concentration pool, -1 for none, boolean indicator only.

    -1,

    //m activation description

    {
	//m power, for a standard heccer, something between 1 and 4 or so.

	3,

	//m gate definition

	{
	    //m initial value, commonly forward over backward steady states

	    0.0078406449371415214,

	    //m corresponding index in tables, set to -1 for initialization.

	    -1,

	    {
		//m forward kinetiks, commonly denoted with alpha or non-perm to perm rate

		{
		    //m multiplier

		    35.0e3,

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

		    //m 2b: multiplier membrane dependence offset, 0.0 for no dependence

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
    },

    //m inactivation description

    {
	//m power, for a standard heccer, something between 1 and 4 or so.

	1,

	//m gate definition

	{
	    //m initial value, commonly forward over backward steady states

	    0.26397776926502026,

	    //m corresponding index in tables, set to -1 for initialization.

	    -1,

	    {
		//m forward kinetiks, commonly denoted with alpha or non-perm to perm rate

		{
		    //m multiplier

		    0.225e3,

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

		    //m 2b: multiplier membrane dependence offset, 0.0 for no dependence

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

    &compSoma,

    //m all other mathematical components

    &mca,

    //m compartment 2 first mechanism number

    piC2m,

#ifdef HECCER_SOURCE_NEUROSPACES

    //m identification of the originator, mostly a cell or cell
    //m population, but perhaps just a segment vector

    //m start range

    ADDRESSING_NEUROSPACES_2_HECCER(1000 - 1),

    //m end range

    ADDRESSING_NEUROSPACES_2_HECCER(9000),

#endif

};


int main(int argc, char *argv[])
{
    //- determine intermediary size, and allocate

    struct MathComponentInfo *pmciCaT = MathComponentInfoLookup(caiCaT.mc.iType);

    struct MathComponentInfo *pmciKdr = MathComponentInfoLookup(csstKdr.mc.iType);

    struct MathComponentInfo *pmciNaP = MathComponentInfoLookup(caNaP.mc.iType);

    struct MathComponentInfo *pmciNaF = MathComponentInfoLookup(caiNaF.mc.iType);

    //- prepare the mechanism intermediary

    int iChars = pmciCaT->iChars + pmciKdr->iChars + pmciNaP->iChars + pmciNaF->iChars;

    void *pmc = calloc(sizeof(char), iChars);

    struct MathComponent *pmcTarget = pmc;

    pmcTarget = MathComponentCopyNext(pmcTarget, &caiCaT.mc);
    pmcTarget = MathComponentCopyNext(pmcTarget, &csstKdr.mc);
    pmcTarget = MathComponentCopyNext(pmcTarget, &caNaP.mc);
    pmcTarget = MathComponentCopyNext(pmcTarget, &caiNaF.mc);

    //- link the intermediary

    mca.pmc = pmc;

    //- do the simulation

    simulate(argc,argv);

#ifdef HECCER_SOURCE_NEUROSPACES

    //- address variables via the external ids

    double *pdAggregator0External = HeccerAddressVariable(pheccer, 1000 - 1, "aggregator[0]");

    double *pdAggregator1External = HeccerAddressVariable(pheccer, 1000 - 1, "aggregator[1]");

    double *pdAggregator2External = HeccerAddressVariable(pheccer, 1000 - 1, "aggregator[2]");

#endif

    //- address variables via the internal indices

    double *pdAggregator0Internal = HeccerAddressAggregator(pheccer, 0, "aggregator[0]");

    double *pdAggregator1Internal = HeccerAddressAggregator(pheccer, 1, "aggregator[1]");

    double *pdAggregator2Internal = HeccerAddressAggregator(pheccer, 2, "aggregator[2]");

#ifdef HECCER_SOURCE_NEUROSPACES

    if (pdAggregator0Internal != pdAggregator0External)
    {
	fprintf(stdout, "*** Error: (pdAggregator0Internal != pdAggregator0External)\n");

	exit(EXIT_FAILURE);
    }

    if (pdAggregator1Internal != pdAggregator1External)
    {
	fprintf(stdout, "*** Error: (pdAggregator1Internal != pdAggregator1External)\n");

	exit(EXIT_FAILURE);
    }

    if (pdAggregator2Internal != pdAggregator2External)
    {
	fprintf(stdout, "*** Error: (pdAggregator2Internal != pdAggregator2External)\n");

	exit(EXIT_FAILURE);
    }

#endif

    fprintf(stdout, "pdAggregator0 is %g\n", pdAggregator0External[0]);

    fprintf(stdout, "pdAggregator1 is %g\n", pdAggregator1External[0]);

    fprintf(stdout, "pdAggregator2 is %g\n", pdAggregator2External[0]);

    //- set default result : ok

    int iResult = EXIT_SUCCESS;

    //- return result

    return(iResult);
}


#define main(argc,argv) simulate(argc,argv)

//t this prototype can give warning and perhaps errors.

int main(int argc, char *argv[]);


#include "main.c"


