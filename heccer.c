static char *pcVersionTime="(08/07/13) Sunday, July 13, 2008 18:47:45 hugo";

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


#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "heccer/heccer.h"


static int HeccerAggregatorsInitialize(struct Heccer *pheccer);


/// **************************************************************************
///
/// SHORT: HeccerAggregatorsInitialize()
///
/// ARGS.:
///
///	pheccer...: a heccer.
///
/// RTN..: int
///
///	Result of operation.
///
/// DESCR: Zero out result arrays for aggregation operators.
///
/// **************************************************************************

static int HeccerAggregatorsInitialize(struct Heccer *pheccer)
{
    //- set default result : ok

    int iResult = TRUE;

    //- zero out ...

    int i;

    for (i = 0 ; i < pheccer->vm.iAggregators ; i++)
    {
	pheccer->vm.pdAggregators[i] = 0.0;
    }

    //- return result

    return(iResult);
}


/// **************************************************************************
///
/// SHORT: HeccerAggregatorsCompile()
///
/// ARGS.:
///
///	pheccer...: a heccer.
///
/// RTN..: int
///
///	Result of operation.
///
/// DESCR: Allocate result arrays for aggregation operators.
///
/// **************************************************************************

int HeccerAggregatorsCompile(struct Heccer *pheccer)
{
    //- check for errors

    if (pheccer->iErrorCount)
    {
	return(FALSE);
    }

    //- set default result : ok

    int iResult = TRUE;

    //- allocate memory

    pheccer->vm.pdAggregators = calloc(pheccer->vm.iAggregators, sizeof(*pheccer->vm.pdAggregators));

    if (!pheccer->vm.pdAggregators)
    {
	return(FALSE);
    }

    //- return result

    return(iResult);
}


/// **************************************************************************
///
/// SHORT: HeccerCanCompile()
///
/// ARGS.:
///
///	pheccer...: a heccer.
///
/// RTN..: int
///
///	Model can be compiled.
///
/// DESCR: Can the model be compiled, given the current options ?
///
/// **************************************************************************

int HeccerCanCompile(struct Heccer *pheccer)
{
    //- check for errors

    if (pheccer->iErrorCount)
    {
	return(FALSE);
    }

    //- set default result : ok

    int iResult = TRUE;

#define MINIMAL_TIME_STEP 1e-30

    if (pheccer->dStep < MINIMAL_TIME_STEP)
    {
	HeccerError
	    (pheccer,
	     NULL,
	     "illegal time step (smallest is %g), cannot compile\n", MINIMAL_TIME_STEP);

	return(FALSE);
    }

    if (pheccer->inter.iCompartments == 0)
    {
	HeccerError
	    (pheccer,
	     NULL,
	     "no compartments found in the intermediary, cannot compile this model\n");

	return(FALSE);
    }

    //- return result

    return(iResult);
}


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
    //- check for errors

    if (pheccer->iErrorCount)
    {
	return(FALSE);
    }

    //- if the intermediary is already available

    if (pheccer->iStatus >= HECCER_STATUS_PHASE_2)
    {
	//- return success

	return(TRUE);
    }

    //- set default result : ok

    int iResult = TRUE;

    //- get access to the translation service

    struct TranslationService *pts = pheccer->pts;

/*     struct TranslationServiceData *ptsd = pts->ptsd; */

    //- build up intermediary using the available service

    ComponentInspector si = pts->segments_inspector;

    iResult = iResult && si(pheccer, pts);

    ComponentInspector mi = pts->mechanisms_inspector;

    iResult = iResult && mi(pheccer, pts);

    //- set new status

    if (iResult)
    {
	pheccer->iStatus = HECCER_STATUS_PHASE_2;
    }
    else
    {
	//t do something sensible here

	//t HeccerError()
    }

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
    //- check for errors

    if (pheccer->iErrorCount)
    {
	return(FALSE);
    }

    //- set default result : ok

    int iResult = TRUE;

    //- first sanity

    if (!HeccerCanCompile(pheccer))
    {
	iResult = FALSE;
    }

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
    //- check for errors

    if (pheccer->iErrorCount)
    {
	return(FALSE);
    }

    //- set default result : ok

    int iResult = TRUE;

    //- compile compartments to byte code

    iResult = iResult && HeccerCompartmentCompile(pheccer);

    //- compile mechanisms to byte code

    iResult = iResult && HeccerMechanismCompile(pheccer);

    //- link mechanisms

    iResult = iResult && HeccerMechanismLink(pheccer);

    //t perhaps should discretize channels overhere ?

    //- allocate memory for aggragate results

    iResult = iResult && HeccerAggregatorsCompile(pheccer);

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
    //- check for errors

    if (pheccer->iErrorCount)
    {
	return(FALSE);
    }

    //- set default result : ok

    int iResult = TRUE;

    if (!pfile)
    {
	pfile = stdout;
    }

    //- name: always present

    fprintf(pfile, "Heccer (pcName) : (%s)\n", pheccer->pcName ? pheccer->pcName : "(null)");

    //- status: reflects phases of compilation.

    fprintf(pfile, "Heccer (iStatus) : (%i)\n", pheccer->iStatus);

    fprintf(pfile, "Heccer (iErrorCount) : (%i)\n", pheccer->iErrorCount);

    //- options and operation mode.

    fprintf(pfile, "Heccer Options (iOptions) : (%i)\n", pheccer->ho.iOptions);

    fprintf(pfile, "Heccer Options (dIntervalStart) : (%g)\n", pheccer->ho.dIntervalStart);

    fprintf(pfile, "Heccer Options (dIntervalEnd) : (%g)\n", pheccer->ho.dIntervalEnd);

    fprintf(pfile, "Heccer Options (dConcentrationGateStart) : (%g)\n", pheccer->ho.dConcentrationGateStart);

    fprintf(pfile, "Heccer Options (dConcentrationGateEnd) : (%g)\n", pheccer->ho.dConcentrationGateEnd);

    fprintf(pfile, "Heccer Options (iIntervalEntries) : (%i)\n", pheccer->ho.iIntervalEntries);

    fprintf(pfile, "Heccer Options (iSmallTableSize) : (%i)\n", pheccer->ho.iSmallTableSize);

    //- simulation time

    fprintf(pfile, "Heccer (dTime) : (%g)\n", pheccer->dTime);

    //- time step

    fprintf(pfile, "Heccer (dStep) : (%g)\n", pheccer->dStep);

    //- identification service : translates serials to math components

    if (iSelection & HECCER_DUMP_SERVICE)
    {
	fprintf(pfile, "Heccer (pts) : (%p)\n", pheccer->pts);
	fprintf(pfile, "Heccer (ped) : (%p)\n", pheccer->ped);
    }

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
/// SHORT: HeccerError()
///
/// ARGS.:
///
///	pheccer..: a heccer.
///	pcContext: context of error.
///	pcError..: error string.
///
/// RTN..: int
///
///	success of operation.
///
/// DESCR: Register an error, print to stderr.
///
/// **************************************************************************

int HeccerError(struct Heccer *pheccer, char *pcContext, char *pcError, ...)
{
    //- set default result: ok

    int iResult = 1;

    //- give diagnostics

    //- print to stderr

    fprintf(stderr, "Heccer the hecc :");

/*     if (pcContext) */
/*     { */
/* 	fprintf */
/* 	    (stderr, */
/* 	     "%s: *** Error: ", */
/* 	     pcContext); */
/*     } */

    //v stdargs list

    va_list vaList;

    //- get start of stdargs

    va_start(vaList, pcError);

    //- give diagnostics

    vfprintf(stderr, pcError, vaList);

    fprintf(stderr, "\n");

    //- end stdargs

    va_end(vaList);

    //- negate status: this heccer is in error

    pheccer->iStatus = - pheccer->iStatus;

    //- increment total error count

    pheccer->iErrorCount++;

    //- return result

    return(iResult);
}


/// **************************************************************************
///
/// SHORT: HeccerGetVersion()
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
    static char *pcVersion="network-14";

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

static int HeccerHecc(struct Heccer *pheccer)
{
    //- check for errors

    if (pheccer->iErrorCount)
    {
	return(FALSE);
    }

    //- set default result : ok

    int iResult = TRUE;

    //- update the simulation time

    pheccer->dTime += pheccer->dStep;

    //- initialize the aggregate results

    if (pheccer->vm.pdAggregators)
    {
	iResult = iResult && HeccerAggregatorsInitialize(pheccer);
    }

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
    //- check for errors

    if (pheccer->iErrorCount)
    {
	return(FALSE);
    }

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
    //- check for errors

    if (pheccer->iErrorCount)
    {
	return(FALSE);
    }

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
///	pc.....: name of this heccer, may be NULL.
///	pts....: translation service.
///	ped....: event distribution service.
///	peq....: event queuing service.
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

struct Heccer *
HeccerNew
(char *pc,
 struct TranslationService *pts,
 struct EventDistributor *ped,
 struct EventQueuer *peq)
{
    //- set result : initialized heccer

    struct Heccer *pheccerResult
	= HeccerNewP1
	  (
	      pc,
	      pts,
	      ped,
	      peq,
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
///	pc.......: name of this heccer, may be NULL.
///	pts......: identification service.
///	ped......: event distribution service.
///	peq......: event queuing service.
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

struct Heccer *
HeccerNewP1
(char *pc,
 struct TranslationService *pts,
 struct EventDistributor *ped,
 struct EventQueuer *peq,
 int iOptions,
 double dStep)
{
    //- set result : a new heccer

    struct Heccer *pheccerResult
	= (struct Heccer *)calloc(1, sizeof(struct Heccer));

    if (!pheccerResult)
    {
	return(NULL);
    }

    //- set name

    pheccerResult->pcName = pc;

    //- set naming service

    pheccerResult->pts = pts;

    //- set event distribution service

    pheccerResult->ped = ped;

    //- set event queuing service

    pheccerResult->peq = peq;

    //- set options and time step

    pheccerResult->ho.iOptions = iOptions;

    pheccerResult->dStep = dStep;

    //- initialize table discretization options

    pheccerResult->ho.dIntervalStart = HECCER_INTERVAL_DEFAULT_START;
    pheccerResult->ho.dIntervalEnd = HECCER_INTERVAL_DEFAULT_END;

    pheccerResult->ho.dConcentrationGateStart = HECCER_INTERVAL_CONCENTRATION_GATE_DEFAULT_START;
    pheccerResult->ho.dConcentrationGateEnd = HECCER_INTERVAL_CONCENTRATION_GATE_DEFAULT_END;

    pheccerResult->ho.iIntervalEntries = HECCER_INTERVAL_DEFAULT_ENTRIES;

    pheccerResult->ho.iSmallTableSize = HECCER_INTERPOL_INTERVAL_DEFAULT_ENTRIES;

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
///	pc......: name of this heccer, may be NULL.
///	pinter..: intermediary with a complete numerical model definition.
///
/// RTN..: struct Heccer *
///
///	Instantiated heccer, NULL for failure.
///
/// DESCR: Create a new heccer.
///
/// **************************************************************************

struct Heccer *HeccerNewP2(char *pc, struct Intermediary *pinter)
{
    //- set result : initialized heccer

    struct Heccer *pheccerResult = HeccerNew(pc, NULL, NULL, NULL);

    //- link in intermediary

    memcpy(&pheccerResult->inter, pinter, sizeof(*pinter));

    //- set new status

    pheccerResult->iStatus = HECCER_STATUS_PHASE_2;

    //- return result

    return(pheccerResult);
}


// Local variables:
// eval: (add-hook 'write-file-hooks 'time-stamp)
// time-stamp-start: "pcVersionTime="
// time-stamp-format: "\"(%02y/%02m/%02d) %a, %b %d, %y %02H:%02M:%02S %u\";"
// time-stamp-end: "$"
// End:
