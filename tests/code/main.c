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


#include <stdio.h>
#include <stdlib.h>


#include "main.h"


//v accessible from the outside if needed

struct Heccer *pheccer = NULL;

struct VClamp *pvc = NULL;


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

#ifndef HECCER_TEST_CONSTRUCT
#define HECCER_TEST_CONSTRUCT \
    memcpy(&pheccer->inter, &inter, sizeof(inter));	\
    pheccer->iStatus = HECCER_STATUS_PHASE_2
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

#ifndef HECCER_TEST_SCHEDULE
#define HECCER_TEST_SCHEDULE ((void)1)
#endif

#ifndef HECCER_TEST_STEPS
#define HECCER_TEST_STEPS 10
#endif

#ifndef HECCER_TEST_TESTED_THINGS
#define HECCER_TEST_TESTED_THINGS HECCER_DUMP_ALL
#endif

#ifndef HECCER_TEST_TIME_STEP
#define HECCER_TEST_TIME_STEP (2e-5)
#endif


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


int main(int argc, char *argv[])
{
    //t use argv for heccer options

    //- set default result : ok

    int iResult = EXIT_SUCCESS;

    //- instantiate a heccer with an initialized intermediary

    //! note: test definition is allowed to allocate the heccer, with services.

    if (!pheccer)
    {
	pheccer = HeccerNewP2(&inter);
    }
    else
    {
	HECCER_TEST_CONSTRUCT;
    }

    //t need sensible API to set options I guess.

    pheccer->dStep = HECCER_TEST_TIME_STEP;

    pheccer->ho.dIntervalStart = HECCER_TEST_INTERVAL_DEFAULT_START;

    pheccer->ho.dIntervalEnd = HECCER_TEST_INTERVAL_DEFAULT_END;

    //t should set test defaults for basal activator tables.

/*     pheccer->ho.dBasalActivatorStart = HECCER_TEST_INTERVAL_DEFAULT_START; */

/*     pheccer->ho.dBasalActivatorEnd = HECCER_TEST_INTERVAL_DEFAULT_END; */

    pheccer->ho.iIntervalEntries = HECCER_TEST_INTERVAL_DEFAULT_ENTRIES;

    pheccer->ho.iSmallTableSize = HECCER_TEST_INTERPOL_INTERVAL_DEFAULT_ENTRIES;

    //- build indices for optimization

    HeccerCompileP2(pheccer);

    //- compile to byte code

    HeccerCompileP3(pheccer);

    //- initiate values

    HeccerInitiate(pheccer);

    //- initialize test specific things

    HECCER_TEST_INITIATE;

    //- initial dump

    //! funny : the first '---' in the output are taken as an option
    //! by Expect.pm, which complicates testing a bit.  So just
    //! removed.

/*     fprintf(stdout, "-------\n"); */

    HECCER_TEST_TESTED_THINGS && fprintf(stdout, "Initiated\n");

    HECCER_TEST_TESTED_THINGS && HeccerDump(pheccer, stdout, HECCER_TEST_TESTED_THINGS);

    //v final report needed ?

    int iFinalReport = 0;

    //- a couple of times

    int i;

    for (i = 0; i < HECCER_TEST_STEPS ; i++)
    {
	//- update the current simulation time.

	double dSimulationTime = (i + 1) * HECCER_TEST_TIME_STEP;

	//- step

	HeccerHecc(pheccer);

	//- schedule other objects

	HECCER_TEST_SCHEDULE;

	//- generate user specified output

	HECCER_TEST_OUTPUT;

	//- dump

	if (i % HECCER_TEST_REPORTING_GRANULARITY == 0)
	{
	    HECCER_TEST_TESTED_THINGS && fprintf(stdout, "-------\n");

	    HECCER_TEST_TESTED_THINGS && fprintf(stdout, "Iteration %i\n", i);

	    HECCER_TEST_TESTED_THINGS && HeccerDump(pheccer, stdout, HECCER_TEST_TESTED_THINGS);
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

	HECCER_TEST_TESTED_THINGS && HeccerDump(pheccer, stdout, HECCER_TEST_TESTED_THINGS);
    }

    //- return result

    return(iResult);
}


