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

    //- get pointer to target table

    int **ppiTargets = NULL;

    //- get pointer to event distributor

    struct EventDistributor *ped = NULL;

    //- tell the distributor to distribute the event over the targets

    NULL;

    //- return result

    return(iResult);
}


