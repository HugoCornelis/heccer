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

#include "../../heccer/addressing.h"
#include "../../heccer/compartment.h"
#include "../../heccer/heccer.h"
#include "../../heccer/output.h"


#define HECCER_TEST_CONSTRUCT \
    memcpy(&pheccer->inter, &inter, sizeof(inter));	\
    pheccer->iStatus = HECCER_STATUS_PHASE_2
#define HECCER_TEST_REPORTING_GRANULARITY 10000
#define HECCER_TEST_STEPS 10000
#define HECCER_TEST_TESTED_THINGS ( HECCER_DUMP_VM_COMPARTMENT_MATRIX \
				    | HECCER_DUMP_VM_COMPARTMENT_DATA \
				    | HECCER_DUMP_VM_COMPARTMENT_OPERATIONS \
				    | HECCER_DUMP_VM_MECHANISM_DATA \
				    | HECCER_DUMP_VM_MECHANISM_OPERATIONS \
				    | HECCER_DUMP_VM_SUMMARY \
	)
#define HECCER_TEST_TIME_STEP (1e-6)


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

    -0.065,

/*     double dInject;		 */

    2e-9,

/*     double dRa; */

    360502, // unscaled 2.5,

/*     double dRm; */

    3.58441e+08, // unscaled 1
};


//v a regular delayed rectifier, taken from the genesis website

struct ChannelAct caKdr =
{
    //m administrative overhead

    {
	//m type of structure

	MATH_TYPE_ChannelAct,
    },

    //m first set of descriptive values, alphabetical order

    //m initial reversal potential

    -0.085,

    //m get reversal potential from this intermediary, -1 for none

    -1,

    //m maximal conductance when all channels are permissive

    1.004349542e-06,

    //m contributes to this concentration pool, -1 for none, boolean indicator only.

    -1,

    //m activation description

    {
	//m power, for a standard heccer, something between 1 and 4 or so.

	4,

	//m gate definition

	{
	    //m initial value, commonly forward over backward steady states

	    0.3176769506,

	    //m corresponding index in tables, set to -1 for initialization.

	    -1,

	    {
		//m forward kinetiks, commonly denoted with alpha or non-perm to perm rate

		{
		    //m multiplier

		    -550.0,

		    //m multiplier membrane dependence, 0.0 for no dependence

		    -10000,

		    //m choose between nominator or denominator, 1 means nominator, -1
		    //m means denominator

		    -1.0,

		    //m nominator or denominator offset

		    -1.0,

		    //m membrane offset

		    0.055,

		    //m denormalized time constant

		    -0.01,
		},

		//m backward kinetiks, commonly denoted with beta or perm to non-perm rate

		{
		    //m multiplier

		    125.0,

		    //m multiplier membrane dependence, 0.0 for no dependence

		    0.0,

		    //m choose between nominator or denominator, 1 means nominator, -1
		    //m means denominator

		    -1.0,

		    //m nominator or denominator offset

		    0.0,

		    //m membrane offset

		    0.065,

		    //m denormalized time constant

		    0.08,
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
    },

    //m first set of descriptive values, alphabetical order

    //m initial reversal potential

    0.045,

    //m get reversal potential from this intermediary, -1 for none

    -1,

    //m maximal conductance when all channels are permissive

    0.00001,

    //m contributes to this concentration pool, -1 for none, boolean indicator only.

    -1,

    //m activation description

    {
	//m power, for a standard heccer, something between 1 and 4 or so.

	3,

	//m gate definition

	{
	    //m initial value, commonly forward over backward steady states

	    0.01224204035,

	    //m corresponding index in tables, set to -1 for initialization.

	    -1,

	    {
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
    },

    //m inactivation description

    {
	//m power, for a standard heccer, something between 1 and 4 or so.

	1,

	//m gate definition

	{
	    //m initial value, commonly forward over backward steady states

	    0.1930685015,

	    //m corresponding index in tables, set to -1 for initialization.

	    -1,

	    {
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
    },
};


struct SpikeGenerator sg =
{
    //m administrative overhead

    {
	//m type of structure

	MATH_TYPE_SpikeGenerator,

#ifdef HECCER_SOURCE_NEUROSPACES

	//m identification

	ADDRESSING_NEUROSPACES_2_HECCER(1000),

#endif

    },

    //m refractory time

    0.001,

    //m spiking threshold

    0.0,

    //m table in event distributor with targets

    0,
};


int piC2m[] =
{
    3,
    -1,
};


struct MathComponentArray mca =
{
    //m number of math components

    3,

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


#include "../../heccer/eventdistributor.h"

struct EventDistributorMatrix pedm[] =
{
    {
	NULL,
	-1,
	NULL,
    },
    {
	NULL,
	-1,
	NULL,
    },
};

struct EventDistributorData edd =
{
    0,

    //m array of targets

    pedm,
};


struct EventDistributor ed =
{
    //m service specific data

    &edd,

    //m distribute an event over the targets

    EventDistributorSend,
};


struct OutputGenerator *pogSpike = NULL;
struct OutputGenerator * pogVm = NULL;

/* double *pdVm = NULL; */

char pcStep[100] = "";

#include "main.h"


int main(int argc, char *argv[])
{
    //- set default result : ok

    int iResult = EXIT_SUCCESS;

    //- determine intermediary size, and allocate

    struct MathComponentInfo *pmciKdr = MathComponentInfoLookup(caKdr.mc.iType);

    struct MathComponentInfo *pmciNaF = MathComponentInfoLookup(caiNaF.mc.iType);

    struct MathComponentInfo *pmciSpiker = MathComponentInfoLookup(sg.mc.iType);

    int iChars = pmciKdr->iChars + pmciNaF->iChars + pmciSpiker->iChars;

    void *pmc = calloc(sizeof(char), iChars);

    //- prepare the mechanism intermediary

    struct ChannelAct *pca = (struct ChannelAct *)pmc;

    *pca = caKdr;

    struct ChannelActInact *pcai = (struct ChannelActInact *)&((char *)pca)[pmciKdr->iChars];

    *pcai = caiNaF;

    struct SpikeGenerator *psg = (struct SpikeGenerator *)&((char *)pcai)[pmciNaF->iChars];

    *psg = sg;

    //- link the intermediary

    mca.pmc = pmc;

    //- link spiking element to output generator

    pogSpike = OutputGeneratorNew("/tmp/output_spike");

    pedm[0].pvObject = pogSpike;
    pedm[0].pvFunction = OutputGeneratorTimedStep;

    //- create output elements

    pogVm = OutputGeneratorNew("/tmp/output_vm");

//d prepare output of membrane potential and spikes

#define HECCER_TEST_INITIATE \
    double *pdVm = HeccerAddressCompartmentVariable(pheccer, 0, "Vm");	\
    OutputGeneratorAddVariable(pogVm, "Vm", pdVm);			\
    double *pdSpike = HeccerAddressMechanismVariable(pheccer, 2, "spike"); \
    OutputGeneratorAddVariable(pogSpike, "spike", pdSpike)

//d generate output of membrane potential each step

#define HECCER_TEST_OUTPUT \
    OutputGeneratorAnnotatedStep(pogVm, sprintf(pcStep, "%i", i) ? pcStep : "sprintf() failed")

    //- allocate the heccer, for the event distributor service

    pheccer = HeccerNew(NULL, &ed, NULL);

    //- do the simulation

    simulate(argc,argv);

    //- finish the simulation output

    OutputGeneratorFinish(pogVm);

    OutputGeneratorFinish(pogSpike);

    //- add the simulation output to the program output

    WriteOutput("/tmp/output_vm");

    WriteOutput("/tmp/output_spike");

    //- return result

    return(iResult);
}


#define main(argc,argv) simulate(argc,argv)

//t this prototype can give warning and perhaps errors.

int main(int argc, char *argv[]);


#include "main.c"


