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


#include <stdlib.h>

#include "../../heccer/addressing.h"
#include "../../heccer/heccer.h"
#include "../../heccer/pulsegen.h"


#include "main.h"


#define HECCER_TEST_REPORTING_GRANULARITY 100
#define HECCER_TEST_STEPS 1000
#define HECCER_TEST_TESTED_THINGS ( HECCER_DUMP_VM_COMPARTMENT_MATRIX \
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

    ppg = PulseGenNew("pulsegen object");

    //- set fields

    double dInject = 0.000003;

    //! setfield ^ gain 0.50 tau_i 0.02 tau_d 0.005 saturation 999.0

    double dR = 1;
    double dC = 0.00003;
    double dCommand_init = 0.0;

    double dGain = 0.50;
    double dTau_i = 0.000003;
    double dTau_d = 0.000003 / 4;
    double dSaturation = 999.0;

    VClampSetFields(ppg, dInject, dC, dR, dCommand_init, dGain, dTau_i, dTau_d, dSaturation);

//d connect the voltage clamp object with the compartment of interest

#define HECCER_TEST_INITIATE \
    double *pdVm = HeccerAddressCompartmentVariable(pheccer, 0, "Vm");	\
    double *pdInject = HeccerAddressCompartmentVariable(pheccer, 0, "inject"); \
    VClampAddVariable(ppg, pdVm, pdInject)

//d schedule the voltage clamper

#define HECCER_TEST_SCHEDULE VClampSingleStep(ppg, (dSimulationTime - HECCER_TEST_TIME_GRANULARITY))

    //- do the simulation

    simulate(argc, argv);
}


#define main(argc,argv) simulate(argc,argv)

//t this prototype can give warning and perhaps errors.

int main(int argc, char *argv[]);


#include "main.c"


