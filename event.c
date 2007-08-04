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


#include "heccer/event.h"
#include "heccer/heccer.h"


/// **************************************************************************
///
/// SHORT: HeccerEventGenerate()
///
/// ARGS.:
///
///	pheccer...: a heccer.
///	iTargets..: index of targets table, in the event distributor.
///
/// RTN..: int
///
///	success of operation.
///
/// DESCR: Generate event for specified targets.
///
/// **************************************************************************

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
	//t HeccerError(number, message, varargs);

	fprintf
	    (stderr,
	     "Heccer the hecc : generating events, but there is no event distribution service.\n");
    }

    //- return result

    return(iResult);
}


/// **************************************************************************
///
/// SHORT: HeccerEventReceive()
///
/// ARGS.:
///
///	pheccer...: a heccer.
///	iTarget...: target identifier (of the event receiver object).
///
/// RTN..: double
///
///	Activation delivered by the events, FLT_MAX for failure.
///
/// DESCR: Receive event arriving at the specified target.
///
/// **************************************************************************

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

	//t call HeccerEventSet() for next event time.

	//t dNext == next event time

	//t HeccerEventSet(pheccer, iTarget, dNext);
    }
    else
    {
	//t HeccerError(number, message, varargs);

	fprintf
	    (stderr,
	     "Heccer the hecc : receiving events, but there is no event queueing service.\n");
    }

    //- return result

    return(dResult);
}


/// **************************************************************************
///
/// SHORT: HeccerEventSet()
///
/// ARGS.:
///
///	pheccer...: a heccer.
///	iTarget...: index of target.
///	dTime.....: firing time of event.
///
/// RTN..: int
///
///	success of operation.
///
/// DESCR: Associate an event with its target.
///
/// **************************************************************************

int HeccerEventSet(struct Heccer *pheccer, int iTarget, double dTime)
{
    //- set default result: ok

    int iResult = 1;

    //- get type specific data

    //! somehow this needs to use the addressing module or so, preferably during compilation

    struct MatsSpringMass *pmats = (struct MatsSpringMass *)&((double *)pheccer->vm.pvMats)[iTarget];

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


