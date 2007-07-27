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


#include "heccer/eventdistributor.h"


/// **************************************************************************
///
/// SHORT: HeccerEventDistribute()
///
/// ARGS.:
///
///	ped.......: an event distributor.
///	ppiTargets: target objects and target ports.
///
/// RTN..: int
///
///	success of operation.
///
/// DESCR: Distribute an event over the targets.
///
/// **************************************************************************

int HeccerEventDistribute(struct EventDistributor *ped, int iTargets)
{
    //- set default result: failure

    int iResult = 0;

    //- return result

    return(iResult);
}

