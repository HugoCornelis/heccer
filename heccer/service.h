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


#ifndef HECCER_SERVICE_H
#define HECCER_SERVICE_H


struct Heccer;

struct TranslationService;

struct TranslationServiceData;


typedef int (*ComponentInspector)(struct Heccer *pheccer, struct TranslationService *pts);

struct TranslationService
{
    /// service specific data

    struct TranslationServiceData *ptsd;

    /// \todo guess need to map this to the biological level as defined by
    /// \todo Neurospaces, not done yet.

    /// \todo additionally need to map this to the 'spatial and temporal
    /// \todo accuracy level'.  Not sure how to do that yet.

    /// initializes segment intermediary

    ComponentInspector segments_inspector;

    /// initializes mechanism intermediary

    ComponentInspector mechanisms_inspector;
};


#endif


