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

#include "heccer/heccer.h"
#include "heccer/serialization.h"


static
int
HeccerDeserializeCompartments
(struct Heccer *pheccer, FILE *pfile);


static
int
HeccerSerializeCompartments
(struct Heccer *pheccer, FILE *pfile);


/// **************************************************************************
///
/// SHORT: HeccerDeserialize()
///
/// ARGS.:
///
///	pheccer...: a heccer.
///	pfile.....: file pointer.
///
/// RTN..: int
///
///	success of operation.
///
/// DESCR: Deserialize this heccer from the given stream.
///
/// **************************************************************************

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

    //t deserialize main structure instead of ...
    //t ... construct a default heccer

    pheccerResult = HeccerNew(NULL, NULL, NULL, NULL);

    if (pheccerResult)
    {
	//- deserialize compartments

	if (HeccerDeserializeCompartments(pheccerResult, pfile))
	{
	    //!
	}
	else
	{
	    pheccerResult = NULL;
	}
    }

    //t mechanisms

    //- return result

    return(pheccerResult);
}


/// **************************************************************************
///
/// SHORT: HeccerDeserializeCompartments()
///
/// ARGS.:
///
///	pheccer...: a heccer.
///	pfile.....: file pointer.
///
/// RTN..: int
///
///	success of operation.
///
/// DESCR: Deserialize the compartments of this heccer from the given stream.
///
/// **************************************************************************

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


/// **************************************************************************
///
/// SHORT: HeccerSerialize()
///
/// ARGS.:
///
///	pheccer...: a heccer.
///	pfile.....: file pointer.
///
/// RTN..: int
///
///	success of operation.
///
/// DESCR: Serialize this heccer to the given stream.
///
/// **************************************************************************

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

    //t serialize main structure

    //- serialize compartments

    iResult = iResult && HeccerSerializeCompartments(pheccer, pfile);

    //t mechanisms

    //- return result

    return(iResult);
}


/// **************************************************************************
///
/// SHORT: HeccerSerializeCompartments()
///
/// ARGS.:
///
///	pheccer...: a heccer.
///	pfile.....: file pointer.
///
/// RTN..: int
///
///	success of operation.
///
/// DESCR: Serialize the compartments of this heccer to the given stream.
///
/// **************************************************************************

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


