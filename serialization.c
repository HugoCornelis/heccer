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

    //- read the serialization version ID

    char pcSerializationVersion[strlen(HECCER_SERIALIZATION_VERSION) + 1];

    fread
	(pcSerializationVersion,
	 sizeof(char),
	 strlen(HECCER_SERIALIZATION_VERSION) + 1,
	 pfile);

    if (0 != strcmp(pcSerializationVersion, HECCER_SERIALIZATION_VERSION))
    {
	return(NULL);
    }

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

		    if (HeccerMechanismLink(pheccerResult))
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

    //- read data: axres

    if (fread(&pheccer->vm.iAxres, sizeof(pheccer->vm.iAxres), 1, pfile) != 1)
    {
	return(0);
    }

    pheccer->vm.pdAxres = (double *)calloc(pheccer->vm.iAxres, sizeof(double));

    if (!pheccer->vm.pdAxres)
    {
	return(0);
    }

    if (fread(pheccer->vm.pdAxres, sizeof(pheccer->vm.pdAxres[0]), pheccer->vm.iAxres, pfile) != pheccer->vm.iAxres)
    {
	return(0);
    }

    //- read data: results

    if (fread(&pheccer->vm.iResults, sizeof(pheccer->vm.iResults), 1, pfile) != 1)
    {
	return(0);
    }

    pheccer->vm.pdResults = (double *)calloc(pheccer->vm.iResults, sizeof(double));

    if (!pheccer->vm.pdResults)
    {
	return(0);
    }

    if (fread(pheccer->vm.pdResults, sizeof(pheccer->vm.pdResults[0]), pheccer->vm.iResults, pfile) != pheccer->vm.iResults)
    {
	return(0);
    }

    //- read data: Vm

    if (fread(&pheccer->vm.iVms, sizeof(pheccer->vm.iVms), 1, pfile) != 1)
    {
	return(0);
    }

    pheccer->vm.pdVms = (double *)calloc(pheccer->vm.iVms, sizeof(double));

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

    memset(&pheccer->tgt, 0, sizeof(pheccer->tgt));

    memset(&pheccer->tsmt, 0, sizeof(pheccer->tsmt));

    memset(&pheccer->vm, 0, sizeof(pheccer->vm));

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
/// \brief Deserialize the mechanisms of this heccer from the given stream.
/// 

static
int
HeccerDeserializeMechanisms
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

    /// mechanism addressables

    if (fread(&pheccer->vm.iMats, sizeof(pheccer->vm.iMats), 1, pfile) != 1)
    {
	return(0);
    }

    pheccer->vm.pvMats = (int *)calloc(pheccer->vm.iMats, 1);

    if (!pheccer->vm.pvMats)
    {
	return(0);
    }

    if (fread(pheccer->vm.pvMats, 1, pheccer->vm.iMats, pfile) != pheccer->vm.iMats)
    {
	return(0);
    }

    /// indexing from mops or mats number towards one of the above

    pheccer->vm.ppvCMatsIndex = (void **)calloc(pheccer->vm.iCompartments + 1, sizeof(void *));

    if (!pheccer->vm.ppvCMatsIndex)
    {
	return(0);
    }

    if (fread(pheccer->vm.ppvCMatsIndex, sizeof(pheccer->vm.ppvCMatsIndex[0]), pheccer->vm.iCompartments + 1, pfile) != pheccer->vm.iCompartments + 1)
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

    pheccer->vm.ppvMatsIndex = (void **)calloc(pheccer->vm.iMatNumber + 1, sizeof(void *));

    if (!pheccer->vm.ppvMatsIndex)
    {
	return(0);
    }

    if (fread(pheccer->vm.ppvMatsIndex, sizeof(pheccer->vm.ppvMatsIndex[0]), pheccer->vm.iMatNumber + 1, pfile) != pheccer->vm.iMatNumber + 1)
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
/// \brief Serialize this heccer to the given stream.
/// 

int
HeccerSerialize
(struct Heccer *pheccer, FILE *pfile)
{
    //- set default result: ok

    int iResult = 1;

    //- write the serialization version ID

    fwrite
	(HECCER_SERIALIZATION_VERSION,
	 sizeof(char),
	 strlen(HECCER_SERIALIZATION_VERSION) + 1,
	 pfile);

    //- serialize main structure

    iResult = iResult && HeccerSerializeMain(pheccer, pfile);

    //- serialize compartments

    iResult = iResult && HeccerSerializeCompartments(pheccer, pfile);

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

    //- read number of math components

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

    /// mechanism addressables

    if (fwrite(&pheccer->vm.iMats, sizeof(pheccer->vm.iMats), 1, pfile) != 1)
    {
	return(0);
    }

    if (fwrite(pheccer->vm.pvMats, 1, pheccer->vm.iMats, pfile) != pheccer->vm.iMats)
    {
	return(0);
    }

    /// indexing from mops or mats number towards one of the above

    if (fwrite(pheccer->vm.ppvCMatsIndex, sizeof(pheccer->vm.ppvCMatsIndex[0]), pheccer->vm.iCompartments + 1, pfile) != pheccer->vm.iCompartments + 1)
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

    if (fwrite(pheccer->vm.ppvMatsIndex, sizeof(pheccer->vm.ppvMatsIndex[0]), pheccer->vm.iMatNumber + 1, pfile) != pheccer->vm.iMatNumber + 1)
    {
	return(0);
    }


    //- return result

    return(iResult);
}


