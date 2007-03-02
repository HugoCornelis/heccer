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


#ifndef HECCER_SERVICE_H
#define HECCER_SERVICE_H


struct Heccer;

struct TranslationService;

struct TranslationServiceData;


typedef int (*ComponentInspector)(struct Heccer *pheccer, struct TranslationService *pts);

struct TranslationService
{
    //m service specific data

    struct TranslationServiceData *ptsd;

    //t guess need to map this to the biological level as defined by
    //t Neurospaces, not done yet.

    //t additionally need to map this to the 'spatial and temporal
    //t accuracy level'.  Not sure how to do that yet.

    //m initializes segment intermediary

    ComponentInspector segments_inspector;

    //m initializes mechanism intermediary

    ComponentInspector mechanisms_inspector;
};


#endif


