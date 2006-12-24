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


#ifndef HECCER_TABLE_H
#define HECCER_TABLE_H


#include "mechanism.h"


#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif


//s interval discretization

struct HeccerInterval
{
    //m start of interval

    double dStart;

    //m end of interval

    double dEnd;

    //m discretization step size

    double dStep;
};


struct HeccerTableApproximationOptions
{
    //m how do we do interpolation

    int iShape;
};


struct HeccerTabulatedGate
{
    //m interval of the tables

    struct HeccerInterval hi;

    //m calculation options

    //! almost tao

    struct HeccerTableApproximationOptions htao;

    //m number of entries, must always match with interval definition I guess

    int iEntries;

    //m forward table (alpha)

    double *pdForward;

    //m backward table (alpha + beta)

    double *pdBackward;
};


//d maximum number of tabulated gates

#define HECCER_TABULATED_GATES_MAX 20

struct TabulatedGateTable
{
    //m tabulated gates (preallocated array)

    struct HeccerTabulatedGate phtg[HECCER_TABULATED_GATES_MAX];

    //m number of entries used in the above

    int iTabulatedGateCount;
};


struct Heccer;


//f prototypes

int
HeccerDiscretizeGateConcept
(struct Heccer *pheccer, struct GateConcept *pgc);

int
HeccerGateConceptTabulate
(struct GateConcept *pgc, struct Heccer *pheccer);

int
HeccerTablesDump
(struct TabulatedGateTable *ptgt, FILE *pfile, int iSelection);

int
HeccerTabulatedGateRegister(struct Heccer *pheccer, struct GateConcept *pgc);


#endif

