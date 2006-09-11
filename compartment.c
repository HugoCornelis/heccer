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

#include "compartment.h"
#include "heccer.h"


/// **************************************************************************
///
/// SHORT: HeccerCompileCompartments()
///
/// ARGS.:
///
///	heccer...: a heccer.
///
/// RTN..: int
///
///	success of operation.
///
/// DESCR: Compile the intermediary of the compartments to byte code.
///
/// **************************************************************************

int HeccerCompileCompartments(struct Heccer *pheccer)
{
    //- set default result : ok

    int iResult = FALSE;

    //- return result

    return(iResult);
}


