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


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "heccer/heccer.h"
#include "heccer/serialization.h"


static
int
HeccerDeserializeCompartments
(struct Heccer *pheccer, FILE *pfile);

static
int
HeccerDeserializeMain
(struct Heccer *pheccer, FILE *pfile);

static
int
HeccerDeserializeMechanisms
(struct Heccer *pheccer, FILE *pfile);

static
int
HeccerSerializeCompartments
(struct Heccer *pheccer, FILE *pfile);

static
int
HeccerSerializeMain
(struct Heccer *pheccer, FILE *pfile);

static
int
HeccerSerializeMechanisms
(struct Heccer *pheccer, FILE *pfile);


/// 
/// \arg pheccer a heccer.
/// \arg pfile file pointer.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Deserialize this heccer from the given stream.
/// 

struct Heccer *
HeccerDeserialize(FILE *pfile)
{
    //- set default result: failure

    struct Heccer *pheccerResult = NULL;

/*     //- read the serialization version ID */

/*     char pcSerializationVersion[strlen(HECCER_SERIALIZATION_VERSION) + 1]; */

/*     fread */
/* 	(pcSerializationVersion, */
/* 	 sizeof(char), */
/* 	 strlen(HECCER_SERIALIZATION_VERSION) + 1, */
/* 	 pfile); */

/*     if (0 != strcmp(pcSerializationVersion, HECCER_SERIALIZATION_VERSION)) */
/*     { */
/* 	return(NULL); */
/*     } */

    //- construct a default heccer

    pheccerResult = HeccerNew(NULL, NULL, NULL, NULL);

    if (pheccerResult)
    {
	//- deserialize main struct

	if (HeccerDeserializeMain(pheccerResult, pfile))
	{
	    //- deserialize compartments

	    if (HeccerDeserializeCompartments(pheccerResult, pfile))
	    {
		//- deserialize mechanisms

		if (HeccerDeserializeMechanisms(pheccerResult, pfile))
		{
		    //- link mechanisms

		    if (HeccerMechanismIndex2Pointer(pheccerResult))
		    {
/* 			//- deserialize aggregators */

/* 			if (HeccerDeserializeAggregators(pheccerResult, pfile)) */
/* 			{ */
/* 			} */
/* 			else */
/* 			{ */
/* 			    pheccerResult = NULL; */
/* 			} */
		    }
		    else
		    {
			pheccerResult = NULL;
		    }
		}
		else
		{
		    pheccerResult = NULL;
		}
	    }
	    else
	    {
		pheccerResult = NULL;
	    }
	}
    }

    //- return result

    return(pheccerResult);
}


/// 
/// \arg pheccer a heccer.
/// \arg pfile file pointer.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Deserialize the compartments of this heccer from the given stream.
/// 

static
int
HeccerDeserializeCompartments
(struct Heccer *pheccer, FILE *pfile)
{
    //- set default result: ok

    int iResult = 1;

    //- deserialize structure

    iResult = iResult && HeccerDeserializeCompartmentStructure(pheccer, pfile);

    //- deserialize state

    iResult = iResult && HeccerDeserializeCompartmentState(pheccer, pfile);

    //- return result

    return(iResult);
}

/// 
/// \arg pheccer a heccer.
/// \arg pfile file pointer.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Deserialize the compartment state of this heccer from the
/// given stream.
///
/// \details If state arrays were already allocated, their contents
/// will be overriden.  In that case an additional check for same
/// sizes is done.
/// 

int
HeccerDeserializeCompartmentState
(struct Heccer *pheccer, FILE *pfile)
{
    //- set default result: ok

    int iResult = 1;

    //- read data: axres

    int iAxres;

    if (fread(&iAxres, sizeof(iAxres), 1, pfile) != 1)
    {
	return(0);
    }

    if (pheccer->vm.pdAxres
	&& pheccer->vm.iAxres != iAxres)
    {
	return(0);
    }

    pheccer->vm.iAxres = iAxres;

    if (!pheccer->vm.pdAxres)
    {
	pheccer->vm.pdAxres = (double *)calloc(pheccer->vm.iAxres, sizeof(double));
    }

    if (!pheccer->vm.pdAxres)
    {
	return(0);
    }

    if (fread(pheccer->vm.pdAxres, sizeof(pheccer->vm.pdAxres[0]), pheccer->vm.iAxres, pfile) != pheccer->vm.iAxres)
    {
	return(0);
    }

    //- read data: results

    int iResults;

    if (fread(&iResults, sizeof(iResults), 1, pfile) != 1)
    {
	return(0);
    }

    if (pheccer->vm.pdResults
	&& pheccer->vm.iResults != iResults)
    {
	return(0);
    }

    pheccer->vm.iResults = iResults;

    if (!pheccer->vm.pdResults)
    {
	pheccer->vm.pdResults = (double *)calloc(pheccer->vm.iResults, sizeof(double));
    }

    if (!pheccer->vm.pdResults)
    {
	return(0);
    }

    if (fread(pheccer->vm.pdResults, sizeof(pheccer->vm.pdResults[0]), pheccer->vm.iResults, pfile) != pheccer->vm.iResults)
    {
	return(0);
    }

    //- read data: Vm

    int iVms;

    if (fread(&iVms, sizeof(iVms), 1, pfile) != 1)
    {
	return(0);
    }

    if (pheccer->vm.pdVms
	&& pheccer->vm.iVms != iVms)
    {
	return(0);
    }

    pheccer->vm.iVms = iVms;

    if (!pheccer->vm.pdVms)
    {
	pheccer->vm.pdVms = (double *)calloc(pheccer->vm.iVms, sizeof(double));
    }

    if (!pheccer->vm.pdVms)
    {
	return(0);
    }

    if (fread(pheccer->vm.pdVms, sizeof(pheccer->vm.pdVms[0]), pheccer->vm.iVms, pfile) != pheccer->vm.iVms)
    {
	return(0);
    }

    //- return result

    return(iResult);
}


/// 
/// \arg pheccer a heccer.
/// \arg pfile file pointer.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Deserialize the compartment structure of this heccer from
/// the given stream.
/// 

int
HeccerDeserializeCompartmentStructure
(struct Heccer *pheccer, FILE *pfile)
{
    //- set default result: ok

    int iResult = 1;

    //- read number of compartments

    if (fread(&pheccer->vm.iCompartments, sizeof(pheccer->vm.iCompartments), 1, pfile) != 1)
    {
	return(0);
    }

    //- read compartment operations

    if (fread(&pheccer->vm.iCops, sizeof(pheccer->vm.iCops), 1, pfile) != 1)
    {
	return(0);
    }

    pheccer->vm.piCops = (int *)calloc(pheccer->vm.iCops, sizeof(int));

    if (!pheccer->vm.piCops)
    {
	return(0);
    }

    if (fread(pheccer->vm.piCops, sizeof(pheccer->vm.piCops[0]), pheccer->vm.iCops, pfile) != pheccer->vm.iCops)
    {
	return(0);
    }

    //- return result

    return(iResult);
}


/// 
/// \arg pfile file pointer.
/// 
/// \return struct Heccer *
/// 
///	a heccer, NULL for failure.
/// 
/// \brief Deserialize a heccer from the given filename.
/// 

struct Heccer *
HeccerDeserializeFromFilename(char *pcFilename)
{
    //- set default result: failure

    struct Heccer *pheccerResult = NULL;

    //- open file

    FILE *pfile = fopen(pcFilename, "r");

    if (!pfile)
    {
	return(NULL);
    }

    //- deserialize heccer from opened file

    pheccerResult = HeccerDeserialize(pfile);

    //- return result

    return(pheccerResult);
}


/// 
/// \arg pheccer a heccer.
/// \arg pfile file pointer.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Deserialize the main struct of this heccer from the given
/// stream.
/// 

static
int
HeccerDeserializeMain
(struct Heccer *pheccer, FILE *pfile)
{
    //- set default result: ok

    int iResult = 1;

    //- read main structure

    if (fread(pheccer, sizeof(*pheccer), 1, pfile) != 1)
    {
	return(0);
    }

    //- process the substructures to void them

    memset(&pheccer->inter, 0, sizeof(pheccer->inter));

    memset(&pheccer->indexers, 0, sizeof(pheccer->indexers));

/*     memset(&pheccer->tgt, 0, sizeof(pheccer->tgt)); */

    memset(&pheccer->tsmt, 0, sizeof(pheccer->tsmt));

    memset(&pheccer->vm, 0, sizeof(pheccer->vm));

    //- loop over all tables

    struct TabulatedGateTable *ptgt = &pheccer->tgt;

    int i;

    for (i = 0 ; i < ptgt->iTabulatedGateCount ; i++)
    {
	//- zero out parameters pointer

	ptgt->phtg[i].pvParameters = NULL;

	//- dump table values

	iResult = iResult && HeccerTableValuesDeserialize(&ptgt->phtg[i], pfile);
    }

    //- return result

    return(iResult);
}


/// 
/// \arg pfile file pointer.
/// 
/// \return long
/// 
///	file position pointer.
/// 
/// \brief Determine the file position pointer/offset for the given
/// stream.
///
/// \note The only reason to have this function here is to make its
/// declaration visible to the debugger.
/// 

long HeccerFilePos(FILE *pfile);

long HeccerFilePos(FILE *pfile)
{
    return ftell(pfile);
}


/// 
/// \arg pheccer a heccer.
/// \arg pfile file pointer.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Deserialize the mechanisms of this heccer from the given stream.
/// 

static
int
HeccerDeserializeMechanisms
(struct Heccer *pheccer, FILE *pfile)
{
    //- set default result: ok

    int iResult = 1;

    //- deserialize structure

    iResult = iResult && HeccerDeserializeMechanismStructure(pheccer, pfile);

    //- deserialize state

    iResult = iResult && HeccerDeserializeMechanismState(pheccer, pfile);

    //- return result

    return(iResult);
}


/// 
/// \arg pheccer a heccer.
/// \arg pfile file pointer.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Deserialize the mechanism state of this heccer from the
/// given stream.
/// 

int
HeccerDeserializeMechanismState
(struct Heccer *pheccer, FILE *pfile)
{
    //- set default result: ok

    int iResult = 1;

    /// mechanism addressables

    int iMats;

    if (fread(&iMats, sizeof(iMats), 1, pfile) != 1)
    {
	return(0);
    }

    if (pheccer->vm.pdMats
	&& pheccer->vm.iMats != iMats)
    {
	return(0);
    }

    if (!pheccer->vm.pdMats)
    {
	pheccer->vm.pdMats = (double *)calloc(pheccer->vm.iMats, 1);
    }

    if (!pheccer->vm.pdMats)
    {
	return(0);
    }

    pheccer->vm.iMats = iMats;

    if (fread(pheccer->vm.pdMats, 1, pheccer->vm.iMats, pfile) != pheccer->vm.iMats)
    {
	return(0);
    }

    //- return result

    return(iResult);
}


/// 
/// \arg pheccer a heccer.
/// \arg pfile file pointer.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Deserialize the mechanism structure of this heccer from the
/// given stream.
/// 

int
HeccerDeserializeMechanismStructure
(struct Heccer *pheccer, FILE *pfile)
{
    //- set default result: ok

    int iResult = 1;

    //- read number of math components

    if (fread(&pheccer->vm.iMathComponents, sizeof(pheccer->vm.iMathComponents), 1, pfile) != 1)
    {
	return(0);
    }

    /// math component number to mat number convertor

    /// \note note that this one does not index compartments, only the mechanism math components.

    if (pheccer->vm.iMathComponents)
    {
	pheccer->vm.piMC2Mat = (uMC2Mat *)calloc(pheccer->vm.iMathComponents + 1, sizeof(pheccer->vm.piMC2Mat[0]));

	if (!pheccer->vm.piMC2Mat)
	{
	    return(0);
	}

	if (fread(pheccer->vm.piMC2Mat, sizeof(pheccer->vm.piMC2Mat[0]), pheccer->vm.iMathComponents + 1, pfile) != pheccer->vm.iMathComponents + 1)
	{
	    return(0);
	}
    }

    /// math component number to mop number convertor

    if (pheccer->vm.iMathComponents)
    {
	pheccer->vm.piMC2Mop = (int *)calloc(pheccer->vm.iMathComponents + 1, sizeof(pheccer->vm.piMC2Mop[0]));

	if (!pheccer->vm.piMC2Mop)
	{
	    return(0);
	}

	if (fread(pheccer->vm.piMC2Mop, sizeof(pheccer->vm.piMC2Mop[0]), pheccer->vm.iMathComponents + 1, pfile) != pheccer->vm.iMathComponents + 1)
	{
	    return(0);
	}
    }

    /// mechanism operations

    if (fread(&pheccer->vm.iMops, sizeof(pheccer->vm.iMops), 1, pfile) != 1)
    {
	return(0);
    }

    pheccer->vm.pvMops = (int *)calloc(pheccer->vm.iMops, 1);

    if (!pheccer->vm.pvMops)
    {
	return(0);
    }

    if (fread(pheccer->vm.pvMops, 1, pheccer->vm.iMops, pfile) != pheccer->vm.iMops)
    {
	return(0);
    }

    /// indexing from mops or mats number towards one of the above

    pheccer->vm.ppdCMatsIndex = (double **)calloc(pheccer->vm.iCompartments + 1, sizeof(double *));

    if (!pheccer->vm.ppdCMatsIndex)
    {
	return(0);
    }

    if (fread(pheccer->vm.ppdCMatsIndex, sizeof(pheccer->vm.ppdCMatsIndex[0]), pheccer->vm.iCompartments + 1, pfile) != pheccer->vm.iCompartments + 1)
    {
	return(0);
    }


    if (fread(&pheccer->vm.iMopNumber, sizeof(pheccer->vm.iMopNumber), 1, pfile) != 1)
    {
	return(0);
    }

    pheccer->vm.ppvMopsIndex = (void **)calloc(pheccer->vm.iMopNumber + 1, sizeof(void *));

    if (!pheccer->vm.ppvMopsIndex)
    {
	return(0);
    }

    if (fread(pheccer->vm.ppvMopsIndex, sizeof(pheccer->vm.ppvMopsIndex[0]), pheccer->vm.iMopNumber + 1, pfile) != pheccer->vm.iMopNumber + 1)
    {
	return(0);
    }


    if (fread(&pheccer->vm.iMatNumber, sizeof(pheccer->vm.iMatNumber), 1, pfile) != 1)
    {
	return(0);
    }

    pheccer->vm.ppdMatsIndex = (double **)calloc(pheccer->vm.iMatNumber + 1, sizeof(double *));

    if (!pheccer->vm.ppdMatsIndex)
    {
	return(0);
    }

    if (fread(pheccer->vm.ppdMatsIndex, sizeof(pheccer->vm.ppdMatsIndex[0]), pheccer->vm.iMatNumber + 1, pfile) != pheccer->vm.iMatNumber + 1)
    {
	return(0);
    }

    //- return result

    return(iResult);
}


/// 
/// \arg pfile serialization stream.
/// 
/// \return int
/// 
///	See fclose().
/// 
/// \brief Close a serialization stream.
/// 

int
HeccerSerializationClose(FILE *pfile)
{
    return(fclose(pfile));
}


/// 
/// \arg pcFilename filename.
/// 
/// \return FILE *
/// 
///	serialization stream.
/// 
/// \brief Open a serialization stream for reading.
/// 

FILE *
HeccerSerializationOpenRead(char *pcFilename)
{
    //- set default result: open stream

    FILE *pfileResult = fopen(pcFilename, "r");

    //- read the serialization version ID

    char pcSerializationVersion[strlen(HECCER_SERIALIZATION_VERSION) + 1];

    size_t sItems
	= fread
	  (pcSerializationVersion,
	   sizeof(char),
	   strlen(HECCER_SERIALIZATION_VERSION) + 1,
	   pfileResult);

    if (sItems != strlen(HECCER_SERIALIZATION_VERSION) + 1)
    {
	fprintf(stderr, "HeccerSerializationOpenRead(): number of items read is different from number requested\n");

	fclose(pfileResult);

	return(NULL);
    }

    if (0 != strcmp(pcSerializationVersion, HECCER_SERIALIZATION_VERSION))
    {
	fprintf(stderr, "HeccerSerializationOpenRead(): wrong HECCER_SERIALIZATION_VERSION on input stream\n");

	fclose(pfileResult);

	return(NULL);
    }

    //- return result

    return(pfileResult);
}


/// 
/// \arg pcFilename filename.
/// 
/// \return FILE *
/// 
///	serialization stream.
/// 
/// \brief Open a serialization stream for writing.
/// 

FILE *
HeccerSerializationOpenWrite(char *pcFilename)
{
    //- set default result: open stream

    FILE *pfileResult = fopen(pcFilename, "w");

    //- write the serialization version ID

    fwrite
	(HECCER_SERIALIZATION_VERSION,
	 sizeof(char),
	 strlen(HECCER_SERIALIZATION_VERSION) + 1,
	 pfileResult);

    //- return result

    return(pfileResult);
}


/// 
/// \arg pheccer a heccer.
/// \arg pfile file pointer.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Serialize this heccer to the given stream.
/// 

int
HeccerSerialize
(struct Heccer *pheccer, FILE *pfile)
{
    //- set default result: ok

    int iResult = 1;

/*     //- write the serialization version ID */

/*     fwrite */
/* 	(HECCER_SERIALIZATION_VERSION, */
/* 	 sizeof(char), */
/* 	 strlen(HECCER_SERIALIZATION_VERSION) + 1, */
/* 	 pfile); */

    //- serialize main structure

    iResult = iResult && HeccerSerializeMain(pheccer, pfile);

    //- serialize compartments

    iResult = iResult && HeccerSerializeCompartments(pheccer, pfile);

    //- unlink mechanisms

    iResult = iResult && HeccerMechanismPointer2Index(pheccer);

    //- serialize mechanisms

    iResult = iResult && HeccerSerializeMechanisms(pheccer, pfile);

    //- return result

    return(iResult);
}


/// 
/// \arg pheccer a heccer.
/// \arg pfile file pointer.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Serialize the compartments of this heccer to the given stream.
/// 

static
int
HeccerSerializeCompartments
(struct Heccer *pheccer, FILE *pfile)
{
    //- set default result: ok

    int iResult = 1;

    //- serialize structure

    iResult = iResult && HeccerSerializeCompartmentStructure(pheccer, pfile);

    //- serialize state

    iResult = iResult && HeccerSerializeCompartmentState(pheccer, pfile);

    //- return result

    return(iResult);
}


/// 
/// \arg pheccer a heccer.
/// \arg pfile file pointer.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Serialize the compartment state of this heccer to the given
/// stream.
/// 

int
HeccerSerializeCompartmentState
(struct Heccer *pheccer, FILE *pfile)
{
    //- set default result: ok

    int iResult = 1;

    //- write data: axres

    if (fwrite(&pheccer->vm.iAxres, sizeof(pheccer->vm.iAxres), 1, pfile) != 1)
    {
	return(0);
    }

    if (fwrite(pheccer->vm.pdAxres, sizeof(pheccer->vm.pdAxres[0]), pheccer->vm.iAxres, pfile) != pheccer->vm.iAxres)
    {
	return(0);
    }

    //- write data: results

    if (fwrite(&pheccer->vm.iResults, sizeof(pheccer->vm.iResults), 1, pfile) != 1)
    {
	return(0);
    }

    if (fwrite(pheccer->vm.pdResults, sizeof(pheccer->vm.pdResults[0]), pheccer->vm.iResults, pfile) != pheccer->vm.iResults)
    {
	return(0);
    }

    //- write data: Vm

    if (fwrite(&pheccer->vm.iVms, sizeof(pheccer->vm.iVms), 1, pfile) != 1)
    {
	return(0);
    }

    if (fwrite(pheccer->vm.pdVms, sizeof(pheccer->vm.pdVms[0]), pheccer->vm.iVms, pfile) != pheccer->vm.iVms)
    {
	return(0);
    }

    //- return result

    return(iResult);
}


/// 
/// \arg pheccer a heccer.
/// \arg pfile file pointer.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Serialize the compartment structure of this heccer to the
/// given stream.
/// 

int
HeccerSerializeCompartmentStructure
(struct Heccer *pheccer, FILE *pfile)
{
    //- set default result: ok

    int iResult = 1;

    //- write number of compartments

    if (fwrite(&pheccer->vm.iCompartments, sizeof(pheccer->vm.iCompartments), 1, pfile) != 1)
    {
	return(0);
    }

    //- write compartment operations

    if (fwrite(&pheccer->vm.iCops, sizeof(pheccer->vm.iCops), 1, pfile) != 1)
    {
	return(0);
    }

    if (fwrite(pheccer->vm.piCops, sizeof(pheccer->vm.piCops[0]), pheccer->vm.iCops, pfile) != pheccer->vm.iCops)
    {
	return(0);
    }

    //- return result

    return(iResult);
}


/// 
/// \arg pheccer a heccer.
/// \arg pfile file pointer.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Serialize the main struct of this heccer to the given
/// stream.
/// 

static
int
HeccerSerializeMain
(struct Heccer *pheccer, FILE *pfile)
{
    //- set default result: ok

    int iResult = 1;

    //- write data: Vm

    if (fwrite(pheccer, sizeof(*pheccer), 1, pfile) != 1)
    {
	return(0);
    }

    //- loop over all tables

    struct TabulatedGateTable *ptgt = &pheccer->tgt;

    int i;

    for (i = 0 ; i < ptgt->iTabulatedGateCount ; i++)
    {
	//- zero out parameters pointer

	ptgt->phtg[i].pvParameters = NULL;

	//- dump table values

	iResult = iResult && HeccerTableValuesSerialize(&ptgt->phtg[i], pfile);
    }

    //- return result

    return(iResult);
}


/// 
/// \arg pheccer a heccer.
/// \arg pfile file pointer.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Serialize the mechanisms of this heccer from the given
/// stream.
/// 

static
int
HeccerSerializeMechanisms
(struct Heccer *pheccer, FILE *pfile)
{
    //- set default result: ok

    int iResult = 1;

    //- serialize structure

    iResult = iResult && HeccerSerializeMechanismStructure(pheccer, pfile);

    //- serialize state

    iResult = iResult && HeccerSerializeMechanismState(pheccer, pfile);

    //- return result

    return(iResult);
}


/// 
/// \arg pheccer a heccer.
/// \arg pfile file pointer.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Serialize the mechanism state of this heccer from the given
/// stream.
/// 

int
HeccerSerializeMechanismState
(struct Heccer *pheccer, FILE *pfile)
{
    //- set default result: ok

    int iResult = 1;

    /// mechanism addressables

    if (fwrite(&pheccer->vm.iMats, sizeof(pheccer->vm.iMats), 1, pfile) != 1)
    {
	return(0);
    }

    if (fwrite(pheccer->vm.pdMats, 1, pheccer->vm.iMats, pfile) != pheccer->vm.iMats)
    {
	return(0);
    }

    //- return result

    return(iResult);
}


/// 
/// \arg pheccer a heccer.
/// \arg pfile file pointer.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Serialize the mechanism structure of this heccer from the
/// given stream.
/// 

int
HeccerSerializeMechanismStructure
(struct Heccer *pheccer, FILE *pfile)
{
    //- set default result: ok

    int iResult = 1;

    //- write number of math components

    if (fwrite(&pheccer->vm.iMathComponents, sizeof(pheccer->vm.iMathComponents), 1, pfile) != 1)
    {
	return(0);
    }

    /// math component number to mat number convertor

    /// \note note that this one does not index compartments, only the mechanism math components.

    if (pheccer->vm.iMathComponents)
    {
	if (fwrite(pheccer->vm.piMC2Mat, sizeof(pheccer->vm.piMC2Mat[0]), pheccer->vm.iMathComponents + 1, pfile) != pheccer->vm.iMathComponents + 1)
	{
	    return(0);
	}
    }

    /// math component number to mop number convertor

    if (pheccer->vm.iMathComponents)
    {
	if (fwrite(pheccer->vm.piMC2Mop, sizeof(pheccer->vm.piMC2Mop[0]), pheccer->vm.iMathComponents + 1, pfile) != pheccer->vm.iMathComponents + 1)
	{
	    return(0);
	}
    }

    /// mechanism operations

    if (fwrite(&pheccer->vm.iMops, sizeof(pheccer->vm.iMops), 1, pfile) != 1)
    {
	return(0);
    }

    if (fwrite(pheccer->vm.pvMops, 1, pheccer->vm.iMops, pfile) != pheccer->vm.iMops)
    {
	return(0);
    }

    /// indexing from mops or mats number towards one of the above

    if (fwrite(pheccer->vm.ppdCMatsIndex, sizeof(pheccer->vm.ppdCMatsIndex[0]), pheccer->vm.iCompartments + 1, pfile) != pheccer->vm.iCompartments + 1)
    {
	return(0);
    }


    if (fwrite(&pheccer->vm.iMopNumber, sizeof(pheccer->vm.iMopNumber), 1, pfile) != 1)
    {
	return(0);
    }

    if (fwrite(pheccer->vm.ppvMopsIndex, sizeof(pheccer->vm.ppvMopsIndex[0]), pheccer->vm.iMopNumber + 1, pfile) != pheccer->vm.iMopNumber + 1)
    {
	return(0);
    }


    if (fwrite(&pheccer->vm.iMatNumber, sizeof(pheccer->vm.iMatNumber), 1, pfile) != 1)
    {
	return(0);
    }

    if (fwrite(pheccer->vm.ppdMatsIndex, sizeof(pheccer->vm.ppdMatsIndex[0]), pheccer->vm.iMatNumber + 1, pfile) != pheccer->vm.iMatNumber + 1)
    {
	return(0);
    }

    //- return result

    return(iResult);
}


/// 
/// \arg pheccer a heccer.
/// \arg pfile file pointer.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Serialize the mechanisms of this heccer from the given
/// stream.
/// 

int
HeccerSerializeToFilename
(struct Heccer *pheccer, char *pcFilename)
{
    //- set default result: failure

    int iResult = 0;

    //- open file

    FILE *pfile = fopen(pcFilename, "w");

    if (!pfile)
    {
	return(0);
    }

    //- serialize heccer to file

    iResult = HeccerSerialize(pheccer, pfile);

    //- return result

    return(iResult);
}


