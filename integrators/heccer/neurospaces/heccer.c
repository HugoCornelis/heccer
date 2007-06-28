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

#include "heccer/addressing.h"
#include "heccer/heccer.h"
#include "heccer/neurospaces/segments.h"
#include "heccer/neurospaces/heccer.h"


int HeccerConstruct(struct Heccer *pheccer, void *pvNeurospaces, char *pcModel)
{
    //- the service core is neurospaces

    struct Neurospaces *pneuro = (struct Neurospaces *)pvNeurospaces;

    //- set default result : ok

    int iResult = 1;

    //- lookup the model

    struct PidinStack *ppistModel = PidinStackParse(pcModel);

    if (!ppistModel)
    {
	fprintf(stderr, "HeccerConstruct: cannot parse model name %s\n", pcModel);

	return(FALSE);
    }

    //- allocate the translation service structures

    struct TranslationServiceData *ptsd
	= (struct TranslationServiceData *)calloc(1, sizeof(struct TranslationServiceData));

    struct TranslationService *pts
	= (struct TranslationService *)calloc(1, sizeof(struct TranslationService));

    pts->ptsd = ptsd;

    pts->ptsd->pneuro = pneuro;

    //- allocate pidin stack pointing to root

    struct PidinStack *ppistRoot = PidinStackCalloc();

    if (!ppistRoot)
    {
	fprintf(stderr, "HeccerConstruct: cannot allocate a root context for %s\n", pcModel);

	return(FALSE);
    }

    PidinStackSetRooted(ppistRoot);

    //! gosh, I had to do the same hack when integrating neurospaces
    //! with genesis2/hsolve.

    struct ParserContext *pacRoot = pneuro->pacRootContext;

    struct ImportedFile *pifRoot
	= ParserContextGetImportedFile(pacRoot);

    //! depending on how the linking is done, there can be multiple
    //! instances of neurospaces around.  The following is a hack to
    //! enforce the singleton (a bit)

/*     fprintf(stdout, "HeccerConstruct(): root import is %p\n", ImportedFileGetRootImport()); */

    ImportedFileSetRootImport(pifRoot);

/*     fprintf(stdout, "HeccerConstruct(): root import is %p\n", ImportedFileGetRootImport()); */

    //- update caches

    struct symtab_HSolveListElement *phsleRoot
	= PidinStackLookupTopSymbol(ppistRoot);

    ptsd->ppistRoot = ppistRoot;

    ptsd->phsleRoot = phsleRoot;

    //- set model

    struct symtab_HSolveListElement *phsleModel
	= PidinStackLookupTopSymbol(ppistModel);

    ptsd->iModel = PidinStackToSerial(ppistModel);

    if (ptsd->iModel == INT_MAX)
    {
	//! don't care about memory leak right now, consider this
	//! right now as a fatal crash

	fprintf(stderr, "HeccerConstruct: cannot find model %s\n", pcModel);

	return(FALSE);
    }

    if (!HeccerNeurospacesSegments2Compartments(pts))
    {
	//! don't care about memory leak right now, consider this
	//! right now as a fatal crash

	fprintf(stderr, "HeccerConstruct: compartment initialization failed for %s\n", pcModel);

	return(FALSE);
    }

    if (!HeccerNeurospacesMechanisms2MathComponents(pts))
    {
	//! don't care about memory leak right now, consider this
	//! right now as a fatal crash

	fprintf(stderr, "HeccerConstruct: mechanism initialization failed for %s\n", pcModel);

	return(FALSE);
    }

    //- set service structures

    pheccer->pts = pts;

    //- initialize the range of the intermediary, for the addressing
    //- function

    //! note: closed interval, would probably be better to use a halve
    //! open interval.

    pheccer->inter.iSerialStart = ADDRESSING_NEUROSPACES_2_HECCER(ptsd->iModel);

    pheccer->inter.iSerialEnd = ADDRESSING_NEUROSPACES_2_HECCER(ptsd->iModel + SymbolGetPrincipalNumOfSuccessors(phsleModel));

    //- free allocated data

    PidinStackFree(ppistModel);

    //- return result

    return(iResult);
}


