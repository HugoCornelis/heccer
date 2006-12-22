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


//o To use this file :
//o
//o set the variable 'inter' to a intermediary representation,
//o #define HECCER_TEST_STEPS 1
//o #define HECCER_TEST_TESTED_THINGS to a dump selection,
//o #include this file, compile, run and parse the output.

int main(int argc, char *argv[])
{
    //t use argv for heccer options

    //- set default result : ok

    int iResult = EXIT_SUCCESS;

    //- instantiate a heccer with an initialized intermediary

    struct Heccer *pheccer = HeccerNewP2(&inter);

    //- build indices for optimization

    HeccerCompileP2(pheccer);

    //- compile to byte code

    HeccerCompileP3(pheccer);

    //- initiate values

    HeccerInitiate(pheccer);

    //- initial dump

    //! funny : the first '---' in the output are taken as an option
    //! by Expect.pm, which complicates testing a bit.  So just
    //! removed.

/*     fprintf(stdout, "-------\n"); */

    fprintf(stdout, "Initiated\n");

    HeccerDump(pheccer, stdout, HECCER_TEST_TESTED_THINGS);

    //- a couple of times

    int i;

    for (i = 0; i < HECCER_TEST_STEPS ; i++)
    {
	//- step

	HeccerHecc(pheccer);

	//- dump

	fprintf(stdout, "-------\n");

	fprintf(stdout, "Iteration %i\n", i);

	HeccerDump(pheccer, stdout, HECCER_TEST_TESTED_THINGS);
    }

    //- return result

    return(iResult);
}


