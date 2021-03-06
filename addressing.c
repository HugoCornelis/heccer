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
(struct simobj_Heccer *pheccer, int iSerial, char *pcType);
#endif

#ifdef HECCER_SOURCE_NEUROSPACES
static
int
HeccerAddressSerial2Intermediary
(struct simobj_Heccer *pheccer, int iIndex, char *pcType);

#endif


/// 
/// \arg pheccer a heccer.
/// \arg iSerial identification number.
/// \arg pcType name of requested variable.
/// \arg dValue new value for this variable.
/// 
/// \return char *
/// 
///	error code, NULL for success.
/// 
/// \brief Set a variable in a compiled model.
/// 

#ifdef HECCER_SOURCE_NEUROSPACES
char *
HeccerAddressableSet
(struct simobj_Heccer *pheccer, int iSerial, char *pcType, double dValue)
{
    //- set default result: success

    char *pcResult = NULL;

    //- find the addressable

    double *pd = HeccerAddressVariable(pheccer, iSerial, pcType);

    if (pd)
    {
	//- if this is a variable that needs conversion: synchan frequency

	if (0 == strcmp(pcType, "FREQUENCY"))
	{
	    //- convert the variable: normalize to time step

	    dValue = pheccer->dStep * dValue;
	}

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


/// 
/// \arg pheccer a heccer.
/// \arg iSerial identification number.
/// \arg pcType name of requested variable.
/// 
/// \return double *
/// 
///	address of the aggregator, NULL for failure.
/// 
/// \brief Get the address of an aggregator.
/// 

double *
HeccerAddressAggregator
(struct simobj_Heccer *pheccer, int iSerial, char *pcType)
{
    //- set default result: not found

    double *pdResult = NULL;

    //- process as an aggregator variable

    if (strncasecmp(pcType, "aggregator", strlen("aggregator")) == 0)
    {
	//- find the requested index

	int iIndex = -1;

	int iAssigned = sscanf(pcType, "aggregator[%i]", &iIndex);

	if (iAssigned == 1)
	{
	    if (iIndex < pheccer->vm.iAggregators)
	    {
		//- set result

		pdResult = &pheccer->vm.pdAggregators[iIndex];
	    }
	    else
	    {
		HeccerError
		    (pheccer,
		     "HeccerAddressAggregator()",
		     "aggregator index of %s is out of range (internal serial %i)",
		     pcType,
		     iSerial);
	    }
	}
	else
	{
	    HeccerError
		(pheccer,
		 "HeccerAddressAggregator()",
		 "invalid aggregator %s (internal serial %i)",
		 pcType,
		 iSerial);
	}
    }

    //- return resulting address if variable was found

    return(pdResult);
}


/// 
/// \arg pheccer a heccer.
/// \arg iIntermediary index of compartment in the intermediary.
/// \arg pcType name of requested variable.
/// 
/// \return double *
/// 
///	pointer to the requested field, NULL for failure.
/// 
/// \brief Find the simulation sequence of a given variable.
/// 

double *
HeccerAddressCompartmentVariable
(struct simobj_Heccer *pheccer, int iIntermediary, char *pcType)
{
    //- set default result : not found

    double *pdResult = NULL;

    //- for membrane potential

    if (strcasecmp(pcType, "Vm") == 0)
    {
	//- convert intermediary to schedule number

	int iSchedule = pheccer->indexers.md.piForward[iIntermediary];

	//- set result

	pdResult = &pheccer->vm.pdVms[iSchedule];
    }

    //- for injected current

    else if (strcasecmp(pcType, "inject") == 0)
    {
	//- convert intermediary to schedule number

	int iSchedule = pheccer->indexers.md.piForward[iIntermediary];

	//- get entry in mat array

	struct MatsCompartment *pmatsc
	    = (struct MatsCompartment *)pheccer->vm.ppdCMatsIndex[iSchedule];

	//- set result

	pdResult = &pmatsc->dInjected;
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

    return(pdResult);
}


/// 
/// \arg pheccer a heccer.
/// \arg iSerial identification number.
/// \arg pcType name of requested variable.
/// 
/// \return int
/// 
///	index into the intermediary, -1 for not found.
/// 
/// \brief Lookup the index of the given serial.
/// 

#ifdef HECCER_SOURCE_NEUROSPACES
static
int
HeccerAddressCompartmentSerial2Intermediary
(struct simobj_Heccer *pheccer, int iSerial, char *pcType)
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
	    /// \todo check if the field type is 'compatible' with the math component

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


/// 
/// \arg pheccer a heccer.
/// \arg iSerial identification number.
/// \arg pcType name of requested variable.
/// 
/// \return int
/// 
///	index into the intermediary, -1 for not found.
/// 
/// \brief Lookup the index of the given serial.
/// 

#ifdef HECCER_SOURCE_NEUROSPACES
static
int
HeccerAddressMechanismSerial2Intermediary
(struct simobj_Heccer *pheccer, int iSerial, char *pcType)
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


/// 
/// \arg pheccer a heccer.
/// \arg iIntermediary index of mechanism in the intermediary.
/// \arg pcType name of requested variable.
/// 
/// \return double *
/// 
///	pointer to the requested field, NULL for failure.
/// 
/// \brief Find the simulation sequence of a given variable.
/// 

double *
HeccerAddressMechanismVariable
(struct simobj_Heccer *pheccer, int iIndex, char *pcType)
{
    //- set default result : not found

    double *pdResult = NULL;

    //- lookup the field operand, we first search for mat entries

    /// \note negative offset for now

    struct field_2_operator
    {
	char *pcType;
	int iOperand;
	int iOffset;
    };

    struct field_2_operator pF2P[] =
    {
	{	"Ca",		0,	0, }, // first operation, first mat entry
	{	"FREQUENCY",	0,	3, }, // first operation, fourth mat entry
	{	"synapses",	0,	4, }, // first operation, fifth mat entry
	{	"Gsyn",		1,	0, }, // after springmass, first mat entry
	{	"Isyn",		1,	1, }, // after two gates, second mat entry
	{	"activation",	0,	1, }, // first operation, second mat entry
	{	"conductance",	2,	0, }, // after two gates, first mat entry
	{	"current",	2,	1, }, // after two gates, second mat entry
	{	"next_event",	0,	0, }, // first operation, first mat entry
	{	"spike",	0,	1, }, // first operation, second mat entry
	{	"state_h",	1,	0, }, // second gate, first mat entry
	{	"state_m",	0,	0, }, // first gate, first mat entry
	{	"state_n",	0,	0, }, // first gate, first mat entry
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

	//! a single mechanism can give rise to multiple mat entries,
	//! so the following two steps:

	//- apply the operand, takes us to the correct mat entry

	iMat += iOperand;

	//- apply offset, takes us to the correct subentry of this mat entry

	int iMatIndex = pheccer->vm.ppdMatsIndex[iMat] - pheccer->vm.pdMats;

/* 	printf("mat number for intermediary mechanism %i is mat %i, mat index %i, offset is %i\n", iIndex, iMat, iMatIndex, pF2P[iField].iOffset); */

	//- set result: pointer to double

	pdResult = &pheccer->vm.ppdMatsIndex[iMat][pF2P[iField].iOffset];
    }

    //- else we try mop entries

    else
    {
	//- first table index

	if (strcasecmp(pcType, "table_A_index") == 0)
	{
	    //- operators are two off

	    iOperand = 2;

	    //- get mop number

	    int iMop = pheccer->vm.piMC2Mop[iIndex];

	    //- apply the operand

	    iMop += iOperand;

	    //- set result

/* 	    int iOffset = (int *)pheccer->vm.ppvMopsIndex[iMop] - (int *)pheccer->vm.pvMops; */

/* 	    printf("mop number for intermediary mechanism %i is mop %i, starts at %i, offset is %i\n", iIndex, iMop, iOffset, 0); */

	    struct MopsSingleGateConcept *pmops = (struct MopsSingleGateConcept *)((int *)pheccer->vm.ppvMopsIndex[iMop]);

	    // \note normally the default for iTableIndex is -1, which
	    // is returned as an error indicator if there is no table
	    // associated with this gate.

	    pdResult = (double *)pmops->iTableIndex;
	}

	//- second table index

	else if (strcasecmp(pcType, "table_B_index") == 0)
	{
	    //- operators are three off

	    iOperand = 3;

	    //- get mop number

	    int iMop = pheccer->vm.piMC2Mop[iIndex];

	    //- apply the operand

	    iMop += iOperand;

	    //- set result

/* 	    int iOffset = (int *)pheccer->vm.ppvMopsIndex[iMop] - (int *)pheccer->vm.pvMops; */

/* 	    printf("mop number for intermediary mechanism %i is mop %i, starts at %i, offset is %i\n", iIndex, iMop, iOffset, 0); */

	    struct MopsSingleGateConcept *pmops = (struct MopsSingleGateConcept *)((int *)pheccer->vm.ppvMopsIndex[iMop]);

	    // \note normally the default for iTableIndex is -1, which
	    // is returned as an error indicator if there is no table
	    // associated with this gate.

	    pdResult = (double *)pmops->iTableIndex;
	}

	//- post-synaptic targets in the event queuer matrix

	else if (strcasecmp(pcType, "postsyn_targets") == 0)
	{
/* 	    //- operators are one off */

/* 	    iOperand = -1; */

	    //- get mop number

	    int iMop = pheccer->vm.piMC2Mop[iIndex];

/* 	    //- apply the operand */

/* 	    iMop += iOperand; */

	    //- set result

/* 	    int iOffset = (int *)pheccer->vm.ppvMopsIndex[iMop] - (int *)pheccer->vm.pvMops; */

/* 	    printf("mop number for intermediary mechanism %i is mop %i, starts at %i, offset is %i\n", iIndex, iMop, iOffset, 0); */

/* 	    struct MopsSpringMass *pmops = (struct MopsSpringMass *)((int *)pheccer->vm.ppvMopsIndex[iMop]); */

/* 	    pdResult = (double *)&pmops->iDiscreteTarget; */

     0;
	    struct MopsEventGenerate *pmops = (struct MopsEventGenerate *)((int *)pheccer->vm.ppvMopsIndex[iMop]);

	    pdResult = (double *)&pmops->iSource2Targets;
	}
	else if (strcasecmp(pcType, "presyn_targets") == 0)
	{
	    //- operators are three off

	    iOperand = -3;

	    //- get mop number

	    int iMop = pheccer->vm.piMC2Mop[iIndex];

	    //- apply the operand

	    iMop += iOperand;

	    //- set result

/* 	    int iOffset = (int *)pheccer->vm.ppvMopsIndex[iMop] - (int *)pheccer->vm.pvMops; */

/* 	    printf("mop number for intermediary mechanism %i is mop %i, starts at %i, offset is %i\n", iIndex, iMop, iOffset, 0); */

/* 	    struct MopsSpringMass *pmops = (struct MopsSpringMass *)((int *)pheccer->vm.ppvMopsIndex[iMop]); */

/* 	    pdResult = (double *)&pmops->iDiscreteTarget; */

     0;
	    struct MopsSpringMass *pmops = (struct MopsSpringMass *)((int *)pheccer->vm.ppvMopsIndex[iMop]);

	    pdResult = (double *)&pmops->iDiscreteTarget;
	}
    }

    //- return result

    return(pdResult);
}


/// 
/// \arg pheccer a heccer.
/// \arg iSerial identification number.
/// \arg pcType name of requested variable.
/// 
/// \return int
/// 
///	index into the intermediary, -1 for not found.
/// 
/// \brief Lookup the index of the given serial.
///
/// \details 
/// 
///	Note that depending on the field, you get an index into
///	mechanisms or an index into the compartments.
/// 

#ifdef HECCER_SOURCE_NEUROSPACES
static
int
HeccerAddressSerial2Intermediary
(struct simobj_Heccer *pheccer, int iSerial, char *pcType)
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


/// 
/// \arg pheccer a heccer.
/// \arg iSerial identification number.
/// \arg pcType name of requested variable.
/// 
/// \return int
/// 
///	index into table array, -1 for failure.
/// 
/// \brief Lookup the table index of the given serial.
///
/// \details 
/// 
///	The returned index is an address into pheccer->tgt.phtg.  See
///	table.h for more information.
/// 

int
HeccerAddressTableIndex
(struct simobj_Heccer *pheccer, int iSerial, char *pcType)
{
    //- set default result : not found

    int iResult = -1;

    //- do a regular lookup

    void *pvResult = HeccerAddressVariable(pheccer, iSerial, pcType);

    /// \todo should be cleaner than this

    //- convert result to int

    iResult = (int)pvResult;

    //- return result

    return(iResult);
}


/// 
/// \arg pheccer a heccer.
/// \arg iSerial identification number.
/// \arg pcType name of requested variable.
/// 
/// \return double *
/// 
///	pointer to the requested field, NULL for failure.
/// 
/// \brief Find the simulation sequence of a given variable.
///
/// \details 
/// 
///	In all cases, as of the moment of writing, the pointer is a
///	pointer to a double.
/// 

double *
HeccerAddressVariable
(struct simobj_Heccer *pheccer, int iSerial, char *pcType)
#ifdef HECCER_SOURCE_NEUROSPACES
{
    //- set default result : not found

    double *pdResult = NULL;

    if (pheccer->iErrorCount)
    {
	return(NULL);
    }

    //- convert serial to heccer space

    iSerial = ADDRESSING_NEUROSPACES_2_HECCER(iSerial);

    //- if this is the serial of the model itself

    if (iSerial == pheccer->inter.iSerialStart)
    {
	//- address as an aggregator

	pdResult = HeccerAddressAggregator(pheccer, iSerial, pcType);

	return(pdResult);
    }

    //- if serial not within range

    if (iSerial < pheccer->inter.iSerialStart
	|| iSerial > pheccer->inter.iSerialEnd)
    {
	//- return failure

	return(NULL);
    }

    //- convert the serial to an intermediary index

    int iIntermediary = HeccerAddressSerial2Intermediary(pheccer, iSerial, pcType);

    //- if we have math components

    if (pheccer->inter.pmca)
    {
	//- based on the low-level typing we translate some of the
	//- variable names for reasons of consistency towards the user.

	// \note both 'Isyn' and 'current' can be used by the user.

	int iMops = pheccer->vm.piMC2Mop[iIntermediary];

	struct MopsInitializeChannel *pmops
	    = (struct MopsInitializeChannel *)pheccer->vm.ppvMopsIndex[iMops];

	if (0 == strcasecmp(pcType, "current")
	    && (pmops->iOperator == HECCER_MOP_INITIALIZESYNCHANNEL
		|| pmops->iOperator == HECCER_MOP_INITIALIZESYNCHANNELEREV))
	{
	    pcType = "Isyn";
	}
	else if (0 == strcasecmp(pcType, "conductance")
		 && (pmops->iOperator == HECCER_MOP_INITIALIZESYNCHANNEL
		     || pmops->iOperator == HECCER_MOP_INITIALIZESYNCHANNELEREV))
	{
	    pcType = "Gsyn";
	}
    }

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
	    pdResult = HeccerAddressCompartmentVariable(pheccer, iIntermediary, pcType);
	}
	else
	{
	    pdResult = HeccerAddressMechanismVariable(pheccer, iIntermediary, pcType);
	}
    }
    else
    {
	/// \note this cannot be, internal error

	HeccerError
	    (pheccer,
	     "HeccerAddressVariable()",
	     "trying to address something that should exist, but cannot find it (internal serial %i)",
	     iSerial);

	//- return error

	return(NULL);
    }

    //- return result

    return(pdResult);
}
#else
{
    return(NULL);
}
#endif


