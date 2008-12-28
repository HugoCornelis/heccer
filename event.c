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
/// 
/// \arg pheccer a heccer.
///	iTargets..: index of targets table, in the event distributor.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Generate event for specified targets.
/// \details 
/// 

int HeccerEventGenerate(struct Heccer *pheccer, int iTargets)
{
    //- set default result: failure

    int iResult = 0;

    //- get pointer to event distributor

    struct EventDistributor *ped = pheccer->ped;

    //- tell the distributor to distribute the event over the targets

    if (ped->eventDistribute)
    {
	iResult = ped->eventDistribute(ped, pheccer->dTime, iTargets);
    }
    else
    {
	/// \todo HeccerError(number, message, varargs);

	fprintf
	    (stderr,
	     "Heccer the hecc : generating events, but there is no event distribution service.\n");
    }

    //- return result

    return(iResult);
}


/// 
/// 
/// \arg pheccer a heccer.
/// \arg iTarget target identifier (of the event receiver object).
/// 
/// \return double
/// 
///	Activation delivered by the events, FLT_MAX for failure.
/// 
/// \brief Receive event arriving at the specified target.
/// \details 
/// 

double HeccerEventReceive(struct Heccer *pheccer, int iTarget)
{
    //- set default result: failure

    double dResult = FLT_MAX;

    //- get pointer to event distributor

    struct EventQueuer *peq = pheccer->peq;

    //- tell the distributor to distribute the event over the targets

    if (peq->eventDequeue)
    {
	dResult = peq->eventDequeue(peq, pheccer->dTime, iTarget);

	/// \todo call HeccerEventSet() for next event time.

	/// \todo dNext == next event time

	/// \todo HeccerEventSet(pheccer, iTarget, dNext);
    }
    else
    {
	/// \todo HeccerError(number, message, varargs);

	fprintf
	    (stderr,
	     "Heccer the hecc : receiving events, but there is no event queueing service.\n");
    }

    //- return result

    return(dResult);
}


/// 
/// 
/// \arg pheccer a heccer.
/// \arg iTarget index of target.
/// \arg dTime firing time of event.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Associate an event with its target.
/// \details 
/// 

int HeccerEventSet(struct Heccer *pheccer, int iTarget, double dTime)
{
    //- set default result: ok

    int iResult = 1;

    //- get type specific data

    /// \note somehow this needs to use the addressing module or so, preferably during compilation

    struct MatsSpringMass *pmats = (struct MatsSpringMass *)&pheccer->vm.pdMats[iTarget];

    //- if there is no next event

    if (pmats->dNextEvent == -1.0

	//- or the next pending event has a later time stamp than the new one

	|| pmats->dNextEvent > dTime)
    {
	//- overwrite the time stamp for the next event with the time stamp of the incoming event

	pmats->dNextEvent = dTime;
    }

    //- return result

    return(iResult);
}


