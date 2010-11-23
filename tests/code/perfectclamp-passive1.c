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


//////////////////////////////////////////////////////////////////////////////
// 
// This is an integration test that tests functionality between the 
// PerfectClamp simulation object and a solved variable from Heccer.
//
//////////////////////////////////////////////////////////////////////////////


#include <stdlib.h>

#include <experiment/perfectclamp.h>

#include "../../heccer/addressing.h"
#include "../../heccer/heccer.h"


#include "main.h"


#define HECCER_TEST_REPORTING_GRANULARITY 100
#define HECCER_TEST_STEPS 1000
#define HECCER_TEST_TESTED_THINGS ( HECCER_DUMP_VM_COMPARTMENT_MATRIX \
				    | HECCER_DUMP_VM_COMPARTMENT_MATRIX_DIAGONALS \
				    | HECCER_DUMP_VM_MECHANISM_OPERATIONS \
	)
#define HECCER_TEST_TIME_STEP (3e-6)


struct Compartment compSoma =
{
    //m administrative overhead

    {
	//m type of structure

	MATH_TYPE_Compartment,
    },

    //m index of parent compartment, -1 for none

    -1,

/*     //m first mechanism */

/*     NULL, */

/*     //m number of mechanisms */

/*     0, */

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


int piC2m[] =
{
    0,
    -1,
};


struct Intermediary inter =
{
    //m compartment array

    1,

    &compSoma,

    //m all other mathematical components

    NULL,

    //m compartment 2 first mechanism number

    piC2m,
};


int main(int argc, char *argv[])
{
    //- allocate a voltage clamp object

    ppc = PerfectClampNew("pc object");

    //- set fields

    double dCommand = 0.1;

    PerfectClampSetFields(ppc, dCommand, NULL);

//d connect the voltage clamp object with the compartment of interest

#define HECCER_TEST_INITIATE \
    double *pdVm = HeccerAddressCompartmentVariable(pheccer, 0, "Vm");	\
    PerfectClampAddVariable(ppc, pdVm)

//d schedule the voltage clamper

#define HECCER_TEST_SCHEDULE PerfectClampSingleStep(ppc, dSimulationTime)

    //- do the simulation

    simulate(argc, argv);
}


#define main(argc,argv) simulate(argc,argv)

//t this prototype can give warning and perhaps errors.

int main(int argc, char *argv[]);


#include "main.c"


