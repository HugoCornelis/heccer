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
#include <stdlib.h>
#include <string.h>

#include "heccer/addressing.h"
#include "heccer/heccer.h"


#ifdef HECCER_SOURCE_NEUROSPACES
static
int
HeccerAddressCompartmentSerial2Intermediary
(struct Heccer *pheccer, int iSerial, char *pcField);
#endif

static
void *
HeccerAddressCompartmentVariable
(struct Heccer *pheccer, int iIntermediary, char *pcField);

static
void *
HeccerAddressMechanismVariable
(struct Heccer *pheccer, int iIndex, char *pcField);

#ifdef HECCER_SOURCE_NEUROSPACES
static
int
HeccerAddressSerial2Intermediary
(struct Heccer *pheccer, int iIndex, char *pcField);
#endif


/// **************************************************************************
///
/// SHORT: HeccerAddressVariable()
///
/// ARGS.:
///
///	pheccer...: a heccer.
///	iSerial...: identification number.
///	pcField...: name of requested variable.
///
/// RTN..: void *
///
///	pointer to the requested field, NULL for failure.
///
/// DESCR: Find the simulation sequence of a given variable.
///
///	In all cases, as of the moment of writing, the pointer is a
///	pointer to a double.
///
/// **************************************************************************

#ifdef HECCER_SOURCE_NEUROSPACES
void *
HeccerAddressVariable
(struct Heccer *pheccer, int iSerial, char *pcType)
{
    //- set default result : not found

    void *pvResult = NULL;

    iSerial = ADDRESSING_NEUROSPACES_2_HECCER(iSerial);

    int iIntermediary = HeccerAddressSerial2Intermediary(pheccer, iSerial, pcType);

    if (iIntermediary != -1)
    {
	//- for membrane potential

	if (strcmp(pcType, "Vm") == 0
	    || strcmp(pcType, "inject") == 0
	    || strcmp(pcType, "Im") == 0
	    || strcmp(pcType, "Ileak") == 0)
	{
	    pvResult = HeccerAddressCompartmentVariable(pheccer, iIntermediary, pcType);
	}
	else
	{
	    pvResult = HeccerAddressMechanismVariable(pheccer, iIntermediary, pcType);
	}
    }

    //- return result

    return(pvResult);
}
#endif


/// **************************************************************************
///
/// SHORT: HeccerAddressCompartmentVariable()
///
/// ARGS.:
///
///	pheccer.......: a heccer.
///	iIntermediary.: index of compartment in the intermediary.
///	pcField.......: name of requested variable.
///
/// RTN..: void *
///
///	pointer to the requested field, NULL for failure.
///
/// DESCR: Find the simulation sequence of a given variable.
///
/// **************************************************************************

static
void *
HeccerAddressCompartmentVariable
(struct Heccer *pheccer, int iIntermediary, char *pcField)
{
    //- set default result : not found

    void *pvResult = NULL;

    //- for membrane potential

    if (strcmp(pcField, "Vm") == 0)
    {
	//- convert intermediary to schedule number

	int iSchedule = pheccer->indexers.md.piForward[iIntermediary];

	//- set result

	double *pdResult = &pheccer->vm.pdVms[iSchedule];

	pvResult = (void *)pdResult;
    }

    //- for injected current

    else if (strcmp(pcField, "inject") == 0)
    {
    }

    //- for total membrane current

    else if (strcmp(pcField, "Im") == 0)
    {
    }

    //- for membrane leak current

    else if (strcmp(pcField, "Ileak") == 0)
    {
    }

    //- return result

    return(pvResult);
}


/// **************************************************************************
///
/// SHORT: HeccerAddressMechanismVariable()
///
/// ARGS.:
///
///	pheccer.......: a heccer.
///	iIntermediary.: index of mechanism in the intermediary.
///	pcField.......: name of requested variable.
///
/// RTN..: void *
///
///	pointer to the requested field, NULL for failure.
///
/// DESCR: Find the simulation sequence of a given variable.
///
/// **************************************************************************

static
void *
HeccerAddressMechanismVariable
(struct Heccer *pheccer, int iIndex, char *pcField)
{
    //- set default result : not found

    void *pvResult = NULL;

    //t map the field to an operator: -1, -2, -3 etc.
    //t subtract the operator from iMat

    //- get mat number

    int iMat = pheccer->vm.piMC2Mat[iIndex];

    //- set result

    printf("mat number for %i is %i\n", iIndex, iMat);

    //! note that this is implicitly assumed to be a pointer to double.

    pvResult = pheccer->vm.ppvMatsIndex[iMat];

    //- return result

    return(pvResult);
}


/// **************************************************************************
///
/// SHORT: HeccerAddressCompartmentSerial2Intermediary()
///
/// ARGS.:
///
///	pheccer...: a heccer.
///	iSerial...: identification number.
///	pcField...: name of requested variable.
///
/// RTN..: int
///
///	index into the intermediary, -1 for not found.
///
/// DESCR: Lookup the index of the given serial.
///
/// **************************************************************************

#ifdef HECCER_SOURCE_NEUROSPACES
static
int
HeccerAddressCompartmentSerial2Intermediary
(struct Heccer *pheccer, int iSerial, char *pcField)
{
    //- set default result : not found

    int iResult = -1;

    //- loop over the compartment intermediary

    int i;

    for (i = 0; i < pheccer->inter.iCompartments ; i++)
    {
	//- get current compartment

	struct Compartment *pcomp = &pheccer->inter.pcomp[i];

	//- if serial matches

	if (pcomp->mc.iSerial == iSerial)
	{
	    //t check if the field type is 'compatible' with the math component

	    //- set result : current index

	    iResult = i;

	    //- break searching loop

	    break;
	}
    }

    //- return result

    return(iResult);
}
#endif


/// **************************************************************************
///
/// SHORT: HeccerAddressMechanismSerial2Intermediary()
///
/// ARGS.:
///
///	pheccer...: a heccer.
///	iSerial...: identification number.
///	pcField...: name of requested variable.
///
/// RTN..: int
///
///	index into the intermediary, -1 for not found.
///
/// DESCR: Lookup the index of the given serial.
///
/// **************************************************************************

#ifdef HECCER_SOURCE_NEUROSPACES
static
int
HeccerAddressMechanismSerial2Intermediary
(struct Heccer *pheccer, int iSerial, char *pcField)
{

    //- set default result : not found

    int iResult = -1;

    //- loop over the compartment intermediary

    int i;

    for (i = 0; i < pheccer->inter.pmca->iMathComponents ; i++)
    {
	//- get math component

	struct MathComponent *pmc = pheccer->inter.pmca->pmc;

	//- if serial matches

	if (pmc->iSerial == iSerial)
	{
	    //- set result : current index

	    iResult = i;

	    //- break searching loop

	    break;
	}
    }

    //- return result

    return(iResult);
}
#endif


/// **************************************************************************
///
/// SHORT: HeccerAddressSerial2Intermediary()
///
/// ARGS.:
///
///	pheccer...: a heccer.
///	iSerial...: identification number.
///	pcField...: name of requested variable.
///
/// RTN..: int
///
///	index into the intermediary, -1 for not found.
///
/// DESCR: Lookup the index of the given serial.
///
///	Note that depending on the field, you get an index into
///	mechanisms or an index into the compartments.
///
/// **************************************************************************

#ifdef HECCER_SOURCE_NEUROSPACES
static
int
HeccerAddressSerial2Intermediary
(struct Heccer *pheccer, int iSerial, char *pcField)
{
    //- set default result : not found

    int iResult = -1;

    if (strcmp(pcField, "Vm") == 0
	|| strcmp(pcField, "inject") == 0
	|| strcmp(pcField, "Im") == 0
	|| strcmp(pcField, "Ileak") == 0)
    {
	iResult = HeccerAddressCompartmentSerial2Intermediary(pheccer, iSerial, pcField);
    }
    else
    {
	iResult = HeccerAddressMechanismSerial2Intermediary(pheccer, iSerial, pcField);
    }

    //- return result

    return(iResult);
}
#endif


