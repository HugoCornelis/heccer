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


#ifndef HECCER_EVENT_DISTRIBUTOR_H
#define HECCER_EVENT_DISTRIBUTOR_H


struct EventDistributor;

struct EventDistributorTarget
{
    //m target object

    void *pvObject;

    //m called function

    //! decouples the event distributor from the target

    int (*pvFunction)();

};


struct EventDistributorData
{
    int iHappy;

    //m array of targets

    struct EventDistributorTarget *ppedt[];
};


//d a event distribution function

typedef int (*EventDistribute)(struct EventDistributor *ped, double dTime, int iTargets);

struct EventDistributor
{
    //m service specific data

    struct EventDistributorData *pedd;

    //m hand an event over to the event distributor

    //! decouples the event distributor from the source

    EventDistribute eventDistribute;

};


//f prototypes

/* extern EventDistribute HeccerEventDistribute; */

int HeccerEventDistribute(struct EventDistributor *ped, double dTime, int iTargets);


#endif


