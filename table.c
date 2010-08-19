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


#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "heccer/heccer.h"
#include "heccer/table.h"


int
static
HeccerChannelPersistentSteadyStateDualTauTabulate
(struct ChannelPersistentSteadyStateDualTau *pcpsdt, struct Heccer *pheccer);

int
static
HeccerChannelPersistentSteadyStateTauTabulate
(struct ChannelPersistentSteadyStateTau *pcpst, struct Heccer *pheccer);

int
static
HeccerChannelSteadyStateSteppedTauTabulate
(struct ChannelSteadyStateSteppedTau *pcsst, struct Heccer *pheccer);

int
static
HeccerDiscretizeConcentrationGate
(struct Heccer *pheccer, struct ConcentrationActivator *pac);

int
static
HeccerDiscretizeGateConcept
(struct Heccer *pheccer, struct GateConcept *pgc);

static int
HeccerTableDump
(struct HeccerTabulatedGate *phtg, int iIndex, FILE *pfile, int iSelection);

static
int
HeccerTabulatedGateCompareParameters
(struct HeccerTabulatedGate *phtg, void *pv, size_t iSize);

static
int
HeccerTabulatedGateLookupParameters
(struct Heccer *pheccer, void *pv, size_t iSize);

static
int
HeccerTabulatedGateNewForParameters
(struct Heccer *pheccer,
 void *pvParameters,
 size_t iSize,
 double dStart,
 double dEnd,
 int iEntries);

int
static
HeccerTabulateSpringMass(struct Heccer *pheccer, struct ChannelSpringMass *pcsm);

static
int
HeccerTabulatedSpringMassCompareParameters
(struct HeccerTabulatedSpringMass *phtsm, void *pv, size_t iSize);

static
int
HeccerTabulatedSpringMassLookup
(struct Heccer *pheccer, void *pv, size_t iSize);

static
int
HeccerTabulatedSpringMassNew
(struct Heccer *pheccer, void *pvParameters, size_t iSize);

static
int
HeccerTabulatedGateLookupTable
(struct Heccer *pheccer,
 struct HeccerTabulatedGate *phtg);

static
int
HeccerTabulatedGateStoreTable
(struct Heccer *pheccer,
 struct HeccerTabulatedGate *phtgNew);


/// 
/// \arg pca a concentration gate concept.
/// \arg pheccer a heccer.
/// 
/// \return int
/// 
///	success of operation.
/// 
///	phtg....: a filled heccer tabulated gate.
/// 
/// \brief Fill the tables with a discretization of concentration gate
/// kinetics.
/// 

int
HeccerConcentrationGateTabulate
(struct ConcentrationActivator *pca, struct Heccer *pheccer)
{
    //- set default result : ok

    int iResult = TRUE;

    //- get access to the tabulated gate structure

    int iIndex = pca->iTable;

    struct HeccerTabulatedGate *phtg = &pheccer->tgt.phtg[iIndex];

    //- get step size

    double dStep = phtg->hi.dStep;

    //- loop over all entries in the table

    int i;
    double dx;

    for (dx = phtg->hi.dStart, i = 0 ; i <= phtg->iEntries ; i++, dx += dStep)
    {
	//- compute steady state

	double dEquilibrium = 1 / (1 + (pca->parameters.dBasalLevel / dx));

	//- fill in A and B table

	/// \todo perhaps the table names should be redefined ?

	/// \note time step normalization done elsewhere

	phtg->pdA[i] = dEquilibrium / pca->parameters.dTau;

	phtg->pdB[i] = 1 / pca->parameters.dTau;
    }

    //- return result

    return(iResult);
}


/// 
/// \arg pheccer a heccer.
/// \arg pca concentration gate concept description.
/// 
/// \return int : success of operation.
/// 
/// \brief Discretize the given concentration gate concept.
/// 

int
static
HeccerDiscretizeConcentrationGate
(struct Heccer *pheccer, struct ConcentrationActivator *pca)
{
    //- set default result : ok

    int iResult = TRUE;

    //- if already registered

    if (pca->iTable != -1)
    {
	return(TRUE);
    }

    //- if table is hardcoded

    if (pca->htg.pdA
	|| pca->htg.pdB)
    {
	if (!pca->htg.pdA
	    || !pca->htg.pdB)
	{
	    HeccerError
		(pheccer,
		 NULL,
		 "HeccerDiscretizeConcentrationGate(): if a gate has a hardcoded table for one kinetic, it must have hardcoded tables for all kinetics.");

	    return(FALSE);
	}

	//- lookup table

	int i = HeccerTabulatedGateLookupTable(pheccer, &pca->htg);

	//- if not found

	if (i == -1)
	{
	    //- store the table as is

	    i = HeccerTabulatedGateStoreTable(pheccer, &pca->htg);

	    if (i == -1)
	    {
		return(FALSE);
	    }
	    else
	    {
		//- register the index where it is stored

		pca->iTable = i;

		//- return success

		return(TRUE);
	    }
	}

	//- if found

	else
	{
	    //- register the index where it is stored

	    pca->iTable = i;

	    //- return success

	    return(TRUE);
	}
    }

    //- allocate structures

    double dStart = pheccer->ho.dConcentrationGateStart;
    double dEnd = pheccer->ho.dConcentrationGateEnd;
    int iEntries = pheccer->ho.iIntervalEntries;

    //- lookup the table parameters ...

    int i = HeccerTabulatedGateLookupParameters(pheccer, &pca->parameters, sizeof(pca->parameters));

    if (i == -1)
    {
	//- ... or create a new table for these parameters

	i = HeccerTabulatedGateNewForParameters(pheccer, &pca->parameters, sizeof(pca->parameters), dStart, dEnd, iEntries);

	if (i == -1)
	{
	    return(FALSE);
	}

	//- register the index

	pca->iTable = i;

	//- fill the table with the discretized gate kinetics

	iResult = iResult && HeccerConcentrationGateTabulate(pca, pheccer);
    }
    else
    {
	pca->iTable = i;
    }

    //- return result

    return(iResult);
}


/// 
/// \arg pheccer a heccer.
/// \arg pgc gate concept description.
/// 
/// \return int : success of operation.
/// 
/// \brief Discretize the given gate concept.
///
/// \details
/// 
///	Note that for a single gate, this function sets up the A
///	and B kinetic discretization.
/// 

int
static
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

    //- if table is hardcoded

    if (pgc->htg.pdA
	|| pgc->htg.pdB)
    {
	if (!pgc->htg.pdA
	    || !pgc->htg.pdB)
	{
	    HeccerError
		(pheccer,
		 NULL,
		 "HeccerDiscretizeGateConcept(): if a gate has a hardcoded table for one kinetic, it must have hardcoded tables for all kinetics.");

	    return(FALSE);
	}

	//- lookup table

	int i = HeccerTabulatedGateLookupTable(pheccer, &pgc->htg);

	//- if not found

	if (i == -1)
	{
	    //- store the table as is

	    i = HeccerTabulatedGateStoreTable(pheccer, &pgc->htg);

	    if (i == -1)
	    {
		return(FALSE);
	    }
	    else
	    {
		//- register the index where it is stored

		pgc->iTable = i;

		//- return success

		return(TRUE);
	    }
	}

	//- if found

	else
	{
	    //- register the index where it is stored

	    pgc->iTable = i;

	    //- return success

	    return(TRUE);
	}
    }

    //- allocate structures

    double dStart = pheccer->ho.dIntervalStart;
    double dEnd = pheccer->ho.dIntervalEnd;
    int iEntries = pheccer->ho.iIntervalEntries;

    //- lookup the table parameters ...

    int i = HeccerTabulatedGateLookupParameters(pheccer, &pgc->parameters, sizeof(pgc->parameters));

    if (i == -1)
    {
	//- ... or create a new table for these parameters

	i = HeccerTabulatedGateNewForParameters(pheccer, &pgc->parameters, sizeof(pgc->parameters), dStart, dEnd, iEntries);

	if (i == -1)
	{
	    return(FALSE);
	}

	//- register the index

	pgc->iTable = i;

	//- fill the table with the discretized gate kinetics

	iResult = iResult && HeccerGateConceptTabulate(pgc, pheccer);
    }
    else
    {
	pgc->iTable = i;
    }

    //- return result

    return(iResult);
}


/// 
/// \arg pgc a heccer gate concept.
/// \arg pheccer a heccer.
/// 
/// \return int
/// 
///	success of operation.
/// 
///	phtg....: a filled heccer tabulated gate.
/// 
/// \brief Fill the tables with a discretization of the gate kinetics.
/// 

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

	if (phtg->pdA)
	{
	    double dMultiplier = pgc->parameters.gkA.dHHScale;
	    double dMembraneDependence = pgc->parameters.gkA.dHHMult;
	    double dMembraneDependenceOffset = pgc->parameters.gkA.dHHOffsetM;
	    int iNominator = pgc->parameters.gkA.iHHFactorFlag;
	    double dDeNominatorOffset = pgc->parameters.gkA.dHHAdd;
	    double dMembraneOffset = pgc->parameters.gkA.dHHOffsetE;
	    double dTauDenormalizer = pgc->parameters.gkA.dHHTau;

	    /// \todo check the MCAD MMGLT macro to see how it deals with
	    /// \todo relative errors.  The current implementation is magnitude
	    /// \todo dependent, and obviously completely add hoc.

	    if (fabs(dTauDenormalizer) < 1e-17)
	    {
		dCarryOver = 0.0;
		phtg->pdA[i] = 0.0;
	    }
	    else
	    {
		double dDeNominator = dDeNominatorOffset + exp((dx + dMembraneOffset) / dTauDenormalizer);

		if (fabs(dDeNominator) < 1e-17)
		{
		    phtg->pdA[i] = phtg->pdA[i - 1];
		}
		else
		{
		    if (iNominator == 1)
		    {
			phtg->pdA[i] = (dMultiplier + (dMembraneDependenceOffset - dMembraneDependence * dx)) * dDeNominator;
		    }
		    else if (iNominator == -1)
		    {
			phtg->pdA[i] = (dMultiplier + (dMembraneDependenceOffset - dMembraneDependence * dx)) / dDeNominator;
		    }
		    else
		    {
			iResult = FALSE;
		    }
		}

		//- remember alpha, such that we can add it to beta below

		dCarryOver = phtg->pdA[i];
	    }
	}

	if (phtg->pdA && phtg->pdB)
	{
	    double dMultiplier = pgc->parameters.gkB.dHHScale;
	    double dMembraneDependence = pgc->parameters.gkB.dHHMult;
	    double dMembraneDependenceOffset = pgc->parameters.gkB.dHHOffsetM;
	    int iNominator = pgc->parameters.gkB.iHHFactorFlag;
	    double dDeNominatorOffset = pgc->parameters.gkB.dHHAdd;
	    double dMembraneOffset = pgc->parameters.gkB.dHHOffsetE;
	    double dTauDenormalizer = pgc->parameters.gkB.dHHTau;

	    if (fabs(dTauDenormalizer) < 1e-17)
	    {
		phtg->pdB[i] = 0.0;
	    }
	    else
	    {
		double dDeNominator = dDeNominatorOffset + exp((dx + dMembraneOffset) / dTauDenormalizer);

		if (fabs(dDeNominator) < 1e-17)
		{
		    phtg->pdB[i] = phtg->pdB[i - 1];
		}
		else
		{
		    if (iNominator == 1)
		    {
			phtg->pdB[i] = (dMultiplier + dMembraneDependenceOffset - (dMembraneDependence * dx)) * dDeNominator;
		    }
		    else if (iNominator == -1)
		    {
			phtg->pdB[i] = (dMultiplier + dMembraneDependenceOffset - (dMembraneDependence * dx)) / dDeNominator;
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
		phtg->pdB[i] += dCarryOver;
	    }
	}

    }

    //- return result

    return(iResult);
}


/// 
/// \arg pcpsdt a channel with steady state and two time constants.
/// \arg pheccer a heccer.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Fill the tables with a discretization of the gate kinetics.
///
/// \details
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

int
static
HeccerChannelPersistentSteadyStateDualTauTabulate
(struct ChannelPersistentSteadyStateDualTau *pcpsdt, struct Heccer *pheccer)
{
    //- set default result : ok

    int iResult = TRUE;

    //- if already registered

    //! note that this test evaluates to true during the second and
    //! third mechanism compilation phase.

    if (pcpsdt->iFirstTable != -1)
    {
	return(TRUE);
    }

    //- allocate structures

    double dStart = pheccer->ho.dIntervalStart;
    double dEnd = pheccer->ho.dIntervalEnd;
    int iEntries = pheccer->ho.iIntervalEntries;

    //- lookup the table parameters ...

    int i = HeccerTabulatedGateLookupParameters(pheccer, &pcpsdt->parameters1, sizeof(pcpsdt->parameters1));

    if (i == -1)
    {
	//- ... or create a new table for these parameters

	i = HeccerTabulatedGateNewForParameters(pheccer, &pcpsdt->parameters1, sizeof(pcpsdt->parameters1), dStart, dEnd, iEntries);

	if (i == -1)
	{
	    return(FALSE);
	}

	//- register the index

	pcpsdt->iFirstTable = i;

	//- get access to the tabulated gate structures

	int iIndex1 = pcpsdt->iFirstTable;

	struct HeccerTabulatedGate *phtg1 = &pheccer->tgt.phtg[iIndex1];

	//- allocate the small tables

	int iSmallTableSize = pheccer->ho.iSmallTableSize;

	//20;

	//- get step size

	double dSmallStep = (phtg1->hi.dEnd - phtg1->hi.dStart) / (iSmallTableSize);

	double *pd1 = (double *)calloc(iSmallTableSize + 1, sizeof(double));
	double *pd2 = (double *)calloc(iSmallTableSize + 1, sizeof(double));

	//- loop over all entries in the first small table

	double dx;

	for (dx = phtg1->hi.dStart, i = 0 ; i <= iSmallTableSize ; i++, dx += dSmallStep)
	{
	    double dA = pcpsdt->parameters1.dSteadyState;

	    double dC
		= (pcpsdt->parameters1.tau.dMultiplier
		   / (pcpsdt->parameters1.tau.dDeNominatorOffset
		      + exp((dx + pcpsdt->parameters1.tau.dMembraneOffset)
			    / pcpsdt->parameters1.tau.dTauDenormalizer)));

	    double dA1 = dA;
	    double dB1 = dC;

	    /// \todo check the MCAD MMGLT macro to see how it deals with
	    /// \todo relative errors.  The current implementation is magnitude
	    /// \todo dependent, and obviously completely add hoc.

	    if (fabs(dA1) < 1e-17)
	    {
		if (dA1 < 0.0)
		{
		    dA1 = -1e-17;
		}
		else
		{
		    dA1 = 1e-17;
		}
	    }

	    pd1[i] = dB1 / dA1;
	    pd2[i] = 1.0 / dA1;
	}

	//- interpolate the tables

	double *ppdSources[]
	    = { pd1, pd2, NULL, };
	double *ppdDestinations[]
	    = { phtg1->pdA, phtg1->pdB, NULL, };

	iResult = iResult && HeccerTableInterpolate(ppdSources, ppdDestinations, iSmallTableSize, iEntries);

	//- free allocated memory

	free(pd1);
	free(pd2);
    }
    else
    {
	pcpsdt->iFirstTable = i;
    }

    //- lookup the table parameters ...

    int j = HeccerTabulatedGateLookupParameters(pheccer, &pcpsdt->parameters2, sizeof(pcpsdt->parameters2));

    if (j == -1)
    {
	//- ... or create a new table for these parameters

	j = HeccerTabulatedGateNewForParameters(pheccer, &pcpsdt->parameters2, sizeof(pcpsdt->parameters2), dStart, dEnd, iEntries);

	if (j == -1)
	{
	    return(FALSE);
	}

	//- register the index

	pcpsdt->iSecondTable = j;

	int iIndex2 = pcpsdt->iSecondTable;

	struct HeccerTabulatedGate *phtg2 = &pheccer->tgt.phtg[iIndex2];

	//- allocate the small tables

	int iSmallTableSize = pheccer->ho.iSmallTableSize;

	//20;

	//- get step size

	double dSmallStep = (phtg2->hi.dEnd - phtg2->hi.dStart) / (iSmallTableSize);

	double *pd3 = (double *)calloc(iSmallTableSize + 1, sizeof(double));
	double *pd4 = (double *)calloc(iSmallTableSize + 1, sizeof(double));

	//- loop over all entries in the first small table

	double dx;

	for (dx = phtg2->hi.dStart, i = 0 ; i <= iSmallTableSize ; i++, dx += dSmallStep)
	{
	    double dB = pcpsdt->parameters2.dSteadyState;

	    double dD
		= (pcpsdt->parameters2.tau.dMultiplier
		   / (pcpsdt->parameters2.tau.dDeNominatorOffset
		      + exp((dx + pcpsdt->parameters2.tau.dMembraneOffset)
			    / pcpsdt->parameters2.tau.dTauDenormalizer)));

	    double dA2 = dB;
	    double dB2 = dD;

	    /// \todo check the MCAD MMGLT macro to see how it deals with
	    /// \todo relative errors.  The current implementation is magnitude
	    /// \todo dependent, and obviously completely add hoc.

	    if (fabs(dA2) < 1e-17)
	    {
		if (dA2 < 0.0)
		{
		    dA2 = -1e-17;
		}
		else
		{
		    dA2 = 1e-17;
		}
	    }

	    pd3[i] = dB2 / dA2;
	    pd4[i] = 1.0 / dA2;
	}

	//- interpolate the tables

	double *ppdSources[]
	    = { pd3, pd4, NULL, };
	double *ppdDestinations[]
	    = { phtg2->pdA, phtg2->pdB, NULL, };

	iResult = iResult && HeccerTableInterpolate(ppdSources, ppdDestinations, iSmallTableSize, iEntries);

	//- free allocated memory

	free(pd3);
	free(pd4);
    }
    else
    {
	pcpsdt->iSecondTable = j;
    }

    //- return result

    return(iResult);
}


/// 
/// \arg pcpst a heccer channel with steady state and time constant.
/// \arg pheccer a heccer.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Fill the tables with a discretization of the gate kinetics.
///
/// \details
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

int
static
HeccerChannelPersistentSteadyStateTauTabulate
(struct ChannelPersistentSteadyStateTau *pcpst, struct Heccer *pheccer)
{
    //- set default result : ok

    int iResult = TRUE;

    //- if already registered

    //! note that this test evaluates to true during the second and
    //! third mechanism compilation phase.

    if (pcpst->iTable != -1)
    {
	return(TRUE);
    }

    //- allocate structures

    double dStart = pheccer->ho.dIntervalStart;
    double dEnd = pheccer->ho.dIntervalEnd;
    int iEntries = pheccer->ho.iIntervalEntries;

    //- lookup the table parameters ...

    int i = HeccerTabulatedGateLookupParameters(pheccer, &pcpst->parameters, sizeof(pcpst->parameters));

    if (i == -1)
    {
	//- ... or create a new table for these parameters

	i = HeccerTabulatedGateNewForParameters(pheccer, &pcpst->parameters, sizeof(pcpst->parameters), dStart, dEnd, iEntries);

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
		= (pcpst->parameters.ss.dNominator
		   / ( pcpst->parameters.ss.dMultiplier1
		       * ((exp((dx + pcpst->parameters.ss.dMembraneOffset1) / pcpst->parameters.ss.dTauDenormalizer1)))
		       + pcpst->parameters.ss.dMultiplier2
		       * (exp ((dx + pcpst->parameters.ss.dMembraneOffset2) / pcpst->parameters.ss.dTauDenormalizer2))));

	    double dB
		= (pcpst->parameters.tc.dNominator
		   / (pcpst->parameters.tc.dDeNominatorOffset
		      + (exp((dx + pcpst->parameters.tc.dMembraneOffset) / pcpst->parameters.tc.dTauDenormalizer))));

	    double dA3 = dA;

	    double dB3 = dB;

	    /// \todo check the MCAD MMGLT macro to see how it deals with
	    /// \todo relative errors.  The current implementation is magnitude
	    /// \todo dependent, and obviously completely add hoc.

	    if (fabs(dA3) < 1e-17)
	    {
		if (dA3 < 0.0)
		{
		    dA3 = -1e-17;
		}
		else
		{
		    dA3 = 1e-17;
		}
	    }

	    pd1[i] = dB3 / dA3;
	    pd2[i] = 1.0 / dA3;
	}

	//- interpolate the tables

	double *ppdSources[]
	    = { pd1, pd2, NULL, };
	double *ppdDestinations[]
	    = { phtg->pdA, phtg->pdB, NULL, };

	iResult = iResult && HeccerTableInterpolate(ppdSources, ppdDestinations, iSmallTableSize, iEntries);

	//- free allocated memory

	free(pd1);
	free(pd2);
    }
    else
    {
	pcpst->iTable = i;
    }

    //- return result

    return(iResult);
}


/// 
/// \arg pheccer a heccer.
/// \arg pv a heccer intermediary with table parameters.
/// \arg iPrototype prototype number, INT_MAX for none.
/// \arg iType type of intermediary.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Create the table for a channel.
/// 

int
HeccerTabulateAny
(struct Heccer *pheccer, void *pv, int iPrototype, int iType)
{
    //- set default result: failure

    int iResult = FALSE;

    //- tabulate depending on tables

    switch (iType)
    {
    case MATH_TYPE_Concentration:
    {
	//! channel act-conc once

	//! one table

	struct ConcentrationActivator *pca = (struct ConcentrationActivator *)pv;

	iResult = HeccerDiscretizeConcentrationGate(pheccer, pca);

	break;
    }
    case MATH_TYPE_GateConcept:
    {
	//! channel act once, channel act-inact twice, channel act-conc once

	//! one table

	struct GateConcept *pgc = (struct GateConcept *)pv;
 
	iResult = HeccerDiscretizeGateConcept(pheccer, pgc);

	break;
    }
    case MATH_TYPE_ChannelPersistentSteadyStateDualTau:
    {
	//! called once per channel

	//! two tables

	struct ChannelPersistentSteadyStateDualTau *pcpsdt = (struct ChannelPersistentSteadyStateDualTau *)pv;

	iResult = HeccerChannelPersistentSteadyStateDualTauTabulate(pcpsdt, pheccer);

	break;
    }
    case MATH_TYPE_ChannelPersistentSteadyStateTau:
    {
	//! called once per channel

	//! one table

	struct ChannelPersistentSteadyStateTau *pcpst = (struct ChannelPersistentSteadyStateTau *)pv;

	iResult = HeccerChannelPersistentSteadyStateTauTabulate(pcpst, pheccer);

	break;
    }
    case MATH_TYPE_ChannelSpringMass:
    {
	//! called once per channel

	//! one table

	struct ChannelSpringMass *pcsm = (struct ChannelSpringMass *)pv;

	iResult = HeccerTabulateSpringMass(pheccer, pcsm);

	break;
    }
    case MATH_TYPE_ChannelSteadyStateSteppedTau:
    {
	//! called once per channel

	//! two tables

	struct ChannelSteadyStateSteppedTau *pcsst = (struct ChannelSteadyStateSteppedTau *)pv;

	iResult = HeccerChannelSteadyStateSteppedTauTabulate(pcsst, pheccer);

	break;
    }
    }

    //- return result

    return(iResult);
}


/// 
/// \arg pheccer a heccer.
/// \arg pcsm a heccer channel with steady state and time constant.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Create the table for a spring mass channel.
/// 

int
static
HeccerTabulateSpringMass(struct Heccer *pheccer, struct ChannelSpringMass *pcsm)
{
    //- set default result : ok

    int iResult = TRUE;

    //- if already registered

    if (pcsm->iTable != -1)
    {
	return(TRUE);
    }

    //- lookup the table parameters ...

    int i = HeccerTabulatedSpringMassLookup(pheccer, &pcsm->parameters, sizeof(pcsm->parameters));

    if (i == -1)
    {
	//- ... or create a new table for these parameters

	i = HeccerTabulatedSpringMassNew(pheccer, &pcsm->parameters, sizeof(pcsm->parameters));

	if (i == -1)
	{
	    return(FALSE);
	}

	//- register the index

	pcsm->iTable = i;

	//- get access to the tabulated spring mass structure

	struct HeccerTabulatedSpringMass *phtsm = &pheccer->tsmt.phtsm[i];

	/// compute time constants derived coefficients

	/// \note we normalize the first coefficient over the time step,
	/// \note propagates through all equations.

	phtsm->dX1 = (pcsm->parameters.dTau1 * (1.0 - exp(- pheccer->dStep / pcsm->parameters.dTau1))) / pheccer->dStep;
	phtsm->dX2 = exp(- pheccer->dStep / pcsm->parameters.dTau1);

	phtsm->dY1 = pcsm->parameters.dTau2 * (1.0 - exp(- pheccer->dStep / pcsm->parameters.dTau2));
	phtsm->dY2 = exp(- pheccer->dStep / pcsm->parameters.dTau2);

    }
    else
    {
	pcsm->iTable = i;
    }

    //- return result

    return(iResult);
}


/// 
/// \arg pheccer a heccer.
/// \arg pcsst a heccer channel with steady state and time constant.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Fill the tables with a discretization of the gate kinetics.
///
/// \details 
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

int
static
HeccerChannelSteadyStateSteppedTauTabulate
(struct ChannelSteadyStateSteppedTau *pcsst, struct Heccer *pheccer)
{
    //- set default result : ok

    int iResult = TRUE;

    //- if already registered

    //! note that this test evaluates to true during the second and
    //! third mechanism compilation phase.

    if (pcsst->iFirstTable != -1)
    {
	return(TRUE);
    }

    //- allocate structures

    double dStart = pheccer->ho.dIntervalStart;
    double dEnd = pheccer->ho.dIntervalEnd;
    int iEntries = pheccer->ho.iIntervalEntries;

    //- lookup the table parameters ...

    int i = HeccerTabulatedGateLookupParameters(pheccer, &pcsst->ss_parameters, sizeof(pcsst->ss_parameters));

    if (i == -1)
    {
	//- ... or create a new table for these parameters

	i = HeccerTabulatedGateNewForParameters(pheccer, &pcsst->ss_parameters, sizeof(pcsst->ss_parameters), dStart, dEnd, iEntries);

	if (i == -1)
	{
	    return(FALSE);
	}

	//- register the index

	pcsst->iFirstTable = i;

	//- get access to the tabulated gate structures

	int iIndex1 = pcsst->iFirstTable;

	struct HeccerTabulatedGate *phtg1 = &pheccer->tgt.phtg[iIndex1];

	//- allocate the small tables

	int iSmallTableSize = pheccer->ho.iSmallTableSize;

	//- get step size

	double dSmallStep = (phtg1->hi.dEnd - phtg1->hi.dStart) / (iSmallTableSize);

	double *pd1 = (double *)calloc(iSmallTableSize + 1, sizeof(double));
	double *pd2 = (double *)calloc(iSmallTableSize + 1, sizeof(double));

	//- loop over all entries in the first small table

	double dx;

	for (dx = phtg1->hi.dStart, i = 0 ; i <= iSmallTableSize ; i++, dx += dSmallStep)
	{
	    double dA
		= (pcsst->ss_parameters.first.a.dMultiplier
		   * (dx + pcsst->ss_parameters.first.a.dMembraneDependenceOffset)
		   / ((exp((dx + pcsst->ss_parameters.first.a.dMembraneOffset)
			   / pcsst->ss_parameters.first.a.dTauDenormalizer))
		      + pcsst->ss_parameters.first.a.dDeNominatorOffset));

	    double dB
		= (pcsst->ss_parameters.first.b.dMultiplier
		   * (exp( - (dx + pcsst->ss_parameters.first.b.dMembraneDependenceOffset)
			   / pcsst->ss_parameters.first.b.dTauDenormalizer)));

	    double dC
		= (pcsst->ss_parameters.second.a.dMultiplier
		   * (dx + pcsst->ss_parameters.second.a.dMembraneDependenceOffset)
		   / ((exp((dx + pcsst->ss_parameters.second.a.dMembraneOffset)
			   / pcsst->ss_parameters.second.a.dTauDenormalizer))
		      + pcsst->ss_parameters.second.a.dDeNominatorOffset));

	    double dD
		= (pcsst->ss_parameters.second.b.dMultiplier
		   * (exp( - (dx + pcsst->ss_parameters.second.b.dMembraneDependenceOffset)
			   / pcsst->ss_parameters.second.b.dTauDenormalizer)));

	    double dA4 = (1.0 / (dA + dB));

	    double dB4 = (dC / (dC + dD));

	    /// \todo check the MCAD MMGLT macro to see how it deals with
	    /// \todo relative errors.  The current implementation is magnitude
	    /// \todo dependent, and obviously completely add hoc.

	    if (fabs(dA4) < 1e-17)
	    {
		if (dA4 < 0.0)
		{
		    dA4 = -1e-17;
		}
		else
		{
		    dA4 = 1e-17;
		}
	    }

	    pd1[i] = dB4 / dA4;
	    pd2[i] = 1.0 / dA4;
	}

	//- interpolate the tables

	double *ppdSources[]
	    = { pd1, pd2, NULL, };
	double *ppdDestinations[]
	    = { phtg1->pdA, phtg1->pdB, NULL, };

	iResult = iResult && HeccerTableInterpolate(ppdSources, ppdDestinations, iSmallTableSize, iEntries);

	//- free allocated memory

	free(pd1);
	free(pd2);
    }
    else
    {
	pcsst->iFirstTable = i;
    }

    //- lookup the table parameters ...

    int j = HeccerTabulatedGateLookupParameters(pheccer, &pcsst->tc_parameters, sizeof(pcsst->tc_parameters));

    if (j == -1)
    {
	//- ... or create a new table for these parameters

	j = HeccerTabulatedGateNewForParameters(pheccer, &pcsst->tc_parameters, sizeof(pcsst->tc_parameters), dStart, dEnd, iEntries);

	if (j == -1)
	{
	    return(FALSE);
	}

	//- register the index

	pcsst->iSecondTable = j;

	//- get access to the tabulated gate structures

	int iIndex2 = pcsst->iSecondTable;

	struct HeccerTabulatedGate *phtg2 = &pheccer->tgt.phtg[iIndex2];

	//- allocate the small tables

	int iSmallTableSize = pheccer->ho.iSmallTableSize;

	//- get step size

	double dSmallStep = (phtg2->hi.dEnd - phtg2->hi.dStart) / (iSmallTableSize);

	double *pd3 = (double *)calloc(iSmallTableSize + 1, sizeof(double));
	double *pd4 = (double *)calloc(iSmallTableSize + 1, sizeof(double));

	//- loop over all entries in the first small table

	double dx;

	for (dx = phtg2->hi.dStart, i = 0 ; i <= iSmallTableSize ; i++, dx += dSmallStep)
	{
	    double dA;

	    if (dx < pcsst->tc_parameters.a.dThreshold)
	    {
		dA = pcsst->tc_parameters.a.dLowTarget;
	    }
	    else
	    {
		dA = pcsst->tc_parameters.a.dHighTarget;
	    }

	    double dY
		= (pcsst->tc_parameters.b.dDeNominatorOffset
		   + (exp((dx + pcsst->tc_parameters.b.dMembraneOffset)
			  / pcsst->tc_parameters.b.dTauDenormalizer)));

	    double dB = (1.0 / dY);

	    /// \todo check the MCAD MMGLT macro to see how it deals with
	    /// \todo relative errors.  The current implementation is magnitude
	    /// \todo dependent, and obviously completely add hoc.

	    if (fabs(dA) < 1e-17)
	    {
		if (dA < 0.0)
		{
		    dA = -1e-17;
		}
		else
		{
		    dA = 1e-17;
		}
	    }

	    pd3[i] = dB / dA;
	    pd4[i] = 1.0 / dA;
	}

	//- interpolate the tables

	double *ppdSources[]
	    = { pd3, pd4, NULL, };
	double *ppdDestinations[]
	    = { phtg2->pdA, phtg2->pdB, NULL, };

	iResult = iResult && HeccerTableInterpolate(ppdSources, ppdDestinations, iSmallTableSize, iEntries);

	//- free allocated memory

	free(pd3);
	free(pd4);
    }
    else
    {
	pcsst->iSecondTable = j;
    }

    //- return result

    return(iResult);
}


/// 
/// \arg phtg a tabulated gate.
/// \arg iIndex index of this gate.
/// \arg pfile stdio file.
/// \arg iSelection selection to dump.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Dump tables to given stream, respecting given selection.
/// 

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
	    fprintf(pfile, "Tabulated gate %i, A (iEntry %i) : (%g)\n", iIndex, i, phtg->pdA[i]);
	}

	for (i = 0 ; i < phtg->iEntries ; i++)
	{
	    fprintf(pfile, "Tabulated gate %i, B (iEntry %i) : (%g)\n", iIndex, i, phtg->pdB[i]);
	}
    }

    //- return result

    return(iResult);
}


/// 
/// \arg ppdSources source tables for interpolation.
/// \arg ppdDestinations destination tables for interpolation.
/// \arg iSourceSize size of source tables.
/// \arg iDestinationSize size of destination tables.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Interpolate given tables, uses bezier curves.
///
/// \details
/// 
///	ppdSources and ppdDestinations must be NULL terminated.
///	ppdDestinations must be preallocated, presumably using
///	HeccerTabulatedGateNew().
/// 

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
	/// \note modified and optimized for heccer from
	/// \note http://people.scs.fsu.edu/~burkardt/cpp_src/spline/spline.C

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


/// 
/// \arg ptgt tabulated gate table.
/// \arg pfile stdio file.
/// \arg iSelection selection to dump.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Dump tables.
/// 

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
	//- dump table

	iResult = iResult && HeccerTableDump(&ptgt->phtg[i], i, pfile, iSelection);
    }

    //- return result

    return(iResult);
}


/// 
/// \arg pheccer a heccer.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Rearrange table values for cache line loading.
/// 

int HeccerTablesRearrange(struct Heccer *pheccer)
{
    //- set default result : ok

    int iResult = TRUE;

    //- allocate rearranged tables

    int iEntries = pheccer->tgt.iTabulatedGateCount * pheccer->ho.iIntervalEntries;

    pheccer->tgt.pdRearranged = calloc(iEntries * 2, sizeof(double));

    if (!pheccer->tgt.pdRearranged)
    {
	return(FALSE);
    }

    //- loop over all tables

    int i;

    for (i = 0 ; i < pheccer->tgt.iTabulatedGateCount; i++)
    {
	//- get pointer to current table

	struct HeccerTabulatedGate *phtg = &pheccer->tgt.phtg[i];

	//- loop over all entries in this table

	int j;

	for (j = 0 ; j < pheccer->ho.iIntervalEntries ; j++)
	{
	    //- copy the values from the unarranged table to the rearranged table

	    pheccer->tgt.pdRearranged[(j * pheccer->tgt.iTabulatedGateCount + i) * 2] = phtg->pdA[j];

	    pheccer->tgt.pdRearranged[(j * pheccer->tgt.iTabulatedGateCount + i) * 2 + 1] = phtg->pdB[j];
	}
    }

    //- return result

    return(iResult);
}


/// 
/// \arg ptgt tabulated gate table.
/// \arg pfile stdio file.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Deserialize the A-B values inside a table.
///
/// \details HeccerTableValuesDeserialize() uses phtg->iEntries to
/// determine the table sizes, allocate memory and read the actual
/// tables values from the file.  No checking for little-endian etc.
/// 

int
HeccerTableValuesDeserialize
(struct HeccerTabulatedGate *phtg, FILE *pfile)
{
    //- set default result : ok

    int iResult = TRUE;

    //- deserialize A part

    if (phtg->iEntries)
    {
	phtg->pdA = (double *)calloc(phtg->iEntries + 1, sizeof(phtg->pdA[0]));

	if (!phtg->pdA)
	{
	    return(0);
	}

	if (fread(phtg->pdA, sizeof(phtg->pdA[0]), phtg->iEntries + 1, pfile) != phtg->iEntries + 1)
	{
	    return(0);
	}
    }

    //- serialize B part

    if (phtg->iEntries)
    {
	phtg->pdB = (double *)calloc(phtg->iEntries + 1, sizeof(phtg->pdB[0]));

	if (!phtg->pdB)
	{
	    return(0);
	}

	if (fread(phtg->pdB, sizeof(phtg->pdB[0]), phtg->iEntries + 1, pfile) != phtg->iEntries + 1)
	{
	    return(0);
	}
    }

    //- return result

    return(iResult);
}


/// 
/// \arg ptgt tabulated gate table.
/// \arg pfile stdio file.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Serialize the A-B values inside a table.
/// 

int
HeccerTableValuesSerialize
(struct HeccerTabulatedGate *phtg, FILE *pfile)
{
    //- set default result : ok

    int iResult = TRUE;

    //- serialize A part

    if (fwrite(&phtg->pdA[0], sizeof(phtg->pdA[0]), phtg->iEntries + 1, pfile) != phtg->iEntries + 1)
    {
	return(0);
    }

    //- serialize B part

    if (fwrite(&phtg->pdB[0], sizeof(phtg->pdB[0]), phtg->iEntries + 1, pfile) != phtg->iEntries + 1)
    {
	return(0);
    }

    //- return result

    return(iResult);
}


/// 
/// \arg phtg an initialized gate table.
/// \arg pv parameters to use for comparison.
/// \arg iSize size of parameter block.
/// 
/// \return int
/// 
///	See memcmp() manual, if sizes differ then -2 is returned.
/// 
/// \details
/// 
///	Compare parameters for a candidate gate with the parameters
///	of an existing table.
/// 

static
int
HeccerTabulatedGateCompareParameters
(struct HeccerTabulatedGate *phtg, void *pv, size_t iSize)
{
    //- set default result : match

    int iResult = 0;

    //- if sizes differ

    if (iSize != phtg->iSizeParameters)
    {
	//- return -2

	return -2;
    }

    //- set result : compare memory regions, using smallest size

    iSize = iSize < phtg->iSizeParameters ? iSize : phtg->iSizeParameters;

    iResult = memcmp(phtg->pvParameters, pv, iSize);

    //- return result

    return(iResult);
}


/// 
/// \arg pheccer a heccer.
/// \arg pv table parameter block.
/// \arg iSize size of parameter block.
/// 
/// \return int
/// 
///	tabulated gate index, -1 for failure.
/// 
/// \brief Lookup an existing table.
/// 

static
int
HeccerTabulatedGateLookupParameters
(struct Heccer *pheccer, void *pv, size_t iSize)
{
    //- set default result : not found

    int iResult = -1;

    /// \note a protection for the case where you accidently forget to dereference

    if (iSize < 10)
    {
	((int *)0)[0] = 0;
    }

    //- loop over all tables

    int i;

    for (i = 0 ; i < pheccer->tgt.iTabulatedGateCount; i++)
    {
	//- get pointer to current table

	struct HeccerTabulatedGate *phtg = &pheccer->tgt.phtg[i];

	//- if match

	if (HeccerTabulatedGateCompareParameters(phtg, pv, iSize) == 0)
	{
	    //- set table index

	    iResult = i;

	    //- break searching loop

	    break;
	}
    }

    //- return result

    return(iResult);
}


/// 
/// \arg pheccer a heccer.
/// \arg dStart start value for table.
/// \arg dEnd end value for table.
/// \arg iEntries number of entries in the table.
/// 
/// \return int
/// 
///	tabulated gate index, -1 for failure.
/// 
/// \brief Allocate a new table.
/// 

static
int
HeccerTabulatedGateNewForParameters
(struct Heccer *pheccer,
 void *pvParameters,
 size_t iSize,
 double dStart,
 double dEnd,
 int iEntries)
{
    struct HeccerTabulatedGate *phtg = NULL;

    if (pheccer->tgt.iTabulatedGateCount >= HECCER_TABULATED_GATES_MAX)
    {
	return(-1);
    }

#define HECCER_STATIC_TABULATED_GATES
#ifdef HECCER_STATIC_TABULATED_GATES

    //- set result : from pool

    phtg = &pheccer->tgt.phtg[pheccer->tgt.iTabulatedGateCount];

#else

    //- set result : allocate a new tabulated gate

    phtg = calloc(1, sizeof(*phtg));

#endif

    //- increment registry count

    pheccer->tgt.iTabulatedGateCount++;

    //- initialize tabulation parameters

    phtg->iSizeParameters = iSize;
    phtg->pvParameters = pvParameters;

    //- initialize interval discretizer

    phtg->hi.dStart = dStart;
    phtg->hi.dEnd = dEnd;
    phtg->hi.dStep = (phtg->hi.dEnd - phtg->hi.dStart) / iEntries;

    //- initialize discrete function entries

    phtg->iEntries = iEntries;
    phtg->pdA = calloc(phtg->iEntries + 1, sizeof(*phtg->pdA));
    phtg->pdB = calloc(phtg->iEntries + 1, sizeof(*phtg->pdB));

    //- initialize the tao

    phtg->htao.iShape = 0;

    //- return result

    return(pheccer->tgt.iTabulatedGateCount - 1);
}


/// 
/// \arg phtsm an initialized gate table.
/// \arg pv parameters to use for comparison.
/// \arg iSize size of parameter block.
/// 
/// \return int
/// 
///	See memcmp() manual.
/// 
/// \details
/// 
///	Compare parameters for a candidate gate with the parameters
///	of an existing table.
/// 

static
int
HeccerTabulatedSpringMassCompareParameters
(struct HeccerTabulatedSpringMass *phtsm, void *pv, size_t iSize)
{
    //- set default result : match

    int iResult = 0;

    //- set result : compare memory regions, using smallest size

    iSize = iSize < phtsm->iSizeParameters ? iSize : phtsm->iSizeParameters;

    iResult = memcmp(phtsm->pvParameters, pv, iSize);

    //- return result

    return(iResult);
}


/// 
/// \arg pheccer a heccer.
/// \arg pv table parameter block.
/// \arg iSize size of parameter block.
/// 
/// \return int
/// 
///	tabulated spring mass index, -1 for failure.
/// 
/// \brief Lookup an existing table.
/// 

static
int
HeccerTabulatedSpringMassLookup
(struct Heccer *pheccer, void *pv, size_t iSize)
{
    //- set default result : not found

    int iResult = -1;

    /// \note a protection for the case where you accidently forget to dereference

    if (iSize < 10)
    {
	((int *)0)[0] = 0;
    }

    //- loop over all tables

    int i;

    for (i = 0 ; i < pheccer->tsmt.iTabulatedSpringMassCount; i++)
    {
	//- get pointer to current table

	struct HeccerTabulatedSpringMass *phtsm = &pheccer->tsmt.phtsm[i];

	//- if match

	if (HeccerTabulatedSpringMassCompareParameters(phtsm, pv, iSize) == 0)
	{
	    //- set table index

	    iResult = i;

	    //- break searching loop

	    break;
	}
    }

    //- return result

    return(iResult);
}


/// 
/// \arg pheccer a heccer.
/// 
/// \return int
/// 
///	tabulated spring mass index, -1 for failure.
/// 
/// \brief Allocate a new table.
/// 

static
int
HeccerTabulatedSpringMassNew
(struct Heccer *pheccer, void *pvParameters, size_t iSize)
{
    struct HeccerTabulatedSpringMass *phtsm = NULL;

    if (pheccer->tsmt.iTabulatedSpringMassCount >= HECCER_TABULATED_SPRINGMASS_MAX)
    {
	return(-1);
    }

    //- set result : from pool

    phtsm = &pheccer->tsmt.phtsm[pheccer->tsmt.iTabulatedSpringMassCount];

    //- increment registry count

    pheccer->tsmt.iTabulatedSpringMassCount++;

    //- initialize tabulation parameters

    phtsm->iSizeParameters = iSize;
    phtsm->pvParameters = pvParameters;

    //- return result

    return(pheccer->tsmt.iTabulatedSpringMassCount - 1);
}


/// 
/// \arg pheccer a heccer.
/// \arg phtg tabulated gate.
/// 
/// \return int
/// 
///	tabulated gate index, -1 for failure.
/// 
/// \brief Lookup table.
///
/// \details
/// 
///	Note that the parameters that identify the table must be
///	initialized correctly before this function is called.
/// 

static
int
HeccerTabulatedGateLookupTable
(struct Heccer *pheccer,
 struct HeccerTabulatedGate *phtg)
{
    //- set default result: not found

    int iResult = -1;

    //- loop over all tables pointers

    int i;

    for (i = 0 ; i < pheccer->tgt.iTabulatedGateCount ; i++)
    {
	//- if pointers match

	if (pheccer->tgt.phtg[i].pdA == phtg->pdA
	    && pheccer->tgt.phtg[i].pdB == phtg->pdB)
	{
	    //- set result

	    iResult = i;

	    //- break search loop

	    break;
	}
    }

    //- return result

    return(iResult);
}


/// 
/// \arg pheccer a heccer.
/// \arg phtgNew tabulated gate.
/// 
/// \return int
/// 
///	tabulated gate index, -1 for failure.
/// 
/// \brief Store a new table.
///
/// \details
/// 
///	Note that the parameters that identify the table must be
///	initialized correctly before this function is called.
/// 

static
int
HeccerTabulatedGateStoreTable
(struct Heccer *pheccer,
 struct HeccerTabulatedGate *phtgNew)
{
    struct HeccerTabulatedGate *phtg = NULL;

    if (pheccer->tgt.iTabulatedGateCount >= HECCER_TABULATED_GATES_MAX)
    {
	return(-1);
    }

#define HECCER_STATIC_TABULATED_GATES
#ifdef HECCER_STATIC_TABULATED_GATES

    //- set result : from pool

    phtg = &pheccer->tgt.phtg[pheccer->tgt.iTabulatedGateCount];

#else

    //- set result : allocate a new tabulated gate

    phtg = calloc(1, sizeof(*phtg));

#endif

    //- increment registry count

    pheccer->tgt.iTabulatedGateCount++;

    //- we simply copy all the parameters

    *phtg = *phtgNew;

    //- return result

    return(pheccer->tgt.iTabulatedGateCount - 1);
}


