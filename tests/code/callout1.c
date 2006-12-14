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

#include "../../callout.h"
#include "../../compartment.h"
#include "../../heccer.h"


struct Compartment compSoma =
{
    //m administrative overhead

    {
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


struct InternalResults pirSoma =
{
    //m membrane potential for this compartment

    0.0,
};


struct ExternalResults perSoma =
{
    //m external conductance, this is just an example

    10.0,

    //m external current, another example

    10.0,
};


ExternalFunction pefSoma;


struct Callout callSoma =
{
    {
	//m type of structure

	MATH_TYPE_CallOut_conductance_current,
    },

    //m external alien data

    NULL,

    //m internal results

    &pirSoma,

    //m external results

    &perSoma,

    //m external function

    pefSoma,
};


struct Intermediary inter =
{
    //m compartment array

    1,

    &compSoma,

    //m mechanism index

    1,

    NULL,

    //m mechanism data

    &callSoma,
};


int pefSoma(struct Callout *pco, struct Heccer *pheccer, struct InternalResults *pir, struct ExternalResults *per)
{
    //- set default result

    int iResult = 0;

    //- initialize

    per->dConductance = 0.0;
    per->dCurrent = 0.0;

    //t do something to compute the current and conductance, using pco->pvAlien

    //t fill in the conductance and current in the external results

    //- give some feedback for testing purposes

    fprintf(stdout, "The pefSoma callout says that it is computing current and conductance externally\n");
    fprintf(stdout, "The pefSoma callout is advancing to time %g\n", pheccer->dTime);

    //- return result

    return(iResult);
}


#include "main.c"

