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
#include <stdio.h>
#include <string.h>

#include "heccer/heccer.h"


/// **************************************************************************
///
/// SHORT: HeccerCompileP1()
///
/// ARGS.:
///
///	pheccer...: a heccer.
///
/// RTN..: int
///
///	success of operation.
///
/// DESCR: Compile a model into an intermediary format.
///
/// **************************************************************************

int HeccerCompileP1(struct Heccer *pheccer)
{
    //- set default result : ok

    int iResult = FALSE;

    //t build up intermediary using the available service

    //t 1. need compartment stream
    //t 2. need mechanism stream
    //t 3. need pool stream

    //- return result

    return(iResult);
}


/// **************************************************************************
///
/// SHORT: HeccerCompileP2()
///
/// ARGS.:
///
///	pheccer...: a heccer.
///
/// RTN..: int
///
///	success of operation.
///
/// DESCR: Analyze the model, build indices for optimization.
///
///	Internally, Heccer addresses mechanisms using their
///	compartment's schedule number.  So the minimum degree
///	algorithm must run first before the mechanisms can be
///	compiled.
///
/// NOTE.:
///
///	This function can be used for testing internals of heccer,
///	just be sure to provide a consistent intermediary image.
///
/// **************************************************************************

int HeccerCompileP2(struct Heccer *pheccer)
{
    //- set default result : ok

    int iResult = TRUE;

    //- do minimum degree

    iResult = iResult && HeccerMinimumDegree(pheccer);

    //- index & sort mechanisms

    iResult = iResult && HeccerMechanismSort(pheccer);

    //- return result

    return(iResult);
}


/// **************************************************************************
///
/// SHORT: HeccerCompileP3()
///
/// ARGS.:
///
///	pheccer...: a heccer.
///
/// RTN..: int
///
///	success of operation.
///
/// DESCR: Compile the intermediary format into byte code.
///
///	 Uses indices, initialized with HeccerCompileP2().
///
/// NOTE.:
///
///	This function can be used for testing internals of heccer,
///	just be sure to provide a consistent intermediary image.
///
/// **************************************************************************

int HeccerCompileP3(struct Heccer *pheccer)
{
    //- set default result : ok

    int iResult = TRUE;

    //- compile compartments to byte code

    iResult = iResult && HeccerCompartmentCompile(pheccer);

    //- compile mechanisms to byte code

    iResult = iResult && HeccerMechanismCompile(pheccer);

    //- link mechanisms

    iResult = iResult && HeccerMechanismLink(pheccer);

    //t perhaps should discretize channels overhere ?

    //- return result

    return(iResult);
}


/// **************************************************************************
///
/// SHORT: HeccerDump()
///
/// ARGS.:
///
///	pheccer...: a heccer.
///	pfile.....: stdio file.
///	iSelection: selection to dump.
///
/// RTN..: int
///
///	success of operation.
///
/// DESCR: Call the dump functions, with the given selection.
///
///	The selection is the boolean or of zero or more of the following :
///
///
///
///	The shorthand HECCER_DUMP_ALL selects everything.
///
/// **************************************************************************

int HeccerDumpV(struct Heccer *pheccer)
{
    return(HeccerDump(pheccer, stdout, HECCER_DUMP_ALL));
}

int HeccerDump(struct Heccer *pheccer, FILE *pfile, int iSelection)
{
    //- set default result : ok

    int iResult = TRUE;

    if (!pfile)
    {
	pfile = stdout;
    }

    //- status : reflects phases of compilation.

    fprintf(pfile, "Heccer (iStatus) : (%i)\n", pheccer->iStatus);

    //- options and operation mode.

    fprintf(pfile, "Heccer Options (iOptions) : (%i)\n", pheccer->ho.iOptions);

    fprintf(pfile, "Heccer Options (dIntervalStart) : (%g)\n", pheccer->ho.dIntervalStart);

    fprintf(pfile, "Heccer Options (dIntervalEnd) : (%g)\n", pheccer->ho.dIntervalEnd);

    fprintf(pfile, "Heccer Options (dBasalActivatorStart) : (%g)\n", pheccer->ho.dBasalActivatorStart);

    fprintf(pfile, "Heccer Options (dBasalActivatorEnd) : (%g)\n", pheccer->ho.dBasalActivatorEnd);

    fprintf(pfile, "Heccer Options (iIntervalEntries) : (%i)\n", pheccer->ho.iIntervalEntries);

    //- simulation time

    fprintf(pfile, "Heccer (dTime) : (%g)\n", pheccer->dTime);

    //- time step

    fprintf(pfile, "Heccer (dStep) : (%g)\n", pheccer->dStep);

    //- identification service : translates serials to math components

    fprintf(pfile, "Heccer (pvService) : (%p)\n", pheccer->pvService);

    //- dump intermediary

    iResult = iResult && HeccerIntermediaryDump(&pheccer->inter, pfile, iSelection);

    //- dump the indices

    iResult = iResult && HeccerIndexersDump(&pheccer->indexers, pfile, iSelection);

    //- dump the tables

    iResult = iResult && HeccerTablesDump(&pheccer->tgt, pfile, iSelection);

    //- dump compartment arrays

    iResult = iResult && HeccerVMDump(&pheccer->vm, pfile, iSelection);

    //- flush output

    fflush(pfile);

    //- return result

    return(iResult);
}


/// **************************************************************************
///
/// SHORT: HeccerHecc()
///
/// ARGS.:
///
/// RTN..: char *
///
///	Version identifier.
///
/// DESCR: Obtain version identifier.
///
/// **************************************************************************

char * HeccerGetVersion(void)
{
    // $Format: "    static char *pcVersion=\"${label}\";"$
    static char *pcVersion="pools-10-pre-release";

    return(pcVersion);
}


/// **************************************************************************
///
/// SHORT: HeccerHecc()
///
/// ARGS.:
///
///	pheccer...: a heccer.
///
/// RTN..: int
///
///	success of operation.
///
/// DESCR: Compute one step of simulation time.
///
/// **************************************************************************

int HeccerHecc(struct Heccer *pheccer)
{
    //- set default result : ok

    int iResult = TRUE;

    //- update the simulation time

    pheccer->dTime += pheccer->dStep;

    //! I am undecided where to make the difference between CN and BE.
    //! From cosmetic viewpoint, here we should only delegate to
    //! HeccerMechanismHecc() and HeccerCompartmentHecc().
    //! Then the difference can be made by looking at the options
    //! (bad~?), or by having byte-code generated for the two specific
    //! cases (slower~?).

    //! On the other hand, this is less work for the moment and delays
    //! the decisions involved in the above (perhaps even unnecessary
    //! to be made~?).

    //- perform mechanism operations (including concentration pools)

    //! doing it like this, assumes that the mechanism values are
    //! correctly given to HeccerInitiate() at time (now - dt/2).  Does
    //! not make a practical difference.

    iResult = iResult && HeccerMechanismSolveCN(pheccer);

    //- perform the compartment operations

    if (pheccer->vm.iVms != 1)
    {
	iResult = iResult && HeccerCompartmentSolveCN(pheccer);
    }

    //- return result

    return(iResult);
}


/// **************************************************************************
///
/// SHORT: HeccerHeccs()
///
/// ARGS.:
///
///	pheccer...: a heccer.
///	dTime.....: current time.
///
/// RTN..: int
///
///	success of operation.
///
/// DESCR: Call HeccerHecc() until dTime.
///
/// **************************************************************************

int HeccerHeccs(struct Heccer *pheccer, double dTime)
{
    //- set default result : ok

    int iResult = TRUE;

    //- while not reached simulation time

    while (pheccer->dTime < dTime)
    {
	//- do a single hecc

	iResult = iResult && HeccerHecc(pheccer);

	//! perhaps should move the advance of the local time to this
	//! point ?  Would allow to remove this test ...
	//! I don't care for the moment.

	if (iResult == FALSE)
	{
	    return(iResult);
	}
    }

    //- return result

    return(iResult);
}


/// **************************************************************************
///
/// SHORT: HeccerInitiate()
///
/// ARGS.:
///
///	pheccer...: a heccer.
///
/// RTN..: int
///
///	success of operation.
///
/// DESCR: Fill the data arrays with initial values.
///
/// TODO.:
///
///	I guess it should be possible to override the initial value
///	array using an additional argument.  Providing NULL means not
///	overriden.  Probably the initial values should be separated
///	out from the intermediary and have their own data structure.
///	In that case, we can also annotate the initial values with
///	flags, e.g. indicating that they are calculated or not (for
///	channel equilibrium state fi.).
///
/// **************************************************************************

int HeccerInitiate(struct Heccer *pheccer)
{
    //- set default result : ok

    int iResult = TRUE;

    //- initiate compartments

    iResult = iResult && HeccerCompartmentInitiate(pheccer);

/*     //- initiate mechanisms */

/*     iResult = iResult && HeccerMechanismInitiate(pheccer); */

    //- return result

    return(iResult);
}


/// **************************************************************************
///
/// SHORT: HeccerNew()
///
/// ARGS.:
///
///	pvService: identification service.
///
/// RTN..: struct Heccer *
///
///	Instantiated heccer, NULL for failure.
///
/// DESCR: Create a new heccer using defaults.
///
///	Defaults include option values and time step.  Look at the
///	code to see what they really are.
///
/// **************************************************************************

struct Heccer *HeccerNew(void *pvService)
{
    //- set result : initialized heccer

    struct Heccer *pheccerResult
	= HeccerNewP1
	  (
	      pvService,
	      0, // HECCER_OPTION_LOGICAL_BRANCH_SCHEDULING,
	      2e-5
	      );

    //- return result

    return(pheccerResult);
}


/// **************************************************************************
///
/// SHORT: HeccerNewP1()
///
/// ARGS.:
///
///	pvService: identification service.
///	iOptions.: see heccer.h.
///	dStep....: required time step (from the time constants of the model).
///
/// RTN..: struct Heccer *
///
///	Instantiated heccer, NULL for failure.
///
/// DESCR: Create a new heccer.
///
/// **************************************************************************

struct Heccer *HeccerNewP1(void *pvService, int iOptions, double dStep)
{
    //- set result : a new heccer

    struct Heccer *pheccerResult
	= (struct Heccer *)calloc(1, sizeof(struct Heccer));

    if (!pheccerResult)
    {
	return(NULL);
    }

    //- set naming service

    pheccerResult->pvService = pvService;

    //- set options and time step

    pheccerResult->ho.iOptions = iOptions;

    pheccerResult->dStep = dStep;

    //- initialize table discretization options

    pheccerResult->ho.dIntervalStart = HECCER_INTERVAL_DEFAULT_START;
    pheccerResult->ho.dIntervalEnd = HECCER_INTERVAL_DEFAULT_END;

    pheccerResult->ho.dBasalActivatorStart = HECCER_INTERVAL_BASAL_ACTIVATOR_DEFAULT_START;
    pheccerResult->ho.dBasalActivatorEnd = HECCER_INTERVAL_BASAL_ACTIVATOR_DEFAULT_END;

    pheccerResult->ho.iIntervalEntries = HECCER_INTERVAL_DEFAULT_ENTRIES;

    //- set new status

    pheccerResult->iStatus = HECCER_STATUS_PHASE_1;

    //- return result

    return(pheccerResult);
}


/// **************************************************************************
///
/// SHORT: HeccerNewP2()
///
/// ARGS.:
///
/// RTN..: struct Heccer *
///
///	Instantiated heccer, NULL for failure.
///
/// DESCR: Create a new heccer.
///
/// **************************************************************************

struct Heccer *HeccerNewP2(struct Intermediary *pinter)
{
    //- set result : initialized heccer

    struct Heccer *pheccerResult = HeccerNew(NULL);

    //- link in intermediary

    memcpy(&pheccerResult->inter, pinter, sizeof(*pinter));

    //- set new status

    pheccerResult->iStatus = HECCER_STATUS_PHASE_2;

    //- return result

    return(pheccerResult);
}


