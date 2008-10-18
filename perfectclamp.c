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


#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "heccer/perfectclamp.h"


/// 
/// 
/// \arg ppc voltage clamper.
///	pvVoltage...: pointer to the voltage variable, assumed is double *
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Clamp the given voltage variable.
/// \details 
/// 

int
PerfectClampAddVariable
(struct PerfectClamp * ppc, void *pvVoltage)
{
    //- set default result: ok

    int iResult = 1;

    if (ppc->iClampsActive >= 1)
    {
	return(0);
    }

    //- set next variable

    ppc->pdVoltage = (double *)pvVoltage;

    ppc->iClampsActive++;

    //- return result

    return(iResult);
}


/// 
/// 
/// \arg ppc voltage clamper.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Free the voltage clamper.
/// \details 
/// 

int PerfectClampFinish(struct PerfectClamp * ppc)
{
    //- set default result: ok

    int iResult = 1;

    //- close files

    if (ppc->pfile)
    {
	fclose(ppc->pfile);
    }

    if (ppc->pcFilename)
    {
	free(ppc->pcFilename);
    }

    //- free all allocated memory

    free(ppc->pcName);

    free(ppc);

    //- return result

    return(iResult);
}


/// 
/// 
/// \arg ppc voltage clamper.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Initiate the voltage clamper.
/// \details 
/// 

int PerfectClampInitiate(struct PerfectClamp * ppc)
{
    //- set default result: ok

    int iResult = 1;

    //- return result

    return(iResult);
}


/// 
/// 
/// \arg pcName name of this object.
/// 
/// \return struct PerfectClamp *
/// 
///	voltage clamper, NULL for failure.
/// 
/// \brief voltage clamper.
/// \details 
/// 

struct PerfectClamp * PerfectClampNew(char *pcName)
{
    //- set default result: failure

    struct PerfectClamp * ppcResult = NULL;

    //- allocate voltage clamper

    ppcResult = (struct PerfectClamp *)calloc(1, sizeof(struct PerfectClamp));

    if (!ppcResult)
    {
	return(NULL);
    }

    //- set name

    ppcResult->pcName = calloc(1 + strlen(pcName), sizeof(char));

    strcpy(ppcResult->pcName, pcName);

    //- return result

    return(ppcResult);
}


/// 
/// 
///	dCommand.....: command voltage, ignored if a filename is given.
///	pcFilename...: filename, file contains sequence of command voltages.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief set operation fields of voltage clamper.
/// \details 
/// 

int
PerfectClampSetFields
(struct PerfectClamp * ppc,
 double dCommand,
 char *pcFilename)
{
    //- set default result: ok

    int iResult = 1;

    //- set fields

    ppc->dCommand = dCommand;

    //- if a filename has been given

    if (pcFilename)
    {
	//- allocate filename

	ppc->pcFilename = calloc(1 + strlen(pcFilename), sizeof(char));

	strcpy(ppc->pcFilename, pcFilename);

	//- open file

	/// \note I need the qualification service overhere.

	ppc->pfile = fopen(pcFilename, "r");

	if (!ppc->pfile)
	{
	    fprintf(stderr, "warning: PerfectClampSetFields() cannot open command file\n");

	    PerfectClampFinish(ppc);

	    return(0);
	}

	//- file stays open during simulation

	/// \note we could also cache the file in memory, depending on an option or so.
    }

    //- return result

    return(iResult);
}


/// 
/// 
/// \arg ppc voltage clamper.
/// \arg dTime current simulation time.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Compute new currents to correct voltages.
/// \details 
/// 
/// \note 
/// 
///	Old current values are overwritten.
/// 

int PerfectClampSingleStep(struct PerfectClamp * ppc, double dTime)
{
    //- set default result: ok

    int iResult = 1;

    //- if running with a file open

    if (ppc->pfile)
    {
	//- read a command voltage from the file

	char pcStep[100];

	char pcCommand[100];

	int iEOF = fscanf(ppc->pfile, " %[^:]: %s", pcStep, pcCommand);

	ppc->dCommand = strtod(pcCommand, (char **)NULL);

	//- if end of file

	if (iEOF == EOF)
	{
	    //- rewind the file

	    if (fseek(ppc->pfile, 0L, SEEK_SET) != 0)
	    {
		fprintf(stderr, "warning: PerfectClampSingleStep() cannot rewind the command file\n");
	    }
	}
	else if (iEOF != 2)
	{
	    fprintf(stderr, "warning: PerfectClampSingleStep() read %i values from the command file (instead of 2)\n", iEOF);
	}

	//- set the output

	*ppc->pdVoltage = ppc->dCommand;
    }
    else
    {
	//- set the output

	*ppc->pdVoltage = ppc->dCommand;
    }

    //- return result

    return(iResult);
}


