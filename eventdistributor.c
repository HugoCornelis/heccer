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


#include "heccer/eventdistributor.h"


/// **************************************************************************
///
/// SHORT: EventDistributorSend()
///
/// ARGS.:
///
///	ped.......: an event distributor.
///	ppiTargets: target objects and target ports.
///
/// RTN..: int
///
///	success of operation.
///
/// DESCR: Distribute an event over the targets.
///
/// **************************************************************************

int EventDistributorSend(struct EventDistributor *ped, double dTime, int iTargets)
{
    //- set default result: ok

    int iResult = 1;

    //- loop over target table

    struct EventDistributorTarget *ppedt = ped->pedd->ppedt[iTargets];

    while (ppedt && ppedt->pvFunction)
    {
	//- get target index

	int iTarget = ppedt->iTarget;

	//- call the target object

	iResult = iResult && ppedt->pvFunction(ppedt->pvObject, dTime, iTarget);

	//- next table entry

	ppedt++;
    }

    //- return result

    return(iResult);
}


/// **************************************************************************
///
/// SHORT: EventQueuerQueue()
///
/// ARGS.:
///
///	peq.......: an event queuer.
///	ppiTargets: target objects and target ports.
///
/// RTN..: int
///
///	success of operation.
///
/// DESCR: Distribute an event over the targets.
///
/// **************************************************************************

int EventQueuerQueue(struct EventQueuer *peq, double dTime, int iTarget)
{
    //- set default result: ok

    int iResult = 1;

    //t 1. just queue event
    //t 2. add function to the queuer service as a solver entry
    //t 3. link heccer with the entry, or better do the scheduling external, so link with ssp
    //t 4. done ?

    //- loop over target table

    struct EventQueuerTarget *ppeqt = peq->peqd->ppeqt[iTarget];

    while (ppeqt && ppeqt->pvFunction)
    {
	//- call the target object

	iResult = iResult && ppeqt->pvFunction(ppeqt->iTarget, dTime);

	//- next table entry

	ppeqt++;
    }

    //- return result

    return(iResult);
}


/// **************************************************************************
///
/// SHORT: EventQueuerReceive()
///
/// ARGS.:
///
///	peq.......: an event queuer.
///	ppiTargets: target objects and target ports.
///
/// RTN..: int
///
///	success of operation.
///
/// DESCR: Distribute an event over the targets.
///
/// **************************************************************************

int EventQueuerReceive(struct EventQueuer *peq, double dTime, int iTargets)
{
    //- set default result: ok

    int iResult = 1;

    //t 1. just queue event
    //t 2. add function to the queuer service as a solver entry
    //t 3. link heccer with the entry, or better do the scheduling external, so link with ssp
    //t 4. done ?

    //- loop over target table

    struct EventQueuerTarget *ppeqt = peq->peqd->ppeqt[iTargets];

    while (ppeqt && ppeqt->pvFunction)
    {
	//- call the target object

	iResult = iResult && ppeqt->pvFunction(ppeqt->iTarget, dTime);

	//- next table entry

	ppeqt++;
    }

    //- return result

    return(iResult);
}


