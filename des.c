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

/* #include <experiment/output.h> */

#include "heccer/event.h"
#include "heccer/des.h"


#if USE_SGLIB

#include "heccer/sglib.h"

#endif


/*!
 * \file eventdistributor.c
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


/// 
/// \arg des discrete event system.
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
///	The shorthand DES_DUMP_ALL selects everything except very
///	verbose uninteresting items, DES_DUMP_ALL_EXTENDED selects
///	those items to, while DES_DUMP_ALL_REDUCED selects less.
/// 

int DESDumpV(struct simobj_DES *pdes)
{
    return(DESDump(pdes, stdout, DES_DUMP_ALL));
}

int DESDump(struct simobj_DES *pdes, FILE *pfile, int iSelection)
{
    //- check for errors

    if (pdes->iErrorCount)
    {
	return(FALSE);
    }

    //- set default result : ok

    int iResult = TRUE;

    if (!pfile)
    {
	pfile = stdout;
    }

    //- if dumping distributor matrices

    if (iSelection & DES_DUMP_DISTRIBUTOR_MATRIX)
    {
	//- loop over all distributors

	int i;

	for (i = 0 ; i < pdes->iPreSerials ; i++)
	{
	    struct EventDistributor *ped = pdes->pped[i];

	    if (ped)
	    {
		struct EventDistributorData *pedd = ped->pedd;

		int iConnection;

		for (iConnection = 0 ; iConnection <= pedd->iLast ; iConnection++)
		{
		    struct EventDistributorMatrix *ppedm = &pedd->ppedm[iConnection];

		    fprintf(pfile, "DES: EventDistributor[%i] : iConnection[%i] : (iTarget %i, pvObject{} %s, pvProcess() %s\n", i, iConnection, ppedm->iTarget, ppedm->pvObject ? "yes" : "nil", ppedm->pvProcess ? "yes" : "nil");
		}
	    }
	}
    }

    //- if dumping queuer matrices

    if (iSelection & DES_DUMP_QUEUER_MATRIX)
    {
	//- loop over all queuers

	int i;

	for (i = 0 ; i < pdes->iCores ; i++)
	{
	    struct EventQueuer *peq = pdes->ppeq[i];

	    struct EventQueuerData *peqd = peq->peqd;

	    int iRow;

	    for (iRow = 0 ; iRow < peqd->iRows ; iRow++)
	    {
		int iColumn = 0;

		struct EventQueuerMatrix *ppeqm = NULL;

		for (iColumn = 0, ppeqm = &peqd->ppeqm[iRow][iColumn] ; ppeqm[1].pvAccept ; iColumn++)
		{
		    ppeqm = &peqd->ppeqm[iRow][iColumn];

		    char pcEvent[100];

		    if (ppeqm->pdEvent)
		    {
			sprintf(pcEvent, "%f", *ppeqm->pdEvent);
		    }
		    else
		    {
			strcpy(pcEvent, "nil");
		    }

		    fprintf(pfile, "DES: EventQueuer[%i] : iConnection[%i, %i] : (dDelay %g, dWeight %g, pdEvent %s, pvObject{} %s, pvAccept() %s\n", i, iRow, iColumn, ppeqm->dDelay, ppeqm->dWeight, pcEvent, ppeqm->pvObject ? "yes" : "nil", ppeqm->pvAccept ? "yes" : "nil");

/* 		    ppeqm++; */

/* 		    iColumn++; */
		}
	    }
	}
    }

    //- flush output

    fflush(pfile);

    //- return result

    return(iResult);
}


/// 
/// \arg pdes discrete event system.
/// \arg iSerial context identifier.
///
/// \return struct EventDistributor
/// 
///	Event distributor for this CPU serial.
/// 
/// \brief Get access to the event distributor for this serial.
/// 

struct EventDistributor *DESGetDistributor(struct simobj_DES *pdes, int iSerial)
{
    //- set default result: not found

    struct EventDistributor *pedResult = NULL;

    //- loop over the distributor array

    int i;

    for ( i = 0 ; i < pdes->iPreSerials ; i++)
    {
	//- if the serial is within the range of the current distributor

	struct EventDistributor *ped = pdes->pped[i];

	if (iSerial >= ped->iSerialStart
	    && iSerial <= ped->iSerialEnd)
	{
	    //- found: set result

	    pedResult = ped;

	    break;
	}
    }

    //- return result

    return(pedResult);
}


/// 
/// \arg pdes discrete event system.
/// \arg iCore CPU core identifier.
///
/// \return struct EventQueuer
/// 
///	Event queuer for this CPU core.
/// 
/// \brief Get access to the event queuer for this CPU core.
/// 

struct EventQueuer *DESGetQueuer(struct simobj_DES *pdes, int iCore)
{
    //- set result: from the queuer array

    struct EventQueuer *peqResult = pdes->ppeq[iCore];

    //- return result

    return(peqResult);
}


/// 
/// \return struct simobj_DES *
/// 
///	Empty connectivity system between solvers.
/// 
/// \brief Create a new connectivity system between solvers.
/// 

struct simobj_DES *DESNew(int iHappy)
{
    //- set default result: new des system

    struct simobj_DES *pdesResult = (struct simobj_DES *)calloc(1, sizeof(struct simobj_DES));

    if (!pdesResult)
    {
	// \todo here is the mega memory leak

	return(NULL);
    }

    pdesResult->iCores = 0;
    pdesResult->iPreSerials = 0;
    pdesResult->piPreSerials = 0;
    pdesResult->pped = NULL;
    pdesResult->ppeq = NULL;

    //- return result

    return(pdesResult);
}


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

	    if (pelEventFirst)
	    {
		pelEventFirst->pelEarlier = NULL;
	    }
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
/// \arg pvEventReceive the event receiving function.
/// \arg iTarget object's target identifier when an event is generated
/// on this connection.
/// 
/// \return int
/// 
///	number of allocated connections, -1 for failure.
/// 
/// \brief Add an output connection to the connection matrix.
///
/// \description pvEventReceive will be called to distribute an event
/// to this connection, eg. OutputGeneratorTimedStep() in the
/// experiment package or equivalent.  Its signature must be that of
/// EventQueuerEnqueue().
/// 

int
EventDistributorAddConnection
(struct EventDistributor *ped, void *pvEventReceive, void *pvObject, int iTarget)
{
    //- set default result: failure

    int iResult = -1;

    //- get matrix data

    struct EventDistributorData *pedd = ped->pedd;

    //- if space available

    if (pedd->iLast + 1 < pedd->iConnections)
    {
	//- increment connection count

	pedd->iLast++;

	//- fill in data

	struct EventDistributorMatrix *ppedm = &ped->pedd->ppedm[pedd->iLast];

	ppedm->pvObject = pvObject;

	// \note -1 for target means undefined, see spiker1 test case.

	if (iTarget == -1)
	{
	    fprintf
		(stderr,
		 "*** Warning: EventDistributorAddConnection() with -1 iTarget index.\n");
	}

	ppedm->iTarget = iTarget;

	ppedm->pvProcess = pvEventReceive;

	//- set result: ok

	iResult = 1;
    }
    else
    {
	fprintf
	    (stderr,
	     "Des doodely des: attempt to add more distributor connections than allocated.\n");
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
/// \arg iConnections number of targeted software components.
/// \arg iPre pre-synaptic serial.
/// 
/// \return struct EventDistributorData *
/// 
///	a connection matrix, NULL for failure.
/// 
/// \brief Construct an empty connection matrix.
/// 

struct EventDistributorData *
EventDistributorDataNew(int iComponents, int iPre)
{
    //- set default result: allocate data

    struct EventDistributorData *peddResult = calloc(1, sizeof(*peddResult));

    //- allocate connection matrix

    struct EventDistributorMatrix *ppedm
	= calloc(iComponents + 1, sizeof(*ppedm));

    //- mark the last entry as not used

    if (iPre == -1)
    {
	fprintf
	    (stderr,
	     "*** Warning: EventDistributorDataNew() with -1 iPre index.\n");
    }

    ppedm[iComponents].iTarget = iPre;
    ppedm[iComponents].pvProcess = NULL;
    ppedm[iComponents].pvObject = NULL;

    //- fill in result

    peddResult->iConnections = iComponents;
    peddResult->iLast = -1;
    peddResult->ppedm = ppedm;

    //- we are already using one entry of the matrix

    peddResult->iLast = 0;

    //- return result

    return(peddResult);
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

    //- mark the serial range as invalid

    pedResult->iSerialStart = -1;

    pedResult->iSerialEnd = -1;

    //- return result

    return(pedResult);
}


/// 
/// \arg ped an event distributor.
/// \arg dTime current simulation time.
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

    if (iTargets == -1)
    {
	fprintf
	    (stderr,
	     "*** Warning: EventDistributorSend() with -1 iTargets index.\n");
    }

    //- loop over target table

    struct EventDistributorMatrix *ppedm = &pedd->ppedm[iTargets];

    while (ppedm && ppedm->pvProcess)
    {
	//- get target port index

	int iTarget = ppedm->iTarget;

	if (iTarget == -1)
	{
	    // \todo Note that DES EventDistributorSend() calls the function
	    // OutputGeneratorTimedStep() with an extra argument, namely iTarget.
	    // See the corresponding comments in EventDistributorSend() and
	    // OutputGeneratorTimedStep().

/* 	    fprintf */
/* 		(stderr, */
/* 		 "*** Warning: EventDistributorSend() with -1 iTarget index.\n"); */
	}

	//- call the target object

	// \note possibly calls directly to
	// OutputGeneratorTimedStep(), possibly calls to
	// EventQueuerEnqueue() to queue the object other hooks
	// possible.

	// \todo Note that DES EventDistributorSend() calls the function
	// OutputGeneratorTimedStep() with an extra argument, namely iTarget.
	// See the corresponding comments in EventDistributorSend() and
	// OutputGeneratorTimedStep().

	iResult = iResult && ppedm->pvProcess(ppedm->pvObject, dTime, iTarget);

	//- next table entry

	ppedm++;
    }

    //- return result

    return(iResult);
}


/// 
/// \arg ped an event distributor.
/// \arg iStart start of serial range.
/// \arg iEnd end of serial range.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Distribute an event over the targets.
/// 

int EventDistributorSetSerialRange(struct EventDistributor *ped, int iStart, int iEnd)
{
    //- set default result: ok

    int iResult = 1;

    if (ped->iSerialStart != -1
	|| ped->iSerialEnd != -1)
    {
	return(0);
    }

    //- set range of this distributor

    ped->iSerialStart = iStart;
    ped->iSerialEnd = iEnd;

    //- return result

    return(iResult);
}


/// 
/// \arg peq an event queuer.
/// \arg iTarget target object index.
/// 
/// \return double
/// 
///	Sum of weights of arriving events, DBL_MAX for failure.
/// 
/// \brief Dequeue events for the given target, return the summed weights.
/// 

double EventQueuerDequeue(struct EventQueuer *peq, double dTime, int iTarget)
{
    //- set default result: no weights

    double dResult = 0.0;

    if (iTarget == -1)
    {
	fprintf
	    (stderr,
	     "*** Warning: EventQueuerDequeue() with -1 iTarget index.\n");
    }

    //- loop over events for this target until this time

    /// \todo loop over events for this target until this time

    struct EventQueuerMatrix *ppeqm = &peq->peqd->ppeqm[0][iTarget];

    while (ppeqm
/* 	   && ppeqm->pvFunction */
	   && dResult != DBL_MAX)
    {
	//- get weight for event

	double dWeight = ppeqm->dWeight;

	if (dWeight == DBL_MAX)
	{
	    return(DBL_MAX);
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

    if (iTarget == -1)
    {
	fprintf
	    (stderr,
	     "*** Warning: EventQueuerEnqueue() with -1 iTarget index.\n");
    }

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
/// \arg peq event queuer.
/// \arg iSerial index into the event queuer matrix.
/// 
/// \return struct EventQueuerMatrix
/// 
///	A single row in the event queuer matrix corresponding to the
///	given index.
/// 
/// \brief Map a queuer index to a row.
/// 

struct EventQueuerMatrix * EventQueuerGetRowFromSerial(struct EventQueuer *peq, int iSerial)
{
    //- set default result: failure

    struct EventQueuerMatrix *ppeqmResult = NULL;

    int iRow = EventQueuerSerial2ConnectionIndex(peq, iSerial);

    if (iRow == -1)
    {
	return(NULL);
    }

    if (iRow >= peq->peqd->iRows)
    {
	return(NULL);
    }

/*     //- loop over all rows */

/*     int i; */

/*     for (i = 0 ; i < peq->iRows ; i++) */
    {
/* 	//- access the current row */

/* 	int j = peq->peqd->ppiSerial2ConnectionIndex */

	ppeqmResult = peq->peqd->ppeqm[iRow];

    }

    //- return result

    return(ppeqmResult);
}


/// 
/// \return struct EventQueuer
/// 
///	An event queuer.
/// 
/// \brief Allocate an event queuer, given a single row.
/// 

struct EventQueuer * EventQueuerNew()
{
    //- set default result: allocate

    struct EventQueuer *peqResult = calloc(1, sizeof(*peqResult));

    if (!peqResult)
    {
	return(NULL);
    }

    peqResult->eventDequeue = EventQueuerDequeue;

    struct EventQueuerData *peqd = calloc(1, sizeof(*peqd));

    if (!peqd)
    {
	free(peqResult);

	return(NULL);
    }

    peqResult->peqd = peqd;

    peqd->iConnectionIndices = 0;

    //- insert the row in the matrix

    peqd->ppeqm = (struct EventQueuerMatrix **)calloc(1, sizeof(struct EventQueuerMatrix *));

    peqd->iRows = 0;

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
/// \brief Process events in the queue, forward the ones that fire.
/// 

int EventQueuerProcess(struct EventQueuer *peq, double dCurrentTime)
{
    //- set default result: ok

    int iResult = 1;

/*     fprintf(stdout, "EventQueuerProcess(): processing until %g\n", dCurrentTime); */

#if USE_SGLIB

    EventList *elElement = sglib_EventList_get_first(elEvents);

#else

    EventList *elElement = pelEventFirst;

#endif

    while (elElement && elElement->dTime <= dCurrentTime)
    {

#if USE_SGLIB

	sglib_EventList_delete(&elEvents, elElement);

#else

	elElement = EventListDequeue();

#endif

	int iTarget = elElement->iTarget;

	if (iTarget == -1)
	{
	    fprintf
		(stderr,
		 "*** Warning: EventQueuerProcess() with -1 iTarget index.\n");
	}

	//- loop over target table

	struct EventQueuerMatrix *ppeqm = peq->peqd->ppeqm[iTarget];

	/// \todo This code SEGV on './configure --with-random', with optimization turned on.
	/// \todo It does not SEGV, when optimization is turned off (gcc 4.0.3-1ubuntu5).
	/// \todo This behaviour was noticed when using sglib, and when using the builtin
	/// \todo event queue.

	while (ppeqm && ppeqm->pvAccept)
	{
	    //- add connection delay

	    double dEvent = elElement->dTime + ppeqm->dDelay;

	    //- call the target object

	    iResult = iResult && ppeqm->pvAccept(ppeqm->pvObject, ppeqm->pdEvent, dEvent);

	    //- next table entry

	    ppeqm++;
	}

#if USE_SGLIB

	elElement = sglib_EventList_get_first(elEvents);

#else

	elElement = pelEventFirst;

#endif

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
(struct EventQueuerData *peqd,
 int iSerial,
 int iIndex)
{
    //- set default result: failure.

    int iResult = 0;

    //- if there is an initialized event queuer

    if (peqd)
    {
	//- add the translation of the connection

	if (peqd->iConnectionIndices < EVENTQUEUER_MAX_CONNECTIONS)
	{
	    peqd->ppiSerial2ConnectionIndex[peqd->iConnectionIndices][0] = iSerial;
	    peqd->ppiSerial2ConnectionIndex[peqd->iConnectionIndices][1] = iIndex;

	    peqd->iConnectionIndices++;

	    iResult = 1;
	}
	else
	{
	    fprintf
		(stderr,
		 "Des doodely des: connection matrix translator overflow (please increase EVENTQUEUER_MAX_CONNECTIONS in the source).\n");
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
	fprintf
	    (stderr,
	     "Des doodely des: connection matrix index comparator() encounters entries with the same serial.\n");

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


