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

    //m forward table (alpha)

    double *pdForward;

    //m backward table (alpha + beta)

    double *pdBackward;
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


struct Heccer;


//f prototypes

int
HeccerBasalActivatorTabulate
(struct Activator *pac, struct Heccer *pheccer);

int
HeccerChannelPersistentSteadyStateTauTabulate
(struct ChannelPersistentSteadyStateTau *pcpst, struct Heccer *pheccer);

int
HeccerChannelPersistentSteadyStateDualTauTabulate
(struct ChannelPersistentSteadyStateDualTau *pcpsdt, struct Heccer *pheccer);

int
HeccerTabulateSpringMass(struct Heccer *pheccer, struct ChannelSpringMass *pcsm);

int
HeccerChannelSteadyStateSteppedTauTabulate
(struct ChannelSteadyStateSteppedTau *pcsst, struct Heccer *pheccer);

int
HeccerDiscretizeBasalActivator
(struct Heccer *pheccer, struct Activator *pac);

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
HeccerTableInterpolate
(double *ppdSources[],
 double *ppdDestinations[],
 int iSourceSize,
 int iDestinationSize);

int
HeccerTabulatedGateRegister(struct Heccer *pheccer, struct GateConcept *pgc);


#endif


