//
// Heccer : a compartmental solver that implements efficient Crank-Nicolson
// integration for neuronal models.
//

//////////////////////////////////////////////////////////////////////////////
//'
//' Heccer : testbed C implementation
//'
//' Copyright (C) 2006-2008 Hugo Cornelis
//'
//' functional ideas ..	Hugo Cornelis, hugo.cornelis@gmail.com
//'
//' coding ............	Hugo Cornelis, hugo.cornelis@gmail.com
//'
//////////////////////////////////////////////////////////////////////////////


#define HECCER_TEST_STEPS 0
#ifndef HECCER_TEST_SERIALIZATION_SIMULATION_TIME
#define HECCER_TEST_SERIALIZATION_SIMULATION_TIME 1.0
#endif

#include "main.h"


int main(int argc, char *argv[])
{
    //- set default result : ok

    int iResult = EXIT_SUCCESS;

    //- do the simulation (no steps, only compile)

    simulate(argc,argv);

    //- serialize

    HeccerWriteToFile(pheccer, "/tmp/heccer");

    //- deserialize

    struct Heccer *pheccer2 = HeccerNewFromFile("/tmp/heccer");

    //- dump both, must be same

    tests_dump(pheccer, stdout, HECCER_TEST_TESTED_THINGS, "pheccer: before simulation\n", -1);

    tests_dump(pheccer2, stdout, HECCER_TEST_TESTED_THINGS, "pheccer2: before simulation\n", -1);

    //- step both heccers

    HeccerHeccs(pheccer, HECCER_TEST_SERIALIZATION_SIMULATION_TIME);

    HeccerHeccs(pheccer2, HECCER_TEST_SERIALIZATION_SIMULATION_TIME);

    //- dump both, must be same

    tests_dump(pheccer, stdout, HECCER_TEST_TESTED_THINGS, "pheccer: after 1 second\n", -1);

    tests_dump(pheccer2, stdout, HECCER_TEST_TESTED_THINGS, "pheccer2: after 1 second\n", -1);

    //- return result

    return(iResult);
}


#ifdef main
#undef main
#endif

#define main(argc,argv) simulate(argc,argv)

//t this prototype can give warning and perhaps errors.

int main(int argc, char *argv[]);


#include "main.c"


