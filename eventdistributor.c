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


#include <float.h>
#include <stdlib.h>

#include "heccer/eventdistributor.h"


/// **************************************************************************
///
/// SHORT: EventDistributorSend()
///
/// ARGS.:
///
///	ped.......: an event distributor.
///	iTargets..: index of target objects and target ports.
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
	//- get target port index

	int iTarget = ppedt->iTarget;

	//- call the target object

	//! possibly calls directly to HeccerOutput,
	//! possibly calls to the EventQueuer to queue the object
	//! other hooks possible.

	iResult = iResult && ppedt->pvFunction(ppedt->pvObject, dTime, iTarget);

	//- next table entry

	ppedt++;
    }

    //- return result

    return(iResult);
}


/// **************************************************************************
///
/// SHORT: EventQueuerDequeue()
///
/// ARGS.:
///
///	peq.......: an event queuer.
///	iTarget...: target object index.
///
/// RTN..: double
///
///	Sum of weights of arriving events, FLT_MAX for failure.
///
/// DESCR: Dequeue events for the given target, return the summed weights.
///
/// **************************************************************************

double EventQueuerDequeue(struct EventQueuer *peq, double dTime, int iTarget)
{
    //- set default result: no weights

    double dResult = 0.0;

    //- loop over events for this target until this time

    //t

    struct EventQueuerTarget *ppeqt = &peq->peqd->ppeqt[0][iTarget];

    while (ppeqt
/* 	   && ppeqt->pvFunction */
	   && dResult != FLT_MAX)
    {
	//- get weight for event

	//t

	double dWeight = ppeqt->dWeight;

	if (dWeight == FLT_MAX)
	{
	    return(FLT_MAX);
	}

	//- add weight to result

	dResult += dWeight;

	//- next table entry

	ppeqt++;

	ppeqt = NULL;
    }

    //- return result

    return(dResult);
}


/// **************************************************************************
///
/// SHORT: EventQueuerEnqueue()
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
/// DESCR: Put an event in the queue untill it fires.
///
/// **************************************************************************

int EventQueuerEnqueue(struct EventQueuer *peq, double dTime, int iSource, int iTarget)
{
    //- set default result: ok

    int iResult = 1;

    //t 1. just queue event
    //t 2. add function to the queuer service as a solver entry
    //t 3. link heccer with the entry, or better do the scheduling external, so link with ssp
    //t 4. done ?

    //- if there is a valid target

    //! guess I will have to get rid of this check.

    if (iTarget != -1)
    {
	//- loop over target table

	struct EventQueuerTarget *ppeqt = peq->peqd->ppeqt[iTarget];

	while (ppeqt && ppeqt->pvFunction)
	{
	    //- add connection delay

	    double dEvent = dTime + ppeqt->dDelay;

	    //- call the target object

	    iResult = iResult && ppeqt->pvFunction(ppeqt->pvObject, ppeqt->iTarget, dEvent);

	    //- next table entry

	    ppeqt++;
	}
    }

    //- return result

    return(iResult);
}


/// **************************************************************************
///
/// SHORT: EventQueuerSerial2PortNumber()
///
/// ARGS.:
///
///	peq.......: an event queuer.
///	iSerial...: serial to convert.
///
/// RTN..: int
///
///	port number, -1 for failure.
///
/// DESCR: Convert an external serial to a solver port number.
///
/// **************************************************************************

int EventQueuerSerial2PortNumber(struct EventQueuer *peq, int iSerial)
{
    //- set default result: failure.

    int iResult = -1;

    //- if there is an initialized event queuer

    if (peq && peq->peqd && peq->peqd->iPorts > 0)
    {
	//! binary search

	//- init top and bottom counters

	int iLower = 0;
	int iUpper = peq->peqd->iPorts - 1;

	//- search until the range to search in becomes invalid

	while (iUpper - iLower >= 0)
	{
	    //- determine the middle of the search range

	    int iMiddle = (iLower + iUpper) / 2;

	    //- set result and break out loop if search value is found here

	    if (iSerial == peq->peqd->ppiSerial2PortNumber[iMiddle][0])
	    {
		iResult = peq->peqd->ppiSerial2PortNumber[iMiddle][1];

		break;
	    }

	    //- set a new lower or upper limit

	    if (iSerial > peq->peqd->ppiSerial2PortNumber[iMiddle][0])
	    {
		iLower = iMiddle + 1;
	    }
	    else
	    {
		iUpper = iMiddle - 1;
	    }
	}
    }

    //- return result

    return(iResult);
}


