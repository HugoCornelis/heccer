//
// Heccer : a compartmental solver that implements efficient Crank-Nicolson
// integration for neuronal models.
//

//////////////////////////////////////////////////////////////////////////////
//'
//' Heccer : testbed C implementation
//'
//' Copyright (C) 2006 Hugo Cornelis
//'
//' functional ideas ..	Hugo Cornelis, hugo.cornelis@gmail.com
//'
//' coding ............	Hugo Cornelis, hugo.cornelis@gmail.com
//'
//////////////////////////////////////////////////////////////////////////////


#include <stdlib.h>
#include <string.h>

#include "heccer.h"


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

    //t build up intermediary

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

    //t index & sort mechanisms

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
///	 Uses indices, initializedso with HeccerCompileP2().
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

    //- do minimum degree

    iResult = iResult && HeccerCompartmentCompile(pheccer);

    //t compile mechanisms

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
///
/// RTN..: int
///
///	success of operation.
///
/// DESCR: Call the dump functions.
///
/// **************************************************************************

int HeccerDump(struct Heccer *pheccer, FILE *pfile)
{
    //- set default result : ok

    int iResult = TRUE;

    //- status : reflects phases of compilation.

    fprintf(pfile, "Heccer (iStatus) : (%i)\n", pheccer->iStatus);

    //- options and operation mode.

    fprintf(pfile, "Heccer (iOptions) : (%i)\n", pheccer->iOptions);

    //- time step

    fprintf(pfile, "Heccer (dStep) : (%g)\n", pheccer->dStep);

    //- identification service : translates serials to math components

    fprintf(pfile, "Heccer (pvService) : (%i)\n", pheccer->pvService);

    //- dump intermediary

    iResult = iResult && HeccerIntermediaryDump(&pheccer->inter, pfile);

    //- dump the indices

    iResult = iResult && HeccerIndexersDump(&pheccer->indexers, pfile);

    //- dump compartment arrays

    iResult = iResult && HeccerVMDump(&pheccer->vm, pfile);

    //- return result

    return(iResult);
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

    //- perform the compartment operations

    iResult = iResult && HeccerCompartmentSolveCN(pheccer);

    //t perform mechanism operations (including concentration pools)

    //- return result

    return(iResult);
}


/// **************************************************************************
///
/// SHORT: HeccerIntialize()
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
/// **************************************************************************

int HeccerIntialize(struct Heccer *pheccer)
{
    return(FALSE);
}


/// **************************************************************************
///
/// SHORT: HeccerNewP1()
///
/// ARGS.:
///
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

struct Heccer *HeccerNewP1(int iOptions, double dStep)
{
    //- set result : a new heccer

    struct Heccer *pheccerResult
	= (struct Heccer *)calloc(1, sizeof(struct Heccer));

    if (!pheccerResult)
    {
	return(NULL);
    }

    //- set options and time step

    pheccerResult->iOptions = iOptions;

    pheccerResult->dStep = dStep;

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

    struct Heccer *pheccerResult
	= HeccerNewP1
	  (
	      0, // HECCER_OPTION_LOGICAL_BRANCH_SCHEDULING,
	      2e-5
	      );

    //- link in intermediary

    memcpy(&pheccerResult->inter, pinter, sizeof(*pinter));

    //- set new status

    pheccerResult->iStatus = HECCER_STATUS_PHASE_2;

    //- return result

    return(pheccerResult);
}


