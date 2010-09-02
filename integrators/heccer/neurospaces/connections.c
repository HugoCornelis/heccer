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


#include <stdio.h>
#include <stdlib.h>

#include <neurospaces/pidinstack.h>
#include <neurospaces/projectionquery.h>
#include <neurospaces/solverinfo.h>

#include "heccer/event.h"
#include "heccer/neurospaces/connections.h"
#include "heccer/neurospaces/heccer.h"


static struct EventQueuerMatrix * EventQueuerDataNew(struct ProjectionQuery *ppq, int iThread);


int DESConstruct(struct SolverRegistry *psr, struct ProjectionQuery *ppq)
{
    //- allocate an array for registration of event distributors

    int iPreSerials = ProjectionQueryCountPreSerials(ppq);

    struct EventDistributor **pped = (struct EventDistributor **)calloc(iPreSerials, sizeof(*pped));

    if (!pped)
    {
	return(-1);
    }

    // \todo this must be replaced with projectionquery traversals

    int *piPreSerials = (int *)calloc(iPreSerials, sizeof(int));

    if (!piPreSerials)
    {
	free(pped);

	return(-2);
    }

    //- construct event distributors

    int iConnections = ProjectionQueryCountConnections(ppq);

    {
	//- loop over all connections

	int iLastPre = -1;

	int i;

	int iPreSerialCount;

	for (i = 0 ; i < iConnections ; i++)
	{
	    //- if this connection has a different pre-synaptic serial from the last one

	    struct CachedConnection *pcconn = OrderedConnectionCacheGetEntry(ppq->poccPre, i);

	    if (iLastPre != pcconn->iPre)
	    {
		//- register this pre-synaptic serial

		iLastPre = pcconn->iPre;

		//- construct an event distributor for this pre-synaptic serial

		// \todo type an arbitrary value: 2 for 1 queuer and 1 spike output

		int iTypeCount = 2;

		struct EventDistributorData *pedd
		    = EventDistributorDataNew(iTypeCount, pcconn->iPre);

		struct EventDistributor *ped = EventDistributorNew(pedd);

		if (!pedd || !ped)
		{
		    return(-1);
		}

		//- register this event distributor

		pped[iPreSerialCount] = ped;

		piPreSerials[iPreSerialCount] = pcconn->iPre;

		//- if a solver has been registered for this pre-synaptic serial

		struct SolverInfo *psi = SolverRegistryGetForAbsoluteSerial(psr, pcconn->iPre);

		void *pvSolver = psi->pvSolver;

		if (pvSolver)
		{
		    // \todo we simply assume it is a heccer: type discrimination required here

		    struct Heccer *pheccer = (struct Heccer *)pvSolver;

		    //- register the event distributor for this solver

		    // \todo error checking, prevent multiple ped registrations maybe.

		    pheccer->ped = ped;
		}
		else
		{
		    fprintf(stderr, "*** Error: DESConstruct() cannot find a solver for ");

		    struct PidinStack *ppistSolved = SolverInfoPidinStack(psi);

		    PidinStackPrint(ppistSolved, stderr);

		    fprintf(stderr, "\n");
		}

		//- next index

		iPreSerialCount++;
	    }
	}

	if (iPreSerialCount != iPreSerials)
	{
	    fprintf(stderr, "*** Error: DESConstruct() internal system error: iPreSerialCount != iPreSerials\n");
	}
    }

/*     //- loop over all solver registrations and connect the solver with the correct ped */

/*     { */
/* 	//- loop over registrations */

/* 	int i; */

/* 	for (i = 0 ; i < iRegistrations ; i++) */
/* 	{ */
/* 	    //- if there is a solver present */

/* 	    struct SolverInfo *psi = ppsiRegistrations[i]; */

/* 	    void *pvSolver = psi->pvSolver; */

/* 	    if (pvSolver) */
/* 	    { */
/* 		// \todo we simply assume it is a heccer: type discrimination required here */

/* 		struct Heccer *pheccer = (struct Heccer *)pvSolver; */

/* 		//- determine the event distributor for this solver */

/* 		// \todo The index here is incorrect.  We need to */
/* 		// compare the iPre serial of the ped and check if it */
/* 		// is in the interval of the solved serials. */

/* 		struct EventDistributor *ped = pped[i]; */

/* 		pheccer->ped = ped; */
/* 	    } */
/* 	    else */
/* 	    { */
/* 		fprintf(stderr, "*** Error: DESConstruct() cannot find a solver for "); */

/* 		struct PidinStack *ppistSolved = SolverInfoPidinStack(ppsiRegistrations[i]); */

/* 		PidinStackPrint(ppistSolved, stderr); */

/* 		fprintf(stderr, "\n"); */
/* 	    } */
/* 	} */
/*     } */

    //- total number of cpu cores is currently always 1

    int iCores = 1;

    //- allocate an array for registration of event distributors

    struct EventQueuer **ppeq = calloc(iCores, sizeof(*ppeq));

    if (!ppeq)
    {
	// \todo the giant memory leak: pped and everything inside

	return(-1);
    }

    //- construct event queuers

    {
	//- loop over the cpu cores

	int i;

	for (i = 0 ; i < iCores ; i++)
	{
	    //- construct an event queuer for this cpu core

	    struct EventQueuerMatrix *ppeqm = EventQueuerDataNew(ppq, i);

	    struct EventQueuer *peq = EventQueuerNewFromSingleRow(ppeqm);

	    int iAdded = EventQueuerSerial2ConnectionIndexAdd(peq, piPreSerials[0], i);

	    //- register this event queuer

	    ppeq[i] = peq;
	}
    }

    //- loop over all distributors and connect them with the correct queuers

    {
	//- loop over the event distributors

	int i;

	for (i = 0 ; i < iPreSerials ; i++)
	{
	    struct EventDistributor *ped = pped[i];

	    //- register the queuer in the distributor

	    // \todo the first entry is always the queuer

	    int iQueuer = 0;

	    // \todo queuer discrimination for multi threaded implementation

	    int iCore = 0;

	    //- determine the queuer for this pre-synaptic serial

	    struct EventQueuer *peq = ppeq[iCore];

	    //- use the queuer to convert the serial to an index

	    // \todo it looks as if
	    // EventQueuerSerial2ConnectionIndex() currently has two
	    // purposes: one is this conversion, the second is to
	    // convert a serial to an queuer matrix row.

	    int iTarget = EventQueuerSerial2ConnectionIndex(peq, piPreSerials[i]);

	    //- fill in the distribution matrix queuer entry

	    ped->pedd->ppedm[iQueuer].iTarget = iTarget;
	    ped->pedd->ppedm[iQueuer].pvFunction = EventQueuerEnqueue;
	    ped->pedd->ppedm[iQueuer].pvObject = ppeq[iCore];
	}
    }

    //- loop over all the queuers and connect them with the correct solvers

    {
	//- loop over the cpu cores

	int i;

	for (i = 0 ; i < iCores ; i++)
	{
	    //- get event queuer for this cpu core

	    struct EventQueuer *peq = ppeq[i];

	    //- loop over all entries in the queuer matrix

	    int iLastPre = -1;

	    //- initialize distributor index

	    int iDistributor = -1;

	    // \todo in single threaded code the same as number of iPreSerials

	    int j;

	    for (j = 0 ; j < iConnections ; j++)
	    {
		// \todo ProjectionQueryTraverseConnectionsForSpikeGenerator()

		//- if this connection has a different pre-synaptic serial from the last one

		struct CachedConnection *pcconn = OrderedConnectionCacheGetEntry(ppq->poccPre, i);

		if (iLastPre != pcconn->iPre)
		{
		    //- increment distributor index

		    iDistributor++;

		    //- get the matrix row that corresponds to this serial

		    struct EventQueuerMatrix *peqm = EventQueuerGetRowFromSerial(peq, pcconn->iPre);

		    peqm->dDelay = pcconn->dDelay;
		    peqm->dWeight = pcconn->dWeight;
		    peqm->iTarget = pcconn->iPost;

		    // \todo HeccerEventSet() or HeccerEventReceive()

		    peqm->pvFunction = NULL;

		    //- if a solver has been registered for this post-synaptic serial

		    struct SolverInfo *psi = SolverRegistryGetForAbsoluteSerial(psr, pcconn->iPost);

		    peqm->pvObject = NULL;

		    void *pvSolver = psi->pvSolver;

		    if (pvSolver)
		    {
			// \todo we simply assume it is a heccer: type
			// discrimination required here, recycle the logic
			// that is already available in ns-sli
			// nsintegrator.h struct SolverRegistration{}.

			struct Heccer *pheccer = (struct Heccer *)pvSolver;

			//- register the event distributor for this solver

			// \todo error checking, prevent multiple ped registrations maybe.

			pheccer->ped = pped[iDistributor];
		    }
		    else
		    {
			fprintf(stderr, "*** Error: DESConstruct() cannot find a solver for ");

			struct PidinStack *ppistSolved = SolverInfoPidinStack(psi);

			PidinStackPrint(ppistSolved, stderr);

			fprintf(stderr, "\n");
		    }
		}
	    }
	}
    }
}


static struct EventQueuerMatrix * EventQueuerDataNew(struct ProjectionQuery *ppq, int iThread)
{
    //- set default result: success

    struct EventQueuerMatrix *ppeqmResult = NULL;

    //- determine the number of connections

    int iConnections = ProjectionQueryCountConnections(ppq);

    //- allocate event queuer matrix, but not data

    ppeqmResult = (struct EventQueuerMatrix *)calloc(1 + iConnections, sizeof(struct EventQueuerMatrix));

    //- mark the last entry as not used

    ppeqmResult[iConnections].dDelay = DBL_MAX;
    ppeqmResult[iConnections].dWeight = DBL_MAX;
    ppeqmResult[iConnections].iTarget = 0;
    ppeqmResult[iConnections].pvFunction = NULL;
    ppeqmResult[iConnections].pvObject = NULL;

    //- loop over all connections

    int i;

    for (i = 0 ; i < iConnections ; i++)
    {
	//- fill in entry

	ppeqmResult[i].dDelay = ppq->pcc->pcconn[i].dDelay;
	ppeqmResult[i].dWeight = ppq->pcc->pcconn[i].dWeight;
	ppeqmResult[i].iTarget = ppq->pcc->pcconn[i].iPost; //t must subtract the solver root serial
	ppeqmResult[i].pvFunction = HeccerEventSet;
	ppeqmResult[i].pvObject = NULL;
    }

    //- return result

    return(ppeqmResult);
}


