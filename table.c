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
HeccerTabulatedGateNew
(struct Heccer *pheccer,
 void *pvParameters,
 int iSize,
 double dStart,
 double dEnd,
 int iEntries);


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

    int i = HeccerTabulatedGateNew(pheccer, NULL, -1, dStart, dEnd, iEntries);

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

    int i = HeccerTabulatedGateNew(pheccer, NULL, -1, dStart, dEnd, iEntries);

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
/// SHORT: HeccerChannelPersistentSteadyStateDualTauTabulate()
///
/// ARGS.:
///
///	pcpsdt..: a channel with steady state and two time constants.
///	pheccer.: a heccer.
///
/// RTN..: int
///
///	success of operation.
///
/// DESCR: Fill the tables with a discretization of the gate kinetics.
///
///	First tables with 149 entries are created using the commonly
///	defined formulas for steady state and time constant (see
///	EDS1994).  Next the full sized tables are created using the
///	small tables, by using b-spline interpolation.
///
///	This is the way it was done in the Purkinje cell model, but is
///	only here for reasons of legacy.  This function should
///	normally not be used.
///
/// **************************************************************************

int
HeccerChannelPersistentSteadyStateDualTauTabulate
(struct ChannelPersistentSteadyStateDualTau *pcpsdt, struct Heccer *pheccer)
{
    //- set default result : ok

    int iResult = TRUE;

    //- if already registered

    if (pcpsdt->iFirstTable != -1)
    {
	return(TRUE);
    }

    //- allocate structures

    double dStart = pheccer->ho.dIntervalStart;
    double dEnd = pheccer->ho.dIntervalEnd;
    int iEntries = pheccer->ho.iIntervalEntries;

    int i = HeccerTabulatedGateNew(pheccer, NULL, -1, dStart, dEnd, iEntries);

    if (i == -1)
    {
	return(FALSE);
    }

    //- register the index

    pcpsdt->iFirstTable = i;

    int j = HeccerTabulatedGateNew(pheccer, NULL, -1, dStart, dEnd, iEntries);

    if (j == -1)
    {
	return(FALSE);
    }

    //- register the index

    pcpsdt->iSecondTable = j;

    //- get access to the tabulated gate structures

    int iIndex1 = pcpsdt->iFirstTable;

    struct HeccerTabulatedGate *phtg1 = &pheccer->tgt.phtg[iIndex1];

    int iIndex2 = pcpsdt->iSecondTable;

    struct HeccerTabulatedGate *phtg2 = &pheccer->tgt.phtg[iIndex2];

    //- allocate the small tables

    int iSmallTableSize = pheccer->ho.iSmallTableSize;

    //20;

    //- get step size

    double dSmallStep = (phtg1->hi.dEnd - phtg1->hi.dStart) / (iSmallTableSize);

    double *pd1 = (double *)calloc(iSmallTableSize + 1, sizeof(double));
    double *pd2 = (double *)calloc(iSmallTableSize + 1, sizeof(double));
    double *pd3 = (double *)calloc(iSmallTableSize + 1, sizeof(double));
    double *pd4 = (double *)calloc(iSmallTableSize + 1, sizeof(double));

    //- loop over all entries in the first small table

    double dx;

    for (dx = phtg1->hi.dStart, i = 0 ; i <= iSmallTableSize ; i++, dx += dSmallStep)
    {
	double dA = pcpsdt->dFirstSteadyState;
	double dB = pcpsdt->dSecondSteadyState;

	double dC
	    = (pcpsdt->tau1.dMultiplier
	       / (pcpsdt->tau1.dDeNominatorOffset
		  + exp((dx + pcpsdt->tau1.dMembraneOffset)
			/ pcpsdt->tau1.dTauDenormalizer)));

	double dD
	    = (pcpsdt->tau2.dMultiplier
	       / (pcpsdt->tau2.dDeNominatorOffset
		  + exp((dx + pcpsdt->tau2.dMembraneOffset)
			/ pcpsdt->tau2.dTauDenormalizer)));

	double dForward1 = dA;
	double dForward2 = dB;
	double dBackward1 = dC;
	double dBackward2 = dD;

	//t check the MCAD MMGLT macro to see how it deals with
	//t relative errors.  The current implementation is magnitude
	//t dependent, and obviously completely add hoc.

	if (fabs(dForward1) < 1e-17)
	{
	    if (dForward1 < 0.0)
	    {
		dForward1 = -1e-17;
	    }
	    else
	    {
		dForward1 = 1e-17;
	    }
	}

	pd1[i] = dBackward1 / dForward1;
	pd2[i] = 1.0 / dForward1;

	//t check the MCAD MMGLT macro to see how it deals with
	//t relative errors.  The current implementation is magnitude
	//t dependent, and obviously completely add hoc.

	if (fabs(dForward2) < 1e-17)
	{
	    if (dForward2 < 0.0)
	    {
		dForward2 = -1e-17;
	    }
	    else
	    {
		dForward2 = 1e-17;
	    }
	}

	pd3[i] = dBackward2 / dForward2;
	pd4[i] = 1.0 / dForward2;
    }

    //- interpolate the tables

    double *ppdSources[]
	= { pd1, pd2, pd3, pd4, NULL, };
    double *ppdDestinations[]
	= { phtg1->pdForward, phtg1->pdBackward, phtg2->pdForward, phtg2->pdBackward, NULL, };

    iResult = iResult && HeccerTableInterpolate(ppdSources, ppdDestinations, iSmallTableSize, iEntries);

    //- free allocated memory

    free(pd1);
    free(pd2);
    free(pd3);
    free(pd4);

    //- return result

    return(iResult);
}


/// **************************************************************************
///
/// SHORT: HeccerChannelPersistentSteadyStateTauTabulate()
///
/// ARGS.:
///
///	pcpst...: a heccer channel with steady state and time constant.
///	pheccer.: a heccer.
///
/// RTN..: int
///
///	success of operation.
///
/// DESCR: Fill the tables with a discretization of the gate kinetics.
///
///	First tables with 149 entries are created using the commonly
///	defined formulas for steady state and time constant (see
///	EDS1994).  Next the full sized tables are created using the
///	small tables, by using b-spline interpolation.
///
///	This is the way it was done in the Purkinje cell model, but is
///	only here for reasons of legacy.  This function should
///	normally not be used.
///
/// **************************************************************************

int
HeccerChannelPersistentSteadyStateTauTabulate
(struct ChannelPersistentSteadyStateTau *pcpst, struct Heccer *pheccer)
{
    //- set default result : ok

    int iResult = TRUE;

    //- if already registered

    if (pcpst->iTable != -1)
    {
	return(TRUE);
    }

    //- allocate structures

    double dStart = pheccer->ho.dIntervalStart;
    double dEnd = pheccer->ho.dIntervalEnd;
    int iEntries = pheccer->ho.iIntervalEntries;

    int i = HeccerTabulatedGateNew(pheccer, NULL, -1, dStart, dEnd, iEntries);

    if (i == -1)
    {
	return(FALSE);
    }

    //- register the index

    pcpst->iTable = i;

    //- get access to the tabulated gate structures

    int iIndex = pcpst->iTable;

    struct HeccerTabulatedGate *phtg = &pheccer->tgt.phtg[iIndex];

    //- allocate the small tables

    int iSmallTableSize = pheccer->ho.iSmallTableSize;

    //- get step size

    double dSmallStep = (phtg->hi.dEnd - phtg->hi.dStart) / (iSmallTableSize);

    double *pd1 = (double *)calloc(iSmallTableSize + 1, sizeof(double));
    double *pd2 = (double *)calloc(iSmallTableSize + 1, sizeof(double));

    //- loop over all entries in the first small table

    double dx;

    for (dx = phtg->hi.dStart, i = 0 ; i <= iSmallTableSize ; i++, dx += dSmallStep)
    {
	double dA
	    = (pcpst->ss.dNominator
	       / ( pcpst->ss.dMultiplier1
		   * ((exp((dx + pcpst->ss.dMembraneOffset1) / pcpst->ss.dTauDenormalizer1)))
		   + pcpst->ss.dMultiplier2
		   * (exp ((dx + pcpst->ss.dMembraneOffset2) / pcpst->ss.dTauDenormalizer2))));

	double dB
	    = (pcpst->tc.dNominator
	       / (pcpst->tc.dDeNominatorOffset
		  + (exp((dx + pcpst->tc.dMembraneOffset) / pcpst->tc.dTauDenormalizer))));

	double dForward = dA;

	double dBackward = dB;

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

	pd1[i] = dBackward / dForward;
	pd2[i] = 1.0 / dForward;
    }

    //- interpolate the tables

    double *ppdSources[]
	= { pd1, pd2, NULL, };
    double *ppdDestinations[]
	= { phtg->pdForward, phtg->pdBackward, NULL, };

    iResult = iResult && HeccerTableInterpolate(ppdSources, ppdDestinations, iSmallTableSize, iEntries);

    //- free allocated memory

    free(pd1);
    free(pd2);

    //- return result

    return(iResult);
}


/// **************************************************************************
///
/// SHORT: HeccerChannelSteadyStateSteppedTauTabulate()
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
///	First tables with 149 entries are created using the commonly
///	defined formulas for steady state and time constant (see
///	EDS1994).  Next the full sized tables are created using the
///	small tables, by using b-spline interpolation.
///
///	This is the way it was done in the Purkinje cell model, but is
///	only here for reasons of legacy.  This function should
///	normally not be used.
///
/// **************************************************************************

int
HeccerChannelSteadyStateSteppedTauTabulate
(struct ChannelSteadyStateSteppedTau *pcsst, struct Heccer *pheccer)
{
    //- set default result : ok

    int iResult = TRUE;

    //- if already registered

    if (pcsst->iFirstTable != -1)
    {
	return(TRUE);
    }

    //- allocate structures

    double dStart = pheccer->ho.dIntervalStart;
    double dEnd = pheccer->ho.dIntervalEnd;
    int iEntries = pheccer->ho.iIntervalEntries;

    int i = HeccerTabulatedGateNew(pheccer, NULL, -1, dStart, dEnd, iEntries);

    if (i == -1)
    {
	return(FALSE);
    }

    //- register the index

    pcsst->iFirstTable = i;

    int j = HeccerTabulatedGateNew(pheccer, NULL, -1, dStart, dEnd, iEntries);

    if (j == -1)
    {
	return(FALSE);
    }

    //- register the index

    pcsst->iSecondTable = j;

    //- get access to the tabulated gate structures

    int iIndex1 = pcsst->iFirstTable;

    struct HeccerTabulatedGate *phtg1 = &pheccer->tgt.phtg[iIndex1];

    int iIndex2 = pcsst->iSecondTable;

    struct HeccerTabulatedGate *phtg2 = &pheccer->tgt.phtg[iIndex2];

    //- allocate the small tables

    int iSmallTableSize = pheccer->ho.iSmallTableSize;

    //- get step size

    double dSmallStep = (phtg1->hi.dEnd - phtg1->hi.dStart) / (iSmallTableSize);

    double *pd1 = (double *)calloc(iSmallTableSize + 1, sizeof(double));
    double *pd2 = (double *)calloc(iSmallTableSize + 1, sizeof(double));
    double *pd3 = (double *)calloc(iSmallTableSize + 1, sizeof(double));
    double *pd4 = (double *)calloc(iSmallTableSize + 1, sizeof(double));

    //- loop over all entries in the first small table

    double dx;

    for (dx = phtg1->hi.dStart, i = 0 ; i <= iSmallTableSize ; i++, dx += dSmallStep)
    {
	double dA
	    = (pcsst->ss.first.a.dMultiplier
	       * (dx + pcsst->ss.first.a.dMembraneDependenceOffset)
	       / ((exp((dx + pcsst->ss.first.a.dMembraneOffset)
		       / pcsst->ss.first.a.dTauDenormalizer))
		  + pcsst->ss.first.a.dDeNominatorOffset));

	double dB
	    = (pcsst->ss.first.b.dMultiplier
	       * (exp( - (dx + pcsst->ss.first.b.dMembraneDependenceOffset)
		       / pcsst->ss.first.b.dTauDenormalizer)));

	double dC
	    = (pcsst->ss.second.a.dMultiplier
	       * (dx + pcsst->ss.second.a.dMembraneDependenceOffset)
	       / ((exp((dx + pcsst->ss.second.a.dMembraneOffset)
		       / pcsst->ss.second.a.dTauDenormalizer))
		  + pcsst->ss.second.a.dDeNominatorOffset));

	double dD
	       = (pcsst->ss.second.b.dMultiplier
		  * (exp( - (dx + pcsst->ss.second.b.dMembraneDependenceOffset)
			  / pcsst->ss.second.b.dTauDenormalizer)));

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

	pd1[i] = dBackward / dForward;
	pd2[i] = 1.0 / dForward;
    }

    for (dx = phtg2->hi.dStart, i = 0 ; i <= iSmallTableSize ; i++, dx += dSmallStep)
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

	pd3[i] = dBackward / dForward;
	pd4[i] = 1.0 / dForward;
    }

    //- interpolate the tables

    double *ppdSources[]
	= { pd1, pd2, pd3, pd4, NULL, };
    double *ppdDestinations[]
	= { phtg1->pdForward, phtg1->pdBackward, phtg2->pdForward, phtg2->pdBackward, NULL, };

    iResult = iResult && HeccerTableInterpolate(ppdSources, ppdDestinations, iSmallTableSize, iEntries);

    //- free allocated memory

    free(pd1);
    free(pd2);
    free(pd3);
    free(pd4);

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
/// SHORT: HeccerTableInterpolate()
///
/// ARGS.:
///
///	ppdSources.......: source tables for interpolation.
///	ppdDestinations..: destination tables for interpolation.
///	iSourceSize......: size of source tables.
///	iDestinationSize.: size of destination tables.
///
/// RTN..: int
///
///	success of operation.
///
/// DESCR: Interpolate given tables, uses bezier curves.
///
///	ppdSources and ppdDestinations must be NULL terminated.
///	ppdDestinations must be preallocated, presumably using
///	HeccerTabulatedGateNew().
///
/// **************************************************************************

int
HeccerTableInterpolate
(double *ppdSources[],
 double *ppdDestinations[],
 int iSourceSize,
 int iDestinationSize)
{
    //- set default result : ok

    int iResult = TRUE;

    //- loop over all gates

    int iGate;

    for (iGate = 0 ; ppdSources[iGate] ; iGate++)
    {
	//! modified and optimized for heccer from
	//! http://people.scs.fsu.edu/~burkardt/cpp_src/spline/spline.C

	double dRangeStep = (double)iSourceSize / (double)iDestinationSize;
	double dActual;

	double dNSA = 1.0 / 6.0;
	double dNSB = 2.0 / 3.0;

	//- loop over the entries of this gate

	double *pdSource = ppdSources[iGate];
	double *pdDestination = ppdDestinations[iGate];

	int iSource;
	int iDestination;

	//- fill the destination till the first element that comes from the source

	for (dActual = 0.0, iDestination = 0, iSource = 0 ; iSource <= 1 ; dActual += dRangeStep, iSource = (int)dActual, iDestination++)
	{
	    pdDestination[iDestination]
		= ((dActual - (double)iSource)
		   * (pdSource[iSource + 1] - pdSource[iSource])
		   + pdSource[iSource]);
	}

	//- do the interpolation

	for( ; iSource <= iSourceSize - 2 ; dActual += dRangeStep, iSource = (int)dActual, iDestination++)
	{
	    double dSource = dActual - (double)iSource;
	    double dSource2 = dSource / 2.0;
	    double dSource4 = dSource * dSource;
	    double dSource42 = dSource4 / 2.0;
	    double dSource8 = dSource4 * dSource;
	    double dSource82 = dSource8 / 2.0;

	    double dWeight1 = - dNSA * dSource8 + dSource42 - dSource2 + dNSA;
	    double dWeight2 = dSource82 - dSource4 + dNSB;
	    double dWeight3 = - dSource82 + dSource42 + dSource2 + dNSA;
	    double dWeight4 = dNSA * dSource8;

	    pdDestination[iDestination]
		= (dWeight1 * pdSource[iSource - 1]
		   + dWeight2 * pdSource[iSource]
		   + dWeight3 * pdSource[iSource + 1] + dWeight4 * pdSource[iSource + 2]);
	}

	//- fill the destination till the end

	for (; iDestination <= iDestinationSize ; dActual += dRangeStep, iSource = (int)dActual, iDestination++)
	{
	    if (iSource < iSourceSize)
	    {
		pdDestination[iDestination]
		    = ((dActual - (double)iSource)
		       * (pdSource[iSource + 1] - pdSource[iSource]) + pdSource[iSource]);
	    }
	    else
	    {
		pdDestination[iDestination] = pdSource[iSourceSize];
	    }
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
HeccerTabulatedGateNew
(struct Heccer *pheccer,
 void *pvParameters,
 int iSize,
 double dStart,
 double dEnd,
 int iEntries)
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


