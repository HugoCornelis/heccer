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


#ifndef HECCER_OUTPUTGENERATOR_H
#define HECCER_OUTPUTGENERATOR_H


#include <stdio.h>


struct OutputGenerator
{
    //m number of variables

    int iVariablesAllocated;

    int iVariablesActive;

    //m all variables

    double **ppdVariables;

    //m output file stream

    FILE *pfileOutput;
};

struct OutputGenerator * OutputGeneratorNew(void);

int
OutputGeneratorAddVariable
(struct OutputGenerator * pog, char *pcName, void *pvVariable);

int OutputGeneratorAnnotatedStep(struct OutputGenerator * pog, char * pc);


#endif

