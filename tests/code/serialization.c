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


#include <stdio.h>
#include <stdlib.h>

#include "../../heccer/compartment.h"
#include "../../heccer/heccer.h"
#include "../../heccer/serialization.h"


/* #define HECCER_TEST_OPTIONS ( HECCER_OPTION_SERIALIZE_AT_FINISH	\ */
/* 	) */
#define HECCER_TEST_STEPS 0
#define HECCER_TEST_TESTED_THINGS HECCER_DUMP_ALL


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
    },

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
    },

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
    },
};


int piC2m[] =
{
    0,
    0,
    0,
    -1,
};


struct Intermediary inter =
{
    //m compartment array

    3,

    comp,

    //m all other mathematical components

    NULL,

    //m compartment 2 first mechanism number

    piC2m,
};


#include "main.h"


int main(int argc, char *argv[])
{
    //- set default result : ok

    int iResult = EXIT_SUCCESS;

    //- do the simulation (no steps, only compile)

    simulate(argc,argv);

    //- serialize

    FILE *pfile1 = fopen("/tmp/heccer", "w");

    HeccerSerialize(pheccer, pfile1);

    fclose(pfile1);

    //- deserialize

    FILE *pfile2 = fopen("/tmp/heccer", "r");

    struct Heccer *pheccer2 = HeccerDeserialize(pfile2);

    fclose(pfile2);

    //- dump

    //! just copied from main.c

/* #define HECCER_TEST_TESTED_THINGS 1 */

    dump(pheccer2, stdout, HECCER_TEST_TESTED_THINGS, "pheccer2: Deserialized\n", -1);

    //- step both heccers

    HeccerHeccs(pheccer, 1.0);

    HeccerHeccs(pheccer2, 1.0);

    //- dump both, must be same

    dump(pheccer, stdout, HECCER_TEST_TESTED_THINGS, "pheccer: after 1 second\n", -1);

    dump(pheccer2, stdout, HECCER_TEST_TESTED_THINGS, "pheccer2: after 1 second\n", -1);

    //- return result

    return(iResult);
}


#define main(argc,argv) simulate(argc,argv)

//t this prototype can give warning and perhaps errors.

int main(int argc, char *argv[]);


#include "main.c"


