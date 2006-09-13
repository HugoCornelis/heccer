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


#include <stdio.h>
#include <stdlib.h>

#include "../../compartment.h"
#include "../../heccer.h"
#include "../../mathcomponent.h"


struct Compartment compSoma =
{
    //m administrative overhead

    {
	//m identification

	1,

	//m type of structure

	MATH_TYPE_Compartment,
    },

    //m index of parent compartment, -1 for none

    -1,

    //m first mechanism

    NULL,

    //m number of mechanisms

    0,

    //m descriptive values, alphabetical order

/*     double dCm; */

    4.57537e-11, // unscaled 0.0164,

/*     double dEm; */

    -0.08,

/*     double dInitVm; */

    -0.068,

/*     double dInject;		 */

    0,

/*     double dRa; */

    360502, // unscaled 2.5,

/*     double dRm; */

    3.58441e+08, // unscaled 1
};


struct Intermediary inter =
{
    //m compartment array

    1,

    &compSoma,

    //m mechanism index

    0,

    NULL,

    //m mechanism data

    NULL,
};


int main(int argc, char *argv[])
{
    //- set default result : ok

    int iResult = EXIT_SUCCESS;

    //- instantiate a heccer with an initialized intermediary

    struct Heccer *pheccer = HeccerNewP2(&inter);

    //- build indices for optimization

    HeccerCompileP2(pheccer);

    //- compile to byte code

    HeccerCompileP3(pheccer);

    //- initial dump

    HeccerDump(pheccer, stdout);

    //- a couple of times

    int i;

    for (i = 0; i < 10 ; i++)
    {
	//- step

	HeccerHecc(pheccer);

	//- dump

	fprintf(stdout, "-------\n");

	fprintf(stdout, "Iteration %i\n", i);

	HeccerDump(pheccer, stdout);
    }

    //- return result

    return(iResult);
}


