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


#include <neurospaces/importedfile.h>
#include <neurospaces/parsersupport.h>
#include <neurospaces/pidinstack.h>

#ifdef HeccerConnect_with_ppq

#include <neurospaces/projectionquery.h>
#include <neurospaces/solverinfo.h>

#endif


#include "heccer/addressing.h"
#include "heccer/heccer.h"
#include "heccer/neurospaces/segments.h"
#include "heccer/neurospaces/heccer.h"


/// 
/// \arg pheccer a heccer.
/// \arg ped the event distributor to be used.
/// \arg ppq global projection query.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Connect this heccer to its assigned event distributor.
///
/// \details
/// 
///	 Likely to use indices, initialized with HeccerCompileP2().
/// 

int HeccerConnectDistributor(struct simobj_Heccer *pheccer, struct EventDistributor *ped, struct SolverRegistry *psr, struct ProjectionQuery *ppq)
{
    //- check for errors

    if (pheccer->iErrorCount)
    {
	fprintf(stderr, "*** Error: HeccerConnectDistributor() cannot a heccer with %i errors\n", pheccer->iErrorCount);

	return(0);
    }

    //- set default result : ok

    int iResult = 1;

    //- connect this heccer spikegens to the event distributor.

    if (ped)
    {
	if (pheccer->ped && pheccer->ped != ped)
	{
	    fprintf(stderr, "*** Error: HeccerConnectDistributor() cannot have multiple event distributors per heccer\n");
	}
	else
	{
	    pheccer->ped = ped;

	    int iRanged = EventDistributorSetSerialRange(ped, pheccer->inter.iSerialStart, pheccer->inter.iSerialEnd);

	    if (!iRanged)
	    {
		fprintf(stderr, "*** Error: HeccerConnectDistributor() cannot register the serial identifier range in its event distributor\n");
	    }
	}
    }

#ifdef HeccerConnect_with_ppq

    // \todo use projection query to loop through all event receivers
    // and, given their serials, fill in the iDiscreteTarget values,
    // using EventQueuerSerial2ConnectionIndex().  The event queuer to
    // be used is given by the CPU core number.

    //- if we got a projection query

    if (ppq)
    {
	//- loop over all connections

	int iConnections = ProjectionQueryCountConnections(ppq);

	//- loop over all event receivers

	int iLastPost = -1;

	//- receiver count

	int iReceiver = -1;

	int i;

	for (i = 0 ; i < iConnections ; i++)
	{
	    struct CachedConnection *pcconn = OrderedConnectionCacheGetEntry(ppq->poccPost, i);

	    //- when we are dealing with a new pre-synaptic source

	    if (iLastPost != pcconn->iPost)
	    {
		//- increment receiver count

		iReceiver++;

		//- register this pre-synaptic serial

		iLastPost = pcconn->iPost;

		//- if this is the correct heccer

		struct SolverInfo *psi = SolverRegistryGetForAbsoluteSerial(psr, pcconn->iPost);

		void *pvSolver = psi->pvSolver;

		if (pvSolver == (void *)pheccer)
		{
		    //- get heccer variable of iDiscreteTarget in mops, post-synaptic targets in the event queuer matrix

		    double *pdDiscreteTarget = HeccerAddressVariable(pheccer, iLastPost, "postsyn_targets");

		    if (pdDiscreteTarget)
		    {
			int *piDiscreteTarget = (int *)pdDiscreteTarget;

			//- fill in target index: is receiver count

			*piDiscreteTarget = iReceiver;
		    }
		    else
		    {
			HeccerError
			    (pheccer,
			     NULL,
			     "Cannot find synchan target field for synchan with serial %i",
			     iLastPost);
		    }
		}
		else
		{
		    HeccerError
			(pheccer,
			 NULL,
			 "Requested this heccer to obtain information about a field solved by another heccer (%s)",
			 psi->pcSolver);
		}
	    }
	}
    }

#endif

    //- return result

    return(iResult);
}


/// 
/// \arg pheccer a heccer.
/// \arg peq the event queuer to be used.
/// \arg ppq global projection query.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Connect this heccer to its assigned event distributor.
///
/// \details
/// 
///	 Likely to use indices, initialized with HeccerCompileP2().
/// 

int HeccerConnectQueuer(struct simobj_Heccer *pheccer, struct EventQueuer *peq, struct SolverRegistry *psr, struct ProjectionQuery *ppq)
{
    //- check for errors

    if (pheccer->iErrorCount)
    {
	fprintf(stderr, "*** Error: HeccerConnectQueuer() cannot a heccer with %i errors\n", pheccer->iErrorCount);

	return(0);
    }

    //- set default result : ok

    int iResult = 1;

    //- connect this heccer synapses to the event queuer.

    // \todo this will not work when we have one queuer per cpu core.

    if (peq)
    {
	if (pheccer->peq && pheccer->peq != peq)
	{
	    fprintf(stderr, "*** Error: HeccerConnect() cannot have multiple event queuers per heccer\n");
	}
	else
	{
	    pheccer->peq = peq;
	}
    }

#ifdef HeccerConnect_with_ppq

    // \todo use projection query to loop through all event receivers
    // and, given their serials, fill in the iDiscreteTarget values,
    // using EventQueuerSerial2ConnectionIndex().  The event queuer to
    // be used is given by the CPU core number.

    //- if we got a projection query

    if (ppq)
    {
	//- loop over all connections

	int iConnections = ProjectionQueryCountConnections(ppq);

	//- loop over all event receivers

	int iLastPost = -1;

	//- receiver count

	int iReceiver = -1;

	int i;

	for (i = 0 ; i < iConnections ; i++)
	{
	    struct CachedConnection *pcconn = OrderedConnectionCacheGetEntry(ppq->poccPost, i);

	    //- when we are dealing with a new pre-synaptic source

	    if (iLastPost != pcconn->iPost)
	    {
		//- increment receiver count

		iReceiver++;

		//- register this pre-synaptic serial

		iLastPost = pcconn->iPost;

		//- if this is the correct heccer

		struct SolverInfo *psi = SolverRegistryGetForAbsoluteSerial(psr, pcconn->iPost);

		void *pvSolver = psi->pvSolver;

		if (pvSolver == (void *)pheccer)
		{
		    //- get heccer variable of iDiscreteTarget in mops, post-synaptic targets in the event queuer matrix

		    double *pdDiscreteTarget = HeccerAddressVariable(pheccer, iLastPost, "postsyn_targets");

		    if (pdDiscreteTarget)
		    {
			int *piDiscreteTarget = (int *)pdDiscreteTarget;

			//- fill in target index: is receiver count

			*piDiscreteTarget = iReceiver;
		    }
		    else
		    {
			HeccerError
			    (pheccer,
			     NULL,
			     "Cannot find synchan target field for synchan with serial %i",
			     iLastPost);
		    }
		}
		else
		{
		    HeccerError
			(pheccer,
			 NULL,
			 "Requested this heccer to obtain information about a field solved by another heccer (%s)",
			 psi->pcSolver);
		}
	    }
	}
    }

#endif

    //- return result

    return(iResult);
}


/// 
/// \arg pheccer a heccer.
/// \arg pvNeurospaces model-container.
/// \arg pcModel model identifier in the model-container.
/// \arg pvEventDistributor event distributor of this heccer.
/// \arg pvEventQueuer event queuer of this heccer.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Connect this heccer to its assigned event distributor.
///
/// \details
/// 
///	 Likely to use indices, initialized with HeccerCompileP2().
/// 

int HeccerConstruct(struct simobj_Heccer *pheccer, void *pvNeurospaces, char *pcModel, void *pvEventDistributor, void *pvEventQueuer)
{
    //- the event_distributor is an event_distributor

    struct EventDistributor *ped = (struct EventDistributor *) pvEventDistributor;

    pheccer->ped = ped;

    //- the event_distributor is an event_distributor

    struct EventQueuer *peq = (struct EventQueuer *) pvEventQueuer;

    pheccer->peq = peq;

    //- the modeling service is neurospaces

    struct Neurospaces *pneuro = (struct Neurospaces *) pvNeurospaces;

    //- set default result : ok

    int iResult = 1;

    //- register the modelname in the heccer

    pheccer->pcName = strdup(pcModel);

    //- lookup the model

    struct PidinStack *ppistModel = PidinStackParse(pcModel);

    if (!ppistModel)
    {
	fprintf(stderr, "HeccerConstruct: cannot parse model name %s\n", pcModel);

	return(FALSE);
    }

    //- allocate the translation service structures

    struct TranslationServiceData *ptsd
	= (struct TranslationServiceData *) calloc(1, sizeof(struct TranslationServiceData));

    struct TranslationService *pts
	= (struct TranslationService *) calloc(1, sizeof(struct TranslationService));

    pts->ptsd = ptsd;

    pts->ptsd->pneuro = pneuro;

    //- allocate pidin stack pointing to root

    struct PidinStack *ppistRoot = PidinStackCalloc();

    if (!ppistRoot)
    {
	fprintf(stderr, "HeccerConstruct: cannot allocate a root context for %s\n", pcModel);

	return(FALSE);
    }

    PidinStackSetRooted(ppistRoot);

    /// \note gosh, I had to do the same hack when integrating neurospaces
    /// \note with genesis2/hsolve.

    struct ParserContext *pacRoot = pneuro->pacRootContext;

    struct ImportedFile *pifRoot
	= ParserContextGetImportedFile(pacRoot);

    /// \note depending on how the linking is done, there can be multiple
    /// \note instances of neurospaces around.  The following is a hack to
    /// \note enforce the singleton (a bit)

/*     fprintf(stdout, "HeccerConstruct(): root import is %p\n", ImportedFileGetRootImport()); */

    ImportedFileSetRootImport(pifRoot);

/*     fprintf(stdout, "HeccerConstruct(): root import is %p\n", ImportedFileGetRootImport()); */

    //- update caches

    struct symtab_HSolveListElement *phsleRoot
	= PidinStackLookupTopSymbol(ppistRoot);

    ptsd->ppistRoot = ppistRoot;

    ptsd->phsleRoot = phsleRoot;

    //- set model

    struct symtab_HSolveListElement *phsleModel
	= PidinStackLookupTopSymbol(ppistModel);

    ptsd->iModel = PidinStackToSerial(ppistModel);

    if (ptsd->iModel == INT_MAX)
    {
	/// \note don't care about memory leak right now, consider this
	/// \note right now as a fatal crash

	fprintf(stderr, "HeccerConstruct: cannot find model %s\n", pcModel);

	return(FALSE);
    }

    if (!HeccerNeurospacesSegments2Compartments(pts))
    {
	/// \note don't care about memory leak right now, consider this
	/// \note right now as a fatal crash

	fprintf(stderr, "HeccerConstruct: compartment initialization failed for %s\n", pcModel);

	return(FALSE);
    }

    if (!HeccerNeurospacesMechanisms2MathComponents(pts))
    {
	/// \note don't care about memory leak right now, consider this
	/// \note right now as a fatal crash

	fprintf(stderr, "HeccerConstruct: mechanism initialization failed for %s\n", pcModel);

	return(FALSE);
    }

    //- set service structures

    pheccer->pts = pts;

    //- initialize the range of the intermediary, for the addressing
    //- function

    /// \note note: closed interval, would probably be better to use a halve
    /// \note open interval.

    /// \todo HeccerConstruct() should not touch inter.
    /// \todo move or copy the field iSerialStart to ptsd

    pheccer->inter.iSerialStart = ADDRESSING_NEUROSPACES_2_HECCER(ptsd->iModel);

    pheccer->inter.iSerialEnd = ADDRESSING_NEUROSPACES_2_HECCER(ptsd->iModel + SymbolGetPrincipalNumOfSuccessors(phsleModel));

    //- free allocated data

    PidinStackFree(ppistModel);

    //- return result

    return(iResult);
}


