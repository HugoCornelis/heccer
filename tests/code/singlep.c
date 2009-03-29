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


#include "../../heccer/addressing.h"
#include "../../heccer/compartment.h"
#include "../../heccer/heccer.h"


/* #define HECCER_TEST_REPORTING_GRANULARITY 100000 */
/* #define HECCER_TEST_STEPS 1000 */


struct Compartment compSoma =
{
    //m administrative overhead

    {
	//m type of structure

	MATH_TYPE_Compartment,

#ifdef HECCER_SOURCE_NEUROSPACES

	/// identification

	ADDRESSING_NEUROSPACES_2_HECCER(3),

#endif

#ifdef HECCER_SOURCE_TYPING

	/// model source type number

	/// \note source typing is used to compute aggregate currents ao
	/// \note things.

	-1,

#endif

#ifdef HECCER_SIZED_MATH_STRUCTURES

	/// size of this structure

	sizeof(struct Compartment),

#endif

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


#include "main.c"


