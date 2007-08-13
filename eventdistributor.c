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
#if USE_SGLIB

#include "heccer/sglib.h"

#endif


//o
//o An event is an abstraction of a point in time where a solved variable
//o crossed a (possibly solved) threshold.  The events are delivered to
//o an event distributor, that distributes the events to event queuers.
//o An event queuer queues the event until it is delivered to a target,
//o normally the target is a solver.
//o
//o An event list is the core of the implementation of an event queuer.
//o Other possible implementation candidates are:
//o
//o 1. A heap, for variable event list size, with an average number
//o    of events above 10000, for those simulation times where there
//o    are events in the queue.  Bursting networks are typical examples.
//o
//o 2. An adaptive calendar queue, for a number of events that is
//o    about constant, for networks that are uniformly active.
//o
//o 3. An Splay tree is a candidate too, see the Neuron simulator.  I have
//o    strong doubts that it performs better than a heap for neural
//o    simulations.
//o
//o From my own experience, the used algorithm for the event queue is of
//o minor importance for simulation of networks with detailed cell
//o morphologies using the Genesis simulator, because Genesis distributes
//o the events to many, many independent queues, such that each queue size
//o is very small (for the simulations that I have investigated, less than
//o 100 events).  A simple sorted list does better than any complicated
//o data structure, according to my results (unpublished, it is difficult
//o to publish anything that fails).
//o 

typedef struct EventList
{
    struct EventList *pelLater;
    struct EventList *pelEarlier;
    int iTarget;
    double dTime;
}
    EventList;

#if USE_SGLIB

#define EVENTLIST_COMPARATOR(e1, e2) (e1->dTime > e2->dTime)

SGLIB_DEFINE_DL_LIST_PROTOTYPES(EventList, EVENTLIST_COMPARATOR, pelEarlier, pelLater);
SGLIB_DEFINE_DL_LIST_FUNCTIONS(EventList, EVENTLIST_COMPARATOR, pelEarlier, pelLater);

EventList *elEvents;

#else

static EventList *pelEventFirst = NULL;
static EventList *pelEventLast = NULL;


static EventList * EventListDequeue(void)
{
    EventList * pelResult = pelEventFirst;

    if (pelEventFirst)
    {
	//- one event in list

	if (pelEventFirst == pelEventLast)
	{
	    //- set: none left

	    pelEventFirst = NULL;
	    pelEventLast = NULL;
	}

	//- more than one event in list

	else
	{
	    //- set: new first event

	    pelEventFirst = pelEventFirst->pelLater;

	    //- set: earlier event for new first has been removed

	    pelEventFirst->pelEarlier = NULL;
	}
    }

    return(pelResult);
}


static int EventListInsert(EventList *pel)
{
    //- if there are elements in the list

    if (pelEventLast)
    {
	//- loop over list starting at last event

	EventList *elCurrent = pelEventLast;

	while (elCurrent)
	{
	    //- if insertion position found

	    if (elCurrent->dTime < pel->dTime)
	    {
		//- link new

		pel->pelLater = elCurrent->pelLater;

		//- protect for last event in list

		if (pel->pelLater)
		{
		    pel->pelLater->pelEarlier = pel;
		}
		else
		{
		    pelEventLast = pel;
		}

		pel->pelEarlier = elCurrent;
		elCurrent->pelLater = pel;

		//- break loop

		break;
	    }

	    //- next event: towards start of list

	    elCurrent = elCurrent->pelEarlier;
	}

	//- if new is earliest element (the unlikely case)

	if (!elCurrent)
	{
	    pel->pelEarlier = NULL;
	    pel->pelLater = pelEventFirst;

	    if (pel->pelLater)
	    {
		pel->pelLater->pelEarlier = pel;
	    }

	    pelEventFirst = pel;
	}

/* 	//- if new is last element */

/* 	if (elCurrent == elEventLast) */
/* 	{ */
/* 	    el->elLater = NULL; */
/* 	    elEventLast = el; */
/* 	} */
    }

    //- else no elements in the list

    else
    {
	//- set start and end

	pelEventFirst = pel;
	pelEventLast = pel;
    }

    return(1);
}


#endif


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

#if USE_SGLIB

    sglib_EventList_add(&elEvents, elElement);

#else

    iResult = EventListInsert(elElement);

#endif

    //- sort event list

#if USE_SGLIB

    sglib_EventList_sort(&elEvents);

#endif

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

#if USE_SGLIB

    EventList *elElement = sglib_EventList_get_first(elEvents);

#else

    EventList *elElement = EventListDequeue();

#endif

    if (elElement)
    {
#if USE_SGLIB

	sglib_EventList_delete(&elEvents, elElement);

#endif

	int iTarget = elElement->iTarget;

	double dTime = elElement->dTime;

	//- loop over target table

	struct EventQueuerMatrix *ppeqm = &peq->peqd->ppeqm[iTarget];

	//t This code SEGV on './configure --with-random', with optimization turned on.
	//t It does not SEGV, when optimization is turned off (gcc 4.0.3-1ubuntu5).
	//t This behaviour was noticed when using sglib, and when using the builtin
	//t event queue.

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


