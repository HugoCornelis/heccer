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


#ifndef HECCER_TABLE_H
#define HECCER_TABLE_H


#include <string.h>

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
    //m original source parameters

    void *pvParameters;

    size_t iSizeParameters;

    //m interval of the tables

    struct HeccerInterval hi;

    //m calculation options

    //! almost tao

    struct HeccerTableApproximationOptions htao;

    //m number of entries, must always match with interval definition I guess

    int iEntries;

    //m A table

    double *pdA;

    //m backward table (alpha + beta)

    double *pdB;
};


struct HeccerTabulatedSpringMass
{
    //m original source parameters

    void *pvParameters;

    size_t iSizeParameters;

    //m two precalculated coefficients for first exponential

    double dX1;
    double dX2;

    //m two precalculated coefficients for second exponential

    double dY1;
    double dY2;
};


//d maximum number of tabulated gates

#define HECCER_TABULATED_GATES_MAX 100

struct TabulatedGateTable
{
    //m tabulated gates (preallocated array)

    struct HeccerTabulatedGate phtg[HECCER_TABULATED_GATES_MAX];

    //m number of entries used in the above

    int iTabulatedGateCount;
};


//d maximum number of tabulated spring mass channels

#define HECCER_TABULATED_SPRINGMASS_MAX 10000

struct TabulatedSpringMassTable
{
    //m tabulated gates (preallocated array)

    struct HeccerTabulatedSpringMass phtsm[HECCER_TABULATED_SPRINGMASS_MAX];

    //m number of entries used in the above

    int iTabulatedSpringMassCount;
};


struct ConcentrationActivator;
struct GateConcept;
struct Heccer;


//f prototypes

int
HeccerConcentrationGateTabulate
(struct ConcentrationActivator *pac, struct Heccer *pheccer);

int
HeccerGateConceptTabulate
(struct GateConcept *pgc, struct Heccer *pheccer);

int
HeccerTablesDump
(struct TabulatedGateTable *ptgt, FILE *pfile, int iSelection);

int
HeccerTableInterpolate
(double *ppdSources[],
 double *ppdDestinations[],
 int iSourceSize,
 int iDestinationSize);

int
HeccerTabulateAny
(struct Heccer *pheccer, void *pv, int iType);

int
HeccerTabulatedGateRegister(struct Heccer *pheccer, struct GateConcept *pgc);


#endif


