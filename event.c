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


#include "heccer/event.h"
#include "heccer/heccer.h"


/// 
/// \arg pheccer a heccer.
/// \arg iTargets index of targets table, in the event distributor.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Generate event for specified targets.
/// 

int HeccerEventGenerate(struct simobj_Heccer *pheccer, int iSource2Targets)
{
    //- set default result: failure

    int iResult = 0;

/*     fprintf */
/* 	(stdout, */
/* 	 "Heccer the hecc: generating events, but there is no valid event distribution service.\n"); */

    //- get pointer to event distributor

    struct EventDistributor *ped = pheccer->ped;

    if (ped)
    {
	//- tell the distributor to distribute the event over the targets

	if (ped->eventDistribute)
	{
	    iResult = ped->eventDistribute(ped, pheccer->dTime, iSource2Targets);
	}
	else
	{
	    /// \todo HeccerError(number, message, varargs);

	    fprintf
		(stderr,
		 "Heccer the hecc: generating events, but there is no valid event distribution service.\n");
	}
    }
    else
    {
	iResult = 1;
    }

    //- return result

    return(iResult);
}


/// 
/// \arg pheccer a heccer.
/// \arg iTarget target identifier (of the event receiver object).
/// 
/// \return double
/// 
///	Activation delivered by the events, DBL_MAX for failure.
/// 
/// \brief Receive event arriving at the specified target.
/// 

double HeccerEventReceive(struct simobj_Heccer *pheccer, int iTarget)
{
    //- set default result: failure

    double dResult = DBL_MAX;

    //- get pointer to event distributor

    struct EventQueuer *peq = pheccer->peq;

    //- ask the queuer for the event activation

    if (peq->eventDequeue)
    {
	dResult = peq->eventDequeue(peq, pheccer->dTime, iTarget);
    }
    else
    {
	/// \todo HeccerError(number, message, varargs);

	fprintf
	    (stderr,
	     "Heccer the hecc: receiving events, but there is no event queueing service.\n");
    }

    //- return result

    return(dResult);
}


/// 
/// \arg pheccer a heccer.
/// \arg pdEvent next time of firing of an event receiver.
/// \arg dTime firing time of event.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Register a new time of firing for an event receiver.
/// 

int HeccerEventSet(struct simobj_Heccer *pheccer, double *pdEvent, double dTime)
{
    //- set default result: ok

    int iResult = 1;

/*     //- get type specific data */

/*     /// \note somehow this needs to use the addressing module or so, preferably during compilation */

/*     struct MatsSpringMass *pmats = (struct MatsSpringMass *)&pheccer->vm.pdMats[iTarget]; */

/*     //- if there is no next event */

/*     if (pmats->dNextEvent == -1.0 */

/* 	//- or the next pending event has a later time stamp than the new one */

/* 	|| pmats->dNextEvent > dTime) */
    {
	//- overwrite the time stamp for the next event with the time stamp of the incoming event

	*pdEvent = dTime;
    }

    //- return result

    return(iResult);
}


