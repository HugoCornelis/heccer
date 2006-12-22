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


#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "heccer/heccer.h"
#include "heccer/table.h"


static int
HeccerTableDump
(struct HeccerTabulatedGate *phtg, FILE *pfile, int iSelection);

static
int
HeccerTabulatedGateNew(struct Heccer *pheccer, double dStart, double dEnd, int iEntries);


/// **************************************************************************
///
/// SHORT: HeccerDiscretizeGateConcept()
///
/// ARGS.:
///
///	pheccer...: a heccer.
///	pgc.......: gate concept description.
///
/// RTN..: int
///
///	tabulated gate index, -1 for failure.
///
/// DESCR: Discretize the given gate concept.
///
///	Note that for a single gate, this function sets up the forward
///	and backward kinetic discretization.
///
/// NOTE:
///
///	This function should be the main entry point for a tabulated
///	gate registry.
///
/// **************************************************************************

static
int
HeccerTabulatedGateNew(struct Heccer *pheccer, double dStart, double dEnd, int iEntries)
{
    if (pheccer->tgt.iTabulatedGateCount >= HECCER_TABULATED_GATES_MAX)
    {
	return(-1);
    }

#define HECCER_STATIC_TABULATED_GATES
#ifdef HECCER_STATIC_TABULATED_GATES

    //- set result : from pool

    struct HeccerTabulatedGate *phtg = NULL;

    phtg = &pheccer->tgt.phtg[pheccer->tgt.iTabulatedGateCount];

#else

    //- set result : allocate a new tabulated gate

    struct HeccerTabulatedGate *phtg = calloc(1, sizeof(*phtg));

#endif

    //- increment registry count

    pheccer->tgt.iTabulatedGateCount++;

    //- initialize interval discretizer

    phtg->hi.dStart = dStart;
    phtg->hi.dEnd = dEnd;
    phtg->hi.dStep = (phtg->hi.dEnd - phtg->hi.dStart) / iEntries;

    //- initialize discrete function entries

    phtg->iEntries = iEntries;
    phtg->pdForward = calloc(phtg->iEntries + 1, sizeof(*phtg->pdForward));
    phtg->pdBackward = calloc(phtg->iEntries + 1, sizeof(*phtg->pdBackward));

    //- initialize the tao

    phtg->htao.iShape = 0;

    //- return result

    return(pheccer->tgt.iTabulatedGateCount - 1);
}


int
HeccerDiscretizeGateConcept
(struct Heccer *pheccer, struct GateConcept *pgc)
{
    //- set default result : ok

    int iResult = TRUE;

    //- allocate structures

    //t values should come from heccer configuration

    int i = HeccerTabulatedGateNew(pheccer, -0.1, 0.05, 3000);

    if (i == -1)
    {
	return(FALSE);
    }

    //- fill the table with the discretized gate kinetics

    iResult = iResult && HeccerGateConceptTabulate(pgc, pheccer, i);

    //- register the table and table descriptor

    iResult = iResult && HeccerTabulatedGateRegister(pheccer, i);

    //- return result

    return(iResult);
}


/// **************************************************************************
///
/// SHORT: HeccerGateConceptTabulate()
///
/// ARGS.:
///
///	pgc.....: a heccer gate concept.
///	iIndex..: a heccer tabulated gate index.
///
/// RTN..: int
///
///	success of operation.
///
///	phtg....: a filled heccer tabulated gate.
///
/// DESCR: Fill the tables with a discretization of the gate kinetics.
///
/// **************************************************************************

int
HeccerGateConceptTabulate
(struct GateConcept *pgc, struct Heccer *pheccer, int iIndex)
{
    //- set default result : ok

    int iResult = TRUE;

    //- get access to the tabulated gate structure

    struct HeccerTabulatedGate *phtg = &pheccer->tgt.phtg[iIndex];

    //- get step size

    double dStep = phtg->hi.dStep;

    //- loop over all entries in the table

    int i;
    double dx;

    for (dx = phtg->hi.dStart, i = 0 ; i <= phtg->iEntries ; i++, dx += dStep)
    {
	//v alpha carry over to beta

	double dCarryOver;

	if (phtg->pdForward)
	{
	    double dMultiplier = pgc->gkForward.dMultiplier;
	    double dMembraneDependence = pgc->gkForward.dMembraneDependence;
	    int iNominator = pgc->gkForward.iNominator;
	    double dDeNominatorOffset = pgc->gkForward.dDeNominatorOffset;
	    double dMembraneOffset = pgc->gkForward.dMembraneOffset;
	    double dTauDenormalizer = pgc->gkForward.dTauDenormalizer;

	    //t check the MCAD MMGLT macro to see how it deals with
	    //t relative errors.  The current implementation is magnitude
	    //t dependent, and obviously completely add hoc.

	    if (fabs(dTauDenormalizer) < 1e-17)
	    {
		dCarryOver = 0.0;
		phtg->pdForward[i] = 0.0;
	    }
	    else
	    {
		double dDeNominator = dDeNominatorOffset + exp((dx + dMembraneOffset) / dTauDenormalizer);

		if (fabs(dDeNominator) < 1e-17)
		{
		    phtg->pdForward[i] = phtg->pdForward[i - 1];
		}
		else
		{
		    if (iNominator == 1)
		    {
			phtg->pdForward[i] = (dMultiplier + dMembraneDependence * dx) * dDeNominator;
		    }
		    else if (iNominator == -1)
		    {
			phtg->pdForward[i] = (dMultiplier + dMembraneDependence * dx) / dDeNominator;
		    }
		    else
		    {
			iResult = FALSE;
		    }
		}

		//- remember alpha, such that we can add it to beta below

		dCarryOver = phtg->pdForward[i];
	    }
	}

	if (phtg->pdForward && phtg->pdBackward)
	{
	    double dMultiplier = pgc->gkBackward.dMultiplier;
	    double dMembraneDependence = pgc->gkBackward.dMembraneDependence;
	    int iNominator = pgc->gkBackward.iNominator;
	    double dDeNominatorOffset = pgc->gkBackward.dDeNominatorOffset;
	    double dMembraneOffset = pgc->gkBackward.dMembraneOffset;
	    double dTauDenormalizer = pgc->gkBackward.dTauDenormalizer;

	    if (fabs(dTauDenormalizer) < 1e-17)
	    {
		phtg->pdBackward[i] = 0.0;
	    }
	    else
	    {
		double dDeNominator = dDeNominatorOffset + exp((dx + dMembraneOffset) / dTauDenormalizer);

		if (fabs(dDeNominator) < 1e-17)
		{
		    phtg->pdBackward[i] = phtg->pdBackward[i - 1];
		}
		else
		{
		    if (iNominator == 1)
		    {
			phtg->pdBackward[i] = (dMultiplier + dMembraneDependence * dx) * dDeNominator;
		    }
		    else if (iNominator == -1)
		    {
			phtg->pdBackward[i] = (dMultiplier + dMembraneDependence * dx) / dDeNominator;
		    }
		    else
		    {
			iResult = FALSE;
		    }
		}
	    }

	    //- add alpha

	    if (iResult == TRUE)
	    {
		phtg->pdBackward[i] += dCarryOver;
	    }
	}
    }

    //- return result

    return(iResult);
}


/// **************************************************************************
///
/// SHORT: HeccerTableDump()
///
/// ARGS.:
///
///	pheccer....: a compartment.
///	pfile......: stdio file.
///	iSelection.: selection to dump.
///
/// RTN..: int
///
///	success of operation.
///
/// DESCR: Dump tables to given stream, respecting given selection.
///
/// **************************************************************************

static int
HeccerTableDump
(struct HeccerTabulatedGate *phtg, FILE *pfile, int iSelection)
{
    //- set default result

    int iResult = TRUE;

    if (iSelection & HECCER_DUMP_TABLE_GATE_SUMMARY)
    {
	fprintf(pfile, "Tabulated gate, interval (dStart) : (%i)\n", phtg->hi.dStart);
	fprintf(pfile, "Tabulated gate, interval (dEnd) : (%i)\n", phtg->hi.dEnd);
	fprintf(pfile, "Tabulated gate, interval (dStep) : (%i)\n", phtg->hi.dStep);
    }

    if (iSelection & HECCER_DUMP_TABLE_GATE_SUMMARY)
    {
	fprintf(pfile, "Tabulated gate, interpolation (iShape) : (%i)\n", phtg->htao.iShape);
    }

    if (iSelection & HECCER_DUMP_TABLE_GATE_SUMMARY)
    {
	fprintf(pfile, "Tabulated gate (iEntries) : (%i)\n", phtg->iEntries);
    }

    if (iSelection & HECCER_DUMP_TABLE_GATE_TABLES)
    {
	int i;

	for (i = 0 ; i < phtg->iEntries ; i++)
	{
	    fprintf(pfile, "Tabulated gate, forward (iEntry %i) : (%g)\n", i, phtg->pdForward[i]);
	}

	for (i = 0 ; i < phtg->iEntries ; i++)
	{
	    fprintf(pfile, "Tabulated gate, backward (iEntry %i) : (%g)\n", i, phtg->pdBackward[i]);
	}
    }

    //- return result

    return(iResult);
}


/// **************************************************************************
///
/// SHORT: HeccerTablesDump()
///
/// ARGS.:
///
///	ptgt.......: tabulated gate table.
///	pfile......: stdio file.
///	iSelection.: selection to dump.
///
/// RTN..: int
///
///	success of operation.
///
/// DESCR: Dump intermediary functions.
///
/// **************************************************************************

int
HeccerTablesDump
(struct TabulatedGateTable *ptgt, FILE *pfile, int iSelection)
{
    //- set default result : ok

    int iResult = TRUE;

    //- number of tables

    fprintf(pfile, "Tables (iTabulatedGateCount) : (%i)\n", ptgt->iTabulatedGateCount);

    //- loop over tables

    int i;

    for (i = 0 ; i < ptgt->iTabulatedGateCount ; i++)
    {
	//- dump compartment

	iResult = iResult && HeccerTableDump(&ptgt->phtg[i], pfile, iSelection);
    }

    //- return result

    return(iResult);
}


/// **************************************************************************
///
/// SHORT: HeccerTabulatedGateRegister()
///
/// ARGS.:
///
///	pheccer.: a compartment.
///	iIndex..: a heccer tabulated gate index.
///
/// RTN..: int
///
///	success of operation.
///
/// DESCR: Register the given tabulated gate.
///
/// **************************************************************************

int
HeccerTabulatedGateRegister(struct Heccer *pheccer, int iIndex)
{
    //- set default result

    int iResult = TRUE;

    //- get access to the tabulated gate structure

    struct HeccerTabulatedGate *phtg = &pheccer->tgt.phtg[iIndex];

#ifdef HECCER_STATIC_TABULATED_GATES

    //! code removed ...

#endif

    //- return result

    return(iResult);
}
