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


#ifndef HECCER_NEUROSPACES_HECCER_H
#define HECCER_NEUROSPACES_HECCER_H


#define PRE_PROTO_TRAVERSAL 1

#include <neurospaces/neurospaces.h>


//s translator specific service data

struct TranslationServiceData
{
    //m root symbol in neurospaces

    struct PidinStack *ppistRoot;

    struct symtab_HSolveListElement *phsleRoot;

    //m the model to be solved by this instantiation

    int iModel;
};


struct Heccer *HeccerConstruct(void *pvNeurospaces, char *pcModel);


#endif


