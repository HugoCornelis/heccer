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


static int segv(char *pc);

static int segv(char *pc)
{
    fprintf(stderr, "serializer_tests failed for %s, bailing out\n", pc);

    return(((int *)0)[0] = 0);
}


int serializer_tests(struct Heccer *pheccer1, struct Heccer *pheccer2)
{
    int iResult = 1;

#define VM_TEST_EQUAL(member)				\
    if (pheccer1->vm.member != pheccer2->vm.member)	\
    {							\
	segv(#member);					\
    }							\

#define VM_TEST_UNEQUAL_POINTERS(member)		\
    if ((pheccer1->vm.member != NULL			\
	 || pheccer2->vm.member != NULL)		\
	&& pheccer1->vm.member == pheccer2->vm.member)	\
    {							\
	segv(#member);					\
    }							\

    //- test compartment structure

/*     VM_TEST_EQUAL(iCompartments); */

    VM_TEST_EQUAL(iCops);
    VM_TEST_UNEQUAL_POINTERS(piCops);

    //- test compartment state

    VM_TEST_EQUAL(iAxres);
    VM_TEST_UNEQUAL_POINTERS(pdAxres);

    VM_TEST_EQUAL(iResults);
    VM_TEST_UNEQUAL_POINTERS(pdResults);

    VM_TEST_EQUAL(iVms);
    VM_TEST_UNEQUAL_POINTERS(pdVms);

    //- test mechanism structure

    VM_TEST_EQUAL(iMathComponents);
    VM_TEST_UNEQUAL_POINTERS(piMC2Mat);
    VM_TEST_UNEQUAL_POINTERS(piMC2Mop);

    VM_TEST_EQUAL(iMops);
    VM_TEST_UNEQUAL_POINTERS(pvMops);

    VM_TEST_UNEQUAL_POINTERS(ppvCMatsIndex);

    VM_TEST_EQUAL(iMopNumber);
    VM_TEST_UNEQUAL_POINTERS(ppvMopsIndex);

    VM_TEST_EQUAL(iMatNumber);
    VM_TEST_UNEQUAL_POINTERS(ppvMatsIndex);

    //- test mechanism state

    VM_TEST_EQUAL(iMats);
    VM_TEST_UNEQUAL_POINTERS(pvMats);

    return(iResult);
}


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

    //- do some trivial tests related to serialization and deserialization

    serializer_tests(pheccer, pheccer2);

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


