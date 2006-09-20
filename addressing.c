//
// Heccer : a compartmental solver that implements efficient Crank-Nicolson
// integration for neuronal models.
//

//////////////////////////////////////////////////////////////////////////////
//'
//' Heccer : testbed C implementation
//'
//' Copyright (C) 2006 Hugo Cornelis
//'
//' functional ideas ..	Hugo Cornelis, hugo.cornelis@gmail.com
//'
//' coding ............	Hugo Cornelis, hugo.cornelis@gmail.com
//'
//////////////////////////////////////////////////////////////////////////////


#include <stdlib.h>
#include <string.h>

#include "addressing.h"
#include "heccer.h"


/// **************************************************************************
///
/// SHORT: AddressCompartmentVariable()
///
/// ARGS.:
///
///	pheccer.......: a heccer.
///	iIntermediary.: index of compartment in the intermediary.
///	pcField.......: name of requested variable.
///
/// RTN..: void *
///
///	pointer to the requested field, NULL for failure.
///
/// DESCR: Find the simulation sequence of a given variable.
///
/// **************************************************************************

void *
AddressCompartmentVariable
(struct Heccer *pheccer, int iIntermediary, char *pcField)
{
    //- set default result : not found

    void *pvResult = NULL;

    //- for membrane potential

    if (strcmp(pcField, "Vm") == 0)
    {
	//- convert intermediary to schedule number

	int iSchedule = pheccer->indexers.md.piForward[iIntermediary];

	//- set result

	double *pdResult = &pheccer->vm.pdVms[iSchedule];

	pvResult = (void *)pdResult;
    }

    //- for injected current

    else if (strcmp(pcField, "inject") == 0)
    {
    }

    //- for total membrane current

    else if (strcmp(pcField, "Im") == 0)
    {
    }

    //- for membrane leak current

    else if (strcmp(pcField, "Ileak") == 0)
    {
    }

    //- return result

    return(pvResult);
}


/// **************************************************************************
///
/// SHORT: AddressMechanismVariable()
///
/// ARGS.:
///
///	pheccer.......: a heccer.
///	iIntermediary.: index of mechanism in the intermediary.
///	pcField.......: name of requested variable.
///
/// RTN..: void *
///
///	pointer to the requested field, NULL for failure.
///
/// DESCR: Find the simulation sequence of a given variable.
///
/// **************************************************************************

void *
AddressMechanismVariable
(struct Heccer *pheccer, int iIndex, char *pcField)
{
    //- set default result : not found

    void *pvResult = NULL;

    //- return result

    return(pvResult);
}


