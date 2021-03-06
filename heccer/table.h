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


/// \struct interval discretization

struct HeccerInterval
{
    /// start of interval

    double dStart;

    /// end of interval

    double dEnd;

    /// discretization step size

    double dStep;
};


struct HeccerTableApproximationOptions
{
    /// how do we do interpolation

    int iShape;
};


struct HeccerTabulatedGate
{
    /// original source parameters

    void *pvParameters;

    size_t iSizeParameters;

    /// interval of the tables

    struct HeccerInterval hi;

    /// calculation options

    /// \note almost tao

    struct HeccerTableApproximationOptions htao;

    /// number of entries, does not necessarily match with the default interval definition

    int iEntries;

    /// A table

    double *pdA;

    /// backward table (alpha + beta)

    double *pdB;
};


struct HeccerTabulatedSpringMass
{
    /// original source parameters

    void *pvParameters;

    size_t iSizeParameters;

    /// two precalculated coefficients for first exponential

    double dX1;
    double dX2;

    /// two precalculated coefficients for second exponential

    double dY1;
    double dY2;
};


/// \def maximum number of tabulated gates

#define HECCER_TABULATED_GATES_MAX 100

struct TabulatedGateTable
{
    /// tabulated gates (preallocated array)

    struct HeccerTabulatedGate phtg[HECCER_TABULATED_GATES_MAX];

    /// number of entries used in the above

    int iTabulatedGateCount;

    /// gate A / B values rearranged for cache lines

    double *pdRearranged;

    /// can tables be rearranged?

    int iCanBeRearranged;

/*     /// the detected minimum and maximum over all tables */

/*     double dRearrangedStart; */

/*     double dRearrangedEnd; */

};


/// \def maximum number of tabulated spring mass channels

#define HECCER_TABULATED_SPRINGMASS_MAX 10000

struct TabulatedSpringMassTable
{
    /// tabulated gates (preallocated array)

    struct HeccerTabulatedSpringMass phtsm[HECCER_TABULATED_SPRINGMASS_MAX];

    /// number of entries used in the above

    int iTabulatedSpringMassCount;
};


struct ConcentrationActivator;
struct GateConcept;
struct simobj_Heccer;



int
HeccerConcentrationGateTabulate
(struct ConcentrationActivator *pac, struct simobj_Heccer *pheccer);

int
HeccerGateConceptTabulate
(struct GateConcept *pgc, struct simobj_Heccer *pheccer);

int
HeccerTablesDump
(struct TabulatedGateTable *ptgt, FILE *pfile, int iSelection);

int HeccerTablesRearrange(struct simobj_Heccer *pheccer);

int
HeccerTableValuesDeserialize
(struct HeccerTabulatedGate *phtg, FILE *pfile);

int
HeccerTableValuesSerialize
(struct HeccerTabulatedGate *phtg, FILE *pfile);

int
HeccerTableInterpolate
(double *ppdSources[],
 double *ppdDestinations[],
 int iSourceSize,
 int iDestinationSize);

int
HeccerTabulateAny
(struct simobj_Heccer *pheccer, void *pv, int iPrototype, int iType);


#endif


