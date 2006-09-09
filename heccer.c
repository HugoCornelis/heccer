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
///	heccer...: a heccer.
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
///	heccer...: a heccer.
///
/// RTN..: int
///
///	success of operation.
///
/// DESCR: Compile the intermediary format into byte code.
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

    //t compile channels

    //- return result

    return(iResult);
}


/// **************************************************************************
///
/// SHORT: HeccerHecc()
///
/// ARGS.:
///
///	heccer...: a heccer.
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
    return(FALSE);
}


/// **************************************************************************
///
/// SHORT: HeccerIntialize()
///
/// ARGS.:
///
///	heccer...: a heccer.
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
/// RTN..: struct Heccer *
///
///	Instantiated heccer, NULL for failure.
///
/// DESCR: Create a new heccer.
///
/// **************************************************************************

struct Heccer *HeccerNewP1(void)
{
    //- set result : a new heccer

    struct Heccer *pheccerResult
	= (struct Heccer *)calloc(1, sizeof(struct Heccer));

    //- set new status

    pheccerResult->iStatus = HECCER_STATUS_PHASE_1;

    //- return result

    return(NULL);
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

    struct Heccer *pheccerResult = HeccerNewP1();

    //- link in intermediary

    memcpy(&pheccerResult->inter, pinter, sizeof(*pinter));

    //- set new status

    pheccerResult->iStatus = HECCER_STATUS_PHASE_2;

    //- return result

    return(pheccerResult);
}


