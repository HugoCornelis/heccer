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


#include <neurospaces/importedfile.h>
#include <neurospaces/parsersupport.h>
#include <neurospaces/pidinstack.h>

#include "heccer/heccer.h"
#include "heccer/neurospaces/segments.h"
#include "heccer/neurospaces/heccer.h"


struct Heccer *HeccerConstruct(void *pvNeurospaces, char *pcModel)
{
    struct Neurospaces *pneuro = (struct Neurospaces *)pvNeurospaces;

    //- set default result : failure

    struct Heccer *pheccerResult = NULL;

    //- lookup the model

    struct PidinStack *ppistModel = PidinStackParse(pcModel);

    if (!ppistModel)
    {
	return(NULL);
    }

    //- allocate the service structures

    struct TranslationServiceData *ptsd
	= (struct TranslationServiceData *)calloc(1, sizeof(struct TranslationServiceData));

    struct TranslationService *pts
	= (struct TranslationService *)calloc(1, sizeof(struct TranslationService));

    pts->ptsd = ptsd;

    //- allocate pidin stack pointing to root

    struct PidinStack *ppistRoot = PidinStackCalloc();

    if (!ppistRoot)
    {
	return(0);
    }

    PidinStackSetRooted(ppistRoot);

    //! gosh, I had to do the same hack when integrating neurospaces
    //! with genesis2/hsolve.

    struct ParserContext *pacRoot = pneuro->pacRootContext;

    struct ImportedFile *pifRoot
	= ParserContextGetImportedFile(pacRoot);

    ImportedFileSetRootImport(pifRoot);

    //- update caches

    struct symtab_HSolveListElement *phsleRoot
	= PidinStackLookupTopSymbol(ppistRoot);

    ptsd->ppistRoot = ppistRoot;

    ptsd->phsleRoot = phsleRoot;

    //- set model

    PidinStackLookupTopSymbol(ppistModel);

    ptsd->iModel = PidinStackToSerial(ppistModel);

    if (!HeccerNeurospacesSegments2Compartments(pts))
    {
	//! don't care about memory leak right now, consider this
	//! right now as a fatal crash

	return(NULL);
    }

    if (!HeccerNeurospacesMechanisms2MathComponents(pts))
    {
	//! don't care about memory leak right now, consider this
	//! right now as a fatal crash

	return(NULL);
    }

    //- allocate the heccer for this service

    //! so the service for heccer is an encoding for the service to
    //! the user, this is the way it should be I guess.

    pheccerResult = HeccerNew(pts);

    //t compile1 constructs the intermediary ?

    //- free allocated data

    PidinStackFree(ppistModel);

    //- return result

    return(pheccerResult);
}


