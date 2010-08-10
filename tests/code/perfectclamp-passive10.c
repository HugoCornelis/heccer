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


struct Compartment comp[] =
{
    {
	//m administrative overhead

	{
	    //m type of structure

	    MATH_TYPE_Compartment,
	},

	//m index of parent compartment, -1 for none

	-1,

/* 	//m first mechanism */

/* 	NULL, */

/* 	//m number of mechanisms */

/* 	0, */

	//m descriptive values, alphabetical order

/*     double dCm; */

	4.575370291e-11, // unscaled 0.0164,

/*     double dEm; */

	-0.08,

/*     double dInitVm; */

	-0.068,

/*     double dInject;		 */

	1e-8,

/*     double dRa; */

	360501.9688, // unscaled 2.5,

/*     double dRm; */

	358440928, // unscaled 3
    },
/* [ /Purkinje/soma ] */
/* activation           = 0 */
/* Vm                   = -0.0680000037 */
/* previous_state       = 0 */
/* Im                   = 0.00378972129 */
/* Em                   = -0.07999999821 */
/* Rm                   = 358440928 */
/* Cm                   = 4.575370291e-11 */
/* Ra                   = 360501.9688 */
/* inject               = 0 */
/* dia                  = 2.979999954e-05 */
/* len                  = 0 */
/* initVm               = -0.0680000037 */
/* somatopetal          = none */
/* somatopetaltag       = 1 */
/* somatofugal          =  /Purkinje/main */
/* somatofugaltag       = 0 */

    {
	//m administrative overhead

	{
	    //m type of structure

	    MATH_TYPE_Compartment,
	},

	//m index of parent compartment, -1 for none

	0,

/* 	//m first mechanism */

/* 	NULL, */

/* 	//m number of mechanisms */

/* 	0, */

	//m descriptive values, alphabetical order

/*     double dCm; */

	5.755329373e-12, // unscaled 0.0164,

/*     double dEm; */

	-0.08,

/*     double dInitVm; */

	-0.068,

/*     double dInject;		 */

	0,

/*     double dRa; */

	772813.4375, // unscaled 2.5,

/*     double dRm; */

	8548598272.0, // unscaled 3
    },
/* [ /Purkinje/main ] */
/* activation           = 0 */
/* Vm                   = -0.0680000037 */
/* previous_state       = 0 */
/* Im                   = 0.03594784066 */
/* Em                   = -0.07999999821 */
/* Rm                   = 8548598272 */
/* Cm                   = 5.755329373e-12 */
/* Ra                   = 772813.4375 */
/* inject               = 0 */
/* dia                  = 7.720000212e-06 */
/* len                  = 1.446968781e-05 */
/* initVm               = -0.0680000037 */
/* somatopetal          = /Purkinje/soma */
/* somatopetaltag       = 0 */
/* somatofugal          =  /Purkinje/main[1] */
/* somatofugaltag       = 0 */

    {
	//m administrative overhead

	{
	    //m type of structure

	    MATH_TYPE_Compartment,
	},

	//m index of parent compartment, -1 for none

	1,

/* 	//m first mechanism */

/* 	NULL, */

/* 	//m number of mechanisms */

/* 	0, */

	//m descriptive values, alphabetical order

/*     double dCm; */

	9.952665428e-12, // unscaled 0.0164,

/*     double dEm; */

	-0.08,

/*     double dInitVm; */

	-0.068,

/*     double dInject;		 */

	0,

/*     double dRa; */

	1107083.25, // unscaled 2.5,

/*     double dRm; */

	4943399424.0, // unscaled 3
    },
/* [ /Purkinje/main[1] ] */
/* activation           = 0 */
/* Vm                   = -0.0680000037 */
/* previous_state       = 0 */
/* Im                   = 0.03594784066 */
/* Em                   = -0.07999999821 */
/* Rm                   = 4943399424 */
/* Cm                   = 9.952665428e-12 */
/* Ra                   = 1107083.25 */
/* inject               = 0 */
/* dia                  = 8.220000382e-06 */
/* len                  = 2.350032264e-05 */
/* initVm               = -0.0680000037 */
/* somatopetal          = /Purkinje/main */
/* somatopetaltag       = 0 */
/* somatofugal          =  /Purkinje/main[2] /Purkinje/b0s01 */
/* somatofugaltag       = 0 */

    {
	//m administrative overhead

	{
	    //m type of structure

	    MATH_TYPE_Compartment,
	},

	//m index of parent compartment, -1 for none

	2,

/* 	//m first mechanism */

/* 	NULL, */

/* 	//m number of mechanisms */

/* 	0, */

	//m descriptive values, alphabetical order

/*     double dCm; */

	3.048169139e-12, // unscaled 0.0164,

/*     double dEm; */

	-0.08,

/*     double dInitVm; */

	-0.068,

/*     double dInject;		 */

	0,

/*     double dRa; */

	306646.9688, // unscaled 2.5,

/*     double dRm; */

	1.614083584e+10, // unscaled 3
    },
/* [ /Purkinje/main[2] ] */
/* activation           = 0 */
/* Vm                   = -0.0680000037 */
/* previous_state       = 0 */
/* Im                   = 0.03594784439 */
/* Em                   = -0.07999999821 */
/* Rm                   = 1.614083584e+10 */
/* Cm                   = 3.048169139e-12 */
/* Ra                   = 306646.9688 */
/* inject               = 0 */
/* dia                  = 8.500000149e-06 */
/* len                  = 6.960275186e-06 */
/* initVm               = -0.0680000037 */
/* somatopetal          = /Purkinje/main[1] */
/* somatopetaltag       = 0 */
/* somatofugal          =  /Purkinje/main[3] /Purkinje/b0s02 */
/* somatofugaltag       = 0 */

    {
	//m administrative overhead

	{
	    //m type of structure

	    MATH_TYPE_Compartment,
	},

	//m index of parent compartment, -1 for none

	3,

/* 	//m first mechanism */

/* 	NULL, */

/* 	//m number of mechanisms */

/* 	0, */

	//m descriptive values, alphabetical order

/*     double dCm; */

	1.866796431e-12, // unscaled 0.0164,

/*     double dEm; */

	-0.08,

/*     double dInitVm; */

	-0.068,

/*     double dInject;		 */

	0,

/*     double dRa; */

	147150.0781, // unscaled 2.5,

/*     double dRm; */

	2.635531059e+10, // unscaled 3
    },
/* [ /Purkinje/main[3] ] */
/* activation           = 0 */
/* Vm                   = -0.0680000037 */
/* previous_state       = 0 */
/* Im                   = 0.03594784439 */
/* Em                   = -0.07999999821 */
/* Rm                   = 2.635531059e+10 */
/* Cm                   = 1.866796431e-12 */
/* Ra                   = 147150.0781 */
/* inject               = 0 */
/* dia                  = 9.22000072e-06 */
/* len                  = 3.929816558e-06 */
/* initVm               = -0.0680000037 */
/* somatopetal          = /Purkinje/main[2] */
/* somatopetaltag       = 0 */
/* somatofugal          =  /Purkinje/main[4] */
/* somatofugaltag       = 0 */

    {
	//m administrative overhead

	{
	    //m type of structure

	    MATH_TYPE_Compartment,
	},

	//m index of parent compartment, -1 for none

	4,

/* 	//m first mechanism */

/* 	NULL, */

/* 	//m number of mechanisms */

/* 	0, */

	//m descriptive values, alphabetical order

/*     double dCm; */

	3.81543408e-12, // unscaled 0.0164,

/*     double dEm; */

	-0.08,

/*     double dInitVm; */

	-0.068,

/*     double dInject;		 */

	0,

/*     double dRa; */

	335501.9375, // unscaled 2.5,

/*     double dRm; */

	1.289499341e+10, // unscaled 3
    },
/* [ /Purkinje/main[4] ] */
/* activation           = 0 */
/* Vm                   = -0.0680000037 */
/* previous_state       = 0 */
/* Im                   = 0.03594784439 */
/* Em                   = -0.07999999821 */
/* Rm                   = 1.289499341e+10 */
/* Cm                   = 3.81543408e-12 */
/* Ra                   = 335501.9375 */
/* inject               = 0 */
/* dia                  = 8.890000572e-06 */
/* len                  = 8.330066521e-06 */
/* initVm               = -0.0680000037 */
/* somatopetal          = /Purkinje/main[3] */
/* somatopetaltag       = 0 */
/* somatofugal          =  /Purkinje/main[5] */
/* somatofugaltag       = 0 */

    {
	//m administrative overhead

	{
	    //m type of structure

	    MATH_TYPE_Compartment,
	},

	//m index of parent compartment, -1 for none

	5,

/* 	//m first mechanism */

/* 	NULL, */

/* 	//m number of mechanisms */

/* 	0, */

	//m descriptive values, alphabetical order

/*     double dCm; */

	2.239454065e-12, // unscaled 0.0164,

/*     double dEm; */

	-0.08,

/*     double dInitVm; */

	-0.068,

/*     double dInject;		 */

	0,

/*     double dRa; */

	230128.9531, // unscaled 2.5,

/*     double dRm; */

	2.196964147e+10, // unscaled 3
    },
/* [ /Purkinje/main[5] ] */
/* activation           = 0 */
/* Vm                   = -0.0680000037 */
/* previous_state       = 0 */
/* Im                   = 0.03594784439 */
/* Em                   = -0.07999999821 */
/* Rm                   = 2.196964147e+10 */
/* Cm                   = 2.239454065e-12 */
/* Ra                   = 230128.9531 */
/* inject               = 0 */
/* dia                  = 8.439999874e-06 */
/* len                  = 5.149985554e-06 */
/* initVm               = -0.0680000037 */
/* somatopetal          = /Purkinje/main[4] */
/* somatopetaltag       = 0 */
/* somatofugal          =  /Purkinje/main[6] /Purkinje/b0s03 */
/* somatofugaltag       = 0 */

    {
	//m administrative overhead

	{
	    //m type of structure

	    MATH_TYPE_Compartment,
	},

	//m index of parent compartment, -1 for none

	6,

/* 	//m first mechanism */

/* 	NULL, */

/* 	//m number of mechanisms */

/* 	0, */

	//m descriptive values, alphabetical order

/*     double dCm; */

	1.754059463e-12, // unscaled 0.0164,

/*     double dEm; */

	-0.08,

/*     double dInitVm; */

	-0.068,

/*     double dInject;		 */

	0,

/*     double dRa; */

	169781.8594, // unscaled 2.5,

/*     double dRm; */

	2.804921958e+10, // unscaled 3
    },
/* [ /Purkinje/main[6] ] */
/* activation           = 0 */
/* Vm                   = -0.0680000037 */
/* previous_state       = 0 */
/* Im                   = 0.03594784439 */
/* Em                   = -0.07999999821 */
/* Rm                   = 2.804921958e+10 */
/* Cm                   = 1.754059463e-12 */
/* Ra                   = 169781.8594 */
/* inject               = 0 */
/* dia                  = 8.609999895e-06 */
/* len                  = 3.954098247e-06 */
/* initVm               = -0.0680000037 */
/* somatopetal          = /Purkinje/main[5] */
/* somatopetaltag       = 0 */
/* somatofugal          =  /Purkinje/main[7] /Purkinje/b0s04 */
/* somatofugaltag       = 0 */

    {
	//m administrative overhead

	{
	    //m type of structure

	    MATH_TYPE_Compartment,
	},

	//m index of parent compartment, -1 for none

	7,

/* 	//m first mechanism */

/* 	NULL, */

/* 	//m number of mechanisms */

/* 	0, */

	//m descriptive values, alphabetical order

/*     double dCm; */

	3.37096605e-12, // unscaled 0.0164,

/*     double dEm; */

	-0.08,

/*     double dInitVm; */

	-0.068,

/*     double dInject;		 */

	0,

/*     double dRa; */

	442254.125, // unscaled 2.5,

/*     double dRm; */

	1.459522355e+10, // unscaled 3
    },
/* [ /Purkinje/main[7] ] */
/* activation           = 0 */
/* Vm                   = -0.0680000037 */
/* previous_state       = 0 */
/* Im                   = 0.03594784811 */
/* Em                   = -0.07999999821 */
/* Rm                   = 1.459522355e+10 */
/* Cm                   = 3.37096605e-12 */
/* Ra                   = 442254.125 */
/* inject               = 0 */
/* dia                  = 7.780000487e-06 */
/* len                  = 8.409710063e-06 */
/* initVm               = -0.0680000037 */
/* somatopetal          = /Purkinje/main[6] */
/* somatopetaltag       = 0 */
/* somatofugal          =  /Purkinje/main[8] */
/* somatofugaltag       = 0 */

    {
	//m administrative overhead

	{
	    //m type of structure

	    MATH_TYPE_Compartment,
	},

	//m index of parent compartment, -1 for none

	8,

/* 	//m first mechanism */

/* 	NULL, */

/* 	//m number of mechanisms */

/* 	0, */

	//m descriptive values, alphabetical order

/*     double dCm; */

	5.048512389e-12, // unscaled 0.0164,

/*     double dEm; */

	-0.08,

/*     double dInitVm; */

	-0.068,

/*     double dInject;		 */

	0,

/*     double dRa; */

	518791.0938, // unscaled 2.5,

/*     double dRm; */

	9745444864.0, // unscaled 3
    },
/* [ /Purkinje/main[8] ] */
/* activation           = 0 */
/* Vm                   = -0.0680000037 */
/* previous_state       = 0 */
/* Im                   = 0.03594784066 */
/* Em                   = -0.07999999821 */
/* Rm                   = 9745444864 */
/* Cm                   = 5.048512389e-12 */
/* Ra                   = 518791.0938 */
/* inject               = 0 */
/* dia                  = 8.439999874e-06 */
/* len                  = 1.160986722e-05 */
/* initVm               = -0.0680000037 */
/* somatopetal          = /Purkinje/main[7] */
/* somatopetaltag       = 0 */
/* somatofugal          =  /Purkinje/br1 /Purkinje/br2 */
/* somatofugaltag       = 0 */

};


int piC2m[] =
{
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    -1,
};


struct Intermediary inter =
{
    //m compartment array

    10,

    comp,

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


