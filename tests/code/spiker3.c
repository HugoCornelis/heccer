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
#include "../../heccer/event.h"
#include "../../heccer/heccer.h"
#include "../../heccer/output.h"


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


struct Compartment compSource =
{
    //m administrative overhead

    {
	//m type of structure

	MATH_TYPE_Compartment,

#ifdef HECCER_SOURCE_NEUROSPACES

	//m identification

	ADDRESSING_NEUROSPACES_2_HECCER(1000),

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

    -0.065,

/*     double dInject;		 */

    2e-9,

/*     double dRa; */

    360502, // unscaled 2.5,

/*     double dRm; */

    3.58441e+08, // unscaled 1
};


//v a regular delayed rectifier, taken from the genesis website

struct ChannelAct caKdrSource =
{
    //m administrative overhead

    {
	//m type of structure

	MATH_TYPE_ChannelAct,

#ifdef HECCER_SOURCE_NEUROSPACES

	//m identification

	ADDRESSING_NEUROSPACES_2_HECCER(2000),

#endif

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

		    10000,

		    //m 2b: multiplier membrane dependence offset, 0.0 for no dependence

		    0.0,

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

		    //m 2b: multiplier membrane dependence offset, 0.0 for no dependence

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

struct ChannelActInact caiNaFSource =
{
    //m administrative overhead

    {
	//m type of structure

	MATH_TYPE_ChannelActInact,

#ifdef HECCER_SOURCE_NEUROSPACES

	//m identification

	ADDRESSING_NEUROSPACES_2_HECCER(3000),

#endif

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


struct SpikeGenerator sgSource =
{
    //m administrative overhead

    {
	//m type of structure

	MATH_TYPE_SpikeGenerator,

#ifdef HECCER_SOURCE_NEUROSPACES

	//m identification

	ADDRESSING_NEUROSPACES_2_HECCER(4000),

#endif

    },

    //m refractory time

    0.001,

    //m spiking threshold

    0.0,

    //m reset value, FLT_MAX for none

    FLT_MAX,

    //m table in event distributor with targets

    0,
};


int piC2m[] =
{
    3,
    -1,
};


struct MathComponentArray mcaSource =
{
    //m number of math components

    3,

    //m math component data

    NULL,

    //m math component index, initialize to NULL

    NULL,

};


struct Intermediary interSource =
{
    //m compartment array

    1,

    &compSource,

    //m all other mathematical components

    &mcaSource,

    //m compartment 2 first mechanism number

    piC2m,
};


struct Compartment compTarget1 =
{
    //m administrative overhead

    {
	//m type of structure

	MATH_TYPE_Compartment,

#ifdef HECCER_SOURCE_NEUROSPACES

	//m identification

	ADDRESSING_NEUROSPACES_2_HECCER(5000),

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

    -0.065,

/*     double dInject;		 */

    0.0,

/*     double dRa; */

    360502, // unscaled 2.5,

/*     double dRm; */

    3.58441e+08, // unscaled 1
};


//s spring mass channel (synaptic channel)

struct ChannelSpringMass csmTarget1 =
{
    //m administrative overhead

    {
	//m type of structure

	MATH_TYPE_ChannelSpringMass,

#ifdef HECCER_SOURCE_NEUROSPACES

	//m identification

	ADDRESSING_NEUROSPACES_2_HECCER(6000),

#endif

    },

    //m initial reversal potential

    0.0,

    //m get reversal potential from this intermediary, -1 for none

    -1,

    //m maximal conductance

    6.87071723162637e-10,

    //m contributes to this concentration pool, -1 for none, boolean indicator only.

    -1,

    //m random activation frequency

    0.0,

    //m first exponential initial value

    0.0,

    //m second exponential initial value

    0.0,

    //m corresponding index in tables, set to -1 for initialization.

    -1,

    //m event time table (FLT_MAX terminated)

    NULL,

    //m yaml file with event time table, the previous must be NULL.

    //! during compilation, the file is converted to a double array
    //! and fills the previous entry.

    NULL,

    //m parameters

    {
	//m first time constant

	5e-4,

	//m second time constant

	1.2e-3,
    },

};


int piC2mTarget1[] =
{
    1,
    -1,
};


struct MathComponentArray mcaTarget1 =
{
    //m number of math components

    1,

    //m math component data

    &csmTarget1.mc,

    //m math component index, initialize to NULL

    NULL,

};


struct Intermediary interTarget1 =
{
    //m compartment array

    1,

    &compTarget1,

    //m all other mathematical components

    &mcaTarget1,

    //m compartment 2 first mechanism number

    piC2mTarget1,
};


struct Compartment compTarget2 =
{
    //m administrative overhead

    {
	//m type of structure

	MATH_TYPE_Compartment,

#ifdef HECCER_SOURCE_NEUROSPACES

	//m identification

	ADDRESSING_NEUROSPACES_2_HECCER(7000),

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

    -0.065,

/*     double dInject;		 */

    0.0,

/*     double dRa; */

    360502, // unscaled 2.5,

/*     double dRm; */

    3.58441e+08, // unscaled 1
};


//s spring mass channel (synaptic channel)

struct ChannelSpringMass csmTarget2 =
{
    //m administrative overhead

    {
	//m type of structure

	MATH_TYPE_ChannelSpringMass,

#ifdef HECCER_SOURCE_NEUROSPACES

	//m identification

	ADDRESSING_NEUROSPACES_2_HECCER(8000),

#endif

    },

    //m initial reversal potential

    0.0,

    //m get reversal potential from this intermediary, -1 for none

    -1,

    //m maximal conductance

    6.87071723162637e-10,

    //m contributes to this concentration pool, -1 for none, boolean indicator only.

    -1,

    //m random activation frequency

    0.0,

    //m first exponential initial value

    0.0,

    //m second exponential initial value

    0.0,

    //m corresponding index in tables, set to -1 for initialization.

    -1,

    //m event time table (FLT_MAX terminated)

    NULL,

    //m yaml file with event time table, the previous must be NULL.

    //! during compilation, the file is converted to a double array
    //! and fills the previous entry.

    NULL,

    //m parameters

    {
	//m first time constant

	5e-4,

	//m second time constant

	1.2e-3,
    },

};


int piC2mTarget2[] =
{
    1,
    -1,
};


struct MathComponentArray mcaTarget2 =
{
    //m number of math components

    1,

    //m math component data

    &csmTarget2.mc,

    //m math component index, initialize to NULL

    NULL,

};


struct Intermediary interTarget2 =
{
    //m compartment array

    1,

    &compTarget2,

    //m all other mathematical components

    &mcaTarget2,

    //m compartment 2 first mechanism number

    piC2mTarget2,
};


#include "../../heccer/eventdistributor.h"

struct OutputGenerator *pogSpikeSource = NULL;
struct OutputGenerator * pogVmSource = NULL;

/* double *pdVm = NULL; */

char pcStep[100] = "";

/* #include "main.h" */


/* #define main(argc,argv) not_used(argc,argv) */


/* #include "main.c" */


//v accessible from the outside if needed

struct Heccer *pheccerSource = NULL;
struct Heccer *pheccerTarget1 = NULL;
struct Heccer *pheccerTarget2 = NULL;


int main(int argc, char *argv[])
{
    //- set default result : ok

    int iResult = EXIT_SUCCESS;

    //- determine intermediary size, and allocate

    struct MathComponentInfo *pmciKdrSource = MathComponentInfoLookup(caKdrSource.mc.iType);

    struct MathComponentInfo *pmciNaFSource = MathComponentInfoLookup(caiNaFSource.mc.iType);

    struct MathComponentInfo *pmciSpikerSource = MathComponentInfoLookup(sgSource.mc.iType);

    int iCharsSource = pmciKdrSource->iChars + pmciNaFSource->iChars + pmciSpikerSource->iChars;

    void *pmcSource = calloc(sizeof(char), iCharsSource);

    //- prepare the mechanism intermediary

    struct ChannelAct *pcaSource = (struct ChannelAct *)pmcSource;

    *pcaSource = caKdrSource;

    struct ChannelActInact *pcaiSource = (struct ChannelActInact *)&((char *)pcaSource)[pmciKdrSource->iChars];

    *pcaiSource = caiNaFSource;

    struct SpikeGenerator *psgSource = (struct SpikeGenerator *)&((char *)pcaiSource)[pmciNaFSource->iChars];

    *psgSource = sgSource;

    //- link the intermediary

    mcaSource.pmc = pmcSource;

    //- create an output generator

    pogSpikeSource = OutputGeneratorNew("/tmp/output_spike_source");

    //- create output elements

    pogVmSource = OutputGeneratorNew("/tmp/output_vm_source");

//d prepare output of membrane potential and spikes

#define HECCER_TEST_INITIATE \
    double *pdVmSource = HeccerAddressCompartmentVariable(pheccerSource, 0, "Vm"); \
    OutputGeneratorAddVariable(pogVmSource, "Vm", pdVmSource);		\
    double *pdSpikeSource = HeccerAddressMechanismVariable(pheccerSource, 2, "spike"); \
    OutputGeneratorAddVariable(pogSpikeSource, "spike", pdSpikeSource)

//d generate output of membrane potential each step

#define HECCER_TEST_OUTPUT \
    OutputGeneratorAnnotatedStep(pogVmSource, sprintf(pcStep, "%i", i) ? pcStep : "sprintf() failed")

    //- do the simulation

    int simulate(int argc, char *argv[]);

    simulate(argc,argv);

    //- finish the simulation output

    OutputGeneratorFinish(pogVmSource);

    OutputGeneratorFinish(pogSpikeSource);

    //- add the simulation output to the program output

    WriteOutput("/tmp/output_vm_source");

    WriteOutput("/tmp/output_spike_source");

    //- return result

    return(iResult);
}


//o To use this file :
//o
//o set the variable 'inter' to an intermediary representation,
//o #define HECCER_TEST_STEPS 1
//o #define HECCER_TEST_TESTED_THINGS to a dump selection,
//o and so on for the defines below, when not set they get a
//o sensible default value.
//o #include this file, compile, run and parse the output.
//o
//o Heccer construction can also be done using the
//o HECCER_TEST_CONSTRUCT macro, in which case the global variable
//o pheccer must be preallocated.
//o
//o Tests with multiple heccers must not use this file.
//o

#ifndef HECCER_TEST_CONSTRUCT_SOURCE
#define HECCER_TEST_CONSTRUCT_SOURCE \
    memcpy(&pheccerSource->inter, &interSource, sizeof(interSource));	\
    pheccerSource->iStatus = HECCER_STATUS_PHASE_2
#endif

#ifndef HECCER_TEST_CONSTRUCT_TARGET1
#define HECCER_TEST_CONSTRUCT_TARGET1 \
    memcpy(&pheccerTarget1->inter, &interTarget1, sizeof(interTarget1));	\
    pheccerTarget1->iStatus = HECCER_STATUS_PHASE_2
#endif

#ifndef HECCER_TEST_CONSTRUCT_TARGET2
#define HECCER_TEST_CONSTRUCT_TARGET2 \
    memcpy(&pheccerTarget2->inter, &interTarget2, sizeof(interTarget2));	\
    pheccerTarget2->iStatus = HECCER_STATUS_PHASE_2
#endif

#ifndef HECCER_TEST_INITIATE
#define HECCER_TEST_INITIATE ((void)1)
#endif

#ifndef HECCER_TEST_INTERVAL_DEFAULT_START
#define HECCER_TEST_INTERVAL_DEFAULT_START (-0.1)
#endif

#ifndef HECCER_TEST_INTERVAL_DEFAULT_END
#define HECCER_TEST_INTERVAL_DEFAULT_END (0.05)
#endif

#ifndef HECCER_TEST_INTERVAL_DEFAULT_ENTRIES
#define HECCER_TEST_INTERVAL_DEFAULT_ENTRIES 3000
#endif

#ifndef HECCER_TEST_INTERPOL_INTERVAL_DEFAULT_ENTRIES
#define HECCER_TEST_INTERPOL_INTERVAL_DEFAULT_ENTRIES 149
#endif

#ifndef HECCER_TEST_OUTPUT
#define HECCER_TEST_OUTPUT ((void)1)
#endif

#ifndef HECCER_TEST_REPORTING_GRANULARITY
#define HECCER_TEST_REPORTING_GRANULARITY 1
#endif

#ifndef HECCER_TEST_STEPS
#define HECCER_TEST_STEPS 10
#endif

#ifndef HECCER_TEST_TESTED_THINGS
#define HECCER_TEST_TESTED_THINGS HECCER_DUMP_ALL
#endif

#ifndef HECCER_TEST_TIME_GRANULARITY
#define HECCER_TEST_TIME_GRANULARITY (1e-9)
#endif

#ifndef HECCER_TEST_TIME_STEP
#define HECCER_TEST_TIME_STEP (2e-5)
#endif


int WriteOutput(char *pcFilename);

int WriteOutput(char *pcFilename)
{
    //- set default result : ok

    int iResult = 1;

    //- copy the file content to stdout

    FILE *pfile = fopen(pcFilename, "r");

    char pc[10000];

    size_t st = fread(pc, sizeof(char), sizeof(pc), pfile);

    while (st == 10000)
    {
	fwrite(pc, sizeof(char), st, stdout);

	st = fread(pc, sizeof(char), sizeof(pc), pfile);
    }

    fwrite(pc, sizeof(char), st, stdout);

    //- return result

    return(iResult);
}


int simulate(int argc, char *argv[]);

int simulate(int argc, char *argv[])
{
    //t use argv for heccer options

    //- set default result : ok

    int iResult = EXIT_SUCCESS;

    //- construct a connection matrix for the event distributor

    struct EventQueuerMatrix peqm[] =
	{
	    //! for target heccer 1

	    {
		//m target object, a solver or so

		NULL,

		//m target object, an index into a array of double ?

		4,

		//m connection delay

		0.001,

		//m connection weight

		1.0,

		//m called function

		HeccerEventSet,
	    },

	    //! for target heccer 2

	    {
		//m target object, a solver or so

		NULL,

		//m target object, an index into a array of double ?

		4,

		//m connection delay

		0.002,

		//m connection weight

		2.0,

		//m called function

		HeccerEventSet,
	    },

	    //! terminator

	    {
		//m target object, a solver or so

		NULL,

		//m target object, an index into a array of double ?

		0,

		//m connection delay

		FLT_MAX,

		//m connection weight

		FLT_MAX,

		//m called function

		NULL,
	    },

	};

    //- allocate event queuer

    struct EventQueuer *peq = EventQueuerNew(peqm);

    //- initialize the serial to connection matrix index convertor

    if (!EventQueuerSerial2ConnectionIndexAdd(peq, 6000, 0))
    {
	exit(1);
    }

    if (!EventQueuerSerial2ConnectionIndexAdd(peq, 8000, 1))
    {
	exit(2);
    }

    if (!EventQueuerSerial2ConnectionIndexSort(peq))
    {
	exit(3);
    }

    //- construct a connection matrix for the event distributor

    struct EventDistributorMatrix pedm[] =
	{
	    //! for HeccerOutput object

	    {
		//m target object, a solver, a HeccerOutput, or so

		pogSpikeSource,

		//m target subcomponent identification

		-1,

		//m called function

		OutputGeneratorTimedStep,

		//m serial in the model container

		-1,
	    },

	    //! for event queuer

	    {
		//m target object, a solver, a HeccerOutput, or so

		peq, // &peqm[0],

		//m target subcomponent identification

		0,

		//m called function

		EventQueuerEnqueue,

		//m serial in the model container

		-1,
	    },

	    //! terminator

	    {
		//m target object, a solver, a HeccerOutput, or so

		NULL,

		//m target subcomponent identification

		-1,

		//m called function

		NULL,

		//m serial in the model container

		-1,
	    },

	};

    struct EventDistributorData edd =
	{
	    //m number of connections in the matrix

	    3,

	    //m last used

	    2,

	    //m array of targets

	    pedm,
	};


    //- allocate event distributor

    struct EventDistributor *ped = EventDistributorNew(&edd);

    //- allocate the heccer, for the event distributor service

    //! the source is constructed overhere and further initialized in simulate(),
    //! the targets are constructed in simulate() only.  Needs to be cleaned up.

    pheccerSource = HeccerNew("source", NULL, ped, NULL);

    pheccerTarget1 = HeccerNew("target1", NULL, NULL, peq);

    pheccerTarget2 = HeccerNew("target2", NULL, NULL, peq);

    //- instantiate a heccer with an initialized intermediary

    //! note: test definition is allowed to allocate the heccer, with services.

    if (!pheccerSource)
    {
	pheccerSource = HeccerNewP2("source", &interSource);
    }
    else
    {
	HECCER_TEST_CONSTRUCT_SOURCE;
    }

    //- instantiate a heccer with an initialized intermediary

    //! note: test definition is allowed to allocate the heccer, with services.

    if (!pheccerTarget1)
    {
	pheccerTarget1 = HeccerNewP2("target1", &interTarget1);
    }
    else
    {
	HECCER_TEST_CONSTRUCT_TARGET1;
    }

    //- instantiate a heccer with an initialized intermediary

    //! note: test definition is allowed to allocate the heccer, with services.

    if (!pheccerTarget2)
    {
	pheccerTarget2 = HeccerNewP2("target2", &interTarget2);
    }
    else
    {
	HECCER_TEST_CONSTRUCT_TARGET2;
    }

    //t need sensible API to set options I guess.

    pheccerSource->dStep = HECCER_TEST_TIME_STEP;

    pheccerSource->ho.dIntervalStart = HECCER_TEST_INTERVAL_DEFAULT_START;

    pheccerSource->ho.dIntervalEnd = HECCER_TEST_INTERVAL_DEFAULT_END;

    //t should set test defaults for basal activator tables.

/*     pheccerSource->ho.dBasalActivatorStart = HECCER_TEST_INTERVAL_DEFAULT_START; */

/*     pheccerSource->ho.dBasalActivatorEnd = HECCER_TEST_INTERVAL_DEFAULT_END; */

    pheccerSource->ho.iIntervalEntries = HECCER_TEST_INTERVAL_DEFAULT_ENTRIES;

    pheccerSource->ho.iSmallTableSize = HECCER_TEST_INTERPOL_INTERVAL_DEFAULT_ENTRIES;

    //- build indices for optimization

    HeccerCompileP2(pheccerSource);

    //- compile to byte code

    HeccerCompileP3(pheccerSource);

    //- initiate values

    HeccerInitiate(pheccerSource);

    //t need sensible API to set options I guess.

    pheccerTarget1->dStep = HECCER_TEST_TIME_STEP;

    pheccerTarget1->ho.dIntervalStart = HECCER_TEST_INTERVAL_DEFAULT_START;

    pheccerTarget1->ho.dIntervalEnd = HECCER_TEST_INTERVAL_DEFAULT_END;

    //t should set test defaults for basal activator tables.

/*     pheccerTarget1->ho.dBasalActivatorStart = HECCER_TEST_INTERVAL_DEFAULT_START; */

/*     pheccerTarget1->ho.dBasalActivatorEnd = HECCER_TEST_INTERVAL_DEFAULT_END; */

    pheccerTarget1->ho.iIntervalEntries = HECCER_TEST_INTERVAL_DEFAULT_ENTRIES;

    pheccerTarget1->ho.iSmallTableSize = HECCER_TEST_INTERPOL_INTERVAL_DEFAULT_ENTRIES;

    //- build indices for optimization

    HeccerCompileP2(pheccerTarget1);

    //- compile to byte code

    HeccerCompileP3(pheccerTarget1);

    //- initiate values

    HeccerInitiate(pheccerTarget1);

    //t need sensible API to set options I guess.

    pheccerTarget2->dStep = HECCER_TEST_TIME_STEP;

    pheccerTarget2->ho.dIntervalStart = HECCER_TEST_INTERVAL_DEFAULT_START;

    pheccerTarget2->ho.dIntervalEnd = HECCER_TEST_INTERVAL_DEFAULT_END;

    //t should set test defaults for basal activator tables.

/*     pheccerTarget2->ho.dBasalActivatorStart = HECCER_TEST_INTERVAL_DEFAULT_START; */

/*     pheccerTarget2->ho.dBasalActivatorEnd = HECCER_TEST_INTERVAL_DEFAULT_END; */

    pheccerTarget2->ho.iIntervalEntries = HECCER_TEST_INTERVAL_DEFAULT_ENTRIES;

    pheccerTarget2->ho.iSmallTableSize = HECCER_TEST_INTERPOL_INTERVAL_DEFAULT_ENTRIES;

    //- build indices for optimization

    HeccerCompileP2(pheccerTarget2);

    //- compile to byte code

    HeccerCompileP3(pheccerTarget2);

    //- initiate values

    HeccerInitiate(pheccerTarget2);

    //- link event queuer to springmass of target 1

    //! see also above, same developer comment

    peqm[0].pvObject = pheccerTarget1;

    //- link event queuer to springmass of target 2

    //! see also above, same developer comment

    peqm[1].pvObject = pheccerTarget2;

    //- initialize test specific things

    HECCER_TEST_INITIATE;

    //- initial dump

    //! funny : the first '---' in the output are taken as an option
    //! by Expect.pm, which complicates testing a bit.  So just
    //! removed.

/*     fprintf(stdout, "-------\n"); */

    HECCER_TEST_TESTED_THINGS && fprintf(stdout, "Initiated\n");

    HECCER_TEST_TESTED_THINGS && HeccerDump(pheccerSource, stdout, HECCER_TEST_TESTED_THINGS);

    HECCER_TEST_TESTED_THINGS && HeccerDump(pheccerTarget1, stdout, HECCER_TEST_TESTED_THINGS);

    HECCER_TEST_TESTED_THINGS && HeccerDump(pheccerTarget2, stdout, HECCER_TEST_TESTED_THINGS);

    //v final report needed ?

    int iFinalReport = 0;

    //- a couple of times

    int i;

    for (i = 0; i < HECCER_TEST_STEPS ; i++)
    {
	//- update the current simulation time.

	double dSimulationTime = i * HECCER_TEST_TIME_STEP + HECCER_TEST_TIME_GRANULARITY;

	//- step

	HeccerHeccs(pheccerSource, dSimulationTime);

	HeccerHeccs(pheccerTarget1, dSimulationTime);

	HeccerHeccs(pheccerTarget2, dSimulationTime);

	EventQueuerProcess(peq);

	//- generate user specified output

	HECCER_TEST_OUTPUT;

	//- dump

	if (i % HECCER_TEST_REPORTING_GRANULARITY == 0)
	{
	    HECCER_TEST_TESTED_THINGS && fprintf(stdout, "-------\n");

	    HECCER_TEST_TESTED_THINGS && fprintf(stdout, "Iteration %i\n", i);

	    HECCER_TEST_TESTED_THINGS && HeccerDump(pheccerSource, stdout, HECCER_TEST_TESTED_THINGS);

	    HECCER_TEST_TESTED_THINGS && HeccerDump(pheccerTarget1, stdout, HECCER_TEST_TESTED_THINGS);

	    HECCER_TEST_TESTED_THINGS && HeccerDump(pheccerTarget2, stdout, HECCER_TEST_TESTED_THINGS);
	}
	else
	{
	    iFinalReport = 1;
	}
    }

    //- add a final report if necessary

    if (iFinalReport)
    {
	HECCER_TEST_TESTED_THINGS && fprintf(stdout, "-------\n");

	HECCER_TEST_TESTED_THINGS && fprintf(stdout, "Final Iteration\n", i);

	HECCER_TEST_TESTED_THINGS && HeccerDump(pheccerSource, stdout, HECCER_TEST_TESTED_THINGS);

	HECCER_TEST_TESTED_THINGS && HeccerDump(pheccerTarget1, stdout, HECCER_TEST_TESTED_THINGS);

	HECCER_TEST_TESTED_THINGS && HeccerDump(pheccerTarget2, stdout, HECCER_TEST_TESTED_THINGS);
    }

    //- return result

    return(iResult);
}


