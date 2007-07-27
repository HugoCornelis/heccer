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


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "heccer/output.h"


#define ALLOCATE_VARIABLES 10000


/// **************************************************************************
///
/// SHORT: OutputGeneratorAddVariable()
///
/// ARGS.:
///
///	pog.........: output generator.
///	pcName......: name of the variable.
///	pvVariable..: pointer to the variable, assumed is double *
///
/// RTN..: int
///
///	success of operation.
///
/// DESCR: Schedule a variable for output.
///
/// **************************************************************************

int
OutputGeneratorAddVariable
(struct OutputGenerator * pog, char *pcName, void *pvVariable)
{
    //- set default result : ok

    int iResult = 1;

    if (pog->iVariablesActive >= ALLOCATE_VARIABLES)
    {
	return(0);
    }

    //- set next variable

    pog->ppdVariables[pog->iVariablesActive] = (double *)pvVariable;

    pog->iVariablesActive++;

    //- return result

    return(iResult);
}


/// **************************************************************************
///
/// SHORT: OutputGeneratorAnnotatedStep()
///
/// ARGS.:
///
///	pog...: output generator.
///	pc....: annotation for current values.
///
/// RTN..: int
///
///	success of operation.
///
/// DESCR: Output all variable values, with the given annotation.
///
/// **************************************************************************

int OutputGeneratorAnnotatedStep(struct OutputGenerator * pog, char * pc)
{
    //- set default result : ok

    int iResult = 1;

    //- write out the annotation

    if (pc)
    {
	//t choose between yaml style and xplot style using options

	fprintf(pog->pfileOutput, "%s", pc);

/* 	fprintf(pog->pfileOutput, "%s:", pc); */
    }

    //- write out all the variables

    int i;

    for (i = 0 ; i < pog->iVariablesActive ; i++)
    {
	fprintf(pog->pfileOutput, " %g", *pog->ppdVariables[i]);
    }

    fprintf(pog->pfileOutput, "\n");

    //- return result

    return(iResult);
}


/// **************************************************************************
///
/// SHORT: OutputGeneratorFinish()
///
/// ARGS.:
///
///	pog...: output generator.
///
/// RTN..: int
///
///	success of operation.
///
/// DESCR: Close files, destruct the output generator.
///
/// **************************************************************************

int OutputGeneratorFinish(struct OutputGenerator * pog)
{
    //- set default result : ok

    int iResult = 1;

    //- if file

    if (pog->pfileOutput)
    {
	//- close file

	if (fclose(pog->pfileOutput) == EOF)
	{
	    iResult = 0;
	}
    }

    //- free allocated memory

    free(pog->ppdVariables);

    //! prevent accidental misuse

    pog->iVariablesAllocated = -9238;

    free(pog);

    //- return result

    return(iResult);
}


/// **************************************************************************
///
/// SHORT: OutputGeneratorNew()
///
/// ARGS.:
///
///	pcFilename..: file name to write output to.
///
/// RTN..: struct OutputGenerator *
///
///	Output generator, NULL for failure.
///
/// DESCR: Output generator.
///
/// **************************************************************************

struct OutputGenerator * OutputGeneratorNew(char *pcFilename)
{
    //- set default result : failure

    struct OutputGenerator * pogResult = NULL;

    //- allocate output generator

    pogResult = (struct OutputGenerator *)calloc(1, sizeof(struct OutputGenerator));

    //- allocate output variables

    pogResult->ppdVariables = (double **)calloc(ALLOCATE_VARIABLES, sizeof(double *));

    pogResult->iVariablesAllocated = ALLOCATE_VARIABLES;

    //- allocate filename

    pogResult->pcFilename = calloc(1 + strlen(pcFilename), sizeof(char));

    strcpy(pogResult->pcFilename, pcFilename);

    //- if file not opened yet

/*     if (!pogResult->pfileOutput) */
    {
	//t file name taken from options

	pogResult->pfileOutput = fopen(pogResult->pcFilename, "w");

	if (!pogResult->pfileOutput)
	{
	    return(NULL);
	}
    }

    //- return result

    return(pogResult);
}


