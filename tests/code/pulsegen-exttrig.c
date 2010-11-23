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
// This is an integration test that tests functionality between the PulseGen
// simulation object and a solved variable from Heccer.
//
//////////////////////////////////////////////////////////////////////////////


#include <stdlib.h>

#include <experiment/pulsegen.h>

#include "../../heccer/addressing.h"
#include "../../heccer/heccer.h"


#include "main.h"


#define HECCER_TEST_REPORTING_GRANULARITY 1
#define HECCER_TEST_STEPS 200
#define HECCER_TEST_TESTED_THINGS ( HECCER_DUMP_VM_COMPARTMENT_MATRIX \
				    | HECCER_DUMP_VM_MECHANISM_OPERATIONS \
	)
#define HECCER_TEST_TIME_STEP (0.5)


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

    ppg = PulseGenNew("pulsegen triggered mode (with delay)");


    //! setfield ^ level1 50.0 width1 3.0 delay1 5.0 level2 -20.0 width2 5.0  \
    //             delay2 8.0 baselevel 10.0 trig_mode 1

    double dLevel1 = 50.0;
    double dWidth1 = 3.0;
    double dDelay1 = 5.0;
    
    double dLevel2 = -20.0;
    double dWidth2 = 5.0;
    double dDelay2 = 8.0;

    double dBaseLevel = 10.0;

    int iTriggerMode = EXT_TRIG;


    PulseGenSetFields(ppg, dLevel1, dWidth1, dDelay1, dLevel2, dWidth2, dDelay2, dBaseLevel, iTriggerMode);

//d connect the voltage clamp object with the compartment of interest

#define HECCER_TEST_INITIATE \
    double *pdVm = HeccerAddressCompartmentVariable(pheccer, 0, "Vm");	\
    PulseGenAddVariable(ppg, pdVm)

//d schedule the voltage clamper

#define HECCER_TEST_SCHEDULE PulseGenSingleStep(ppg, dSimulationTime)

    //- do the simulation

    simulate(argc, argv);
}


#define main(argc,argv) simulate(argc,argv)

//t this prototype can give warning and perhaps errors.

int main(int argc, char *argv[]);


#include "main.c"


