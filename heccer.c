static char *pcVersionTime="(13/02/09) Saturday, February 9, 2013 09:14:41 hugo";

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


#include <math.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "heccer/addressing.h"
#include "heccer/heccer.h"
#include "heccer/serialization.h"


static int HeccerAggregatorsInitialize(struct simobj_Heccer *pheccer);

static int HeccerApplyLinearCable(struct simobj_Heccer *pheccer);

static int HeccerApplyOptions(struct simobj_Heccer *pheccer);


/// 
/// \arg pheccer a heccer.
/// 
/// \return int
/// 
///	Result of operation.
/// 
/// \brief Zero out result arrays for aggregation operators.
/// 

static int HeccerAggregatorsInitialize(struct simobj_Heccer *pheccer)
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


/// 
/// \arg pheccer a heccer.
/// 
/// \return int
/// 
///	Result of operation.
/// 
/// \brief Allocate result arrays for aggregation operators.
/// 

int HeccerAggregatorsCompile(struct simobj_Heccer *pheccer)
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


/// 
/// \arg pheccer a heccer.
/// 
/// \return int
/// 
///	Model can be compiled.
/// 
/// \brief Can the model be compiled, given the current options ?
/// 

int HeccerCanCompile(struct simobj_Heccer *pheccer)
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


/// 
/// \arg pheccer a heccer.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Compile a model into an intermediary format.
/// 

int HeccerCompileP1(struct simobj_Heccer *pheccer)
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
	/// \todo do something sensible here

	/// \todo HeccerError()
    }

    //- return result

    return(iResult);
}


/// 
/// \arg pheccer a heccer.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Recalculates compartment diameters and lengths of linear
/// cables for improved accuracy.
///
/// \note 
/// 
///	This changes the dRa cable properties of selected compartments
///	in the intermediary (namely those compartments with neighbours
///	that have a different length).
/// 

static int HeccerApplyLinearCable(struct simobj_Heccer *pheccer)
{
    //- set default result : ok

    int iResult = 1;

    //- apply options to the model

#ifdef USE_ENABLE_LINEAR_MODE

    if ((pheccer->ho.iOptions & HECCER_OPTION_ENABLE_LINEAR_MODE)
	&& !(pheccer->ho.iOptions & HECCER_OPTION_ENABLE_LINEAR_MODE_APPLIED)
	&& !(pheccer->ho.iCorrections & HECCER_CORRECTION_ENABLE_LINEAR_MODE_DISABLED))
    {
	int i;

	//- loop over all compartments

	for (i = 0 ; i < pheccer->inter.iCompartments ; i++)
	{
	    //- get intermediary number for the current compartment

	    int iChild = pheccer->indexers.md.piBackward[i];

	    //- if it has a parent

	    int iParent = pheccer->inter.pcomp[iChild].iParent;

	    if (iParent != -1)
	    {
		//- get parent length and diameter

		double dLengthParent = pheccer->inter.pcomp[iParent].dLength;

		double dDiaParent = pheccer->inter.pcomp[iParent].dDia;

		//- get child length and diameter

		double dLengthChild = pheccer->inter.pcomp[iChild].dLength;

		double dDiaChild = pheccer->inter.pcomp[iChild].dDia;

		//- new_len*new_dia (preserve surface area)

		double dA = dLengthParent * dDiaParent;

		//- preserve length/x-area

		double dB = (dLengthParent / (dDiaParent * dDiaParent) + dLengthChild / (dDiaChild * dDiaChild)) / 2.0;

		double dNewLength = dA * pow((dB / dA), (1.0 / 3.0));

		double dNewDia = dA / dNewLength;

		//- rescale parent axial resistance to shift the point of computation

		pheccer->inter.pcomp[iParent].dRa *= (dNewLength / dLengthParent) * (dDiaParent / dNewDia);
	    }
	}

	pheccer->ho.iOptions |= HECCER_OPTION_ENABLE_LINEAR_MODE_APPLIED;
    }

#endif

    //- return result

    return(iResult);
}


/// 
/// \arg pheccer a heccer.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Apply options that affect the intermediary representation.
///
/// \details
/// 
///	Currently calls HeccerApplyLinearCable() if the option
///	HECCER_OPTION_ENABLE_LINEAR_MODE is set.
/// 
/// \note 
/// 
///	This can change the cable properties in the intermediary.
/// 

static int HeccerApplyOptions(struct simobj_Heccer *pheccer)
{
    //- set default result : ok

    int iResult = TRUE;

    //- apply options to the model

    iResult = iResult && HeccerApplyLinearCable(pheccer);

    //- return result

    return(iResult);
}


/// 
/// \arg pheccer a heccer.
/// \arg pcDescription description of these parameters.
/// \arg va_list -1 terminated list of boolean values.
/// 
/// \return int
/// 
///	positive value == success, negative value == error.
/// 
/// \brief Check parameters utility function.
///
/// \details
/// 
///	Just give a list of boolean expressions, telling if the
///	parameters comply or not, a description where they occur.
///	This function will call HeccerError() for any FALSE boolean in
///	the stdarg list.
/// 

int
HeccerCheckParameters
(struct simobj_Heccer *pheccer, char *pcDescription, ...)
{
    //- set default result: ok

    int iResult = 0;

    //v stdargs list

    va_list vaList;

    //- get start of stdargs

    va_start(vaList, pcDescription);

    //- loop over all arguments

    int iOk = va_arg(vaList, int);

    while (iOk != -1)
    {
	//- if current argument not ok

	if (!iOk)
	{
	    char pcMessage[1000];

	    sprintf(pcMessage, "%s invalid", pcDescription);

	    HeccerError
		(pheccer,
		 NULL,
		 pcMessage);

	    //- set error condition

	    iResult = - iResult;

	    //- break loop

	    break;
	}

	//- go to next argument

	iResult++;

	iOk = va_arg(vaList, int);
    }

    //- end stdargs

    va_end(vaList);

    //- return result

    return(iResult);
}


/// 
/// \arg pheccer a heccer.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Analyze the model, build indices for optimization.
///
/// \details
/// 
///	Internally, Heccer addresses mechanisms using their
///	compartment's schedule number.  So the minimum degree
///	algorithm must run first before the mechanisms can be
///	compiled.
/// 
/// \note 
/// 
///	This function can be used for testing internals of heccer,
///	just be sure to provide a consistent intermediary image.
/// 

int HeccerCompileP2(struct simobj_Heccer *pheccer)
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

    //- apply options to the model

    iResult = iResult && HeccerApplyOptions(pheccer);

    //- index & sort mechanisms

    iResult = iResult && HeccerMechanismSort(pheccer);

    //- return result

    return(iResult);
}


/// 
/// \arg pheccer a heccer.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Compile the intermediary format into byte code.
///
/// \details
/// 
///	 Uses indices, initialized with HeccerCompileP2().
/// 
/// \note 
/// 
///	This function can be used for testing internals of heccer,
///	just be sure to provide a consistent intermediary image.
/// 

int HeccerCompileP3(struct simobj_Heccer *pheccer)
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

    //- rearrange table values for cache line loading

    if (!HeccerTablesRearrange(pheccer))
    {
	// \todo tell user about this, it is only a warning and heccer
	// should be happy although running at reduced speed.
    }

    //- allocate memory for aggregate results

    iResult = iResult && HeccerAggregatorsCompile(pheccer);

    //- return result

    return(iResult);
}


/// 
/// \arg pheccer a heccer.
/// \arg pfile stdio file.
/// \arg iSelection selection to dump.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Call the dump functions, with the given selection.
///
/// \details
/// 
///	The selection is the boolean or of zero or more of the following :
/// 
/// 
///	The shorthand HECCER_DUMP_ALL selects everything except very
///	verbose uninteresting items, HECCER_DUMP_ALL_EXTENDED selects
///	those items to, while HECCER_DUMP_ALL_REDUCED selects less.
/// 

int HeccerDumpV(struct simobj_Heccer *pheccer)
{
    return(HeccerDump(pheccer, stdout, HECCER_DUMP_ALL));
}

int HeccerDump(struct simobj_Heccer *pheccer, FILE *pfile, int iSelection)
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


/// 
/// \arg pheccer a heccer.
/// \arg pcContext context of error.
/// \arg pcError error string.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Register an error, print to stderr.
/// 

int HeccerError(struct simobj_Heccer *pheccer, char *pcContext, char *pcError, ...)
{
    //- set default result: ok

    int iResult = 1;

    //- give diagnostics

    //- print to stderr

    fprintf(stderr, "Heccer the hecc: ");

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


/* /// ************************************************************************** */
/* /// */
/* /// SHORT: HeccerFinish() */
/* /// */
/* /// ARGS.: */
/* /// */
/* ///	pheccer...: a heccer. */
/* /// */
/* /// \return int */
/* /// */
/* ///	success of operation. */
/* /// */
/* /// \brief Finish the operations performed by this heccer. */
/// \details 
/* /// */
/* ///	It is possible to continue operations. */
/* /// */
/* /// ************************************************************************** */

/* int HeccerFinish(struct simobj_Heccer *pheccer, pfile) */
/* { */
/*     //- set default result: ok */

/*     int iResult = 1; */

/*     //- if serialization is turned on */

/*     if (pheccer->ho.iOptions & HECCER_OPTION_SERIALIZE_AT_FINISH) */
/*     { */
/* 	//- serialize */

/* 	FILE *pfile = fopen(pheccer->ho.pcSerialized, "w"); */

/* 	if (!pfile) */
/* 	{ */
/* 	    return(0); */
/* 	} */

/* 	if (!HeccerSerialize(pheccer, pfile)) */
/* 	{ */
/* 	    return(0); */
/* 	} */

/* 	fclose(pfile); */
/*     } */

/*     //- return result */

/*     return(iResult); */
/* } */


/// 
/// \return char *
/// 
///	Version identifier.
/// 
/// \brief Obtain version identifier.
/// 

char * HeccerGetVersion(void)
{
    // $Format: "    static char *pcVersion=\"${package}-${label}\";"$
    static char *pcVersion="heccer-alpha";

    return(pcVersion);
}


/// 
/// \arg pheccer a heccer.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Compute one step of simulation time.
/// 

static int HeccerHecc(struct simobj_Heccer *pheccer)
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

    if (pheccer->vm.pdAggregators && pheccer->vm.iAggregators)
    {
	iResult = iResult && HeccerAggregatorsInitialize(pheccer);
    }

    /// \note I am undecided where to make the difference between CN and BE.
    /// From cosmetic viewpoint, here we should only delegate to
    /// HeccerMechanismHecc() and HeccerCompartmentHecc().
    /// Then the difference can be made by looking at the options
    /// (bad~?), or by having byte-code generated for the two specific
    /// cases (slower~?).

    /// \note On the other hand, this is less work for the moment and delays
    /// the decisions involved in the above (perhaps even unnecessary
    /// to be made~?).

    //- perform mechanism operations (including concentration pools)

    /// \note doing it like this, assumes that the mechanism values are
    /// correctly given to HeccerInitiate() at time (now - dt/2).  Does
    /// not make a practical difference.

    iResult = iResult && HeccerMechanismSolveCN(pheccer);

    //- perform the compartment operations

    if (pheccer->vm.iVms != 1)
    {
	iResult = iResult && HeccerCompartmentSolveCN(pheccer);
    }

    //- return result

    return(iResult);
}


/// 
/// \arg pheccer a heccer.
/// \arg dTime current time.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Call HeccerHecc() until dTime.
/// 

int HeccerHeccs(struct simobj_Heccer *pheccer, double dTime)
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

	/// \note perhaps should move the advance of the local time to this
	/// \note point ?  Would allow to remove this test ...
	/// \note I don't care for the moment.

	if (iResult == FALSE)
	{
	    return(iResult);
	}
    }

    //- return result

    return(iResult);
}


/// 
/// \arg pheccer a heccer.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Fill the data arrays with initial values.
/// 
/// \todo 
/// 
///	I guess it should be possible to override the initial value
///	array using an additional argument.  Providing NULL means not
///	overriden.  Probably the initial values should be separated
///	out from the intermediary and have their own data structure.
///	In that case, we can also annotate the initial values with
///	flags, e.g. indicating that they are calculated or not (for
///	channel equilibrium state fi.).
/// 

int HeccerInitiate(struct simobj_Heccer *pheccer)
{
    //- check for errors

    if (pheccer->iErrorCount)
    {
	return(FALSE);
    }

    //- set default result : ok

    int iResult = TRUE;

    //- reset the time

    pheccer->dTime = 0.0;

    //- initiate compartments

    iResult = iResult && HeccerCompartmentInitiate(pheccer);

/*     //- initiate mechanisms */

/*     iResult = iResult && HeccerMechanismInitiate(pheccer); */

    //- return result

    return(iResult);
}


/// 
/// \arg pc name of this heccer, may be NULL.
/// \arg pts translation service.
/// \arg ped event distribution service.
/// \arg peq event queuing service.
/// 
/// \return struct simobj_Heccer *
/// 
///	Instantiated heccer, NULL for failure.
/// 
/// \brief Create a new heccer using defaults.
///
/// \details
/// 
///	Defaults include option values and time step.  Look at the
///	code to see what they really are.
/// 

struct simobj_Heccer *
HeccerNew
(char *pc,
 struct TranslationService *pts,
 struct EventDistributor *ped,
 struct EventQueuer *peq)
{
    //- set result : initialized heccer

    struct simobj_Heccer *pheccerResult
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


/// 
/// \arg pc name of this heccer, may be NULL.
/// \arg pts identification service.
/// \arg ped event distribution service.
/// \arg peq event queuing service.
/// \arg iOptions see heccer.h.
/// \arg dStep required time step (from the time constants of the model).
/// 
/// \return struct simobj_Heccer *
/// 
///	Instantiated heccer, NULL for failure.
/// 
/// \brief Create a new heccer.
/// 

struct simobj_Heccer *
HeccerNewP1
(char *pc,
 struct TranslationService *pts,
 struct EventDistributor *ped,
 struct EventQueuer *peq,
 int iOptions,
 double dStep)
{
    //- set result : a new heccer

    struct simobj_Heccer *pheccerResult
	= (struct simobj_Heccer *) calloc(1, sizeof(struct simobj_Heccer));

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

/*     //- initialize table range detectors: not detected yet */

/*     pheccerResult->tgt.dRearrangedStart = DBL_MAX; */

/*     pheccerResult->tgt.dRearrangedEnd = DBL_MIN; */

    //- set new status

    pheccerResult->iStatus = HECCER_STATUS_PHASE_1;

    //- return result

    return(pheccerResult);
}


/// 
/// \arg pc name of this heccer, may be NULL.
/// \arg pinter intermediary with a complete numerical model definition.
/// 
/// \return struct simobj_Heccer *
/// 
///	Instantiated heccer, NULL for failure.
/// 
/// \brief Create a new heccer.
/// 

struct simobj_Heccer *HeccerNewP2(char *pc, struct Intermediary *pinter)
{
    //- set result : initialized heccer

    struct simobj_Heccer *pheccerResult = HeccerNew(pc, NULL, NULL, NULL);

    //- link in intermediary

    memcpy(&pheccerResult->inter, pinter, sizeof(*pinter));

    //- set new status

    pheccerResult->iStatus = HECCER_STATUS_PHASE_2;

    //- return result

    return(pheccerResult);
}


/// 
/// \arg pc filename.
/// 
/// \return struct simobj_Heccer *
/// 
///	New heccer, NULL for failure.
/// 
/// \brief Construct a heccer from a file.
/// 

struct simobj_Heccer *HeccerNewFromFile(char *pc)
{
    //- set default result: failure

    struct simobj_Heccer *pheccerResult = NULL;

    //- deserialize

    FILE *pfile = HeccerSerializationOpenRead(pc);

    pheccerResult = HeccerDeserialize(pfile);

    HeccerSerializationClose(pfile);

    //- return result

    return(pheccerResult);
}


/// 
/// \arg pheccer heccer to write.
/// \arg pc filename.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Write the heccer to the file.
/// 

int HeccerWriteToFile(struct simobj_Heccer *pheccer, char *pc)
{
    //- set default result: ok

    int iResult = 1;

    //- open file

    FILE *pfile = HeccerSerializationOpenWrite(pc);

    //- serialize

    iResult = HeccerSerialize(pheccer, pfile);

    //- close file

    HeccerSerializationClose(pfile);

    //- return success

    return(iResult);
}


// Local variables:
// eval: (add-hook 'write-file-hooks 'time-stamp)
// time-stamp-start: "pcVersionTime="
// time-stamp-format: "\"(%02y/%02m/%02d) %a, %b %d, %y %02H:%02M:%02S %u\";"
// time-stamp-end: "$"
// End:
