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
#include <stdio.h>

#include "heccer/eventdistributor.h"
#include "heccer/sglib.h"


typedef struct EventList
{
    struct EventList *ptr_to_next;
    struct EventList *ptr_to_previous;
    int iTarget;
    double dTime;
}
    EventList;

#define EVENTLIST_COMPARATOR(e1, e2) (e1->dTime > e2->dTime)

SGLIB_DEFINE_DL_LIST_PROTOTYPES(EventList, EVENTLIST_COMPARATOR, ptr_to_previous, ptr_to_next);
SGLIB_DEFINE_DL_LIST_FUNCTIONS(EventList, EVENTLIST_COMPARATOR, ptr_to_previous, ptr_to_next);

EventList *elEvents = NULL;


/// **************************************************************************
///
/// SHORT: EventDistributorNew()
///
/// ARGS.:
///
///	ppedm...: event distributor connection matrix.
///
/// RTN..: struct EventDistributor
///
///	An event distributor.
///
/// DESCR: Allocate an event distributor.
///
/// **************************************************************************

struct EventDistributor *
EventDistributorNew
(struct EventDistributorMatrix *ppedm)
{
    //- set default result: allocate

    struct EventDistributor *pedResult = calloc(1, sizeof(*pedResult));

    if (!pedResult)
    {
	return(NULL);
    }

    pedResult->eventDistribute = EventDistributorSend;

    struct EventDistributorData *pedd = calloc(1, sizeof(*pedd));

    if (!pedd)
    {
	free(pedResult);

	return(NULL);
    }

    pedResult->pedd = pedd;

    pedd->iHappy = 0;

    pedd->ppedm = ppedm;

    //- return result

    return(pedResult);
}


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

    struct EventDistributorMatrix *ppedm = &ped->pedd->ppedm[iTargets];

    while (ppedm && ppedm->pvFunction)
    {
	//- get target port index

	int iTarget = ppedm->iTarget;

	//- call the target object

	//! possibly calls directly to HeccerOutput,
	//! possibly calls to the EventQueuer to queue the object
	//! other hooks possible.

	iResult = iResult && ppedm->pvFunction(ppedm->pvObject, dTime, iTarget);

	//- next table entry

	ppedm++;
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

    //t loop over events for this target until this time

    struct EventQueuerMatrix *ppeqm = &peq->peqd->ppeqm[iTarget];

    while (ppeqm
/* 	   && ppeqm->pvFunction */
	   && dResult != FLT_MAX)
    {
	//- get weight for event

	double dWeight = ppeqm->dWeight;

	if (dWeight == FLT_MAX)
	{
	    return(FLT_MAX);
	}

	//- add weight to result

	dResult += dWeight;

	//- next table entry

	ppeqm++;

	ppeqm = NULL;
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

    //- queue the incoming event

    EventList *elElement = malloc(sizeof(EventList));

    elElement->dTime = dTime;
    elElement->iTarget = iTarget;

    sglib_EventList_add(&elEvents, elElement);

    //- sort event list

    sglib_EventList_sort(&elEvents);

/*     iResult = EventQueuerProcess(peq, iTarget, dTime); */

    //- return result

    return(iResult);
}


/// **************************************************************************
///
/// SHORT: EventQueuerNew()
///
/// ARGS.:
///
///	ppeqm...: event queuer connection matrix.
///
/// RTN..: struct EventQueuer
///
///	An event queuer.
///
/// DESCR: Allocate an event queuer.
///
/// **************************************************************************

struct EventQueuer * EventQueuerNew(struct EventQueuerMatrix *ppeqm)
{
    //- set default result: allocate

    struct EventQueuer *peqResult = calloc(1, sizeof(*peqResult));

    if (!peqResult)
    {
	return(NULL);
    }

    peqResult->eventDequeue = EventQueuerDequeue;

    peqResult->eventEnqueue = EventQueuerEnqueue;

    struct EventQueuerData *peqd = calloc(1, sizeof(*peqd));

    if (!peqd)
    {
	free(peqResult);

	return(NULL);
    }

    peqResult->peqd = peqd;

    peqd->iConnectionIndices = 0;

    peqd->ppeqm = ppeqm;

    //- return result

    return(peqResult);
}


/// **************************************************************************
///
/// SHORT: EventQueuerProcess()
///
/// ARGS.:
///
///	peq...: event queuer.
///
/// RTN..: int
///
///	success of operation.
///
/// DESCR: Process events in the queue, forward the ones that should fire.
///
/// **************************************************************************

int EventQueuerProcess(struct EventQueuer *peq)
{
    //- set default result: ok

    int iResult = 1;

    EventList *elElement = sglib_EventList_get_first(elEvents);

    if (elElement)
    {
	sglib_EventList_delete(&elEvents, elElement);

	int iTarget = elElement->iTarget;

	double dTime = elElement->dTime;

	//- loop over target table

	struct EventQueuerMatrix *ppeqm = &peq->peqd->ppeqm[iTarget];

	while (ppeqm && ppeqm->pvFunction)
	{
	    //- add connection delay

	    double dEvent = dTime + ppeqm->dDelay;

	    //- call the target object

	    iResult = iResult && ppeqm->pvFunction(ppeqm->pvObject, ppeqm->iTarget, dEvent);

	    //- next table entry

	    ppeqm++;
	}
    }

    //- return result

    return(iResult);
}


/// **************************************************************************
///
/// SHORT: EventQueuerSerial2ConnectionIndex()
///
/// ARGS.:
///
///	peq.......: an event queuer.
///	iSerial...: serial to convert.
///
/// RTN..: int
///
///	connection matrix index, -1 for failure.
///
/// DESCR: Convert an external serial to a connection matrix index.
///
/// **************************************************************************

int EventQueuerSerial2ConnectionIndex(struct EventQueuer *peq, int iSerial)
{
    //- set default result: failure.

    int iResult = -1;

    //- if there is an initialized event queuer

    if (peq && peq->peqd && peq->peqd->iConnectionIndices > 0)
    {
	//! binary search

	//- init top and bottom counters

	int iLower = 0;
	int iUpper = peq->peqd->iConnectionIndices - 1;

	//- search until the range to search in becomes invalid

	while (iUpper - iLower >= 0)
	{
	    //- determine the middle of the search range

	    int iMiddle = (iLower + iUpper) / 2;

	    //- set result and break out loop if search value is found here

	    if (iSerial == peq->peqd->ppiSerial2ConnectionIndex[iMiddle][0])
	    {
		iResult = peq->peqd->ppiSerial2ConnectionIndex[iMiddle][1];

		break;
	    }

	    //- set a new lower or upper limit

	    if (iSerial > peq->peqd->ppiSerial2ConnectionIndex[iMiddle][0])
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


/// **************************************************************************
///
/// SHORT: EventQueuerSerial2ConnectionIndexAdd()
///
/// ARGS.:
///
///	peq.......: an event queuer.
///	iSerial...: serial to convert.
///	iIndex....: connection index.
///
/// RTN..: int
///
///	success of operation.
///
/// DESCR: Add an external serial to that was added to the connection matrix.
///
/// **************************************************************************

int
EventQueuerSerial2ConnectionIndexAdd
(struct EventQueuer *peq,
 int iSerial,
 int iIndex)
{
    //- set default result: failure.

    int iResult = 0;

    //- if there is an initialized event queuer

    if (peq && peq->peqd)
    {
	//- add the translation of the connection

	if (peq->peqd->iConnectionIndices < EVENTQUEUER_MAX_CONNECTIONS)
	{
	    peq->peqd->ppiSerial2ConnectionIndex[peq->peqd->iConnectionIndices][0] = iSerial;
	    peq->peqd->ppiSerial2ConnectionIndex[peq->peqd->iConnectionIndices][1] = iIndex;

	    peq->peqd->iConnectionIndices++;

	    iResult = 1;
	}
	else
	{
	    //t HeccerError(number, message, varargs);

	    fprintf
		(stderr,
		 "Heccer the hecc : connection matrix translator overflow (please increase EVENTQUEUER_MAX_CONNECTIONS in the source).\n");
	}
    }

    //- return result

    return(iResult);
}


/// **************************************************************************
///
/// SHORT: EventQueuerSerial2ConnectionIndexSort()
///
/// ARGS.:
///
///	peq.......: an event queuer.
///
/// RTN..: int
///
///	success of operation.
///
/// DESCR: Sort the serial 2 connection index array.
///
/// **************************************************************************

static int comparator(const void *pv1, const void *pv2)
{
    int iResult = 0;

    int *pi1 = (int *)pv1;
    int *pi2 = (int *)pv2;

    if (pi1[0] < pi2[0])
    {
	return(-1);
    }
    else if (pi1[0] > pi2[0])
    {
	return(1);
    }
    else
    {
	//t HeccerError(number, message, varargs);

	fprintf
	    (stderr,
	     "Heccer the hecc : connection matrix index comparator() encounters entries with the same serial.\n");

	return(0);
    }
}

int EventQueuerSerial2ConnectionIndexSort(struct EventQueuer *peq)
{
    //- set default result: failure.

    int iResult = 0;

    //- if there is an initialized event queuer

    if (peq && peq->peqd)
    {
	qsort
	    (&peq->peqd->ppiSerial2ConnectionIndex[0][0], 
	     peq->peqd->iConnectionIndices,
	     sizeof(peq->peqd->ppiSerial2ConnectionIndex[0]),
	     comparator);

	iResult = 1;
    }

    //- return result

    return(iResult);
}


