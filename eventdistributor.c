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


#include <float.h>
#include <stdlib.h>
#include <stdio.h>

#include "heccer/eventdistributor.h"
#include "heccer/output.h"

#if USE_SGLIB

#include "heccer/sglib.h"

#endif


/*!
 * \file pidinstack.c
 * \author Hugo Cornelis
 *
 *
 * An event is an abstraction of a point in time where a solved variable
 * crossed a (possibly solved) threshold.  The events are delivered to
 * an event distributor, that distributes the events to event queuers.
 * An event queuer queues the event until it is delivered to a target,
 * normally the target is a solver.
 *
 * An event list is the core of the implementation of an event queuer.
 * Other possible implementation candidates are:
 *
 * 1. A heap, for variable event list size, with an average number
 *    of events above 10000, for those simulation times where there
 *    are events in the queue.  Bursting networks are typical examples.
 *
 * 2. An adaptive calendar queue, for a number of events that is
 *    about constant, for networks that are uniformly active.
 *
 * 3. An Splay tree is a candidate too, see the Neuron simulator.  I have
 *    strong doubts that it performs better than a heap for neural
 *    simulations.
 *
 * From my own experience, the used algorithm for the event queue is of
 * minor importance for simulation of networks with detailed cell
 * morphologies using the Genesis simulator, because Genesis distributes
 * the events to many, many independent queues, such that each queue size
 * is very small (for the simulations that I have investigated, less than
 * 100 events).  A simple sorted list does better than any complicated
 * data structure, according to my results (unpublished, it is difficult
 * to publish anything that fails, which is sad, as we learn the most
 * from our mistakes).
 *
 */


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


/// 
/// \arg ped event distributor.
/// \arg pog output object.
/// \arg iType 1: OutputGeneratorTimedStep() used to send the event.
/// \arg iTarget 
/// 
/// \return int
/// 
///	number of allocated connections, -1 for failure.
/// 
/// \brief Add an output connection to the connection matrix.
/// 

int
EventDistributorAddConnection
(struct EventDistributor *ped, struct OutputGenerator *pog, int iType)
{
    //- set default result: failure

    int iResult = -1;

    //- get matrix data

    struct EventDistributorData *pedd = ped->pedd;

    //- if space available

    if (pedd->iLast < pedd->iConnections)
    {
	//- fill in data

	struct EventDistributorMatrix *ppedm = &ped->pedd->ppedm[pedd->iLast];

	ppedm->pvObject = pog;

	/// \note output objects don't have an internal target for now,
	/// \note could be changed in the future.  -1 means undefined, see
	/// \note spiker1 test case.

	ppedm->iTarget = -1;

	if (iType == 1)
	{
	    ppedm->pvFunction = OutputGeneratorTimedStep;
	}

	//- increment connection count

	pedd->iLast++;
    }

    //- return result

    return(iResult);
}


/// 
/// \arg pedd event distributor data.
/// \arg iEntry entry number to get access to.
/// 
/// \return struct EventDistributorMatrix *
/// 
///	a single entry in the connection matrix, NULL for failure.
/// 
/// \brief Get access to an entry in the connection matrix.
/// 

struct EventDistributorMatrix *
EventDistributorDataGetEntry(struct EventDistributorData *pedd, int iEntry)
{
    //- set default result: failure

    struct EventDistributorMatrix *ppedmResult = NULL;

    //- compute result

    ppedmResult = &pedd->ppedm[iEntry];

    //- return result

    return(ppedmResult);
}


/// 
/// \arg iConnections number of connections in the matrix.
/// 
/// \return struct EventDistributorData *
/// 
///	a connection matrix, NULL for failure.
/// 
/// \brief Construct an empty connection matrix.
/// 

struct EventDistributorData *
EventDistributorDataNew(int iConnections)
{
    //- set default result: allocate data

    struct EventDistributorData *peddResult = calloc(1, sizeof(*peddResult));

    //- allocate connection matrix

    struct EventDistributorMatrix *ppedm
	= calloc(iConnections + 1, sizeof(*ppedm));

    //- fill in result

    peddResult->iConnections = iConnections;
    peddResult->iLast = 0;
    peddResult->ppedm = ppedm;

    //- return result

    return(peddResult);
}


/// 
/// \arg ped event distributor.
/// \arg iType type of setup to perform.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Initiate the event distributor service.
///
/// \details 
/// 
///	Initiation means setup internal state, at this moment this
///	only involves initializing the distribution function.
/// 
/// \note
/// 
///	I consider this function a hack that gets around swig
///	deficiencies in an acceptable way (or I don't have enough
///	knowledge of swig).  To extend: add new iType values, and map
///	to your own functions.
/// 

int
EventDistributorInitiate
(struct EventDistributor *ped, int iType)
{
    //- set default result: failure

    int iResult = 0;

    //- if known type

    if (iType == 1)
    {
	//- set distribution function

	ped->eventDistribute = EventDistributorSend;

	//- set result: ok

	iResult = 1;
    }

    //- return result

    return(iResult);
}


/// 
/// \arg ppedm event distributor connection matrix.
/// 
/// \return struct EventDistributor
/// 
///	An event distributor.
/// 
/// \brief Allocate an event distributor.
/// 

struct EventDistributor *
EventDistributorNew
(struct EventDistributorData *pedd)
{
    //- set default result: allocate

    struct EventDistributor *pedResult = calloc(1, sizeof(*pedResult));

    if (!pedResult)
    {
	return(NULL);
    }

    pedResult->eventDistribute = EventDistributorSend;

    //- link the distributor with the connection matrix

    pedResult->pedd = pedd;

    //- return result

    return(pedResult);
}


/// 
/// \arg ped an event distributor.
/// \arg iSerial serial of a bio component that generates spikes.
/// 
/// \return int
/// 
///	corresponding index in the connection matrix, -1 for not found.
/// 
/// \brief Lookup a spikegen serial, return the internal index.
/// 

int EventDistributorSerial2Index(struct EventDistributor *ped, int iSerial)
{
    //- set default result: failure

    int iResult = -1;

    //- loop over connection matrix

    int iConnection;

    for (iConnection = 0 ; iConnection < ped->pedd->iLast ; iConnection++)
    {
	//- if serials match

	struct EventDistributorMatrix *ppedm = &ped->pedd->ppedm[iConnection];

	if (ppedm->iSerial == iSerial)
	{
	    //- set result

	    iResult = iSerial;

	    //- break loop

	    break;
	}
    }

    //- return result

    return(iResult);
}


/// 
/// \arg ped an event distributor.
/// \arg iTargets index of target objects and target ports.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Distribute an event over the targets.
/// 

int EventDistributorSend(struct EventDistributor *ped, double dTime, int iTargets)
{
    //- set default result: ok

    int iResult = 1;

    //- get matrix data

    struct EventDistributorData *pedd = ped->pedd;

    //- loop over target table

    struct EventDistributorMatrix *ppedm = &pedd->ppedm[iTargets];

    while (ppedm && ppedm->pvFunction)
    {
	//- get target port index

	int iTarget = ppedm->iTarget;

	//- call the target object

	/// \note possibly calls directly to HeccerOutput,
	/// \note possibly calls to the EventQueuer to queue the object
	/// \note other hooks possible.

	iResult = iResult && ppedm->pvFunction(ppedm->pvObject, dTime, iTarget);

	//- next table entry

	ppedm++;
    }

    //- return result

    return(iResult);
}


/// 
/// \arg peq an event queuer.
/// \arg iTarget target object index.
/// 
/// \return double
/// 
///	Sum of weights of arriving events, FLT_MAX for failure.
/// 
/// \brief Dequeue events for the given target, return the summed weights.
/// 

double EventQueuerDequeue(struct EventQueuer *peq, double dTime, int iTarget)
{
    //- set default result: no weights

    double dResult = 0.0;

    //- loop over events for this target until this time

    /// \todo loop over events for this target until this time

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


/// 
/// \arg peq an event queuer.
/// \arg dTime time the event arrives.
/// \arg iSource source identifier.
/// \arg iTarget target identifier.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Put an event in the queue untill it fires.
/// 

int EventQueuerEnqueue(struct EventQueuer *peq, double dTime, /* int iSource,  */int iTarget)
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


/// 
/// \arg ppeqm event queuer connection matrix.
/// 
/// \return struct EventQueuer
/// 
///	An event queuer.
/// 
/// \brief Allocate an event queuer.
/// 

struct EventQueuer * EventQueuerNew(struct EventQueuerMatrix *ppeqm)
{
    //- set default result: allocate

    struct EventQueuer *peqResult = calloc(1, sizeof(*peqResult));

    if (!peqResult)
    {
	return(NULL);
    }

    peqResult->eventDequeue = EventQueuerDequeue;

/*     peqResult->eventEnqueue = EventQueuerEnqueue; */

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


/// 
/// \arg peq event queuer.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Process events in the queue, forward the ones that should fire.
/// 

int iTarget = -1;

struct EventQueuerMatrix *ppeqm = NULL;

EventList *elElement = NULL;

int EventQueuerProcess(struct EventQueuer *peq)
{
    //- set default result: ok

    int iResult = 1;

#if USE_SGLIB

    elElement = sglib_EventList_get_first(elEvents);

#else

    elElement = EventListDequeue();

#endif

    if (elElement)
    {
#if USE_SGLIB

	sglib_EventList_delete(&elEvents, elElement);

#endif

	iTarget = elElement->iTarget;

	double dTime = elElement->dTime;

	//- loop over target table

	ppeqm = &peq->peqd->ppeqm[iTarget];

	/// \todo This code SEGV on './configure --with-random', with optimization turned on.
	/// \todo It does not SEGV, when optimization is turned off (gcc 4.0.3-1ubuntu5).
	/// \todo This behaviour was noticed when using sglib, and when using the builtin
	/// \todo event queue.

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


/// 
/// \arg peq an event queuer.
/// \arg iSerial serial to convert.
/// 
/// \return int
/// 
///	connection matrix index, -1 for failure.
/// 
/// \brief Convert an external serial to a connection matrix index.
/// 

int EventQueuerSerial2ConnectionIndex(struct EventQueuer *peq, int iSerial)
{
    //- set default result: failure.

    int iResult = -1;

    //- if there is an initialized event queuer

    if (peq && peq->peqd && peq->peqd->iConnectionIndices > 0)
    {
	/// \note binary search

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


/// 
/// \arg peq an event queuer.
/// \arg iSerial serial to convert.
/// \arg iIndex connection index.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Add an external serial to that was added to the connection matrix.
/// 

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
	    /// \todo HeccerError(number, message, varargs);

	    fprintf
		(stderr,
		 "Heccer the hecc : connection matrix translator overflow (please increase EVENTQUEUER_MAX_CONNECTIONS in the source).\n");
	}
    }

    //- return result

    return(iResult);
}


/// 
/// \arg peq an event queuer.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Sort the serial 2 connection index array.
/// 

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
	/// \todo HeccerError(number, message, varargs);

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


