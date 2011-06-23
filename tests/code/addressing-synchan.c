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


#include <stdio.h>
#include <stdlib.h>

#include <experiment/output.h>

#include "../../heccer/addressing.h"
#include "../../heccer/compartment.h"
#include "../../heccer/heccer.h"


#define HECCER_TEST_REPORTING_GRANULARITY 2000
#define HECCER_TEST_STEPS 30
#define HECCER_TEST_TIME_STEP (1e-5)


struct Compartment pcomp[] =
{
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

	//m descriptive values, alphabetical order

/*     double dCm; */

	4.57537e-11, // unscaled 0.0164,

/*     double dEm; */

	-0.08,

/*     double dInitVm; */

	-0.08,

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

#ifdef HECCER_SOURCE_NEUROSPACES

	    //m identification

	    ADDRESSING_NEUROSPACES_2_HECCER(1500),

#endif

	},

	//m index of parent compartment, -1 for none

	0,

	//m descriptive values, alphabetical order

/*     double dCm; */

	5.755329373e-12, // unscaled 0.0164,

/*     double dEm; */

	-0.08,

/*     double dInitVm; */

	-0.08,

/*     double dInject;		 */

	0,

/*     double dRa; */

	772813.4375, // unscaled 2.5,

/*     double dRm; */

	8.548598272e9, // unscaled 3
    },
};


double pdEvents[] =
{
    0.0001,
    DBL_MAX,
};


//s spring mass channel (synaptic channel)

struct ChannelSpringMass csm =
{
    //m administrative overhead

    {
	//m type of structure

	MATH_TYPE_ChannelSpringMass,

#ifdef HECCER_SOURCE_NEUROSPACES

	//m identification

	ADDRESSING_NEUROSPACES_2_HECCER(2000),

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

    0.0001,

    //m first exponential initial value

    0.0,

    //m second exponential initial value

    0.0,

    //m corresponding index in tables, set to -1 for initialization.

    -1,

    //m event time table (DBL_MAX terminated)

    pdEvents,

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


int piC2m[] =
{
    0,
    1,
    -1,
};


struct MathComponentArray mca =
{
    //m number of math components

    1,

    //m math component data

    &csm.mc,

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

#ifdef HECCER_SOURCE_NEUROSPACES

    //m identification of the originator, mostly a cell or cell
    //m population, but perhaps just a segment vector

    //m start range

    ADDRESSING_NEUROSPACES_2_HECCER(1000 - 1),

    //m end range

    ADDRESSING_NEUROSPACES_2_HECCER(9000),

#endif

};


struct OutputGenerator * pogActivation = NULL;

struct OutputGenerator * pogNextEvent = NULL;

double *pdActivation = NULL;

double *pdNextEvent = NULL;

char pcStep[100] = "";

#include "main.h"


int main(int argc, char *argv[])
{
    //- set default result : ok

    int iResult = EXIT_SUCCESS;

#ifdef HECCER_SOURCE_NEUROSPACES

    //- create output elements

    pogActivation = OutputGeneratorNew("/tmp/output");

    OutputGeneratorInitiate(pogActivation);

    pogNextEvent = OutputGeneratorNew("/tmp/output2");

    OutputGeneratorInitiate(pogNextEvent);

//d generate output of membrane potential each step

#define HECCER_TEST_INITIATE \
    pdActivation = HeccerAddressVariable(pheccer, 2000, "activation"); \
    OutputGeneratorAddVariable(pogActivation, "Activation", pdActivation); \
    pdNextEvent = HeccerAddressVariable(pheccer, 2000, "next_event"); \
    OutputGeneratorAddVariable(pogNextEvent, "NextEvent", pdNextEvent)

//d generate output of membrane potential each step

#define HECCER_TEST_OUTPUT OutputGeneratorAnnotatedStep(pogActivation, sprintf(pcStep, "%i", i) ? pcStep : "sprintf() failed"); OutputGeneratorAnnotatedStep(pogNextEvent, sprintf(pcStep, "%i", i) ? pcStep : "sprintf() failed")

#endif

    //- do the simulation

    simulate(argc,argv);

#ifdef HECCER_SOURCE_NEUROSPACES

    //- finish the simulation output

    OutputGeneratorFinish(pogActivation);

    OutputGeneratorFinish(pogNextEvent);

    //- add the simulation output to the program output

    WriteOutput("/tmp/output");

    WriteOutput("/tmp/output2");

#endif


#ifdef HECCER_SOURCE_NEUROSPACES

    //- address variables via the external ids

    double *pdVmExternal = HeccerAddressVariable(pheccer, 1000, "Vm");

    double *pdActivationExternal = HeccerAddressVariable(pheccer, 2000, "activation");

    double *pdNextEventExternal = HeccerAddressVariable(pheccer, 2000, "next_event");

/*     double *pdFrequencyExternal = HeccerAddressVariable(pheccer, 2000, "FREQUENCY"); */

#endif

    //- address variables via the internal indices

    double *pdVmInternal = HeccerAddressCompartmentVariable(pheccer, 0, "Vm");

    double *pdActivationInternal = HeccerAddressMechanismVariable(pheccer, 0, "activation");

    double *pdNextEventInternal = HeccerAddressVariable(pheccer, 2000, "next_event");

/*     double *pdFrequencyInternal = HeccerAddressMechanismVariable(pheccer, 2000, "FREQUENCY"); */

#ifdef HECCER_SOURCE_NEUROSPACES

    if (pdVmInternal != pdVmExternal)
    {
	fprintf(stdout, "*** Error: (pdVmInternal != pdVmExternal)\n");

	exit(EXIT_FAILURE);
    }

    if (pdActivationInternal != pdActivationExternal)
    {
	fprintf(stdout, "*** Error: (pdActivationInternal != pdActivationExternal)\n");

	exit(EXIT_FAILURE);
    }

    if (pdNextEventExternal != pdNextEventInternal)
    {
	fprintf(stdout, "*** Error: (pdNextEventExternal != pdNextEventInternal)\n");

	exit(EXIT_FAILURE);
    }

/*     if (pdFrequencyExternal != pdFrequencyInternal) */
/*     { */
/* 	fprintf(stdout, "*** Error: (pdFrequencyExternal != pdFrequencyInternal)\n"); */

/* 	exit(EXIT_FAILURE); */
/*     } */

#endif

    fprintf(stdout, "Membrane potential is %g\n", pdVmInternal[0]);

    fprintf(stdout, "Activation state is %g\n", pdActivationInternal[0]);

    fprintf(stdout, "next event time is %g\n", pdNextEventInternal[0]);

/*     fprintf(stdout, "activation frequency is %g\n", pdFrequencyInternal[0]); */

    //- return result

    return(iResult);
}


#define main(argc,argv) simulate(argc,argv)

//t this prototype can give warning and perhaps errors.

int main(int argc, char *argv[]);


#include "main.c"


