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
///	iTargets..: index of targets table.
///
/// RTN..: int
///
///	success of operation.
///
/// DESCR: Generate event for associated targets.
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
///	iSource...: index of targets table.
///
/// RTN..: double
///
///	activation delivered by the events, -1.0 for failure.
///
/// DESCR: Receive event for given source.
///
/// **************************************************************************

double HeccerEventReceive(struct Heccer *pheccer, int iSource, int iTarget)
{
    //- set default result: failure

    double dResult = -1.0;

    //- get pointer to event distributor

    struct EventQueuer *peq = pheccer->peq;

    //- tell the distributor to distribute the event over the targets

    if (peq->eventReceive)
    {
	dResult = peq->eventReceive(peq, pheccer->dTime, iSource);
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


