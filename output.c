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


#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "heccer/output.h"


#define ALLOCATE_VARIABLES 10000


/// 
/// \arg pog output generator.
/// \arg pcName name of the variable.
/// \arg pvVariable pointer to the variable, assumed is double *
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Schedule a variable for output.
/// 

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


/// 
/// \arg pog output generator.
/// \arg pc annotation for current values.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Output all variable values, with the given annotation.
/// 

int OutputGeneratorAnnotatedStep(struct OutputGenerator * pog, char * pc)
{
    //- set default result : ok

    int iResult = 1;

    //- write out the annotation

    if (pc)
    {
	/// \todo choose between yaml style and xplot style using options

	fprintf(pog->pfileOutput, "%s", pc);

/* 	fprintf(pog->pfileOutput, "%s:", pc); */
    }

    //- write out all the variables

    int i;

    for (i = 0 ; i < pog->iVariablesActive ; i++)
    {
	if (*pog->ppdVariables[i] != pog->dBase)
	{
	    fprintf(pog->pfileOutput, " %g", *pog->ppdVariables[i]);
	}
    }

    fprintf(pog->pfileOutput, "\n");

    //- return result

    return(iResult);
}


/// 
/// \arg pog output generator.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Close files, destruct the output generator.
/// 

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

    /// \note prevent accidental misuse

    pog->iVariablesAllocated = -9238;

    free(pog);

    //- return result

    return(iResult);
}


/// 
/// \arg pog output generator.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Flush files.
/// 

int OutputGeneratorFlush(struct OutputGenerator * pog)
{
    //- set default result : ok

    int iResult = 1;

    //- if file

    if (pog->pfileOutput)
    {
	//- flush file buffers to disk

	if (fflush(pog->pfileOutput) == EOF)
	{
	    iResult = 0;
	}
    }

    //- return result

    return(iResult);
}


/// 
/// \arg pog output generator.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Open files.
/// 

int OutputGeneratorInitiate(struct OutputGenerator * pog)
{
    //- set default result : ok

    int iResult = 1;

/*     //- if file not opened yet */

/*     if (!pog->pfileOutput) */
    {
	/// \todo what again did I mean with this todo ?

	/// \todo file name taken from options

	//- open file

	pog->pfileOutput = fopen(pog->pcFilename, "w");

	if (!pog->pfileOutput)
	{
	    return(0);
	}
    }

    //- return result

    return(iResult);
}


/// 
/// \arg pcFilename file name to write output to.
/// 
/// \return struct OutputGenerator *
/// 
///	Output generator, NULL for failure.
/// 
/// \brief Output generator.
/// 

struct OutputGenerator * OutputGeneratorNew(char *pcFilename)
{
    //- set default result : failure

    struct OutputGenerator * pogResult = NULL;

    //- allocate output generator

    pogResult = (struct OutputGenerator *)calloc(1, sizeof(struct OutputGenerator));

    if (!pogResult)
    {
	return(NULL);
    }

    //- allocate output variables

    pogResult->ppdVariables = (double **)calloc(ALLOCATE_VARIABLES, sizeof(double *));

    pogResult->iVariablesAllocated = ALLOCATE_VARIABLES;

    if (!pogResult->ppdVariables)
    {
	free(pogResult);

	return(NULL);
    }

    //- allocate filename

    pogResult->pcFilename = calloc(1 + strlen(pcFilename), sizeof(char));

    if (!pogResult->pcFilename)
    {
	free(pogResult->ppdVariables);

	free(pogResult);

	return(NULL);
    }

    strcpy(pogResult->pcFilename, pcFilename);

    //- initialize base value: FLT_MAX

    pogResult->dBase = FLT_MAX;

    //- return result

    return(pogResult);
}


/// 
/// \arg pog output generator.
/// \arg dTime simulation time.
/// 
/// \return int
/// 
///	success of operation.
/// 
/// \brief Output all variable values, at the given time.
///
/// \details This gets remapped to OutputGeneratorAnnotatedStep(),
/// with the time as annotation.
/// 

int OutputGeneratorTimedStep(struct OutputGenerator * pog, double dTime)
{
    //- set default result : ok

    int iResult = 1;

    char pc[100];

    sprintf(pc, "%g", dTime);

    iResult = OutputGeneratorAnnotatedStep(pog, pc);

    //- return result

    return(iResult);
}



