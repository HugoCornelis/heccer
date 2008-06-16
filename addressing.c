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


#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "heccer/addressing.h"
#include "heccer/heccer.h"
#include "heccer/mathcomponent.h"


#ifdef HECCER_SOURCE_NEUROSPACES
static
int
HeccerAddressCompartmentSerial2Intermediary
(struct Heccer *pheccer, int iSerial, char *pcType);
#endif

#ifdef HECCER_SOURCE_NEUROSPACES
static
int
HeccerAddressSerial2Intermediary
(struct Heccer *pheccer, int iIndex, char *pcType);
#endif


/// **************************************************************************
///
/// SHORT: HeccerAddressableSet()
///
/// ARGS.:
///
///	pheccer...: a heccer.
///	iSerial...: identification number.
///	pcType....: name of requested variable.
///	dValue....: new value for this variable.
///
/// RTN..: char *
///
///	error code, NULL for success.
///
/// DESCR: Set a variable in a compiled model.
///
/// **************************************************************************

#ifdef HECCER_SOURCE_NEUROSPACES
char *
HeccerAddressableSet
(struct Heccer *pheccer, int iSerial, char *pcType, double dValue)
{
    //- set default result: success

    char *pcResult = NULL;

    //- find the addressable

    double *pd = HeccerAddressVariable(pheccer, iSerial, pcType);

    if (pd)
    {
	//- set the value

	*pd = dValue;
    }
    else
    {
	pcResult = "Variable cannot be found in this compiled heccer instance";
    }

    //- return result

    return(pcResult);
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
///	pcType........: name of requested variable.
///
/// RTN..: void *
///
///	pointer to the requested field, NULL for failure.
///
/// DESCR: Find the simulation sequence of a given variable.
///
/// **************************************************************************

void *
HeccerAddressCompartmentVariable
(struct Heccer *pheccer, int iIntermediary, char *pcType)
{
    //- set default result : not found

    void *pvResult = NULL;

    //- for membrane potential

    if (strcasecmp(pcType, "Vm") == 0)
    {
	//- convert intermediary to schedule number

	int iSchedule = pheccer->indexers.md.piForward[iIntermediary];

	//- set result

	double *pdResult = &pheccer->vm.pdVms[iSchedule];

	pvResult = (void *)pdResult;
    }

    //- for injected current

    else if (strcasecmp(pcType, "inject") == 0)
    {
	//- convert intermediary to schedule number

	int iSchedule = pheccer->indexers.md.piForward[iIntermediary];

	//- get entry in mat array

	struct MatsCompartment *pmatsc
	    = (struct MatsCompartment *)pheccer->vm.ppvCMatsIndex[iSchedule];

	//- set result

	double *pdResult = &pmatsc->dInjected;

	pvResult = (void *)pdResult;
    }

    //- for total membrane current

    else if (strcasecmp(pcType, "Im") == 0)
    {
    }

    //- for membrane leak current

    else if (strcasecmp(pcType, "Ileak") == 0)
    {
    }

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
///	pcType....: name of requested variable.
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
(struct Heccer *pheccer, int iSerial, char *pcType)
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
///	pcType....: name of requested variable.
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
(struct Heccer *pheccer, int iSerial, char *pcType)
{

    //- set default result : not found

    int iResult = -1;

    //- loop over the math components intermediary

    struct MathComponent *pmc = pheccer->inter.pmca->pmc;

    int i;

    for (i = 0; i < pheccer->inter.pmca->iMathComponents ; i++)
    {
	//- if searched serial lower than current serial

	if (pmc->iSerial > iSerial)
	{
	    //- break searching loop

	    break;
	}

	//- go to next math component

	pmc = MathComponentNext(pmc);
    }

    //- set result : previous index

    iResult = i - 1;

    //- return result

    return(iResult);
}
#endif


/// **************************************************************************
///
/// SHORT: HeccerAddressMechanismVariable()
///
/// ARGS.:
///
///	pheccer.......: a heccer.
///	iIntermediary.: index of mechanism in the intermediary.
///	pcType........: name of requested variable.
///
/// RTN..: void *
///
///	pointer to the requested field, NULL for failure.
///
/// DESCR: Find the simulation sequence of a given variable.
///
/// **************************************************************************

void *
HeccerAddressMechanismVariable
(struct Heccer *pheccer, int iIndex, char *pcType)
{
    //- set default result : not found

    void *pvResult = NULL;

    //- lookup the field operand, we first search for mat entries

    //! negative offset for now

    struct field_2_operator
    {
	char *pcType;
	int iOperand;
	int iOffset;
    };

    struct field_2_operator pF2P[] =
    {
	{	"Ca",		0,	0, },
	{	"spike",	0,	1, },
	{	"state_h",	0,	0, },
	{	"state_m",	-1,	0, },
	{	"state_n",	0,	0, },
	{	NULL,		INT_MAX,	INT_MAX, },
    };

    int iField;

    for (iField = 0 ; pF2P[iField].pcType ; iField++)
    {
	if (strcasecmp(pcType, pF2P[iField].pcType) == 0)
	{
	    break;
	}
    }

    //- if mat entry found

    int iOperand = pF2P[iField].iOperand;

    if (iOperand != INT_MAX)
    {
	//- get mat number

	int iMat = pheccer->vm.piMC2Mat[iIndex].iMat;

	//- apply the operand

	iMat += iOperand;

	//- set result

	int iOffset = (double *)pheccer->vm.ppvMatsIndex[iMat] - (double *)pheccer->vm.pvMats;

	printf("mat number for intermediary mechanism %i is mat %i, starts at %i, offset is %i\n", iIndex, iMat, iOffset, pF2P[iField].iOffset);

	//! note that this is implicitly assumed to be a pointer to double.

	pvResult = &((double *)pheccer->vm.ppvMatsIndex[iMat])[pF2P[iField].iOffset];
    }

    //- else

    else
    {
	//- we try mop entries

	if (strcasecmp(pcType, "table_A_index") == 0)
	{
	    //- operators are two off

	    iOperand = -2;
	}
	else if (strcasecmp(pcType, "table_B_index") == 0)
	{
	    //- operators are one off

	    iOperand = -1;
	}

	if (iOperand != INT_MAX)
	{
	    //- get mop number

	    int iMop = pheccer->vm.piMC2Mop[iIndex];

	    //- apply the operand

	    iMop += iOperand;

	    //- set result

	    int iOffset = (int *)pheccer->vm.ppvMopsIndex[iMop] - (int *)pheccer->vm.pvMops;

	    printf("mop number for intermediary mechanism %i is mop %i, starts at %i, offset is %i\n", iIndex, iMop, iOffset, 0);

	    struct MopsSingleGateConcept *pmops = (struct MopsSingleGateConcept *)((int *)pheccer->vm.ppvMopsIndex[iMop]);

	    printf("table index is %i\n", pmops->iTableIndex);

	    //! normally the default for iTableIndex is -1, which is
	    //! returned as an error indicator if there is no table
	    //! associated with this gate.

	    pvResult = (int *)pmops->iTableIndex;
	}
    }

    //- return result

    return(pvResult);
}


/// **************************************************************************
///
/// SHORT: HeccerAddressSerial2Intermediary()
///
/// ARGS.:
///
///	pheccer...: a heccer.
///	iSerial...: identification number.
///	pcType....: name of requested variable.
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
(struct Heccer *pheccer, int iSerial, char *pcType)
{
    //- set default result: not found

    int iResult = -1;

    //- for compartment addressables

/*     if (strcmp(pcType, "Vm") == 0 */
/* 	|| strcmp(pcType, "inject") == 0 */
/* 	|| strcmp(pcType, "Im") == 0 */
/* 	|| strcmp(pcType, "Ileak") == 0) */
    if (strcasecmp(pcType, "Vm") == 0
	|| strcasecmp(pcType, "inject") == 0
	|| strcasecmp(pcType, "Im") == 0
	|| strcasecmp(pcType, "Ileak") == 0)
    {
	iResult = HeccerAddressCompartmentSerial2Intermediary(pheccer, iSerial, pcType);
    }
    else
    {
	iResult = HeccerAddressMechanismSerial2Intermediary(pheccer, iSerial, pcType);
    }

    //- return result

    return(iResult);
}
#endif


/// **************************************************************************
///
/// SHORT: HeccerAddressTableIndex()
///
/// ARGS.:
///
///	pheccer...: a heccer.
///	iSerial...: identification number.
///	pcType....: name of requested variable.
///
/// RTN..: int
///
///	index into table array, -1 for failure.
///
/// DESCR: Lookup the table index of the given serial.
///
///	The returned index is an address into ptgt->phtg.  See table.h
///	for more information.
///
/// **************************************************************************

int
HeccerAddressTableIndex
(struct Heccer *pheccer, int iSerial, char *pcType)
{
    //- set default result : not found

    int iResult = -1;

    //- do a regular lookup

    void *pvResult = HeccerAddressVariable(pheccer, iSerial, pcType);

    //t should be cleaner than this

    //- convert result to int

    iResult = (int)pvResult;

    //- return result

    return(iResult);
}


/// **************************************************************************
///
/// SHORT: HeccerAddressVariable()
///
/// ARGS.:
///
///	pheccer...: a heccer.
///	iSerial...: identification number.
///	pcType....: name of requested variable.
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

    //- if serial not within range

    if (iSerial < pheccer->inter.iSerialStart
	|| iSerial > pheccer->inter.iSerialEnd)
    {
	//- return failure

	return(NULL);
    }

    //- convert the serial to an intermediary index

    int iIntermediary = HeccerAddressSerial2Intermediary(pheccer, iSerial, pcType);

    if (iIntermediary != -1)
    {
	//- for compartment addressables

/* 	if (strcmp(pcType, "Vm") == 0 */
/* 	    || strcmp(pcType, "inject") == 0 */
/* 	    || strcmp(pcType, "Im") == 0 */
/* 	    || strcmp(pcType, "Ileak") == 0) */
	if (strcasecmp(pcType, "Vm") == 0
	    || strcasecmp(pcType, "inject") == 0
	    || strcasecmp(pcType, "Im") == 0
	    || strcasecmp(pcType, "Ileak") == 0)
	{
	    pvResult = HeccerAddressCompartmentVariable(pheccer, iIntermediary, pcType);
	}
	else
	{
	    pvResult = HeccerAddressMechanismVariable(pheccer, iIntermediary, pcType);
	}
    }
    else
    {
	//! this cannot be, internal error

	HeccerError
	    (pheccer,
	     NULL,
	     "trying to address something that should exist, but cannot find it (internal serial %i)",
	     iSerial);

	//- return error

	return(NULL);
    }

    //- return result

    return(pvResult);
}
#endif


