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

    //- initialize values

    HeccerInitialize(pheccer);

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


