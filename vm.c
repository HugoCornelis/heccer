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


#include "vm.h"


/// **************************************************************************
///
/// SHORT: HeccerVMDump()
///
/// ARGS.:
///
///	pvm...: heccer indexers.
///	pfile.: stdio file.
///
/// RTN..: int
///
///	success of operation.
///
/// DESCR: Dump VM functions.
///
/// **************************************************************************

int HeccerVMDump(struct VM *pvm, FILE *pfile)
{
    //- set default result : ok

    int iResult = TRUE;

    //m compartment operations

    int iCops;

    int *piCops;

    //- compartment data : diagonals

    int i;

    for (i = 0 ; i < pvm->iDiagonals ; i++)
    {
	fprintf(pfile, "VM Diagonals (pdDiagonals[%i]) : (%g)\n", i, pvm->pdDiagonals[i]);
    }

    //- compartment data : axial resistances

    for (i = 0 ; i < pvm->iAxres ; i++)
    {
	fprintf(pfile, "VM Axial Resistances (pdAxres[%i]) : (%g)\n", i, pvm->pdAxres[i]);
    }

    //- results : intermediate

    for (i = 0 ; i < pvm->iResults ; i++)
    {
	fprintf(pfile, "VM Axial Resistances (pdResults[%i]) : (%g)\n", i, pvm->pdResults[i]);
    }

    //- results : membrane potentials

    for (i = 0 ; i < pvm->iVms ; i++)
    {
	fprintf(pfile, "VM Membrane Potentials (pdVms[%i]) : (%g)\n", i, pvm->pdVms[i]);
    }

/*     //m mechanism operations */

/*     //t data type unspecified */

/*     void *pvMops; */

/*     //m mechanism data */

/*     //t data type unspecified */

/*     void *pvMats; */

    //- return result

    return(iResult);
}


