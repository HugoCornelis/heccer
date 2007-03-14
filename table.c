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


#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "heccer/heccer.h"
#include "heccer/table.h"


static int
HeccerTableDump
(struct HeccerTabulatedGate *phtg, int iIndex, FILE *pfile, int iSelection);

static
int
HeccerTabulatedGateNew(struct Heccer *pheccer, double dStart, double dEnd, int iEntries);


/// **************************************************************************
///
/// SHORT: HeccerBasalActivatorTabulate()
///
/// ARGS.:
///
///	pac.....: a basal activator gate concept.
///	pheccer.: a heccer.
///
/// RTN..: int
///
///	success of operation.
///
///	phtg....: a filled heccer tabulated gate.
///
/// DESCR: Fill the tables with a discretization of the basal
/// activator gate kinetics.
///
/// **************************************************************************

int
HeccerBasalActivatorTabulate
(struct Activator *pac, struct Heccer *pheccer)
{
    //- set default result : ok

    int iResult = TRUE;

    //- get access to the tabulated gate structure

    int iIndex = pac->iTable;

    struct HeccerTabulatedGate *phtg = &pheccer->tgt.phtg[iIndex];

    //- get step size

    double dStep = phtg->hi.dStep;

    //- loop over all entries in the table

    int i;
    double dx;

    for (dx = phtg->hi.dStart, i = 0 ; i <= phtg->iEntries ; i++, dx += dStep)
    {
	//- compute steady state

	double dEquilibrium = 1 / (1 + (pac->dBasalLevel / dx));

	//- fill in forward and backward table

	//t perhaps the table names should be redefined ?

	//! time step normalization done elsewhere

	phtg->pdForward[i] = dEquilibrium / pac->dTau;

	phtg->pdBackward[i] = 1 / pac->dTau;
    }

    //- return result

    return(iResult);
}


/// **************************************************************************
///
/// SHORT: HeccerDiscretizeBasalActivator()
///
/// ARGS.:
///
///	pheccer...: a heccer.
///	pac.......: basal activator concept description.
///
/// RTN..: int : success of operation.
///
/// DESCR: Discretize the given basal activator concept.
///
/// **************************************************************************

int
HeccerDiscretizeBasalActivator
(struct Heccer *pheccer, struct Activator *pac)
{
    //- set default result : ok

    int iResult = TRUE;

    //- if already registered

    if (pac->iTable != -1)
    {
	return(TRUE);
    }

    //- allocate structures

    double dStart = pheccer->ho.dBasalActivatorStart;
    double dEnd = pheccer->ho.dBasalActivatorEnd;
    int iEntries = pheccer->ho.iIntervalEntries;

    //t integrate these into the options

    dStart = 0.00004;
    dEnd = 0.300;

    int i = HeccerTabulatedGateNew(pheccer, dStart, dEnd, iEntries);

    if (i == -1)
    {
	return(FALSE);
    }

    //- register the index

    pac->iTable = i;

    //- fill the table with the discretized gate kinetics

    iResult = iResult && HeccerBasalActivatorTabulate(pac, pheccer);

    //- return result

    return(iResult);
}


/// **************************************************************************
///
/// SHORT: HeccerDiscretizeGateConcept()
///
/// ARGS.:
///
///	pheccer...: a heccer.
///	pgc.......: gate concept description.
///
/// RTN..: int : success of operation.
///
/// DESCR: Discretize the given gate concept.
///
///	Note that for a single gate, this function sets up the forward
///	and backward kinetic discretization.
///
/// **************************************************************************

int
HeccerDiscretizeGateConcept
(struct Heccer *pheccer, struct GateConcept *pgc)
{
    //- set default result : ok

    int iResult = TRUE;

    //- if already registered

    if (pgc->iTable != -1)
    {
	return(TRUE);
    }

    //- allocate structures

    double dStart = pheccer->ho.dIntervalStart;
    double dEnd = pheccer->ho.dIntervalEnd;
    int iEntries = pheccer->ho.iIntervalEntries;

    int i = HeccerTabulatedGateNew(pheccer, dStart, dEnd, iEntries);

    if (i == -1)
    {
	return(FALSE);
    }

    //- register the index

    pgc->iTable = i;

    //- fill the table with the discretized gate kinetics

    iResult = iResult && HeccerGateConceptTabulate(pgc, pheccer);

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
///	pheccer.: a heccer.
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
(struct GateConcept *pgc, struct Heccer *pheccer)
{
    //- set default result : ok

    int iResult = TRUE;

    //- get access to the tabulated gate structure

    int iIndex = pgc->iTable;

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
/// SHORT: HeccerChannelSteadyStateTauTabulate()
///
/// ARGS.:
///
///	pcsst...: a heccer channel with steady state and time constant.
///	pheccer.: a heccer.
///
/// RTN..: int
///
///	success of operation.
///
/// DESCR: Fill the tables with a discretization of the gate kinetics.
///
/// **************************************************************************

int
HeccerSteadyStateTauTabulate
(struct ChannelSteadyStateTau *pcsst, struct Heccer *pheccer)
{
    //- set default result : ok

    int iResult = TRUE;

    //- if already registered

    if (pcsst->iForwardTable != -1)
    {
	return(TRUE);
    }

    //- allocate structures

    double dStart = pheccer->ho.dIntervalStart;
    double dEnd = pheccer->ho.dIntervalEnd;
    int iEntries = pheccer->ho.iIntervalEntries;

    int i = HeccerTabulatedGateNew(pheccer, dStart, dEnd, iEntries);

    if (i == -1)
    {
	return(FALSE);
    }

    //- register the index

    pcsst->iForwardTable = i;

    int j = HeccerTabulatedGateNew(pheccer, dStart, dEnd, iEntries);

    if (j == -1)
    {
	return(FALSE);
    }

    //- register the index

    pcsst->iBackwardTable = j;

    //- get access to the tabulated gate structures

    int iIndex1 = pcsst->iForwardTable;

    struct HeccerTabulatedGate *phtg1 = &pheccer->tgt.phtg[iIndex1];

    int iIndex2 = pcsst->iBackwardTable;

    struct HeccerTabulatedGate *phtg2 = &pheccer->tgt.phtg[iIndex2];

    //- get step size

    double dStep = phtg1->hi.dStep;

    //- loop over all entries in the table

    double dx;

    for (dx = phtg1->hi.dStart, i = 0 ; i <= phtg1->iEntries ; i++, dx += dStep)
    {
	double dA
	    = (pcsst->ss.forward.a.dMultiplier
	       * (dx + pcsst->ss.forward.a.dMembraneDependence)
	       / ((exp((dx + pcsst->ss.forward.a.dMembraneOffset)
		       / pcsst->ss.forward.a.dTauDenormalizer))
		  + pcsst->ss.forward.a.dDeNominatorOffset));

	double dB
	    = (pcsst->ss.forward.b.dMultiplier
	       * (exp( - (dx + pcsst->ss.forward.b.dMembraneDependenceOffset)
		       / pcsst->ss.forward.b.dTauDenormalizer)));

	double dC
	    = (pcsst->ss.backward.a.dMultiplier
	       * (dx + pcsst->ss.backward.a.dMembraneDependenceOffset)
	       / ((exp((dx + pcsst->ss.backward.a.dMembraneOffset)
		       / pcsst->ss.backward.a.dTauDenormalizer))
		  + pcsst->ss.backward.a.dDeNominatorOffset));

	double dD
	       = (pcsst->ss.backward.b.dMultiplier
		  * (exp( - (dx + pcsst->ss.backward.b.dMembraneDependenceOffset)
			  / pcsst->ss.backward.b.dTauDenormalizer)));

	double dForward = (1.0 / (dA + dB));

	double dBackward = (dC / (dC + dD));

	//t check the MCAD MMGLT macro to see how it deals with
	//t relative errors.  The current implementation is magnitude
	//t dependent, and obviously completely add hoc.

	if (fabs(dForward) < 1e-17)
	{
	    if (dForward < 0.0)
	    {
		dForward = -1e-17;
	    }
	    else
	    {
		dForward = 1e-17;
	    }
	}

	phtg1->pdForward[i] = dBackward / dForward;
	phtg1->pdBackward[i] = 1.0 / dForward;
    }

    for (dx = phtg2->hi.dStart, i = 0 ; i <= phtg2->iEntries ; i++, dx += dStep)
    {
	double dForward;

	if (dx < pcsst->tc.a.dThreshold)
	{
	    dForward = pcsst->tc.a.dLowTarget;
	}
	else
	{
	    dForward = pcsst->tc.a.dHighTarget;
	}

	double dY
	    = (pcsst->tc.b.dDeNominatorOffset
	       + (exp((dx + pcsst->tc.b.dMembraneOffset)
		      / pcsst->tc.b.dTauDenormalizer)));

	double dBackward = (1.0 / dY);

	//t check the MCAD MMGLT macro to see how it deals with
	//t relative errors.  The current implementation is magnitude
	//t dependent, and obviously completely add hoc.

	if (fabs(dForward) < 1e-17)
	{
	    if (dForward < 0.0)
	    {
		dForward = -1e-17;
	    }
	    else
	    {
		dForward = 1e-17;
	    }
	}

	phtg2->pdForward[i] = dBackward / dForward;
	phtg2->pdBackward[i] = 1.0 / dForward;
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
///	phtg.......: a tabulated gate.
///	iIndex.....: index of this gate.
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
(struct HeccerTabulatedGate *phtg, int iIndex, FILE *pfile, int iSelection)
{
    //- set default result

    int iResult = TRUE;

    if (iSelection & HECCER_DUMP_TABLE_GATE_SUMMARY)
    {
	fprintf(pfile, "Tabulated gate %i, interval (dStart) : (%g)\n", iIndex, phtg->hi.dStart);
	fprintf(pfile, "Tabulated gate %i, interval (dEnd) : (%g)\n", iIndex, phtg->hi.dEnd);
	fprintf(pfile, "Tabulated gate %i, interval (dStep) : (%g)\n", iIndex, phtg->hi.dStep);
    }

    if (iSelection & HECCER_DUMP_TABLE_GATE_SUMMARY)
    {
	fprintf(pfile, "Tabulated gate %i, interpolation (iShape) : (%i)\n", iIndex, phtg->htao.iShape);
    }

    if (iSelection & HECCER_DUMP_TABLE_GATE_SUMMARY)
    {
	fprintf(pfile, "Tabulated gate %i, (iEntries) : (%i)\n", iIndex, phtg->iEntries);
    }

    if (iSelection & HECCER_DUMP_TABLE_GATE_TABLES)
    {
	int i;

	for (i = 0 ; i < phtg->iEntries ; i++)
	{
	    fprintf(pfile, "Tabulated gate %i, forward (iEntry %i) : (%g)\n", iIndex, i, phtg->pdForward[i]);
	}

	for (i = 0 ; i < phtg->iEntries ; i++)
	{
	    fprintf(pfile, "Tabulated gate %i, backward (iEntry %i) : (%g)\n", iIndex, i, phtg->pdBackward[i]);
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

	iResult = iResult && HeccerTableDump(&ptgt->phtg[i], i, pfile, iSelection);
    }

    //- return result

    return(iResult);
}


/// **************************************************************************
///
/// SHORT: HeccerTabulatedGateNew()
///
/// ARGS.:
///
///	pheccer...: a heccer.
///	dStart....: start value for table.
///	dEnd......: end value for table.
///	iEntries..: number of entries in the table.
///
/// RTN..: int
///
///	tabulated gate index, -1 for failure.
///
/// DESCR: Allocate a new table.
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


