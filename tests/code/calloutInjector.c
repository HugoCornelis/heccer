//
// Heccer : a compartmental solver that implements efficient Crank-Nicolson
// integration for neuronal models.
//

//////////////////////////////////////////////////////////////////////////////
//'
//' Heccer : testbed C implementation
//'
//' Copyright (C) 2006-2007 Hugo Cornelis
//'
//' functional ideas ..	Hugo Cornelis, hugo.cornelis@gmail.com
//'
//' coding ............	Hugo Cornelis, hugo.cornelis@gmail.com
//'
//////////////////////////////////////////////////////////////////////////////


#include <stdio.h>

#include "../../heccer/callout.h"
#include "../../heccer/compartment.h"
#include "../../heccer/heccer.h"


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


ExternalFunction pefInjector;


//s a state describing structure that is external to heccer

struct ExternalState
{
    //m the number of times the external callout has been called by
    //m heccer.

    int iSteps;
};

struct ExternalState esSimulation =
{
    0,
};

struct Callout callSoma =
{
    {
	//m type of structure

	MATH_TYPE_CallOut_conductance_current,
    },

    //m external alien data

    &esSimulation,

    //m internal results

    &pirSoma,

    //m external results

    &perSoma,

    //m external function

    pefInjector,
};


int piC2m[] =
{
    1,
    -1,
};


struct Intermediary inter =
{
    //m compartment array

    1,

    &compSoma,

    //m number of mechanisms

    1,

    //m mechanism data

    &callSoma,

    //m compartment 2 first mechanism number

    piC2m,
};


int pefInjector(struct Callout *pco, struct Heccer *pheccer, struct InternalResults *pir, struct ExternalResults *per)
{
    //- set default result

    int iResult = 0;

    //- you can use pco->pvAlien to figure out the external state

    //- to do this, define you own private external state structure, see above

    //- access the external state structure using pco->pvAlien

    struct ExternalState *pes;

    pes = (struct ExternalState *)pco->pvAlien;

    //- and use it at your own convenience, we use it here to track
    //- the number of steps the callout has been called.

    pes->iSteps++;

    //- set conductance and current according to the number of steps

    per->dConductance = 0.0;

    if (pes->iSteps > 2 && pes->iSteps < 9)
    {
	per->dCurrent = 5e-10;
    }
    else
    {
	per->dCurrent = 0.0;
    }

    //- give some feedback for testing purposes

    fprintf(stdout, "The pefInjector callout injected %g current, and added %g conductance, at step %i\n", per->dCurrent, per->dConductance, pes->iSteps);
    fprintf(stdout, "The pefInjector callout is advancing to time %g\n", pheccer->dTime);

    //- return result

    return(iResult);
}


#include "main.c"


