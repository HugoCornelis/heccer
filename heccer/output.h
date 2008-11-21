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


#ifndef HECCER_OUTPUTGENERATOR_H
#define HECCER_OUTPUTGENERATOR_H


#include <stdio.h>


struct OutputGenerator
{
    /// number of variables

    int iVariablesAllocated;

    int iVariablesActive;

    /// all variables

    double **ppdVariables;

    /// output file stream

    char *pcFilename;

    FILE *pfileOutput;
};

int
OutputGeneratorAddVariable
(struct OutputGenerator * pog, char *pcName, void *pvVariable);

int OutputGeneratorAnnotatedStep(struct OutputGenerator * pog, char * pc);

int OutputGeneratorFinish(struct OutputGenerator * pog);

int OutputGeneratorInitiate(struct OutputGenerator * pog);

struct OutputGenerator * OutputGeneratorNew(char *pcFilename);

int OutputGeneratorTimedStep(struct OutputGenerator * pog, double dTime);


#endif


