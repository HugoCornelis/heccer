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

    if (instanceof_segment(phsle))
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

	//t check for error returns, abort traversal if necessary

	double dCm
	    = SymbolParameterResolveScaledValue(phsle, "CM", ptstr->ppist);

	if (dCm == FLT_MAX)
	{
	    iResult = TSTR_PROCESSOR_ABORT;
	}

	double dEm
	    = SymbolParameterResolveValue(phsle, "ELEAK", ptstr->ppist);

	if (dEm == FLT_MAX)
	{
	    iResult = TSTR_PROCESSOR_ABORT;
	}

	double dInitVm
	    = SymbolParameterResolveValue(phsle, "Vm_init", ptstr->ppist);

	if (dInitVm == FLT_MAX)
	{
	    iResult = TSTR_PROCESSOR_ABORT;
	}

	double dInject
	    = SymbolParameterResolveValue(phsle, "INJECT", ptstr->ppist);

	if (dInject == FLT_MAX)
	{
	    dInject = 0.0;
	}

	double dRa
	    = SymbolParameterResolveScaledValue(phsle, "RA", ptstr->ppist);

	if (dRa == FLT_MAX)
	{
	    iResult = TSTR_PROCESSOR_ABORT;
	}

	double dRm
	    = SymbolParameterResolveScaledValue(phsle, "RM", ptstr->ppist);

	if (dRm == FLT_MAX)
	{
	    iResult = TSTR_PROCESSOR_ABORT;
	}

	pinter->pcomp[iSegment].dCm = dCm;
	pinter->pcomp[iSegment].dEm = dEm;
	pinter->pcomp[iSegment].dInitVm = dInitVm;
	pinter->pcomp[iSegment].dInject = dInject;
	pinter->pcomp[iSegment].dRa = dRa;
	pinter->pcomp[iSegment].dRm = dRm;

	//- register serial of parent

	{
	    struct symtab_Parameters *pparParent
		= SymbolFindParameter(phsle, "PARENT", ptstr->ppist);

	    if (pparParent)
	    {
		//t I can just subtract the cell's segment ID ?

		struct PidinStack *ppistParent
		    = ParameterResolveToPidinStack(pparParent, ptstr->ppist);

		//! cannot give an error return, but anyway

		if (ppistParent)
		{
		    PidinStackLookupTopSymbol(ppistParent);

		    int iParent = PidinStackToSerial(ppistParent);

		    //t check for error

		    if (iParent != INT_MAX)
		    {
			pinter->pcomp[iSegment].iParent = iParent;
		    }
		    else
		    {
			//! parent does not exist

			iResult = TSTR_PROCESSOR_ABORT;
		    }
		}
		else
		{
		    iResult = TSTR_PROCESSOR_ABORT;
		}
	    }
	    else
	    {
		pinter->pcomp[iSegment].iParent = -1;
	    }
	}

	//- increment number of solved segments

	pinter->iCompartments++;
    }

    //- return result

    return(iResult);
}


static int cellsolver_getsegments(struct Heccer *pheccer, struct TranslationService *pts)
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

    struct Intermediary *pinter = &pheccer->inter;

    pinter->iCompartments = 0; //iSegments;

    pinter->pcomp
	= (struct Compartment *)calloc(iSegments, sizeof(struct Compartment));

    //- register solved segments in cell

    SymbolTraverseSegments
	(phsleModel, ppistModel, solver_segmentprocessor, NULL, pinter);

    //t link the segments together using the parent link

    //t probably also have to index the segments on serial ?

    //t produce a piC2m array: all zeros for now

    return(0);
}


int HeccerNeurospacesSegments2Compartments(struct TranslationService *pts)
{
    //- set the service function pointer to cellsolver_getsegments()

    pts->segments_inspector = cellsolver_getsegments;

    //- return result

    return(1);
}


