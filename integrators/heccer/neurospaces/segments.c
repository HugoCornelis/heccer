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


#include <neurospaces/pidinstack.h>
#include <neurospaces/treespacetraversal.h>

#include "heccer/compartment.h"
#include "heccer/intermediary.h"
#include "heccer/neurospaces/heccer.h"
#include "heccer/neurospaces/segments.h"
#include "heccer/service.h"


static int 
solver_segmentprocessor
(struct TreespaceTraversal *ptstr,
 void *pvUserdata)
{
    //- set default result : ok

    int iResult = TSTR_PROCESSOR_SUCCESS;

    //- get actual symbol

    struct symtab_HSolveListElement *phsle = TstrGetActual(ptstr);

    //- if segment

    if (InstanceOfSegment(phsle))
    {
	//- get pointer to intermediary

	struct Intermediary *pinter = (struct Intermediary *)pvUserdata;

	//- register current symbol

	int iSegment = pinter->iCompartments;

	//- register type

	pinter->pcomp[iSegment].mc.iType = MATH_TYPE_Compartment;

	//- register identification

	//! note: assumes pp define HECCER_SOURCE_NEUROSPACES

	pinter->pcomp[iSegment].mc.iSerial
	    = PidinStackToSerial(ptstr->ppist);

	//- register parameters

	pinter->pcomp[iSegment].dCm
	    = SymbolParameterResolveScaledValue(phsle, "CM", ptstr->ppist);

	pinter->pcomp[iSegment].dEm
	    = SymbolParameterResolveValue(phsle, "ELEAK", ptstr->ppist);

	pinter->pcomp[iSegment].dInitVm
	    = SymbolParameterResolveValue(phsle, "Vm_init", ptstr->ppist);

	pinter->pcomp[iSegment].dInject
	    = SymbolParameterResolveValue(phsle, "INJECT", ptstr->ppist);

	pinter->pcomp[iSegment].dRa
	    = SymbolParameterResolveScaledValue(phsle, "RA", ptstr->ppist);

	pinter->pcomp[iSegment].dRm
	    = SymbolParameterResolveScaledValue(phsle, "RM", ptstr->ppist);

	//- register serial of parent

	{
	    struct symtab_Parameters *pparParent
		= SymbolFindParameter(phsle, "SOMATOPETAL", ptstr->ppist);

	    struct PidinStack *ppistParent
		= ParameterResolveToPidinStack(pparParent, ptstr->ppist);

	    int iParent = PidinStackToSerial(ppistParent);

	    //t I can just subtract the cell's segment ID ?

	    pinter->pcomp[iSegment].iParent = iParent;
	}

	//- increment number of solved segments

	pinter->iCompartments++;
    }

    //- return result

    return(iResult);
}


static int cellsolver_getsegments(struct TranslationService *pts)
{
    //- allocate pidin stack pointing to root

    struct PidinStack *ppistRoot = pts->ptsd->ppistRoot;

    struct symtab_HSolveListElement *phsleRoot = pts->ptsd->phsleRoot;

    //- get model context to solve

    struct PidinStack *ppistModel
	= SymbolPrincipalSerial2Context(phsleRoot, ppistRoot, pts->ptsd->iModel);

    //- lookup symbol

    struct symtab_HSolveListElement *phsleModel
	= PidinStackLookupTopSymbol(ppistModel);

    int iSegments = SymbolCountSegments(phsleModel, ppistModel);

    int i;

    //- allocate intermediary for segments to solve

    struct Intermediary *pinter
	= (struct Intermediary *)calloc(1, sizeof(struct Intermediary));

    pinter->iCompartments = 0; //iSegments;

    pinter->pcomp
	= (struct Compartment *)calloc(iSegments, sizeof(struct Compartment));

    //- register solved segments in cell

    SymbolTraverseSegments
	(phsleModel, ppistModel, solver_segmentprocessor, NULL, pinter);

    //- link the segments together using the parent link

    //t probably also have to index the segments on serial ?

    return(0);
}


int HeccerNeurospacesSegments2Compartments(struct TranslationService *pts)
{
    //- set the service function pointer to cellsolver_getsegments()

    pts->segments_inspector = cellsolver_getsegments;

    //- return result

    return(1);
}


