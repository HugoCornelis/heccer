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
#include <string.h>
#include <strings.h>

#include <neurospaces/components/attachment.h>
/* #include <neurospaces/function.h> */
#include <neurospaces/parsersupport.h>
#include <neurospaces/pidinstack.h>
#include <neurospaces/treespacetraversal.h>

#include "heccer/addressing.h"
#include "heccer/compartment.h"
#include "heccer/event.h"
#include "heccer/intermediary.h"
#include "heccer/mathcomponent.h"
#include "heccer/neurospaces/connections.h"
#include "heccer/neurospaces/heccer.h"
#include "heccer/service.h"


/*
 * A structure for storing error states.
 *
 */

#define MATH_COMPONENT_MAX_ERRORS 200

struct MathComponentError
{

    int iStatus;
  
    char * pcError;

};


struct MathComponentErrorReport
{

    int iNumErrors;

    struct MathComponentError mce[MATH_COMPONENT_MAX_ERRORS];

};


struct MathComponentData
{
    /// solution engine

    struct Heccer *pheccer;

    /// compartment number

    int iCompartment;

    /// compartment 2 mechanism convertor

    int *piC2m;

    /// current compartment

    struct symtab_HSolveListElement *phsleCompartment;

    struct PidinStack *ppistCompartment;

    /// array of all math component types

    int iDescendants;

    int iCurrentType;

    int *piTypes;

    /// current mathcomponent

    struct MathComponent * pmc;

    /// number of spikegens

    int iSpikeGens;

    /// operational status: positive is positive, negative is negative (error)

    int iStatus;

    char pcContext[1000];

    char *pcMessage;

    /// channels that contribute to a pool

    int iConnectors;

    int **ppiConnectors;


    struct MathComponentErrorReport mcer;

    

};


#define STATUS_OVERFLOW -1
#define STATUS_UNKNOWN_TYPE -2
#define STATUS_MANY_POOLS -3
#define STATUS_MEMORY -4
#define STATUS_CONSISTENCY -5
#define STATUS_UNRESOLVABLE_PARAMETERS -6
#define STATUS_MANY_CHANNELS -7
#define STATUS_UNKNOWN_ERROR -8
#define STATUS_NON_CHANNEL_OUTPUTS_IK -9
#define STATUS_CONSTANT_NERNST -10
#define STATUS_NON_POOL_FOR_NERNST -11
#define STATUS_ILLEGAL_PARAMETER_VALUES -12
#define STATUS_UNQUALIFIABLE_FILENAME -13
#define STATUS_UNKNOWN_CHANNEL_TYPE1 -14
#define STATUS_UNKNOWN_CHANNEL_TYPE2 -15
#define STATUS_UNKNOWN_CHANNEL_TYPE3 -16

static
char *ppcStatusMessages[] =
{
    NULL,
    "overflow",
    "unknown mechanism type found in the intracellular mechanisms of the model",
    "many_pools: channels can have at most one concentration dependency",
    "out of memory",
    "found an internal inconsistency during typing of the model intracellular mechanisms",
    "unresolvable parameters: the model container does not associate a numerical value with one of the parameters",
    "many_channels: an exponential decay concentration pool had to many channel feeds (max is EXPONENTIALDECAY_CONTRIBUTORS)" ,
    "unknown_error during channel examination",
    "non_channel_outputs_ik: something feeds a current to a pool, but it is not a channel while it should",
    "constant_nernst: the nerst equation must be connected to an internal concentration pool",
    "non_pool_for_nernst: the internal concentration of a nerst equation is not connected to a concentration pool",
    "illegal_parameter_values: some parameters have values that don't make sense from a mathematical viewpoint",
    "unqualifiable_filename: a parameter filename cannot be resolved to an existing file",
    "cannot determine the value of a channel type parameter",
    "unknown_channel_type2",
    "unknown_channel_type3",
    NULL,
};


/* static */
/* int */
/* MathComponentDataStatusSet(struct MathComponentData * pmcd, int iStatus, struct PidinStack *ppist); */

static
int
MathComponentError(struct MathComponentData * pmcd, int iStatus, char *pcError);


static
int
MathComponentPrintErrorReport(struct MathComponentData * pmcd);



int DESConstruct(struct ProjectionQuery *ppq)
{
    //- allocate an array for registration of event distributors

    int iPreSerials = ProjectionQueryCountPreSerials(ppq);

    struct EventDistributor **pped = calloc(iPreSerials, sizeof(*pped));

    if (!pped)
    {
	return(-1);
    }

    //- construct event distributors

    {
	//- loop over all pre-synaptic serials

	int iLastPre = -1;

	int i;

	for (i = 0 ; i < iPreSerials ; i++)
	{
	    //- if this connection has a different pre-synaptic serial

	    struct CachedConnection *pcconn = OrderedConnectionCacheGetEntry(ppq->poccPre, i);

	    if (iLastPre != pcconn->iPre)
	    {
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

		pped[i] = ped;
	    }
	}
    }

    // \todo loop over all solver registrations and register the correct ped

    //- total number of CPU cores is 1

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
	//- loop over the cores

	int i;

	for (i = 0 ; i < iCores ; i++)
	{
	    //- construct an event queuer for this core

	    struct EventQueuerMatrix *ppeqm = EventQueuerDataNew(ppq);

	    struct EventQueuer *peq = EventQueuerNew(ppeqm);

	    //- register this event queuer

	    ppeq[i] = peq;
	}
    }

    // \todo loop over all distributors and connect them with the correct queuers

    // \todo loop over all the queuers and connect them with the correct solvers
}


struct EventQueuerMatrix * EventQueuerDataNew(struct ProjectionQuery *ppq)
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


/* static */
/* int */
/* MathComponentDataStatusSet(struct MathComponentData * pmcd, int iStatus, struct PidinStack *ppist) */
/* { */
/*     //- set default result: current status */

/*     int iResult = pmcd->iStatus; */

/*     //- if everything still ok */

/*     if (iResult > 0) */
/*     { */
/* 	//- get string from context */

/* 	PidinStackString(ppist, pmcd->pcContext, sizeof(pmcd->pcContext)); */

/* 	//- set new status */

/* 	pmcd->iStatus = iStatus; */

/* 	//- set result: new status */

/* 	iResult = pmcd->iStatus; */
/*     } */

/*     //- return result */

/*     return(iResult); */
/* } */


static
int
MathComponentError(struct MathComponentData * pmcd, int iStatus, char *pcError)
{

    if(!pmcd || pmcd->mcer.iNumErrors == MATH_COMPONENT_MAX_ERRORS)
	return 0;

    pmcd->mcer.mce[ pmcd->mcer.iNumErrors ].iStatus = iStatus; 

    pmcd->mcer.mce[ pmcd->mcer.iNumErrors ].pcError = pcError;

     
    pmcd->mcer.iNumErrors++; 



    return 1;


}


static
int
MathComponentPrintErrorReport(struct MathComponentData * pmcd)
{


    int i;


    fprintf(stderr,"%d errors for context: %s\n",pmcd->mcer.iNumErrors , pmcd->pcContext);


    for( i = 0; i < pmcd->mcer.iNumErrors; i++ )
    {

	switch( pmcd->mcer.mce[i].iStatus )
	{

	case STATUS_UNRESOLVABLE_PARAMETERS:
	    fprintf(stderr,"\tUnresolvable Parameter: %s\n", pmcd->mcer.mce[i].pcError);
	    break;



	default:
	    fprintf(stderr,"\tError: %s\n", pmcd->mcer.mce[i].pcError);
	}
    


    }


    return 1;
}


