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
#include "../../heccer/mathcomponent.h"
#include "../../heccer/output.h"


/* #define HECCER_TEST_INTERVAL_DEFAULT_START			(-0.1) */
/* #define HECCER_TEST_INTERVAL_DEFAULT_END			(0.05) */
/* #define HECCER_TEST_INTERVAL_DEFAULT_ENTRIES			3000 */
#define HECCER_TEST_REPORTING_GRANULARITY 10000
#define HECCER_TEST_STEPS 40000
#define HECCER_TEST_TESTED_THINGS ( HECCER_DUMP_VM_COMPARTMENT_MATRIX \
				    | HECCER_DUMP_VM_COMPARTMENT_MATRIX_DIAGONALS \
				    | HECCER_DUMP_VM_COMPARTMENT_OPERATIONS \
				    | HECCER_DUMP_VM_MECHANISM_DATA \
				    | HECCER_DUMP_VM_MECHANISM_OPERATIONS \
				    | HECCER_DUMP_VM_SUMMARY \
	)
#define HECCER_TEST_TIME_STEP (5e-7)


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

    2.827430998e-11,

/*     double dEm; */

    -0.05939999968,

/*     double dInitVm; */

    -0.070,

/*     double dInject;		 */

    3e-10,

/*     double dRa; */

    12732.40625,

/*     double dRm; */

    117891472,
};


//v a simple fast sodium channel

struct ChannelActInact caiNa =
{
    //m administrative overhead

    {
	//m type of structure

	MATH_TYPE_ChannelActInact,
    },

    //m first set of descriptive values, alphabetical order

    //m initial reversal potential

    0.045,

    //m get reversal potential from this intermediary, -1 for none

    -1,

    //m maximal conductance when all channels are permissive

    3.392917279e-06,

    //m contributes to this concentration pool, -1 for none, boolean indicator only.

    -1,

    //m activation description

    {
	//m power, for a standard heccer, something between 1 and 4 or so.

	3,

	//m gate definition

	{
	    //m initial value, commonly forward over backward steady states

	    0.05293248736,

	    //m corresponding index in tables, set to -1 for initialization.

	    -1,

	    {
		//m forward kinetiks, commonly denoted with alpha or non-perm to perm rate

		{
		    //m multiplier

		    -4500,

		    //m multiplier membrane dependence, 0.0 for no dependence

		    0.1e6,

		    //m 2b: multiplier membrane dependence offset, 0.0 for no dependence

		    0.0,

		    //m choose between nominator or denominator, 1 means nominator, -1
		    //m means denominator

		    -1.0,

		    //m nominator or denominator offset

		    -1.0,

		    //m membrane offset

		    0.045,

		    //m denormalized time constant

		    -0.01,
		},

		//m backward kinetiks, commonly denoted with beta or perm to non-perm rate

		{
		    //m multiplier

		    4e3,

		    //m multiplier membrane dependence, 0.0 for no dependence

		    0.0,

		    //m 2b: multiplier membrane dependence offset, 0.0 for no dependence

		    1.0,

		    //m choose between nominator or denominator, 1 means nominator, -1
		    //m means denominator

		    -1.0,

		    //m nominator or denominator offset

		    0.0,

		    //m membrane offset

		    0.07,

		    //m denormalized time constant

		    18e-3,
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

	    0.5961207962,

	    //m corresponding index in tables, set to -1 for initialization.

	    -1,

	    {
		//m forward kinetiks, commonly denoted with alpha or non-perm to perm rate

		{
		    //m multiplier

		    70,

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

		    0.07,

		    //m denormalized time constant

		    0.02,
		},

		//m backward kinetiks, commonly denoted with beta or perm to non-perm rate

		{
		    //m multiplier

		    1.0e3,

		    //m multiplier membrane dependence, 0.0 for no dependence

		    0.0,

		    //m 2b: multiplier membrane dependence offset, 0.0 for no dependence

		    1.0,

		    //m choose between nominator or denominator, 1 means nominator, -1
		    //m means denominator

		    -1.0,

		    //m nominator or denominator offset

		    1.0,

		    //m membrane offset

		    0.04,

		    //m denormalized time constant

		    -10.0e-3,
		},
	    },
	},
    },
};


struct ChannelAct caK =
{
    //m administrative overhead

    {
	//m type of structure

	MATH_TYPE_ChannelAct,
    },

    //m first set of descriptive values, alphabetical order

    //m initial reversal potential

    -0.08200000226,

    //m get reversal potential from this intermediary, -1 for none

    -1,

    //m maximal conductance when all channels are permissive

    1.017875206e-06,

    //m contributes to this concentration pool, -1 for none, boolean indicator only.

    -1,

    //m activation description

    {
	//m power, for a standard heccer, something between 1 and 4 or so.

	4,

	//m gate definition

	{
	    //m initial value, commonly forward over backward steady states

	    0.3176768857,

	    //m corresponding index in tables, set to -1 for initialization.

	    -1,

	    {
		//m forward kinetiks, commonly denoted with alpha or non-perm to perm rate

		{
		    //m multiplier

		    -600,

		    //m multiplier membrane dependence, 0.0 for no dependence

		    10000,

		    //m 2b: multiplier membrane dependence offset, 0.0 for no dependence

		    0.0,

		    //m choose between nominator or denominator, 1 means nominator, -1
		    //m means denominator

		    -1.0,

		    //m nominator or denominator offset

		    -1.0,

		    //m membrane offset

		    60e-3,

		    //m denormalized time constant

		    -10.0e-3,
		},

		//m backward kinetiks, commonly denoted with beta or perm to non-perm rate

		{
		    //m multiplier

		    125,

		    //m multiplier membrane dependence, 0.0 for no dependence

		    0.0,

		    //m 2b: multiplier membrane dependence offset, 0.0 for no dependence

		    1.0,

		    //m choose between nominator or denominator, 1 means nominator, -1
		    //m means denominator

		    -1.0,

		    //m nominator or denominator offset

		    0.0,

		    //m membrane offset

		    70e-3,

		    //m denormalized time constant

		    80e-3,
		},
	    },
	},
    },
};


int piC2m[] =
{
    2,
    -1,
};


struct MathComponentArray mca =
{
    //m number of math components

    2,

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
};


struct OutputGenerator * pogVm = NULL;

double *pdVm = NULL;

char pcStep[100] = "";

#include "main.h"


int main(int argc, char *argv[])
{
    //- set default result : ok

    int iResult = EXIT_SUCCESS;

    //- determine intermediary size, and allocate

    struct MathComponentInfo *pmciNa = MathComponentInfoLookup(caiNa.mc.iType);

    struct MathComponentInfo *pmciK = MathComponentInfoLookup(caK.mc.iType);

    int iChars = pmciNa->iChars + pmciK->iChars;;

    void *pmc = calloc(sizeof(char), iChars);

    //- prepare the mechanism intermediary

    struct ChannelActInact *pcaiNa = (struct ChannelActInact *)pmc;

    *pcaiNa = caiNa;

    struct ChannelAct *pcaK = (struct ChannelAct *)&((char *)pcaiNa)[pmciNa->iChars];

    *pcaK = caK;

    //- link the intermediary

    mca.pmc = pmc;

    //- create output elements

    pogVm = OutputGeneratorNew("/tmp/output");

    OutputGeneratorInitiate(pogVm);

//d generate output of membrane potential each step

#define HECCER_TEST_INITIATE \
    pdVm = HeccerAddressCompartmentVariable(pheccer, 0, "Vm"); \
    OutputGeneratorAddVariable(pogVm, "Vm", pdVm)

//d generate output of membrane potential each step

#define HECCER_TEST_OUTPUT OutputGeneratorAnnotatedStep(pogVm, sprintf(pcStep, "%i", i) ? pcStep : "sprintf() failed")

    //- do the simulation

    simulate(argc,argv);

    //- finish the simulation output

    OutputGeneratorFinish(pogVm);

    //- add the simulation output to the program output

    WriteOutput("/tmp/output");

    //- return result

    return(iResult);
}


#define main(argc,argv) simulate(argc,argv)

//t this prototype can give warning and perhaps errors.

int main(int argc, char *argv[]);


#include "main.c"


